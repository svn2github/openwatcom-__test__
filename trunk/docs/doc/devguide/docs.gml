.chap Producing Documentation

The purpose of this document is twofold: to provide an overview of the
Open Watcom documentation system togehter with the steps necessary for
editing and producing online or printed documents, and at the same time
serve as an example of the documentation system usage.
.np
It is useful to note that the online documentation is almost, but not quite,
independent of the rest of the Open Watcom compilers and tools. One
important exception is online help files for Open Watcom GUI tools. Formatting
online documentation generates include files containing #defines
designating help entries. These are used during building of the tools
binaries. If the binaries are not built with the right header files, the
online help will be out of sync and not all that helpful.
.np
There's one other link going in the other direction: certain documentation
files live with their respective projects and not in the documents tree.
This is especially true for error message documentation for the compilers
and tools.


.section Setting up
.*
.np
.ix 'setting up'
.ix 'installation'
A Win32 or OS/2 system can be used to produce most of the documentation.
OS/2 Warp is required for the final step in producing the OS/2 online help
files and Win32 system is needed for producing Windows help files (unless
you can run the required help compilers on your host platform). DOS may
work but is untested at this time.
.np
The environment variable
.id doc_root
must point to the root of the doc
tree (the place where cmds, doc, gml, and Hlp directories are located).
If you're wondering where the Hlp directory is, run
.id mkall.bat/mkall.cmd
located in the bat directory. But first you'll need to do something like
.millust begin
 set doc_root=d:\OpenWatcom\docs
.millust end
.np
Add
.id %doc_root%\cmds
to your
.id PATH.
Your
.id PATH
must also contain the Open Watcom C/C++
binary directories appropriate for your host platform (for wmake). This is
taken care of automatically by using
.id setvars.cmd/setvars.bat.
.np
Note that to produce Windows and/or OS/2 online documentation, you will need
the appropriate SDKs and Toolkits containing the platform specific online
help compilers.


.section Building PostScript Documentation
.*
.ix 'PostScript'
.np
Here are the steps to formatting a book for printing on a PostScript
printer.
.millust begin
cd %doc_root%\doc
fmt <bn> pass 2
.millust end
.np
where
.id <bn>
is one of
.millust begin
devguide    Developer's Guide (this document)
c_readme    C/C++ Read Me First
cguide      C/C++ User's Guide
cguideq     C/C++ User's Guide for QNX
clib_dos    C Library Reference (for all systems except QNX)
clib_fox    C Library Reference for FoxPro (obsolete)
clib_nec    C Library Reference Kanji Functions subset
clib_nt     C Library Reference for Win32 (Power++)
clib_pp     C Library Reference for PenPoint (obsolete)
clib_qnx    C Library Reference for QNX (stale)
clib_tst    C Library Reference (for testing a subset of doc)
clslib      C++ Class Library Reference (obsolete)
cpplib      C++ Class Library Reference (current)
ctools      C/C++ Tools User's Guide
f77graph    F77 Graphics Library Reference
f_readme    F77 Read Me First
fpguide     F77 Programmer's Guide
ftools      F77 Tools User's Guide
fuguide     F77 User's Guide
guitool     Graphical Tools User's Guide
lguide      Linker User's Guide
pguide      C/C++ Programmer's Guide
rcerrs      Resource Compiler Diagnostic Messages (obsolete)
wasaxp      AXP Assembler User's Guide (obsolete)
wdbg        Debugger User's Guide
wlinkerr    Linker Error Messages (obsolete)
.millust end
.np
Two passes (i.e.,
.id pass 2
) should be enough to format most books so that
the table of contents is placed at the front and cross-references are
resolved.  If a message appears that says more passes are required to
resolve things then specify
.id pass 3.
.np
The output file is of type
.id .ps.
You should be able to send this file to any PostScript printer or view
it in GhostScript or convert it to PDF or do whatever it is you do with
PostScript files.


