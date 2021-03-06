
ifdef _BUILDING_MATHLIB

include mdef.inc
include struct.inc

        modstart  sqrt086

        xdefp   __sqrtd

;
;      double __sqrtd( double AX BX CX DX );
;
        defp    __sqrtd
        push    SI                      ; save SI
        push    DS                      ; save DS
        sub     SP,10                   ; allocate space for long double
        mov     SI,SS                   ; set DS=SS
        mov     DS,SI                   ; ...
        mov     SI,SP                   ; point DS:SI to long double
        call    __EmuFDLD               ; convert double to long double
        mov     AX,SP                   ; point to long double
        call    __sqrt                  ; calculate square root
        mov     BX,SP                   ; point to long double
        call    __EmuLDFD               ; convert it to double
        add     SP,10                   ; remove long double from stack
        pop     DS                      ; restore DS
        pop     SI                      ; restore SI
        ret                             ; return
        endproc __sqrtd


endif

        xdefp   __sqrt
;
;       __sqrt( long double *AX );
;

__sqrt  proc    near
        push    BP              ; save BP
        push    DI              ; save DI
        push    SI              ; save SI
        push    DX              ; save DX
        push    CX              ; save CX
        push    BX              ; save BX
        mov     SI,AX           ; get address of argument
        mov     CX,8[SI]        ; get exponent

        _guess                          ; guess: special number
          mov   AX,[SI]                 ; - check for 0
          or    AX,2[SI]                ; - ...
          or    AX,4[SI]                ; - ...
          _quif ne                      ; - quit if not 0
          or    AX,6[SI]                ; - ...
          _if   e                       ; - if equal so far
            _shl  CX,1                  ; - - get rid of sign bit
            je    done1                 ; - - answer is 0 if exponent is 0
            rcr   CX,1                  ; - - put back the sign bit
          _endif                        ; - endif
          _guess                        ; - guess: answer is indefinite
            or    AX,AX                 ; - - quit if unnormal
            _quif e                     ; - - ...
;           shl   CX,1                  ; - - get rid of sign bit
;           _quif e                     ; - - quit if denormal
;           rcr   CX,1                  ; - - put back the sign
            cmp   CX,7FFFh              ; - - if +ve infinity
            _if   e                     ; - - then
              shl   AX,1                ; - - - answer is +ve infinity
              je    done1               ; - - - ...
            _endif                      ; - - endif
          _admit                        ; - admit: answer is indefinite
indefinite: mov   word ptr 8[SI],0FFFFh ; - - set result to indefinite
            sub   AX,AX                 ; - - ...
            mov   6[SI],AX              ; - - ...
            mov   4[SI],AX              ; - - ...
            mov   2[SI],AX              ; - - ...
            mov   [SI],AX               ; - - ...
