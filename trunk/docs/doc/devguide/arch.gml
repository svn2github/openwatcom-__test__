.chap Build Architecture

In an effort to clean up the build process, make it easier for projects to
compile on various people's machines and allow for easier ports to other
architectures, every project which is developed under the Open Watcom Project
should follow certain conventions as far as makefile layout is concerned.
This section describes the conventions and requirements for these makefiles,
as well as the steps needed to get projects to compile on a "build" machine.
.np
For those who do not desire a lecture on the preparation and maintenance of
makefiles, feel free to skip straight to the Executive Summary at the end.
.np
Every build machine must have the mif project (
.us bld\build\mif
) installed. That is taken care of by uncompressing the Open Watcom source
archive and/or syncing up with Perforce. For the purposes of this document,
every machine where a project can be built is considered a build machine,
not just the "official" build server.

.section Makeinit
.*
.np
.ix 'makeinit'
All the magic starts with
.us makeinit.
Every build machine must have a
.us makeinit
file with the following defined therein:
.begnote
.note mif_dir:
        must point to the directory in which the mif project has been installed
.note lang_root:
        the location of the installed (Open) Watcom compiler
.endnote

For each project with name X you wish to have on the build machine,
.id X_dir
must be set to the directory containing the project. That is, if you want the
code generator on your machine (and who wouldn't?), it is officially
named cg (see Project Names below) and so you would define
.id cg_dir.
.np
Alternatively, if all of your projects are in directories which correspond
to their project names under a common directory, you can set dev_dir and
.us !include cdirs.mif
in your
.us makeinit.
This is the recommended setup and default for Open Watcom. You do not have
to take any extra action to use it.
.np
Alternatively, you can do the above and then redefine
.id X_dir
for any projects which are not under the
.id dev_dir.

.section Project Names
.*
.np
.ix 'names'

Each project must be given a unique name, which should also be a valid
directory name under FAT file systems (8.3 convention).
.np

.section Makefiles
.*
.np
Each makefile should be located in the object file directory - ie. no more
of this silly cd'ing into the object directory based on crystal-balls and
what not. The makefile must define the following:
.begnote
.note host_CPU:
        architecture which the resulting executable code will run on.
.note host_OS:
        os which the resulting executable code will run on
.note proj_name:
        the project name
.endnote
.np
Valid values for
.id host_CPU
are 386, i86, axp, ppc. These should be self-explanatory.
Valid values for
.id host_OS
are dos, nt, os2, nov, qnx, win, osi. These should be self-explanatory for
the most part, with one possible exception: osi stands for OS Independent,
the executables can run on multiple OSes if appropriate loader stub is
provided.
.np
The makefile must then include
.us cproj.mif.
This will define all sorts of make
variables, which can then be used to build the project. A list of the
most important of these variables and what they can be used for is
included below.
.np
A makefile can also include
.us deftarg.mif,
for definition of the required clean target, and
.us defrule.mif,
which has the default compilation rules. A makefile is free to override
these defaults as long as it follows the following conventions:
.np
.autonote
.note
Tools which have macros defined for them must be referred to by the
macros - these are currently (any additions should be brought to my attention):
.begnote
.note $(CC):
The C compiler
.note $(CPP):
The C++ compiler
.note $(LINKER):
The linker
.note $(LIBRARIAN):
The librarian
.note $(AS):
The assembler, if applicable
.note $(RC):
The resource compiler
.note $(EDIT):
Our VI editor
.note $(YACC):
Our version of yacc
.note $(RE2C):
The regular-expression to C compiler
.endnote
.np
note
After the
.us cproj.mif
is included and before a command is run, the
.id INCLUDE
environment variable must be set to
.id inc_path.
A project is not allowed to set
.id INCLUDE
to something else - it may redefine certain elements of
.id inc_path
 - see Include Paths below. This ensures that include paths can be
easily controlled and tracked.
.np
.note
When referring to other projects, a makefile should use the
.id X_dir
macro, where X is the name of the project.
.endnote


.section Requirements To Build
.*
.np
.ix 'build requirements'
A project should be able to build either a -d2 (if
.id release_$(proj_name)
!= 1)
or releaseable (if
.id release_$(proj_name)
== 1 ) executable providing the following are done:
.begbull
.bull
the project is uptodate and
.id $(proj_name)_dir
is set correctly
.bull
the mif project is uptodate and make knows to look for .mif files in there
.bull
lang_root is set
.bull
all depended upon projects are uptodate and have
.id $(proj_name)_dir
set correctly
.bull
all depended upon projects have been built
.bull
any required executables from
.us bld\build\bin
are in the path
.endbull
.np
Note that there are no other requirements here &mdash it is very annoying when
a project requires you to define handles for tools, create directories in
which it can deposit stuff, scrounge up obscure tools from who knows where
or pretend to be Jim Welch
.* .fn begin
.* One of the original Watcom compiler developers
.* .fn end
in order to get a debuggable version of the executable.
.np
Perhaps it should be noted that "releasable" build still contains debugging
information, but only at the -d1 level and in a separate .sym file. In case
of crashes or other highly unusual behaviour, release build should be enough
to point you in the right direction but usually not sufficient to fully
diagnose and rectify the problem.
.np
Now, if you wish to allow certain abberant behaviours based upon cryptic
make variables, that is fine, as long as the project can build both a
debuggable (ie full -d2) version as well as a release (ie no -d2, -d1 only
and no memory tracker) version without these things being set. That is, if
you want stupid stuff in your
.us makeinit
&mdash fine, but don't require others to do this in order to build the project.
.np
Any non-standard makefile variables which you do use should be prepended
by the name of your project and an underscore, to prevent namespace clutter
and clashes.
.np
Tools required to build are an issue that will have to be handled on a
case-by-case basis. For example, stuff to bind up DOS protected mode apps
will likely be added to the standard suite of tools available, and macros
made for them. Before we do this, we should standardize on one extender and
use it wherever possible. Any small special purpose tools should be checked
in along with the project and built as part of the build process (so that
we don't have to check in zillions of binaries for all supported platforms). An
important future consideration will be the ability to build on a different
architecture. Please try and avoid weirdo tools that have no hope of running
on an Alpha or PPC running NT. More general tools (yacc, re2c, w32bind) that
are likely to be used by several projects should be copied up into the bin
directories under
.us bld\build
&mdash bin for DOS, binp for OS/2 and binnt for some other OS, forget which.
These tools should be referenced from the makefile as
.id $(bld_dir)\tool.
If your tool cannot run under a particular OS, you should at least put
a batchfile in that bin which echoes a message to that effect (to alert
people to the fact that you've just made their life difficult).


.section The Runtime DLL Libraries
.*
.np
.ix 'DLL runtime'
If you set
.id $(proj_name)_rtdll
= 1, the -br switch should be thrown for you automatically, providing the
target os supports it.


.section Memory Trackers
.*
.np
.ix 'memory trackers'
The memory tracker is an useful development aid &mdash it tracks all dynamic
memory allocations and deallocations, making it easy to spot memory leaks and
helping to pinpoint heap corruption or other unsociable behaviour that so
rarely happens in our code.
.np
If the memory tracker is an optional part of your project, and independant
of the release mode, it is suggested that you enable it if
.id $(proj_name)_trmem
is set to 1, and disable it otherwise.
.np
The source to the memory tracker can be found in
.us bld\trmem.


.section The Clean Target
.*
.np
.ix 'clean target'
Each makefile should support a clean target. This should not be part of the
default target list, and should delete every makefile generated file. Which
means that after running "wmake clean", the directory should look exactly
like a new installation of the project on a bare drive. !including
.us deftarg.mif
should do for most people who do not get creative with file extensions or
generated source files.
.np
Do not underestimate the importance of proper cleanup. It guarantees that
every part of a project can be built from scratch, ensuring that there
will be no nasty surprises when stuff breaks for people after a clean
install just because you had a generated file hanging around and never
discovered that it can no longer be made.


.section Pmake Support
.*
.np
.ix 'pmake'
Every makefile should contain a pmake line at the top. Pmake is a tool which
was invented in order to make life easier with the clib project. Pmake, when
run from a root directory, crawls down all subdirectories looking for files
called
.us makefile.
When it finds one, it checks to see if there is a wmake comment which looks
like:
.millust begin
#pmake: <some identifiers>
.millust end
If there is such a comment, and any identifiers in the list given to pmake
appear in the list after the colon, then wmake is invoked in that directory.
This provides a handy way to control selective builds and destroys. Some
tokens which should be used by the appropriate makefiles are:
.begnote $break
.note all
should be in every makefile
.note build
indicates that wmake should be run in this directory as part of the build process
.note os_x
for each x in the list of the valid host_OS tokens
.note cpu_x
for each x in the list of the valid host_CPU tokens
.note target_x
for each x in the list of valid host_CPU tokens (for compilers and targetted apps)
.note tiny, small, compact, medium, large, huge, flat, nomodel
the memory model
.note inline, calls
whether an app uses inline 8087 stuff or fp calls
.endnote
.np
For example, an executable which is going to run on the PPC version of NT
should have a pmake line which contains, at a minimum:
.millust begin
#pmake: all build os_nt cpu_ppc
.millust end
You are free to add as many mnemonic identifiers as you want, of course,
but anything which you feel is an abstract classification that would apply
to other projects, please bring to our collective attention and if deemed
useful, it will get added to the appropriate places (and the list above).
.np
For an example of where this is useful, if we suddenly found out that our
NT headers were bogus and everything including them needed a recompile, we
could do the following on the build machine: "pmake os_nt -h clean & pmake
os_nt -h".
.np
Another very useful property of this setup is that it allows people to
build libraries/binaries only for their host platform. This is especially
convenient if they don't have all the necessary SDKs, Toollkits and
whatnot installed and/or cannot run some or all of the platform specific
tools required during builds. And this situation is the norm rather than
exception &mdash only dedicated build servers usually have all necessary
files in place.


.section Misc Conventions
.*
.np
.ix 'conventions'
To make it easy to see what projects are required to make a given project,
all needed projects should be listed in a makefile comment in the main
makefile of the dependant project. Hopefully, this main makefile should
be called
.us master.mif
and be in the root directory, or a mif subdirectory thereof, of the project.
.np
Also, it is suggested that the object file directory name be a combination
of the
.id host_OS
followed by the
.id host_CPU,
if convenient. For example, NT versions for the PPC should be genned into
a ntppc directory. If a directory structure which is different than this
is used for some reason, then comments explaining exactly what is built
where would be nice in the
.us master.mif
file.
.np
Things get more interesting if cross compilers are thrown into the mix.
In that case three components are required in the name: for instance a
.us nt386.axp
directory can hold the Alpha AXP NT compiler producing 386 code.


.section DLLs and Windowed Apps
.*
.np
.ix 'DLLs'
.ix 'windowed applications'
Set
.id host_OS
and
.id host_CPU
as normal, and then, if creating a windowed app, set
.id sys_windowed
= 1. If creating a DLL, set
.id sys_dll
= 1. Delightfully simple.


.section Include Paths
.*
.np
.ix 'include paths'
The
.id inc_path
macro, which every project should set the include environment variable to
before executing any build commands, is composed of several other variables.
Projects are able to hook any of these variables by redefining them after
.us cproj.mif
is included. The current, and likely to change, structure looks like this:
.millust begin
inc_path = inc_dirs | inc_dirs_$(host_OS) | inc_dirs_sys
inc_dirs_sys = inc_dirs_lang | inc_dirs_sys_$(host_OS)
inc_dirs_lang = $(lang_root)\h
.millust end
So, a project should put any include directories it needs into inc_dirs - this
includes
.id $(watcom_dir)\h
&mdash no project should assume anything will be set except the location of the
(Open) Watcom C compiler header files and the appropriate system header files.
.np
If it needs to, a project can override any and all of these &mdash for instance,
the clib needs to be built with the next release header files, and so would
redefine
.id inc_dirs_lang.
.np
Any OS-specific header files needed by the project can be set in
.id inc_dirs_$(host_OS)
&mdash again, this should not include the standard system
header files, which will be defined in
.id inc_dirs_sys_$(host_OS).


.section Executive Summary
.*
.np
.ix 'summary'
In order to convert a project to this new structure or create a new (and
conforming) project, do the following:
.np
.autonote
.note
Create an object file directory for each combination of host_OS/host_CPU
under your project.
.note
Give your project a name, for instance Foo.
.note
Create a
.us master.mif
in the root of your project.
.note
Put all the normal makefile gear in this
.us master.mif.
.note
Add
.id proj_name
 = Foo to the top of master.mif
.note
Include the following files (in this order)
.us cproj.mif, deftarg.mif, defrule.mif
in
.us master.mif
.note
Add
.id inc_dirs
= {list of directories, separated by semi-colons, which your project needs
in include path - this does not include OS-specific includes (ie
.us \lang\h\win
)}
.note
Add
.id extra_c_flags
= {list of c flags, not including optimization, /w4, /zq. /we and model info,
needed to compile your application} These should be host_OS/host_CPU independant.
.note
Add
.id extra_l_flags
 = {list of linker directives, not incuding system or debug directives}
 Should be host_OS/host_CPU independant.
.note
Use following to compile:
.id $(cc) $(cflags)
filename etc...
.note
Use following to link:
.id $(linker) $(lflags)
file { list of obj files }
.note
Use following to create libraries:
.id $(librarian)
.note
In each object file directory, create a makefile which looks like the following:
.millust begin
#pmake: all build os_X cpu_Y
host_OS=X
host_CPU=Y
!include ..\master.mif
.millust end
.endnote
.np
That's it! The only downside is that sticking to these guidelines will make
everyone's life less exciting.

.chap Build Process

We use the (Open) Watcom C/C++ compilers and Watcom
.us wmake
to build our tools, but at the top level we have a custom tool which oversees
traversing the build tree, deciding which projects to build for what platforms,
logging the results to a file, and copying the finished software into the
release tree (rel2), making fully automated builds a possibility. If nothing
goes wrong that is.

.section Builder
.*
.np
.ix 'builder'
This wondrous tool is called
.us builder.
You can see
.us bld\builder\builder.doc
for detailed info on the tool and/or look at the source if the documentation
doesn't satisfy you.
.np
So how does builder work? Each project has a
.us lang.ctl
builder script file. If you go to a project directory and run builder, it will
make only that project; if you go to
.us bld
and run builder, it will build everything under the sun. The overall build uses
.us bat\lang.ctl
which includes all of the individual project
.us lang.ctl
files that we use. Note that if you run builder, it will traverse directories upwards
until it finds a
.us lang.ctl
(or it hits the root and still doesn't find anything, but then you must have
surely done something wrong). Results are logged to
.us build.log
in the current project directory and the previous
.us build.log
file is copied to
.us build.lo1.
The log file contains captured console output (both stdout and stderr).
.np
Common commands:
.begnote
.note builder build
&mdash build the software
.note builder rel2
&mdash build the software, and copy it into the "rel2" release tree
.note builder clean
&mdash erase object files, executables, etc. so you can build from scratch
.endnote

.section Pmake
.*
.np
.ix 'pmake'
Many of the projects use the "pmake" features of builder (see
.us builder.doc
) or standalone pmake tool. If you want to see its guts, the
.us pmake
source is in
.us bld\pmake.
.np
Each makefile has a comment line at the top of the file which is read by
.us pmake.
Most of our
.us lang.ctl
files will have a line similar to this:
.millust begin
pmake -d build -h ...
.millust end
this will cause
.us wmake
to be run in every subdirectory where the makefile contains
.id "build"
on the
.id #pmake
line. See for instance the C compiler makefiles (in
.us bld\cc)
for an example.
.np
You can also specify more parmeters to build a smaller subset of files. This
is especially useful if you do not have all required tools/headers/libraries
for all target platforms.
.np
For example:
.millust begin
builder rel2 os_nt
.millust end
will (generally) build only the NT version of the tools.
.np
A word of warning: running a full build may take upwards of two hours on
a ~1GHz machine. There is a LOT to build! This is not your ol' OS kernel
or a single-host, single-target C/C++ compiler.
.np
It is generally possible to build specific binaries/libraries by going to
their directory and running
.us wmake.
For instance to build the OS/2 version of
.us wlink
you can go to
.us bld\wl\os2386
and run
.us wmake
there (note that the process won't successfully finish unless several
required libraries had been built). Builder is useful for making full
"release" builds while running
.us wmake
in the right spot is the thing to do during development.
.np
Happy Building!


.chap Testing
.*
.ix 'testing'
There is undoubtedly a question on your mind: Now that I have the Open Watcom
compilers, libraries and tools built, what do I do next? The answer is simpler
than you may have expected: Ensure that what you built actually works.
.np
Fortunately there is a number of more or less automated test available in the
source tree. Currently these tests are not part of the build process per se,
although that might (and perhaps should) change in future.
.np
There are two major classes of situations when the tests should be run:
.begbull
.bull
After building on a fresh system for the first time, running (and passing)
the tests verifies that what was built behaves at least somewhat as expected.
In this case it might be prudent to run as many tests as possible, especially
when building on a new, not yet widely tested platform.
.bull
After making modifications to a particular tool or library, run the
appropriate tests exercising the component (if available) to ensure that the
changes didn't cause any serious regressions.
.endbull
.np
If a bug is discovered and fixed, it is a good practice to code up a simple
test verifying the fix. That way we can prevent (or at least expediently
discover) regressions in future builds. In other words, we won't be embarrassed
by the same bug cropping up again. Just because commercial compiler vendors
occasionally have this problem doesn't mean we have to as well!
.np
Passing the automated tests can never completely guarantee that everything
works perfectly as designed, but it does let you sleep easier at night,
comfortable in the knowledge that there aren't any really major problems.

.section Running the tests
.*
.np
This section maps the major test nests and gives brief description on how
to run the tests and how they're constructed. There is often a single batch
file or script that will build and run all the tests for a given project,
the end result being either "all set to go" or "we have a bug infestation
problem at location xyz, send out bug swat team immediately".
.np
To make automated testing feasible, the test programs do not require user
input (unless they were testing user input of course). Some test programs do
their work and then decide whether everything worked as expected or not and
output a message to that effect. Other test programs ouput messages mapping
their progress as they go and the output is then compared with a file
containing the 'good' output. Which method exactly is used depends mostly
on what is being tested. When testing error and warning messages
printed by the compilers and tools, it is natural to compare the captured
output to the expected text. When testing the runtime library for instance,
it makes sense for the test program itself to decide whether the function
call results are what was expected.
.np
Now we'll go through the projects alphabetically and make a stop whenever
there's something interesting to see. Note that not all of the tests are
automated, the really extensive tests are however. Being a lazy folk,
programmers are likely to bang together an automated test suite if that
helps them avoid babysitting the tests.
.begnote
.note as
In
.us bld\as\alpha\test
there are several tests exercising the Alpha AXP assembler, using C wrappers
for infrastructure.
.note aui
Not a real test, nevertheless the sample programs in
.us bld\aui\sample
are useful in demonstrating and informally testing the user interface library.
.note brinfo
In
.us bld\brinfo\test
there is a simple browser information test program.
.note browser
Tests exercising the class browser are located in
.us bld\browser\test.
.note cg
In
.us cg\test\far16
there is a test exercising the
.id __far16
keyword. Real code generator tests are found elsewhere.
.note clib
The C runtime library tests are located in
.us bld\clib\qa.
These tests are not terribly comprehensive but they do verify the basic C
runtime functionality.
.note gui
Again not a real test, there is a GUI library sample in
.us bld\gui\sample.
.note ndisasm
Tests for the 'new' disassembler (not many at this point) are located in
.us bld\ndisasm\test.
.note orl
The Object Reader Library tests are in
.us bld\orl\test.
.note plustest
This project holds
.us the
test suite. Ostensibly designed to exercise the C++ compiler, the tests also
verify the functionality of the code generator and some are designed for the
C compiler. Running these tests can take a while as there are over a thousand
test cases. Highly recommended.
.note ssl
In
.us bld\ssl\test
there are several simple test scripts for SSL.
.note trmem
While the memory tracker is not a test, it bears mentioning here. This can be
used for testing many other projects for memory leaks, memory overwrites and
other cases of rude behaviour.
.note viprdemo
Again not a test per se, the 'Viper demo' is a good way to verify basic IDE
functionality.
.note wasm
Extensive assembler test can be found (rather predictably) in
.us bld\wasm\test.
.note wdisasm
Tests for the 'old' disassembler are located in
.us bld\wdisasm\test.
.note wmake
Extensive make utility tests can be found in
.us bld\wmake\reg
and
.us bld\wmake\regress.
.note wprof
A profiler test program is located in
.us bld\wprof\test.
.note yacc
Several sample/test YACC input files are in
.us bld\yacc\y.
.endnote

