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
* Description: This file contains the functional tests for std::vector.
*
****************************************************************************/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "sanity.cpp"

bool construction_test( )
{
  bool rc = true;
  std::vector< int > v1;
  std::vector< int > v2(10);
  std::vector< int > v3(v1);
  std::vector< int > v4(v2);
  std::vector< int > v5(10, 1);

  if( v1.size( ) != 0 || !v1.empty( ) || INSANE( v1 ) ) {
    std::cout << "construct FAIL 0001\n"; rc = false;
  }
  if( v2.size( ) != 10 || v2.empty( ) || INSANE( v2 ) ) {
    std::cout << "construct FAIL 0002\n"; rc = false;
  }
  if( v3.size( ) != 0 || !v3.empty( ) || INSANE( v3 ) ) {
    std::cout << "construct FAIL 0003\n"; rc = false;
  }
  if( v4.size( ) != 10 || v4.empty( ) || INSANE( v4 ) ) {
    std::cout << "construct FAIL 0004\n"; rc = false;
  }
  if( v5.size( ) != 10 || v5.empty( ) || INSANE( v5 ) ) {
    std::cout << "construct FAIL 0005\n"; rc = false;
  }

  // Use checked access so that we get an exception if something's wrong.
  for( std::vector< int >::size_type i = 0; i < v5.size( ); ++i ) {
    if( v5.at( i ) != 1 ) {
      std::cout << "construct FAIL 0006\n"; rc = false;
    }
  }

  return( rc );
}

bool access_test( )
{
  using std::out_of_range;

  bool rc = true;
  std::vector< int > v(10);

  for (int i = 0; i < 10; ++i ) {
    v[i] = i;
  }
  for (int i = 0; i < 10; ++i ) {
    if( v[i] != i ) {
      std::cout << "access FAIL 0001\n";
    }
  }

  for (int i = 0; i < 10; ++i ) {
    v.at( i ) = i;
  }
  for (int i = 0; i < 10; ++i ) {
    if( v.at( i ) != i ) {
      std::cout << "access FAIL 0002\n";
    }
  }

  try {
    v.at( 10 ) = 0;
    std::cout << "access FAIL 0003\n";
  }
  catch( out_of_range ) {
    // Okay
  }

  return( rc );
}

bool assign_test( )
{
  bool rc = true;
  std::vector< int > v1(10, 1);
  std::vector< int > v2( 5, 2);
  std::vector< int > v3(15, 3);

  v1 = v2;
  if( v1.size( ) != 5  || INSANE( v1 ) ) {
    std::cout << "assign FAIL 0001\n"; rc = false;
  }
  for( std::vector< int >::size_type i = 0; i < v1.size( ); ++i ) {
    if( v1.at( i ) != 2 ) {
      std::cout << "assign FAIL 0002\n"; rc = false;
    }
  }

  v1 = v3;
  if( v1.size( ) != 15 || INSANE( v1 ) ) {
    std::cout << "assign FAIL 0003\n"; rc = false;
  }
  for( std::vector< int >::size_type i = 0; i < v1.size( ); ++i ) {
    if( v1.at( i ) != 3 ) {
      std::cout << "assign FAIL 0004\n"; rc = false;
    }
  }

  v1.assign( 10, 4 );
  if( v1.size( ) != 10 || INSANE( v1 ) ) {
    std::cout << "assign FAIL 0005\n"; rc = false;
  }
  for( std::vector< int >::size_type i = 0; i < v1.size( ); ++i ) {
    if( v1.at( i ) != 4 ) {
      std::cout << "assign FAIL 0006\n"; rc = false;
    }
  }

  v1.assign( 20, 5 );
  if( v1.size( ) != 20 || INSANE( v1 ) ) {
    std::cout << "assign FAIL 0007\n"; rc = false;
  }
  for( std::vector< int >::size_type i = 0; i < v1.size( ); ++i ) {
    if( v1.at( i ) != 5 ) {
      std::cout << "assign FAIL 0008\n"; rc = false;
    }
  }

  return( rc );
}

