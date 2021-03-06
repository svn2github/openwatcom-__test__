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


#include "gdefn.h"


_WCRTLINK short _WCI86FAR _CGRAPH _grtext( short x, short y, char _WCI86FAR *string )
/*===============================================================

   This routine prints a text string using the current text settings.
   The letters are clipped.  The routine returns a success flag. */

{
    short           success;

    if( _GrProlog() ) {
        success = _L2grtext( _VtoPhysX( x ), _VtoPhysY( y ), string );
        _GrEpilog();
    } else {
        success = 0;
    }
    return( success );
}

Entry( _GRTEXT, _grtext ) // alternate entry-point


short _WCI86FAR _L2grtext( short x, short y, char _WCI86FAR *string )
/*=========================================================

   This routine prints a text string using the current text settings.
   The letters are clipped.  The routine returns a success flag. */

{
    _L1Text( x, y, string );
    return( TRUE );
}
