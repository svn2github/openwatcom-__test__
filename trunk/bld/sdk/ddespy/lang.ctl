# DDESPY Builder Control file
# ============================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 ]
    <CPCMD> <DEVDIR>/sdk/ddespy/wini86/wddespy.exe <RELROOT>/rel2/binw/wddespy.exe
    <CPCMD> <DEVDIR>/sdk/ddespy/nt386/wddespy.exe <RELROOT>/rel2/binnt/wddespy.exe
#    <CPCMD> <DEVDIR>/sdk/ddespy/ntaxp/wddespy.exe <RELROOT>/rel2/axpnt/wddespy.exe

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
