/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "standard.h"
#include "coderep.h"
#include "opcodes.h"
#include "procdef.h"
#include "symdbg.h"
#include "offset.h"
#include "pattern.h"
#include "sysmacro.h"
#include "model.h"
#include "ppcenc.h"
#include "ppcparm.h"

extern  seg_id          SetOP( seg_id );
extern  seg_id          AskCodeSeg( void );
extern  unsigned        DepthAlign( unsigned );
extern  void            CodeLabel( label_handle, unsigned );
extern  hw_reg_set      *GPRegs();
extern  hw_reg_set      *FPRegs();
extern  hw_reg_set      *ParmRegs();
extern  hw_reg_set      SaveRegs();
extern  void            GenMEMINS( uint_8, uint_8, uint_8, signed_16 );
extern  void            GenOPINS( uint_8, uint_8, uint_8, uint_8, uint_8 );
extern  void            GenOPIMM( uint_8, uint_8, uint_8, signed_16 );
extern  void            GenMTSPR( uint_8, uint_8, bool );
extern  pointer         CGAlloc( unsigned );
extern  void            CGFree( pointer );
extern  hw_reg_set      StackReg();
extern  hw_reg_set      ScratchReg();
extern  hw_reg_set      FrameReg();
extern  hw_reg_set      FrameBaseReg();
extern  hw_reg_set      TocReg();
extern  hw_reg_set      VarargsHomePtr();
extern  void            GenRET();
extern  sym_handle      AskForLblSym( label_handle );
extern  fe_attr         FEAttr( sym_handle );
extern  void            DbgRtnBeg( dbg_rtn *rtn,  offset lc );
extern  void            DbgProEnd( dbg_rtn *rtn, offset lc );
extern  void            DbgEpiBeg( dbg_rtn *rtn, offset lc );
extern  void            DbgRtnEnd( dbg_rtn *rtn, offset lc );
extern  offset          AskLocation();
extern  void            OutFuncStart( label_handle label, offset start, int line );
extern  void            OutFileStart( int line );
extern  void            OutFuncEnd( offset end );
extern void             OutPDataRec( label_handle label, uint_32 pro_size, uint_32 proc_end );
extern  hw_reg_set      FrameReg(void);
extern  uint_8          RegTrans(hw_reg_set);
extern  void            OutTOCRec( label_handle lbl );
extern  type_length     TempLocation( name * );

extern  proc_def        *CurrProc;
extern  block           *HeadBlock;
extern  type_length     MaxStack;

static  void    CalcUsedRegs() {
/******************************/


    block       *blk;
    instruction *ins;
    name        *result;
    hw_reg_set  used;

    CurrProc->targ.leaf = TRUE;
    HW_CAsgn( used, HW_EMPTY );
    blk = HeadBlock;
    while( blk != NULL ) {
        ins = blk->ins.hd.next;
        while( ins->head.opcode != OP_BLOCK ) {
            result = ins->result;
            if( result != NULL && result->n.class == N_REGISTER ) {
                HW_TurnOn( used, result->r.reg );
            }
            /* place holder for big label doesn't really zap anything*/
            if( ins->head.opcode != OP_NOP ) {
                HW_TurnOn( used, ins->zap->reg );
            }
            if( ins->head.opcode == OP_CALL ||
                ins->head.opcode == OP_CALL_INDIRECT ) {
                CurrProc->targ.leaf = FALSE;
            }
            ins = ins->head.next;
        }
        blk = blk->next_block;
    }
    HW_TurnOn( CurrProc->state.used, used );
}

extern  void    AddCacheRegs() {
/******************************/
    if( !CurrProc->targ.base_is_fp ) {
        HW_TurnOff( CurrProc->state.unalterable, FrameBaseReg() );
    }
}

#define _unused( x )    ( (x) = (x) )

static  void    initParmCache( stack_record *pc, type_length *offset ) {
/**********************************************************************/

    pc->start = *offset;
    pc->size = MaxStack;
    if( !CurrProc->targ.leaf ) {
        if( pc->size < ( 8 * 4 ) ) {
            pc->size = 8 * 4;
        }
    }
    if( pc->size > 0 ) {
        *offset += MaxStack;
    }
}

static  void    emitParmCacheProlog( stack_record *pc ) {
/*******************************************************/

    _unused( pc );
}

static  void    emitParmCacheEpilog( stack_record *pc ) {
/*******************************************************/

    _unused( pc );
}

static  void    initLocals( stack_record *locals, type_length *offset ) {
/***********************************************************************/

    locals->start = *offset;
    locals->size = CurrProc->locals.size;
    *offset += locals->size;
}

