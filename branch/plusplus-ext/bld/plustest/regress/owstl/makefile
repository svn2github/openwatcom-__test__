plustest_name = owstl
!include ..\environ.mif

!ifdef test1
test_cflags_386 = -d2-fpd-xs-za
test_cflags_i86 = -d2-fpd-xs-za
test_cflags_axp = -d2-xs-za
!else ifdef test2
test_cflags_386 = -os-d1-3s-xss-br
test_cflags_i86 = -os-d1-xss
test_cflags_axp = -os-d1-xss
!else ifdef test3
test_cflags_386 = -os-d1-3s-xss-xr
test_cflags_i86 = -os-d1-xss-xr
test_cflags_axp = -os-d1-xss-xr
!else ifdef test4
test_cflags_386 = -ot-d1-3r-fpd-xs -oe500
test_cflags_i86 = -ot-d1-fpd-xs -oe100
test_cflags_axp = -ot-d1-xs -oe500
!else ifdef test5
test_cflags_386 = -d2-br-xs
test_cflags_i86 = -d2-xs
test_cflags_axp = -d2-xs
!else
test_cflags_386 = -os-d2-xst
test_cflags_i86 = -os-d2-xst
test_cflags_axp = -os-d2-xst
!endif

test_cflags_386 += -zq-wx-wcd433-fpi87-fp5-mf
test_cflags_i86 += -zq-wx-wcd433-fpi87-fp5-ml-zm
test_cflags_axp += -zq-wx-wcd433

stack_386=opt stack=16k
stack_i86=opt stack=8k
stack_axp=opt stack=16k

# to update add test names here:
template = &
        aaa$(ext)       &
	algn01$(ext)    &
	algm01$(ext)    &
        algs01$(ext)    &
        bitset01$(ext)  &
        clib01$(ext)    &
        cmplx01$(ext)   &
        deque01$(ext)   &
        fun01$(ext)     &
        iter01$(ext)    &
        lim01$(ext)     &
        list01$(ext)    &
        locale01$(ext)  &
        map01$(ext)     &
        map02$(ext)     &
        mem01$(ext)     &
        mmwin16$(ext)   &
        mmwindef$(ext)  &
        numer01$(ext)   &
        stack01$(ext)   &
        set01$(ext)     &
        set02$(ext)     &
        string01$(ext)  &
        string02$(ext)  &
        typetr01$(ext)  &
        unoset01$(ext)  &
        util01$(ext)    &
        vector01$(ext)  

# the list of .exe targets
ext = .$(exe)
tests = $+ $(template) $-
# a list of names so lazy old me can type "wmake alg01" to 
# create and run algo01.exe without running the full suite
ext =
names = $+ $(template) $-
# this is used as special target to run multiple commands for each test
ext = ._do_test_
do_tests = $+ $(template) $-

# define flags specific to tests here
extra_cflags_typetr01 = -za0x
extra_cflags_mmwin16 = -i$(%WATCOM)\h\win -dmmWin16
extra_cflags_mmwindef = -i$(%WATCOM)\h\nt

.cpp.obj :
    $(wpp_$(arch)) $[@ $(test_cflags_$(arch)) -e1000 $(extra_cflags_$[*)

# this is my laziness bit...
$(names) : .symbolic
    @%make $^&.$(exe)
    $(run) $^*
    @echo PASS

$(tests) :: test.lnk

.obj.$(exe):
    $(linker) @test.lnk NAME $^* FILE $^*

# the main target environment.mif calls to run the test suite
test : .symbolic $(tests)
    %create test.out
    # if I could figure out how to make a "for" loop execute multiple 
    # commands this would be a lot more clear...
    @%make $(do_tests)
    diff test.out test.chk
    %make global
    %append $(log_file) PASS $(%__CWD__)

# the special target that runs the required commands for each test
$(do_tests) : .symbolic
# Note that there must be no space before the redirection symbol - otherwise
# echo will emit the space character and subsequent diff will fail. This
# way is more transparent than keeping trailing blanks in the check file.
    @echo ----------$^*---------->> test.out
    $(run) $^* >> test.out

test.lnk : makefile
    %create $^@
    @%append $^@ $(ldebug_$(arch))
    @%append $^@ $(lnk_$(arch))
    @%append $^@ $(stack_$(arch))

global : .SYMBOLIC
    @%make common_clean

# ensures mmwindef.cpp and mmwin16.cpp are always identical to 
# nominmax.cpp

mmwin16.cpp : nominmax.cpp
    copy nominmax.cpp mmwin16.cpp /v

mmwindef.cpp : nominmax.cpp
    copy nominmax.cpp mmwindef.cpp /v