NaN:        or    word ptr 6[SI],0C000h ; - - ...
done1:      jmp   sqrt9                 ; - - and return
          _endguess                     ; - endguess
        _endguess                       ; endguess
        _guess                          ; guess: NaN
          mov   AX,CX                   ; - get exponent
          and   AX,7FFFh                ; - get rid of sign
          cmp   AX,7FFFh                ; - check for NaN
          je    NaN                     ; - result stays as a NaN
          _shl  CX,1                    ; - get rid of sign bit
          jc    indefinite              ; - result of -ve number is indefinite
          shr   CX,1                    ; - restore sign
          _quif e                       ; - quit if number is denormal
          mov   AX,6[SI]                ; - check for unnormal number
          _shl  AX,1                    ; - top bit should be on
          jnc   indefinite              ; - number is a unnormal
        _endguess                       ; endguess

        push    SI              ; save address of operand
        sub     AX,AX           ; zero guard bits
        mov     DX,6[SI]        ; get high part of operand
        mov     BX,4[SI]        ; ...
        mov     BP,2[SI]        ; ...
        mov     DI,[SI]         ; ...

        sub     CX,3FFFh        ; remove bias
        sar     CX,1            ; divide by 2
        _if     nc              ; if exponent is even
          shr   DX,1            ; - divide argument by 2
          rcr   BX,1            ; - ...
          rcr   BP,1            ; - ...
          rcr   DI,1            ; - ...
          rcr   AX,1            ; - save guard bit
        _endif                  ; endif
        add     CX,3FFFh        ; add bias back in
        mov     8[SI],CX        ; store exponent
        push    AX              ; save guard bit

        mov     CX,DX           ; save operand
        mov     AX,BX           ; ...

        mov     SI,DX           ; get high order word
        stc                     ; calculate initial estimate
        rcr     SI,1            ; ...
        inc     DX              ; check for DX=FFFFh
        _if     e               ; if (high word was -1)
          dec   DX              ; - set DX back to -1
          cmp   BX,SI           ; - if next word is -1
          _if   e               ; - then
            cmp   BP,SI         ; - - if third word is also -1
            _if   e             ; - - then
              cmp   DI,SI       ; - - - if last word is -1
              _if   e           ; - - - then answer is all ones
                jmp   sqrt8     ; - - - - ...
              _endif            ; - - - endif
            _endif              ; - - endif
            pop   AX            ; - - get guard word
            mov   CX,BX         ; - - get second word
            mov   BX,BP         ; - - get third word
            mov   AX,DI         ; - - get last word
            stc                 ; - - set carry
            jmp   sqrt7         ; - - calculate final answer
          _endif                ; - endif
          mov   CX,BX           ; -
          stc                   ; -
          rcr   CX,1            ; - calc. second word of estimate
          mov   AX,CX           ; - multiply to see if estimate is too big
          mul   CX              ; - ...
          mov   SI,CX           ; - ...
          add   SI,SI           ; - ...
          inc   SI              ; - ...
          sub   DX,CX           ; - ...
          sbb   SI,0            ; - ...
          sub   DX,CX           ; - ...
          sbb   SI,0            ; - ...
          sub   DI,AX           ; - subtract result from operand
          sbb   BP,DX           ; - ...
          sbb   BX,SI           ; - ...
          push  CX              ; - save first estimate
          mov   DX,CX           ; - value for new estimate
          _if   nc              ; - if our estimate is too small
            _loop               ; - - loop
              inc   DX          ; - - - increment estimate
              sub   DI,CX       ; - - - adjust remainder
              sbb   BP,0FFFFh   ; - - - ...
              sbb   BX,0        ; - - - ...
            _until  c           ; - - until OK
          _endif                ; - endif
          _loop                 ; - loop
            dec   DX            ; - - decrement estimate
            add   DI,CX         ; - - adjust remainder
            adc   BP,0FFFFh     ; - - ...
            adc   BX,0          ; - - ...
          _until  c             ; - until OK
          pop   CX              ; - restore first estimate
          mov   SI,-1           ; - reset top word to -1
          mov   AX,SI           ; - place in AX as well
          jmp   short sqrt5     ; - continue
        _endif                  ; endif

; else high word not -1, then

        dec     DX              ; restore DX
        _loop                   ; loop
          div   SI              ; - calculate newer estimate
          dec   SI              ; - want estimate to be within one
          cmp   SI,AX           ; -
          _quif na              ; - quit if estimate good enough
          inc   SI              ; -
          add   SI,AX           ; - calculate new estimate as (old+new)/2
          rcr   SI,1            ; - ...
          mov   DX,CX           ; - restore operand
          mov   AX,BX           ; - ...
        _endloop                ; endloop
        inc     SI              ; restore divisor
        push    AX              ; save word of quotient
        mov     AX,BP           ; get next word of operand
        div     SI              ; calculate next word of quotient
        pop     DX              ; restore high word of quotient
;
;       SI:0   estimate is too small
;       DX:AX estimate is too large
;       calculate new estimate as (SI:0+DX:AX)/2
;
        add     SI,DX           ; ...
        stc                     ; divide by 2
        rcr     SI,1            ; ...
        rcr     AX,1            ; ...
        mov     CX,AX           ; save low word of result
;
;  square SI:CX and subtract from operand to see if result needs adjusting
;
        mul     AX              ; multiply low*low
        sub     DI,AX           ; subtract from operand
        sbb     BP,DX           ; ...
        sbb     BX,0            ; ...
        mov     AX,CX           ; multiply low*high
        mul     SI              ; ..
        sub     BP,AX           ; subtract from operand
        sbb     BX,DX           ; ...
        sub     BP,AX           ; subtract from operand again
        sbb     BX,DX           ; ...
        mov     AX,SI           ; multiply high*high
        mul     SI              ; ...
        sub     BX,AX           ; subtract from operand
        mov     DX,CX           ; save low word of result
