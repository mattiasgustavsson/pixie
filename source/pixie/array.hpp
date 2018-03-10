/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

array.hpp - v0.1 - Generic ordered array implementation for C++.

Do this:
	#define ARRAY_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef array_hpp
#define array_hpp

namespace array_ns {

namespace internal { template< typename T > struct align_helper { align_helper( align_helper const& ); char x; T y; }; }

enum POD_ENUM { IS_POD, NOT_POD };

template< typename T, int CAPACITY, POD_ENUM POD > 
struct array_type
	{
	explicit array_type( int initial_capacity = CAPACITY, void* memctx = 0 );
	~array_type();

	array_type( array_type<T, CAPACITY, POD> const& other );
	template< typename U > array_type( U const& other );
	template< typename U > array_type( U const* items, int count, void* memctx = 0  );

	array_type<T, CAPACITY, POD> const& operator= ( array_type<T, CAPACITY, POD> const& other );
	template< typename U > array_type<T, CAPACITY, POD> const& operator= ( U const& other );

	T& add( T const& item);
	T& add();
	T& insert( int index, T const& item);
	T& insert( int index );
	void set( int index, T const& item);
	void remove( int index );
	void unordered_remove( int index );
	void clear();
	void resize( int new_count, T const& item );
	void resize( int new_count );	
	void capacity_set( int capacity ) const;

	int capacity() const;
	int count() const;

	T& get( int index );
	T const& get( int index ) const;

	T& operator[]( int index );
	T const& operator[]( int index ) const;

	T* data();
	T const* data() const;

	bool contains( T const& item ) const;
				
		
	private:		
		// Specialized implementations for POD/NON-POD

		template< POD_ENUM P > struct implementation { };

		void ensure_capacity( implementation<NOT_POD>, int capacity );
		void ensure_capacity( implementation<IS_POD>, int capacity );

		T& add( implementation<NOT_POD>, T const& item );
		T& add( implementation<IS_POD>, T const& item );
		T& add( implementation<NOT_POD> );
		T& add( implementation<IS_POD> );

		T& insert( implementation<NOT_POD>, int index, T const& item );
		T& insert( implementation<IS_POD>, int index, T const& item );
		T& insert( implementation<NOT_POD>, int index );
		T& insert( implementation<IS_POD>, int index );

		void set( implementation<NOT_POD>, int index, T const& item );
		void set( implementation<IS_POD>, int index, T const& item );

		void remove( implementation<NOT_POD>, int index );
		void remove( implementation<IS_POD>, int index );
		void unordered_remove( implementation<NOT_POD>, int index );
		void unordered_remove( implementation<IS_POD>, int index );

		void clear( implementation<NOT_POD> );
		void clear( implementation<IS_POD> );

		void resize( implementation<NOT_POD>, int new_count, T const& item );
		void resize( implementation<IS_POD>, int new_count, T const& item );
		void resize( implementation<NOT_POD>, int new_count );
		void resize( implementation<IS_POD>, int new_count );


		template< typename U > void init( 
			implementation<NOT_POD>, U const* items, int count );
		template< typename U > void init( 
			implementation<IS_POD>, U const* items, int count );
		void init( implementation<IS_POD>, T const* items, int count );


		template< typename U > void copy( implementation<NOT_POD>, U const& other );
		template< typename U > void copy( implementation<IS_POD>, U const& other );
		template< typename U, int CAPACITY_OTHER, POD_ENUM POD_OTHER > void copy( 
			implementation<NOT_POD>, array_type<U, CAPACITY_OTHER, POD_OTHER> const& other );
		template< typename U, int CAPACITY_OTHER, POD_ENUM POD_OTHER > void copy( 
			implementation<IS_POD>, array_type<U, CAPACITY_OTHER, POD_OTHER> const& other );
		template< int CAPACITY_OTHER, POD_ENUM POD_OTHER > void copy( 
			implementation<IS_POD>, array_type<T, CAPACITY_OTHER, POD_OTHER> const& other );

