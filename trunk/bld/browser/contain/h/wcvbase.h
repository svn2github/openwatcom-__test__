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


//
//  wcvbase.h    Definitions for the base classes used by
//               the WATCOM Container Vector Class
//
//  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
//

#ifndef _WCVBASE_H_INCLUDED

#ifndef __cplusplus
#error wcvbase.h is for use with C++
#endif



//
//  constants used by vector classes
//


//
//  The default number of elements a vector is created to store.  Specifying
//  the first parameter to the vector constructors will override this value.
//
const size_t WCDEFAULT_VECTOR_LENGTH = 10;

//
//  The default number of elements a vector will grow by when an element is
//  inserted into a full vector (the number of entries in the vector is
//  the same as the vector length).  This growth is performed using the
//  resize member function.
//  This constant applies only ordered and sorted vectors with the
//  resize_required exception disabled.
//  Specifying the second paramter to the ordered and sorted vector
//  constructors will override this value.
//
const size_t WCDEFAULT_VECTOR_RESIZE_GROW = 5;



//
//  Implementation note:
//  From the user's view, all vector elements have been constructed
//  (possibly with only the default constructor).
//
//  In order to avoid any overhead from default intializing and then
//  immediately assigning a value to a vector element, the C-array used
//  to implement arrays is uninitialized (contains raw memory with none
//  of Type's constuctors called) until it needs to be.  This means
//  more effiecent copy constucters can be used, and default constuctors
//  do not get called unless they need to.  This is especially helpfull
//  for the resize member function.
//  Initializing previously allocated chunks of memory requires calling the
//  new operator with the allocated memory as a placement syntax parameter.
//  If Type defines an operator new with any parameters, then Type must
//  provide the following operator new for the vector classes:
//  void *operator new( size_t, void *ptr ) { return ptr; }
//  WCValVector and WCPtrVector are implemented so that whenever the user
//  accesses an element which has not been initialized, all uninitalized
//  elements upto and including the accessed element are initialized using
//  Type's default constructor.
//  ordered and sorted vectors do not have this "random access" issue, since
//  the index operator can only index previously initialized elements.  The
//  last element in a vector is copied in using the copy constructor on and
//  each insert, and the last element(s) in a vector is/are destructed after
//  a remove is performed, so that the number of initialized elements in a
//  vector is always equal to the number of entries in the vector.
//




//
//  This class is the base class for all vector container classes.
//  WCExcept provides common exception handling for all vectors.
//
//  It is an abstract base class to prevent objects of this class
//  from being created.
//

template<class Type>
class WCBareVectorBase : public WCExcept {
protected:
    Type *vector;
    int vector_len;
    int num_init;

    // WCValVector, WCPtrVector assignment operator base
    void base_assign( const WCBareVectorBase * );
    // WCValVector, WCPtrVector copy constructor base
    void base_construct( const WCBareVectorBase * );
    int base_index_check( int ) const;
    virtual void base_init_upto( int );
public:
    WCBareVectorBase( size_t length );
    virtual ~WCBareVectorBase() = 0;

    int operator==( const WCBareVectorBase & rhs ) const {
        return( this == &rhs );
    };

    inline void clear() {
        resize( 0 );
    };

    WCbool resize( size_t new_length );
};


template<class Type>
void WCBareVectorBase<Type>::base_assign( const WCBareVectorBase * orig ) {
    if( this != orig ) {
        resize( 0 );
        base_construct( orig );
    }
};


template<class Type>
void WCBareVectorBase<Type>::base_construct( const WCBareVectorBase * orig ) {
    WCExcept::base_construct( orig );
    num_init = orig->num_init;
    vector_len = orig->vector_len;
    if( vector_len > 0 ) {
        // get the raw memory for the vector's C-array
        vector = ( Type * )new char[ sizeof( Type ) * vector_len ];
        if( vector != 0 ) {
            for( int i = 0; i < num_init; i++ ) {
                // Copy all initialized elements from orig to vector, using
                // Type's copy constructor.  The placement parameter is used
                // so that the C-array's raw memory is initialized, instead
                // of allocating a new chunck of memory.
                new( &( vector[ i ] ) ) Type( orig->vector[ i ] );
            }
        } else {
            num_init = 0;
            vector_len = 0;
            base_throw_out_of_memory();
        }
    } else {
        vector = 0;
    }
};