;
;       BX:BP:DI contains the remainder, check to see if needs adjusting
;
        mov     AX,SI           ; get high word of new estimate
        _if     ns              ; if top word is not negative
          _loop                 ; - loop
            add   DX,1          ; - - adjust new estimate
            adc   AX,0          ; - - overflow to high word of new estimate
            sub   DI,CX         ; - - subtract divisor from remainder
            sbb   BP,SI         ; - - until we get a borrow
            sbb   BX,0          ; - - ...
          _until  c             ; - until we get a borrow
        _endif                  ; endif
        _loop                   ; loop
          sub     DX,1          ; - decrement low word of new estimate
          sbb     AX,0          ; - borrow from high word of new estimate
          add     DI,CX         ; - add back on
          adc     BP,SI         ; - ...
          adc     BX,0          ; - ...
        _until  c               ; until remainder < divisor
sqrt5:  pop     BX              ; get guard word
        push    AX              ; save high word of new estimate
        push    DX              ; save second word of new estimate
        cmp     SI,BP           ; if this will cause divide overflow
        _if     e               ; then
          mov     AX,-1         ; - estimate is FFFF
        _else                   ; else
          mov     DX,BP         ; - get remainder
          mov     AX,DI         ; - ...
          div     SI            ; - estimate next word of result
        _endif                  ; endif
;
;       remainder is in BP:DI:BX
;
        push    AX              ; save this estimate
        mul     CX              ; multiply estimate (AX) by divisor(SI:CX)
        sub     BX,AX           ; and subtract from remainder
        sbb     DI,DX           ; ...
        sbb     BP,0            ; ...
        pop     AX              ; restore estimate
        push    BX              ; save low word of remainder
        mov     BX,AX           ; save estimate
        mul     SI              ; multiply by high word of divisor
        sub     DI,AX           ; and subtract
        sbb     BP,DX           ; ...
        pop     AX              ; restore low word of remainder
;
;       we should never get an estimate that is too small (but just in case)
;       remainder is in BP:DI:AX
;
        pop     DX              ; restore second word of new estimate
        push    BP              ; save high word of remainder
        mov     BP,SP           ; get access to stack
        _if     nc              ; if no carry (estimate too small)
          _loop                 ; - loop
            add   BX,1          ; - - increment estimate
            adc   DX,0          ; - - overflow to next higher word
            adc   word ptr 2[BP],0; - - ...
            sub   AX,CX         ; - - subtract divisor from remainder
            sbb   DI,SI         ; - - ...
            sbb   word ptr 0[BP],0; - - ...
          _until  c             ; - until we did it one too many times
        _endif                  ; endif
        _loop                   ; loop (estimate was too big)
          sub   BX,1            ; - decrement estimate
          sbb   DX,0            ; - borrow from next higher word
          sbb   word ptr 2[BP],0; - ...
          add   AX,CX           ; - add divisor back to remainder
          adc   DI,SI           ; - ...
          adc   word ptr 0[BP],0; - ...
        _until  c               ; until estimate is correct
        pop     BP              ; clean up stack
        push    DX              ; save second word of new estimate
        cmp     SI,DI           ; if this will cause divide overflow
        _if     e               ; then
          mov   AX,-1           ; - estimate is FFFF
        _else                   ; else
          mov   DX,DI           ; - get remainder
          div   SI              ; - estimate last word of new estimate
        _endif                  ; endif
        pop     DX              ; restore second word of new estimate
        pop     DI              ; restore high word of new estimate
;
;       DI:DX:BX:AX             ; is our new estimate
;       SI:CX                   ; was our original estimate
;
        add     CX,DX           ; add the two estimates together
        adc     SI,DI           ; ...
sqrt7:  rcr     SI,1            ; and divide by 2
        rcr     CX,1            ; ...
        rcr     BX,1            ; ...
        rcr     AX,1            ; ...
        adc     AX,0            ; round up
        adc     BX,0
        adc     CX,0
        adc     SI,0

sqrt8:  pop     DI              ; restore address of operand
        mov     [DI],AX         ; store result
        mov     2[DI],BX        ; ...
        mov     4[DI],CX        ; ...
        mov     6[DI],SI        ; ...

sqrt9:  pop     BX              ; restore BX
        pop     CX              ; restore CX
        pop     DX              ; restore DX
        pop     SI              ; restore SI
        pop     DI              ; restore DI
        pop     BP              ; restore BP
        ret                     ; return to caller
        endproc __sqrt

ifdef _BUILDING_MATHLIB

EMUL_VERSION equ 1

include xception.inc
include fstatus.inc

        xref    F8InvalidOp
        xref    F8OverFlow

include ldfd086.asm
include fdld086.asm

        endmod

        endf    equ end
else
        endf    equ <>

endif

endf
