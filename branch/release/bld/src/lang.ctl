# SRC Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    cdsay ../f77/samples
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CPCMD> <DEVDIR>/clib/startup/a/cstrt386.asm <RELROOT>/rel2/src/startup/386/cstrt386.asm
    <CPCMD> <DEVDIR>/clib/startup/a/cstrtw32.asm <RELROOT>/rel2/src/startup/386/cstrtw32.asm
    <CPCMD> <DEVDIR>/clib/startup/a/cstrtwnt.asm <RELROOT>/rel2/src/startup/386/cstrtwnt.asm
#    <CPCMD> <DEVDIR>/clib/startup/a/cstrtwwt.asm <RELROOT>/rel2/src/startup/386/cstrtwwt.asm
    <CPCMD> <DEVDIR>/clib/startup/a/cstrtx32.asm <RELROOT>/rel2/src/startup/386/cstrtx32.asm
    <CPCMD> <DEVDIR>/clib/startup/c/cmain386.c <RELROOT>/rel2/src/startup/386/cmain386.c
    <CPCMD> <DEVDIR>/clib/startup/c/wildargv.c <RELROOT>/rel2/src/startup/wildargv.c
    <CPCMD> <DEVDIR>/clib/startup/a/cstrt086.asm <RELROOT>/rel2/src/startup/dos/cstrt086.asm
    <CPCMD> <DEVDIR>/clib/startup/a/dos16m.asm <RELROOT>/rel2/src/startup/dos/dos16m.asm
    <CPCMD> <DEVDIR>/clib/startup/a/dstrt386.asm <RELROOT>/rel2/src/startup/386/dstrt386.asm
    <CPCMD> <DEVDIR>/clib/startup/c/cmain086.c <RELROOT>/rel2/src/startup/dos/cmain086.c
    <CPCMD> <DEVDIR>/clib/startup/c/cmain086.c <RELROOT>/rel2/src/startup/os2/cmain086.c
    <CPCMD> <DEVDIR>/clib/startup/c/hpgrw086.c <RELROOT>/rel2/src/startup/dos/hpgrw086.c
    <CPCMD> <DEVDIR>/clib/startup/c/dmaino16.c <RELROOT>/rel2/src/startup/os2/dmaino16.c
    <CPCMD> <DEVDIR>/clib/startup/c/libmno16.c <RELROOT>/rel2/src/startup/os2/libmno16.c
    <CPCMD> <DEVDIR>/clib/startup/c/maino16.c <RELROOT>/rel2/src/startup/os2/maino16.c
    <CPCMD> <DEVDIR>/clib/startup/c/main2o32.c <RELROOT>/rel2/src/startup/386/main2o32.c
    <CPCMD> <DEVDIR>/clib/startup/c/libmno32.c <RELROOT>/rel2/src/startup/386/libmno32.c
    <CPCMD> <DEVDIR>/clib/startup/c/dmaino32.c <RELROOT>/rel2/src/startup/386/dmaino32.c
    <CPCMD> <DEVDIR>/clib/startup/c/main2wnt.c <RELROOT>/rel2/src/startup/386/main2wnt.c
    <CPCMD> <DEVDIR>/clib/startup/c/wmainwnt.c <RELROOT>/rel2/src/startup/386/wmainwnt.c
    <CPCMD> <DEVDIR>/clib/startup/c/lmainwnt.c <RELROOT>/rel2/src/startup/386/lmainwnt.c
    <CPCMD> <DEVDIR>/clib/startup/c/dmainwnt.c <RELROOT>/rel2/src/startup/386/dmainwnt.c
    <CPCMD> <DEVDIR>/clib/startup/c/lmn2wnt.c <RELROOT>/rel2/src/startup/386/lmn2wnt.c
    <CPCMD> <DEVDIR>/clib/startup/a/cstrto16.asm <RELROOT>/rel2/src/startup/os2/cstrto16.asm
    <CPCMD> <DEVDIR>/clib/startup/a/cstrto32.asm <RELROOT>/rel2/src/startup/386/cstrto32.asm
    <CPCMD> <DEVDIR>/clib/startup/a/cstrtw16.asm <RELROOT>/rel2/src/startup/win/cstrtw16.asm
    <CPCMD> <DEVDIR>/clib/startup/a/libentry.asm <RELROOT>/rel2/src/startup/win/libentry.asm
    <CPCMD> <DEVDIR>/clib/startup/c/8087cw.c <RELROOT>/rel2/src/startup/8087cw.c
    <CPCMD> <DEVDIR>/lib_misc/h/exitwmsg.h <RELROOT>/rel2/src/startup/os2/exitwmsg.h
    <CPCMD> <DEVDIR>/clib/startup/h/initfini.h <RELROOT>/rel2/src/startup/386/initfini.h
    <CPCMD> <DEVDIR>/clib/startup/h/initfini.h <RELROOT>/rel2/src/startup/os2/initfini.h
    <CPCMD> <DEVDIR>/watcom/h/wos2.h <RELROOT>/rel2/src/startup/os2/wos2.h
    <CPCMD> <DEVDIR>/watcom/h/mdef.inc <RELROOT>/rel2/src/startup/mdef.inc

    <CPCMD> <DEVDIR>/src/misc/*.* <RELROOT>/rel2/src/
    <CPCMD> <DEVDIR>/src/os2/pdd/*.*    <RELROOT>/rel2/src/os2/pdd/
    <CPCMD> <DEVDIR>/f77/src/*.* <RELROOT>/rel2/src/fortran/
    <CPCMD> <DEVDIR>/f77/src/win/*.* <RELROOT>/rel2/src/fortran/win/
    <CPCMD> <DEVDIR>/f77/src/dos/*.* <RELROOT>/rel2/src/fortran/dos/
    <CPCMD> <DEVDIR>/f77/src/os2/*.* <RELROOT>/rel2/src/fortran/os2/
    <CPCMD> <DEVDIR>/f77/samples/os2/*.* <RELROOT>/rel2/samples/fortran/os2/
    <CPCMD> <DEVDIR>/f77/samples/os2/rexx/*.* <RELROOT>/rel2/samples/fortran/os2/rexx/
    <CPCMD> <DEVDIR>/f77/samples/mthread/mthrdos2.for <RELROOT>/rel2/samples/fortran/os2/mthread.for
    <CPCMD> <DEVDIR>/f77/samples/mthread/mthrdnt.for <RELROOT>/rel2/samples/fortran/win32/mthread.for
    <CPCMD> <DEVDIR>/f77/samples/win/*.* <RELROOT>/rel2/samples/fortran/win/
    <CPCMD> <DEVDIR>/f77/samples/windll/*.* <RELROOT>/rel2/samples/fortran/win/dll/
    <CPCMD> <DEVDIR>/f77/samples/dll/*.* <RELROOT>/rel2/samples/fortran/os2/dll/
    <CPCMD> <DEVDIR>/f77/samples/dll/*.* <RELROOT>/rel2/samples/fortran/win32/dll/

    <CPCMD> <DEVDIR>/plusplus/cpplib/contain/cpp/*.* <RELROOT>/rel2/src/cpplib/contain/

    <CPCMD> <DEVDIR>/src/clibexam/*.*   <RELROOT>/rel2/samples/clibexam/
    <CPCMD> <DEVDIR>/src/cplbexam/*.*   <RELROOT>/rel2/samples/cplbexam/

#    <CPCMD> <DEVDIR>/src/cppexamp/*.*  <RELROOT>/rel2/samples/cppexamp/
#    <CPCMD> <DEVDIR>/src/cppexamp/excarea/*.*  <RELROOT>/rel2/samples/cppexamp/excarea/
#    <CPCMD> <DEVDIR>/src/cppexamp/membfun/*.*  <RELROOT>/rel2/samples/cppexamp/membfun/

    <CPCMD> <DEVDIR>/src/dll/*.*        <RELROOT>/rel2/samples/dll/
    <CPCMD> <DEVDIR>/src/goodies/*.*    <RELROOT>/rel2/samples/goodies/
    <CPCMD> <DEVDIR>/src/os2/*.*        <RELROOT>/rel2/samples/os2/
    <CPCMD> <DEVDIR>/src/os2/dll/*.*    <RELROOT>/rel2/samples/os2/dll/
    <CPCMD> <DEVDIR>/src/win/*.*        <RELROOT>/rel2/samples/win/
    <CPCMD> <DEVDIR>/src/clibexam/kanji/*.*     <RELROOT>/rel2/samples/clibexam/kanji/
    <CPCMD> <DEVDIR>/src/clibexam/test/*.*      <RELROOT>/rel2/samples/clibexam/test/
    <CPCMD> <DEVDIR>/src/cplbexam/complex/*.*   <RELROOT>/rel2/samples/cplbexam/complex/
    <CPCMD> <DEVDIR>/src/cplbexam/contain/*.*   <RELROOT>/rel2/samples/cplbexam/contain/
    <CPCMD> <DEVDIR>/src/cplbexam/fstream/*.*   <RELROOT>/rel2/samples/cplbexam/fstream/
    <CPCMD> <DEVDIR>/src/cplbexam/ios/*.*       <RELROOT>/rel2/samples/cplbexam/ios/
    <CPCMD> <DEVDIR>/src/cplbexam/iostream/*.*  <RELROOT>/rel2/samples/cplbexam/iostream/
    <CPCMD> <DEVDIR>/src/cplbexam/string/*.*    <RELROOT>/rel2/samples/cplbexam/string/
    <CPCMD> <DEVDIR>/src/cplbexam/strstrea/*.*  <RELROOT>/rel2/samples/cplbexam/strstrea/
    <CPCMD> <DEVDIR>/src/cplbexam/complex/friend/*.*    <RELROOT>/rel2/samples/cplbexam/complex/friend/
    <CPCMD> <DEVDIR>/src/cplbexam/complex/pubfun/*.*    <RELROOT>/rel2/samples/cplbexam/complex/pubfun/
    <CPCMD> <DEVDIR>/src/cplbexam/complex/relfun/*.*    <RELROOT>/rel2/samples/cplbexam/complex/relfun/
    <CPCMD> <DEVDIR>/src/cplbexam/complex/relop/*.*     <RELROOT>/rel2/samples/cplbexam/complex/relop/
    <CPCMD> <DEVDIR>/src/cplbexam/fstream/fstream/*.*   <RELROOT>/rel2/samples/cplbexam/fstream/fstream/
    <CPCMD> <DEVDIR>/src/cplbexam/fstream/ifstream/*.*  <RELROOT>/rel2/samples/cplbexam/fstream/ifstream/
    <CPCMD> <DEVDIR>/src/cplbexam/fstream/ofstream/*.*  <RELROOT>/rel2/samples/cplbexam/fstream/ofstream/
    <CPCMD> <DEVDIR>/src/cplbexam/iostream/iostream/*.* <RELROOT>/rel2/samples/cplbexam/iostream/iostream/
    <CPCMD> <DEVDIR>/src/cplbexam/iostream/istream/*.*  <RELROOT>/rel2/samples/cplbexam/iostream/istream/
    <CPCMD> <DEVDIR>/src/cplbexam/iostream/ostream/*.*  <RELROOT>/rel2/samples/cplbexam/iostream/ostream/
    <CPCMD> <DEVDIR>/src/cplbexam/string/friend/*.*     <RELROOT>/rel2/samples/cplbexam/string/friend/
    <CPCMD> <DEVDIR>/src/cplbexam/string/pubfun/*.*     <RELROOT>/rel2/samples/cplbexam/string/pubfun/
    <CPCMD> <DEVDIR>/src/cplbexam/strstrea/istrstre/*.* <RELROOT>/rel2/samples/cplbexam/strstrea/istrstre/
    <CPCMD> <DEVDIR>/src/cplbexam/strstrea/ostrstre/*.* <RELROOT>/rel2/samples/cplbexam/strstrea/ostrstre/
    <CPCMD> <DEVDIR>/src/cplbexam/strstrea/strstre/*.*  <RELROOT>/rel2/samples/cplbexam/strstrea/strstre/
    <CPCMD> <DEVDIR>/src/win/alarm/*.*  <RELROOT>/rel2/samples/win/alarm/
    <CPCMD> <DEVDIR>/src/win/datactl/*.*        <RELROOT>/rel2/samples/win/datactl/
    <CPCMD> <DEVDIR>/src/win/edit/*.*   <RELROOT>/rel2/samples/win/edit/
    <CPCMD> <DEVDIR>/src/win/generic/*.*        <RELROOT>/rel2/samples/win/generic/
    <CPCMD> <DEVDIR>/src/win/helpex/*.* <RELROOT>/rel2/samples/win/helpex/
    <CPCMD> <DEVDIR>/src/win/iconview/*.*       <RELROOT>/rel2/samples/win/iconview/
    <CPCMD> <DEVDIR>/src/win/life/*.*   <RELROOT>/rel2/samples/win/life/
    <CPCMD> <DEVDIR>/src/win/shootgal/*.*       <RELROOT>/rel2/samples/win/shootgal/
    <CPCMD> <DEVDIR>/src/win/watzee/*.* <RELROOT>/rel2/samples/win/watzee/
    <CPCMD> <DEVDIR>/src/win/alarm/win16/*.*    <RELROOT>/rel2/samples/win/alarm/win16/
    <CPCMD> <DEVDIR>/src/win/alarm/win32/*.*    <RELROOT>/rel2/samples/win/alarm/win32/
    <CPCMD> <DEVDIR>/src/win/alarm/win386/*.*   <RELROOT>/rel2/samples/win/alarm/win386/
#    <CPCMD> <DEVDIR>/src/win/alarm/winaxp/*.*  <RELROOT>/rel2/samples/win/alarm/winaxp/
    <CPCMD> <DEVDIR>/src/win/datactl/win16/*.*  <RELROOT>/rel2/samples/win/datactl/win16/
    <CPCMD> <DEVDIR>/src/win/datactl/win32/*.*  <RELROOT>/rel2/samples/win/datactl/win32/
    <CPCMD> <DEVDIR>/src/win/datactl/win386/*.* <RELROOT>/rel2/samples/win/datactl/win386/
#    <CPCMD> <DEVDIR>/src/win/datactl/winaxp/*.*        <RELROOT>/rel2/samples/win/datactl/winaxp/
    <CPCMD> <DEVDIR>/src/win/edit/win16/*.*     <RELROOT>/rel2/samples/win/edit/win16/
    <CPCMD> <DEVDIR>/src/win/edit/win32/*.*     <RELROOT>/rel2/samples/win/edit/win32/
    <CPCMD> <DEVDIR>/src/win/edit/win386/*.*    <RELROOT>/rel2/samples/win/edit/win386/
#    <CPCMD> <DEVDIR>/src/win/edit/winaxp/*.*   <RELROOT>/rel2/samples/win/edit/winaxp/
    <CPCMD> <DEVDIR>/src/win/generic/win16/*.*  <RELROOT>/rel2/samples/win/generic/win16/
    <CPCMD> <DEVDIR>/src/win/generic/win32/*.*  <RELROOT>/rel2/samples/win/generic/win32/
    <CPCMD> <DEVDIR>/src/win/generic/win386/*.* <RELROOT>/rel2/samples/win/generic/win386/
#    <CPCMD> <DEVDIR>/src/win/generic/winaxp/*.*        <RELROOT>/rel2/samples/win/generic/winaxp/
    <CPCMD> <DEVDIR>/src/win/helpex/win16/*.*   <RELROOT>/rel2/samples/win/helpex/win16/
    <CPCMD> <DEVDIR>/src/win/helpex/win32/*.*   <RELROOT>/rel2/samples/win/helpex/win32/
    <CPCMD> <DEVDIR>/src/win/helpex/win386/*.*  <RELROOT>/rel2/samples/win/helpex/win386/
#    <CPCMD> <DEVDIR>/src/win/helpex/winaxp/*.* <RELROOT>/rel2/samples/win/helpex/winaxp/
    <CPCMD> <DEVDIR>/src/win/iconview/win16/*.* <RELROOT>/rel2/samples/win/iconview/win16/
    <CPCMD> <DEVDIR>/src/win/iconview/win32/*.* <RELROOT>/rel2/samples/win/iconview/win32/
    <CPCMD> <DEVDIR>/src/win/iconview/win386/*.*        <RELROOT>/rel2/samples/win/iconview/win386/
#    <CPCMD> <DEVDIR>/src/win/iconview/winaxp/*.*       <RELROOT>/rel2/samples/win/iconview/winaxp/
    <CPCMD> <DEVDIR>/src/win/life/win16/*.*     <RELROOT>/rel2/samples/win/life/win16/
    <CPCMD> <DEVDIR>/src/win/life/win32/*.*     <RELROOT>/rel2/samples/win/life/win32/
    <CPCMD> <DEVDIR>/src/win/life/win386/*.*    <RELROOT>/rel2/samples/win/life/win386/
#    <CPCMD> <DEVDIR>/src/win/life/winaxp/*.*   <RELROOT>/rel2/samples/win/life/winaxp/
    <CPCMD> <DEVDIR>/src/win/shootgal/win16/*.* <RELROOT>/rel2/samples/win/shootgal/win16/
    <CPCMD> <DEVDIR>/src/win/shootgal/win32/*.* <RELROOT>/rel2/samples/win/shootgal/win32/
    <CPCMD> <DEVDIR>/src/win/shootgal/win386/*.*        <RELROOT>/rel2/samples/win/shootgal/win386/
#    <CPCMD> <DEVDIR>/src/win/shootgal/winaxp/*.*       <RELROOT>/rel2/samples/win/shootgal/winaxp/
    <CPCMD> <DEVDIR>/src/win/watzee/win16/*.*   <RELROOT>/rel2/samples/win/watzee/win16/
    <CPCMD> <DEVDIR>/src/win/watzee/win32/*.*   <RELROOT>/rel2/samples/win/watzee/win32/
    <CPCMD> <DEVDIR>/src/win/watzee/win386/*.*  <RELROOT>/rel2/samples/win/watzee/win386/
#    <CPCMD> <DEVDIR>/src/win/watzee/winaxp/*.* <RELROOT>/rel2/samples/win/watzee/winaxp/

[ BLOCK <1> clean ]
#==================
    sweep killobjs
