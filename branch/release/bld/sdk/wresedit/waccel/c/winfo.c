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


#define STRICT
#include <windows.h>
#include <string.h>
#include "wglbl.h"
#include "wmem.h"
#include "waccel.h"
#include "winfo.h"

/****************************************************************************/
/* external function prototypes                                             */
/****************************************************************************/

/****************************************************************************/
/* macro definitions                                                        */
/****************************************************************************/

/****************************************************************************/
/* type definitions                                                         */
/****************************************************************************/

/****************************************************************************/
/* static function prototypes                                               */
/****************************************************************************/

/****************************************************************************/
/* static variables                                                         */
/****************************************************************************/

WAccelInfo * WINEXPORT WAccAllocAccelInfo ( void )
{
    WAccelInfo *info;

    info = (WAccelInfo *) WMemAlloc ( sizeof(WAccelInfo) );

    memset ( info, 0, sizeof(WAccelInfo) );

    return ( info );
}

void WINEXPORT WAccFreeAccelInfo ( WAccelInfo *info )
{
    if ( info ) {
        if ( info->res_name ) {
            WMemFree ( info->res_name );
        }
        if ( info->file_name ) {
            WMemFree ( info->file_name );
        }
        if ( info->data ) {
            WMemFree ( info->data );
        }
        WMemFree ( info );
    }
}