template< class Type >
bool pushback_test(Type *check, std::size_t check_size )
{
  using std::vector;  // Make sure this works.

  bool rc = true;
  vector< Type > vec;

  for( typename vector< Type >::size_type i = 0; i < check_size; ++i ) {
    vec.push_back( check[i] );
    if( vec.back( ) != check[i] ) {
      std::cout << "pushback FAIL 0001\n"; rc = false;
    }
    if( vec.front( ) != check[0] ) {
      std::cout << "pushback FAIL 0002\n"; rc = false;
    }
  }
  if( vec.size( ) != check_size || INSANE( vec ) ) {
    std::cout << "pushback FAIL 0003\n"; rc = false;
  }

  std::reverse( check, check + check_size );
  for( typename vector< Type >::size_type i = 0; i < check_size; ++i ) {
    if( vec.back( ) != check[i] ) {
      std::cout << "pushback FAIL 0004\n"; rc = false;
    }
    if( vec.front( ) != check[check_size - 1] ) {
      std::cout << "pushback FAIL 0005\n"; rc = false;
    }
    vec.pop_back( );
  }
  if( vec.size( ) != 0 || INSANE( vec ) ) {
    std::cout << "pushback FAIL 0006\n"; rc = false;
  }

  return( rc );
}

bool iterator_test( )
{
  bool rc = true;
  std::vector< int > vec(10);
  int counter;

  for(std::vector< int >::size_type i = 0; i < 10; ++i ) {
    vec[i] = i;
  }

  std::vector< int >::iterator p;

  counter = 0;
  for( p = vec.begin( ); p != vec.end( ); ++p ) {
    if( *p != counter ) {
      std::cout << "iterator FAIL 0001\n"; rc = false;
    }
    ++counter;
  }

  // Use p++ (probably a more exhaustive test should be created).
  counter = 0;
  for( p = vec.begin( ); p != vec.end( ); p++ ) {
    if( *p != counter ) {
      std::cout << "iterator FAIL 0002\n"; rc = false;
    }
    ++counter;
  }

  // Also run iterators backwards, do pointer arithmetic, compare, etc.

  return( rc );
}

bool insert_single_test( )
{
  bool rc = true;
  typedef std::vector< int >::size_type size_type;
  typedef std::vector< int >::iterator iterator;

  // Try inserting repeatedly at the beginning.
  std::vector< int > v1;
  size_type cap = v1.capacity( );
  int       lim = 4 * cap;
  iterator   it = v1.end( );

  for( int i = 0; i < lim; ++i ) {
    it = v1.insert( it, i );
    if( INSANE( v1 ) ) {
      std::cout << "insert_single FAIL 0001\n"; rc = false;
    }
  }
  int expected_value = lim - 1;
  for( size_type i = 0; i < lim; ++i ) {
    if( v1[i] != expected_value ) {
      std::cout << "insert_single FAIL 0002\n"; rc = false;
    }
    --expected_value;
  }

  // Try inserting repeatedly at the end.
  std::vector< int > v2;
  cap = v2.capacity( );
  lim = 4 * cap;
  it  = v2.end( );

  for( int i = 0; i < lim; ++i ) {
    it = v2.insert( it, i );
    ++it;
    if( INSANE( v2 ) ) {
      std::cout << "insert_single FAIL 0003\n"; rc = false;
    }
  }
  expected_value = 0;
  for( size_type i = 0; i < lim; ++i ) {
    if( v2[i] != expected_value ) {
      std::cout << "insert_single FAIL 0004\n"; rc = false;
    }
    ++expected_value;
  }

  // Add test case for repeated insertions in the middle.

  return( rc );
}