.section Building Online Help Documentation
.*
.np
For Microsoft Help format (both old and new help formats):
.begbull
.bull
Switch to the appropriate directory:
.millust begin
cd %doc_root%\doc\hlp\win
.millust end
.bull
Run
.id mkall.bat
to create all online help.
.np
Look at
.id mk.bat
for a hint on how to do one document at a time. Or read on
if you're lazy.
.np
The Win16 format help files (*.hlp) are copied to the
.id %doc_root%\Hlp\win
directory. The Win32 format help files (*.hlp, *.cnt) are copied to the
.id %doc_root%\Hlp\win95
directory.
.endbull
.np
For Watcom Help format (for Watcom WHELP command):
.begbull
.bull
Switch to the appropriate directory:
.millust begin
cd %doc_root%\doc\hlp\ib
.millust end
.bull
Run
.id mkall.bat
to create all online help.
.np
Look at
.id mk.bat
for a hint on how to do one document at a time.
Or read on if you're lazy.
.np
The WHELP format help files (*.ihp) are copied to the
.id %doc_root%\Hlp\ib
directory.
.endbull
.np
For OS/2 Help format:
.begbull
.bull
Switch to the appropriate directory:
.millust begin
cd %doc_root%\doc\hlp\os2
.millust end
.bull
Run
.id mkall.bat
to create all the IPF files for the OS/2 IPF compiler.
.np
Look at
.id mk.bat
for a hint on how to do one document at a time. Or read on
if you're lazy.
.bull
Transfer the IPF files, bitmap files, etc. to an OS/2 system.
.np
Look at
.id cpos2.bat
for an example of what needs to be copied and what
directories are set up.
.endbull
.np
Under OS/2:
.begbull
.bull
Define the
.id doc_root
environment variable.
.bull
Run
.id doit.cmd
under OS/2 to produce the INF and HLP files.
.np
Look at
.id doit.cmd
for a hint on how to do one document at a time.
Or read on if you're lazy.
.np
The OS/2 format help files (*.INF, *.HLP) should be moved to the
.id %doc_root%\Hlp\os2
directory on the Win32 platform.
.endbull
.np
To format one document at a time, go to the appropriate directory
(for instance
.id docs\doc\hlp\os2
) and run wmake with argument
.id hbook=<book_name>
where
.id <book_name>
is one of the online books listed above.


.section Editing the Documentation
.*
.np
All the documentation is stored in ASCII text files with the file
extension "GML". The files are annotated with a combination of Script
and GML (Generalized Markup Language) tags.
.np
The Script tags are of the form ".tag" (i.e., they begin with a period
and are followed by two or more letters or digits). Script tags will
be most familiar to anyone who has ever used Waterloo Script or IBM
Script. The tagged format is also similar in idea to other tagged
formatting systems like RUNOFF or ROFF.
.np
The GML tags are of the form ":TAG." (i.e., they begin with a colon,
followed by some letters and digits and end with a period). GML tags
will be most familiar to anyone who has ever used IBM GML or Waterloo
GML. This tag set is a variant of SGML. The most familiar SGML tag
format is
.id <TAG>.
In Watcom GML, the "<" and ">" are replaced by the
":" and ".". If you know HTML, you know how tags work &mdash HTML is
just another variant of SGML.
.np
The tag set includes a base set of predefined tags. In addition to
this base set, you can define an extended tag set using the built-in
macro language. The base Script tag set employs two letters (e.g.,
.dm, .if, .se, .cp, .us). The user-defined (extended set) can employ
two, three, four or more letters (e.g. .chapter, .section, .beglevel).
For a good example of user-defined Script tags, see
.id %doc_root%\doc\gml\fmtmacro.gml.
GML tags can also be defined. For a
good example of user-defined GML tags, see
.id %doc_root%\doc\gml\cppextra.gml.
.np
These tags are described here for you, not so that you can begin defining
your own tags, but so that you will recognize them in the ASCII text
that comprises the documentation. But of course no-one's stopping you
from defining your own tags should you feel so inclined.
.np
Here's a snippet from one of the doc files.
.millust begin
    .np
    The recommended options for generating the fastest 16-bit Intel code
    are:
    .ix 'fastest 16-bit code'
    .begnote
    .note Pentium Pro
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.6 &sw.fpi87 &sw.fp6
    .note Pentium
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.5 &sw.fpi87 &sw.fp5
    .note 486
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.4 &sw.fpi87 &sw.fp3
    .note 386
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.3 &sw.fpi87 &sw.fp3
    .note 286
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.2 &sw.fpi87 &sw.fp2
    .note 186
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.1 &sw.fpi87
    .note 8086
    &sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.0 &sw.fpi87
    .endnote
    .np
    The recommended options for generating the fastest 32-bit Intel code
    are:
