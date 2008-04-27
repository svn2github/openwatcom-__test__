# wlink Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wlink

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set BOOTCOPY=<CPCMD> wl.exe <OWBINDIR>/wlink<CMDEXT>
set BOOTCLEAN=rm -f <OWBINDIR>/wlink<CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================

  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dos386/wl.exe                     <RELROOT>/binw/wlink.exe
    <CPCMD> <PROJDIR>/dos386/wl.sym                     <RELROOT>/binw/wlink.sym
    <CPCMD> <PROJDIR>/ms2wlink/dosi86/ms2wlink.exe      <RELROOT>/binw/ms2wlink.exe
    <CPCMD> <PROJDIR>/fcenable/dosi86/fcenable.exe      <RELROOT>/binw/fcenable.exe
    <CPCMD> <PROJDIR>/exe2bin/dosi86/exe2bin.exe        <RELROOT>/binw/exe2bin.exe
    <CPCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CPCMD> <PROJDIR>/wlbin.lnk                         <RELROOT>/binw/wlink.lnk
    <CPCMD> <PROJDIR>/ovlldr/dosi86/wovl.lib            <RELROOT>/lib286/dos/wovl.lib
#    <CPCMD> <PROJDIR>/ovlldr/dosi86/wmovl.lib           <RELROOT>/lib286/dos/wmovl.lib

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386.dll/wl.exe                 <RELROOT>/binp/wlink.exe
    <CPCMD> <PROJDIR>/os2386.dll/wl.dll                 <RELROOT>/binp/dll/wlink.dll
    <CPCMD> <PROJDIR>/os2386.dll/wl.sym                 <RELROOT>/binp/dll/wlink.sym
    <CPCMD> <PROJDIR>/ms2wlink/os2i86/ms2wlink.exe      <RELROOT>/binp/ms2wlink.exe
    <CPCMD> <PROJDIR>/fcenable/os2i86/fcenable.exe      <RELROOT>/binp/fcenable.exe
    <CPCMD> <PROJDIR>/exe2bin/os2386/exe2bin.exe        <RELROOT>/binp/exe2bin.exe
    <CPCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CPCMD> <PROJDIR>/wlbinp.lnk                        <RELROOT>/binp/wlink.lnk

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386.dll/wl.exe                  <RELROOT>/binnt/wlink.exe
    <CPCMD> <PROJDIR>/nt386.dll/wl.dll                  <RELROOT>/binnt/wlink.dll
    <CPCMD> <PROJDIR>/nt386.dll/wl.sym                  <RELROOT>/binnt/wlink.sym
    <CPCMD> <PROJDIR>/nt386.rtd/wl.exe                  <RELROOT>/binnt/rtdll/wlink.exe
    <CPCMD> <PROJDIR>/nt386.rtd/wl.dll                  <RELROOT>/binnt/rtdll/wlink.dll
    <CPCMD> <PROJDIR>/ms2wlink/nt386/ms2wlink.exe       <RELROOT>/binnt/ms2wlink.exe
    <CPCMD> <PROJDIR>/fcenable/nt386/fcenable.exe       <RELROOT>/binnt/fcenable.exe
    <CPCMD> <PROJDIR>/exe2bin/nt386/exe2bin.exe         <RELROOT>/binnt/exe2bin.exe
    <CPCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CPCMD> <PROJDIR>/wlbinnt.lnk                       <RELROOT>/binnt/wlink.lnk

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/wl.exe                   <RELROOT>/binl/wlink
    <CPCMD> <PROJDIR>/linux386/wl.sym                   <RELROOT>/binl/wlink.sym
    <CPCMD> <PROJDIR>/ms2wlink/linux386/ms2wlink.exe    <RELROOT>/binl/ms2wlink
    <CPCMD> <PROJDIR>/fcenable/linux386/fcenable.exe    <RELROOT>/binl/fcenable
    <CPCMD> <PROJDIR>/exe2bin/linux386/exe2bin.exe      <RELROOT>/binl/exe2bin
    <CPCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binl/wlsystem.lnk
    <CPCMD> <PROJDIR>/wlbinl.lnk                        <RELROOT>/binl/wlink.lnk

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp.dll/wl.exe                  <RELROOT>/axpnt/wlink.exe
    <CPCMD> <PROJDIR>/ntaxp.dll/wl.dll                  <RELROOT>/axpnt/wlink.dll
    <CPCMD> <PROJDIR>/exe2bin/ntaxp/exe2bin.exe         <RELROOT>/axpnt/exe2bin.exe
    <CPCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CPCMD> <PROJDIR>/wlaxpnt.lnk                       <RELROOT>/axpnt/wlink.lnk

  [ IFDEF (os_qnx) <2*> ]
    <CPCMD> <PROJDIR>/qnx386/wl.exe                     <RELROOT>/qnx/binq/wlink
    <CPCMD> <PROJDIR>/qnx386/wl.sym                     <RELROOT>/qnx/sym/wlink.sym
    <CPCMD> <PROJDIR>/qnx.lnk                           <RELROOT>/qnx/etc/wlink.lnk

[ BLOCK . . ]
#============

cdsay <PROJDIR>