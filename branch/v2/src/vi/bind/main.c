/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  VI editor bind utility.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "banner.h"

#include "clibext.h"

char    magic_cookie[] = "CGEXXX";

#define MAGIC_COOKIE_SIZE sizeof( magic_cookie )

#define isWSorCtrlZ(x)  (isspace( x ) || (x == 0x1A))

#define MAX_LINE_LEN    1024
#define FALSE           0
#define TRUE            1
#define COPY_SIZE       0x8000 - 512
#define MAX_DATA_FILES  255

char    *dats[MAX_DATA_FILES];

int16_t  FileCount;
int32_t *idx;
int16_t *entries;
int     sflag = FALSE;
int     qflag = FALSE;
char    _bf[] = "edbind.dat";
char    *bindfile = _bf;

void Banner( void )
{
    if( qflag ) {
        return;
    }
    printf( "%s\n", banner1w( "Editor Bind Utility",_EDBIND_VERSION_ ) );
    printf( "%s\n", banner2a() );
    printf( "%s\n", banner3 );
    printf( "%s\n", banner3a );
}

/*
 * Abort - made a boo-boo
 */
void Abort( char *str, ... )
{
    va_list     al;

    va_start( al, str );
    vprintf( str, al );
    va_end( al );
    printf( "\n" );
    exit( 1 );

} /* Abort */

/*
 * MyPrintf - do a printf
 */
void MyPrintf( char *str, ... )
{
    va_list     al;

    if( !qflag ) {
        va_start( al, str );
        vprintf( str, al );
        va_end( al );
    }

} /* MyPrintf */

/*
 * AddDataToEXE - tack data to end of an EXE
 */
void AddDataToEXE( char *exe, char *buffer, int len, unsigned long tocopy )
{
    int                 h, i, newh;
    char                buff[MAGIC_COOKIE_SIZE + 3];
    int32_t             shift;
    int16_t             taillen;
    char                *copy;
    char                foo[128];
    char                drive[_MAX_DRIVE], dir[_MAX_DIR];

    /*
     * get files
     */
    copy = malloc( COPY_SIZE );
    if( copy == NULL ) {
        Abort( "Out of Memory" );
    }
    h = open( exe, O_RDWR | O_BINARY );
    if( h == -1 ) {
        Abort( "Fatal error opening \"%s\"", exe );
    }
    _splitpath( exe, drive, dir, NULL, NULL );
    _makepath( foo, drive, dir, "__cge__", ".exe" );
    newh = open( foo, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY,
                 S_IRWXU | S_IRWXG | S_IRWXO );
    if( newh == -1 ) {
        Abort( "Fatal error opening \"%s\"", foo );
    }

    /*
     * get trailer
     */
    i = lseek( h, -((long)MAGIC_COOKIE_SIZE + 3L), SEEK_END );
    if( i == -1 ) {
        Abort( "Initial seek error on \"%s\"", exe );
    }
    i = read( h, buff, 3 + MAGIC_COOKIE_SIZE );
    if( i == -1 ) {
        Abort( "Read error on \"%s\"", exe );
    }

    /*
     * if trailer is one of ours, then set back to overwrite data;
     * else just set to write at end of file
     */
    if( strcmp( buff, magic_cookie ) ) {
        if( sflag ) {
            Abort( "\"%s\" does not contain configuration data!", exe );
        }
    } else {
        taillen = *( (uint16_t *)&(buff[MAGIC_COOKIE_SIZE + 1]) );
        shift = -((int32_t)taillen + MAGIC_COOKIE_SIZE + 3);
        tocopy += shift;
    }
    i = lseek( h, 0, SEEK_SET );
    if( i ) {
        Abort( "Seek error on \"%s\"", exe );
    }

    /*
     * copy crap
     */
    while( tocopy > 0 ) {
        if( tocopy > (unsigned long)COPY_SIZE ) {
            i = read( h, copy, COPY_SIZE );
            if( i != COPY_SIZE ) {
                Abort( "Read error on \"%s\"", exe );
            }
            i = write( newh, copy, COPY_SIZE );
            if( i != COPY_SIZE ) {
                Abort( "Write error on \"%s\"", foo );
            }
            tocopy -= (unsigned long)COPY_SIZE;
        } else {
            i = read( h, copy, (unsigned int)tocopy );
            if( i != tocopy ) {
                Abort( "Read error on \"%s\"", exe );
            }
            i = write( newh, copy, (unsigned int)tocopy );
            if( i != (int)tocopy ) {
                Abort( "Write error on \"%s\"", foo );
            }
            tocopy = 0;
        }
    }
    close( h );

    /*
     * write out data and new trailer
     */
    if( !sflag ) {
        i = write( newh, buffer, len );
        if( i != len ) {
            Abort( "write 1 error on \"%s\"", exe );
        }
        i = write( newh, magic_cookie, MAGIC_COOKIE_SIZE + 1 );
        if( i != MAGIC_COOKIE_SIZE + 1 ) {
            Abort( "write 2 error on \"%s\"", exe );
        }
        i = write( newh, &len, sizeof( int16_t ) );
        if( i != sizeof( int16_t ) ) {
            Abort( "write 3 error on \"%s\"", exe );
        }
    }
    close( newh );
    remove( exe );
    rename( foo, exe );

} /* AddDataToEXE */

