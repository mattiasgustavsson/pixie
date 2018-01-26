/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

strpool_util.hpp - v0.1 - utility functions for strpool.

Do this:
	#define STRPOOL_UTIL_IMPLEMENTATION
before you include this file in *one* C++ file to create the implementation.

Dependencies: 
	strpool.hpp
*/

#ifndef strpool_util_hpp
#define strpool_util_hpp

#include "strpool.hpp"

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stdarg.h>

namespace strpool {

template< typename POOL >  string_type<POOL> operator+( string_type<POOL> const& a, string_type<POOL> const& b );
template< typename POOL >  string_type<POOL> operator+( string_type<POOL> const& a, char const* b );
template< typename POOL >  string_type<POOL> operator+( char const* a, string_type<POOL> const& b );
template< typename POOL > string_type<POOL>& operator+=( string_type<POOL>& a, string_type<POOL> const& b );
template< typename POOL > string_type<POOL>& operator+=( string_type<POOL>& a, char const* b );
template< typename POOL >		        bool operator<( string_type<POOL> const& a, string_type<POOL> const& b );
template< typename POOL >		        bool operator>( string_type<POOL> const& a, string_type<POOL> const& b );
template< typename POOL >		        bool operator<=( string_type<POOL> const& a, string_type<POOL> const& b );
template< typename POOL >		        bool operator>=( string_type<POOL> const& a, string_type<POOL> const& b );
template< typename POOL >  string_type<POOL> trim( string_type<POOL> const& str ); // remove leading and trailing whitespace
template< typename POOL >  string_type<POOL> ltrim( string_type<POOL> const& str ); // remove leading whitespace 
template< typename POOL >  string_type<POOL> rtrim( string_type<POOL> const& str );  // remove trailing whitespace
template< typename POOL >  string_type<POOL> left( string_type<POOL> const& source, int number ); // return the leftmost characters of a string
template< typename POOL >  string_type<POOL> right( string_type<POOL> const& source, int number );  // return the rightmost characters of a string
template< typename POOL >  string_type<POOL> mid( string_type<POOL> const& source, int offset, int number = -1 );  // return a number of characters from the middle of a string
template< typename POOL >			     int instr( string_type<POOL> const& haystack, char const* needle, int start = 0 );  // search for occurrences of one string within another string
template< typename POOL >			     int instr( string_type<POOL> const& haystack, string_type<POOL> const& needle, int start = 0 );  // search for occurrences of one string within another string
template< typename POOL >			     int any( string_type<POOL> const& haystack, char const* needles, int start = 0 );  // search for the next occurrence of any character of one string within another string
template< typename POOL >			     int any( string_type<POOL> const& haystack, string_type<POOL> const& needles, int start = 0 );  // search for the next occurrence of any character of one string within another string
template< typename POOL >  string_type<POOL> upper( string_type<POOL> const& old );  // convert a string of text to upper case
template< typename POOL >  string_type<POOL> lower( string_type<POOL> const& old ); // convert a string of text to lower case
template< typename POOL >  string_type<POOL> str( int x ); // convert a number into a string
template< typename POOL >  string_type<POOL> str( float x ); // convert a number into a string
template< typename POOL >              float val( string_type<POOL> const& x ); // convert a string of digits into a floating point value
template< typename POOL >		         int integer( string_type<POOL> const& x ); // convert a string of digits into an integer value
template< typename POOL >  string_type<POOL> space ( int number ); // space out a string
template< typename POOL >  string_type<POOL> flip( string_type<POOL> const& original ); //invert a string
template< typename POOL >  string_type<POOL> repeat( string_type<POOL> const& text, int number ); // repeat a string
template< typename POOL >  string_type<POOL> chr( int code ); // return the character with a given ASCII code
template< typename POOL >			     int asc( string_type<POOL> const& str ); // give the ASCII code of a character
template< typename POOL >			     int len( string_type<POOL> const& str ); // give the length of a string
template< typename POOL >  string_type<POOL> format( string_type<POOL> format_string, ... );
template< typename POOL >  string_type<POOL> format( string_type<POOL> format_string, va_list args );


} /* namespace strpool */


