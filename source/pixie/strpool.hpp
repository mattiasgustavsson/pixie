/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

strpool.hpp - v0.1 - 

Do this:
	#define STRPOOL_HPP_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.

Dependencies: 
    strpool.h
*/

#ifndef strpool_hpp
#define strpool_hpp

namespace strpool {

#ifndef STRPOOL_U64
	typedef unsigned long long u64;
#else
    typedef STRPOOL_U64 u64;
#endif


struct DEFAULT_POOL;
struct STRINGID_POOL;

template< typename POOL > 
struct string_type
	{
	string_type();
	~string_type();

	string_type& operator=( string_type const& other );
	string_type( string_type const& other );

	template< typename OTHER_POOL > 
	string_type( string_type<OTHER_POOL>  const& other );

	string_type( char* str );
	string_type( char const* str );
	string_type( char const* begin, char const* end );

	int length() const;
	char const* c_str() const;

	bool operator==( string_type const& other ) const;
	bool operator!=( string_type const& other ) const;

	template< typename OTHER_POOL> 
	bool operator==( string_type<OTHER_POOL> const& other ) const;

	template< typename OTHER_POOL> 
	bool operator!=( string_type<OTHER_POOL> const& other ) const;

	static void defrag();
	static void nuke();

	static char* temp_buffer( int len );

	private:
		template< typename POOL > friend struct string_type;
        u64 handle_;
			
		#ifndef NDEBUG
			char debug_[ 56 ];
		#endif
	};

typedef string_type<DEFAULT_POOL> string;
typedef string_type<STRINGID_POOL> string_id;


} /* namespace strpool */

#endif /* strpool_h */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef strpool_hpp_impl
#define strpool_hpp_impl

struct strpool_t;

// placement new
#if !defined( PLACEMENT_NEW_OPERATOR_DEFINED ) && !defined( __PLACEMENT_NEW_INLINE )
#define PLACEMENT_NEW_OPERATOR_DEFINED
#define __PLACEMENT_NEW_INLINE
inline void* operator new( size_t, void* p ) throw() { return p; } inline void operator delete(void*, void*) throw() { }
#endif 

namespace strpool { namespace internal {

int entry_count( strpool_t* pool );

struct string_pool
	{
	string_pool( bool case_sensitive, void* memctx = 0 );
	~string_pool();

	void defrag();
	void nuke();
			
	u64 get_handle( char const* string_type, int length );

	void inc_ref_count( u64 handle );
	void dec_ref_count( u64 handle );

	char const* get_string( u64 handle );
	int get_length( u64 handle );

	char* temp_buffer( int len );
				
	private:
		template< typename POOL > 
		friend internal::string_pool& pool_instance( bool destroy );

		void* memctx_;
		struct strpool_t* pool_;
		char* temp_buffer_;
		int temp_buffer_size_;
	};

size_t strlen( char const* str );
char* strcpy( char* dst, char const* src );
char* strncpy( char* dest, char const* source, size_t count );
int memcmp( void const* buf1, void const* buf2, size_t count );
void* allocate( size_t size );
void release( void* ptr );
				
template< typename POOL >
internal::string_pool& pool_instance( bool destroy = false )
	{
	static string_pool* instance = 0;
	if( destroy )
		{
		if( instance && entry_count( instance->pool_ ) == 0 )
			{
			instance->~string_pool();
			release( instance );
			instance = 0;
			}
		}
	else if( !instance )
		{
		instance = (string_pool*) allocate( sizeof( *instance ) );
		new (instance) string_pool( true );
		}

	return *instance;
	}	


template<>
inline internal::string_pool& pool_instance<STRINGID_POOL>( bool destroy )
	{
	static string_pool* instance = 0;
	if( destroy )
		{
		if( instance && entry_count( instance->pool_ ) == 0 )
			{
			instance->~string_pool();
			release( instance );
			instance = 0;
			}
		}
	else if( !instance )
		{
		instance = (string_pool*) allocate( sizeof( *instance ) );
		new (instance) string_pool( false );
		}

	return *instance;
	}	


} /* namespace internal */ } /*namespace strpool */