bool insert_multiple_test( )
{
  // This test considers vector's initial capacity of 16.
  bool rc = true;
  typedef std::vector< int >::size_type size_type;
  typedef std::vector< int >::iterator iterator;

  // Small insertion, no reallocation.
  std::vector< int > v1;
  v1.push_back( 1 ); v1.push_back( 2 ); v1.push_back( 3 ); v1.push_back( 4 );
  v1.insert( v1.begin( ), 1, -1 );
  if( v1.size( ) != 5 || INSANE( v1 ) ) {
    std::cout << "insert_multiple FAIL 0001\n"; rc = false;
  }
  for( size_type i = 0; i < v1.size( ); ++i ) {
    if( i == 0 && v1[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0002\n"; rc = false;
    }
    if( i != 0 && v1[i] != i ) {
      std::cout << "insert_multiple FAIL 0003\n"; rc = false;
    }
  }

  // Large insertion, no reallocation.
  std::vector< int > v2;
  v2.push_back( 1 ); v2.push_back( 2 ); v2.push_back( 3 ); v2.push_back( 4 );
  v2.insert( v2.begin( ), 4, -1 );
  if( v2.size( ) != 8 || INSANE( v2 ) ) {
    std::cout << "insert_multiple FAIL 0004\n"; rc = false;
  }
  for( size_type i = 0; i < v2.size( ); ++i ) {
    if( i < 4 && v2[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0005\n"; rc = false;
    }
    if( i >= 4 && v2[i] != i - 3 ) {
      std::cout << "insert_multiple FAIL 0006\n"; rc = false;
    }
  }

  // Very large insertion, no reallocation.
  std::vector< int > v3;
  v3.push_back( 1 ); v3.push_back( 2 ); v3.push_back( 3 ); v3.push_back( 4 );
  v3.insert( v3.begin( ), 8, -1 );
  if( v3.size( ) != 12 || INSANE( v3 ) ) {
    std::cout << "insert_multiple FAIL 0007\n"; rc = false;
  }
  for( size_type i = 0; i < v3.size( ); ++i ) {
    if( i < 8 && v3[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0008\n"; rc = false;
    }
    if( i >= 8 && v3[i] != i - 7 ) {
      std::cout << "insert_multiple FAIL 0009\n"; rc = false;
    }
  }

  // Insertion at the end, no reallocation.
  std::vector< int > v4;
  v4.push_back( 1 ); v4.push_back( 2 ); v4.push_back( 3 ); v4.push_back( 4 );
  v4.insert( v4.end( ), 8, -1 );
  if( v4.size( ) != 12 || INSANE( v4 ) ) {
    std::cout << "insert_multiple FAIL 0010\n"; rc = false;
  }
  for( size_type i = 0; i < v4.size( ); ++i ) {
    if( i < 4 && v4[i] != i + 1 ) {
      std::cout << "insert_multiple FAIL 0011\n"; rc = false;
    }
    if( i >= 4 && v4[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0012\n"; rc = false;
    }
  }

  // Do a no-reallocation insertion in the middle as well?

  // Insertion at beginning, reallocation necessary.
  std::vector< int > v5;
  v5.push_back( 1 ); v5.push_back( 2 ); v5.push_back( 3 ); v5.push_back( 4 );
  v5.insert( v5.begin( ), 32, -1 );
  if( v5.size( ) != 36 || INSANE( v5 ) ) {
    std::cout << "insert_multiple FAIL 0013\n"; rc = false;
  }
  for( size_type i = 0; i < v5.size( ); ++i ) {
    if( i < 32 && v5[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0014\n"; rc = false;
    }
    if( i >= 32 && v5[i] != i - 31 ) {
      std::cout << "insert_multiple FAIL 0015\n"; rc = false;
    }
  }

  // Insertion at end, reallocation necessary.
  std::vector< int > v6;
  v6.push_back( 1 ); v6.push_back( 2 ); v6.push_back( 3 ); v6.push_back( 4 );
  v6.insert( v6.end( ), 32, -1 );
  if( v6.size( ) != 36 || INSANE( v6 ) ) {
    std::cout << "insert_multiple FAIL 0016\n"; rc = false;
  }
  for( size_type i = 0; i < v6.size( ); ++i ) {
    if( i < 4 && v6[i] != i + 1 ) {
      std::cout << "insert_multiple FAIL 0017\n"; rc = false;
    }
    if( i >= 4 && v6[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0018\n"; rc = false;
    }
  }

  // Insertion in the middle, reallocation necessary.
  std::vector< int > v7;
  v7.push_back( 1 ); v7.push_back( 2 ); v7.push_back( 3 ); v7.push_back( 4 );
  v7.insert( v7.begin( ) + 2, 32, -1 );
  if( v7.size( ) != 36 || INSANE( v7 ) ) {
    std::cout << "insert_multiple FAIL 0019\n"; rc = false;
  }
  for( size_type i = 0; i < v7.size( ); ++i ) {
    if( i < 2 && v7[i] != i + 1 ) {
      std::cout << "insert_multiple FAIL 0020\n"; rc = false;
    }
    if( i >= 2 && i < 34 && v7[i] != -1 ) {
      std::cout << "insert_multiple FAIL 0021\n"; rc = false;
    }
    if( i >= 34 && v7[i] != i - 31 ) {
      std::cout << "insert_multiple FAIL 0022\n"; rc = false;
    }
  }

  return( rc );
}

bool erase_test( )
{
  bool rc = true;

  std::vector< int > v1;
 
  v1.push_back( 5 );
  v1.erase( v1.begin( ) );
  if( v1.size( ) != 0 || INSANE( v1 ) ) {
    std::cout << "erase FAIL 0001\n"; rc = false;
  }

  v1.push_back( 6 ); v1.push_back( 7 );
  v1.erase( v1.end( ) - 1 );
  if( v1.size( ) != 1 || v1[0] != 6 || INSANE( v1 ) ) {
    std::cout << "erase FAIL 0002\n"; rc = false;
  }

  v1.push_back( 8 );
  v1.erase( v1.begin( ) );
  if( v1.size( ) != 1 || v1[0] != 8 || INSANE( v1 ) ) {
    std::cout << "erase FAIL 0003\n"; rc = false;
  }

  std::vector< int > v2;
  v2.push_back( 1 ); v2.push_back( 2 ); v2.push_back( 3 );
  v2.erase( v2.begin( ), v2.begin( ) + 2 );
  if( v2.size( ) != 1 || v2[0] != 3 || INSANE( v2 ) ) {
    std::cout << "erase FAIL 0004\n"; rc = false;
  }

  v2.push_back( 2 ); v2.push_back( 1 );
  v2.erase( v2.begin( ) + 1, v2.begin( ) + 3 );
  if( v2.size( ) != 1 || v2[0] != 3 || INSANE( v2 ) ) {
    std::cout << "erase FAIL 0005\n"; rc = false;
  }
  return( rc );
}

bool relational_test( )
{
  bool rc = true;

  // These initializations are crude, but good enough for now.
  std::vector< char > s1;
  s1.push_back( 'a' ); s1.push_back( 'b' );
  s1.push_back( 'c' ); s1.push_back( 'd' );

  std::vector< char > s2;
  s2.push_back( 'a' ); s2.push_back( 'b' );
  s2.push_back( 'c' ); s2.push_back( 'd' );

  std::vector< char > s3;
  s3.push_back( 'a' ); s3.push_back( 'b' );
  s3.push_back( 'c' ); s3.push_back( 'c' );

  std::vector< char > s4;
  s4.push_back( 'a' ); s4.push_back( 'b' );
  s4.push_back( 'c' ); s4.push_back( 'e' );

  std::vector< char > s5;
  s5.push_back( 'a' ); s5.push_back( 'b' );
  s5.push_back( 'c' );

  std::vector< char > s6;
  s6.push_back( 'a' ); s6.push_back( 'b' );
  s6.push_back( 'c' ); s6.push_back( 'd' );
  s6.push_back( 'e' );

  // Operator==
  if( !( s1 == s2 ) ) {
    std::cout << "relational FAIL 0001\n"; rc = false;
  }
  if(  ( s1 == s5 ) ) {
    std::cout << "relational FAIL 0002\n"; rc = false;
  }

  // Operator !=
  if(  ( s1 != s2 ) ) {
    std::cout << "relational FAIL 0003\n"; rc = false;
  }
  if( !( s5 != s1 ) ) {
    std::cout << "relational FAIL 0004\n"; rc = false;
  }

  // Operator<
  if(  ( s1 < s2 ) ) {
    std::cout << "relational FAIL 0005\n"; rc = false;
  }
  if( !( s3 < s1 ) ) {
    std::cout << "relational FAIL 0006\n"; rc = false;
  }
  if(  ( s4 < s1 ) ) {
    std::cout << "relational FAIL 0007\n"; rc = false;
  }
  if( !( s5 < s1 ) ) {
    std::cout << "relational FAIL 0008\n"; rc = false;
  }
  if(  ( s4 < s6 ) ) {
    std::cout << "relational FAIL 0009\n"; rc = false;
  }

  // Operator>
  if( !( s4 > s3 ) ) {
    std::cout << "relational FAIL 0010\n"; rc = false;
  }
  if(  ( s1 > s6 ) ) {
    std::cout << "relational FAIL 0011\n"; rc = false;
  }
  
  // Operator <=
  if( !( s1 <= s2 && s3 <= s2 ) ) {
    std::cout << "relational FAIL 0012\n"; rc = false;
  }
  if(  ( s2 <= s3 || s6 <= s5 ) ) {
    std::cout << "relational FAIL 0013\n"; rc = false;
  }

  // Operator>=
  if( !( s2 >= s1 && s6 >= s5 ) ) {
    std::cout << "relational FAIL 0014\n"; rc = false;
  }
  if(  ( s3 >= s4 || s5 >= s4 ) ) {
    std::cout << "relatioanl FAIL 0015\n"; rc = false;
  }

  return( rc );
}

bool swap_test( )
{
  bool rc = true;

  std::vector< int > v1, v2;
  v1.push_back(  1 ); v1.push_back(  2 );
  v2.push_back( 10 ); v2.push_back( 20 );

  v1.swap( v2 );
  if( v1[0] != 10 || v1[1] != 20 || INSANE( v1 ) ) {
    std::cout << "swap FAIL 0001\n"; rc = false;
  }
  if( v2[0] !=  1 || v2[1] !=  2 || INSANE( v2 ) ) {
    std::cout << "swap FAIL 0002\n"; rc = false;
  }

  #ifdef __NEVER
  std::swap( v1, v2 );
  if( v1[0] !=  1 || v1[1] !=  2 || INSANE( v1 ) ) {
    std::cout << "swap FAIL 0003\n"; rc = false;
  }
  if( v2[0] != 10 || v2[1] != 20 || INSANE( v2 ) ) {
    std::cout << "swap FAIL 0004\n"; rc = false;
  }
  #endif

  return( rc );
}

bool clear_test( )
{
  bool rc = true;

  std::vector< int > vec;
  vec.push_back( 1 ); vec.push_back( 2 ); vec.push_back( 3 );

  vec.clear( );
  if( vec.size( ) != 0 || INSANE( vec ) ) {
    std::cout << "clear FAIL 0001\n"; rc = false;
  }

  return( rc );
}

int main( )
{
  // Probably the entire test suite should be a template so that all
  // tests can be run using both structured and unstructed types. For
  // now this is better than nothing.
  //
  static int int_check[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
  const std::size_t int_check_size =
    sizeof( int_check )/sizeof( int );

  static std::string string_check[] = {
    "abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx", "yz" };
  const std::size_t string_check_size =
    sizeof( string_check )/sizeof( std::string );

  int rc = 0;
  try {
    if( !construction_test( )    || !heap_ok( "t01" ) ) rc = 1;
    if( !access_test( )          || !heap_ok( "t02" ) ) rc = 1;
    if( !assign_test( )          || !heap_ok( "t03" ) ) rc = 1;
    if( !pushback_test( int_check, int_check_size ) ||
          !heap_ok( "t4" ) ) rc = 1;
    if( !pushback_test( string_check, string_check_size ) ||
          !heap_ok( "t5" ) ) rc = 1;
    if( !iterator_test( )        || !heap_ok( "t06" ) ) rc = 1;
    if( !insert_single_test( )   || !heap_ok( "t07" ) ) rc = 1;
    if( !insert_multiple_test( ) || !heap_ok( "t08" ) ) rc = 1;
    if( !erase_test( )           || !heap_ok( "t09" ) ) rc = 1;
    if( !relational_test( )      || !heap_ok( "t10" ) ) rc = 1;
    if( !swap_test( )            || !heap_ok( "t11" ) ) rc = 1;
    if( !clear_test( )           || !heap_ok( "t12" ) ) rc = 1;
  }
  catch( ... ) {
    std::cout << "Unexpected exception of unexpected type.\n";
    rc = 1;
  }

  return( rc );
}