static  void    emitLocalProlog( stack_record *locals ) {
/*******************************************************/

    _unused( locals );
}

static  void    emitLocalEpilog( stack_record *locals ) {
/*******************************************************/

    _unused( locals );
}

static  uint_32 registerMask( hw_reg_set rs, hw_reg_set *rl ) {
/*************************************************************/

    hw_reg_set          *curr;
    uint_32             result;

    result = 0;
    for( curr = rl; !HW_CEqual( *curr, HW_EMPTY ); curr++ ) {
        if( HW_Ovlap( rs, *curr ) ) {
            result |= 1 << RegTrans( *curr );
        }
    }
    return( result );
}

static  uint_32 countBits( uint_32 value ) {
/******************************************/

    uint_32             r, l;

    r = ( value      ) & 0x55555555;
    l = ( value >> 1 ) & 0x55555555;
    value = r + l;
    r = ( value      ) & 0x33333333;
    l = ( value >> 2 ) & 0x33333333;
    value = r + l;
    r = ( value      ) & 0x0f0f0f0f;
    l = ( value >> 4 ) & 0x0f0f0f0f;
    value = r + l;
    r = ( value      ) & 0x00ff00ff;
    l = ( value >> 8 ) & 0x00ff00ff;
    value = r + l;
    r = ( value       ) & 0x0000ffff;
    l = ( value >> 16 ) & 0x0000ffff;
    value = r + l;
    return( value );
}

static  void    initSavedRegs( stack_record *saved_regs, type_length *offset ) {
/******************************************************************************/

    unsigned            num_regs;
    hw_reg_set          saved;

    saved = SaveRegs();
    if( CurrProc->targ.base_is_fp ) {
        HW_TurnOn( saved, FrameBaseReg() );
    }
#if 1
    // saved in previous frame's LR-save location below
    if( !CurrProc->targ.leaf ) {
        // this is really the value of LR (set up by first ins)
        HW_CTurnOn( saved, HW_D0 );
    }
#endif
    CurrProc->targ.gpr_mask = registerMask( saved, GPRegs() );
    CurrProc->targ.fpr_mask = registerMask( saved, FPRegs() );
    num_regs  = countBits( CurrProc->targ.gpr_mask );
    num_regs += countBits( CurrProc->targ.fpr_mask );
    saved_regs->size = num_regs * REG_SIZE;
    saved_regs->start = *offset;
    *offset += saved_regs->size;
}

#define STORE_DWORD     36
#define STORE_DOUBLE    54
#define LOAD_DWORD      32
#define LOAD_DOUBLE     50
#define ADDI_OPCODE     14

#define STACK_REG       1
#define FRAME_REG       31
#define VARARGS_PTR     14

static  void    genMove( uint_32 src, uint_32 dst ) {
/***************************************************/

    GenOPINS( 31, 144, dst, src, src );
}

static  void    genAdd( uint_32 src, signed_16 disp, uint_32 dst ) {
/******************************************************************/

    GenOPIMM( ADDI_OPCODE, dst, src, disp );
}

static  void    saveReg( uint_32 index, type_length offset, bool fp ) {
/*********************************************************************/

    uint_8              opcode;

    opcode = STORE_DWORD;
    if( fp ) {
        opcode = STORE_DOUBLE;
    }
    GenMEMINS( opcode, index, STACK_REG, offset );
}

static  void    loadReg( uint_32 index, type_length offset, bool fp ) {
/*********************************************************************/

    uint_8              opcode;
    uint_8              frame_reg;

    opcode = LOAD_DWORD;
    if( fp ) {
        opcode = LOAD_DOUBLE;
    }
    frame_reg = STACK_REG;
    if( CurrProc->targ.base_is_fp ) {
        frame_reg = FRAME_REG;
    }
    GenMEMINS( opcode, index, frame_reg, offset + CurrProc->locals.size );
}

static  int     regSize( bool fp ) {
/**********************************/

    return( fp ? 8 : 4 );
}

static  void    saveRegSet( uint_32 reg_set, type_length offset, bool fp ) {
/**************************************************************************/

    uint_32     index;
    uint_32     high_bit;

    index = sizeof( reg_set ) * 8 - 1;
    high_bit = 1 << index;
    while( reg_set != 0 ) {
        if( reg_set & high_bit ) {
            offset -= regSize( fp );
            saveReg( index, offset, fp );
        }
        reg_set <<= 1;
        index -= 1;
    }
}

