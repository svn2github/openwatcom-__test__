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
* Description:  PowerPC type conversions.
*
****************************************************************************/


#include "standard.h"
#include "pattern.h"
#include "coderep.h"
#include "tables.h"
#include "opcodes.h"
#include "regset.h"
#include "funits.h"
#include "vergen.h"
#include "zoiks.h"
#include "model.h"
#include "rttable.h"
#include "rtclass.h"

extern  name    *       AllocS32Const( signed_32 );
extern  name    *       AllocTemp(type_class_def);
extern  instruction*    MakeUnary(opcode_defs,name*,name*,type_class_def);
extern  instruction*    MakeBinary(opcode_defs,name*,name*,name*,type_class_def);
extern  instruction*    MakeConvert(name*,name*,type_class_def,type_class_def);
extern  void            PrefixIns(instruction*,instruction*);
extern  instruction*    MakeMove(name*,name*,type_class_def);
extern  void            ReplIns(instruction*,instruction*);
extern  opcode_entry    *OpcodeTable( table_def );
extern  void            UpdateLive(instruction*,instruction*);

extern    int   RoutineNum;

static  opcode_entry    FSTODTable[] = {
/**************************************/
/*    from  to    eq       verify        gen             reg           fu*/
_Un( R,    R,   NONE ),   V_NO,         G_MOVE_FP,      RG_FLOAT,     FU_NO,
_Un( C,    ANY, NONE ),   V_NO,         R_FORCEOP1CMEM, RG_FLOAT,     FU_NO,
_Un( M,    ANY, NONE ),   V_NO,         R_MOVOP1TEMP,   RG_FLOAT,     FU_NO,
_Un( ANY,  M,   NONE ),   V_NO,         R_MOVRESTEMP,   RG_FLOAT,     FU_NO,
_Un( ANY,  ANY, NONE ),   V_NO,         G_UNKNOWN,      RG_FLOAT_NEED,FU_NO,
};


static instruction *cFSTOD( instruction *ins ) {

    ins->table = &FSTODTable[ 0 ];
    return( ins );
}

//FIXME: this is way too inefficient (and guaranteed to show up on a benchmark)
static  opcode_entry    RTCallTable[] = {
/***************************************/
/*    from  to    eq       verify        gen             reg           fu*/
_Un( ANY,  ANY, NONE ),   V_NO,         R_MAKECALL,     RG_FLOAT,     FU_NO,
};

static instruction *cI4TOD( instruction *ins ) {

    ins->table = &RTCallTable[ 0 ];
    return( ins );
}

static instruction *cU4TOD( instruction *ins ) {

    ins->table = &RTCallTable[ 0 ];
    return( ins );
}

static instruction *cDTOU4( instruction *ins ) {

    ins->table = &RTCallTable[ 0 ];
    return( ins );
}

#if 0
static  opcode_entry    FDToI4Table[] = {
/***************************************/
/*    from  to    eq       verify        gen             reg           fu*/
_Un( R,    M,   NONE ),   V_NO,         G_FREGTOMI4,    RG_FLOAT,     FU_NO,
_Un( M|C,  M,   NONE ),   V_NO,         R_MOVOP1TEMP,   RG_FLOAT,     FU_NO,
_Un( ANY,  R,   NONE ),   V_NO,         R_MOVRESTEMP,   RG_FD,        FU_NO,
_Un( R,    U,   NONE ),   V_NO,         R_FORCERESMEM,  RG_,          FU_NO,
_Un( ANY,  ANY, NONE ),   V_NO,         G_UNKNOWN,      RG_FLOAT_NEED,FU_NO,
};
#endif

static instruction *cDTOI4( instruction *ins ) {

    // ins->table = &FDToI4Table[ 0 ];
    ins->table = &RTCallTable[ 0 ];
    return( ins );
}

typedef enum {
    FIRST_METHOD = XX,  // last typeclass from typclass.h
    NA,
    OK,
    #define _C_( a )    a,
    #include "convert.h"
    #undef _C_
    LST
} conv_method;

typedef instruction *(*convert_rtn)( instruction * );