/*
 * GetFromEnv - get file name from environment
 */
static void GetFromEnv( char *what, char *path )
{
    _searchenv( what, "EDPATH", path );
    if( path[0] != 0 ) {
        return;
    }
    _searchenv( what, "PATH", path );

} /* GetFromEnv */

/*
 * GetFromEnvAndOpen - search env and fopen a file
 */
FILE *GetFromEnvAndOpen( char *inpath )
{
    char tmppath[_MAX_PATH];

    GetFromEnv( inpath, tmppath );
    if( tmppath[0] != 0 ) {
        MyPrintf( " %s...", tmppath );
        return( fopen( tmppath, "r" ) );
    }
    return( NULL );

} /* GetFromEnvAndOpen */

/*
 * Usage - dump the usage message
 */
void Usage( char *msg )
{
    if( msg != NULL ) {
        printf( "%s\n", msg );
    }
    printf( "Usage: edbind [-?sq] [-d<datfile>] <exename>\n" );
    if( msg == NULL ) {
        printf( "\t<exename>\t     executable to add editor data to\n" );
        printf( "\tOptions -?:\t     display this message\n" );
        printf( "\t\t-s:\t     strip info from executable\n" );
        printf( "\t\t-q:\t     run quietly\n" );
        printf( "\t\t-d<datfile>: specify data file other than edbind.dat\n" );
    }
    exit( 1 );

} /* Usage */

/*
 * EliminateFirstN - eliminate first n chars from buff
 */
static void EliminateFirstN( char *buff, int n  )
{
    char        *buff2;

    buff2 = &buff[n];
    while( *buff2 != 0 ) {
        *buff++ = *buff2++;
    }
    *buff = 0;

} /* EliminateFirstN */

/*
 * RemoveLeadingSpaces - remove leading spaces from a string
 */
void RemoveLeadingSpaces( char *buff )
{
    int         k = 0;

    if( buff[0] == 0 ) {
        return;
    }
    while( isspace( buff[k] ) ) {
        k++;
    }
    if( k == 0 ) {
        return;
    }
    EliminateFirstN( buff, k );

} /* RemoveLeadingSpaces */

/*
 * MyAlloc - allocate memory, failing if cannot
 */
void *MyAlloc( unsigned size )
{
    void        *tmp;

    tmp = malloc( size );
    if( tmp == NULL ) {
        Abort( "Out of Memory!" );
    }
    return( tmp );

} /* MyAlloc */


