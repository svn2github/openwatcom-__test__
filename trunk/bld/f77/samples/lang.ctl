# FORTRAN samples Builder Control file
# ====================================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>\master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]
cdsay .
[ INCLUDE <LANG_BLD>\wproj.ctl ]

[ BLOCK <1> build rel2 ]
    cdsay windll
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h cover16.obj
    cdsay <projdir>

[ BLOCK <1> rel2 cprel2 ]
#========================
<CPCMD> <devdir>\f77\src\*.*    <relroot>\rel2\src\fortran\
<CPCMD> <devdir>\f77\src\win\*.*        <relroot>\rel2\src\fortran\win\
<CPCMD> <devdir>\f77\src\dos\*.*        <relroot>\rel2\src\fortran\dos\
<CPCMD> <devdir>\f77\src\ads\*.*        <relroot>\rel2\src\fortran\ads\
<CPCMD> <devdir>\f77\src\ads\rel12\*.*  <relroot>\rel2\src\fortran\ads\rel12\
<CPCMD> <devdir>\f77\src\os2\*.*        <relroot>\rel2\src\fortran\os2\
<CPCMD> <devdir>\f77\samples\os2\*.*    <relroot>\rel2\samples\fortran\os2\
<CPCMD> <devdir>\f77\samples\os2\rexx\*.*       <relroot>\rel2\samples\fortran\os2\rexx\
<CPCMD> <devdir>\f77\samples\mthread\mthrdos2.for       <relroot>\rel2\samples\fortran\os2\mthread.for
<CPCMD> <devdir>\f77\samples\mthread\mthrdnt.for        <relroot>\rel2\samples\fortran\win32\mthread.for
<CPCMD> <devdir>\f77\samples\win\*.*    <relroot>\rel2\samples\fortran\win\
# These don't exist?
#<CPCMD> <devdir>\f77\samples\win32\*.* <relroot>\rel2\samples\fortran\win32\
#<CPCMD> <devdir>\f77\samples\win32\dll\*.*     <relroot>\rel2\samples\fortran\win32\dll\
#<CPCMD> <devdir>\f77\samples\os2\dll\*.*       <relroot>\rel2\samples\fortran\os2\dll\
# /These don't exist?
<CPCMD> <devdir>\f77\samples\windll\*.* <relroot>\rel2\samples\fortran\win\dll\
<CPCMD> <devdir>\f77\samples\dll\*.*    <relroot>\rel2\samples\fortran\os2\dll\
<CPCMD> <devdir>\f77\samples\dll\*.*    <relroot>\rel2\samples\fortran\win32\dll\
