.func abs
#include <stdlib.h>
int abs( int j );
.funcend
.desc begin
The &func function returns the absolute value of its integer argument
.arg j.
.desc end
.return begin
The &func function returns the absolute value of its argument.
.return end
.see begin
.seelist abs fabs labs
.see end
.exmp begin
#include <stdio.h>
#include <stdlib.h>

void main()
  {
    printf( "%d %d %d\n", abs( -5 ), abs( 0 ), abs( 5 ) );
  }
.exmp output
5 0 5
.exmp end
.class ANSI
.system
