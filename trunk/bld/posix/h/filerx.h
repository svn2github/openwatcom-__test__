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
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#ifndef _INCLUDED_FILERX_H
#define _INCLUDED_FILERX_H

#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif

int FileMatch( void *crx, const char *name );
char *FileMatchInit( void **crx, const char *wild );
void FileMatchFini( void *crx ) ;
int FileNameWild( const char *wild, int isrx );
DIR *OpenDirAll( const char *filename,  char *wild );
int FileMatchNoRx( const char *name, const char *wild );
int isFILESEP( int c );

/* Removed FILESEP - \ and / correct except in UNIX.   W.Briscoe 20031112 */
#ifndef __QNX__
#define FILESEPSTR      "\\"
#else
#define FILESEPSTR      "/"
#endif

#endif