template<class Type>
int WCBareVectorBase<Type>::base_index_check( int index ) const {
    int entry_index = vector_len - 1;
    if( index < 0 || index > entry_index ) {
        base_throw_index_range();
        if( index < 0 ) {
            index = 0;
        } else {
            if( entry_index <= 0 ) {
                index = 0;
            } else {
                index = entry_index;
            }
        }
    }
    return( index );
};


//
//  Initialize all unintialized elements upto and including the index'th
//  element using Type's default constructor.
//

template<class Type>
void WCBareVectorBase<Type>::base_init_upto( int index ) {
    if( index >= num_init ){
        for( int i = num_init; i <= index; i++ ){
            // initialize elements using Type's default constructor.  The
            // placement parameter is used so that the C-array's raw memory
            // is initialized, instead of allocating a new chunck of memory.
            new( &( vector[ i ] ) ) Type();
        }
        num_init = index + 1;
    }
}


template<class Type>
WCBareVectorBase<Type>::WCBareVectorBase( size_t length ){
    vector_len = length;
    num_init = 0;
    if( length > 0 ){
        // get the raw memory for the vector's C-array
        vector = ( Type * )new char[ sizeof( Type ) * length ];
        if( vector == 0 ) {
            vector_len = 0;
        }
    } else {
        vector = 0;
    }
};


template<class Type>
virtual WCBareVectorBase<Type>::~WCBareVectorBase() {
    if( vector ) {
        base_throw_not_empty();
        // call destructors for any initialized elements
        for( int i = 0; i < num_init; i++ ){
            vector[ i ].~Type();
        }
        // delete the C-array (now just raw memory)
        delete (void *)vector;
    }
};


template<class Type>
WCbool WCBareVectorBase<Type>::resize( size_t new_length ) {
    Type *new_vector;
    int max_index = num_init < new_length ? num_init : new_length;

    if( new_length > 0 ) {
        // get the raw memory for the vector's C-array
        new_vector = ( Type * )new char[ sizeof( Type ) * new_length ];
        if( new_vector == 0 ){
            base_throw_out_of_memory();
            return( FALSE );
        }
        // Copy all initialized elements from vector (the old C-array) to
        // new_vector (the new C-array), using Type's copy constructor.
        // The placement parameter is used so that the C-array's raw memory
        // is initialized, instead of allocating a new chunck of memory.
        for( int i = 0; i < max_index; i++ ){
            new( &( new_vector[ i ] ) ) Type( vector[ i ] );
        }
    } else {
        new_vector = 0;
    }
    // call destructors for any initialized elements in the old vector
    for( int i = 0; i < num_init; i++ ){
        vector[ i ].~Type();
    }
    // delete the old C-array (now just raw memory)
    delete (void *) vector;
    num_init = max_index;
    vector = new_vector;
    vector_len = new_length;
    return( TRUE );
};


//
//  This class is the base class for Ptr and Val OrderedVector and SortedVector
//  container classes.
//
//  It is an abstract base class to prevent objects of this class
//  from being created.
//

template<class Type>
class WCVectorBase : public WCBareVectorBase<Type> {
protected:
    unsigned num_entries;
    unsigned resize_grow;       // the number of elements to grow a vector
                                // when inserting into a full vector

    enum find_type {            // for the base_find function
        find_any,               // find any matching element in the vector
        find_first,             // find first matching element in vector
        next_mult_find,         // find next matching element in vector
        find_for_insert };      // find index to insert element in sorted vector

    // the assignment operator base
    void base_assign( const WCVectorBase * );
    // the copy constructor base
    void base_construct( const WCVectorBase * );
    virtual int base_equivalent( const Type &elem1
                               , const Type &elem2 ) const = 0;
    // find first parm in vector, with specified find_type.  index passes
    // in where to start the search, and returns the index where first param
    // found if returns true
    virtual WCbool base_find( const Type &, find_type, int * index ) const = 0;
    int base_index_check( int ) const;
    WCbool base_insert_at( int, const Type& );
    void base_remove_at( int );

public:
    inline WCVectorBase( size_t length, unsigned grow )
                        : num_entries( 0 ), resize_grow( grow ),
                                WCBareVectorBase<Type>( length ) {};
    inline virtual ~WCVectorBase() = 0;

