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
* Description:  Base 2 logarithm routine.
*
****************************************************************************/


#include "variety.h"
#include <math.h>
#include "mathcode.h"
#include "ifprag.h"
#include "mathlib.h"

#define log2_of_e    1.44269504888963407

_WMRTLINK double __log2( double x )
{
    return( log2( x ) );
}

_WMRTLINK double log2( double x )
/*******************************/
{
    if( x <= 0.0 ) {
//        x = _matherr( x == 0.0 ? SING : DOMAIN, "log2", &x, &x, -HUGE_VAL );
        x = __log87_err( x, FUNC_LOG2 );
    } else {
        x =  log(x) * log2_of_e;
    }
    return( x );
}