#define CONVERT_ROUTINE( x, gen, reg )                                                          \
static  opcode_entry    ctable_##x[] = {                                                        \
/**************************************/                                                        \
/*      from    to      eq              verify          gen             reg       fu */         \
_Un(    R,      R,      NONE ),         V_NO,           gen,            RG_##reg, FU_ALU,       \
_Un(    R,      M,      NONE ),         V_NO,           R_MOVRESTEMP,   RG_##reg, FU_ALU,       \
_Un(    M,      ANY,    NONE ),         V_NO,           R_MOVOP1TEMP,   RG_##reg, FU_ALU,       \
_Un(    ANY,    ANY,    NONE ),         V_NO,           G_UNKNOWN,      RG_##reg##_NEED, FU_ALU,\
};                                                                                              \
static instruction *c##x( instruction *ins ) { ins->table = &ctable_##x[0]; return( ins ); }

CONVERT_ROUTINE( Z1TO2, G_ZERO, BW );
CONVERT_ROUTINE( Z1TO4, G_ZERO, BD );
CONVERT_ROUTINE( Z1TO8, G_ZERO, BQ );
CONVERT_ROUTINE( Z2TO4, G_ZERO, WD );
CONVERT_ROUTINE( Z2TO8, G_ZERO, WQ );

CONVERT_ROUTINE( S1TO2, G_SIGN, BW );
CONVERT_ROUTINE( S1TO4, G_SIGN, BD );
CONVERT_ROUTINE( S1TO8, G_SIGN, BQ );
CONVERT_ROUTINE( S2TO4, G_SIGN, WD );
CONVERT_ROUTINE( S2TO8, G_SIGN, WQ );

CONVERT_ROUTINE( C8TO2, G_MOVE, QW );
CONVERT_ROUTINE( C8TO1, G_MOVE, QB );
CONVERT_ROUTINE( C4TO2, G_MOVE, DW );
CONVERT_ROUTINE( C4TO1, G_MOVE, DB );
CONVERT_ROUTINE( C2TO1, G_MOVE, WB );

static opcode_entry ctable_C8TO4[] = {
/************************************/
/*      from    to      eq              verify          gen             reg       fu */
_Un(    ANY,    ANY,    NONE ),         V_NO,           R_MOVELOW,      RG_,      FU_NO,
};

static instruction *cC8TO4( instruction *ins ) { ins->table = ctable_C8TO4; return( ins ); }

static opcode_entry ctable_S4TO8[] = {
/************************************/
/*      from    to      eq              verify          gen             reg       fu */
_Un(    ANY,    ANY,    NONE ),         V_NO,           R_SEX_4TO8,     RG_,      FU_NO,
};

static instruction *cS4TO8( instruction *ins ) { ins->table = ctable_S4TO8; return( ins ); }

static opcode_entry ctable_Z4TO8[] = {
/************************************/
/*      from    to      eq              verify          gen             reg       fu */
_Un(    ANY,    ANY,    NONE ),         V_NO,           R_CLRHI_4,      RG_,      FU_NO,
};

static instruction *cZ4TO8( instruction *ins ) { ins->table = ctable_Z4TO8; return( ins ); }


static convert_rtn ConvertRoutines[] = {
    #define _C_( a )    c##a,
    #include "convert.h"
    #undef _C_
};

