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
* Description:  Symbol mangling routines.
*
****************************************************************************/


#include "asmglob.h"

#include "asmsym.h"
#include "asmalloc.h"
#include "directiv.h"
#include "mangle.h"


/* constants used by the name manglers ( changes ) */
#define     NORMAL              0
#define     USCORE_FRONT        1
#define     USCORE_BACK         2
#define     REM_USCORE_FRONT    4
#define     REM_USCORE_BACK     8
#define     UPPERCASE           16

static char *AsmMangler( struct asm_sym *sym, char *buffer )
/***************************************************/
{
    char *name;

    if( buffer == NULL ) {
        name = AsmAlloc( strlen( sym->name ) + 1 );
        strcpy( name, sym->name );
        return( name );
    } else {
        strcpy( buffer, sym->name );
        return( buffer );
    }
}

static char *CMangler( struct asm_sym *sym, char *buffer )
/*************************************************/
{
    char                *name;
    char                *ptr = sym->name;
    uint                changes = NORMAL;
    uint                additional_size = 1; // for null

    if( Options.watcom_c_mangler ) {
        switch( Options.naming_convention ) {
        case DO_NOTHING:
            return( AsmMangler( sym, buffer ));
        case ADD_USCORES:
            if( sym->state == SYM_PROC ) {
                changes |= USCORE_BACK;
            } else {
                switch( sym->mem_type ) {
                case T_NEAR:
                case T_FAR:
                case EMPTY:
                    changes |= USCORE_BACK;
                    break;
                default:
                    changes |= USCORE_FRONT;
                }
            }
            break;
        case REMOVE_USCORES:
            if( sym->state == SYM_PROC ) {
                changes |= REM_USCORE_BACK;
            } else {
                switch( sym->mem_type ) {
                case T_NEAR:
                case T_FAR:
                case EMPTY:
                    changes |= REM_USCORE_BACK;
                    break;
                default:
                    changes |= REM_USCORE_FRONT;
                }
            }
        }
        if( sym->state == SYM_PROC ) {
            if( ( sym->langtype == LANG_C ) || ( sym->langtype == LANG_STDCALL ) ) {
                changes |= USCORE_BACK;
            } else if( ( sym->langtype >= LANG_BASIC ) && ( sym->langtype <= LANG_PASCAL ) ) {
                changes |= UPPERCASE;
            }
        }
    } else {
        if( ( sym->langtype == LANG_C ) || ( sym->langtype == LANG_STDCALL ) ) {
            changes |= USCORE_FRONT;
        } else if( ( sym->langtype >= LANG_BASIC ) && ( sym->langtype <= LANG_PASCAL ) ) {
            changes |= UPPERCASE;
        } else {
            return( AsmMangler( sym, buffer ));
        }
    }

    #define USCORE "_"

    if( changes & USCORE_FRONT ) {
        additional_size++;
    }
    if( changes & USCORE_BACK ) {
        additional_size++;
    }
    if( changes & REM_USCORE_FRONT ) {
        if( *ptr == '_' ) {
            ptr++;
        }
    }

    if( buffer == NULL ) {
        name = AsmAlloc( strlen( ptr ) + additional_size );
    } else {
        name = buffer;
    }

    if( changes & USCORE_FRONT ) {
        strcpy( name, USCORE );
    } else {
        strcpy( name, NULLS );
    }
    strcat( name, ptr );
    if( changes & UPPERCASE ) {
        strupr( name );
    }
    if( changes & USCORE_BACK ) {
        strcat( name, USCORE );
    } else if( changes & REM_USCORE_BACK ) {
        ptr = name + strlen( name ) - 1;
        if( *ptr == '_' ) {
            *ptr = NULLC;
        }
    }
    return( name );
}

typedef char *(*mangle_func)( struct asm_sym *, char * );

static mangle_func GetMangler( char *mangle_type )
{
    mangle_func         mangle;

    mangle = NULL;
    if( mangle_type != NULL ) {
        if( stricmp( mangle_type, "C" ) == 0 ) {
            mangle = CMangler;
        } else if( stricmp( mangle_type, "N" ) == 0 ) {
            mangle = AsmMangler;
        } else {
            AsmErr( UNKNOWN_MANGLER, mangle_type );
        }
    }
    return( mangle );
}

char *Mangle( struct asm_sym *sym, char *buffer )
{
    mangle_func mangle;

    mangle = sym->mangler;
    if( mangle == NULL ) {
        mangle = GetMangler( Options.default_name_mangler );
        if( mangle == NULL ) {
            if( sym->langtype == LANG_NONE ) {
                mangle = AsmMangler;
            } else {
                mangle = CMangler;
            }
        }
        sym->mangler = mangle;
    }
    return( mangle( sym, buffer ) );
}

void SetMangler( struct asm_sym *sym, char *mangle_type, int langtype )
/*********************************************************************/
{
    mangle_func mangle;

    if( langtype != LANG_NONE )
        sym->langtype = langtype;
    mangle = GetMangler( mangle_type );
    if( mangle == NULL ) {
        /* nothing to do */
    } else if( sym->mangler == NULL ) {
        sym->mangler = mangle;
    } else if( sym->mangler != mangle ) {
        AsmErr( CONFLICTING_MANGLER, sym->name );
    }
}
