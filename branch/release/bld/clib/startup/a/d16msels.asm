;*****************************************************************************
;*
;*                            Open Watcom Project
;*
;*    Copyright (c) 2007 Open Watcom Contributors. All Rights Reserved.
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
;* Description:  Define selectors for DOS16/M extender segments.
;*
;*****************************************************************************


        .286p

DGROUP  group   _DATA

_TEXT   SEGMENT PARA PUBLIC 'CODE'
_TEXT   ENDS

_DATA   SEGMENT PARA PUBLIC 'DATA'
        assume  ds:DGROUP

        public  ___d16_selectors
___d16_selectors label  word
        dw      2           ; 0x00
        dw      GDTSEG      ; 0x08
        dw      IDTSEG      ; 0x10
        dw      RTCODESEG   ; 0x18
        dw      RTDATASEG   ; 0x20
        dw      PSPSEG      ; 0x28
        dw      ENVSEG      ; 0x30
        dw      MEM0SEG     ; 0x38
        dw      BIOSDATSEG  ; 0x40
        dw      0           ; 0x48
        dw      VIDB0SEG    ; 0x50
        dw      0           ; 0x58
        dw      0           ; 0x60
        dw      0           ; 0x68
        dw      DUMMY14     ; 0x70
        dw      0           ; 0x78
        dw      _TEXT       ; 0x80

_DATA   ENDS

GDTSEG      segment para public 'FAR_DATA'
GDTSEG      ends

IDTSEG      segment para public 'FAR_DATA'
IDTSEG      ends

RTCODESEG   segment para public 'FAR_DATA'
RTCODESEG   ends

RTDATASEG   segment para public 'FAR_DATA'
RTDATASEG   ends

PSPSEG      segment para public 'FAR_DATA'
PSPSEG      ends

ENVSEG      segment para public 'FAR_DATA'
ENVSEG      ends

MEM0SEG     segment para public 'FAR_DATA'
MEM0SEG     ends

BIOSDATSEG  segment para public 'FAR_DATA'
BIOSDATSEG  ends

VIDB0SEG    segment para public 'FAR_DATA'
VIDB0SEG    ends

DUMMY14     segment para public 'FAR_DATA'
DUMMY14     ends

        end
