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
* Description:  Installer data source file I/O routines.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "setupio.h"

enum ds_type {
    DS_FILE,
    DS_ZIP
};

typedef struct data_source_t {
    enum ds_type    type;
    union {
        int         fhandle;
    };
} data_source;


extern void *FileOpen( const char *path, int flags )
{
    data_source     *ds;

    ds = malloc( sizeof( *ds ) );
    if( ds == NULL )
        return( NULL );

    ds->fhandle = open( path, flags );
    ds->type = DS_FILE;
    if( ds->fhandle == -1 ) {
        free( ds );
        ds = NULL;
    }
    return( ds );
}


extern int FileClose( void *handle )
{
    data_source     *ds = handle;
    int             rc;

    switch( ds->type ) {
    case DS_FILE:
        rc = close( ds->fhandle );
        break;
    case DS_ZIP:
    default:
        rc = -1;
    }

    free( ds );
    return( rc );
}


extern long FileSeek( void *handle, long offset, int origin )
{
    data_source     *ds = handle;
    long            pos;

    switch( ds->type ) {
    case DS_FILE:
        pos = lseek( ds->fhandle, offset, origin );
        break;
    case DS_ZIP:
    default:
        pos = -1;
    }

    return( pos );
}


extern size_t FileRead( void *handle, void *buffer, size_t length )
{
    data_source     *ds = handle;
    size_t          amt;

    switch( ds->type ) {
    case DS_FILE:
        amt = read( ds->fhandle, buffer, length );
        break;
    case DS_ZIP:
    default:
        amt = 0;
    }

    return( amt );
}
