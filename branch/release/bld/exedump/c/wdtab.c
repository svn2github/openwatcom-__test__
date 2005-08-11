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
* Description:  NE/LE/LX name tables processing.
*
****************************************************************************/


#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>
#include <unistd.h>

#include "wdglb.h"
#include "wdfunc.h"

extern struct int_entry_pnt     *Entry_pnts = NULL;

/*
 * Dump the tables
 */
void Dmp_ne_tbls( void )
/**********************/
{
    prs_ent_tab( New_exe_off + Os2_head.entry_off, Os2_head.entry_size );
    Banner( "Resident Names Table" );
    dmp_res_nonres_tab( New_exe_off + Os2_head.resident_off );
    dmp_mod_ref_tab( New_exe_off + Os2_head.module_off, Os2_head.modrefs );
    if( Os2_head.import_off != Os2_head.entry_off )
        dmp_import_tab( New_exe_off + Os2_head.import_off );
    dmp_entry_tab();
    Wdputslc( "\n" );
    Banner( "Nonresident Names Table" );
    dmp_res_nonres_tab( Os2_head.nonres_off );
    Dmp_relocs();
}

/*
 * Dump the tables
 */
void Dmp_le_lx_tbls( void )
/*************************/
{
    unsigned_32     size;

    Banner( "Resident Names Table" );
    dmp_res_nonres_tab( New_exe_off + Os2_386_head.resname_off );
    Dmp_fixpage_tab( New_exe_off + Os2_386_head.fixpage_off,
                    Os2_386_head.fixrec_off - Os2_386_head.fixpage_off );
    Dmp_fixrec_tab( New_exe_off + Os2_386_head.fixrec_off );
    size = Os2_386_head.impproc_off - Os2_386_head.impmod_off;
    if( size > 1 ) {
        Wdputslc( "\n" );
        Banner( "Import Module Name Table" );
        dmp_imp_tab( New_exe_off + Os2_386_head.impmod_off, size );
    }
    size = Os2_386_head.fixup_size + Os2_386_head.fixpage_off
                    - Os2_386_head.impproc_off;
    if( size > 1 ) {
        Wdputslc( "\n" );
        Banner( "Import Procedure Name Table" );
        dmp_imp_tab( New_exe_off + Os2_386_head.impproc_off, size );
    }
    dmp_ent_tab( New_exe_off + Os2_386_head.entry_off );
    Wdputslc( "\n" );
    Banner( "Nonresident Names Table" );
    dmp_res_nonres_tab( Os2_386_head.nonres_off );
}

/*
 * Dump the Resident or Nonresident Names Tables
 */
static void dmp_res_nonres_tab( unsigned_32 res_nam_tab )
/*******************************************************/
{
    unsigned_8                      string_len;

    if( res_nam_tab <= New_exe_off ) return;
    Wlseek( res_nam_tab );
    for( ;; ) {
        Wread( &string_len, sizeof( unsigned_8 ) );
        if( string_len == 0 ) {
            return;
        }
        dmp_res_nonres_nam( string_len );
    }
}

/*
 * Dump a resident/nonresident name
 */
static void dmp_res_nonres_nam( unsigned_16 string_len )
/******************************************************/
{
    char *                          resident;
    unsigned_16                     entry_index;

    resident = alloca( string_len + 2 );
    if( resident == NULL ) {
        Wdputslc( "Error! Dynamic memory exausted.\n" );
        longjmp( Se_env, 1 );
    }
    Wread( resident, string_len );
    Wread( &entry_index, sizeof( unsigned_16 ) );
    resident[ string_len ] = '\0';
    Wdputs( resident );
    if( Form == FORM_NE ) {
        Dmp_ordinal( entry_index );
    } else {
        Wdputs( "   ordinal = " );
        Puthex( entry_index, 4 );
    }
    Wdputslc( "\n" );
}

/*
 * Dump the module reference table
 */