namespace strpool { 

template< typename POOL > 	
string_type<POOL>::string_type():
	handle_( 0 )
	{
	#ifndef NDEBUG
		internal::strcpy( debug_, "");
	#endif
	}

template< typename POOL > 	
string_type<POOL>::~string_type()
	{
	if( handle_ )
		{
		internal::pool_instance<POOL>().dec_ref_count( handle_ );
		}
	internal::pool_instance<POOL>( true );
	}

template< typename POOL > 	
string_type<POOL>& string_type<POOL>::operator=( string_type const& other )
	{
	if( handle_ ) internal::pool_instance<POOL>().dec_ref_count( handle_ );
	handle_ = other.handle_;
	if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif

	return *this;
	}

template< typename POOL > 	
string_type<POOL>::string_type( string_type const& other ):
	handle_( other.handle_ )
	{
	if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif
	}

template< typename POOL > template< typename OTHER_POOL > 
string_type<POOL>::string_type( string_type<OTHER_POOL> const& other )
	{
	handle_ = internal::pool_instance<POOL>().get_handle( other.c_str(), other.length() );
	if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif
	}

template< typename POOL > 	
string_type<POOL>::string_type( char* str )
	{
	size_t len = 0;
	if( str ) len = internal::strlen( str );
	if( len == 0 )
		{
		handle_ = 0;
		}
	else
		{
		handle_ = internal::pool_instance<POOL>().get_handle( str, (int) len );
		if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );
		}

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif
	}

template< typename POOL > 	
string_type<POOL>::string_type( char const* str )
	{
	size_t len = 0;
	if( str ) len = internal::strlen( str );
	if( len == 0 )
		{
		handle_ = 0;
		}
	else
		{
		handle_ = internal::pool_instance<POOL>().get_handle( str, (int) len );
		if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );
		}

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif
	}

template< typename POOL > 	
string_type<POOL>::string_type( char const* begin, char const* end ) :
    handle_( 0 )
	{
    if( !begin ) 
        {
	    #ifndef NDEBUG
		    internal::strcpy( debug_, "");
	    #endif
        }
	size_t len = end ? (size_t)( end - begin ) : internal::strlen( begin );
	if( len == 0 )
		{
		handle_ = 0;
		}
	else
		{
		handle_ = internal::pool_instance<POOL>().get_handle( begin, (int) len );
		if( handle_ ) internal::pool_instance<POOL>().inc_ref_count( handle_ );
		}

	#ifndef NDEBUG
		internal::strncpy( debug_, c_str(), sizeof( debug_ ) );
        debug_[ sizeof( debug_ ) - 1 ] = '\0';
	#endif
	}

template< typename POOL > 	
int string_type<POOL>::length() const
	{
	if( handle_ )
		return internal::pool_instance<POOL>().get_length( handle_ );
	else
		return 0;
	}
			
template< typename POOL > 	
char const* string_type<POOL>::c_str() const
	{
	if( handle_ )
		return internal::pool_instance<POOL>().get_string( handle_ );
	else
		return "";
	}

template< typename POOL > 	
bool string_type<POOL>::operator==( string_type const& other ) const
	{
	return handle_ == other.handle_;
	}

template< typename POOL > 	
bool string_type<POOL>::operator!=( string_type const& other ) const
	{
	return !( (*this) == other );
	}

template< typename POOL > template< typename OTHER_POOL> 	
bool string_type<POOL>::operator==( string_type<OTHER_POOL> const& other ) const
	{
	if( !handle_ ) return other.handle_ ? false : true;

	int const length = internal::pool_instance<POOL>().get_length( handle_ );
	int const other_length = internal::pool_instance<OTHER_POOL>().get_length( other.handle_ );
	return length == other_length && ( length == 0 || internal::memcmp( c_str(), other.c_str(), (size_t) length ) == 0 );
	}

template< typename POOL > template< typename OTHER_POOL > 
bool string_type<POOL>::operator!=( string_type<OTHER_POOL> const& other ) const
	{
	return !( (*this) == other );
	}

	
