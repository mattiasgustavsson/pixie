/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

cpp_compat.hpp - v0.1 - C++ compatibility workarounds for some systems/compilers.

Ensures we can use final, override and nullptr in all compilers.
Defines a STATIC_ASSERT macro to make static asserts available everywhere.
Makes available the basic integer types from <stdint.h> for all compilers.
*/

#ifndef cpp_compat_hpp
#define cpp_compat_hpp

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

// clang-compatible macros
#ifndef __has_builtin         
	#define __has_builtin( x ) 0  // Compatibility with non-clang compilers.
#endif

#ifndef __has_feature         
	#define __has_feature( x ) 0  // Compatibility with non-clang compilers.
#endif

#ifndef __has_extension
	#define __has_extension __has_feature // Compatibility with pre-3.0 compilers.
#endif

// final
#if ( defined(_MSC_VER) && _MSC_VER < 1700 ) \
||	( defined( __GNUC__) && !defined( __clang__ ) && !( __GNUC__ >= 4 && __GNUC_MINOR__ >= 7 ) ) \
||  ( defined( __clang__ ) && !( __has_feature( cxx_override_control ) || __has_extension( cxx_override_control ) ) )
	#define final
#endif

// override
#if ( defined(_MSC_VER) && _MSC_VER < 1400 ) \
||	( defined( __GNUC__) && !defined( __clang__ ) && !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 7 ) ) \
||  ( defined( __clang__ ) && !( __has_feature( cxx_override_control ) || __has_extension( cxx_override_control ) ) )
	#define override
#endif

// nullptr
#if ( defined(_MSC_VER) && _MSC_VER < 1600 ) \
||	( defined( __GNUC__) && !defined( __clang__ ) && !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 6 ) ) \
||  ( defined( __clang__ ) && !( __has_feature( cxx_nullptr ) || __has_extension( cxx_nullptr ) ) )

	struct nullptr_t
		{
		template< typename T > 
		operator T*() const 
			{ 
			return 0; 
			}

		template< typename T, typename U > 
		operator U T::*() const
			{ 
			return 0; 
			}

		private:
			void operator&() const;

		};

	nullptr_t const nullptr = {};

#endif

// static_assert
#if ( defined(_MSC_VER) && _MSC_VER < 1600 ) \
||	( defined( __GNUC__) && !defined( __clang__ ) && !( __GNUC__ >= 4 && __GNUC_MINOR__ >= 3 ) ) \
||  ( defined( __clang__ ) && !( __has_feature( cxx_static_assert ) || __has_extension( cxx_static_assert ) ) )
	#define CPP_COMPAT_CONCAT_IMPL( x, y ) x##y
	#define CPP_COMPAT_CONCAT_MACRO( x, y ) CPP_COMPAT_CONCAT_IMPL( x, y )

	#define STATIC_ASSERT( expression, message ) \
		struct CPP_COMPAT_CONCAT_MACRO( static_assert_, __COUNTER__ ) \
			{ int (message) : !!( (expression) ); } 
#else
	#define STATIC_ASSERT( expression, message ) \
		static_assert( expression, #message )
#endif

// stdint
#if defined(_MSC_VER) && _MSC_VER < 1600

	typedef __int8 int8_t;
	typedef unsigned __int8 uint8_t;
	typedef __int16 int16_t;
	typedef unsigned __int16 uint16_t;
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#else
	#include <stdint.h>
#endif

#if defined(_MSC_VER) && _MSC_VER < 1500
	#include <time.h>
#endif


/*
// MSVC version numbers, for reference
MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio 2002)
MSVC++ 6.0  _MSC_VER == 1200
MSVC++ 5.0  _MSC_VER == 1100
*/

#endif /* cpp_compat_hpp */

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
