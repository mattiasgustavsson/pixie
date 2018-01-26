/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

refcount.hpp - v0.1 - Simple reference counting pointer wrapper for C++.

Do this:
	#define REFCOUNT_IMPLEMENTATION
before you include this file in *one* C++ file to create the implementation.
*/

#ifndef refcount_hpp
#define refcount_hpp

namespace refcount { 

template< typename T > struct ref
	{
	ref();
	ref( ref<T> const& other );
	ref<T>& operator=( ref<T> const& other );
	~ref();
	T* operator->() const;
	operator T*() const;

	template< typename U > operator ref<U>(); // for derived classes

	inline static ref<T> make_new();
	template< typename P0 > static ref<T> make_new( P0 );
	template< typename P0, typename P1 > static ref<T> make_new( P0, P1 );
	template< typename P0, typename P1, typename P2 > static ref<T> make_new( P0, P1, P2 );
	template< typename P0, typename P1, typename P2, typename P3 > static ref<T> make_new( P0, P1, P2, P3 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4 > static ref<T> make_new( P0, P1, P2, P3, P4 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > static ref<T> make_new( P0, P1, P2, P3, P4, P5 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > static ref<T> make_new( P0, P1, P2, P3, P4, P5, P6 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > static ref<T> make_new( P0, P1, P2, P3, P4, P5, P6, P7 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > static ref<T> make_new( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > static ref<T> make_new( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );

	private:
		template< typename U > friend ref<U> make_ref( U* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) );
		template< typename T > friend ref<T> new_ref();
		template< typename T, typename P0 > friend ref<T> new_ref( P0 );
		template< typename T, typename P0, typename P1 > friend ref<T> new_ref( P0, P1 );
		template< typename T, typename P0, typename P1, typename P2 > ref<T> new_ref( P0, P1, P2 );
		template< typename T, typename P0, typename P1, typename P2, typename P3 > friend ref<T> new_ref( P0, P1, P2, P3 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > friend ref<T> new_ref( P0, P1, P2, P3, P4 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > friend ref<T> new_ref( P0, P1, P2, P3, P4, P5 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > friend ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > friend ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > friend ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
		template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > friend ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );
		
		ref( T* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) );
		template< typename U > ref( U* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) );
		
		T* instance_;
		void (*destroy_instance_)( void* );
		int* count_;
		void (*destroy_count_)( int* );
		
	};

template< typename T > ref<T> make_ref( T* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) );

template< typename T > ref<T> new_ref();
template< typename T, typename P0 > ref<T> new_ref( P0 );
template< typename T, typename P0, typename P1 > ref<T> new_ref( P0, P1 );
template< typename T, typename P0, typename P1, typename P2 > ref<T> new_ref( P0, P1, P2 );
template< typename T, typename P0, typename P1, typename P2, typename P3 > ref<T> new_ref( P0, P1, P2, P3 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > ref<T> new_ref( P0, P1, P2, P3, P4 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > ref<T> new_ref( P0, P1, P2, P3, P4, P5 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );

} /* namespace refcount */

#endif /* refcount_hpp */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef ref_impl
#define ref_impl

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

// placement new
#if !defined( PLACEMENT_NEW_OPERATOR_DEFINED ) && !defined( __PLACEMENT_NEW_INLINE )
#define PLACEMENT_NEW_OPERATOR_DEFINED
#define __PLACEMENT_NEW_INLINE
inline void* operator new( size_t, void* p ) throw() { return p; } inline void operator delete(void*, void*) throw() { }
#endif 

namespace refcount { namespace internal {

void* mem_alloc( size_t size );
void mem_free( void* ptr );

template< typename T > void alloc_helper( void** ptr, int** count )
	{
	size_t size = sizeof( T ) + sizeof( int ) ;
	uintptr_t storage = (uintptr_t) mem_alloc( size );
	*ptr = (void*) storage;
	*count = (int*)( storage + sizeof( T ) );
	}

template< typename T > void destroy_helper( void* ptr ) 
	{ 
	( (T*) ptr )->~T(); 
	mem_free( ptr ); 
	}  

} /* namespace internal */ } /* namespace refcount */


namespace refcount { 

template< typename T > ref<T>::ref(): 
	instance_( 0 ), 
	destroy_instance_( 0 ),
	count_( 0 ),
	destroy_count_( 0 )
	{ 
	}


template< typename T > ref<T>::ref( T* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) ) :
	instance_( instance ),  
	destroy_instance_( destroy_instance ),
	count_( count ),
	destroy_count_( destroy_count ) 
	{
	if( count_ ) *count_ = 1;
	}


template< typename T > template< typename U > ref<T>::ref( U* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) ) : 
	instance_( instance ), 
	destroy_instance_( destroy_instance ) ,
	count_( count ),
	destroy_count_( destroy_count ) 
	{ 
	if( count_ ) *count_ = 1;
	}


template< typename T > ref<T>::ref( ref<T> const& other ): 
	instance_( other.instance_ ), 
	destroy_instance_( other.destroy_instance_ ) ,
	count_( other.count_ ),
	destroy_count_( other.destroy_count_ )
	{ 
	if( count_ ) ++(*count_); 
	}


template< typename T > ref<T>& ref<T>::operator=( ref<T> const& other ) 
	{ 
	if( instance_ != other.instance_ ) 
		{ 
		if( count_ )
			{
			--(*count_); 
			if( *count_ == 0 ) 
				{ 
				if( destroy_instance_ ) destroy_instance_( instance_ );
				if( destroy_count_ ) destroy_count_( count_ );
				} 
			}
		instance_ = other.instance_; 
		destroy_instance_ = other.destroy_instance_; 
		count_ = other.count_; 
		destroy_count_ = other.destroy_count_;
		if( count_ ) ++(*count_); 
		} 
	return *this; 
	}


template< typename T > ref<T>::~ref() 
	{ 
	if( count_ )
		{
		--(*count_); 
		if( *count_ == 0 ) 
			{ 
			if( destroy_instance_ ) destroy_instance_( instance_ );
			if( destroy_count_ ) destroy_count_( count_ );
			} 
		}
	}


template< typename T > T* ref<T>::operator->() const
	{ 
	return instance_; 
	}


template< typename T > ref<T>::operator T*() const 
	{ 
	return instance_; 
	}


template< typename T > template< typename U > ref<T>::operator ref<U>() 
	{ 
	static_cast<U*>( instance_ ); // Generate an error if attempting to cast between unrelated types ( U* and T* )
	ref<U>* ret = (ref<U>*) this; // Do the actual cast as c-style cast, as ref<U> and ref<T> are unrelated types
	return *ret;
	}


template< typename T > 
ref<T> ref<T>::make_new() 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T(), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0 > 
ref<T> ref<T>::make_new( P0 p0 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4, p5 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4, p5, p6 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4, p5, p6, p7 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4, p5, p6, p7, p8 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > 
template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
ref<T> ref<T>::make_new( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	void* ptr; int* count; internal::alloc_helper<T>( &ptr, &count );
	return make_ref( new (ptr) T( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ), internal::destroy_helper<T>, count, 0 ); 
	}


template< typename T > ref<T> make_ref( T* instance, void (*destroy_instance)( void* ), int* count, void (*destroy_count)( int* ) )
	{
	return ref<T>( instance, destroy_instance, count, destroy_count );
	}


template< typename T > 
ref<T> new_ref() 
	{ 
	return ref<T>::make_new(); 
	}


template< typename T, typename P0 > 
ref<T> new_ref( P0 p0 ) 
	{ 
	return ref<T>::make_new( p0 ); 
	}


template< typename T, typename P0, typename P1 > 
ref<T> new_ref( P0 p0, P1 p1 ) 
	{ 
	return ref<T>::make_new( p0, p1 );
	}


template< typename T, typename P0, typename P1, typename P2 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
ref<T> new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); 
	}


} /* namespace refcount */

#endif /* refcount_impl */


#ifdef REFCOUNT_IMPLEMENTATION
#undef REFCOUNT_IMPLEMENTATION


#ifndef REFCOUNT_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#if defined(__cplusplus)
		#define REFCOUNT_MALLOC( size ) ( ::malloc( size ) )
		#define REFCOUNT_FREE( ptr ) ( ::free( ptr ) )
	#else
		#define REFCOUNT_MALLOC( size ) ( malloc( size ) )
		#define REFCOUNT_FREE( ptr ) ( free( ptr ) )
	#endif
#endif


void* refcount::internal::mem_alloc( size_t size )
	{
	return REFCOUNT_MALLOC( size );
	}


void refcount::internal::mem_free( void* ptr )
	{
	REFCOUNT_FREE( ptr );
	}


#endif /* REFCOUNT_IMPLEMENTATION */

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
