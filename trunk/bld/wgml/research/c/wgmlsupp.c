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
* Description:  Defines functions required by research programs which must
*               link to the wgml code but which cannot be linked to because
*               they are in wgml.c and linking with wgml.obj would create
*               an executable with two main() functions, which the debugger
*               cannot handle reasonably. 
*                   free_inc_fp()
*                   free_resources()
*                   get_line()
*                   get_macro_line()
*                   my_exit()
*                   reopen_inc_fp()
*                   show_include_stack()
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__ 1

#include <errno.h>
#include <stdbool.h>    // Needed, but not included by, "gtype.h".
#include <stdint.h>     // Needed, but not included by, "gtype.h".

#include "copfiles.h"   // Needed, but not included by, "gvars.h".
#include "gtype.h"      // Needed, but not included by, "gvars.h".
#include "gvars.h"
#include "wgml.h"

/* Static functions from wgml.c. */

static  bool    free_inc_fp( void )
{
    inputcb *   ip;
    filecb  *   cb;
    int         rc;

    ip = input_cbs;
    while( ip != NULL ) {              // as long as input stack is not empty
        if( ip->fmflags & II_file ) {   // if file (not macro)
            if( (cb = ip->s.f) != NULL ) {
                if( (cb->flags & FF_open) ) {   // and file is open
                    rc = fgetpos( cb->fp, &cb->pos );
                    if( rc != 0 ) {
                        strerror_s( buff2, buf_size, errno );
                        g_err( err_file_io, buff2, cb->filename );
                        err_count++;
                        g_suicide();
                    }
                    rc = fclose( cb->fp );
                    if( rc != 0 ) {
                        strerror_s( buff2, buf_size, errno );
                        g_err( err_file_io, buff2, cb->filename );
                        err_count++;
                        g_suicide();
                    }
                    cb->flags &= ~FF_open;
                    return( true );
                }
            }
        }
        ip = ip->prev;                  // next higher input level
    }
    return( false );                    // nothing to close
}

static  void    get_macro_line( void )
{
    macrocb *   cb;

    if( input_cbs->fmflags & II_file ) {
        g_err( err_logic_mac );
        show_include_stack();
        err_count++;
        g_suicide();
    }
    cb = input_cbs->s.m;

    if( cb->macline == NULL ) {         // no more macrolines
        input_cbs->fmflags |= II_eof;
        cb->flags          |= FF_eof;
        cb->flags          &= ~FF_startofline;
        *buff2              = '\0';
    } else {
        cb->lineno++;
        cb->flags          |= FF_startofline;
        cb->flags          &= ~FF_eof;
        input_cbs->fmflags &= ~II_eof;
        strcpy_s( buff2, buf_size, cb->macline->value );
        cb->macline         = cb->macline->next;
    }
}

static void reopen_inc_fp( filecb *cb )
{
    int         rc;
    errno_t     erc;
    errno_t     erc2;

    if( ! cb->flags & FF_open ) {
        for( ;; ) {
            erc = fopen_s( &cb->fp, cb->filename, "rb" );
            if( erc == 0 ) break;
            erc2 = errno;
            if( errno != ENOMEM && errno != ENFILE && errno != EMFILE ) break;
            if( !free_inc_fp() ) break; // try closing an include file
        }
        if( erc == 0 ) {
            rc = fsetpos( cb->fp, &cb->pos );
            if( rc != 0 ) {
                strerror_s( buff2, buf_size, errno );
                g_err( err_file_io, buff2, cb->filename );
                err_count++;
                g_suicide();
            }
            cb->flags |= FF_open;
        } else {
            strerror_s( buff2, buf_size, erc2 );
            g_err( err_file_io, buff2, cb->filename );
            err_count++;
            g_suicide();
        }
    }
    return;
}

/* Global functions from wgml.c. */

bool free_resources( errno_t in_errno )
{
    if( in_errno == ENOMEM) out_msg( "ERR_NOMEM_AVAIL\n" );
    else out_msg( "Out of file handles!\n" );
    return( false );
}

