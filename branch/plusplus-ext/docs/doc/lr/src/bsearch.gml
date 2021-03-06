.func bsearch
#include <stdlib.h>
void *bsearch( const void *key,
               const void *base,
               size_t num,
               size_t width,
               int (*compar)( const void *pkey,
                              const void *pbase) );
.funcend
.*
.safealt
.*
.desc begin
The &func function performs a binary search of a sorted array of
.arg num
elements, which is pointed to by
.arg base,
for an item which matches the object pointed to by
.arg key.
Each element in the array is
.arg width
bytes in size.
The comparison function pointed to by
.arg compar
is called with two arguments that point to elements in the array.
The first argument
.arg pkey
points to the same object pointed to by
.arg key.
The second argument
.arg pbase
points to a element in the array.
The comparison function shall return an integer less than, equal to,
or greater than zero if the
.arg key
object is less than, equal to,
or greater than the element in the array.
.desc end
.return begin
The &func function returns a pointer to the matching member
of the array, or
.mono NULL
if a matching object could not be found.
If there are multiple values in the array which are equal to the
.arg key,
the return value is not necessarily the first occurrence of a matching
value when the array is searched linearly.
.return end
.see begin
.seelist bsearch bsearch_s lfind lsearch qsort qsort_s
.see end
.exmp begin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *keywords[] = {
        "auto",
        "break",
        "case",
        "char",
        /* . */
        /* . */
        /* . */
        "while"
  };
.exmp break
#define NUM_KW  sizeof(keywords) / sizeof(char *)
.exmp break
int kw_compare( const void *p1, const void *p2 )
{
    const char *p1c = (const char *) p1;
    const char **p2c = (const char **) p2;
    return( strcmp( p1c, *p2c ) );
}
.exmp break
int keyword_lookup( const char *name )
{
    const char **key;
    key = (char const **) bsearch( name, keywords, NUM_KW,
                   sizeof( char * ),  kw_compare );
    if( key == NULL ) return( -1 );
    return key - keywords;
}
.exmp break
void main()
{
    printf( "%d\n", keyword_lookup( "case" ) );
    printf( "%d\n", keyword_lookup( "crigger" ) );
    printf( "%d\n", keyword_lookup( "auto" ) );
}
//************ Sample program output ************
//2
//-1
//0
.exmp output
2
-1
0
.exmp end
.class ANSI
.system