.millust end
.np
The ".np" is a user-defined tag for "start a new paragraph". The ".ix"
creates an index entry in the index. It doesn't appear with the text.
In on-line help, this index entry becomes a searchable item. The
".begnote", ".note", and ".endnote" user-defined tags are used to
create an unordered list. Every piece of text entered into the source
file is identified by tags like these.
.np
The best way to understand what the tags do is to look at a printed
copy of the document and see what it looks like. Luckily for you,
you don't have to look very far:
.np
The recommended options for generating the fastest 16-bit Intel code
are:
.ix 'fastest 16-bit code'
.begnote
.note Pentium Pro
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.6 &sw.fpi87 &sw.fp6
.note Pentium
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.5 &sw.fpi87 &sw.fp5
.note 486
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.4 &sw.fpi87 &sw.fp3
.note 386
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.3 &sw.fpi87 &sw.fp3
.note 286
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.2 &sw.fpi87 &sw.fp2
.note 186
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.1 &sw.fpi87
.note 8086
&sw.oneatx &sw.oh &sw.oi+ &sw.ei &sw.zp8 &sw.0 &sw.fpi87
.endnote
.np
The recommended options for generating the fastest 32-bit Intel code
are:
.np
The WATCOM GML program (WGML) is a compiler/interpreter that reads the
document's source files to produce an output file. In our case, we
want PostScript for printing and we want another form for generation
of online help. This second form is a non-printable form that is
suitable for post-processing to turn it into IPF for the OS/2 IPF
compiler, RTF for the WinHelp tools, special Watcom-defined format
for use with a DOS-based help tool (WHELP) or the ever-popular HTML.
.np
If you are a programmer, and that is likely, you'll be somewhat comfortable
with the whole process of turning ASCII text into documentation. WGML is
a text processor (compiler) that reads a source file (GML) which, in turn,
imbeds other source files, and produces an output file (the object
file). WGML is very fast. It was very fast in the old 20MHz 386 days
and is, of course, much faster with today's processors. The C Library
Reference comprising 1,241 pages takes one minute to format into
PostScript on a 600 MHz Pentium-III.
.np
If you ever used TeX or LaTeX you will be comfortable with the
concept of nonvisual content-driven formatting. If you only know
so-called WYSIWYG word processors heavily relying on visual
formatting, you might be surprised to find that it is possible to
let the computer do lot of the hard work. Just give up the idea
of controlling every pixel &mdash it never works right anyway. Instead
of saying "this is Arial 10pt Bold" you will say "this is a keyword"
or "this is a code example" and let the machine worry about
formatting.

.section Diagnostic Messages
.*
.np
If you see
.id ***WARNING***
messages issued by WGML, you can ignore them. Of course it is better
if you don't and correct whatever is causing the warnings.
If you see
.id ***ERROR***
messages, you cannot ignore them and have to fix them before any
output is produced.

.* Get text in a neat frame
.*.remark
.*Kevin Goodman describes "unwinds" in his article.
.*.eremark
