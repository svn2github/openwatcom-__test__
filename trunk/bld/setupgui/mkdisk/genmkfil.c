#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <process.h>
#include <sys\types.h>
#include <sys\stat.h>


enum {
    FALSE,
    TRUE
};


typedef struct file_info {
    char                *file;
    char                *pack;
    char                *path;
    char		*rel_file;
    struct file_info    *next;
} FILE_INFO;

typedef struct version_info {
    char		*version;
    struct version_info	*next;
} VERSION_INFO;


FILE_INFO               *FileList = NULL;
VERSION_INFO		*VersionList = NULL;


int main( int argc, char *argv[] )
//================================

{
    int                 i, ok;
    FILE                *fp;

    if( argc < 2 ) {
	printf( "Usage: GEMMKFIL <file_list> [versions]\n" );
	return( 1 );
    }
    fp = fopen( argv[ 1 ], "r" );
    if( fp == NULL ) {
	printf( "Cannot open '%s'\n", argv[ 1 ] );
	return( 1 );
    }
    for( i = 2; argv[ i ] != NULL; ++i ) {
	AddVersion( argv[ i ] );
    }
    ok = ReadList( fp );
    fclose( fp );
    if( ok ) {
	CreateMakeFile();
    }
    return( 0 );
}


int ReadList( FILE *fp )
//======================

{
    char                *type;
    char		*path;
    char		*file;
    char		*rel_file;
    char		*extra;
    char		*patch;
    char		*where;
    char                buf[ 128 ];

    while( fgets( buf, 127, fp ) != NULL ) {
	buf[ strlen( buf ) - 1 ] = '\0';
	if( buf[ 0 ] == '\0' ) continue;
	if( buf[ 0 ] == '#' ) {
	    if( buf[ 2 ] == '@' ) {     // database
		buf[ 1 ] = '-';         // (so strtok works)
	    } else {
		continue;
	    }
	}
	type = strtok( buf, " \t" );
	path = strtok( NULL, " \t" );
	file = strtok( NULL, " \t" );
	rel_file = strtok( NULL, " \t" );
	extra = strtok( NULL, " \t" );
	patch = strtok( NULL, " \t" );
	for( ;; ) {
	    where = strtok( NULL, " \t" );
	    if( where == NULL ) break;
	    if( InVersionList( where ) ) {
		if( !AddFile( path, file, rel_file, patch ) ) {
		    return( FALSE );
		}
		break;
	    }
	}
    }
    return( TRUE );
}


int AddFile( char *path, char *file, char *rel_file, char *patch )
//================================================

{
    FILE_INFO           *new, *curr;

    new = malloc( sizeof( FILE_INFO ) );
    if( new == NULL ) {
	printf( "Out of memory\n" );
	return( FALSE );
    } else {
	new->path = strdup( path );
	new->file = strdup( file );
	new->rel_file = strdup( rel_file );
	new->pack = strdup( patch );
	if( new->path == NULL || new->file == NULL || new->pack == NULL ) {
	    printf( "Out of memory\n" );
	    return( FALSE );
	}
	new->next = NULL;
	if( FileList == NULL ) {
	    FileList = new;
	} else {
	    curr = FileList;
	    while( curr->next != NULL ) {
		curr = curr->next;
	    }
	    curr->next = new;
	}
	return( TRUE );
    }
}


void CreateMakeFile()
//===================

{
    FILE                *fp;
    FILE_INFO           *curr;

    fp = fopen( "mkfile", "w" );
    if( fp == NULL ) {
	printf( "Cannot create file 'mkfile'\n" );
	fp = stdout;
    }

    fprintf( fp, "all : .symbolic\nall : &\n" );
    for( curr = FileList; ; ) {
	fprintf( fp, "    $(%%packdir)\\%s", curr->pack );
	curr = curr->next;
	if( curr == NULL ) break;
	fprintf( fp, " &\n" );
    }
    fprintf( fp, "\n\n" );

    for( curr = FileList; curr != NULL; curr = curr->next ) {
	fprintf( fp, "$(%%packdir)\\%s : ", curr->pack );
	if( strchr( curr->path, ':' ) == NULL ) {
	    fprintf( fp, "$(%%relroot)\\" );
	}
	if( stricmp( curr->rel_file, "." ) != 0 ) {
	    fprintf( fp, "%s\n", curr->rel_file );
	} else {
	    if( stricmp( curr->path, "." ) != 0 ) {
		fprintf( fp, "%s\\", curr->path );
	    } 
	    fprintf( fp, "%s\n", curr->file );
	}
//      fprintf( fp, "    @del $^@ >nul\n    wpack -a -q $^@ $[@\n" );
	fprintf( fp, "    wpack -a -q $^@ $[@\n" );
    }
    fclose( fp );
}


void AddVersion( char *str )
//==========================

{
    VERSION_INFO	*ver;

    ver = malloc( sizeof( VERSION_INFO ) );
    if( ver == NULL ) {
	printf( "Out of memory\n" );
    } else {
	ver->version = str;
	ver->next = VersionList;
	VersionList = ver;
    }
}


int InVersionList( char *str )
//============================

{
    VERSION_INFO	*ver;

    if( VersionList == NULL ) {
	return( TRUE );
    } else {
	for( ver = VersionList; ver != NULL; ver = ver->next ) {
	    if( stricmp( str, ver->version ) == 0 ) {
		return( TRUE );
	    }
	}
	return( FALSE );
    }
}