	private:
		template< typename T, int CAPACITY = 16, POD_ENUM POD = NOT_POD > friend struct array_type;

		void* memctx_;
		int capacity_;
		int count_;
		T* items_;
		T* data_large_;
		
		#define ARRAY_ALIGNMENT_PADDING( T ) ( ( (size_t)&( ( ( internal::align_helper<T>*) 0 )->y ) ) - 1U )
		#define ARRAY_CAPACITY_FIX( x ) ( ( x ) > ( 0 ) ? ( x ) : ( 1 ) )
		unsigned char data_[ ARRAY_CAPACITY_FIX( CAPACITY * sizeof( T ) + ARRAY_ALIGNMENT_PADDING( T ) ) ];	
		#undef ARRAY_CAPACITY_FIX
		#undef ARRAY_ALIGNMENT_PADDING
	};


#pragma warning( push ) 
#pragma warning( disable: 4619 ) // pragma warning : there is no warning number 'number'
#pragma warning( disable: 4217 ) // nonstandard extension used : function declaration from a previous block

template< typename T, int CAPACITY = 16 > 
struct array : array_type< T, CAPACITY, NOT_POD >
	{ 
	explicit array( int initial_capacity = CAPACITY, void* memctx = 0 ) : array_type<T, CAPACITY, NOT_POD>( initial_capacity, memctx ) {}
	template< typename U > array( U const& other ) : array_type<T, CAPACITY, NOT_POD>( other ) {}
	template< typename U > array( U const* items, int count, void* memctx = 0 ) : array_type<T, CAPACITY, NOT_POD>( items, count, memctx ) {}
	};


template< typename T, int CAPACITY = 16 > 
struct pod_array : array_type< T, CAPACITY, IS_POD >
	{ 
	explicit pod_array( int initial_capacity = CAPACITY, void* memctx = 0 ) : array_type<T, CAPACITY, IS_POD>( initial_capacity, memctx ) {}
	template< typename U > pod_array( U const& other ) : array_type<T, CAPACITY, IS_POD>( other ) {}
	template< typename U > pod_array( U const* items, int count, void* memctx = 0  ) : array_type<T, CAPACITY, IS_POD>( items, count, memctx ) {}
	};

#pragma warning( pop ) 

} /*  namespace array_ns */


#endif /* array_hpp */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef array_impl
#define array_impl

// placement new
#if !defined( PLACEMENT_NEW_OPERATOR_DEFINED ) && !defined( __PLACEMENT_NEW_INLINE )
#define PLACEMENT_NEW_OPERATOR_DEFINED
#define __PLACEMENT_NEW_INLINE
inline void* operator new( size_t, void* p ) throw() { return p; } inline void operator delete(void*, void*) throw() { }
#endif 

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#ifndef ARRAY_ASSERT
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <assert.h>
	#define ARRAY_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

#ifndef ARRAY_MEMSET
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <string.h>
	#define ARRAY_MEMSET( ptr, val, cnt ) ( memset( ptr, val, cnt ) )
#endif 

#ifndef ARRAY_MEMCPY
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <string.h>
	#define ARRAY_MEMCPY( dst, src, cnt ) ( memcpy( dst, src, cnt ) )
#endif 

namespace array_ns { namespace internal {
	
void* array_malloc( void* ctx, size_t size );
void array_free( void* ctx, void* ptr );

template< typename T, POD_ENUM P > struct MUST_BE_POD { MUST_BE_POD() { } };
template< typename T > struct MUST_BE_POD<T, IS_POD >{ MUST_BE_POD() { union T_must_be_POD { T a; T b; }; } };

template< typename T > T* aligned_pointer( T* const ptr )
	{
	size_t const alignment = ( (size_t)&( ( ( internal::align_helper<T>*) 0 )->y ) );
	size_t const alignment_bits = alignment - 1U;
	return (T*) ( ( ( (uintptr_t) ptr ) + alignment_bits ) & ~alignment_bits );
	}

} /*  namespace internal */ } /*  namespace array_ns */