static void dmp_imp_tab( unsigned_32 proc_off, unsigned_32 size_proc )
/********************************************************************/
{
    unsigned_8                      string_len;
    unsigned_16                     size;
    char *                          imp_nam;

    Wlseek( proc_off );
    for( size = 0; size < size_proc; size += string_len + 1 ) {
        Wread( &string_len, sizeof( unsigned_8 ) );
        imp_nam = Wmalloc( string_len + 1 );
        Wread( imp_nam, string_len );
        imp_nam[ string_len ] = '\0';
        Wdputs( imp_nam );
        Wdputslc( "\n" );
    }
}

/*
 * Dump the module reference table
 */
static void dmp_mod_ref_tab( unsigned_32 mod_ref, unsigned_16 num_mod_ref )
/*************************************************************************/
{
    unsigned_16                     *mod_ref_tab;
    unsigned_16                     size_mod_ref;
    unsigned_16                     ref_num;
    char                            *imp_nam;
    unsigned_32                     imp_off;
    unsigned_8                      string_len;

    if( num_mod_ref == 0 ) {
        return;
    }
    Wdputslc( "\n" );
    Banner( "Module Reference Table" );
    Wlseek( mod_ref );
    size_mod_ref = num_mod_ref * sizeof( unsigned_16 );
    mod_ref_tab = Wmalloc( size_mod_ref );
    Wread( mod_ref_tab, size_mod_ref );
    Int_mod_ref_tab = Wmalloc( num_mod_ref * sizeof( unsigned_8 * ) );
    for( ref_num = 0; ref_num != num_mod_ref; ++ref_num ) {
        imp_off = New_exe_off + mod_ref_tab[ ref_num ] + Os2_head.import_off;
        Wlseek( imp_off );
        Wread( &string_len, sizeof( unsigned_8 ) );
        imp_nam = Wmalloc( string_len + 1 );
        Wread( imp_nam, string_len );
        imp_nam[ string_len ] = '\0';
        Wdputs( imp_nam );
        Wdputslc( "\n" );
        Int_mod_ref_tab[ ref_num ] = imp_nam;
    }
    free( mod_ref_tab );
}

/*
 * Dump the Imported Names Tables
 */
static void dmp_import_tab( unsigned_32 imp_nam_tab )
/***************************************************/
{
    unsigned_8                      string_len;
    char                            *resident;

    Wlseek( imp_nam_tab );
    Wread( &string_len, sizeof( unsigned_8 ) );
    if( string_len == 0 ) {
        return;
    }
    Wdputslc( "\n" );
    Banner( "Imported Name Table" );
    for( ;; ) {
        resident = alloca( string_len );
        if( resident == NULL ) {
            Wdputslc( "Error! Dynamic memory exausted.\n" );
            longjmp( Se_env, 1 );
        }
        Wread( resident, string_len );
        resident[ string_len ] = '\0';
        Wdputs( resident );
        Wdputslc( "\n" );
        Wread( &string_len, sizeof( unsigned_8 ) );
        if( string_len == 0 ) {
            return;
        }
    }
}

/*
 * Dump the Entry Table
 */
static void dmp_ent_tab( unsigned_32 ent_tab )
/********************************************/
{
    flat_bundle_prefix      ent_bund_pfx;

    Wlseek( ent_tab );
    Wread( &ent_bund_pfx, sizeof( flat_bundle_prefix ) );
    if( !ent_bund_pfx.b32_cnt ) {
        return;
    }
    Wdputslc( "\n" );
    Banner( "Entry Point Table" );
    for( ; ent_bund_pfx.b32_cnt != 0; ) {
        Wdputs( "number of entries in bundle = " );
        Puthex( ent_bund_pfx.b32_cnt, 2 );
        Wdputslc( "\ntype = " );
        Puthex( ent_bund_pfx.b32_type, 2 );
        if( ent_bund_pfx.b32_type != FLT_BNDL_EMPTY ) {
            Wdputslc( "\nobject number = " );
            Puthex( ent_bund_pfx.b32_obj, 4 );
        }
        Wdputslc( "\n" );
        for( ; ent_bund_pfx.b32_cnt != 0; ent_bund_pfx.b32_cnt-- ) {
            dmp_ent_type( ent_bund_pfx.b32_type );
        }
        Wread( &ent_bund_pfx, sizeof( flat_bundle_prefix ) );
    }
    Wdputslc( "\n" );
}

