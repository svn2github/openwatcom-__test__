/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2006 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  This file contains the queue tests.
****************************************************************************/

#include <iostream>
#include <list>
#include <queue>

#include "sanity.cpp"

// I really want a template template parameter. I should be able to give basic_test a template
// (not a type) and have it instantiate that template internally using an appropriate type. In
// other words, it should not be necessary for the caller of basic_test to know that the type
// 'int' is used during testing. Open Watcom 1.9 does not support template template parameters.
//
template< class Container >
bool basic_test( )
{
    std::queue< int, Container > q;
    if( !q._Sane( )      ) FAIL;
    if(  q.size ( ) != 0 ) FAIL;
    if( !q.empty( )      ) FAIL;

    // Push enough items on the queue to exercise the underlying container a bit.
    for( int i = 1; i <= 1000; ++i ) {
        q.push( i );
        if( q.size( ) != i ) FAIL;
    }

    // Remove the items.
    for( int i = 1; i <= 1000; ++i ) {
        if( q.front( ) != i ) FAIL;
        q.pop( );
        if( q.size( ) != 1000 - i ) FAIL;
    }

    if( !q._Sane( )      ) FAIL;
    if(  q.size ( ) != 0 ) FAIL;
    if( !q.empty( )      ) FAIL;
    return( true );
}


bool relational_test( )
{
    // At the time of this writing, std::dequeue::swap is not implemented. Also the relational
    // operators in std::list are not implemented. Once those issues are fixed this test can be
    // enabled and generalized to use both container templates.
#ifdef NEVER
    std::queue< int > a, b;

    for( int i = 0; i < 1000; ++i ) {
        a.push( i );
        b.push( i );
    }

    if( !(a == b) ) FAIL;
    b.pop( );
    if(  (a == b) ) FAIL;
    if( !(a <  b) ) FAIL;

    a.swap( b );
    if( !(a._Sane( ) and b._Sane( )) ) FAIL;
    if(  (a == b) ) FAIL;
    if( !(b <  a) ) FAIL;
#endif
    return( true );
}


int main( )
{
    int rc = 0;
    int original_count = heap_count( );

    try {
        if( !basic_test< std::deque< int > >( )  || !heap_ok( "t01" ) ) rc = 1;
        if( !basic_test< std::list< int > >( )   || !heap_ok( "t02" ) ) rc = 1;
        if( !relational_test( )                  || !heap_ok( "t03" ) ) rc = 1;
    }
    catch( ... ) {
        std::cout << "Unexpected exception of unexpected type.\n";
        rc = 1;
    }

    if( heap_count( ) != original_count ) {
        std::cout << "Possible memory leak!\n";
        rc = 1;
    }
    return( rc );
}
