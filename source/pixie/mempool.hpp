/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

mempool.hpp - v0.1 - Fixed-size memory blocks allocator for C/C++.

Do this:
	#define MEMPOOL_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef mempool_hpp
#define mempool_hpp

namespace mempool_ns {

template< typename T > struct mempool final
	{
	mempool( int initial_capacity = 256, void* memctx = 0 );
	~mempool();

	inline T* create();
	template< typename P0 > T* create( P0 p0 );
	template< typename P0, typename P1 > T* create( P0 p0, P1 p1 );
	template< typename P0, typename P1, typename P2 > T* create( P0 p0, P1 p1, P2 p2 );
	template< typename P0, typename P1, typename P2, typename P3 > T* create( P0 p0, P1 p1, P2 p2, P3 p3 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 );
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > T* create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 );
	void destroy( T* );

	void clear();
	bool contains( T* item );
	
	T* allocate();
	void deallocate( T* ptr );

	private:
		void* memctx_;
		int next_capacity_;
		struct item_t final
			{
			T item;
			mempool<T>* owner;
			};
		struct block_t final
			{
		    item_t* items;
		    int items_capacity;
		    int items_count;
			int freelist;
			};
		block_t* blocks_;
		int blocks_capacity_;
		int blocks_count_;
	};

} /* namespace mempool_ns */

#endif /* mempool_hpp */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef mempool_impl
#define mempool_impl

// placement new
#if !defined( PLACEMENT_NEW_OPERATOR_DEFINED ) && !defined( __PLACEMENT_NEW_INLINE )
#define PLACEMENT_NEW_OPERATOR_DEFINED
#define __PLACEMENT_NEW_INLINE
inline void* operator new( size_t, void* p ) throw() { return p; } inline void operator delete(void*, void*) throw() { }
#endif 

#ifndef MEMPOOL_ASSERT
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <assert.h>
	#define MEMPOOL_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

namespace mempool_ns { namespace internal { 

void* mempool_alloc( void* memctx, size_t size );
void mempool_free( void* memctx, void* p );
void* mempool_memcpy( void* destination, void const* source, size_t count );

} /* namespace internal */ } /* namespace mempool_ns */


template< typename T > mempool_ns::mempool<T>::mempool( int initial_capacity, void* memctx ):
	memctx_( memctx ),
	next_capacity_( initial_capacity * 2 ),
	blocks_count_( 0 ),
	blocks_capacity_( 64 )
	{
	blocks_ = (block_t*) internal::mempool_alloc( memctx, sizeof( block_t ) * blocks_capacity_ );
	block_t* initial_block = &blocks_[ blocks_count_++ ];
	initial_block->freelist = -1;
	initial_block->items_count = 0;
	initial_block->items_capacity = initial_capacity;
	initial_block->items = (item_t*) internal::mempool_alloc( memctx_, sizeof( item_t ) * initial_block->items_capacity );    
	memset( initial_block->items, 0, sizeof( item_t ) * initial_block->items_capacity );
	}


template< typename T > 
mempool_ns::mempool<T>::~mempool()
	{
	for( int i = 0; i < blocks_count_; ++i )
		{
		block_t* block = &blocks_[ i ];
		for( int j = 0; j < block->items_count; ++j )
			{
			if( block->items[ j ].owner ) block->items[ j ].item.~T();
			}
		internal::mempool_free( memctx_, block->items );
		}
	internal::mempool_free( memctx_, blocks_ );
	}


template< typename T > 
bool mempool_ns::mempool<T>::contains( T* item )
	{
	uintptr_t item_ptr = (uintptr_t) item;
	for( int i = 0; i < blocks_count_; ++i )
		{
		block_t* block = &blocks_[ i ];
		uintptr_t block_begin = (uintptr_t) block->items;
		uintptr_t block_end = block_begin + block->items_capacity * sizeof( item_t );
		if( item_ptr >= block_begin && item_ptr < block_end )
			return true;
		}

	return false;
	}


template< typename T > 
T* mempool_ns::mempool<T>::allocate()
	{
	for( int i = blocks_count_ - 1; i >= 0; --i )
		{
		block_t* block = &blocks_[ i ];
		if( block->freelist >= 0 )
			{
			int item_index = block->freelist;
			block->freelist = *( (int*) &block->items[ item_index ] );
			block->items[ item_index ].owner = this;
			return &block->items[ item_index ].item;
			}
		else if( block->items_count < block->items_capacity )
			{
			int item_index = block->items_count++;
			block->items[ item_index ].owner = this;
			return &block->items[ item_index ].item;
			}
		}

	if( blocks_count_ >= blocks_capacity_ )
		{
		blocks_capacity_ *= 2;
		block_t* new_blocks = (block_t*) internal::mempool_alloc( memctx_, sizeof( block_t ) * blocks_capacity_ );
		internal::mempool_memcpy( new_blocks, blocks_, sizeof( block_t ) * blocks_count_ );
		internal::mempool_free( memctx_, blocks_ );
		blocks_ = new_blocks;
		}

	block_t* block = &blocks_[ blocks_count_++ ];
	block->freelist = -1;
	block->items_count = 1;
	block->items_capacity = next_capacity_;
	block->items = (item_t*) internal::mempool_alloc( memctx_, sizeof( item_t ) * block->items_capacity );    
	memset( block->items, 0, sizeof( item_t ) * block->items_capacity );
	next_capacity_ *= 2;
	block->items[ 0 ].owner = this;
	return &block->items[ 0 ].item;
	}


