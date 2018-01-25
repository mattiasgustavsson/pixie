#ifndef dictionary_hpp
#define dictionary_hpp


/* TODO: proper implementation using hash table */

#include "array.hpp"

namespace dictionary_ns {

template<typename KEY, typename T> struct entry_t 
	{
	KEY key;
	T value;
	};
		
#pragma warning( push ) 
#pragma warning( disable: 4619 ) // pragma warning : there is no warning number 'number'
#pragma warning( disable: 4217 ) // nonstandard extension used : function declaration from a previous block


template< typename KEY, typename T, int CAPACITY = 16 > 
struct dictionary : array_ns::array_type< entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD >
	{ 
	explicit dictionary() : 
		array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>( CAPACITY, pixie::internal::memctx() )
		{ 
		}
		
		
	template< typename U > dictionary( U const& other ) : 
		array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>( other ) 
		{			
		}
		
		
	template< typename U > explicit dictionary( U const* items, int count ) :
		array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>( items, count ) 
		{		
		}
		

    T const* find( KEY const& key ) const
        {
        for( int i = 0; i < count(); ++i )
			if( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).key == key )
				return &( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).value );
        }

    T* find( KEY const& key ) 
        {
        for( int i = 0; i < count(); ++i )
			if( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[](i).key == key )
				return &( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).value );
		return 0;
        }

    void remove( KEY const& key ) 
        {
        for( int i = 0; i < count(); ++i )
			if( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).key == key )
				array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::remove( i );
        }
        
		
	KEY const& key( int index ) const
		{
		return array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( index ).key;
		} 

	T& item( int index )
		{
		return array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( index ).value;
		} 

	T const& item( int index ) const
		{
		return array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( index ).value;
		} 

    T& operator[]( KEY const& key )
        {
        for( int i = 0; i < count(); ++i )
			if( array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).key == key )
				return array_ns::array_type<entry_t<KEY, T>, CAPACITY, array_ns::NOT_POD>::operator[]( i ).value;
			
		entry_t<KEY, T>& entry = add();
		entry.key = key;
		entry.value = T();
		return entry.value;
        }

    };

#pragma warning( pop ) 

} /* namespace dictionary_ns */


#endif // dictionary_hpp