bool get_line( void )
{
    filecb      *   cb;
    char        *   p;
    inp_line    *   pline;

    if( input_cbs->hidden_head != NULL ) {  // line was previously split,
        strcpy( buff2, input_cbs->hidden_head->value ); // take 2nd part
        pline = input_cbs->hidden_head;
        input_cbs->hidden_head = input_cbs->hidden_head->next;
        mem_free( pline );
        if( input_cbs->hidden_head == NULL ) {
            input_cbs->hidden_tail = NULL;
        }
    } else {
        if( input_cbs->pe_cb.count > 0 ) {  // .pe perform active
            strcpy( buff2, input_cbs->pe_cb.line );
            input_cbs->pe_cb.count--;
            if( input_cbs->pe_cb.count <= 0 ) {
                reset_pe_cb();
            }
        } else {
            if( input_cbs->fmflags & II_macro ) {
                get_macro_line();       // input from macro line
            } else {
                cb = input_cbs->s.f;    // input from file
                if( !(cb->flags & FF_open) ) {
                    g_info( err_inf_reopen );
                    show_include_stack();
                    reopen_inc_fp( cb );
                }
                do {
                    fgetpos( cb->fp, &cb->pos );// remember position for label
                    p = fgets( buff2, buf_size, cb->fp );
                    if( p != NULL ) {
                        if( cb->lineno >= cb->linemax ) {
                            input_cbs->fmflags |= II_eof;
                            cb->flags |= FF_eof;
                            cb->flags &= ~FF_startofline;
                            *buff2 = '\0';
                            break;
                        }
                        cb->lineno++;
                        cb->flags |= FF_startofline;

                        if( cb->flags & FF_crlf ) {// try to delete CRLF at end
                            p += strlen( p ) - 1;
                            if( *p == '\r' ) {
                                *p-- = '\0';
                                if( *p == '\n' ) {
                                    *p-- = '\0';
                                }
                            } else if( *p == '\n' ) {
                                *p-- = '\0';
                                if( *p == '\r' ) {
                                    *p-- = '\0';
                                }
                            }
                        }
                    } else {
                        if( feof( cb->fp ) ) {
                            input_cbs->fmflags |= II_eof;
                            cb->flags |= FF_eof;
                            cb->flags &= ~FF_startofline;
                            *buff2 = '\0';
                            break;
                        } else {
                            strerror_s( buff2, buf_size, errno );
                            g_err( err_file_io, buff2, cb->filename );

                            err_count++;
                            g_suicide();
                        }
                    }
                } while( cb->lineno < cb->linemin );
            }
        }
    }

    buff2_lg = strnlen_s( buff2, buf_size );
    *(buff2 + buff2_lg) = '\0';
    *(buff2 + buff2_lg + 1) = '\0';
    if( input_cbs->fmflags & II_file ) {
        input_cbs->s.f->usedlen = buff2_lg;
    }

    if( !(input_cbs->fmflags & II_eof) && GlobalFlags.research &&
        GlobalFlags.firstpass ) {
        printf( "%s\n", buff2 );
    }
    return( !(input_cbs->fmflags & II_eof) );
}

void my_exit( int rc )
{
    exit( rc );
}

void show_include_stack( void )
{
    inputcb *   ip;
    char        linestr[MAX_L_AS_STR];
    char        linemac[MAX_L_AS_STR];

    if( inc_level > 1 ) {
        ip = input_cbs;
        while( ip != NULL ) {
            switch( ip->fmflags & II_input ) {
            case    II_file:
                utoa( ip->s.f->lineno, linestr, 10 );
                g_info( err_inf_line_file, linestr, ip->s.f->filename );
                break;
            case    II_tag :
                g_info( err_inf_tag, ip->s.m->tag->name );
                // fallthrough
            case    II_macro :
                utoa( ip->s.m->lineno, linestr, 10 );
                utoa( ip->s.m->mac->lineno, linemac, 10 );
                g_info( err_inf_mac_def, linestr, ip->s.m->mac->name,
                        linemac, ip->s.m->mac->mac_file_name);
                break;
            default:
                g_info( err_inc_unknown );
                break;
            }
            ip = ip->prev;
        }
    }
    return;
}

