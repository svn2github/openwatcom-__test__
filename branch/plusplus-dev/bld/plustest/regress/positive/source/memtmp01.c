#include "fail.h"

static const int C = 3;

struct A
{
    static const int C = 2;

    template< class T >
    int f( T t )
    {
        return 2*t;
    }

    int f( short s )
    {
        return 4*s;
    }

    int f( int i )
    {
        return 3*i;
    }

    template< class T >
    int g( int i, T t )
    {
        return i + t + T();
    }

    template< int i >
    int h()
    {
        return 5*i + C;
    }
};

template< class T >
struct B
    : public A
{ };

int main()
{
    A a;

    if( a.f(1) != 3 ) fail( __LINE__ );
    if( a.f((short) 1) != 4 ) fail( __LINE__ );
    if( a.f<>(1) != 2 ) fail( __LINE__ );
    if( a.f<int>(1) != 2 ) fail( __LINE__ );
    if( a.f<int>((short) 1) != 2 ) fail( __LINE__ );
    if( a.g((short) 1, (short) 2) != 3 ) fail( __LINE__ );
    if( a.h<3>() != 17 ) fail( __LINE__ );

    B< int > b;

    if( b.f(1) != 3 ) fail( __LINE__ );
    if( b.f((short) 1) != 4 ) fail( __LINE__ );
    if( b.f<>(1) != 2 ) fail( __LINE__ );
    if( b.f<int>(1) != 2 ) fail( __LINE__ );
    if( b.f<int>((short) 1) != 2 ) fail( __LINE__ );
    if( b.g((short) 1, (short) 2) != 3 ) fail( __LINE__ );
    if( b.h<3>() != 17 ) fail( __LINE__ );

    _PASS;
}
