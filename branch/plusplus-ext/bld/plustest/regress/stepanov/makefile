plustest_name = stepanov
!include ..\environ.mif


oopacks = &
oop_v1p5.$(exe) &
oop_v1p6.$(exe) &
oop_v1p7.$(exe)

stepanovs = &
ste_v1p1.$(exe) &
ste_v1p2.$(exe)

exes = $(oopacks) $(stepanovs)

!ifdef test1
alt_error=01
test_flags = -d2-w0-zq
!else ifdef test2
alt_error=02
test_flags = -ox-d1-zq-w0-j
!else
alt_error=00
test_flags = -ox-d1-zq-w0-otexanr
!endif

test_flags_i86 = -mm

stack_386=opt stack=16k
stack_i86=opt stack=8k
stack_axp=opt stack=16k

.c.obj:
    $(wpp_$(arch)) $[@ $(test_flags) $(test_flags_$(arch)) $(opt_$^*)

.obj.$(exe):
    wlink @stepanov FILE $[@

!ifeq arch i86
test : .symbolic
!else
test : .symbolic stepanov.lnk $(exes)
    %create stepanov.out
# Note: Fast machines may need larger iteration counts, otherwise the code could run
# "too fast" and finish at "zero" execution time.
    $(run) oop_v1p5 Max=5000 18 Matrix=50 15 Complex=4000 50 Iterator=15000 14 >>stepanov.out
    $(run) oop_v1p6 Max=5000 49 Matrix=50 13 Complex=4000 52 Iterator=15000 18 >>stepanov.out
    $(run) oop_v1p7 Max=5000 14 Matrix=50 14 Complex=4000 83 Iterator=15000 19 >>stepanov.out
    @for %i in ( $(stepanovs) ) do $(run) %i 2500 >>stepanov.out
    diff stepanov.out stepanov.chk
!endif
    %make global
    %append $(log_file) PASS $(%__CWD__)

stepanov.lnk : $(__MAKEFILES__)
    %create $^@
    @%append $^@ $(ldebug_$(arch))
    @%append $^@ $(lnk_$(arch))
    @%append $^@ $(stack_$(arch))

save : .symbolic
    if exist s$(arch)_$(alt_error).sav erase s$(arch)_$(alt_error).sav
    if exist stepanov.out copy stepanov.out s$(arch)_$(alt_error).sav

global : .SYMBOLIC
    @%make common_clean
