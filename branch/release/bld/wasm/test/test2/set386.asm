.386
.model small
.data
extern b:word
extern d:dword
extern e:fword

extern h:near
extern i:far
extern j:proc
.code

call  b
call  d
call  e
call  h
call  far ptr i
call  far ptr j

end
