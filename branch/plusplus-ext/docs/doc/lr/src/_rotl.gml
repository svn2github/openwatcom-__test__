.func _rotl
#include <stdlib.h>
unsigned int _rotl( unsigned int value,
                    unsigned int shift );
.ixfunc2 '&Rotate' &func
.funcend
.desc begin
The &func function rotates the unsigned integer, determined by
.arg value,
to the left by the number of bits specified in
.arg shift.
If you port an application using &func between a 16-bit and a 32-bit
environment, you will get different results because of the difference
in the size of integers.
.desc end
.return begin
The rotated value is returned.
.return end
.see begin
.seelist _rotl _lrotl _lrotr _rotr
.see end
.exmp begin
#include <stdio.h>
#include <stdlib.h>

unsigned int mask = 0x0F00;

void main()
  {
    mask = _rotl( mask, 4 );
    printf( "%04X\n", mask );
  }
.exmp output
F000
.exmp end
.class WATCOM
.system