static  void    loadRegSet( uint_32 reg_set, type_length offset, bool fp ) {
/**************************************************************************/

    uint_32     index;

    index = 0;
    while( reg_set != 0 ) {
        if( reg_set & 1 ) {
            loadReg( index, offset, fp );
            offset += regSize( fp );
        }
        index++;
        reg_set >>= 1;
    }
}

static  void    emitSavedRegsProlog( stack_record *saved_regs ) {
/***************************************************************/

    type_length         offset;

    offset = saved_regs->start + saved_regs->size - regSize( FALSE );
    saveRegSet( CurrProc->targ.gpr_mask, offset, FALSE );
    if( CurrProc->targ.gpr_mask == 0 ) {
        offset -= regSize( TRUE ) - regSize( FALSE );   // make it sp-8 for first double
    }
    offset -= countBits( CurrProc->targ.gpr_mask ) * regSize( FALSE );
    saveRegSet( CurrProc->targ.fpr_mask, offset, TRUE );
}

static  void    emitSavedRegsEpilog( stack_record *saved_regs ) {
/***************************************************************/

    type_length         offset;

    offset = saved_regs->start - regSize( TRUE );
    loadRegSet( CurrProc->targ.fpr_mask, offset, TRUE );
    if( CurrProc->targ.fpr_mask == 0 ) {
        offset += regSize( TRUE ) - regSize( FALSE );
    }
    offset += countBits( CurrProc->targ.fpr_mask ) * regSize( TRUE );
    loadRegSet( CurrProc->targ.gpr_mask, offset, FALSE );
}

static  void    initVarargs( stack_record *varargs, type_length *offset ) {
/*************************************************************************/

    varargs->start = *offset;
    varargs->size = 0;
}

static  void    emitVarargsProlog( stack_record *varargs ) {
/**********************************************************/

    type_length         offset;
    int                 i;

    _unused( varargs );
    if( CurrProc->state.attr & ROUTINE_HAS_VARARGS ) {
        // save our registers in our caller's context - uhg!
        offset = CurrProc->targ.frame_size + STACK_HEADER_SIZE;
        for( i = CurrProc->state.parm.gr; i <= LAST_SCALAR_PARM_REG; i++ ) {
            saveReg( i, offset + ( i - FIRST_SCALAR_PARM_REG ) * 4, FALSE );
        }
    }
}

static  void    emitVarargsEpilog( stack_record *varargs ) {
/**********************************************************/

    // NB see FrameSaveEpilog below
    _unused( varargs );
}

static  void    initSlop( stack_record *slop, type_length *offset ) {
/*******************************************************************/

    type_length         off;

    off = *offset;
    slop->start = off;
    slop->size = 0;
    if( off & ( STACK_ALIGNMENT - 1 ) ) {
        slop->size = STACK_ALIGNMENT - ( off & ( STACK_ALIGNMENT - 1 ) );
        *offset += slop->size;
    }
}

static  void    emitSlopProlog( stack_record *fs ) {
/**************************************************/

    _unused( fs );
}

static  void    emitSlopEpilog( stack_record *fs ) {
/**************************************************/

    _unused( fs );
}

static  void    initStackHeader( stack_record *stk, type_length *offset ) {
/*************************************************************************/

    stk->start = *offset;
    stk->size = STACK_HEADER_SIZE;
    *offset += stk->size;
}

static  void    emitStackHeaderProlog( stack_record *stk ) {
/**********************************************************/

    _unused( stk );
}

static  void    emitStackHeaderEpilog( stack_record *stk ) {
/**********************************************************/

    _unused( stk );
}


static  signed_32 frameSize( stack_map *map ) {
/*********************************************/

    signed_32           size;

    size = map->varargs.size + map->slop.size + map->saved_regs.size +
                map->locals.size + map->parm_cache.size + map->stack_header.size;
    if( size == ( map->slop.size + map->stack_header.size ) &&
        CurrProc->targ.leaf ) {
        // we are a leaf function whose stack frame consists only of a
        // stack header and some slop to make it 16-byte aligned, so instead
        // don't use any stack frame
        size = 0;
    }
    assert( ( size & ( STACK_ALIGNMENT - 1 ) ) == 0 );
    return( size );
}

static  void    initStackLayout( stack_map *map ) {
/*************************************************/

    type_length         offset;

    offset = 0;
    initStackHeader( &map->stack_header, &offset );
    initParmCache( &map->parm_cache, &offset );
    initLocals( &map->locals, &offset );
    initSavedRegs( &map->saved_regs, &offset );
    initSlop( &map->slop, &offset );
    initVarargs( &map->varargs, &offset );
}