    inline void clear() {
        WCBareVectorBase::clear();
        num_entries = 0;
    };

    WCbool contains( const Type & ) const;

    inline unsigned entries() const {
        return( num_entries );
    };

    WCbool find( const Type &elem, Type &ret_val ) const;

    inline Type first() const {
        return( vector[ base_index_check( 0 ) ] );
    }

    int index( const Type & ) const;

    inline WCbool isEmpty() const {
        return( num_entries == 0 );
    };

    inline Type last() const {
        return( vector[ base_index_check( num_entries - 1 ) ] );
    }

    int occurrencesOf( const Type & elem ) const;

    WCbool remove( const Type & elem );

    unsigned removeAll( const Type & elem );

    WCbool removeAt( int );

    inline WCbool removeFirst() {
        return( removeAt( 0 ) );
    };

    inline WCbool removeLast() {
        return( removeAt( num_entries - 1 ) );
    };

    WCbool resize( size_t );

    inline Type& operator[] ( int index ) {
        return( vector[ base_index_check( index ) ] );
    };

    inline const Type& operator[] ( int index ) const {
        return( vector[ base_index_check( index ) ] );
    };
};


template<class Type>
void WCVectorBase<Type>::base_assign( const WCVectorBase * orig ) {
    if( this != orig ) {
        resize( 0 );
        base_construct( orig );
    }
};


template<class Type>
void WCVectorBase<Type>::base_construct( const WCVectorBase * orig ) {
    WCBareVectorBase<Type>::base_construct( orig );
    resize_grow = orig->resize_grow;
    if( vector != 0 ) {
        num_entries = orig->num_entries;
    } else {
        num_entries = 0;
    }
}


//
//  Check to see if index is valid, and return the closest valid index.
//  If index is invalid then exceptions are thrown if enabled, and if
//  exceptions are disabled and the vector has no entries, then the first
//  element is default initialized, effectively inserting a first element
//  (this is done for the index operators and first and last member
//  functions)
//
template<class Type>
int WCVectorBase<Type>::base_index_check( int index ) const {
    int entry_index = num_entries - 1;
    if( index < 0 || index > entry_index ) {
        if( num_entries == 0 ) {
            base_throw_empty_container();
            base_throw_index_range();
            // insert the first element as a default intialized element
            WCVectorBase<Type> * const non_const_this
                    = ( WCVectorBase<Type> * )this;
            if( vector_len == 0 ) {
                if( !non_const_this->resize( 1 ) ) {
                    // An invalid operation on an empty vector, and out memory.
                    // return the first element of a NULL C-array.
                    return( 0 );
                }
            }
            non_const_this->base_init_upto( 0 );
            non_const_this->num_entries = 1;
            index = 0;
        } else if( index < 0 ) {
            index = 0;
            base_throw_index_range();
        } else {
            index = entry_index;
            base_throw_index_range();
        }
    }
    return( index );
};


//
//  insert new_entry before the element currently at index.  If index is the
//  number of entries, insert new_entry as the last element.
//

template<class Type>
WCbool WCVectorBase<Type>::base_insert_at( int index, const Type& new_entry ) {
    if( index > (int)num_entries ) {
        base_throw_index_range();
        index = num_entries;
    } else if( index < 0 ) {
        base_throw_index_range();
        index = 0;
    }
    if( num_entries == vector_len ){
        base_throw_resize_required();
        // automatically grow the vector if it was full, the resize_required
        // exception is disabled, and the amount to grow the vector is greater
        // than zero.
        if( ( resize_grow == 0 )
          ||( !resize( vector_len + resize_grow ) ) ) {
            return( FALSE );
        }
    }
    // the last entry in the vector must be copied in, since it was previously
    // unused, and unused elements are unitialized.
    if( index == num_entries ){
        new( &( vector[ index ] ) ) Type( new_entry );
    } else {
        new( &( vector[ num_entries ] ) ) Type( vector[ num_entries - 1 ] );
        for( int i = num_entries - 2; i >= index; i-- ) {
            vector[ i + 1 ] = vector[ i ];
        }
        vector[ index ] = new_entry;
    }
    num_entries++;
    num_init++;
    return( TRUE );
}


