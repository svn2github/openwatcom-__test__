# HDR Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
    <CPCMD> <PROJDIR>/dos/*.h*           <RELROOT>/rel2/h/
    <CPCMD> <PROJDIR>/dos/*.cnv          <RELROOT>/rel2/h/
    <CPCMD> <PROJDIR>/dos/sys/*.h        <RELROOT>/rel2/h/sys/
    <CPCMD> <PROJDIR>/dos/win/*.h        <RELROOT>/rel2/h/win/
    <CPCMD> <PROJDIR>/linux/*.h*         <RELROOT>/rel2/lh/
    <CPCMD> <PROJDIR>/linux/arpa/*.h     <RELROOT>/rel2/lh/arpa/
    <CPCMD> <PROJDIR>/linux/sys/*.h      <RELROOT>/rel2/lh/sys/
    <CPCMD> <PROJDIR>/linux/netinet/*.h  <RELROOT>/rel2/lh/netinet/
#    <CPCMD> <PROJDIR>/qnx/*.h*           <RELROOT>/rel2/qh/
#    <CPCMD> <PROJDIR>/qnx/sys/*.h        <RELROOT>/rel2/qh/sys/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