#ifdef _MSC_VER
	#define ARRAY_PODTEST_DISABLE_WARNING_CONSTANT_EXPRESSION \
		__pragma( warning( push ) ) \
		__pragma( warning( disable: 4127 ) )

	#define ARRAY_PODTEST_RESTORE_WARNING_LEVEL __pragma( warning( pop ) )
#else
	#define ARRAY_PODTEST_DISABLE_WARNING_CONSTANT_EXPRESSION
	#define ARRAY_PODTEST_RESTORE_WARNING_LEVEL
#endif


#define ARRAY_TEST_POD( T, POD_ENUM ) \
	ARRAY_PODTEST_DISABLE_WARNING_CONSTANT_EXPRESSION \
	while( 0 ) { internal::MUST_BE_POD<T, POD_ENUM> POD_TEST; (void) POD_TEST; } \
	ARRAY_PODTEST_RESTORE_WARNING_LEVEL

#define ARRAY_ERROR_IF_NOT_POD( T ) \
	ARRAY_PODTEST_DISABLE_WARNING_CONSTANT_EXPRESSION \
	while( 0 ) { internal::MUST_BE_POD<T, IS_POD> POD_TEST; (void) POD_TEST; } \
	ARRAY_PODTEST_RESTORE_WARNING_LEVEL


namespace array_ns {

// Constructor
template< typename T, int CAPACITY, POD_ENUM POD >
array_type<T, CAPACITY, POD>::array_type( int initial_capacity, void* memctx ):
	memctx_( memctx ),
	capacity_( initial_capacity == 0 ? 16 : initial_capacity ),
	count_( 0 ),
	data_large_( 0 ),
	items_( internal::aligned_pointer( (T*) data_ ) )
	{
	}	


// Destructor
template< typename T, int CAPACITY, POD_ENUM POD >
array_type<T, CAPACITY, POD>::~array_type()
	{
	clear( implementation<POD>() );
	if( data_large_ ) internal::array_free( memctx_, data_large_ );
	}


// Copy Constructor
template< typename T, int CAPACITY, POD_ENUM POD>   
array_type<T, CAPACITY, POD>::array_type( array_type<T, CAPACITY, POD> const& other ):
	memctx_( other.memctx_ ),
	capacity_( other.capacity_ ),
	count_( 0 ),
	data_large_( 0 ),
	items_( internal::aligned_pointer( (T*) data_ ) )
	{
	init( implementation<POD>(), other.data(), other.count() );
	}	


// Copy Constructor
template< typename T, int CAPACITY, POD_ENUM POD > template< typename U > 
array_type<T, CAPACITY, POD>::array_type( U const& other ):
	memctx_( other.memctx_ ),
	capacity_( other.capacity_ ),
	count_( 0 ),
	data_large_( 0 ),
	items_( internal::aligned_pointer( (T*) data_ ) )
	{
	init( implementation<POD>(), other.data(), other.count() );
	}


// Initializing Constructor
template< typename T, int CAPACITY, POD_ENUM POD > template< typename U >
array_type<T, CAPACITY, POD>::array_type( U const* items, int count, void* memctx ):
	memctx_( memctx ),
	capacity_( count_ ),
	count_( 0 ),
	data_large_( 0 ),
	items_( internal::aligned_pointer( (T*) data_ ) )
	{
	init( implementation<POD>(), items, count );
	}	


// operator=
template< typename T, int CAPACITY, POD_ENUM POD > 
array_type<T, CAPACITY, POD> const& array_type<T, CAPACITY, POD>::operator=( 
	array_type<T, CAPACITY, POD> const& other )
	{ 
	clear( implementation<POD>() );
	init( implementation<POD>(), other.data(), other.count() );
	return *this;
	}


// operator=
template< typename T, int CAPACITY, POD_ENUM POD > template< typename U > 
array_type<T, CAPACITY, POD> const& array_type<T, CAPACITY, POD>::operator=( U const& other )
	{ 
	clear( implementation<POD>() );
	init( implementation<POD>(), other.data(), other.count() );
	return *this;
	}


// ensure_capacity NOT POD
template< typename T, int CAPACITY, POD_ENUM POD >
void array_type<T, CAPACITY, POD>::ensure_capacity( implementation<NOT_POD>, int min_capacity )
	{
	if( min_capacity > CAPACITY && ( !data_large_ || min_capacity > capacity_ ) )
		{	
		int new_capacity = capacity_;
		while( new_capacity < min_capacity ) new_capacity *= 2;

		T* new_data = (T*) internal::array_malloc( memctx_, sizeof( T ) * new_capacity );
		ARRAY_ASSERT( new_data, "Allocation failed when allocating memory for array" );

		// copy each item from the old array to the new one
		for( int i = 0; i < count_; ++i )
			{
			// copy using placement new and copy constructor
			new ( new_data + i ) T( items_[ i ] );

			// Call destructor manually on items to be deleted
			items_[ i ].~T();
			}

		
		// Release memory for the old array
		if( data_large_ ) internal::array_free( memctx_, data_large_ );

		// Store the pointer to the new array instead of the old
		data_large_ = new_data;
		items_ = data_large_;

		// Increase the maximum number of items
		capacity_ = new_capacity;
		}

	}



// ensure_capacity POD
template< typename T, int CAPACITY, POD_ENUM POD >
void array_type<T, CAPACITY, POD>::ensure_capacity( implementation<IS_POD>, int min_capacity )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	if( min_capacity > CAPACITY && ( !data_large_ || min_capacity > capacity_ ) )
		{	
		int new_capacity = capacity_;
		while( new_capacity < min_capacity ) new_capacity *= 2;

		if( data_large_ )
			{
			T* new_large = (T*) internal::array_malloc( memctx_, sizeof( T ) * new_capacity );
			if( count_ > 0 ) ARRAY_MEMCPY( new_large, data_large_, sizeof( T ) * count_ );
			internal::array_free( memctx_, data_large_ );
			data_large_ = new_large;
			}
		else
			{
			data_large_ = (T*) internal::array_malloc( memctx_, sizeof( T ) * new_capacity );
			if( count_ > 0 ) ARRAY_MEMCPY( data_large_, items_, sizeof( T ) * count_ );
			}

		ARRAY_ASSERT( data_large_, "Allocation failed when allocating memory for array" );
		items_ = data_large_;

		// Increase the maximum number of items
		capacity_ = new_capacity;
		}


	}


