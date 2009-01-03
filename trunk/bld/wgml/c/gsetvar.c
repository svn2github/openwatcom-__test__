/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  process :set tag, .se and .sr keywords and symbolic substitution
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"



/* construct symbol name and optionally subscript from input
 *
 *
 */

char    *scan_sym( char * p, symvar * sym, sub_index * subscript )
{
    size_t      k;
    char    *   sym_start;
    inputcb *   cb = input_cbs;
    char        quote;

    scan_err = false;
    sym->next = NULL;
    sym->flags = 0;
    *subscript = no_subscript;          // not subscripted

    while( *p && *p == ' ' ) {          // skip over spaces
        p++;
    }
    if( *p == '"' || *p == '\'' ) {
        quote = *p++;
    } else {
        quote = '\0';
    }
    if( *p == '*' ) {                   // local var
        p++;
        sym->flags = local_var;
    }
    sym_start = p;
    sym->name[ 0 ] = '\0';

    k = 0;
    while( *p && test_symbol_char( *p ) ) {

        if( k < SYM_NAME_LENGTH ) {
            if( (k == 3) && (sym->name[ 0 ] != '$') ) {
                if( sym->name[ 0 ] == 's' &&
                    sym->name[ 1 ] == 'y' &&
                    sym->name[ 2 ] == 's' ) {

                    sym->name[ 0 ] = '$';   // create sys shortcut $
                    k = 1;
                }
            }
            sym->name[ k++ ] = tolower( *p );
            sym->name[ k ] = '\0';
        } else {
            if( !scan_err ) {
                scan_err = true;
                if( !ProcFlags.suppress_msg ) {
                    // SC--074 For the symbol '%s'
                    //     The length of a symbol cannot exceed ten characters
                    if( cb->fmflags & II_macro ) {
                        out_msg( "ERR_SYM_NAME_too_long '%s'\n"
                            "The length of a symbol cannot exceed 10 characters\n"
                            "\t\t\tLine %d of macro '%s'\n",
                            sym_start, cb->s.m->mac->name, cb->s.m->lineno );
                    } else {
                        out_msg( "ERR_SYM_NAME_too_long '%s'\n"
                            "The length of a symbol cannot exceed 10 characters\n"
                            "\t\t\tLine %d of macro '%s'\n",
                            sym_start, cb->s.f->lineno, cb->s.f->filename );
                    }
                    if( inc_level > 1) {
                        show_include_stack();
                    }
                    err_count++;
                }
            }
        }
        p++;
    }

    if( p == sym_start ) {              // special for &*
        if( (sym->flags & local_var) && (input_cbs->fmflags & II_macro) ) {
            strcpy_s( sym->name, SYM_NAME_LENGTH, MAC_STAR_NAME );
        } else {
            scan_err = true;
            if( !ProcFlags.suppress_msg ) {
                out_msg( "ERR_SYMBOL_NAME_missing %s\n", sym_start );
                err_count++;
                if( inc_level > 1) {
                    show_include_stack();
                }
            }
        }
    }
    if( quote && quote == *p ) {        // over terminating quote
        p++;
//  } else {
//      if( (*p != '=') && (*p != '(')  && (*p != ')') && (*p != ' ') ) {
//          scan_err = true;
//      }
    }
    if( !scan_err && (*p == '(') ) {    // subscripted ?
        char    *   psave = p;
        int         sign  = 1;          // default positive
        long        val   = 0;
        sub_index   var_ind;
        symsub  *   symsubval;
        int         rc;

        p++;
        if( *p == ')' ) {               // () is auto increment
            p++;
            var_ind = 0;
            if( sym->flags & local_var )  {
                rc = find_symvar( &input_cbs->local_dict, sym->name,
                              var_ind, &symsubval );
            } else {
                rc = find_symvar( &global_dict, sym->name, var_ind,
                                  &symsubval );
            }
            if( rc > 0 ) {              // variable exists use last_auto_inc
                *subscript = symsubval->base->last_auto_inc + 1;
            } else {
                *subscript = 1;         // start with index 1
            }
            sym->flags |= auto_inc + subscripted;
        } else {
            if( !isdigit( *p ) ) {
                if( *p == '-' ) {
                    sign = -1;
                } else if( *p == '+' ) {
                    sign = 1;
                } else {
                    scan_err = true;
                }
            }
            while( *p && *p != ')' ) {
                if( isdigit( *p ) ) {
                    val = val * 10 + *p - '0';
                }
                p++;
            }
            if( !scan_err && (*p == ')') ) {
                p++;
            }
            *subscript = val * sign;
            if( scan_err ) {
               p = psave;
            }
        }
    }
    return( p );
}

