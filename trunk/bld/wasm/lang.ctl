# WASM Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
    <CPCMD> nt386/wasm.exe    <RELROOT>/rel2/binnt/wasm.exe
    <CPCMD> nt386/wasm.sym    <RELROOT>/rel2/binnt/wasm.sym
#    <CPCMD> ntaxp/wasm.exe    <RELROOT>/rel2/axpnt/wasm.exe
#    <CPCMD> ntaxp/wasm.sym    <RELROOT>/rel2/axpnt/wasm.sym
    <CPCMD> os2386/wasm.exe   <RELROOT>/rel2/binp/wasm.exe
    <CPCMD> os2386/wasm.sym   <RELROOT>/rel2/binp/wasm.sym
    <CPCMD> dos386/wasm.exe   <RELROOT>/rel2/binw/wasm.exe
    <CPCMD> dos386/wasm.sym   <RELROOT>/rel2/binw/wasm.sym
#    <CPCMD> qnx386/wasm.qnx   <RELROOT>/rel2/qnx/binq/wasm.
#    <CPCMD> qnx386/wasm.sym   <RELROOT>/rel2/qnx/sym/
    <CPCMD> linux386/wasm.exe <RELROOT>/rel2/binl/wasm.
    <CPCMD> linux386/wasm.sym <RELROOT>/rel2/binl/wasm.sym

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
