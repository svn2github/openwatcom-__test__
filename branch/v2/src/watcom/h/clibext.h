/* clibext.h:
   This file contains defines and prototypes of functions that are present
   in Watcom's CLIB but not in many other C libraries */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/types.h>      /* for off_t */
#if defined(__QNX__) || defined(__SVR4)
    #define _XPG4_2         /* Required on Solaris... */
    #include <strings.h>    /* for str*case* functions */
    #undef _XPG4_2          /* ...but causes trouble */
#endif

#if defined(__linux__) && !defined(__LINUX__)
#define __LINUX__
#endif
#if defined(__unix__) && !defined(__UNIX__)
#define __UNIX__
#endif

#ifndef F_OK
#define F_OK 00
#endif
#ifndef S_IRUSR
#define S_IRUSR _S_IREAD
#endif
#ifndef S_IWUSR
#define S_IWUSR _S_IWRITE
#endif
#ifndef S_IRGRP
#define S_IRGRP _S_IREAD
#endif
#ifndef S_IWGRP
#define S_IWGRP _S_IWRITE
#endif
#ifndef O_BINARY
#define O_BINARY 0
#endif
#ifndef O_TEXT
#define O_TEXT 0
#endif
#ifdef _MSC_VER
#define _A_VOLID 0
#endif
#if !defined(__WATCOMC__) && !defined(_MSC_VER)
#define stricmp strcasecmp
#define strcmpi strcasecmp
#define strnicmp strncasecmp
#ifndef getch
#define getch getchar
#endif
#endif
#ifdef _MSC_VER
#define _vbprintf _vsnprintf
#else
#define _vbprintf vsnprintf
#define _vsnprintf vsnprintf
#endif
#define __near
#define near
#define __based(x)
#define _snprintf snprintf
#define  __va_list  va_list
#define __Strtold(s,ld,endptr) ((*(double *)(ld))=strtod(s,endptr))
#ifndef _MSC_VER
#define SOPEN_DEFINED
#define sopen(x,y,z) open((x),(y))
#define _fsopen(x,y,z) fopen(x,y)
#endif
#define _fmemcpy memcpy
#ifndef PATH_MAX
/* PATH_MAX is not standard, just common. FILENAME_MAX is ISO C. */
#define PATH_MAX FILENAME_MAX
#endif
#ifndef _MAX_PATH
#define _MAX_PATH (PATH_MAX+1)
#endif
#ifndef _MAX_PATH2
#define _MAX_PATH2 (_MAX_PATH+3)
#endif
#ifndef _MAX_DRIVE
#define _MAX_DRIVE   3
#endif
#ifndef _MAX_DIR
#define _MAX_DIR (PATH_MAX-3)
#endif
#ifndef _MAX_FNAME
#define _MAX_FNAME (PATH_MAX-3)
#endif
#ifndef _MAX_EXT
#define _MAX_EXT (PATH_MAX-3)
#endif
#ifndef SH_DENYWR
#define SH_DENYWR 0
#endif

#ifndef max 
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#ifndef _WCRTLINK
#define _WCRTLINK
#endif
#ifndef _WCI86FAR
#define _WCI86FAR
#endif
#ifndef _WCNEAR
#define _WCNEAR
#endif
#ifndef _MSC_VER
#define __int64 long long
#define _HEAPOK 0
#define _heapchk(x) _HEAPOK
#define _expand(x,y) (NULL)
#endif

char *itoa( int value, char *buf, int radix );
char *utoa( unsigned int value, char *buf, int radix );
char *ltoa( long int value, char *buf, int radix );
char *ultoa( unsigned long int value, char *buf, int radix );
void _splitpath2( const char *inp, char *outp, char **drive,
                  char **dir, char **fn, char **ext );
void _splitpath( const char *path, char *drive,
                 char *dir, char *fname, char *ext );
void _makepath( char *path, const char *drive, const char *dir,
                const char *fname, const char *ext );
char *_fullpath( char *buf, const char *path, size_t size );
char *strlwr( char *string );
char *strupr( char *string );
char *strrev( char *string );
int memicmp(const void *, const void *, size_t);
off_t tell( int handle );
long filelength(int handle);
int eof( int fildes );
int _bgetcmd( char *buffer, int len );
char *getcmd( char *buffer );
char *_cmdname( char *name );
void _searchenv( const char *name, const char *env_var, char *buf );
char *strnset( char *string, int c, size_t len );
#ifdef __GLIBC__
size_t strlcpy( char *dst, const char *src, size_t len );
size_t strlcat( char *dst, const char *t, size_t n );
#endif

extern char **_argv;    /* argument vector */
extern int  _argc;