template<class Type>
void WCVectorBase<Type>::base_remove_at( int index ) {
    for( int i = index; i < num_entries - 1; i++ ) {
        vector[ i ] = vector[ i + 1 ];
    }
    // destruct the last element in the array, so that unused elements are
    // unitialized.
    vector[ num_entries - 1 ].~Type();
    num_entries--;
    num_init--;
}


template<class Type>
WCVectorBase<Type>::~WCVectorBase() {};


template<class Type>
WCbool WCVectorBase<Type>::contains( const Type &elem ) const {
    int index = 0;

    if( ( num_entries != 0 )
      &&( base_find( elem, find_any, &index ) ) ) {
        return( TRUE );
    } else {
        return( FALSE );
    }
}


template<class Type>
WCbool WCVectorBase<Type>::find( const Type &elem, Type &ret_val ) const {
    int index = 0;
    if( ( num_entries > 0 )
      &&( base_find( elem, find_first, &index ) ) ) {
        ret_val = vector[ index ];
        return( TRUE );
    } else {
        Type temp;
        ret_val = temp;
        return( FALSE );
    }
};


template<class Type>
int WCVectorBase<Type>::index( const Type & elem ) const {
    int ret_index = 0;

    if( ( num_entries > 0 )
      &&( base_find( elem, find_first, &ret_index ) ) ) {
        return( ret_index );
    } else {
        return( -1 );
    }
}


template<class Type>
int WCVectorBase<Type>::occurrencesOf( const Type & elem ) const {
    int index = 0;
    int count = 0;

    if( ( num_entries > 0 )
      &&( base_find( elem, find_first, &index ) ) ) {
        do {
            count++;
            index++;
        } while( base_find( elem, next_mult_find, &index ) );
    }
    return( count );
};


template<class Type>
WCbool WCVectorBase<Type>::remove( const Type & elem ) {
    int index = 0;

    if( ( num_entries > 0 )
      &&( base_find( elem, find_first, &index ) ) ) {
        base_remove_at( index );
        return( TRUE );
    } else {
        return( FALSE );
    }
};


template<class Type>
unsigned WCVectorBase<Type>::removeAll( const Type & elem ) {
    int found_index = 0;
    int count = 0;

    // make sure only elements which need to be moved are moved
    // no element is moved more than once
    if( ( num_entries > 0 )
      &&( base_find( elem, find_first, &found_index ) ) ) {
        // at least one element is being removed
        int curr_index = found_index;
        count++;
        found_index++;
        while( base_find( elem, next_mult_find, &found_index ) ) {
            // move entries which were between any occurrances of elem
            for( ;curr_index < found_index - count; curr_index++ ){
                vector[ curr_index ] = vector[ curr_index + count ];
            }
            count++;
            found_index++;
        };
        // move entries after any occurances of elem
        for( ;curr_index < num_entries - count; curr_index++ ){
            vector[ curr_index ] = vector[ curr_index + count ];
        }
        // destruct elements at the end of the vector which were copied or
        // removed, so that unused elements are unitialized
        for( ;curr_index < num_entries; curr_index++ ){
            vector[ curr_index ].~Type();
        }
        num_entries -= count;
        num_init -= count;
    }
    return( count );
}



template<class Type>
WCbool WCVectorBase<Type>::removeAt( int index ) {
    if( num_entries == 0 ) {
        base_throw_empty_container();
        return( FALSE );
    } else {
        index = base_index_check( index );
        base_remove_at( index );
        return( TRUE );
    }
};


template<class Type>
WCbool WCVectorBase<Type>::resize( size_t new_length ) {
    WCbool return_val = WCBareVectorBase<Type>::resize( new_length );
    if( return_val && num_entries > new_length ){
        num_entries = new_length;
    }
    return( return_val );
};




