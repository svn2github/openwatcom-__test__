# IDEBAT Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <DEVDIR>/idebatch/os2/batserv.exe  <RELROOT>/rel2/binp/batserv.exe
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <DEVDIR>/idebatch/nt/batserv.exe   <RELROOT>/rel2/binnt/batserv.exe
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <DEVDIR>/idebatch/dos/int.exe      <RELROOT>/rel2/binw/dosserv.exe
# there is no makefile in the wini86 dir
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> <DEVDIR>/idebatch/wini86/batchbox.pif <RELROOT>/rel2/binw/batchbox.pif

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============

cdsay <PROJDIR>
