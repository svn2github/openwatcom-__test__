.if '&alpha' eq 'AXP' .do begin
.sr x86only='(x86 only)'
.sr 286only='(x86 16-bit only)'
.sr 386only='(x86 32-bit only)'
.sr AXPonly='(AXP only)'
.do end
.el .do begin
.sr x86only=''
.sr 286only='(16-bit only)'
.sr 386only='(32-bit only)'
.sr AXPonly='????should not appear????'
.do end
.*
.note 0
:CMT. .ix 'options' '0'
&286only.
8088 and 8086 instructions
(default for 16-bit)
:optref refid='SW0'.
.*
.note 1
:CMT. .ix 'options' '1'
&286only.
188 and 186 instructions
:optref refid='SW1'.
.*
.note 2
:CMT. .ix 'options' '2'
&286only.
286 instructions
:optref refid='SW2'.
.*
.note 3
:CMT. .ix 'options' '3'
&286only.
386 instructions
:optref refid='SW3'.
.*
.note 4
:CMT. .ix 'options' '4'
&286only.
486 instructions
:optref refid='SW4'.
.*
.note 5
:CMT. .ix 'options' '5'
&286only.
Pentium instructions
:optref refid='SW5'.
.*
.if &version ge 110 .do begin
.note 6
:CMT. .ix 'options' '6'
&286only.
Pentium Pro instructions
:optref refid='SW6'.
.do end
.*
.note 3r&optdag.
:CMT. .ix 'options' '3r'
&386only.
generate 386 instructions based on 386 instruction timings and use
register-based argument passing conventions
:optref refid='SW3RS'.
.*
.note 3s
:CMT. .ix 'options' '3s'
&386only.
generate 386 instructions based on 386 instruction timings and use
stack-based argument passing conventions
:optref refid='SW3RS'.
.*
.note 4r&optdag.
:CMT. .ix 'options' '4r'
&386only.
generate 386 instructions based on 486 instruction timings and use
register-based argument passing conventions
:optref refid='SW4RS'.
.*
.note 4s
:CMT. .ix 'options' '4s'
&386only.
generate 386 instructions based on 486 instruction timings and use
stack-based argument passing conventions
:optref refid='SW4RS'.
.*
.note 5r&optdag.
:CMT. .ix 'options' '5r'
&386only.
generate 386 instructions based on Intel Pentium instruction timings
and use register-based argument passing conventions
(default for 32-bit)
:optref refid='SW5RS'.
.*
.note 5s
:CMT. .ix 'options' '5s'
&386only.
generate 386 instructions based on Intel Pentium instruction timings
and use stack-based argument passing conventions
:optref refid='SW5RS'.
.*
.if &version ge 110 .do begin
.note 6r&optdag.
:CMT. .ix 'options' '6r'
&386only.
generate 386 instructions based on Intel Pentium Pro instruction
timings and use register-based argument passing conventions
:optref refid='SW6RS'.
.*
.note 6s
:CMT. .ix 'options' '6s'
&386only.
generate 386 instructions based on Intel Pentium Pro instruction
timings and use stack-based argument passing conventions
:optref refid='SW6RS'.
.do end
.*
.if &version lt 107 .do begin
.note 7&optdag.
:CMT. .ix 'options' '7'
generate in-line 80x87 instructions
(equivalent to "fpi87" option below)
:optref refid='SW7'.
.do end
.*
.if &version ge 112 .do begin
.note ad[=<file_name>]
generate makefile style auto depend file
:optref refid='SWad'.
.do end
.if &version ge 112 .do begin
.note adbs
force slashes generated in makefile style auto depend to backward
:optref refid='SWadbs'.
.do end
.if &version ge 112 .do begin
.note add[=<file_name>]
specify source dependancy name generated in make-style autodep file
:optref refid='SWadd'.
.do end
.if &version ge 112 .do begin
.note adfs
force slashes generated in makefile style auto depend to forward
:optref refid='SWadfs'.
.do end
.if &version ge 112 .do begin
.note adt[=<target_name>]
specify target name generated in makefile style auto depend
:optref refid='SWadt'.
.do end
.if '&alpha' eq 'AXP' .do begin
.note as
:CMT. .ix 'options' 'as'
&AXPonly.
assume short integers are aligned
:optref refid='SWas'.
.do end
.*
.if &version ge 110 .do begin
.note bc
:CMT. .ix 'options' 'bc'
(C++ only)
build target is a console application
:optref refid='SWbc'.
.do end
.*
.note bd
:CMT. .ix 'options' 'bd'
build target is a Dynamic Link Library (DLL)
:optref refid='SWbd'.
.*
.if &version ge 110 .do begin
.note bg
:CMT. .ix 'options' 'bg'
(C++ only)
build target is a GUI application
:optref refid='SWbg'.
.do end
.*
.note bm
:CMT. .ix 'options' 'bm'
build target is a multi-thread environment
:optref refid='SWbm'.
.*
.if &version ge 107 .do begin
.note br
:CMT. .ix 'options' 'br'
build target uses DLL version of C/C++ run-time libraries
:optref refid='SWbr'.
.do end
.*
.note bt[=<os>]
:CMT. .ix 'options' 'bt'
build target for operating system <os>
:optref refid='SWbt'.
.*
.note bw
:CMT. .ix 'options' 'bw'
build target uses default windowing support
:optref refid='SWbw'.
.*
.if &version ge 107 .do begin
.note d0
:CMT. .ix 'options' 'd0'
(C++ only)
no debugging information
:optref refid='SWd0'.
.do end
.*
.note d1
:CMT. .ix 'options' 'd1'
line number debugging information
:optref refid='SWd1'.
.*
.note d1+
:CMT. .ix 'options' 'd1+'
(C only)
line number debugging information plus typing information for global
symbols and local structs and arrays
:optref refid='SWd1pls'.
.*
.note d2
:CMT. .ix 'options' 'd2'
full symbolic debugging information
:optref refid='SWd2'.
.*
.if &version ge 107 .do begin
.note d2i
:CMT. .ix 'options' 'd2i'
(C++ only)
d2 and debug inlines; emit inlines as external out-of-line functions
:optref refid='SWd2i'.
.do end
.*
.if &version ge 110 .do begin
.note d2s
:CMT. .ix 'options' 'd2s'
(C++ only)
d2 and debug inlines; emit inlines as static out-of-line functions
:optref refid='SWd2s'.
.do end
.*
.if &version ge 107 .do begin
.note d2t
:CMT. .ix 'options' 'd2t'
(C++ only)
full symbolic debugging information, without type names
:optref refid='SWd2t'.
.do end
.*
.note d3
:CMT. .ix 'options' 'd3'
full symbolic debugging with unreferenced type names
:optref refid='SWd3'.
,*
.if &version ge 110 .do begin
.note d3i
:CMT. .ix 'options' 'd3i'
(C++ only)
d3 plus debug inlines; emit inlines as external out-of-line functions
:optref refid='SWd3i'.
.do end
.*
.if &version ge 110 .do begin
.note d3s
:CMT. .ix 'options' 'd3s'
(C++ only)
d3 plus debug inlines; emit inlines as static out-of-line functions
:optref refid='SWd3s'.
.do end
.*
.note d<name>[=text]
:CMT. .ix 'options' 'd'
preprocessor #define name [text]
:optref refid='SWd'.
.*
.note d+
:CMT. .ix 'options' 'd+'
allow extended -d macro definitions
:optref refid='SWdpls'.
.*
.note db
:CMT. .ix 'options' 'db'
generate browsing information
:optref refid='SWdb'.
.*
.note e<number>
:CMT. .ix 'options' 'e'
set error limit number (default is 20)
:optref refid='SWe'.
.*
.note ee
:CMT. .ix 'options' 'ee'
&x86only.
call epilogue hook routine
:optref refid='SWee'.
.*
.if &version ge 107 .do begin
.note ef
:CMT. .ix 'options' 'ef'
use full path names in error messages
:optref refid='SWef'.
.do end
.*
.note ei
:CMT. .ix 'options' 'ei'
force enum base type to use at least an int
:optref refid='SWei'.
.*
.if &version ge 107 .do begin
.note em
:CMT. .ix 'options' 'em'
force enum base type to use minimum
:optref refid='SWem'.
.do end
.*
.note en
:CMT. .ix 'options' 'en'
&x86only.
emit routine name before prologue
:optref refid='SWen'.
.*
.note ep[<number>]
:CMT. .ix 'options' 'ep'
&x86only.
call prologue hook routine with number of stack bytes available
:optref refid='SWep'.
.*
.if &version ge 107 .do begin
.note eq
:CMT. .ix 'options' 'eq'
do not display error messages (they are still written to a file)
:optref refid='SWeq'.
.do end
.*
.if &version ge 110 .do begin
.note er
:CMT. .ix 'options' 'er'
(C++ only)
do not recover from undefined symbol errors
:optref refid='SWer'.
.do end
.*
.note et
:CMT. .ix 'options' 'et'
&x86only.
Pentium profiling
:optref refid='SWet'.
.*
.note ew
:CMT. .ix 'options' 'ew'
(C++ only)
generate less verbose messages
:optref refid='SWew'.
.*
.note ez&optdag.
:CMT. .ix 'options' 'ez'
&386only.
generate Phar Lap Easy OMF-386 object file
:optref refid='SWez'.
.*
.if &version ge 107 .do begin
.note fc=<file_name>
:CMT. .ix 'options' 'fc'
(C++ only)
specify file of command lines to be batch processed
:optref refid='SWfc'.
.do end
.*
.note fh[q][=<file_name>]
:CMT. .ix 'options' 'fh, fhq'
use precompiled headers
:optref refid='SWfh'.
.*
.if &version ge 107 .do begin
.note fhd
:CMT. .ix 'options' 'fhd'
store debug info for pre-compiled header once (DWARF only)
:optref refid='SWfhd'.
.do end
.*
.if &version ge 110 .do begin
.note fhr
:CMT. .ix 'options' 'fhr'
(C++ only)
force compiler to read pre-compiled header
:optref refid='SWfhr'.
.do end
.*
.if &version ge 107 .do begin
.note fhw
:CMT. .ix 'options' 'fhw'
(C++ only)
force compiler to write pre-compiled header
:optref refid='SWfhw'.
.do end
.*
.if &version ge 110 .do begin
.note fhwe
:CMT. .ix 'options' 'fhwe'
(C++ only)
don't include pre-compiled header warnings when "we" is used
:optref refid='SWfhwe'.
.do end
.*
.note fi=<file_name>
:CMT. .ix 'options' 'fi'
force file_name to be included
:optref refid='SWfi'.
.*
.note fo=<file_name>
:CMT. .ix 'options' 'fo'
set object or preprocessor output file specification
:optref refid='SWfo'.
:optref refid='SWfo2'.
.*
.note fpc
:CMT. .ix 'options' 'fpc'
&x86only.
generate calls to floating-point library
:optref refid='SWfpc'.
.*
.note fpi&optdag.
:CMT. .ix 'options' 'fpi'
&286only.
generate in-line 80x87 instructions with emulation (default)
.np
&386only.
generate in-line 387 instructions with emulation (default)
:optref refid='SWfpi'.
.*
.note fpi87&optdag.
:CMT. .ix 'options' 'fpi87'
&286only.
generate in-line 80x87 instructions
.np
&386only.
generate in-line 387 instructions
:optref refid='SWfpi87'.
.*
.note fp2
:CMT. .ix 'options' 'fp2'
&x86only.
generate in-line 80x87 instructions
:optref refid='SWfp2'.
.*
.note fp3
:CMT. .ix 'options' 'fp3'
&x86only.
generate in-line 387 instructions
:optref refid='SWfp3'.
.*
.note fp5&optdag.
:CMT. .ix 'options' 'fp5'
&x86only.
generate in-line 80x87 instructions optimized for Pentium processor
:optref refid='SWfp5'.
.*
.if &version ge 110 .do begin
.note fp6&optdag.
:CMT. .ix 'options' 'fp6'
&x86only.
generate in-line 80x87 instructions optimized for Pentium Pro
processor
:optref refid='SWfp6'.
.do end
.*
.note fpd&optdag.
:CMT. .ix 'options' 'fpd'
&x86only.
enable generation of Pentium FDIV bug check code
:optref refid='SWfpd'.
.*
.note fpr&optdag.
:CMT. .ix 'options' 'fpr'
&x86only.
generate 8087 code compatible with older versions of compiler
:optref refid='SWfpr'.
.*
.note fr=<file_name>
:CMT. .ix 'options' 'fr'
set error file specification
:optref refid='SWfr'.
.*
.note ft
:CMT. .ix 'options' 'ft'
(C++ only)
try truncated (8.3) header file specification
:optref refid='SWft'.
.*
.note fx
:CMT. .ix 'options' 'fx'
(C++ only)
do not try truncated (8.3) header file specification
:optref refid='SWfx'.
.*
.note fzh
:CMT. .ix 'options' 'fzh'
(C++ only)
do not automatically append extensions for include files
:optref refid='SWfzh'.
.*
.note fzs
:CMT. .ix 'options' 'fzs'
(C++ only)
do not automatically append extensions for source files
:optref refid='SWfzs'.
.*
.note g=<codegroup>
:CMT. .ix 'options' 'g'
&x86only.
set code group name
:optref refid='SWg'.
.*
.note h{w,d,c}
:CMT. .ix 'options' 'hw, hd, hc'
set debug output format (&company, Dwarf, Codeview)
:optref refid='SWhwdc'
.*
:CMT. .note h{d,c}
:CMT. :CMT. .ix 'options' 'hw, hd, hc'
:CMT. &AXPonly.
:CMT. set debug output format (Dwarf, Codeview)
:CMT. :optref refid='SWhdc'
.*
.note i=<directory>
:CMT. .ix 'options' 'i'
add directory to list of include directories
:optref refid='SWi'.
.*
.note j
:CMT. .ix 'options' 'j'
change char default from unsigned to signed
:optref refid='SWj'.
.*
.if &version ge 107 .do begin
.note k
:CMT. .ix 'options' 'k'
(C++ only)
continue processing files (ignore errors)
:optref refid='SWk'.
.do end
.*
.note m{f,s,m,c,l,h}
:CMT. .ix 'options' 'mf, ms, mm, mc, ml, mh'
&x86only.
memory model &mdash.
mf=flat :optref refid='SWmf'.,
ms=small :optref refid='SWms'.,
mm=medium :optref refid='SWmm'.,
mc=compact :optref refid='SWmc'.,
ml=large :optref refid='SWml'.,
mh=huge :optref refid='SWmh'.
(default is "ms" for 16-bit and Netware, "mf" for 32-bit)
.*
.if &e'&wcldesc. eq 1 .do begin
.note mt
:CMT. .ix '&wclcmdup16 options' 'mt'
:CMT. .ix '&wclcmdup32 options' 'mt'
&286only.
compile code for the small memory model and then use the &lnkname to
generate a "COM" file
.do end
.*
.note nc=<name>
:CMT. .ix 'options' 'nc'
&x86only.
set name of the code class
:optref refid='SWnc'.
.*
.note nd=<name>
:CMT. .ix 'options' 'nd'
&x86only.
set name of the "data" segment
:optref refid='SWnd'.
.*
.note nm=<name>
:CMT. .ix 'options' 'nm'
set module name different from filename
:optref refid='SWnm'.
.*
.note nt=<name>
:CMT. .ix 'options' 'nt'
&x86only.
set name of the "text" segment
:optref refid='SWnt'.
.*
.if &version ge 110 .do begin
.note o{a,b,c,d,e,f,f+,h,i,i+,k,l,l+,m,n,o,p,r,s,t,u,x,z}
.do end
.el .if &version ge 107 .do begin
.note o{a,b,c,d,e,f,f+,i,l,l+,m,n,o,p,r,s,t,u,x,z}
.do end
.el .do begin
.note o{a,c,d,e,f,f+,i,l,l+,m,n,o,p,r,s,t,u,x,z}
.do end
:CMT. .ix 'options' 'oa'
.sr $SWoa=1
.if &version ge 107 .do begin
:CMT. .ix 'options' 'ob'
.sr $SWob=1
.do end
:CMT. .ix 'options' 'oc'
.sr $SWoc=1
:CMT. .ix 'options' 'od'
.sr $SWod=1
:CMT. .ix 'options' 'oe'
.sr $SWoe=1
:CMT. .ix 'options' 'of'
.sr $SWof=1
:CMT. .ix 'options' 'of+'
.sr $SWofpls=1
.if &version ge 110 .do begin
:CMT. .ix 'options' 'oh'
.sr $SWoh=1
.do end
:CMT. .ix 'options' 'oi'
.sr $SWoi=1
.if &version ge 110 .do begin
:CMT. .ix 'options' 'oi+'
.sr $SWoipls=1
.do end
.if &version ge 110 .do begin
:CMT. .ix 'options' 'ok'
.sr $SWok=1
.do end
:CMT. .ix 'options' 'ol'
.sr $SWol=1
:CMT. .ix 'options' 'ol+'
.sr $SWolpls=1
:CMT. .ix 'options' 'om'
.sr $SWom=1
:CMT. .ix 'options' 'on'
.sr $SWon=1
:CMT. .ix 'options' 'oo'
.sr $SWoo=1
:CMT. .ix 'options' 'op'
.sr $SWop=1
:CMT. .ix 'options' 'or'
.sr $SWor=1
:CMT. .ix 'options' 'os'
.sr $SWos=1
:CMT. .ix 'options' 'ot'
.sr $SWot=1
:CMT. .ix 'options' 'ou'
.sr $SWou=1
:CMT. .ix 'options' 'ox'
.sr $SWox=1
:CMT. .ix 'options' 'oz'
.sr $SWoz=1
.*
&x86only.
control optimization
:optref refid='SWoa'.
:optref refid='SWof'.
.*
.if '&alpha' eq 'AXP' .do begin
.note o{a,d,e,i,l,n,o,r,s,t,u,x,z}
:CMT. .ix 'options' 'oa'
.sr $SWoa=1
:CMT. .ix 'options' 'od'
.sr $SWod=1
:CMT. .ix 'options' 'oe'
.sr $SWoe=1
:CMT. .ix 'options' 'oi'
.sr $SWoi=1
:CMT. .ix 'options' 'ol'
.sr $SWol=1
:CMT. .ix 'options' 'on'
.sr $SWon=1
:CMT. .ix 'options' 'oo'
.sr $SWoo=1
:CMT. .ix 'options' 'or'
.sr $SWor=1
:CMT. .ix 'options' 'os'
.sr $SWos=1
:CMT. .ix 'options' 'ot'
.sr $SWot=1
:CMT. .ix 'options' 'ou'
.sr $SWou=1
:CMT. .ix 'options' 'ox'
.sr $SWox=1
:CMT. .ix 'options' 'oz'
.sr $SWoz=1
&AXPonly.
control optimization
:optref refid='SWoa'.
.do end
.*
.note p{e,l,c,w=<num>}
:CMT. .ix 'options' 'pe'
:CMT. .ix 'options' 'pl'
:CMT. .ix 'options' 'pc'
:CMT. .ix 'options' 'pw'
.*
preprocess file only, sending output to standard output;
"c" include comments;
"e" encrypt identifiers (C++ only);
"l" include #line directives;
w=<num> wrap output lines at <num> columns (zero means no wrap)
:optref refid='SWp'.
.*
.note r&optdag.
:CMT. .ix 'options' 'r'
&x86only.
save/restore segment registers
:optref refid='SWr'.
.*
.note ri&optdag.
:CMT. .ix 'options' 'ri'
&x86only.
return chars and shorts as ints
:optref refid='SWri'.
.*
.note s
:CMT. .ix 'options' 's'
remove stack overflow checks
:optref refid='SWs'.
.*
.note sg
:CMT. .ix 'options' 'sg'
&x86only.
generate calls to grow the stack
:optref refid='SWsg'.
.*
.if '&alpha' eq 'AXP' .do begin
.note si
:CMT. .ix 'options' 'si'
&AXPonly.
initialize stack frame storage with pattern
:optref refid='SWsi'.
.do end
.*
.note st
:CMT. .ix 'options' 'st'
&x86only.
touch stack through SS first
:optref refid='SWst'.
.*
.note t=<num>
:CMT. .ix 'options' 't'
(C++ only)
set tab stop multiplier
:optref refid='SWt'.
.*
.note u<name>
:CMT. .ix 'options' 'u'
preprocessor #undef name
:optref refid='SWu'.
.*
.note v
:CMT. .ix 'options' 'v'
output function declarations to .def file (with typedef names)
:optref refid='SWv'.
.*
.if &version ge 110 .do begin
.note vc...
:CMT. .ix 'options' 'vc'
(C++ only)
VC++ compatibility options
:optref refid='SWvc'.
.do end
.*
.note w<number>
:CMT. .ix 'options' 'w'
set warning level number (default is w1)
:optref refid='SWw'.
.*
.if &version ge 107 .do begin
.note wcd=<num>
:CMT. .ix 'options' 'wcd'
warning control: disable warning message <num>
:optref refid='SWwcd'.
.do end
.*
.if &version ge 110 .do begin
.note wce=<num>
:CMT. .ix 'options' 'wce'
warning control: enable warning message <num>
:optref refid='SWwce'.
.do end
.*
.note we
:CMT. .ix 'options' 'we'
treat all warnings as errors
:optref refid='SWwe'.
.*
.note wo
:CMT. .ix 'options' 'wo'
(C only)
&286only.
warn about problems with overlaid code
:optref refid='SWwo'.
.*
.note wx
:CMT. .ix 'options' 'wx'
set warning level to maximum setting
:optref refid='SWwx'.
.*
.note xd
:CMT. .ix 'options' 'xd'
(C++ only) disable exception handling (default)
:optref refid='SWxd'.
.*
.note xdt
:CMT. .ix 'options' 'xdt'
(C++ only) disable exception handling (same as "xd")
:optref refid='SWxdt'.
.*
.note xds
:CMT. .ix 'options' 'xds'
(C++ only) disable exception handling (table-driven destructors)
:optref refid='SWxds'.
.*
.if &version ge 110 .do begin
.note xr
:CMT. .ix 'options' 'xr'
(C++ only) enable RTTI
:optref refid='SWxr'.
.do end
.*
.note xs
:CMT. .ix 'options' 'xs'
(C++ only) enable exception handling
:optref refid='SWxs'.
.*
.note xst
:CMT. .ix 'options' 'xst'
(C++ only) enable exception handling (direct calls for destruction)
:optref refid='SWxst'.
.*
.note xss
:CMT. .ix 'options' 'xss'
(C++ only) enable exception handling (table-driven destructors)
:optref refid='SWxss'.
.*
.note z{a,e}
:CMT. .ix 'options' 'za, ze'
disable/enable language extensions (default is ze)
:optref refid='SWza'.
:optref refid='SWze'.
.*
.note zat
:CMT. .ix 'options' 'zat'
(C++ only) disable alternative tokens
:optref refid='SWzat'.
.*
.note zc
:CMT. .ix 'options' 'zc'
place literal strings in code segment
:optref refid='SWzc'.
.*
.note zd{f,p}&optdag.
:CMT. .ix 'options' 'zdf'
:CMT. .ix 'options' 'zdp'
&x86only.
allow DS register to "float" or "peg" it to DGROUP (default is zdp)
:optref refid='SWzdfp'.
.*
.note zdl&optdag.
:CMT. .ix 'options' 'zdl'
&386only.
load DS register directly from DGROUP
:optref refid='SWzdl'.
.*
.note zev&optdag.
:CMT. .ix 'options' 'zev'
(C only, Unix extension) enable arithmetic on void derived types
:optref refid='SWzev'
.*
.note zf&optdag.
:CMT. .ix 'options' 'zf'
(C++ only) let scope of for loop initialization extend beyond loop
:optref refid='SWzf'
.*
.note zf{f,p}&optdag.
:CMT. .ix 'options' 'zfp'
:CMT. .ix 'options' 'zff'
&x86only.
allow FS register to be used (default for all but flat memory model)
or not be used (default for flat memory model)
:optref refid='SWzffp'.
.*
.note zg
:CMT. .ix 'options' 'zg'
output function declarations to .def (without typedef names)
:optref refid='SWzg'.
.*
.note zg{f,p}&optdag.
:CMT. .ix 'options' 'zgp'
:CMT. .ix 'options' 'zgf'
&x86only.
allow GS register to be used or not used
:optref refid='SWzgfp'.
.*
.note zk0
:CMT. .ix 'options' 'zk0'
double-byte char support for Kanji
:optref refid='SWzk'.
.*
.note zk0u
:CMT. .ix 'options' 'zk0u'
translate Kanji double-byte characters to UNICODE
:optref refid='SWzk0u'.
.*
.note zk1
:CMT. .ix 'options' 'zk1'
double-byte char support for Chinese/Taiwanese
:optref refid='SWzk'.
.*
.note zk2
:CMT. .ix 'options' 'zk2'
double-byte char support for Korean
:optref refid='SWzk'.
.*
.note zkl
:CMT. .ix 'options' 'zkl'
double-byte char support if current code page has lead bytes
:optref refid='SWzk'.
.*
.note zku=<codepage>
:CMT. .ix 'options' 'zku'
load UNICODE translate table for specified code page
:optref refid='SWzku'.
.*
.note zl
:CMT. .ix 'options' 'zl'
suppress generation of library file names and references in object
file
:optref refid='SWzl'.
.*
.note zld
:CMT. .ix 'options' 'zld'
suppress generation of file dependency information in object file
:optref refid='SWzld'.
.*
.note zlf&optdag.
:CMT .ix 'options' 'zlf'
add default library information to object files
:optref refid='SWzlf'
.*
.note zls&optdag.
:CMT .ix 'options' 'zls'
remove automatically inserted symbols (such as runtime library references)
:optref refid='SWzls'
.*
.note zm
:CMT. .ix 'options' 'zm'
place each function in separate segment (near functions not allowed)
:optref refid='SWzm'.
.*
.if &version ge 107 .do begin
.note zmf
:CMT. .ix 'options' 'zmf'
place each function in separate segment (near functions allowed)
:optref refid='SWzmf'.
.do end
.*
:CMT..note zo
:CMT.:CMT. .ix 'options' 'zo'
:CMT.(C++ only) use exception-handling for a specific operating system
:CMT.:optref refid='SWzo'.
.*
.note zp[{1,2,4,8,16}]
:CMT. .ix 'options' 'zp'
set minimal structure packing (member alignment)
:optref refid='SWzp'.
.*
.if '&alpha' eq 'AXP' .do begin
.note zps
:CMT. .ix 'options' 'zps'
&AXPonly.
always align structs on qword boundaries
:optref refid='SWzps'.
.do end
.*
.if &version ge 110 .do begin
.note zpw
:CMT. .ix 'options' 'zpw'
output warning when padding is added in a struct/class
:optref refid='SWzpw'.
.do end
.*
.note zq
:CMT. .ix 'options' 'zq'
operate quietly
:optref refid='SWzq'.
.*
.note zri
:CMT. .ix 'options' 'zri'
inline floating point rounding code
:optref refid='SWzri'.
.*
.note zro
:CMT. .ix 'options' 'zro'
omit floating point rounding code
:optref refid='SWzro'.
.*
.note zs
:CMT. .ix 'options' 'zs'
syntax check only
:optref refid='SWzs'.
.*
.note zt<number>
:CMT. .ix 'options' 'zt'
set data threshold (default is zt32767)
:optref refid='SWzt'.
.*
.note zu&optdag.
:CMT. .ix 'options' 'zu'
&x86only.
do not assume that SS contains segment of DGROUP
:optref refid='SWzu'.
.*
.if &version ge 107 .do begin
.note zv
:CMT. .ix 'options' 'zv'
(C++ only)
enable virtual function removal optimization
:optref refid='SWzv'.
.do end
.*
.note zw&optdag.
:CMT. .ix 'options' 'zw'
&x86only.
Microsoft Windows prologue/epilogue code sequences
:optref refid='SWzw'.
.*
.note zW
:CMT. .ix 'options' 'zW'
&286only.
Microsoft Windows optimized prologue/epilogue code sequences
:optref refid='SWzW86'.
.*
.note zWs
:CMT. .ix 'options' 'zWs'
&286only.
Microsoft Windows smart callback sequences
:optref refid='SWzWs'.
.*
.note zz
:CMT. .ix 'options' 'zz'
&x86only.
remove "@size" from __stdcall function names (10.0 compatible)
:optref refid='SWzz'.
.*
