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


#include "vi.h"
#include "win.h"

/*
 * MoveScreenML - screen shifting (mainly for scrolling - used only for mdles)
 */
int MoveScreenML( linenum ntop )
{
    linenum     lastline;

    if( ntop > LeftTopPos.line ) {
        CFindLastLine( &lastline );
        if( ntop > lastline ) {
            ntop = lastline;
        }
    } else {
        if( ntop < 1 ) {
            ntop = 1;
        }
    }
    LeftTopPos.line = ntop;
    return( ERR_NO_ERR );

} /* MoveScreenML */

/*
 * MoveScreenDown - expose bottom line
 */
int MoveScreenDown( void )
{
    linenum     lne, cnt, lines, top, x;

    CFindLastLine( &lne );
    lines = WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES );
    x = lne - lines + 1;
    if( x <= 0 ) {
        return( ERR_NO_ERR );
    }
    cnt = GetRepeatCount();
    top = LeftTopPos.line + cnt;
    if( top > x ) {
        top = x;
    }
    LeftTopPos.line = top;
    if( top >= CurrentPos.line ) {
        GoToLineNoRelCurs( top );
    }
    DCDisplayAllLines();
    SetWindowCursor();
    return( ERR_NO_ERR );

} /* MoveScreenDown */

/*
 * MoveScreenUp - expose top line
 */
int MoveScreenUp( void )
{
    linenum     lne, cnt, lines, top, nlne;

    lines = WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES );
    CFindLastLine( &lne );
    cnt = GetRepeatCount();
    top = LeftTopPos.line - cnt;
    if( top < 1 ) {
        top = 1;
    }
    LeftTopPos.line = top;
    if( CurrentPos.line >= top + lines ) {
        nlne = top + lines - 1;
        if( nlne > lne ) {
            nlne = lne;
        }
        GoToLineNoRelCurs( nlne );
    }
    DCDisplayAllLines();
    SetWindowCursor();
    return( ERR_NO_ERR );

} /* MoveScreenUp */

int MoveScreenDownPageML( void )
{
    return MoveScreenML( LeftTopPos.line +
                         WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES ) );
}

int MoveScreenUpPageML( void )
{
    return MoveScreenML( LeftTopPos.line -
                         WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES ) );
}

int MoveScreenLeftPageML( void )
{
    return MoveScreenLeftRightML(
        LeftTopPos.column - WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_COLS ) + 2 );
}

int MoveScreenRightPageML( void )
{
    return MoveScreenLeftRightML(
        LeftTopPos.column + WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_COLS ) - 2 );
}

/*
 * MovePage - move by a number of pages
 */
int MovePage( int dir, long repcnt, bool keepselect )
{
    int         rc;
    linenum     x, top, ll;
    linenum     tmp;

    if( EditFlags.Modeless && (keepselect == FALSE) ) {
        UnselectRegion();
    }

    tmp = (repcnt * dir *
                WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES ))
                - (dir * PageLinesExposed);
#if 0
    x = CurrentPos.line + tmp;
    top = LeftTopPos.line + tmp;
    CFindLastLine( &ll );
    if( top > ll ) {
        top = ll;
    } else if( top < 1 ) {
        top = 1;
    }
    if( x > ll ) {
        x = ll;
    } else if( x < 1 ) {
        x = 1;
    }
#else
    top = LeftTopPos.line + tmp;
    if( top < 1 ) {
        top = 1;
    }
    rc = CAdvanceToLine( top );
    if( rc == ERR_NO_SUCH_LINE ) {
        rc = CFindLastLine( &ll );
        top = ll;
    }
    if( rc ) {
        return( rc );
    }
    x = CurrentPos.line + tmp;
    if( x < 1 ) {
        x = 1;
    }
    rc = CAdvanceToLine( x );
    if( rc == ERR_NO_SUCH_LINE ) {
        rc = CFindLastLine( &ll );
        x = ll;
    }
    if( rc ) {
        return( rc );
    }
#endif
    LeftTopPos.line = top;
    SetCurrentLineNumber( x );
    rc = CGimmeLinePtr( CurrentPos.line, &CurrentFcb, &CurrentLine );
    if( !rc ) {
        CheckCurrentColumn();
        UpdateStatusWindow();
        SetWindowCursor();
        DCInvalidateAllLines();
        DCDisplayAllLines();
    }
    return( rc );

} /* MovePage */

int MovePageDown( void )
{
    return( MovePage( 1, GetRepeatCount(), FALSE ) );
}

int MovePageUp( void )
{
    return( MovePage( -1, GetRepeatCount(), FALSE ) );
}


/*
 * MovePosition - move to a screen position
 */
int MovePosition( void )
{
    linenum     lne, lines;
    int         key, i;

    if( RepeatDigits == 0 ) {
        lne = CurrentPos.line;
    } else {
        lne = GetRepeatCount();
        if( IsPastLastLine( lne ) ) {
            return( ERR_INVALID_REDRAW );
        }
    }
    lines = WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES );
    key = GetNextEvent( FALSE );
    switch( key ) {
    case '.':
        LeftTopPos.line = lne - lines / 2;
        break;
    case VI_KEY( ENTER ):
        LeftTopPos.line = lne;
        break;
    case '-':
        LeftTopPos.line = lne - lines + 1;
        break;
    default:
        return( ERR_INVALID_REDRAW );
    }
    if( LeftTopPos.line < 1 ) {
        LeftTopPos.line = 1;
    }
    SetCurrentLineNumber( lne );
    i = CGimmeLinePtr( CurrentPos.line, &CurrentFcb, &CurrentLine );
    CurrentPos.column = 1;
    DCInvalidateAllLines();
    DCDisplayAllLines();
    if( !i ) {
        i = GoToColumnOnCurrentLine( FindStartOfCurrentLine() );
    }
    return( i );

} /* MovePosition */


/*
 * moveHalfPage - display half a page
 */
static int moveHalfPage( int dir )
{
    int         ople, rc;
    long        repcnt;
    int         ln;

    ople = PageLinesExposed;
    repcnt = GetRepeatCount();
    if( repcnt > 1 ) {
        ln = WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES ) - repcnt;
        if( ln < 1 ) {
            ln = 1;
        }
        HalfPageLines = ln;
    }

    PageLinesExposed = HalfPageLines;
    rc = MovePage( dir, 1, FALSE );
    PageLinesExposed = ople;
    return( rc );

} /* moveHalfPage */

int MoveHalfPageDown( void )
{
    return( moveHalfPage( 1 ) );

} /* MoveHalfPageDown */

int MoveHalfPageUp( void )
{
    return( moveHalfPage( -1 ) );

} /* MoveHalfPageUp */

int MoveScreenLeftRightML( int newleft )
{
    LeftTopPos.column = newleft;

    if( LeftTopPos.column <= 0 ) {
        LeftTopPos.column = 0;
    } else {
        if( LeftTopPos.column >= MAX_INPUT_LINE - 1 ) {
            LeftTopPos.column = MAX_INPUT_LINE - 1;
        }
    }
    return( ERR_NO_ERR );
}
