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
* Description:  Main C library entry point for Linux
*
****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "exitwmsg.h"
#include "initfini.h"
#include "thread.h"
#include "rtdata.h"
#include "syslinux.h"

int     _argc;                      /* argument count  */
char    **_argv;                    /* argument vector */

/* address of FP exception handler */
#if defined( __386__ )
extern  void    (*__FPE_handler)(int);

static void __null_FPE_rtn( int i )
{
}
#endif

extern int main( int, char **, char ** );

void __cdecl _LinuxMain( int argc, char **argv, char **arge )
{
//    thread_data *tdata;

    // Initialise the heap. To do this we call sbrk() with
    // a value of 0, which will return the current top of the
    // process address space which is where we start the heap.
    _curbrk             = (unsigned)sbrk( 0 );

    // TODO: Need to find the end of the stack from the kernel! For now
    //       we make it big enough to cover the heap. This will work, but
    //       stack checking will not.
    _STACKLOW           = _curbrk;
    _argc               = argc;
    _argv               = argv;
    environ             = arge;
#if defined( __386__ )
    __FPE_handler =     &__null_FPE_rtn;
#endif
    __InitRtns( 1 );
//    tdata = __alloca( __ThreadDataSize );
//    memset( tdata, 0, __ThreadDataSize );
//    tdata->__data_size = __ThreadDataSize;
    __InitRtns( 255 );
    _amblksiz = 8 * 1024;       /* set minimum memory block allocation  */
    exit( main( argc, argv, arge ) );
}