/*
 * Dump the Entry Table
 */
static void dmp_ent_type( unsigned_8 type )
/*****************************************/
{
    flat_bundle_entry32     ent_bund32;
    flat_bundle_entry16     ent_bund16;
    flat_bundle_gate16      gate_bund;
    flat_bundle_entryfwd    ent_bund_fwd;

    switch( type ) {
    case FLT_BNDL_EMPTY:
        break;
    case FLT_BNDL_ENTRY16:
        Wread( &ent_bund16, sizeof( flat_bundle_entry16 ) );
        Wdputslc( "\nflags = " );
        Puthex( ent_bund16.e32_flags, 2 );
        Wdputs( "   offset = " );
        Puthex( ent_bund16.e32_offset, 4 );
        if( ent_bund16.e32_flags & ENTRY_EXPORTED ) {
            Wdputs( "  EXPORTED" );
        }
        break;
    case FLT_BNDL_GATE16:
        Wread( &gate_bund, sizeof( flat_bundle_gate16 ) );
        Wdputslc( "\nflags = " );
        Puthex( gate_bund.e32_flags, 2 );
        Wdputs( "   offset = " );
        Puthex( gate_bund.offset, 4 );
        Wdputs( "   callgate = " );
        Puthex( gate_bund.callgate, 4 );
        if( gate_bund.e32_flags & ENTRY_EXPORTED ) {
            Wdputs( "  EXPORTED" );
        }
        break;
    case FLT_BNDL_ENTRY32:
        Wread( &ent_bund32, sizeof( flat_bundle_entry32 ) );
        Wdputslc( "\nflags = " );
        Puthex( ent_bund32.e32_flags, 2 );
        Wdputs( "   offset = " );
        Puthex( ent_bund32.e32_offset, 8 );
        if( ent_bund32.e32_flags & ENTRY_EXPORTED ) {
            Wdputs( "  EXPORTED" );
        }
        break;
    case FLT_BNDL_ENTRYFWD:
        Wread( &ent_bund_fwd, sizeof( flat_bundle_entryfwd ) );
        Wdputslc( "\nflags = " );
        Puthex( ent_bund_fwd.e32_flags, 2 );
        Wdputs( "   module ordinal = " );
        Puthex( ent_bund_fwd.modord, 4 );
        Wdputs( "   offset or ordinal = " );
        Puthex( ent_bund_fwd.value, 8 );
        if( ent_bund_fwd.e32_flags & ENTRY_EXPORTED ) {
            Wdputs( "  EXPORTED" );
        }
        break;
    }
}

/*
 * Parse the Entry Table
 */
static void prs_ent_tab( unsigned_32 ent_tab, unsigned_16 ent_tab_len )
/*********************************************************************/
{
    struct bundle_prefix    *ent_bund;
    struct bundle_prefix    *init_ent_bund;
    unsigned_16             ent_pnt_index;
    unsigned_16             num_ent_pnts;

    if( ent_tab_len == 0 ) {
        return;
    }
    Wlseek( ent_tab );
    ent_bund = Wmalloc( ent_tab_len );
    init_ent_bund = ent_bund;
    Wread( ent_bund, ent_tab_len );
    ent_pnt_index = 1;
    for( ; ent_bund->number != 0; ) {
        num_ent_pnts = ent_bund->number;
        switch( ent_bund->type ) {
        case 0:                   /* just incrementing entry table index */
            ++ent_bund;
            break;
        case MOVABLE_ENTRY_PNT:       /* movable segment                 */
            ent_bund = dmp_movable_seg_ent_pnts( num_ent_pnts,
                ++ent_bund, ent_pnt_index );
            break;
        default:                  /* fixed segment                       */
            ent_bund = dmp_fixed_seg_ent_pnts( num_ent_pnts,
                ++ent_bund, ent_pnt_index, ent_bund->type );
            break;
        }
        ent_pnt_index += num_ent_pnts;
    }
    free( init_ent_bund );
}

