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
* Description:  Overlay manager debug services constants declaration
*
****************************************************************************/

#ifndef _OVLDBG_H_
#define _OVLDBG_H_

enum ovldbg_service {
    OVLDBG_GET_STATE_SIZE,
    OVLDBG_READ_STATE,
    OVLDBG_WRITE_STATE,
    OVLDBG_TRANSLATE_VECTOR_ADDR,
    OVLDBG_TRANSLATE_RETURN_ADDR,
    OVLDBG_GET_OVL_TABLE,
    OVLDBG_GET_REMAP_ENTRY,  // GET_CHANGED_SECTIONS,
    OVLDBG_GET_SECTION_DATA
};

_Packed struct ovl_header {
    unsigned char   short_jmp[2];
    unsigned_16     signature;
    void            (far *hook)();
    unsigned_16     handler_offset;
#if 1 //support for the 9.5 overlay manager, remove at a later date.
    unsigned_16     spare1;
    unsigned_16     spare2;
    unsigned_16     dyn_area;
#endif
};

#define OVL_SIGNATURE   0x2112

#endif
