.func memicmp _memicmp _fmemicmp _umemicmp
#include <string.h>
int memicmp( const void *s1,
             const void *s2,
             size_t length );
.ixfunc2 '&Compare' &func
.if &'length(&_func.) ne 0 .do begin
int _memicmp( const void *s1,
              const void *s2,
              size_t length );
.ixfunc2 '&Compare' &_func
.do end
.if &farfnc eq 1 .do begin
int _fmemicmp( const void __far *s1,
               const void __far *s2,
               size_t length );
.ixfunc2 '&Compare' &ffunc
.do end
:cmt. .if &'length(&ufunc.) ne 0 .do begin
:cmt. int _umemicmp( const void *s1,
:cmt.                const void *s2,
:cmt.                size_t length );
:cmt. .ixfunc2 '&Compare' &ufunc
:cmt. .do end
.funcend
.desc begin
The &func function compares, with case insensitivity (upper- and
lowercase characters are equivalent), the first
.arg length
characters of the object pointed to by
.arg s1
to the object pointed to by
.arg s2.
.im farparm
.if &'length(&_func.) ne 0 .do begin
.np
The &_func function is identical to &func..
Use &_func for ANSI/ISO naming conventions.
.do end
:cmt. .if &'length(&ufunc.) ne 0 .do begin
:cmt. .np
:cmt. The &ufunc Unicode function is identical to &func except that it
:cmt. operates on 16-bit Unicode character strings.
:cmt. The argument
:cmt. .arg length
:cmt. is interpreted to mean the number of Unicode characters.
:cmt. .do end
.desc end
.return begin
The &func function returns an integer less than, equal to, or greater
than zero, indicating that the object pointed to by
.arg s1
is less than, equal to, or greater than the object pointed to by
.arg s2.
.return end
.see begin
.seelist &function. memchr memcmp memcpy memicmp memset
.see end
.exmp begin
#include <stdio.h>
#include <string.h>

void main()
  {
    char buffer[80];
.exmp break
    if( memicmp( buffer, "Hello", 5 ) < 0 ) {
      printf( "Less than\n" );
    }
  }
.exmp end
.class WATCOM
.if &'length(&_func.) ne 0 .do begin
.np
&_func conforms to ANSI/ISO naming conventions
.do end
.system
