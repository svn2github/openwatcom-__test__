# PLUS Builder Control file
# =========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d buildwpp <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
#
# 386 NT hosted compilers
#
#  i86 target
    <CPCMD> nt386.i86/wcppi86.exe <relroot>/rel2/binnt/wpp.exe
    <CPCMD> nt386.i86/wppdi86.dll <relroot>/rel2/binnt/wppdi86.dll
    <CPCMD> nt386.i86/wppdi86.sym <relroot>/rel2/binnt/wppdi86.sym
    <CPCMD> nt386.i86/wppi8601.int <relroot>/rel2/binnt/wppi8601.int
#  386 target
    <CPCMD> nt386.386/wcpp386.exe <relroot>/rel2/binnt/wpp386.exe
    <CPCMD> nt386.386/wppd386.dll <relroot>/rel2/binnt/wppd386.dll
    <CPCMD> nt386.386/wppd386.sym <relroot>/rel2/binnt/wppd386.sym
    <CPCMD> nt386.386/wpp38601.int <relroot>/rel2/binnt/wpp38601.int

#  Optima 386 target (with -br switch)
    <CPCMD> nt386dll.386/wcpp386.exe <relroot>/rel2/binnt/rtdll/wpp386.exe
    <CPCMD> nt386dll.386/wppd386.dll <relroot>/rel2/binnt/rtdll/wppd386.dll
    <CPCMD> nt386dll.386/wppd386.sym <relroot>/rel2/binnt/rtdll/wppd386.sym
    <CPCMD> nt386dll.386/wpp38601.int <relroot>/rel2/binnt/rtdll/wpp38601.int

#
# 386 OS/2 hosted compilers
#
#  i86 target
    <CPCMD> os2386.i86/wcppi86.exe <relroot>/rel2/binp/wpp.exe
    <CPCMD> os2386.i86/wppdi86.dll <relroot>/rel2/binp/dll/wppdi86.dll
    <CPCMD> os2386.i86/wppdi86.sym <relroot>/rel2/binp/dll/wppdi86.sym
    <CPCMD> os2386.i86/wppi8601.int <relroot>/rel2/binp/dll/wppi8601.int
#  386 target
    <CPCMD> os2386.386/wcpp386.exe <relroot>/rel2/binp/wpp386.exe
    <CPCMD> os2386.386/wppd386.dll <relroot>/rel2/binp/dll/wppd386.dll
    <CPCMD> os2386.386/wppd386.sym <relroot>/rel2/binp/dll/wppd386.sym
    <CPCMD> os2386.386/wpp38601.int <relroot>/rel2/binp/dll/wpp38601.int
#
# 386 OSI hosted compilers
#
#  i86 target
#    <CPCMD> osi386.i86/wcppi86.exe <relroot>/rel2/binw/wpp.exe
#    <CPCMD> osi386.i86/wcppi86.sym <relroot>/rel2/binw/wpp.sym
#    <CPCMD> osi386.i86/wppi8601.int <relroot>/rel2/binw/wppi8601.int
#  386 target
#    <CPCMD> osi386.386/wcpp386.exe <relroot>/rel2/binw/wpp386.exe
#    <CPCMD> osi386.386/wcpp386.sym <relroot>/rel2/binw/wpp386.sym
#    <CPCMD> osi386.386/wpp38601.int <relroot>/rel2/binw/wpp38601.int
#
# 386 DOS hosted compilers
#
#  i86 target
    <CPCMD> dos386.i86/wcppi86.exe <relroot>/rel2/binw/wpp.exe
    <CPCMD> dos386.i86/wcppi86.sym <relroot>/rel2/binw/wpp.sym
    <CPCMD> dos386.i86/wppi8601.int <relroot>/rel2/binw/wppi8601.int
#  386 target
    <CPCMD> dos386.386/wcpp386.exe <relroot>/rel2/binw/wpp386.exe
    <CPCMD> dos386.386/wcpp386.sym <relroot>/rel2/binw/wpp386.sym
    <CPCMD> dos386.386/wpp38601.int <relroot>/rel2/binw/wpp38601.int
#
# 386 QNX hosted compilers
#
#  i86 target
#    <CPCMD> qnx386.i86/wcppi86.qnx <relroot>/rel2/qnx/binq/wpp.
#    <CPCMD> qnx386.i86/wcppi86.sym <relroot>/rel2/qnx/sym/wpp.sym
#    <CPCMD> qnx386.i86/wppi8601.int <relroot>/rel2/qnx/sym/wppi8601.int
#  386 target
#    <CPCMD> qnx386.386/wcpp386.qnx <relroot>/rel2/qnx/binq/wpp386.
#    <CPCMD> qnx386.386/wcpp386.sym <relroot>/rel2/qnx/sym/wpp386.sym
#    <CPCMD> qnx386.386/wpp38601.int <relroot>/rel2/qnx/sym/wpp38601.int

# 386 Linux hosted compilers
#
#  i86 target
    <CPCMD> linux386.i86/wcppi86.elf <relroot>/rel2/binl/wpp
    <CPCMD> linux386.i86/wcppi86.sym <relroot>/rel2/binl/wpp.sym
    <CPCMD> linux386.i86/wppi8601.int <relroot>/rel2/binl/wppi8601.int
#  386 target
    <CPCMD> linux386.386/wcpp386.elf <relroot>/rel2/binl/wpp386
    <CPCMD> linux386.386/wcpp386.sym <relroot>/rel2/binl/wpp386.sym
    <CPCMD> linux386.386/wpp38601.int <relroot>/rel2/binl/wpp38601.int

[ BLOCK <1> clean ]
#==================
    pmake -d buildwpp <2> <3> <4> <5> <6> <7> <8> <9> -h clean