template< typename POOL > 
void string_type<POOL>::defrag() 
	{ 
	internal::pool_instance<POOL>().defrag(); 
	}


template< typename POOL > 
void string_type<POOL>::nuke()
	{
	internal::pool_instance<POOL>().nuke();
	}


template< typename POOL > 
char* string_type<POOL>::temp_buffer( int const len )
	{
	return internal::pool_instance<POOL>().temp_buffer( len );
	}

} /* namespace strpool */


#endif /* strpool_hpp_impl */



#ifdef STRPOOL_HPP_IMPLEMENTATION
#undef STRPOOL_HPP_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <memory.h>
#include <string.h>


#ifndef STRPOOL_HPP_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define STRPOOL_HPP_MALLOC( ctx, size ) ( malloc( size ) )
	#define STRPOOL_HPP_FREE( ctx, ptr ) ( free( ptr ) )
#endif

#include "strpool.h"

namespace strpool { namespace internal {

int entry_count( strpool_t* pool )
    {
    return pool->entry_count;
    }


string_pool::string_pool( bool case_sensitive, void* memctx ):
	memctx_( memctx ),
	temp_buffer_size_( 256 )
	{
	strpool_config_t config = strpool_default_config;
	config.memctx = memctx;
	config.ignore_case = case_sensitive ? 0 : 1;
    pool_ = (strpool_t*) STRPOOL_HPP_MALLOC( memctx, sizeof( strpool_t ) );
	strpool_init( pool_, &config );
	temp_buffer_ = (char*) STRPOOL_HPP_MALLOC( memctx, (size_t) temp_buffer_size_ );
	}
	
string_pool::~string_pool()
	{
	strpool_term( pool_ );
    STRPOOL_HPP_FREE( memctx_, pool_ );
	STRPOOL_HPP_FREE( memctx_, temp_buffer_ );
	}

void string_pool::defrag()
	{
	strpool_defrag( pool_ );
	}

void string_pool::nuke()
	{
	strpool_term( pool_ );
	strpool_init( pool_, &strpool_default_config );
	}

STRPOOL_U64 string_pool::get_handle( char const* const str, int const length )
	{
	return strpool_inject( pool_, str, length );
	}

void string_pool::inc_ref_count( STRPOOL_U64 const handle )
	{
	strpool_incref( pool_, handle );
	}

void string_pool::dec_ref_count( STRPOOL_U64 const handle )
	{
	if( strpool_decref( pool_, handle ) <= 0 )
		{
		strpool_discard( pool_, handle );
		}
	}

char const* string_pool::get_string( STRPOOL_U64 const handle )
	{
	return strpool_cstr( pool_, handle );
	}

int string_pool::get_length( STRPOOL_U64 const handle )
	{
	return strpool_length( pool_, handle );
	}

char* string_pool::temp_buffer( int const len )
	{
	if( temp_buffer_size_ < len + 1 ) 
		{
		temp_buffer_size_ = len + 1;
		STRPOOL_HPP_FREE( memctx_, temp_buffer_ );
		temp_buffer_ = (char*) STRPOOL_HPP_MALLOC( memctx_, (size_t) temp_buffer_size_ );
		}

	return temp_buffer_;
	}

size_t strlen( char const* const str ) { return ::strlen( str ); }
char* strcpy( char* const dst, char const* const src ) { return ::strcpy( dst, src ); }
char* strncpy( char* const dest, char const* const source, size_t const count ) { return ::strncpy( dest, source, count ); }
int memcmp( void const* const buf1, void const* const buf2, size_t const count ) { return ::memcmp( buf1, buf2, count ); }
void* allocate( size_t size ) { return STRPOOL_HPP_MALLOC( 0, size ); }
void release( void* ptr ) { return STRPOOL_HPP_FREE( 0, ptr ); }

} /* namespace internal */ } /* namespace strpool */

#endif /* STRPOOL_HPP_IMPLEMENTATION */


/*
revision history:
	1.0		first released version	
*/


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
