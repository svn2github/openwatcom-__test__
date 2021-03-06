.func main wmain WinMain wWinMain _getargv _wgetargv
.funcw wmain
int main( void );
int main( int argc, const char *argv[] );
.if '&machsys' eq 'QNX' .do begin
int main( int argc, const char *argv[], char *envp[] );
.do end
.ixfunc2 '&Process' &func
.if &'length(&wfunc.) ne 0 .do begin
int wmain( void );
int wmain( int argc, wchar_t *argv[] );
.do end
.if '&machsys' ne 'QNX' .do begin
int PASCAL WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszCmdLine,
                    int nCmdShow );
int PASCAL wWinMain( HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     wcharT *lpszCmdLine,
                     int nCmdShow );
void *_getargv( int historical, char *exe, char *cmd,
                  int *pargc, char ***pargv );
void *_wgetargv( int historical, wchar_t *exe, wchar_t *cmd,
                   int *pargc, wchar_t ***pargv );
.do end
.funcend
.desc begin
&func is a user-supplied function where program execution begins.
.ix 'main program'
The command line to the program is broken into a sequence of tokens
separated by blanks and are passed to &func as an array of pointers
to character strings in the parameter
.arg argv.
The number of arguments found is passed in the parameter
.arg argc.
The first element of
.arg argv
will be a pointer to a character string containing the program name.
The last element of the array pointed to by
.arg argv
will be a NULL pointer (i.e.
.arg argv[argc]
will be
.mono NULL
.ct ).
Arguments that contain blanks can be passed to &func by enclosing them
within double quote characters (which are removed from that element in
the
.arg argv
vector.
A literal double quote character can be passed by preceding it with a
backslash.
A literal backslash followed by an enclosing double quote character can
be passed as a pair of backslash characters and a double quote character.
.exmp begin
echo "he\"l\lo world\\"
.exmp end
passes the single argument
.arg he"l\lo world\
.np
The command line arguments can also be obtained in its original
format by using the
.kw getcmd
function.
.if '&machsys' eq 'QNX' .do begin
.np
The
.arg envp
argument points at an array of pointers to character strings which are
the environment strings for the current process.
This value is identical to the
.kw environ
variable which is defined in the
.hdrfile stdlib.h
header file.
.do end
.np
Alternatively, the &func function can be declared to return
.kw void
(i.e., no return value).
In this case, you will not be able to return an exit code from &func
using a
.kw return
statement but must use the
.kw exit
function to do so.
.if &'length(&wfunc.) ne 0 .do begin
.np
The &wfunc function is a user-defined wide-character version of &func
that operates with wide-character strings.
If this function is present in the application, then it will be called
by the run-time system startup code (and the &func function, if
present, will not be called).
.np
As with &func, the &wfunc function can be declared to return
.kw void
and the same considerations will apply.
.do end
.********************************
.if '&machsys' ne 'QNX' .do begin
.np
The
.kw WinMain
function is called by the system as the initial entry point for a
Windows-based application.
The
.kw wWinMain
function is a wide-character version of
.kw WinMain.
.begterm 10
.termhd1 Parameters
.termhd2 Meaning
.term hInstance
Identifies the current instance of the application.
.term hPrevInstance
Identifies the previous instance of the application. For an
application written for Win32, this parameter is always NULL.
.term lpszCmdLine
Points to a null-terminated string specifying the command line for the
application.
.term nCmdShow
Specifies how the window is to be shown. This parameter can be one of
the following values:
.begterm 12
.termhd1 Value
.termhd2 Meaning
.term SW_HIDE
Hides the window and activates another window.
.term SW_MINIMIZE
Minimizes the specified window and activates the top-level window in
the system's list.
.term SW_RESTORE
Activates and displays a window.
If the window is minimized or maximized, Windows restores it to its
original size and position (same as
.kw SW_SHOWNORMAL
.ct ).
.term SW_SHOW
Activates a window and displays it in its current size and position.
.term SW_SHOWMAXIMIZED
Activates a window and displays it as a maximized window.
.term SW_SHOWMINIMIZED
Activates a window and displays it as an icon.
.term SW_SHOWMINNOACTIVE
Displays a window as an icon.
The active window remains active.
.term SW_SHOWNA
Displays a window in its current state.
The active window remains active.
.term SW_SHOWNOACTIVATE
Displays a window in its most recent size and position.
The active window remains active.
.term SW_SHOWNORMAL
Activates and displays a window.
If the window is minimized or maximized, Windows restores it to its
original size and position (same as
.kw SW_RESTORE
.ct ).
.endterm
.endterm
.np
The
.kw WinMain
function initializes an application, and then performs a message
retrieval-and-dispatch loop that is the top-level control structure for
the remainder of the application's execution.
The loop terminates when a
.kw WM_QUIT
message is received.
At that point,
.kw WinMain
exits the application, returning the value passed in the
.kw WM_QUIT
message's
.kw wParam
parameter.
If
.kw WM_QUIT
was received as a result of calling
.kw PostQuitMessage,
the value of
.kw wParam
is the value of the
.kw PostQuitMessage
function's
.kw nExitCode
parameter.
.do end
.********************************
.np
The
.kw _getargv
function analyses a "command line" into a sequence of tokens
separated by blanks and passed to the caller as an array of pointers
to character strings.
.kw _wgetargv
is the wide character version of
.kw _getargv.
Each has the following parameters:
.arg historical
selects between historical and modern methods of handling double quote
characters in command lines and should be passed with a value of zero;
.arg exe
is the name of the "executable";
.arg cmd
is the "command line" to be analysed after removal of the name of the "executable";
.arg pargc
is set on output to the number of arguments found;
.arg pargv
is set on output to point at an array of arguments.
.********************************
.desc end
.return begin
The
.if &'length(&wfunc.) eq 0 .do begin
&func function returns
.do end
.el .do begin
&func and &wfunc functions return
.do end
an exit code to the calling program (usually the operating
system).
.if '&machsys' ne 'QNX' .do begin
.np
If the
.kw WinMain
function terminates before entering the message loop, it should
return 0.
Otherwise, it should terminate when it receives a
.kw WM_QUIT
message and return the exit value contained in that message's
.kw wParam
parameter.
.do end
.np
The
.kw _getargv
and
.kw _wgetargv
functions return a pointer to memory allocated by those functions or
.kw NULL
on an allocation failure. That memory may be passed to
.kw free
when access to the output argument array is no longer needed.
.return end
.see begin
.im seeproc main
.see end
.exmp begin
.blkcode begin
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int i;
    for( i = 0; i < argc; ++i ) {
        printf( "argv[%d] = %s\n", i, argv[i] );
    }
    return( 0 );
}
.if &'length(&wfunc.) ne 0 .do begin
#ifdef _WIDE_
int wmain( int wargc, wchar_t *wargv[] )
{
    int i;
    for( i = 0; i < wargc; ++i ) {
        wprintf( L"wargv[%d] = %s\n", i, wargv[i] );
    }
    return( 0 );
}
#endif
.do end
.exmp output
.if '&machsys' eq 'PP' .do begin
argv[0] = mypgm
.do end
.el .if '&machsys' eq 'QNX' .do begin
argv[0] = mypgm
.do end
.el .do begin
argv[0] = C:\WATCOM\DEMO\MYPGM.EXE
.do end
argv[1] = hhhhh
argv[2] = another arg
.blkcode end
.blktext begin
when the program
.mono mypgm
is executed with the command
.blktext end
.blkcode begin
mypgm hhhhh  "another arg"
.blkcode end
.if '&machsys' ne 'QNX' .do begin
.blktext begin
A sample Windows main program is shown below.
.blktext end
.blkcode begin
int PASCAL WinMain( HANDLE this_inst, HANDLE prev_inst,
                    LPSTR cmdline, int cmdshow )
{
    MSG         msg;

    if( !prev_inst ) {
        if( !FirstInstance( this_inst ) ) return( 0 );
    }
    if( !AnyInstance( this_inst, cmdshow ) ) return( 0 );
    /*
      GetMessage returns FALSE when WM_QUIT is received
    */
    while( GetMessage( &msg, NULL, NULL, NULL ) ) {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    return( msg.wParam );
}
.blkcode end
.do end
.blktext begin
A sample usage of _getargv follows:
.blktext end
.blkcode begin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *_getargv( int historical, char *exe, char *cmd,
                  int *pargc, char ***pargv );

void extraparams( const char *envname )
{
    char const * const evaluero = getenv( envname );
    if( evaluero ) {
        char * const cmd = strdup( evaluero );
        char exe[] = "dummy";
        int c;
        char **v;
        void * const opaque = _getargv( 0, exe, cmd,
                                          &c, &v );
        if( opaque ) {
            int i;
            for( i = 0; i < c; ++i ) {
                printf( "argv[%d] = %s\n", i, v[i] );
            }
            free( opaque );
        }
    }
}

void main( int argc, char **argv )
{
    if( argc >= 2 ) {
        extraparams( argv[1] );
    }
}
.exmp output
argv[0] = dummy
argv[1] = a
argv[2] = b
.blkcode end
.blktext begin
when
.mono mypgm
is executed with the command
.blktext end
.blkcode begin
mypgm name
.blkcode end
.blktext begin
is run while the environment variable
.arg name
has the value
.arg a b
.blktext end
.exmp end
.sr wfunc=''
.sr ffunc='x wmain'
.sr mfunc='x WinMain'
.sr fmfunc='x wWinMain'
.sr ffunc='x _getargv'
.sr ffunc='x _wgetargv'
.class ANSI
.system
