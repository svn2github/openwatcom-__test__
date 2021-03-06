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


#include "variety.h"
#include <jstring.h>


/**
*
*  Name:        jstrcat         文字列を結合する
*               jstrncat
*
*  Synopsis:    p = jstrncat( to, from, n );
*               p = jstrcat( to, from );
*
*               JSTRING p;      ｔｏと同じ値
*               JSTRING to;     結合される文字列
*               JSTRING from;   結合する文字列
*               int n;          文字数
*
*  Description: 文字列ｔｏの後に文字列ｆｒｏｍの先頭から
*               ｎ文字分だけ結合する。
*
*  Returns:     第１引数ｔｏと同じものを返す。
*
*
*  Name:        jstrcat          concatenate KANJI strings
*               jstrncat
*
*  Synopsis:    p = jstrncat( to, from, n );
*               p = jstrcat( to, from );
*
*               JSTRING p;      same value as argument "to"
*               JSTRING to;     distination KANJI string pointer.
*               JSTRING from;   KANJI string pointer for appendage
*               int     n;      number of letters should be appended
*
* Description:  The jstrcat and jstrncat functions append a copy of the KANJI
*               string pointed to by "from" to the end of the KANJI string
*               pointed to by "to".  The first letter of "from" overwrite the
*               null character at the end of "to", and jstrncat appends only
*               "n" number of letters.
*
*  Returns:     The value of "to" is returned.
**/

_WCRTLINK JSTRING jstrncat( JCHAR *to, const JCHAR *from, size_t n )
{
    JCHAR *p;
    size_t m;
    JMOJI mm;

    p = to;
    while( p = jgetmoji( p, &mm ), mm );

    m = mtob( from, n );
    while( m-- > 0 ) *p++ = *from++;
    *p = '\0';
    return( to );
}

_WCRTLINK JSTRING jstrcat( JCHAR *to, const JCHAR *from )
{
    return jstrncat( to, from, jstrlen( from ) );
}