//
// WCOrderedVectorBase  - this is the base class for WCValOrderedVector and
//                        WCPtrOrderedVector.
//
// This is a abstract class to prevent objects of this type being created
//

template <class Type>
class WCOrderedVectorBase : public WCVectorBase<Type> {
protected:
    virtual WCbool base_find( const Type &, find_type, int * ) const;
public:
    inline WCOrderedVectorBase( size_t length, unsigned default_grow )
                        : WCVectorBase<Type>( length, default_grow ) {};

    inline virtual ~WCOrderedVectorBase() = 0;

    inline WCbool append( const Type& new_elem ){
        return( insert( new_elem ) );
    };

    inline WCbool insert( const Type& new_elem ){
        return( base_insert_at( num_entries, new_elem ) );
    };

    inline WCbool insertAt( int index, const Type& new_elem ){
        return( base_insert_at( index, new_elem ) );
    };

    inline WCbool prepend( const Type& new_elem ){
        return( base_insert_at( 0, new_elem ) );
    };

};


template <class Type>
WCOrderedVectorBase<Type>::~WCOrderedVectorBase() {};


template <class Type>
WCbool WCOrderedVectorBase<Type>::base_find( const Type &elem, find_type
                                , int *st_found_index ) const {
    int index = *st_found_index;

    while( index < num_entries ) {
         if( base_equivalent( vector[ index ], elem ) ) {
             *st_found_index = index;
             return( TRUE );
         }
         index++;
    }
    return( FALSE );
};




//
// WCSortedVectorBase   - this is the base class for WCValSortedVector and
//                        WCPtrSortedVector.
//
// This is a abstract class to prevent objects of this type being created
//

template <class Type>
class WCSortedVectorBase : public WCVectorBase<Type> {
protected:
    virtual WCbool base_find( const Type &, find_type, int * ) const;
    virtual int base_less_than( const Type& elem1
                              , const Type& elem2 ) const = 0;
public:
    inline WCSortedVectorBase( size_t length, unsigned default_grow )
                        : WCVectorBase<Type>( length, default_grow ) {};

    inline virtual ~WCSortedVectorBase() = 0;

    WCbool insert( const Type& );
};


template <class Type>
WCSortedVectorBase<Type>::~WCSortedVectorBase() {};


template <class Type>
WCbool WCSortedVectorBase<Type>::base_find( const Type &elem, find_type type
        , int * st_found_index ) const {
    // for multiple searches, check to see next element also matches
    if( type == next_mult_find ) {
        int index = *st_found_index;
        if( ( index < num_entries )
          &&( base_equivalent( vector[ index ], elem ) ) ) {
             return( TRUE );
        }
        return( FALSE );
    }

    // the binary search
    int low_bound = 0;
    int up_bound = num_entries - 1;
    int bisector;
    while( low_bound < up_bound ) {
        // bisector must be calculated so that it is less than up_bound
        bisector = ( up_bound - low_bound ) / 2 + low_bound;
        if( base_less_than( vector[ bisector ], elem ) ) {
            low_bound = bisector + 1;
        } else {
            up_bound = bisector;
        }
    }

    bisector = low_bound;
    // if we found elem, the first match is at index bisector

    if( base_equivalent( elem, vector[ bisector ] ) ) {
        // found match, bisector is the first match
        if( type == find_for_insert ) {
            while( ( bisector < num_entries )
                 &&( base_equivalent( vector[ bisector ], elem ) ) ) {
                bisector++;
            }
        }
        *st_found_index = bisector;
        return( TRUE );
    }

    // search failed, if find for insert make sure we are *after* elem
    if( type == find_for_insert ){
        if( base_less_than( vector[ bisector ], elem ) ) {
            bisector++;
        }
        *st_found_index = bisector;
    }
    return( FALSE );
}


template <class Type>
WCbool WCSortedVectorBase<Type>::insert( const Type& elem ) {
    int index = 0;

    if( num_entries > 0 ) {
        base_find( elem, find_for_insert, &index );
    }
    return( base_insert_at( index, elem ) );
};