int main( int argc, char *argv[] )
{
    char                *buff = NULL;
    char                *buff2, *buff3;
    char                *buffn, *buffs;
    int                 i, cnt, bytes, lines, j, k;
    FILE                *f;
    struct stat         fs;
    char                drive[_MAX_DRIVE], dir[_MAX_DIR];
    char                fname[_MAX_FNAME], ext[_MAX_EXT];
    char                path[_MAX_PATH];
    char                tmppath[_MAX_PATH];
    char                tmpfname[_MAX_FNAME], tmpext[_MAX_EXT];
    int                 c;

    while( (c = getopt( argc, argv, "d:qs" )) != EOF ) {
        switch( c ) {
        case 's':
            sflag = TRUE;
            break;
        case 'q':
            qflag = TRUE;
            break;
        case 'd':
            bindfile = optarg;
            break;
        case '?':
            Banner();
            Usage( NULL );
            break;
        default:
            Banner();
            Usage( "Invalid option" );
        }
    }

    Banner();

    /*
     * now, check for null file name
     */
    if( optind >= argc ) {
        Usage( "No executable to bind" );
    }
    _splitpath( argv[optind], drive, dir, fname, ext );
    if( ext[0] == 0 ) {
        _makepath( path, drive, dir, fname, ".exe" );
    } else {
        strcpy( path, argv[optind] );
    }
    if( stat( path, &fs ) == -1 ) {
        Abort( "Could not find executable \"%s\"", path );
    }

    if( !sflag ) {

        buff = MyAlloc( 65000 );
        buff2 = MyAlloc( 32000 );
        buff3 = MyAlloc( MAX_LINE_LEN );

        /*
         * read in all data files
         */
        MyPrintf( "Getting data files from" );
        f = GetFromEnvAndOpen( bindfile );
        MyPrintf( "\n" );
        if( f == NULL ) {
            Abort( "Could not open %s", bindfile );
        }
        while( fgets( buff3, MAX_LINE_LEN, f ) != NULL ) {
            for( i = strlen( buff3 ); i && isWSorCtrlZ( buff3[i - 1] ); --i ) {
                buff3[i - 1] = '\0';
            }
            if( buff3[0] == '\0' ) {
                continue;
            }
            RemoveLeadingSpaces( buff3 );
            if( buff3[0] == '#' ) {
                continue;
            }
            dats[FileCount] = MyAlloc( strlen( buff3 ) + 1 );
            strcpy( dats[FileCount], buff3 );
            FileCount++;
            if( FileCount >= MAX_DATA_FILES ) {
                Abort( "Too many files to bind!" );
            }
        }
        fclose( f );
        idx = MyAlloc( FileCount * sizeof( int32_t ) );
        entries = MyAlloc( FileCount * sizeof( int16_t ) );

        buffn = buff;
        cnt = 0;

        *(int16_t *)buffn = FileCount;
        buffn += sizeof( int16_t );
        cnt += sizeof( int16_t );
        buffs = buffn;
        buffn += sizeof( int16_t );
        cnt += sizeof( int16_t );
        k = 0;
        for( i = 0; i < FileCount; i++ ) {
//          j = strlen( dats[i] ) + 1;
//          memcpy( buffn, dats[i], j );
            _splitpath( dats[i], NULL, NULL, tmpfname, tmpext );
            _makepath( tmppath, NULL, NULL, tmpfname, tmpext );
            j = strlen( tmppath ) + 1;
            memcpy( buffn, tmppath, j );
            buffn += j;
            cnt += j;
            k += j;
        }
        *(int16_t *)buffs = k + 1;  /* size of token list */
        *buffn = 0;                 /* trailing zero */
        buffn++;
        cnt++;
        buffs = buffn;
        buffn += FileCount * (sizeof( int16_t ) + sizeof( int32_t ));
        cnt += FileCount * (sizeof( int16_t ) + sizeof( int32_t ));

        for( j = 0; j < FileCount; j++ ) {
            MyPrintf( "Loading" );
            f = GetFromEnvAndOpen( dats[j] );
            if( f == NULL ) {
                Abort( "\nLoad of %s failed!", dats[j] );
            }
            setvbuf( f, buff2, _IOFBF, 32000 );
            bytes = lines = 0;
            idx[j] = cnt;
            while( fgets( buff3, MAX_LINE_LEN, f ) != NULL ) {
                for( i = strlen( buff3 ); i && isWSorCtrlZ( buff3[i - 1] ); --i )
                    buff3[i - 1] = '\0';
                if( buff3[0] == '\0' ) {
                    continue;
                }
                RemoveLeadingSpaces( buff3 );
                if( buff3[0] == '#' ) {
                    continue;
                }
                i = strlen( buff3 );
                *buffn = (char)i;
                buffn++;
                memcpy( buffn, buff3, i );
                buffn += i;
                cnt += i + 1;
                lines++;
                bytes += i;
            }
            fclose( f );
            entries[j] = lines;
            MyPrintf( "Added %d lines (%d bytes)\n", lines, bytes );
        }
        i = FileCount;
        memcpy( buffs, idx, FileCount * sizeof( int32_t ) );
        buffs += FileCount * sizeof( int32_t );
        memcpy( buffs, entries, FileCount * sizeof( int16_t ) );
    }

    AddDataToEXE( path, buff, cnt, fs.st_size );
    if( !sflag ) {
        MyPrintf( "Added %d bytes to \"%s\"\n", cnt, path );
    } else {
        MyPrintf( "\"%s\" has been stripped of configuration information\n", path );
    }
    return( 0 );

} /* main */