// add
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add( T const& item )
	{
	return add( implementation<POD>(), item );
	}


// add NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add( implementation<NOT_POD>, T const& item )
	{
	ensure_capacity( implementation<NOT_POD>(), count_ + 1 );

	// set the item
	T* slot = items_ + count_;
	new ( slot ) T( item ); // Placement new to copy item

	++count_;

	return *slot;
	}


// add POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add( implementation<IS_POD>, T const& item )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ensure_capacity( implementation<IS_POD>(), count_ + 1 );

	// set the item
	T* slot = items_ + count_;
	*slot = item;

	++count_;

	return *slot;
	}


// add
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add()
	{
	return add( implementation<POD>() );
	}


// add NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add( implementation<NOT_POD> )
	{
	ensure_capacity( implementation<NOT_POD>(), count_ + 1 );

	// set the item
	T* slot = items_ + count_;
	#pragma warning( push ) 
	#pragma warning( disable: 4619 ) // there is no warning number '4345'
	#pragma warning( disable: 4345 ) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
	new ( slot ) T(); // Placement new 
	#pragma warning( pop )

	++count_;

	return *slot;
	}


// add POD

template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::add( implementation<IS_POD> )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ensure_capacity( implementation<IS_POD>(), count_ + 1 );

	// set the item
	T* slot = items_ + count_;

	++count_;

	return *slot;
	}


