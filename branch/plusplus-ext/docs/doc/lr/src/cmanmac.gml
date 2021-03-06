:set symbol="sysrb" value="~b".
:set symbol="XMPset" value="of".
.*
.* Define these here otherwise &_func. expands to &_func. and not ''
.*
.sr _func=''
.sr ffunc=''
.sr wfunc=''
.sr mfunc=''
.sr fmfunc=''
.sr ufunc=''
.*
.dm prelim begin
.dm prelim end
.*
.dm dos begin
.if '&machsys' eq 'DOS' .do begin
.im &*
.do end
.dm dos end
.*
.dm qnx begin
.if '&machsys' eq 'QNX' .do begin
.im &*
.do end
.dm qnx end
.*
.dm debug begin
.* .ty &*
.dm debug end
.*
.dm funkw begin
.se *fnd=&'vecpos(&*,fnclst)
.if &*fnd. eq 0 .me
.if &__sysl(&*fnd.) eq 0 .ty ***WARNING*** &* not in library
.if |&fncttl.| eq || .do begin
.   .sr fncttl=&*
.do end
.el .do begin
.   .sr fncttl=&fncttl., &*
.do end
.se __fnx=&__fnx.+1
.se $$fnc(&__fnx.)=&*
.* try to classify type of function
.if '&*' eq '_&$$fnc(1)' .do begin
.   .sr _func=&*
.do end
.el .if '&*' eq '_f&$$fnc(1)' .do begin
.   .sr ffunc=&*
.do end
.el .if &'pos('_w',&*) eq 1 .do begin
.   .if '&*' ne '_wrapon' .do begin
.   .   .sr wfunc=&*
.   .do end
.do end
.el .if &'pos('wc',&*) eq 1 .do begin
.   .sr wfunc=&*
.do end
.el .if &'pos('wmem',&*) eq 1 .do begin
.   .sr wfunc=&*
.do end
.el .if &'pos('wasc',&*) eq 1 .do begin
.   .sr wfunc=&*
.do end
.el .if &'pos('_mb',&*) eq 1 .do begin
.   .sr mfunc=&*
.do end
.el .if &'pos('_fmb',&*) eq 1 .do begin
.   .sr fmfunc=&*
.do end
.el .if &'pos('_u',&*) eq 1 .do begin
.   .if '&*' ne '_utime' .do begin
.   .   .sr ufunc=&*
.   .do end
.do end
.dm funkw end
.*
.dm funix begin
.ixm &*
.if &e'&dohelp eq 1 .do begin
.   .sr *iw="&'strip('&*','L','_') "
.   .if '&*iw.' ne '&*' .do begin
.   .   .ixm &*iw.
.   .do end
.do end
.dm funix end
.*
.*  .func norm Functions
.*  .func norm
.*  .func norm _norm _wnorm _mbsnorm
.*
.dm func begin
.sr func=&'strip(&*1,'T',',')
.sr _func=''
.sr ffunc=''
.sr wfunc=''
.sr mfunc=''
.sr fmfunc=''
.sr ufunc=''
.if '&*2' eq 'Functions' .do begin
.   .sr fncttl=&*1 &*2
.   .se __fnx=1
.   .se $$fnc(1)=&*1
.do end
.el .do begin
.   .sr fncttl=''
.   .se __fnx=0
.   .se *i=1
.   .pe &*0.
.   .   .funkw &*&*i.;.se *i=&*i.+1
.do end
.topsect &fncttl.
.se *i=1
.pe &__fnx.
.   .funix &$$fnc(&*i.);.se *i=&*i.+1
.cp 5
.newcode Synopsis:
.dm func end
.*
:CMT. .dm func begin
:CMT. .sr funcs=&*
:CMT. .sr func=&'strip(&*1,'T',',')
:CMT. .sr _func=''
:CMT. .sr ffunc=''
:CMT. .sr ufunc=''
:CMT. .if &'wordpos('_',&*,2) ne 0 .do begin
:CMT. .   .sr funcs=&*1
:CMT. .   .sysstr _&func
:CMT. .   .if '&$$str' ne '' .do begin
:CMT. .   .   .sr _func=_&func.
:CMT. .   .do end
:CMT. .do end
:CMT. .if &'wordpos('f',&*,2) ne 0 .do begin
:CMT. .   .sr funcs=&*1
:CMT. .   .if &farfnc eq 1 .do begin
:CMT. .   .   .sysstr _f&func
:CMT. .   .   .if '&$$str' ne '' .do begin
:CMT. .   .   .   .sr ffunc=_f&func.
:CMT. .   .   .do end
:CMT. .   .do end
:CMT. .do end
:CMT. .if &'wordpos('u',&*,2) ne 0 .do begin
:CMT. .   .sr funcs=&*1
:CMT. .   .if &unifnc eq 1 .do begin
:CMT. .   .   .sysstr _u&func
:CMT. .   .   .if '&$$str' ne '' .do begin
:CMT. .   .   .   .sr ufunc=_u&func.
:CMT. .   .   .do end
:CMT. .   .do end
:CMT. .do end
:CMT. .if '&*2' eq 'Functions' .do begin
:CMT. .   .sr funcs=&*1 &*2
:CMT. .do end
:CMT. .el .do begin
:CMT. .   .sr funcs=&func.
:CMT. .   .if '&_func' ne '' .do begin
:CMT. .   .   .sr funcs=&funcs., _&func.
:CMT. .   .do end
:CMT. .   .if '&ffunc' ne '' .do begin
:CMT. .   .   .sr funcs=&funcs., _f&func.
:CMT. .   .do end
:CMT. .   .if '&ufunc' ne '' .do begin
:CMT. .   .   .sr funcs=&funcs., _u&func.
:CMT. .   .do end
:CMT. .do end
:CMT. .topsect &funcs.
:CMT. .ixm &func.
:CMT. .se __fnx=1
:CMT. .se $$fnc(1)=&func.
:CMT. .if '&_func' ne '' .do begin
:CMT. .   .se __fnx=&__fnx.+1
:CMT. .   .se $$fnc(&__fnx.)=_&func.
:CMT. .   .ixm _&func.
:CMT. .do end
:CMT. .if '&ffunc' ne '' .do begin
:CMT. .   .se __fnx=&__fnx.+1
:CMT. .   .se $$fnc(&__fnx.)=_f&func.
:CMT. .   .ixm _f&func.
:CMT. .do end
:CMT. .if '&ufunc' ne '' .do begin
:CMT. .   .se __fnx=&__fnx.+1
:CMT. .   .se $$fnc(&__fnx.)=_u&func.
:CMT. .   .ixm _u&func.
:CMT. .do end
:CMT. .cp 5
:CMT. .newcode Synopsis:
:CMT. .dm func end
.*
.* func2 create an index entry for &* also
.*
.dm func2 begin
:cmt .if &e'&dohelp eq 1 .xmpoff
.funkw &*1
:cmt. .if &e'&dohelp eq 1 .xmpon
.dm func2 end
.*
.* The funcw macro explicitly declares the "wide" name of a function
.*
.dm funcw begin
.if &version ge 107 .do begin
.  .sr wfunc=&*
.do end
.dm funcw end
.*
.dm ixfunc begin
.if &'vecpos(&*1,fnclst) ne 0 .do begin
.ix '&*1'
.do end
.dm ixfunc end
.*
.dm ixfunc2 begin
.if &'vecpos(&*2,fnclst) ne 0 .do begin
.if &e'&dohelp eq 1 .xmpoff
.ix '&*1' '&*2'
.if &e'&dohelp eq 1 .xmpon
.do end
.dm ixfunc2 end
.*
.dm funcend begin
.endcode
.if &'length(&_func.) ne 0 .do begin
.   :set symbol="_func" value=";.sf4 &_func.;.esf ".
.do end
.if &'length(&ffunc.) ne 0 .do begin
.   :set symbol="ffunc" value=";.sf4 &ffunc.;.esf ".
.do end
.if &'length(&wfunc.) ne 0 .do begin
.   :set symbol="wfunc" value=";.sf4 &wfunc.;.esf ".
.do end
.if &'length(&mfunc.) ne 0 .do begin
.   :set symbol="mfunc" value=";.sf4 &mfunc.;.esf ".
.do end
.if &'length(&fmfunc.) ne 0 .do begin
.   :set symbol="fmfunc" value=";.sf4 &fmfunc.;.esf ".
.do end
.if &'length(&ufunc.) ne 0 .do begin
.   :set symbol="ufunc" value=";.sf4 &ufunc.;.esf ".
.do end
.sr function=&func.
:set symbol="func" value=";.sf4 &function.;.esf ".
.dm funcend end
.*
.dm funcbold begin
:set symbol="func" value=";.sf2 &*;.esf "
.dm funcbold end
.*
.dm desc begin
.if '&*' eq 'begin' .newtext Description:
.el .if '&*' eq 'end' .oldtext
.dm desc end
.*
.dm exmp begin
.if '&*' eq 'begin' .do begin
.cp 8
.newcode Example:
.do end
.el .if '&*' eq 'end' .endcode
.el .if '&*' eq 'break' .brkcode
.el .if '&*' eq 'output' .outcode
.dm exmp end
.*
.dm seexmp begin
.newtext Example:
See example provided with
.mono &*..
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
.in &INDlvl
.dm seexmp end
.*
.dm newcode begin
.in 0
.if &e'&dohelp eq 0 .do begin
:DL &NTEphi..:DT.&*:DD.
.do end
.el .do begin
:ZDL &NTEphi..:ZDT.&*:ZDD.
.do end
.xmpon
.sk -1
.sr XMPlin=&sysfnum.
.dm newcode end
.*
.dm endcode begin
.if '&XMPset' eq 'on' .xmpoff
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
.in &INDlvl
.sr XMPlin=0
.dm endcode end
.*
.dm brkcode begin
.sk 1
.dm brkcode end
.*
.dm outcode begin
.sk 1
.if '&XMPset' eq 'on' .xmpoff
produces the following:
.xmpon
.sk 1
.dm outcode end
.*
.dm return begin
.if '&*' eq 'begin' .newtext Returns:
.el .if '&*' eq 'end' .oldtext
.dm return end
.*
.dm error begin
.if '&*' eq 'begin' .do begin
.newtext Errors:
When an error has occurred,
.kw errno
contains a value indicating the type of error that has been detected.
.do end
.el .if '&*' eq 'end' .oldtext
.dm error end
.*
.dm begterm begin
.if '&*1' ne '' .do begin
.begnote $setptnt &*.
.do end
.el .do begin
.begnote $setptnt 15
.do end
.dm begterm end
.*
.dm termhd1 begin
.if &e'&dohelp eq 0 .do begin
:DTHD.&*
.do end
.el .do begin
:cmt. :ZDT.:SF font=2.&*:eSF.
.sr termhd1$='&*'
.do end
.dm termhd1 end
.*
.dm termhd2 begin
.if &e'&dohelp eq 0 .do begin
:DDHD.&*
.do end
.el .do begin
:cmt. :ZDD.:SF font=2.&*:eSF.
:ZDT.:SF font=2.&termhd1$.~b~b~b~b~b&*:eSF.
.do end
.dm termhd2 end
.*
.dm term begin
.if '&*1' eq '.arg' .termhi &*2
.el .if '&*1' eq '.kw' .termhi &*2
.el .if '&*1' eq '.mono' .termhi &*2
.el .termhi &*
.dm term end
.*
.dm termhi begin
.note &*
.ix '&*'
.dm termhi end
.*
.dm endterm begin
.endnote
.dm endterm end
.*
:cmt. .dm beglist begin
:cmt. :XMP.:SF font=0.~b
:cmt. .dm beglist end
:cmt. .*
:cmt. .dm endlist begin
:cmt. :eSF.:eXMP.
:cmt. .dm endlist end
.*
.dm filename begin
.mono &*
.dm filename end
.*
.dm hdrfile begin
.mono <&*>
.dm hdrfile end
.*
.dm proto begin
Prototype in
.mono <&*>.
.br
.dm proto end
.*
.dm id begin
:SF font=4.&*:eSF.
.dm id end
.*
.dm kw begin
.ix '&*'
.ct
:SF font=4.&*:eSF.
.dm kw end
.*
.dm arg begin
:SF font=1.&*:eSF.
.dm arg end
.*
.dm class begin
.in 0
.sr __class=&*1
.if &e'&dohelp eq 0 .do begin
:DL &NTEphi..:DT.Classification::DD.
.do end
.el .do begin
:ZDL &NTEphi..:ZDT.Classification::ZDD.
.do end
:set symbol="*extr" value=0.
.if &'length(&_func.) ne 0 .do begin
.'  :set symbol="_func" value="&'translate("&_func.",' ',';')".
.'  :set symbol="_func" value="&'word("&_func.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &'length(&ffunc.) ne 0 .do begin
.'  :set symbol="ffunc" value="&'translate("&ffunc.",' ',';')".
.'  :set symbol="ffunc" value="&'word("&ffunc.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &'length(&wfunc.) ne 0 .do begin
.'  :set symbol="wfunc" value="&'translate("&wfunc.",' ',';')".
.'  :set symbol="wfunc" value="&'word("&wfunc.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &'length(&mfunc.) ne 0 .do begin
.'  :set symbol="mfunc" value="&'translate("&mfunc.",' ',';')".
.'  :set symbol="mfunc" value="&'word("&mfunc.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &'length(&fmfunc.) ne 0 .do begin
.'  :set symbol="fmfunc" value="&'translate("&fmfunc.",' ',';')".
.'  :set symbol="fmfunc" value="&'word("&fmfunc.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &'length(&ufunc.) ne 0 .do begin
.'  :set symbol="ufunc" value="&'translate("&ufunc.",' ',';')".
.'  :set symbol="ufunc" value="&'word("&ufunc.",2)".
.'  :set symbol="*extr" value=1.
.do end
.if &*extr. eq 0 .do begin
&*
.do end
.el .if |&*| eq |WATCOM| .do begin
&*
.do end
.el .if &'words(|&*|) gt 6 .do begin
&*
.do end
.el .do begin
.   &function. is &*
.   .if &*1 eq ISO OR &*1 eq TR .do begin
.   .   .sr *cls=&'strip(&*,'T',',')
.   .   .if |&*| eq |ISO C90| .do begin
.   .   .   .sr *wcls='ISO C95'
.   .   .do end
.   .   .el .do begin
.   .   .   .sr *wcls=&'strip(&*,'T',',')
.   .   .do end
.   .do end
.   .el .do begin
.   .   .sr *cls=&'strip(&*1,'T',',')
.   .   .sr *wcls=&'strip(&*1,'T',',')
.   .do end
.   .if &'length(&_func.) ne 0 .do begin
.   .   .ct , &_func. is not &*cls
.   .do end
.   .if &'length(&ffunc.) ne 0 .do begin
.   .   .ct , &ffunc. is not &*cls
.   .do end
.   .if &'length(&wfunc.) ne 0 .do begin
.   .   .if "&'substr(&wfunc.,1,1)" eq "_" .do begin
.   .   .   .ct , &wfunc. is not &*cls
.   .   .do end
.   .   .el .do begin
.   .   .   .if '&wfunc.' ne '&funcn.' .do begin
.   .   .   .   .ct , &wfunc. is &*wcls
.   .   .   .do end
.   .   .do end
.   .do end
.   .if &'length(&mfunc.) ne 0 .do begin
.   .   .ct , &mfunc. is not &*cls
.   .do end
.   .if &'length(&fmfunc.) ne 0 .do begin
.   .   .ct , &fmfunc. is not &*cls
.   .do end
.   .if &'length(&ufunc.) ne 0 .do begin
.   .   .ct , &ufunc. is not &*cls
.   .do end
.do end
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
.in &INDlvl
.dm class end
.*
.dm system begin
.if '&machsys' eq 'PP' or '&__class' eq 'WIN386' .me
.if '&machsys' eq 'WIN32' .me
.in 0
.se *stm=0
.se *flg=0
...loopsys
.se *stm=&*stm.+1
.sysstr &$$fnc(&*stm.)
.if '&$$str' ne '' .do begin
.   .if &*flg. eq 0 .do begin
.   .   .se *flg=1
.   .   .if &e'&dohelp eq 0 .do begin
.   .   .   :DL &NTEphi..:DT.Systems::DD.
.   .   .do end
.   .   .el .do begin
.   .   .   :ZDL &NTEphi..:ZDT.Systems::ZDD.
:cmt.   .   .br
.   .   .do end
.   .do end
.   .if &__fnx. gt 1 .do begin
.   .   .mono &$$fnc(&*stm.) - &$$str
.   .   .br
.   .do end
.   .el .do begin
.   .    &$$str
.   .do end
.do end
.if &*stm. lt &__fnx. .go loopsys
.if &*flg. ne 0 .do begin
.   .if &e'&dohelp eq 0 .do begin
.   :eDL.
.   .do end
.   .el .do begin
.   :ZeDL.
.   .do end
.do end
.in &INDlvl
.dm system end
.*
.dm see begin
.se seecnt=0
.if '&*' eq 'begin' .newtext See Also:
.el .if '&*' eq 'end' .oldtext
.dm see end
.*
.dm seelist begin
.se *i=2
.se *j=3
.pe &*0.-1
.   .seekw &*1 &*&*i. &*&*j.;.se *i=&*i.+1;.se *j=&*i.+1
.dm seelist end
.*
.dm seekw begin
.if '&*2' ne '' .do begin
.   .if '&*2' ne 'Functions' .do begin
.   .   .if '&*1' ne '&*2' .do begin
.   .   .   .if &'vecpos(&*2,fnclst) ne 0 .do begin
.   .   .   .   .if &seecnt. ne 0 .ct,
.   .   .   .   .se seecnt=1
.   .   .   .   .if &e'&dohelp eq 0 .do begin
.   .   .   .   .   .mono &*2
.   .   .   .   .do end
.   .   .   .   .el .do begin
:QREF str='&*2'.
.   .   .   .   .do end
.   .   .   .   .if '&*3' eq 'Functions' .do begin
&*3
.   .   .   .   .do end
.   .   .   .do end
.   .   .do end
.   .do end
.do end
.dm seekw end
.*
.dm seeall begin
.newtext See also:
All functions starting with &mn.&*&emn.~...
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
.in &INDlvl
.dm seeall end
.*
.dm blkcode begin
.if '&*' eq 'begin' .do begin
.   .if '&XMPset' eq 'of' .do begin
.   .   .xmpon
.   .   .sk 1 c
.   .do end
.do end
.el .if '&*' eq 'end' .do begin
.   .if '&XMPset' ne 'on' .er ***error*** blkcode misuse
.   .xmpoff
.do end
.dm blkcode end
.*
.dm blktext begin
.if '&*' eq 'begin' .do begin
.   .if '&XMPset' eq 'on' .do begin
.   .   .xmpoff
.   .do end
.   .se BLKlin=&sysfnum.-1
.   .if &BLKlin. eq &XMPlin.   .do begin
.   .   .sk -1
.   .do end
.   .el .do begin
.   .   .sk 1 c
.   .do end
.   .co on
.do end
.el .if '&*' eq 'end' .do begin
.do end
.el .er ***error*** blktext misuse
.dm blktext end
.*
.dm emp begin
.if '&*' eq 'begin' .empon
.el .if '&*' eq 'end' .empoff
.dm emp end
.*
.dm empon begin
:P.:SF font=2.
.dm empon end
.*
.dm empoff begin
:eSF.:P.
.dm empoff end
.*
.dm xmpon begin
:set symbol="XMPset" value="on".:SF font=4.
.co off
.dm xmpon end
.*
.dm xmpoff begin
.co on
:eSF.:set symbol="XMPset" value="of".
.dm xmpoff end
.*
.dm newtext begin
.cp 3
.in 0
.if &e'&dohelp eq 0 .do begin
:DL &NTEphi..:DT.&*:DD.
.do end
.el .do begin
:ZDL &NTEphi..:ZDT.&*:ZDD.
.do end
.dm newtext end
.*
.dm oldtext begin
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
:cmt. .in &INDlvl
.in 0.76i
.dm oldtext end
.*
.dm doscmd begin
DOS
.mono &*
command
.ix 'DOS command' '&*'
.dm doscmd end
.*
.dm qnxcmd begin
QNX
.mono &*
command
.ix 'QNX command' '&*'
.dm qnxcmd end
.*
.*       describe functions for c library  2006-03-16
.*  new version with explicit type and classification
.*  if omitted, default classification is WATCOM
.*   .functinit
.*   .funct     norm              classification
.*   .funct_    _norm                  "
.*   .funct_f   farnorm                "
.*   .funct_m   multibytenorm          "
.*   .funct_fm  farmultibytenorm       "
.*   .funct_w   widenorm               "
.*   .funct_fw  farwidewnorm           "
.*   .funct_u   unicodenorm            "
.*
.*   .functm    doublemathfunc         "
.*   .functm_f  floatmathfunc          "
.*   .functm_l  longdoublemathfunc     "
.*
.*   .functgen
.*
.*   .functend
.*   .classt
.*
.*  .functinit
.*      init set symbols must be first call of functxxx macros
.*
.dm functinit begin
.sr function=''
.sr func=''
.sr _func=''
.sr ffunc=''
.sr fwfunc=''
.sr wfunc=''
.sr mfunc=''
.sr fmfunc=''
.sr ufunc=''
.*
.sr mathfunc=''
.sr fmathfunc=''
.sr lmathfunc=''
.*
.sr fncttl=''
.se __fnx=0
.se __cltxt=''
.dm functinit end
.*
.*
.*  functii internal macro for funct_xxx
.*
.dm functii begin
.se *fnd=&'vecpos(&*1,fnclst)
.if &*fnd. eq 0 .me
.if &__sysl(&*fnd.) eq 0 .ty ***WARNING*** &* not in library
.if |&fncttl.| eq || .do begin
.   .sr fncttl=&*1
.do end
.el .do begin
.   .sr fncttl=&fncttl., &*1
.do end
.se __fnx=&__fnx.+1
.se $$fnc(&__fnx.)=&*1
.if /&*2./ eq // .se __cl=WATCOM
.el .se __cl=&*2. &*3.
.if &__fnx. eq 1 .se __cltxt=&*1 is &__cl.
.el .se __cltxt=&__cltxt., &*1 is &__cl.
.dm functii end
.*
.*  macros for the different function types
.*
.dm funct  begin
.sr func=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct  end
.*
.dm funct_  begin
.sr _func=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_  end
.*
.dm funct_f begin
.sr ffunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_f end
.*
.dm funct_m begin
.sr mfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_m end
.*
.dm funct_w begin
.sr wfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_w end
.*
.dm funct_fm begin
.sr fmfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_fm end
.*
.dm funct_fw begin
.sr fwfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_fw end
.*
.dm funct_u begin
.sr ufunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm funct_u end
.*
.dm functm begin
.sr mathfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm functm end
.*
.dm functm_f begin
.sr fmathfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm functm_f end
.*
.dm functm_l begin
.sr lmathfunc=&*1
.if '&function' eq '' .sr function=&*1.
.functii &*
.dm functm_l end
.*
.*  .functgen
.*     generate title and start of code (declaration)
.*
.dm functgen begin
.sr funcn=&function.
.topsect &fncttl.
.cp 5
.newcode Synopsis:
.dm functgen end
.*
.*
.*  final processing for functions
.*
.dm functend begin
.endcode
.se *i=1
.pe &__fnx.
.   .funix &$$fnc(&*i.);.se *i=&*i.+1
.if &'length(&_func.) ne 0 .do begin
.   :set symbol="_func" value=";.sf4 &_func.;.esf ".
.do end
.if &'length(&ffunc.) ne 0 .do begin
.   :set symbol="ffunc" value=";.sf4 &ffunc.;.esf ".
.do end
.if &'length(&wfunc.) ne 0 .do begin
.   :set symbol="wfunc" value=";.sf4 &wfunc.;.esf ".
.do end
.if &'length(&fwfunc.) ne 0 .do begin
.   :set symbol="fwfunc" value=";.sf4 &fwfunc.;.esf ".
.do end
.if &'length(&mfunc.) ne 0 .do begin
.   :set symbol="mfunc" value=";.sf4 &mfunc.;.esf ".
.do end
.if &'length(&fmfunc.) ne 0 .do begin
.   :set symbol="fmfunc" value=";.sf4 &fmfunc.;.esf ".
.do end
.if &'length(&ufunc.) ne 0 .do begin
.   :set symbol="ufunc" value=";.sf4 &ufunc.;.esf ".
.do end
.if &'length(&mathfunc.) ne 0 .do begin
.   :set symbol="mathfunc" value=";.sf4 &mathfunc.;.esf ".
.do end
.if &'length(&fmathfunc.) ne 0 .do begin
.   :set symbol="fmathfunc" value=";.sf4 &fmathfunc.;.esf ".
.do end
.if &'length(&lmathfunc.) ne 0 .do begin
.   :set symbol="lmathfunc" value=";.sf4 &lmathfunc.;.esf ".
.do end
:set symbol="func" value=";.sf4 &function.;.esf ".
.dm functend end
.*
.*  classt
.*    output classifications for the defined functions
.*
.dm classt begin
.in 0
.sr __class=&*1
.if &e'&dohelp eq 0 .do begin
:DL &NTEphi..:DT.Classification::DD.
.do end
.el .do begin
:ZDL &NTEphi..:ZDT.Classification::ZDD.
.do end
:set symbol="*extr" value=0.
&__cltxt.
.if &e'&dohelp eq 0 .do begin
:eDL.
.do end
.el .do begin
:ZeDL.
.do end
.in &INDlvl
.dm classt end
.*
:cmt. include 'Safer C Library' related macros
:INCLUDE file='safecmac'.
