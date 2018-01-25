/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

objrepo.hpp - v0.1 - Generic object repositories with type-based lookup for C++.
*/

#ifndef objrepo_hpp
#define objrepo_hpp

namespace objrepo {

namespace internal { struct object_t; struct list_t; } /* namespace internal */

struct object_repo
	{
	object_repo( void* memctx = 0 );
	~object_repo();

	template< typename T > void add( T* object );
	template< typename T > void remove( T* object );
	template< typename T > T* get() const;
	
	private:
		void* memctx_;
		internal::object_t* objects_;
		int capacity_;
		int count_;
	};


struct object_list_repo
	{
	object_list_repo( void* memctx = 0 );
	~object_list_repo();

	template< typename T > void add( T* object );
	template< typename T > void remove( T* object );

	template< typename T > struct list
		{
		T** objects;
		int count;
		};
	template< typename T > list<T> get() const;
	
	private:
		void* memctx_;
		internal::list_t* lists_;
		int capacity_;
		int count_;
	};

} /* namespace objrepo */


#endif /* objrepo_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef objrepo_impl
#define objrepo_impl

namespace objrepo { namespace internal {

typedef void const* type_id_t;
template< typename T > struct internal_type_id_helper { static int* id() { static int t; return &t; } };
template< typename T > type_id_t type_id() { return (type_id_t) &internal_type_id_helper<T>::id; }
template< typename T > type_id_t type_id( T const& ) { return (type_id_t) &internal_type_id_helper<T>::id; }

void objects_add( object_t** objects, int* capacity, int* count, void* object, type_id_t type, void* memctx );
void objects_remove( object_t** objects, int* count, void* object, type_id_t type );
void* objects_get( object_t const* objects, int count, type_id_t type );

void lists_add( list_t** lists, int* capacity, int* count, void* object, type_id_t type );
void lists_remove( list_t** lists, int* count, void* object, type_id_t type );
void** lists_get( int* result_count, list_t const* lists, int count, type_id_t type );

} /* namespace internal */ } /* namespace objrepo */


namespace objrepo { 
	
template< typename T > 
void object_repo::add( T* object )
	{
	internal::objects_add( &objects_, &capacity_, &count_, object, internal::type_id<T>(), memctx_ );
	}


template< typename T > 
void object_repo::remove( T* object )
	{
	internal::objects_remove( &objects_, &count_, object, internal::type_id<T>() );
	}


template< typename T > T* object_repo::get() const
	{
	return (T*) internal::objects_get( objects_, count_, internal::type_id<T>() );
	}


template< typename T > 
void object_list_repo::add( T* object )
	{
	internal::lists_add( &lists_, &capacity_, &count_, object, internal::type_id<T>() );
	}


template< typename T > 
void object_list_repo::remove( T* object )
	{
	internal::lists_remove( &lists_, &count_, object, internal::type_id<T>() );
	}


template< typename T > 
object_list_repo::list<T> object_list_repo::get() const
	{
	list<T> list;
	list.objects = (T**) internal::lists_get( &list.count, lists_, count_, internal::type_id<T>() );
	return list;
	}
	
} /* namespace objrepo */

#endif /* objrepo_impl */


#ifdef OBJREPO_IMPLEMENTATION
#undef OBJREPO_IMPLEMENTATION

#ifndef OBJREPO_MALLOC
	#include <stdlib.h>
	#define OBJREPO_MALLOC( ctx, size ) ( ::malloc( size ) )
	#define OBJREPO_FREE( ctx, ptr ) ( ::free( ptr ) )
#endif

#ifndef OBJREPO_ASSERT
    #undef _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #undef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
    #include <assert.h>
    #define OBJREPO_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

namespace objrepo { namespace internal {

struct object_t
	{
	internal::type_id_t type;
	void* instance;
	};


void objects_add( object_t** objects, int* capacity, int* count, void* object, type_id_t type, void* memctx )
	{
	(void) memctx;
	OBJREPO_ASSERT( object, "Attempting to add a null-pointer object." );
	OBJREPO_ASSERT( !objects_get( *objects, *count, type ), "An object of this type was already added." );
	if( *count >= *capacity )
		{
		*capacity *= 2;
        object_t* new_objects = (object_t*) OBJREPO_MALLOC( memctx, *capacity * sizeof( **objects ) );
        memcpy( new_objects, *objects, *count * sizeof( **objects ) );
        OBJREPO_FREE( memctx, *objects );
		*objects = new_objects;
		}
	object_t* entry = &(*objects)[ (*count)++ ];
	entry->type = type;
	entry->instance = object;
	}