static  conv_method         CvtTable[] = {
/*                               from*/
/*U1   I1     U2     I2     U4     I4     U8     I8     CP    PT    FS     FD    FL          to*/
OK,    OK,    C2TO1, C2TO1, C4TO1, C4TO1, U4,    I4,    C4TO1,C4TO1,U4,    U4,   U4,      /* U1*/
OK,    OK,    C2TO1, C2TO1, C4TO1, C4TO1, U4,    I4,    C4TO1,C4TO1,I4,    I4,   I4,      /* I1*/
Z1TO2, S1TO2, OK,    OK,    C4TO2, C4TO2, U4,    I4,    C4TO2,C4TO2,U4,    U4,   U4,      /* U2*/
Z1TO2, S1TO2, OK,    OK,    C4TO2, C4TO2, U4,    I4,    C4TO2,C4TO2,I4,    I4,   I4,      /* I2*/
Z1TO4, S1TO4, Z2TO4, S2TO4, OK,    OK,    C8TO4, C8TO4, OK,   OK,   FD,    DTOU4,DTOU4,   /* U4*/
Z1TO4, S1TO4, Z2TO4, S2TO4, OK,    OK,    C8TO4, C8TO4, OK,   OK,   FD,    DTOI4,DTOI4,   /* I4*/
U4,    U4,    U4,    U4,    Z4TO8, S4TO8, OK,    OK,    S4TO8,S4TO8,NA,    NA,   NA,      /* U8*/
U4,    I4,    U4,    I4,    Z4TO8, S4TO8, OK,    OK,    S4TO8,S4TO8,FD,    NA,   NA,      /* I8*/
NA,    NA,    NA,    NA,    OK,    OK,    NA,    NA,    OK,   OK,   NA,    NA,   NA,      /* CP*/
NA,    NA,    NA,    NA,    OK,    OK,    NA,    NA,    OK,   OK,   NA,    NA,   NA,      /* PT*/
I4,    I4,    I4,    I4,    I4,    FD,    FD,    FD,    NA,   NA,   OK,    FSTOD,FSTOD,   /* FS*/
I4,    I4,    I4,    I4,    U4TOD, I4TOD, NA,    NA,    NA,   NA,   OK,    OK,   OK,      /* FD*/
I4,    I4,    I4,    I4,    U4TOD, I4TOD, NA,    NA,    NA,   NA,   OK,    OK,   OK,      /* FL*/
};

extern  conv_method      AskHow( type_class_def fr, type_class_def to ) {
/************************************************************************
    return the conversion method required to convert from "fr" to "to"
*/

    if( to == XX || fr == XX ) {
        return( BAD );
    }
    return( CvtTable[  fr + to * XX  ] );
}

extern  bool    CvtOk( type_class_def fr, type_class_def to ) {
/**************************************************************
    return true if a conversion from "fr" to "to" can be done
*/

    if( fr == XX ) return( FALSE );
    if( to == XX ) return( FALSE );
    if( AskHow( fr, to ) != NA ) return( TRUE );
    return( FALSE );
}

extern  instruction     *rDOCVT( instruction *ins ) {
/***************************************************/

    name        *src;
    name        *dst;
    name        *temp;
    instruction *new_ins;
    conv_method how;

    src = ins->operands[ 0 ];
    dst = ins->result;
    if( src->n.name_class != XX && ins->base_type_class == XX ) {
        ins->base_type_class = src->n.name_class;
    }
    ins->head.state = INS_NEEDS_WORK;
    if( src->n.class == N_CONSTANT && src->c.const_type == CONS_ABSOLUTE
     && ins->type_class != XX ) {
        how = OK;
    } else {
        how = AskHow( ins->base_type_class, ins->type_class );
    }
    if( how < NA ) {
        temp = AllocTemp( how );
        new_ins = MakeConvert( src, temp, how, ins->base_type_class );
        ins->operands[ 0 ] = temp;
        ins->base_type_class = how;
        new_ins->table = NULL;
        PrefixIns( ins, new_ins );
        UpdateLive( new_ins, ins );
    } else if( how < LST && how > OK ) {
        new_ins = ConvertRoutines[ how - OK - 1 ]( ins );
    } else {
        new_ins = MakeMove( src, dst, ins->type_class );
        ReplIns( ins, new_ins );
        if( how != OK ) {
            _Zoiks( ZOIKS_092 );
        }
    }
    return( new_ins );
}

extern  void    LookupConvertRoutine( instruction *ins ) {
/********************************************************/

    int         rtn;

    #define _Munge( x, y )              ( (x) * XX + (y) )
    switch( _Munge( ins->base_type_class, ins->type_class ) ) {
    case _Munge( I4, FD ):
        rtn = RT_I4TOD;
        break;
    case _Munge( U4, FD ):
        rtn = RT_U4TOD;
        break;
    case _Munge( FD, I4 ):
        rtn = RT_DTOI4;
        break;
    case _Munge( FD, U4 ):
        rtn = RT_DTOU4;
        break;
    default:
        rtn = RT_NOP;
        break;
    }
    RoutineNum = rtn;
}
