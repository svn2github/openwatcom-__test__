# DMPOBJ Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay .

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dos386/dmpobj.exe    <RELROOT>/rel2/binw/dmpobj.exe
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/dmpobj.exe    <RELROOT>/rel2/binp/dmpobj.exe
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/dmpobj.exe     <RELROOT>/rel2/binnt/dmpobj.exe
  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/dmpobj.exe  <RELROOT>/rel2/binl/dmpobj

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
