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


#include "vi.h"
#include "keys.h"
#include "subclass.h"
#include "hotkey.h"

/*
 * HotkeyProc - pass hotkeys on to root for various modeless 'bars'
 */
long WINEXP HotkeyProc( HWND hwnd, UINT msg, UINT wparam, LONG lparam )
{
    int         ch;

    switch( msg ) {
    case WM_KEYDOWN:
        ch = MapVirtualKeyToVIKey( wparam, HIWORD( lparam ) );
        if( ch == VI_KEY( F7 ) ||
            ch == VI_KEY( F8 ) ||
            ch == VI_KEY( F9 ) ) {
            return( SendMessage( Root, msg, wparam, lparam ) );
        }
        break;
    }

    return( CallWindowProc( SubclassGenericFindOldProc( hwnd ),
                            hwnd, msg, wparam, lparam ) );
}