// insert
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert( int index, T const& item )
	{
	return insert( implementation<POD>(), index, item );
	}


// insert NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert( implementation<NOT_POD>, int index, T const& item )
	{
	ARRAY_ASSERT( index >= 0 && index <= count_, "Index out of range" );
	if( index < 0 || index > count_ ) return *items_;  // Return the first slot, just to return a valid address

	// Make room
	add( implementation<NOT_POD>() );

	// Shift existing items 
	for( int i = count_ - 1; i > index; --i )
		{
		items_[ i ].~T();
		new ( items_ + i ) T( items_[ i - 1 ] );
		}

	// set the item
	T* slot = items_ + index;
	slot->~T();

	new ( slot ) T( item ); // Placement new to copy item

	return *slot;
	}


// insert POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert( implementation<IS_POD>, int index, T const& item )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ARRAY_ASSERT( index >= 0 && index <= count_, "Index out of range" );
	if( index < 0 || index > count_ ) return *items_;  // Return the first slot, just to return a valid address

	// Make room
	add( implementation<IS_POD>() );

	// Shift existing items 
	int count = count_ - index;
	if( count > 0 ) memmove( items_ + index + 1, items_ + index, sizeof( T ) * count );

	// set the item
	T* slot = items_ + index;
	*slot = item;

	return *slot;
	}


// insert
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert(int index )
	{
	return insert( implementation<POD>(), index );
	}


// insert NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert( implementation<NOT_POD>, int index )
	{
	ARRAY_ASSERT( index >= 0 && index <= count_, "Index out of range" );
	if( index < 0 || index > count_ ) return *items_;  // Return the first slot, just to return a valid address

	// Make room
	add( implementation<NOT_POD>() );

	// Shift existing items 
	for( int i = count_ - 1; i > index; --i )
		{
		items_[ i ].~T();
		new ( items_ + i ) T( items_[ i - 1 ] );
		}

	// set the item
	T* slot = items_ + index;
	slot->~T();

	#pragma warning( push ) 
	#pragma warning( disable: 4619 ) // there is no warning number '4345'
	#pragma warning( disable: 4345 ) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
	new ( slot ) T(); // Placement new
	#pragma warning( pop )

	return *slot;
	}


// insert POD
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::insert( implementation<IS_POD>, int index )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ARRAY_ASSERT( index >= 0 && index <= count_, "Index out of range" );
	if( index < 0 || index > count_ ) return *items_;  // Return the first slot, just to return a valid address

	// Make room
	add( implementation<IS_POD>() );

	// Shift existing items 
	int count = count_ - index;
	if( count > 0 ) memmove( items_ + index + 1, items_ + index, sizeof( T ) * count );

	// set the item
	T* slot = items_ + index;

	return *slot;
	}


// remove
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::remove( int index )
	{
	remove( implementation<POD>(), index );
	}


// remove NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::remove( implementation<NOT_POD>, int index )
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	// Move items after the item to be removed
	for( int i = index; i < count_ - 1; ++i )
		{
		items_[ i ].~T();
		new ( items_ + i ) T( items_[ i + 1 ] );
		}
	
	// Decrease the total number of items
	--count_;

	// Call destructor on removed object
	items_[ count_ ].~T();	
	}


// remove POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::remove( implementation<IS_POD>, int index )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	// Move items after the item to be removed
	int count = count_ - index - 1;
	if( count > 0 ) memmove( items_ + index, items_ + index + 1, sizeof( T ) * count );

	// Decrease the total number of items
	--count_;
	}


// unordered_remove
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::unordered_remove( int index )
	{
	unordered_remove( implementation<POD>(), index );
	}


// unordered_remove NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::unordered_remove( implementation<NOT_POD>, int index )
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	--count;
	items_[ index ].~T();
	new ( items_ + index ) T( items_[ count ] );
	items_[ count ].~T();		
	}


// unordered_remove POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::unordered_remove( implementation<IS_POD>, int index )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	items_[ index ] = items_[ --count_ ];
	}