/***************************************************************************/
/*  processing  SET                                                        */
/*                                                                         */
/*                          = <character string>                           */
/*         .SE       symbol = <numeric expression>                         */
/*                          <OFF>                                          */
/*   symbol may be subscripted (3) or () for auto increment 1 - n          */
/*                                                                         */
/*         .se x1     'string            case 1                            */
/*         .se x2  =  'string            case 2 a                          */
/*         .se x2  =  'string'           case 2 b                          */
/*         .se x2  =  "string"           case 2 b                          */
/*         .se x2     off                case 3                            */
/*         .se n1  =  1234               case 2                            */
/*         .se n2  =  (1+(2+5)/6)        case 4                            */
/*         .se n2  =  -1+(2+5)/6)        case 4                            */
/*                                                                         */
/***************************************************************************/

void    scr_se( void )
{
    char        *   p;
    char        *   valstart;
    symvar          sym;
    sub_index       subscript;
    int             rc;
    symvar      * * working_dict;
    symsub      *   symsubval;

    subscript = no_subscript;           // not subscripted
    scan_err = false;
    p = scan_sym( scan_start, &sym, &subscript );

    if( sym.flags & local_var ) {
        working_dict = &input_cbs->local_dict;
    } else {
        working_dict = &global_dict;
    }

    if( ProcFlags.blanks_allowed ) {
        while( *p && *p == ' ' ) {      // skip over spaces
            p++;
        }
    }
    if( *p == '\0' ) {
        if( !ProcFlags.suppress_msg ) {
            out_msg( "WNG_SYMBOL_VALUE_MISSING for %s\n", sym.name );
            if( inc_level > 1) {
                show_include_stack();
            }
            wng_count++;
        }
        scan_err = true;
    }
    if( !scan_err ) {
        if( (*p == '=') || (*p == '\'') ) {
            if( *p == '=' ) {
                p++;                    // over =
            }
            if( ProcFlags.blanks_allowed ) {
                while( *p && *p == ' ' ) {  // skip over spaces
                    p++;
                }
            }
            valstart = p;
            if( *valstart == '\'' || *valstart == '"' ) { // quotes ?
                p++;
                while( *p && (*valstart != *p) ) { // look for quote end
                    ++p;
                }
                if( *p == *valstart ) { // delete quotes case 2 b
                    valstart++;
                    *p = '\0';
                } else {
                    if( *valstart == '\'' ) {   // case 1 and 2a
                        valstart++;
                    }
                }
            } else {                    // case 2 and 4
                getnum_block    gn;
                condcode        cc;

                gn.argstart      = valstart;
                gn.argstop       = scan_stop;
                gn.ignore_blanks = 1;

                cc = getnum( &gn );     // try numeric expression evaluation
                if( cc != notnum ) {
                    valstart = gn.resultstr;
                }                       // if notnum treat as character value
            }

            rc = add_symvar( working_dict, sym.name, valstart, subscript,
                             sym.flags );

        } else {                        // OFF value = delete variable ?
            if( tolower( *p )       == 'o' &&
                tolower( *(p + 1) ) == 'f' &&
                tolower( *(p + 2) ) == 'f' &&
                *(p + 3)            == '\0' ) { // case 3

                p += 3;
                rc = find_symvar( working_dict, sym.name, subscript,
                                  &symsubval );
                if( rc == 2 ) {
                    symsubval->base->flags |= deleted;
                }
            } else {
                if( !ProcFlags.suppress_msg ) {
                     out_msg( "WNG_SYMBOL_VALUE_INVALID for %s (%s)\n",
                              sym.name, p );
                     wng_count++;
                }
                scan_err = true;
            }
        }
    }
    return;
}

