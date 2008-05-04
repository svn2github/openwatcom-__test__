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
* Description:  prototypes for read/write FPU routines
*
****************************************************************************/

#ifndef _MISC7086_H_INCLUDED
#define _MISC7086_H_INCLUDED

extern void FPUExpand( void far * );
extern void FPUContract( void far * );

extern void Read8087( void far * );
extern void Write8087( void far * );

extern void Read387( void far * );
extern void Write387( void far * );

#ifdef __WATCOMC__

#pragma aux GetMSW = \
        ".286p"       \
        "smsw ax"    \
        value [ax];
extern unsigned short GetMSW( void );

#define MSW_EM       0x04

#define HAVE_EMU (GetMSW() & MSW_EM)

#else

#define HAVE_EMU     0

#endif

extern unsigned_8 NPXType( void );

#endif
