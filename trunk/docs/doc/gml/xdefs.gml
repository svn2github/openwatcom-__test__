.*
.* Global to all books
.*
.if &e'&target eq 0 .do begin
:set symbol="target"    value="AXPNT".
:set symbol="computer"  value="AXP".
:set symbol="target"    value="DOS".
:set symbol="computer"  value="Intel".
.do end
.if &e'&company eq 0 .do begin
:set symbol="company"   value="Open Watcom".
:set symbol="scompany"  value="Watcom International Corp.".
:set symbol="pcompany"  value="Sybase".
:set symbol="spcompany" value="Sybase, Inc.".
.do end
:set symbol="cpyyear"   value="2002".
.dm cpyrit begin
Copyright by WATCOM International Corp. &*, &cpyyear.. All rights reserved.
.dm cpyrit end
.dm trdmrk begin
WATCOM is a trademark of Sybase, Inc. and its subsidiaries.
.dm trdmrk end
:set symbol="ver"       value="1".
:set symbol="rev"       value="0".
:set symbol="pver"      value="10".
:set symbol="prev"      value="6".
:set symbol="version"   value="110".
:set symbol="minram"    value="8 MB".
:set symbol="mfc16"     value="MFC 2.52b".
:set symbol="mfc32"     value="MFC 4.1".
:set symbol="alpha"     value="noAXP".
:set symbol="cmpcname"  value="&company C".
:set symbol="cmppname"  value="&company C++".
:set symbol="cmpfname"  value="&company FORTRAN 77".
.*
:set symbol="watpathup" value="WATCOM".
.*
.if '&target' eq 'QNX' .do begin
:set symbol="pathnam"   value="/usr".
:set symbol="pathnamup" value="/usr".
:set symbol="sw"         value="-".
:set symbol="pc"         value="/".
:set symbol="ps"         value=":".
:set symbol="psword"     value="colon".
.do end
.el .do begin
:set symbol="pathnam"   value="\watcom".
:set symbol="pathnamup" value="\WATCOM".
:set symbol="sw"        value="/".
:set symbol="pc"        value="\".
:set symbol="ps"        value="~;".
:set symbol="psword"    value="semicolon".
.do end
.*
.* Powersoft Power++ Specific
.*
:set symbol="powerpp"   value="Power++".
.*
.* WATCOM Debugger Specific
.*
:set symbol="dbgname"   value="&company Debugger".
.if '&target' eq 'QNX' .do begin
:set symbol="dbgvar"    value="WD".
:set symbol="dbgvarup"  value="WD".
:set symbol="dbgcmd"    value="wd".
:set symbol="dbgcmdup"  value="wd".
:set symbol="dbgsuff"   value="dbg".
:set symbol="dbgsuffup" value="dbg".
.do end
.el .do begin
:set symbol="dbgvar"    value="wd".
:set symbol="dbgvarup"  value="WD".
:set symbol="dbgcmd"    value="wd".
:set symbol="dbgcmdup"  value="WD".
:set symbol="dbgsuff"   value="dbg".
:set symbol="dbgsuffup" value="DBG".
.do end
.*
.* WATCOM Linker/Librarian/Strip Specific
.*
:set symbol="lnkname"   value="&company Linker".
:set symbol="lnkcmd"    value="wlink".
:set symbol="overlay"   value="no".
:set symbol="m2wcmd"    value="ms2wlink".
:set symbol="fcename"   value="&company Far Call Optimization Enabling Utility"
:set symbol="fcecmd"    value="fcenable".
:set symbol="libname"   value="&company Library Manager".
:set symbol="libcmd"    value="wlib".
:set symbol="stripname" value="&company Strip Utility".
:set symbol="stripcmd"  value="wstrip".
.if '&target' eq 'QNX' .do begin
:set symbol="lnkcmdup"  value="wlink".
:set symbol="m2wcmdup"  value="ms2wlink".
:set symbol="fcecmdup"  value="fcenable".
:set symbol="libcmdup"  value="wlib".
:set symbol="stripcmdup" value="wstrip".
:set symbol="libvar"    value="LIB".
:set symbol="pathvar"   value="WATCOM".
.do end
.el .do begin
:set symbol="lnkcmdup"  value="WLINK".
:set symbol="m2wcmdup"  value="MS2WLINK".
:set symbol="fcecmdup"  value="FCENABLE".
:set symbol="libcmdup"  value="WLIB".
:set symbol="stripcmdup" value="WSTRIP".
:set symbol="libvar"    value="lib".
:set symbol="pathvar"   value="watcom".
.do end
:set symbol="libvarup"  value="LIB".
:set symbol="pathvarup" value="WATCOM".
.*
.* WATCOM Assembler Specific
.*
:set symbol="asmname"   value="&company Assembler".
:set symbol="asmcmd"    value="wasm".
.if '&target' eq 'QNX' .do begin
:set symbol="asmcmdup"  value="wasm".
.do end
.el .do begin
:set symbol="asmcmdup"  value="WASM".
.do end
:set symbol="wasname"   value="&company AXP Assembler".
:set symbol="wascmd"    value="wasaxp".
.if '&target' eq 'QNX' .do begin
:set symbol="wascmdup"  value="wasaxp".
.do end
.el .do begin
:set symbol="wascmdup"  value="WASAXP".
.do end
.*
.* WATCOM Disassembler Specific
.*
:set symbol="disname"   value="&company Disassembler".
:set symbol="discmd"    value="wdis".
.if '&target' eq 'QNX' .do begin
:set symbol="discmdup"  value="wdis".
.do end
.el .do begin
:set symbol="discmdup"  value="WDIS".
.do end
.*
.* WATCOM Patch Utility Specific
.*
:set symbol="patchname" value="&company Patch Utility".
:set symbol="patchcmd"  value="bpatch".
.if '&target' eq 'QNX' .do begin
:set symbol="patchcmdup" value="bpatch".
.do end
.el .do begin
:set symbol="patchcmdup" value="BPATCH".
.do end
.*
.* WATCOM Make and Touch Specific
.*
:set symbol="makname"   value="&company Make".
:set symbol="maksname"  value="Make".
:set symbol="makcmd"    value="wmake".
:set symbol="makcmdup"  value="WMAKE".
:set symbol="tchname"   value="&company Touch".
:set symbol="tchcmd"    value="wtouch".
:set symbol="tchcmdup"  value="WTOUCH".
.*
.* WATCOM Profiler Specific
.*
:set symbol="prfname"   value="&company Execution Profiler".
:set symbol="prfcmd"    value="wprof".
:set symbol="smpname"   value="&company Execution Sampler".
:set symbol="smpcmd"    value="wsample".
.if '&target' eq 'QNX' .do begin
:set symbol="prfcmdup"  value="wprof".
:set symbol="smpcmdup"  value="wsample".
.do end
.el .do begin
:set symbol="prfcmdup"  value="WPROF".
:set symbol="smpcmdup"  value="WSAMPLE".
.do end
.*
.* WATCOM Windows Resource Compiler Specific
.*
:set symbol="wrcname"   value="&company Resource Compiler".
:set symbol="wrccmd"    value="wrc".
:set symbol="wrccmdup"  value="WRC".
.*
.* GUI Tools
.*
:set symbol="drwc"      value="Dr. &company".
:set symbol="dr95"      value="Dr. &company".
:set symbol="drnt"      value="Dr. &company".
:set symbol="spy"       value="Spy".
:set symbol="dde"       value="DDE Spy".
:set symbol="edname"    value="&company Editor".
:set symbol="editor"    value="Editor".
:set symbol="ide"       value="Integrated Development Environment".
:set symbol="wide"      value="&company &ide".
:set symbol="vip"       value="IDE".
:set symbol="vip_cfg"   value="ide.cfg".
:set symbol="dbgname"   value="&company Debugger".
:set symbol="dbgcmd"    value="wd".
:set symbol="dbgcmdup"  value="WD".
:set symbol="brname"    value="&company Browser".
:set symbol="br"        value="Browser".
:set symbol="watc"      value="&company C/C++".
:set symbol="watf"      value="&company FORTRAN 77".
.* following are used in "Getting Started"
.if '&format' eq '7x9' .do begin
:set symbol="watc16"    value="&company C/C++&S'16.".
:set symbol="watc32"    value="&company C/C++&S'32.".
:set symbol="watf16"    value="&company FORTRAN 77&S'16.".
:set symbol="watf32"    value="&company FORTRAN 77&S'32.".
.do end
.el .do begin
:set symbol="watc16"    value="&company C/C++(16)".
:set symbol="watc32"    value="&company C/C++(32)".
:set symbol="watf16"    value="&company FORTRAN 77/16".
:set symbol="watf32"    value="&company FORTRAN 77/32".
.do end
.*
.* Blue Sky Visual Programmer
.*
:set symbol="vpname"    value="Visual Programmer".
.*
.* AmerEnglish spelling
.*
.sr colour='color'
.sr ccolour='Color'