//
// WCPtrVectorBase      - this is a base class for WCPtrOrderedVector and
//                        WCPtrSortedVector.
//
// This is a abstract class to prevent objects of this type being created
//
// Implementation note:
// All WCPtrOrdered vectors and WCPtrSorted vectors inherit from WCVectorBase
// templated over <void *>.  This saves most of the vector code being
// generated for pointer vectors templated over different types, speeding
// up compile time, and reducing code size.
//

template <class Type, class BaseClass>
class WCPtrVectorBase : public BaseClass {
protected:
    typedef Type * __Type_Ptr;
    typedef void * __Stored_Ptr;

    inline Type *base_ptr_remove_at( int index ) {
        Type *ret_ptr = (Type *)vector[ index ];
        base_remove_at( index );
        return( ret_ptr );
    }

    virtual void base_init_upto( int );

public:
    inline WCPtrVectorBase( size_t length, unsigned default_grow )
                        : BaseClass( length, default_grow ) {};

    inline virtual ~WCPtrVectorBase() = 0;

    void clearAndDestroy();

    inline WCbool contains( const Type * elem ) const {
        return( BaseClass::contains( (const __Type_Ptr)elem ) );
    };

    Type *find( const Type * elem ) const;

    inline Type *first() const {
        return( (Type *)BaseClass::first() );
    }

    inline int index( const Type * elem ) const {
        return( BaseClass::index( (const __Type_Ptr)elem ) );
    };

    inline Type *last() const {
        return( (Type *)BaseClass::last() );
    }

    int occurrencesOf( const Type * elem ) const {
        return( BaseClass::occurrencesOf( (const __Type_Ptr)elem ) );
    };

    Type *remove( const Type * elem );

    unsigned removeAll( const Type * elem ) {
        return( BaseClass::removeAll( (const __Type_Ptr)elem ) );
    };

    Type *removeAt( int index );

    inline Type *removeFirst() {
        return( removeAt( 0 ) );
    };

    inline Type *removeLast() {
        return( removeAt( num_entries - 1 ) );
    };

    inline Type * &operator[] ( int index ) {
        return( (Type * &)BaseClass::operator[]( index ) );
    };

    inline Type * const & operator[] ( int index ) const {
        return( (Type * const &)BaseClass::operator[]( index ) );
    };
};


template<class Type, class BaseClass>
void WCPtrVectorBase<Type, BaseClass>::base_init_upto( int index ) {
    if( index >= num_init ){
        // intialize the vector by NULLing out unitialized elements
        memset( &vector[ num_init ], 0
              , ( index + 1 - num_init ) * sizeof( void * ) );
        num_init = index + 1;
    }
}


template <class Type, class BaseClass>
WCPtrVectorBase<Type, BaseClass>::~WCPtrVectorBase() {};


template<class Type, class BaseClass>
void WCPtrVectorBase<Type, BaseClass>::clearAndDestroy() {
    for( unsigned i = 0; i < num_entries; i++ ) {
        delete( (Type *)vector[ i ] );
    }
    clear();
};


template<class Type, class BaseClass>
Type *WCPtrVectorBase<Type, BaseClass>::find( const Type * elem ) const {
    int index = 0;
    if( ( num_entries > 0 )
      &&( base_find( (const __Type_Ptr)elem, find_any, &index ) ) ) {
        return( (Type *)vector[ index ] );
    } else {
        return( 0 );
    }
};


template<class Type, class BaseClass>
Type *WCPtrVectorBase<Type, BaseClass>::remove( const Type *elem ) {
    int index = 0;

    if( ( num_entries > 0 )
      &&( base_find( (const __Type_Ptr)elem, find_first, &index ) ) ) {
        return( base_ptr_remove_at( index ) );
    } else {
        return( 0 );
    }
};


template<class Type, class BaseClass>
Type *WCPtrVectorBase<Type, BaseClass>::removeAt( int index ) {
    if( num_entries == 0 ) {
        base_throw_empty_container();
        return( 0 );
    } else {
        index = base_index_check( index );
        return( base_ptr_remove_at( index ) );
    }
};


#define _WCVBASE_H_INCLUDED
#endif
