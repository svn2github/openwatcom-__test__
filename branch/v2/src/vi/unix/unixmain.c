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
* Description:  Mainline for Unix systems.
*
****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __WATCOMC__
    #include <malloc.h>
    #include <process.h>
  #if defined( __X86__ )
    #include "stack.h"
  #endif
#else
    #include "clibext.h"
#endif
#include "vi.h"
#include "source.h"

int main( int argc, char *argv[] )
{
    static char buffer[FILENAME_MAX];
    argc = argc;
#ifndef __WATCOMC__
    _argc = argc;
    _argv = argv;
#endif
    EXEName = _cmdname(buffer);
#if defined( __WATCOMC__ ) && defined( __X86__ )
    InitialStack();
#endif
    VarAddGlobalStr( "OS", "unix" );
    Comspec = getenv( "SHELL" );
    InitializeEditor();
#if defined( __WATCOMC__ ) && defined( __X86__ )
    FinalStack();
#endif
    EditMain();
    return( 0 );

} /* main */