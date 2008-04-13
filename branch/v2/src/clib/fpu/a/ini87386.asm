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
;* Description:  routine for checking FPU type
;*
;*****************************************************************************


include mdef.inc

        modstart init8087

        xdefp   __x87id

__x87id proc
        sub     EAX,EAX
        push    EAX                     ; allocate space for status word
        finit                           ; use default infinity mode
        fstcw   word ptr [ESP]          ; save control word
        fwait
        pop     EAX
        mov     AL,0
        cmp     AH,3
        jnz     nox87
        push    EAX                     ; allocate space for status word
        fld1                            ; generate infinity by
        fldz                            ;   dividing 1 by 0
        fdiv                            ; ...
        fld     st                      ; form negative infinity
        fchs                            ; ...
        fcompp                          ; compare +/- infinity
        fstsw   word ptr [ESP]          ; equal for 87/287
        fwait                           ; wait fstsw to complete
        pop     EAX                     ; get NDP status word
        mov     AL,2                    ; assume 80287
        sahf                            ; store condition bits in flags
        jz      not387                  ; it's 287 if infinities equal
        mov     AL,3                    ; indicate 80387
not387: finit                           ; re-initialize the 8087
nox87:  mov     AH,0
        ret                             ; return
__x87id endp

        endmod
        end