void *dmp_fixed_seg_ent_pnts( unsigned_16 num_ent_pnts,
        void *ent_pnts, unsigned_16 ent_pnt_index, unsigned_16 seg_num )
/**********************************************************************/
{
    struct fixed_record             *fix_ent;
    struct int_entry_pnt            *new;

    fix_ent = ent_pnts;
    for( ; num_ent_pnts != 0; num_ent_pnts-- ) {
        new = new_ent_pnt();
        new->ordinal = ent_pnt_index++;
        new->seg_num = seg_num;
        new->offset = fix_ent->entry;
        new->ent_flag = fix_ent->info;
        ++fix_ent;
    }
    return( fix_ent );
}

void *dmp_movable_seg_ent_pnts( unsigned_16 num_ent_pnts,
                        void *ent_pnts, unsigned_16 ent_pnt_index )
/*****************************************************************/
{
    struct movable_record           *mov_ent;
    struct int_entry_pnt            *new;

    mov_ent = ent_pnts;
    for( ; num_ent_pnts != 0; num_ent_pnts-- ) {
        new = new_ent_pnt();
        new->ordinal = ent_pnt_index++;
        new->ent_flag = mov_ent->info;
        new->seg_num = mov_ent->entrynum;
        new->offset = mov_ent->entry;
        ++mov_ent;
    }
    return( mov_ent );
}

/*
 * allocate a new int_entry_pnt structure
 */
struct int_entry_pnt *new_ent_pnt( void )
/***************************************/
{
    struct int_entry_pnt    *new_ent;

    new_ent = Wmalloc( sizeof( struct int_entry_pnt ) );
    new_ent->next = Entry_pnts;
    Entry_pnts = new_ent;
    return( new_ent );
}

/*
 * dump an ordinal entry point
 */
void Dmp_ordinal( unsigned_16 ord )
/*********************************/
{
    struct int_entry_pnt    *find;

    for( find = Entry_pnts; find != NULL; find = find->next ) {
        if( find->ordinal == ord ) {
            dmp_an_ord( find );
            return;
        }
    }
    Wdputs( " unknown ordinal " );
    Puthex( ord, 4 );
}

/*
 * dump the entry point table
 */
static void dmp_entry_tab( void )
/*******************************/
{
    struct int_entry_pnt    *find;

    if( Entry_pnts == NULL ) {
        return;
    }
    Wdputslc( "\n" );
    Banner( "Entry Point Table" );
    for( find = Entry_pnts; find != NULL; find = find->next ) {
        dmp_an_ord( find );
        Wdputslc( "\n" );
    }
}

static void dmp_an_ord( struct int_entry_pnt *find )
/**************************************************/
{
    unsigned_16     flag;

    Wdputc( '.' );
    Putdec( find->ordinal );
    Wdputs( " seg " );
    Puthex( find->seg_num, 4 );
    Wdputs( " off " );
    Puthex( find->offset, 4 );
    Wdputs( " parm " );
    flag = find->ent_flag;
    Puthex( flag >> IOPL_WORD_SHIFT, 4 );
    if( flag & ENTRY_EXPORTED ) {
        Wdputs( " EXPORTED" );
    }
    if( flag & ENTRY_SHARED ) {
        Wdputs( "|SHAREDATA" );
    }
}