template< typename T > 
void mempool_ns::mempool<T>::deallocate( T* item )
	{   
	uintptr_t item_ptr = (uintptr_t) item;
	for( int i = 0; i < blocks_count_; ++i )
		{
		block_t* block = &blocks_[ i ];
		uintptr_t block_begin = (uintptr_t) block->items;
		uintptr_t block_end = block_begin + block->items_capacity * sizeof( item_t );
		if( item_ptr >= block_begin && item_ptr < block_end )
			{
			int item_index = (int)( ( item_ptr - block_begin ) / sizeof( item_t ) );
			MEMPOOL_ASSERT( block->items[ item_index ].owner, "Attempt to destroy an item which is not currently allocated." );
			if( block->items[ item_index ].owner )
				{
				block->items[ item_index ].owner = 0;
				*( (int*) &block->items[ item_index ] ) = block->freelist;
				block->freelist = item_index;
				}
			return;
			}
		}
	MEMPOOL_ASSERT( false, "Attempt to destroy an item not allocated from this mempool." );
	}

	
template< typename T > 
void mempool_ns::mempool<T>::clear()
	{
	for( int i = 0; i < blocks_count_; ++i )
		{
		block_t* block = &blocks_[ i ];
		for( int j = 0; j < block->items_count; ++j )
			{
			if( block->items[ j ].owner ) 
				{
				block->items[ j ].item.~T();
				block->items[ j ].owner = 0;
				}
			}
		block->freelist = -1;
		block->items_count = 0;
		}
	}


template< typename T > 
inline T* mempool_ns::mempool<T>::create()
	{
	#pragma warning( push ) 
	#pragma warning( disable: 4619 ) // there is no warning number '4345'
	#pragma warning( disable: 4345 ) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
	return new ( allocate() ) T();
	#pragma warning( pop ) 
	}


template< typename T > template< typename P0 > 
T* mempool_ns::mempool<T>::create( P0 p0 )
	{
	return new ( allocate() ) T( p0 );
	}

	
template< typename T > template< typename P0, typename P1 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1 )
	{
	return new ( allocate() ) T( p0, p1 );
	}


template< typename T > template< typename P0, typename P1, typename P2 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2 )
	{
	return new ( allocate() ) T( p0, p1, p2 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4, p5 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4, p5, p6 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4, p5, p6, p7 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4, p5, p6, p7, p8 );
	}


template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
T* mempool_ns::mempool<T>::create( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 )
	{
	return new ( allocate() ) T( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
	}


template< typename T > 
void mempool_ns::mempool<T>::destroy( T* item )
	{   
	uintptr_t item_ptr = (uintptr_t) item;
	for( int i = 0; i < blocks_count_; ++i )
		{
		block_t* block = &blocks_[ i ];
		uintptr_t block_begin = (uintptr_t) block->items;
		uintptr_t block_end = block_begin + block->items_capacity * sizeof( item_t );
		if( item_ptr >= block_begin && item_ptr < block_end )
			{
			int item_index = (int)( ( item_ptr - block_begin ) / sizeof( item_t ) );
			MEMPOOL_ASSERT( block->items[ item_index ].owner, "Attempt to destroy an item which is not currently allocated." );
			if( block->items[ item_index ].owner )
				{
				block->items[ item_index ].item.~T();
				block->items[ item_index ].owner = 0;
				*( (int*) &block->items[ item_index ] ) = block->freelist;
				block->freelist = item_index;
				}
			return;
			}
		}
	MEMPOOL_ASSERT( false, "Attempt to destroy an item not allocated from this mempool." );
	}

#endif /* mempool_impl */

#ifdef MEMPOOL_IMPLEMENTATION
#undef MEMPOOL_IMPLEMENTATION

#ifndef MEMPOOL_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define MEMPOOL_MALLOC( ctx, size ) ( malloc( size ) )
	#define MEMPOOL_FREE( ctx, ptr ) ( free( ptr ) )
#endif

#ifndef MEMPOOL_MEMCPY
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <string.h>
	#define MEMPOOL_MEMCPY( dst, src, cnt ) ( memcpy( dst, src, cnt ) )
#endif 

void* mempool_ns::internal::mempool_alloc( void* memctx, size_t size )
	{
	return MEMPOOL_MALLOC( memctx, size );
	}


void mempool_ns::internal::mempool_free( void* memctx, void* p )
	{
	MEMPOOL_FREE( memctx, p );
	}


void* mempool_ns::internal::mempool_memcpy( void* destination, void const* source, size_t count )
	{
	return MEMPOOL_MEMCPY( destination, source, count );
	}

#endif /* MEMPOOL_IMPLEMENTATION */

/*
------------------------------------------------------------------------------

This software is available under 2 licenses - you may choose the one you like.

------------------------------------------------------------------------------

ALTERNATIVE A - MIT License

Copyright (c) 2017 Mattias Gustavsson

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