static  void    emitProlog( stack_map *map ) {
/********************************************/

    type_length         frame_size;

    frame_size = frameSize( map );
    if( !CurrProc->targ.leaf ) {
        // mflr r0
        GenMTSPR( 0, SPR_LR, TRUE );
    }
    if( frame_size != 0 ) {
        // stwu sp,-frame_size(sp)
        GenMEMINS( 37, STACK_REG, STACK_REG, -frame_size );
        emitVarargsProlog( &map->varargs );
        emitSlopProlog( &map->varargs );
        emitSavedRegsProlog( &map->saved_regs );
        emitLocalProlog( &map->locals );
        emitParmCacheProlog( &map->parm_cache );
        emitStackHeaderProlog( &map->stack_header );
        if( CurrProc->targ.base_is_fp ) {
            genMove( STACK_REG, FRAME_REG );
        }
    }
}

static  void    emitEpilog( stack_map *map ) {
/********************************************/

    type_length         frame_size;
    uint_8              frame_reg;

    frame_size = frameSize( map );
    if( frame_size != 0 ) {
        emitStackHeaderEpilog( &map->stack_header );
        emitParmCacheEpilog( &map->parm_cache );
        emitLocalEpilog( &map->locals );
        emitSavedRegsEpilog( &map->saved_regs );
        emitSlopEpilog( &map->slop );
        emitVarargsEpilog( &map->varargs );
        if( !CurrProc->targ.leaf ) {
            GenMTSPR( 0, SPR_LR, FALSE );
        }
        frame_reg = STACK_REG;
        if( CurrProc->targ.base_is_fp ) {
            frame_reg = FRAME_REG;
        }
        genAdd( frame_reg, frame_size, STACK_REG );
    }
}

extern  void    GenProlog() {
/***************************/

    seg_id              old;
    label_handle        label;
    offset              lc;

    old = SetOP( AskCodeSeg() );
    lc = AskLocation();
    CurrProc->targ.proc_start = lc;
    label = CurrProc->label;
    if( _IsModel( NUMBERS ) ) {
        OutFileStart( HeadBlock->ins.hd.line_num );
    }
    OutTOCRec( label );
    CodeLabel( label, DepthAlign( PROC_ALIGN ) );
    if( _IsModel( NUMBERS ) ) {
        OutFuncStart( label, lc, HeadBlock->ins.hd.line_num );
    }
    if( _IsModel( DBG_LOCALS ) ) {  // d1+ or d2
        DbgRtnBeg( CurrProc->targ.debug, lc );
    }
    // keep stack aligned
    CurrProc->locals.size = _RoundUp( CurrProc->locals.size, 16 );
    CurrProc->parms.base = 0;
    CurrProc->parms.size = CurrProc->state.parm.offset;
    CalcUsedRegs();
    initStackLayout( &CurrProc->targ.stack_map );
    CurrProc->targ.frame_size = frameSize( &CurrProc->targ.stack_map );
    emitProlog( &CurrProc->targ.stack_map );
    lc = AskLocation();
    CurrProc->targ.pro_size = lc;
    if( _IsModel( DBG_LOCALS ) ) {  // d1+ or d2
  //    DbgRetOffset( CurrProc->parms.base - CurrProc->targ.base_adjust
  //                    - ret_size );
        DbgProEnd( CurrProc->targ.debug, lc );
    }
    SetOP( old );
}


extern  void    GenEpilog() {
/***************************/

    seg_id              old;
    offset              lc;

    old = SetOP( AskCodeSeg() );
    if( _IsModel( DBG_LOCALS ) ){  // d1+ or d2
        lc = AskLocation();
        DbgEpiBeg( CurrProc->targ.debug, lc );
    }
    // Pop();
    emitEpilog( &CurrProc->targ.stack_map );
    GenRET();
    CurrProc->prolog_state |= GENERATED_EPILOG;
    lc = AskLocation();
    if( _IsModel( DBG_LOCALS ) ){  // d1+ or d2
        DbgRtnEnd( CurrProc->targ.debug, lc );
    }
    if( _IsModel( NUMBERS ) ) {
        OutFuncEnd( lc );
    }
    OutPDataRec( CurrProc->label, CurrProc->targ.pro_size, lc );
    SetOP( old );
}


extern  int     AskDisplaySize( int level ) {
/*******************************************/

    return( 0 );
}

extern  void    InitStackDepth( block *blk ) {
/********************************************/
}

extern  type_length     PushSize( type_length len ) {
/***************************************************/

    if( len < REG_SIZE ) return( REG_SIZE );
    return( len );
}

extern  type_length     NewBase( name *op ) {
/*******************************************/

    return( TempLocation( op ) );
}

extern  int     ParmsAtPrologue( void ) {
/***************************************/

    return( 0 );
}
