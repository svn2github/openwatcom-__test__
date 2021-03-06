:INCLUDE file='lytchg'.
.if &e'&dohelp eq 0 .do begin
:INCLUDE file='wnohelp'.
.do end
:INCLUDE file='fmtmacro'.
:INCLUDE file='xdefs'.
:set symbol="lang"       value="C/C++".
:INCLUDE file='defs'.
.dc cw 
:INCLUDE file='cppextra'.
.*
.if &e'&dohelp eq 1 .do begin
.dm sepsect begin
.dm sepsect end
.do end
.*
:GDOC.
.if &e'&dohelp eq 0 .do begin
:FRONTM.
:TITLEP.
:TITLE stitle="&cmppname Class Library Reference"
:TITLE.&cmppname Class Library Reference
.if &vol eq 1 .do begin
:TITLE.Volume 1
.do end
.el .if &vol eq 2 .do begin
:TITLE.Volume 2
.do end
:TITLE.3rd Edition
:set symbol="isbn" value="1-55094-073-2"
:AUTHOR.WATCOM International Corporation
:ADDRESS.
:ALINE.Waterloo, Ontario, Canada
:eADDRESS.
:eTITLEP.
:ABSTRACT.
. :INCLUDE file='copyrite'.
. :INCLUDE file='disclaim'.
.if '&target' ne 'QNX' .do begin
. :INCLUDE file='newslett'.
.do end
:PREFACE.
. :INCLUDE file='preface'.
.pa odd
:TOC.
.do end
.*
:BODY.
.if &e'&dohelp eq 1 .do begin
:exhelp
:include file='&book..idx'
:include file='&book..tbl'
:include file='&book..kw'
.do end
.*
.if &e'&dohelp eq 0 .do begin
:SEPSECT.&cmppname Class Library Reference
.do end
.if &vol eq 1 or &e'&vol eq 0 .do begin
:CHAPTER.Header Files
. :INCLUDE file='hdrs'.
:CHAPTER.Common Types
. :INCLUDE file='iotypes'.
:CHAPTER.Predefined Objects
. :INCLUDE file='predef'.
:CHAPTER.istream Input
. :INCLUDE file='istr_in'.
:CHAPTER.ostream Output
. :INCLUDE file='ostr_out'.
:CHAPTER.Library Functions and Types
.se headtext$=Functions and Types
. :INCLUDE file='intro'.
:CHAPTER.Complex Class
.se headtext$=Complex Class
. :INCLUDE file='complex_'.
.do end
.if &vol eq 2 or &e'&vol eq 0 .do begin
:CHAPTER.Container Exception Classes
. :INCLUDE file='wcexcep'
. :INCLUDE file='wcitexc'
:CHAPTER.Container Allocators and Deallocators
. :INCLUDE file='wcalloc'
:CHAPTER.Hash Containers
. :INCLUDE file='wchash'.
:CHAPTER.Hash Iterators
. :INCLUDE file='wchashit'.
:CHAPTER.List Containers
. :INCLUDE file='listcont'
. :INCLUDE file='wcdlink'
. :INCLUDE file='wcisv'
. :INCLUDE file='wcptr'
. :INCLUDE file='wcslink'
. :INCLUDE file='wcval'
:CHAPTER.List Iterators
. :INCLUDE file='listiter'
. :INCLUDE file='wcisvit'
. :INCLUDE file='wcptrit'
. :INCLUDE file='wcvalit'
:CHAPTER.Queue Container
. :INCLUDE file='queue'
:CHAPTER.Skip List Containers
. :INCLUDE file='wcskip'.
:CHAPTER.Stack Container
. :INCLUDE file='stack'
:CHAPTER.Vector Containers
. :INCLUDE file='wcvector'.
.do end
.if &vol eq 1 or &e'&vol eq 0 .do begin
:CHAPTER.Input/Output Classes
.se headtext$=Input/Output Classes
. :INCLUDE file='filebuf_'
. :INCLUDE file='fstream_'
. :INCLUDE file='fstrbse_'
. :INCLUDE file='ifstrm_'
. :INCLUDE file='ios_'
. :INCLUDE file='iostrm_'
. :INCLUDE file='istream_'
. :INCLUDE file='isstrm_'
. :INCLUDE file='manip_'.
. :INCLUDE file='ofstrm_'
. :INCLUDE file='ostream_'
. :INCLUDE file='osstrm_'
. :INCLUDE file='stdiobu_'
. :INCLUDE file='streamb_'
. :INCLUDE file='sstrm_'
. :INCLUDE file='sstrbse_'
. :INCLUDE file='sstrbuf_'
:CHAPTER.String Class
.se headtext$=String Class
. :INCLUDE file='string_'
.do end
.if &e'&dohelp eq 0 .do begin
:BACKM.
.cd set 2
:INDEX.
.do end
:eGDOC.