 void objects_remove( object_t** objects, int* count, void* object, type_id_t type )
	{
	(void) object;
	for( int i = 0; i < *count; ++i )
		{
		object_t* entry = &(*objects)[ i ];
		if( entry->type == type )
			{
			OBJREPO_ASSERT( entry->instance == object, "A matching object type was found, but the instances don not match." );
			(*objects)[ i ] = (*objects)[ --(*count) ];
			return;
			}
		}
	OBJREPO_ASSERT( false, "Object of the specified type could not be found." );
	}


void* objects_get( object_t const* objects, int count, type_id_t type )
	{
	for( int i = 0; i < count; ++i )
		{
		object_t const* entry = &objects[ i ];
		if( entry->type == type )
			return entry->instance;
		}
	return 0;
	}


struct list_t
	{
	internal::type_id_t type;
	void** instances;
	int capacity;
	int count;
	};


list_t* find_list( list_t* lists, int count, type_id_t type )
	{
	for( int i = 0; i < count; ++i )
		{
		list_t* entry = &lists[ i ];
		if( entry->type == type )
			return entry;
		}
	return 0;
	}


void lists_add( list_t** lists, int* capacity, int* count, void* object, type_id_t type, void* memctx )
	{
	(void) memctx;
	list_t* list = find_list( *lists, *count, type );
	if( !list )
		{
		if( *count >= *capacity )
			{
			*capacity *= 2;
            list_t* new_lists = (list_t*) OBJREPO_MALLOC( memctx, *capacity * sizeof( **lists ) );
            memcpy( new_lists, *lists, *count * sizeof( **lists ) );
            OBJREPO_FREE( memctx, *lists );
            *lists = new_lists;
			}
		list = &(*lists)[ (*count)++ ];
		list->count = 0;
		list->capacity = 256;
		list->instances = (void**) OBJREPO_MALLOC( memctx, list->capacity * sizeof( *list->instances ) );
		list->type = type;
		}

	if( list->count >= list->capacity )
		{
		list->capacity *= 2;
        void** new_instances = (void**) OBJREPO_MALLOC( memctx, list->capacity * sizeof( *list->instances ) );
        memcpy( new_instances, list->instances, list->count * sizeof( *list->instances ) );
        OBJREPO_FREE( memctx, list->instances );
		list->instances = new_instances;
		}

	list->instances[ list->count++ ] = object;
	}


void lists_remove( list_t** lists, int* count, void* object, type_id_t type )
	{
	list_t* list = find_list( *lists, *count, type );
	OBJREPO_ASSERT( list, "No objects of this type has been added." );
	for( int i = 0; i < list->count; ++i )
		{
		void** entry = &list->instances[ i ];
		if( entry == object )
			{
			list->instances[ i ] = list->instances[ --list->count ];
			return;
			}
		}
	OBJREPO_ASSERT( false, "Object could not be found." );
	}


void** lists_get( int* result_count, list_t const* lists, int count, type_id_t type )
	{
	list_t* list = find_list( (list_t*) lists, count, type );
	if( list )
		{
		*result_count = list->count;
		return list->instances;
		}
	else
		{
		*result_count = 0;
		return 0;
		}
	}

} /* namespace internal */ } /* namespace objrepo */


namespace objrepo {

object_repo::object_repo( void* memctx ):
	memctx_( memctx ),
	capacity_( 256 ),
	count_( 0 )
	{
	objects_ = (internal::object_t*) OBJREPO_MALLOC( memctx_, capacity_ * sizeof( *objects_ ) );
	}


object_repo::~object_repo()
	{
	OBJREPO_FREE( memctx_, objects_ );
	}


object_list_repo::object_list_repo( void* memctx ):
	memctx_( memctx ),
	capacity_( 256 ),
	count_( 0 )
	{
	lists_ = (internal::list_t*) OBJREPO_MALLOC( memctx_, capacity_ * sizeof( *lists_ ) );
	}


object_list_repo::~object_list_repo()
	{
	for( int i = 0; i < count_; ++i )
		OBJREPO_FREE( memctx_, lists_[ i ].instances );

	OBJREPO_FREE( memctx_, lists_ );
	}

} /* namespace objrepo */


#endif /* OBJREPO_IMPLEMENTATION */

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
