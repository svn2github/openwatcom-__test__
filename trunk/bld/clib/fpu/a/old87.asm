;*****************************************************************************
;*
;*                            Open Watcom Project
;*
;*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
;*
;*  ========================================================================
;*
;*    This file contains Original Code and/or Modifications of Original
;*    Code as defined in and that are subject to the Sybase Open Watcom
;*    Public License version 1.0 (the 'License'). You may not use this file
;*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
;*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
;*    provided with the Original Code and Modifications, and is also
;*    available at www.sybase.com/developer/opensource.
;*
;*    The Original Code and all software distributed under the License are
;*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
;*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
;*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
;*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
;*    NON-INFRINGEMENT. Please see the License for the specific language
;*    governing rights and limitations under the License.
;*
;*  ========================================================================
;*
;* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
;*               DESCRIBE IT HERE!
;*
;*****************************************************************************


include mdef.inc

        xref    __8087

ifdef __DOS__
ifndef __386__

        xdefp   __old_8087_emu

DGROUP  GROUP _DATA
_DATA segment word 'DATA'
        __old_8087_emu dw 0
_DATA ends

endif
endif

        modstart _old8087

        xdefp    __old_8087
        defp     __old_8087
        fldz
        fldz
        fldz
        fldz
ifdef __DOS__
ifndef __386__
assume DS:DGROUP
        push    ds
if _MODEL and _BIG_DATA
        mov     ax,DGROUP
        mov     ds,ax
endif
        cmp     word ptr __old_8087_emu, 0
        jz      l1
        call    __old_8087_emu
l1:     pop     ds
endif
endif
        ret
        endproc __old_8087
        endmod

include xinit.inc

        xinit   __old_8087,3

        end
