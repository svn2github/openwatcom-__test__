.func vfscanf_s vfwscanf_s _uvfscanf_s
.funcw vfwscanf_s
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdarg.h>
#include <stdio.h>
int vfscanf_s( FILE * restrict stream,
         const char * restrict format, va_list arg );
.ixfunc2 '&StrIo' &func
.if &'length(&wfunc.) ne 0 .do begin
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
int vfwscanf_s( FILE * restrict stream, 
       const wchar_t * restrict format, va_list arg );
.ixfunc2 '&StrIo' &wfunc
.ixfunc2 '&Wide' &wfunc
.do end
.if &'length(&ufunc.) ne 0 .do begin
int _uvfscanf_s( FILE * restrict stream, 
        const wchar_t * restrict format, va_list arg );
.ixfunc2 '&StrIo' &ufunc
.do end
.funcend
.*
.rtconst begin
Neither
.arg stream
nor
.arg format
shall be a null pointer.
Any argument indirected through in order to store converted input shall
not be a null pointer.
.np
If there is a runtime-constraint violation, the &func function does not
attempt to perform further input, and it is unspecified to what extent
&func performed input before discovering the runtime-constraint violation.
.rtconst end
.*
.desc begin
The &func function is equivalent to
.kw fscanf_s,
with the variable argument list replaced by
.arg arg,
which shall have been initialized by the
.kw va_start
macro (and possibly subsequent
.kw va_arg
calls). The &func function does not invoke the
.kw va_end
macro.
.if &'length(&wfunc.) ne 0 .do begin
.np
The &wfunc function is identical to &func except that it accepts a
wide-character string argument for
.arg format.
.do end
.if &'length(&ufunc.) ne 0 .do begin
.np
The &ufunc Unicode function is identical to &func except that it
accepts a Unicode string argument for
.arg format
and the input consists of 16-bit Unicode characters.
.do end
.desc end
.*
.return begin
The &func function returns
.kw EOF
if an input failure occurred before any conversion or if there was
a runtime-constraint violation.
Otherwise, the &func function returns the number of input items
successfully assigned, which can be fewer than provided for, or even zero.
.np
When a file input error occurs, the
.kw errno
global variable may be set.
.return end
.*
.see begin
.im seevscnf vfscanf_s
.see end
.*
.exmp begin
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdarg.h>
.exmp break
void ffind( FILE *fp, char *format, ... )
{
    va_list arglist;

    va_start( arglist, format );
    vfscanf_s( fp, format, arglist );
    va_end( arglist );
}
.exmp break
void main( void )
{
    int day, year;
    char weekday[10], month[10];
.exmp break
    ffind( stdin,
            "%s %s %d %d",
            weekday, sizeof( weekday ),
	    month, sizeof( month ),
	    &day, &year );
    printf_s( "\n%s, %s %d, %d\n",
              weekday, month, day, year );
}
.exmp end
.*
.class TR 24731
.system