#endif /* strpool_util_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef strpool_util_impl
#define strpool_util_impl


namespace strpool { namespace internal {
	
int snprintf( char* s, size_t n, char const* format, ... );
int toupper( int c );
int tolower( int c );
char* strtok( char* str, char const* delimiters );
float atof( char const* str );
int atoi( char const* str );

} /* namespace internal */ } /* namespace strpool */

namespace strpool {

template< typename POOL > string_type<POOL> operator+( string_type<POOL> const& a, string_type<POOL> const& b ) 
	{ 
	int const len_a = a.length();
	int const len_b = b.length();
	char* const temp = string_type<POOL>::temp_buffer( len_a + len_b );
	memcpy( temp, a.c_str(), (size_t) len_a );
	memcpy( temp + len_a, b.c_str(), (size_t) len_b );
	*( temp + len_a + len_b ) = '\0';
	return temp;
	}

template< typename POOL > string_type<POOL> operator+( string_type<POOL> const& a, char const* str_b ) 
	{ 
	return a + string_type<POOL>( str_b );
	}

template< typename POOL > string_type<POOL> operator+( char const* str_a, string_type<POOL> const& b ) 
	{ 
	return string_type<POOL>( str_a ) + b;
	}

template< typename POOL > string_type<POOL>& operator+=( string_type<POOL>& a, string_type<POOL> const& b ) 
	{
	int const len_a = a.length();
	int const len_b = b.length();
	char* const temp = string_type<POOL>::temp_buffer( len_a + len_b );
	memcpy( temp, a.c_str(), (size_t) len_a );
	memcpy( temp + len_a, b.c_str(), (size_t) len_b );
	*( temp + len_a + len_b ) = '\0';
	a = temp;
	return a;
	}

template< typename POOL > string_type<POOL>& operator+=( string_type<POOL>& a, char const* str_b ) 
	{
	return a += string_type<POOL>( str_b );
	}

template< typename POOL > bool operator<( string_type<POOL> const& a, string_type<POOL> const& b ) 
	{ 
	return strcmp( a.c_str(), b.c_str() ) < 0;
	}

template< typename POOL > bool operator>( string_type<POOL> const& a, string_type<POOL> const& b )
	{ 
	return strcmp( a.c_str(), b.c_str() ) > 0;
	}

template< typename POOL > bool operator<=( string_type<POOL> const& a, string_type<POOL> const& b )
	{ 
	return strcmp( a.c_str(), b.c_str() ) <= 0;
	}

template< typename POOL > bool operator>=( string_type<POOL> const& a, string_type<POOL> const& b )
	{ 
	return strcmp( a.c_str(), b.c_str() ) >= 0;
	}

template< typename POOL > string_type<POOL> trim( string_type<POOL> const& str ) 
	{
	int const len = str.length();
	char const* start = str.c_str();
	while( *start && *start <= ' ' ) 
		++start;
	char const* end = str.c_str() + len - 1;
	while( end > start && *end <= ' ' )
		--end;
	return string_type<POOL>( start, end + 1 );
	}

template< typename POOL > string_type<POOL> ltrim( string_type<POOL> const& str )
	{
	char const* src = str.c_str();
	while( *src && *src <= ' ' ) 
		++src;
	return src;
	}

template< typename POOL > string_type<POOL> rtrim( string_type<POOL> const& str )
	{
	int const len = str.length();
	char const* const start = str.c_str();
	char const* end = start + len - 1;
	while( end > start && *end <= ' ' )
		--end;
	return string_type<POOL>( start, end + 1 );
	}

template< typename POOL > string_type<POOL> left( string_type<POOL> const& source, int number ) 
	{
	int const len = source.length();
	if( number < 0 ) number = 0;
	if( number > len ) number = len;
	char const* const c_str = source.c_str();
	return string_type<POOL>( c_str, c_str + number ); 
	}

template< typename POOL > string_type<POOL> right( string_type<POOL> const& source, int number ) 
	{ 
	int const len = source.length();
	if( number < 0 ) number = 0;
	if( number > len ) number = len;
	char const* const c_str = source.c_str();
	return c_str + len - number; 
	}

template< typename POOL > string_type<POOL> mid( string_type<POOL> const& source, int offset, int number ) 
	{ 
	int const len = source.length();
	if( offset < 0 ) offset = 0;
	if( offset > len ) offset = len;
	if( number < 0 ) number = len - offset;
	if( offset + number > len ) number = len - offset;
	char const* const c_str = source.c_str();
	return string_type<POOL>( c_str + offset, c_str + offset + number ); 
	}

template< typename POOL > int instr( string_type<POOL> const& haystack, char const* needle, int start ) 
	{ 
	char const* const str_a = haystack.c_str();
	char const* const str_b = needle;
	int const len_a = haystack.length();
	if( start < 0 ) start = 0;
	if( start > len_a ) start = len_a;
	char const* const find = strstr( str_a + start, str_b );
	
	return (int)( find ? ( find - str_a ) : -1 ); 
	}

template< typename POOL > int instr( string_type<POOL> const& haystack, string_type<POOL> const& needle, int start ) 
	{ 
	char const* const str_a = haystack.c_str();
	char const* const str_b = needle.c_str();
	int const len_a = haystack.length();
	if( start < 0 ) start = 0;
	if( start > len_a ) start = len_a;
	char const* const find = strstr( str_a + start, str_b );
	
	return (int)( find ? ( find - str_a ) : -1 ); 
	}

template< typename POOL > int any( string_type<POOL> const& haystack, char const* needles, int start )
	{
	char const* const str_a = haystack.c_str();
	char const* const str_b = needles;
	int const len_a = haystack.length();
	int const len_b = (int) strlen( needles );

	if( start < 0 ) start = 0;
	if( start > len_a ) start = len_a;
	
	for( int i = start; i < len_a; ++i )
		{
		for( int j = 0; j < len_b; ++j )
			{
			if( str_a[ i ] == str_b[ j ] )
				return i;            
			}
		}

	return -1; 
	}

template< typename POOL > int any( string_type<POOL> const& haystack, string_type<POOL> const& needles, int start )
	{
	char const* const str_a = haystack.c_str();
	char const* const str_b = needles.c_str();
	int const len_a = haystack.length();
	int const len_b = needles.length();

	if( start < 0 ) start = 0;
	if( start > len_a ) start = len_a;
	
	for( int i = start; i < len_a; ++i )
		{
		for( int j = 0; j < len_b; ++j )
			{
			if( str_a[ i ] == str_b[ j ] )
				return i;            
			}
		}

	return -1; 
	}

template< typename POOL > string_type<POOL> upper( string_type<POOL> const& old )
	{
	int const len = old.length();
	char* const temp = string_type<POOL>::temp_buffer( len );
	char* dst = temp;
	char const* src = old.c_str();
	for( int i = 0; i < len; ++i )
		{
		*dst++ = (char) internal::toupper( *src++ );
		}
	*dst = '\0';
	return temp; 
	}

template< typename POOL > string_type<POOL> lower( string_type<POOL> const& old )
	{
	int const len = old.length();
	char* const temp = string_type<POOL>::temp_buffer( len );
	char* dst = temp;
	char const* src = old.c_str();
	for( int i = 0; i < len; ++i )
		{
		*dst++ = (char) internal::tolower( *src++ );
		}
	*dst = '\0';
	return temp; 
	}

template< typename POOL > string_type<POOL> str( int x )
	{
	char* const temp = string_type<POOL>::temp_buffer( 16 );
	int len = internal::snprintf( temp, 16, "%d", x );
	return string_type<POOL>( temp, temp + len );
	}

template< typename POOL > string_type<POOL> str( float x )
	{
	char* const temp = string_type<POOL>::temp_buffer( 64 );
	int len = internal::snprintf( temp, 64, "%f", x );
	return string_type<POOL>( temp, temp + len );
	}

template< typename POOL > float val( string_type<POOL> const& x ) 
	{
	char const* const c_str = x.c_str();
	if( !c_str ) return 0.0f;
	return internal::atof( c_str );
	}

template< typename POOL > int integer( string_type<POOL> const& x ) 
	{
	char const* const c_str = x.c_str();
	if( !c_str ) return 0;
	return internal::atoi( c_str );
	}

template< typename POOL > string_type<POOL> space( int number ) 
	{ 
	char* const temp = string_type<POOL>::temp_buffer( number );
	char* dst = temp;
	for( int i = 0; i < number; ++i )
		{
		*dst++ = ' ';
		} 
	*dst = '\0';
	return temp; 
	}

template< typename POOL > string_type<POOL> flip( string_type<POOL> const& original ) 
	{ 
	int const len = original.length();
	char* const temp = string_type<POOL>::temp_buffer( len );
	char* dst = temp + len;
	char const* src = original.c_str();
	*dst-- = '\0';
	for( int i = 0; i < len; ++i )
		{
		*dst-- = *src++;
		}
	return temp; 
	}

template< typename POOL > string_type<POOL> repeat( string_type<POOL> const& text, int const number ) 
	{ 
	int const len = text.length();
	char* const temp = string_type<POOL>::temp_buffer( len * number );
	char* dst = temp;
	char const* src = text.c_str();
	for( int i = 0; i < number; ++i )
		{
		memcpy( dst, src, (size_t) len );
		dst += len;
		}
	*dst = '\0';
	return temp; 
	}

template< typename POOL > string_type<POOL> chr( int code ) 
	{ 
	char const str[] = { (char) code, '\0' }; 
	return str; 
	}

template< typename POOL > int asc( string_type<POOL> const& str ) 
	{ 
	char const* const c_str = str.c_str();
	
	return c_str ? (int) *c_str : 0; 
	}

template< typename POOL > int len( string_type<POOL> const& str ) 
	{ 
	return str.length(); 
	}

namespace internal {

template< typename POOL > char* temp_buffer( int size ) 
	{
	return string_type<POOL>::temp_buffer( size );
	}

char* format( char* (*temp_buffer_func)( int ), char const* format_string, char* args );

} /* namespace internal */


template< typename POOL > string_type<POOL> format( string_type<POOL> format_string, ... )
	{
	va_list args;
	va_start( args, format_string );
	char* temp = internal::format( internal::temp_buffer<POOL>, format_string.c_str(), args );
	va_end( args );
	return temp;
	}


template< typename POOL > string_type<POOL> format( string_type<POOL> format_string, va_list args )
	{
	char* temp = internal::format( internal::temp_buffer<POOL>, format_string.c_str(), args );
	return temp;
	}


} /* namespace strpool */