// set
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::set( int index, T const& item )
	{
	set( implementation<POD>(), index, item );
	}


// set NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::set( implementation<NOT_POD>, int index, T const& item )
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	T* slot = items_ + index;
	slot->~T();
	new ( slot ) T( item ); // Placement new to copy item
	}


// set POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::set( implementation<IS_POD>, int index, T const& item )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index >= count_ ) return;

	T* slot = items_ + index;
	*slot = item;
	}


// clear
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::clear()
	{	
	clear( implementation<POD>() );
	}


// clear NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::clear( implementation<NOT_POD> )
	{
	// Call destructor manually on existing items
	T* items = items_;
	for( int i = 0; i < count_; ++i )
		{
		items->~T();
		++items;
		}

	// clear used range
	count_ = 0;	
	}


// clear POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::clear( implementation<IS_POD> )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	// clear used range
	count_ = 0;	
	}


// resize
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( int count, T const& item )
	{	
	resize( implementation<POD>(), count, item );
	}


// resize NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( implementation<NOT_POD>, int new_count, T const& item  )
	{
	ensure_capacity( implementation<NOT_POD>(), new_count );

	// Destroy extraneous items
	for( int i = new_count; i < count_; ++i )
		items_[ i ].~T();

	// Initialize new items
	for( int i = count_; i < new_count; ++i )
		new ( items_ + i ) T( item ); // Placement new to copy item

	count_ = new_count;
	}


// resize POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( implementation<IS_POD>, int new_count, T const& item  )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ensure_capacity( implementation<IS_POD>(), new_count );

	// Initialize new items
	for( int i = count_; i < new_count; ++i )
		items_[ i ] = item;

	count_ = new_count;
	}


// resize
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( int new_count )
	{	
	resize( implementation<POD>(), new_count );
	}


// resize NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( implementation<NOT_POD>, int new_count )
	{
	ensure_capacity( implementation<NOT_POD>(), new_count );

	// Destroy extraneous items
	for( int i = new_count; i < count_; ++i )
		items_[ i ].~T();

	// Initialize new items
	#pragma warning( push ) 
	#pragma warning( disable: 4619 ) // there is no warning number '4345'
	#pragma warning( disable: 4345 ) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized

	for( int i = count_; i < new_count; ++i )
		new ( items_ + i ) T(); // Placement new

	#pragma warning( pop )

	count_ = new_count;
	}


// resize POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::resize( implementation<IS_POD>, int new_count )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	ensure_capacity( implementation<IS_POD>(), new_count );

	count_ = new_count;
	}


// capacity
template< typename T, int CAPACITY, POD_ENUM POD > 
int array_type<T, CAPACITY, POD>::capacity() const
	{
	return capacity_;
	}


// count
template< typename T, int CAPACITY, POD_ENUM POD > 
int array_type<T, CAPACITY, POD>::count() const

	{
	return count_;
	}


// get
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::get( int index )
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index < count_ )
		{
		T* slot = items_ + index;
		return *slot;
		}

	return *items_;  // Return the first slot, just to return a valid address
	}


// get const
template< typename T, int CAPACITY, POD_ENUM POD > 
T const& array_type<T, CAPACITY, POD>::get( int index ) const
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index < count_ )
		{
		T const* slot = items_ + index;
		return *slot;
		}

	return *items_;  // Return the first slot, just to return a valid address
	}


// operator[]
template< typename T, int CAPACITY, POD_ENUM POD > 
T& array_type<T, CAPACITY, POD>::operator[]( int index )
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index < count_ )
		{
		T* slot = items_ + index;
		return *slot;
		}

	return *items_;  // Return the first slot, just to return a valid address
	}


// operator[] const
template< typename T, int CAPACITY, POD_ENUM POD > 
T const& array_type<T, CAPACITY, POD>::operator[]( int index ) const
	{
	ARRAY_ASSERT( index < count_, "Index out of range" );
	if( index < count_ )
		{
		T const* slot = items_ + index;
		return *slot;
		}

	return *items_;  // Return the first slot, just to return a valid address
	}


