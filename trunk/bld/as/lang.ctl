# asaxp Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/alpha/dos386/wasaxp.exe    <RELROOT>/rel2/binw/wasaxp.exe
    <CPCMD> <PROJDIR>/ppc/dos386/wasppc.exe      <RELROOT>/rel2/binw/wasppc.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/alpha/os2386/wasaxp.exe    <RELROOT>/rel2/binp/wasaxp.exe
    <CPCMD> <PROJDIR>/ppc/os2386/wasppc.exe      <RELROOT>/rel2/binp/wasppc.exe

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/alpha/nt386/wasaxp.exe     <RELROOT>/rel2/binnt/wasaxp.exe
    <CPCMD> <PROJDIR>/ppc/nt386/wasppc.exe       <RELROOT>/rel2/binnt/wasppc.exe

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/alpha/linux386/wasaxp.exe  <RELROOT>/rel2/binl/wasaxp
    <CPCMD> <PROJDIR>/ppc/linux386/wasppc.exe    <RELROOT>/rel2/binl/wasppc

#<CPCMD> <PROJDIR>/alpha/ntaxp/wasaxp.exe     <RELROOT>/rel2/axpnt/wasaxp.exe

[ BLOCK <1> clean ]
#==================
    pmake -d all -h clean
    cdsay <PROJDIR>