#endif /* strpool_util_impl */


#ifdef STRPOOL_UTIL_IMPLEMENTATION
#undef STRPOOL_UTIL_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

namespace strpool { namespace internal {
	
int snprintf( char* s, size_t n, char const* format, ... )
	{
	va_list args;
	va_start( args, format );
	#ifdef _WIN32
		int r = _vsnprintf( s, n, format, args );
	#else
	    int r = vsnprintf( s, n, format, args );
	#endif
	va_end( args );
	return r;
	}


char* format( char* (*temp_buffer_func)( int ), char const* format_string, va_list args )
	{
	char* temp = temp_buffer_func( 256 );
	#ifdef _WIN32
		int size = _vscprintf( format_string, args );
	#else
	    int size = vsnprintf( temp, 0, format_string, args );
	#endif
	temp = temp_buffer_func( size + 1 );
	#ifdef _WIN32
		_vsnprintf( temp, (size_t) size + 1, format_string, args );
	#else
		vsnprintf( temp, (size_t) size + 1, format_string, args );
	#endif
	return temp;
	}


int toupper( int c )
	{
	return ::toupper( c );
	}


int tolower( int c )
	{
	return ::tolower( c );
	}

char* strtok( char* str, char const* delimiters )
	{
	return ::strtok( str, delimiters );
	}

float atof( char const* str )
	{
	return (float)::atof( str );
	}
	
int atoi( char const* str )
	{
	return (int)::atoi( str );
	}

} /* namespace internal */ } /* namespace strpool */


#endif /* STRPOOL_UTIL_IMPLEMENTATION */


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