// data
template< typename T, int CAPACITY, POD_ENUM POD > 
T* array_type<T, CAPACITY, POD>::data()
	{
	return items_;
	}
	

// data const
template< typename T, int CAPACITY, POD_ENUM POD > 
T const* array_type<T, CAPACITY, POD>::data() const
	{
	return items_;
	}
	

// contains
template< typename T, int CAPACITY, POD_ENUM POD > 
bool array_type<T, CAPACITY, POD>::contains( T const& item ) const
	{
	T const* items = data();
	for( int i = 0; i < count_; ++i )
		{
		if( *items == item ) return true;
		++items;
		}

	return false;
	}


// init NOT POD
template< typename T, int CAPACITY, POD_ENUM POD > template< typename U >
void array_type<T, CAPACITY, POD>::init( implementation<NOT_POD>, U const* items, int count )
	{
	ensure_capacity( implementation<POD>(), count );
	count_ = count;		

	U const* source_item = items;
	T* item = items_;
	for( int i = 0; i < count; ++i )
		{
		ARRAY_MEMSET( item, 0, sizeof( *item ) );
		new ( item ) T( *source_item ); // Placement new to create a new item
		++source_item;
		++item;
		}
	}


// init POD, different types
template< typename T, int CAPACITY, POD_ENUM POD > template< typename U > 
void array_type<T, CAPACITY, POD>::init( implementation<IS_POD>, U const* items, int count )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	resize( implementation<IS_POD>(), count ); 

	U const* source_item = items;
	T* item = items_;
	for( int i = 0; i < count; i++ )
		{
		*item = T( *source_item );
		++source_item;
		++item;
		}

	count_ = count;
	}


// init POD
template< typename T, int CAPACITY, POD_ENUM POD > 
void array_type<T, CAPACITY, POD>::init( implementation<IS_POD>, T const* items, int count )
	{
	ARRAY_ERROR_IF_NOT_POD( T );

	resize( implementation<IS_POD>(), count );
	ARRAY_MEMCPY( items_, items, count * sizeof( T ) );
	}

} /* namespace array_ns */

#undef ARRAY_PODTEST_DISABLE_WARNING_CONSTANT_EXPRESSION
#undef ARRAY_PODTEST_RESTORE_WARNING_LEVEL
#undef ARRAY_TEST_POD
#undef ARRAY_ERROR_IF_NOT_POD

#endif /* array_impl */


#ifdef ARRAY_IMPLEMENTATION
#undef ARRAY_IMPLEMENTATION

#ifndef ARRAY_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define ARRAY_MALLOC( ctx, size ) ( ::malloc( size ) )
	#define ARRAY_FREE( ctx, ptr ) ( ::free( ptr ) )
#endif

namespace array_ns { namespace internal {

void* array_malloc( void* ctx, size_t size )
	{
	(void) ctx;
	return ARRAY_MALLOC( ctx, size );
	}

void array_free( void* ctx, void* ptr )
	{
	(void) ctx;
	return ARRAY_FREE( ctx, ptr );
	}

} /* namespace internal */ } /* namespace array_ns */


#endif /* ARRAY_IMPLEMENTATION */


/*
------------------------------------------------------------------------------

This software is available under 2 licenses - you may choose the one you like.

------------------------------------------------------------------------------

ALTERNATIVE A - MIT License

Copyright (c) 2015 Mattias Gustavsson

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.

------------------------------------------------------------------------------

ALTERNATIVE B - Public Domain (www.unlicense.org)

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this 
software, either in source code form or as a compiled binary, for any purpose, 
commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this 
software dedicate any and all copyright interest in the software to the public 
domain. We make this dedication for the benefit of the public at large and to 
the detriment of our heirs and successors. We intend this dedication to be an 
overt act of relinquishment in perpetuity of all present and future rights to 
this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

------------------------------------------------------------------------------
*/
