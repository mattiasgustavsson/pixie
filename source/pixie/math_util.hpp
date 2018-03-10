/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

math_util.hpp - v0.1 - math helper functions for C++.

Do this:
	#define MATH_UTIL_IMPLEMENTATION
before you include this file in *one* C++ file to create the implementation.
*/

#ifndef math_util_hpp
#define math_util_hpp

namespace math_util {

#ifdef max 
	#undef max
#endif

#ifdef min
	#undef min
#endif

template< typename T, typename T1, typename T2 > T max( T1 const& a, T2 const& b );
template< typename T, typename T1, typename T2 > T min( T1 const& a, T2 const& b );
template< typename T, typename T1, typename T2, typename T3 > T clamp( T1 const& x, T2 const& min, T3 const& max );
template< typename T > void swap( T& a, T& b );

float const PI     = 3.1415926535897932384626433832795f;
float const TWO_PI = 6.2831853071795864769252867665590f;

float to_radians( float degrees );
float to_degrees( float radians );
float angle_diff( float a, float b );
float angle_lerp( float a, float b, float t );
float lerp( float a, float b, float t );

unsigned int pow2_ceil( unsigned int x );

int fast_round( float x );

short float_to_half( float f );
float half_to_float( short hf );

} /* namespace math_util */


// Unrolled macro version of pow2_ceil, which rounds a constant (at compile time) up to its nearest power-of-two value. 
#define POW2_CEIL( x ) ( (((((((x) - 1) | ( ((x) - 1) >> 1 )) | ( (((x) - 1) | ( ((x) - 1) >> 1 )) >> 2 )) \
	| ( ((((x) - 1) | ( ((x) - 1) >> 1 )) | ( (((x) - 1) | ( ((x) - 1) >> 1 )) >> 2 )) >> 4 )) | ( (((((x) - 1) \
	| ( ((x) - 1) >> 1 )) | ( (((x) - 1) | ( ((x) - 1) >> 1 )) >> 2 )) | ( ((((x) - 1) | ( ((x) - 1) >> 1 )) \
	| ( (((x) - 1) | ( ((x) - 1) >> 1 )) >> 2 )) >> 4 )) >> 8 )) | ( ((((((x) - 1) | ( ((x) - 1) >> 1 )) \
	| ( (((x) - 1) | ( ((x) - 1) >> 1 )) >> 2 )) | ( ((((x) - 1) | ( ((x) - 1) >> 1 )) | ( (((x) - 1) \
	| ( ((x) - 1) >> 1 )) >> 2 )) >> 4 )) | ( (((((x) - 1) | ( ((x) - 1) >> 1 )) | ( (((x) - 1) \
	| ( ((x) - 1) >> 1 )) >> 2 )) | ( ((((x) - 1) | ( ((x) - 1) >> 1 )) | ( (((x) - 1) \
	| ( ((x) - 1) >> 1 )) >> 2 )) >> 4 )) >> 8 )) >> 16 )) + 1 )


#endif /* math_util_hpp */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef math_util_impl
#define math_util_impl

namespace math_util {


template< typename T, typename T1, typename T2 > T max( T1 const& a, T2 const& b ) 
	{ 
	return T( a ) > T( b ) ? T( a ) : T( b ); 
	}


template< typename T, typename T1, typename T2 > T min( T1 const& a, T2 const& b ) 
	{ 
	return T( a ) < T( b ) ? T( a ) : T( b ); 
	}


template< typename T, typename T1, typename T2, typename T3 > T clamp( T1 const& x, T2 const& min, T3 const& max ) 
	{ 
	return max<T>( min<T>( x, max ), min ); 
	}


template< typename T > void swap( T& a, T& b ) 
	{ 
	T t = a; 
	a = b; 
	b = t; 
	}


} /* namespace math_util */

#endif /* math_util_impl */


#ifdef MATH_UTIL_IMPLEMENTATION
#undef MATH_UTIL_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#include <math.h>
#pragma warning( pop )

#ifndef MATH_UTIL_ASSERT
	#undef _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#undef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	#include <assert.h>
	#define MATH_UTIL_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

#if ( defined( _M_IX86_FP ) && ( _M_IX86_FP > 0 ) ) || defined( _M_X64 )
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#pragma warning( push )
	#pragma warning( disable: 4548 ) // expression before comma has no effect; expected expression with side-effect
	#include <xmmintrin.h>
	#pragma warning( pop )
#endif

namespace math_util {

float to_radians( float const degrees ) 
	{ 
	return ( degrees * PI ) / 180.0f; 
	}


float to_degrees( float const radians ) 
	{ 
	return ( radians * 180.0f ) / PI; 
	}


float angle_diff( float const a, float const b )
	{
	float d = fmodf( b - a, TWO_PI );
	return fmodf( 2.0f * d, TWO_PI ) - d;
	}


float angle_lerp( float const a, float const b, float const t )
	{
	return a + angle_diff( b, a ) * t;
	}


float lerp( float const a, float const b, float const t )
	{
	return a + ( a - b ) * t;
	}


unsigned int pow2_ceil( unsigned int x )
	{
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	++x;
	x += ( x == 0 );
	return x;
	}


int fast_round( float x )
	{
	#if ( defined( _M_IX86_FP ) && ( _M_IX86_FP > 0 ) ) || defined( _M_X64 )
		__m128 m;
		m.m128_f32[ 0 ] = x;
		return _mm_cvtss_si32( m );
	#else
		MATH_UTIL_ASSERT( fabs( x )<=0x003fffff, "Only 23 bit values handled" );
		float f = x + ( 3 << 22 );
		int i = *(int*)&f;    
		return ( i & 0x007fffff ) - 0x00400000;
	#endif
	}


short float_to_half( float f )
	{
	typedef unsigned short hfloat;

	// max exponent value in single precision that will be converted
	// to Inf or Nan when stored as a half-float
	const unsigned int HALF_FLOAT_MAX_BIASED_EXP_AS_SINGLE_FP_EXP = 0x47800000;
	const unsigned int HALF_FLOAT_MAX_BIASED_EXP = (0x1F << 10);

	// -15 stored using a single precision bias of 127
	const unsigned int HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP = 0x38000000;

	// 255 is the max exponent biased value
	const unsigned int FLOAT_MAX_BIASED_EXP = (0xFF << 23);

	unsigned int x = *(unsigned int *)(&f);
	unsigned int sign = (unsigned short)(x >> 31);
	unsigned int mantissa;
	unsigned int exp;
	hfloat hf;

	// get mantissa
	mantissa = x & ((1 << 23) - 1);
	// get exponent bits
	exp = x & FLOAT_MAX_BIASED_EXP;
	if (exp >= HALF_FLOAT_MAX_BIASED_EXP_AS_SINGLE_FP_EXP)
		{
		// check if the original single precision float number is a NaN
		if (mantissa && (exp == FLOAT_MAX_BIASED_EXP))
			{
			// we have a single precision NaN
			mantissa = (1 << 23) - 1;
			}
		else
			{
			// 16-bit half-float representation stores number as Inf
			mantissa = 0;
			}
		hf = (hfloat)( (((hfloat)sign) << 15) | (hfloat)(HALF_FLOAT_MAX_BIASED_EXP) |	(hfloat)(mantissa >> 13) );
		}
	// check if exponent is <= -15
	else if (exp <= HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP)
		{

		// store a denorm half-float value or zero
		exp = (HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP - exp) >> 23;
		mantissa >>= (14 + exp);

		hf = (hfloat)( (((hfloat)sign) << 15) | (hfloat)(mantissa) );
		}
	else
		{
		hf = (hfloat)( (((hfloat)sign) << 15) | (hfloat)((exp - HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP) >> 13) | (hfloat)(mantissa >> 13) );
		}

	return (short) hf;
	}


float half_to_float( short hf )
	{
	typedef unsigned short hfloat;

	// -15 stored using a single precision bias of 127
	const unsigned int HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP = 0x38000000;

	// 255 is the max exponent biased value
	const unsigned int FLOAT_MAX_BIASED_EXP = (0xFF << 23);

	const unsigned int HALF_FLOAT_MAX_BIASED_EXP = (0x1F << 10);

	unsigned int sign = (unsigned int)(((hfloat)hf) >> 15);
	unsigned int mantissa = (unsigned int)(((hfloat)hf) & ((1 << 10) - 1));
	unsigned int exp = (unsigned int)(((hfloat)hf) & HALF_FLOAT_MAX_BIASED_EXP);
	unsigned int f;

	if (exp == HALF_FLOAT_MAX_BIASED_EXP)
		{
		// we have a half-float NaN or Inf
		// half-float NaNs will be converted to a single precision NaN
		// half-float Infs will be converted to a single precision Inf
		exp = FLOAT_MAX_BIASED_EXP;
		if (mantissa)
			mantissa = (1 << 23) - 1;    // set all bits to indicate a NaN
		}
	else if (exp == 0x0)
		{
		// convert half-float zero/denorm to single precision value
		if (mantissa)
			{
			mantissa <<= 1;
			exp = HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP;
			// check for leading 1 in denorm mantissa
			while ((mantissa & (1 << 10)) == 0)
				{
				// for every leading 0, decrement single precision exponent by 1
				// and shift half-float mantissa value to the left
				mantissa <<= 1;
				exp -= (1 << 23);
				}
			// clamp the mantissa to 10-bits
			mantissa &= ((1 << 10) - 1);
			// shift left to generate single-precision mantissa of 23-bits
			mantissa <<= 13;
			}
		}
	else
		{
		// shift left to generate single-precision mantissa of 23-bits
		mantissa <<= 13;
		// generate single precision biased exponent value
		exp = (exp << 13) + HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP;
		}

	f = (sign << 31) | exp | mantissa;
	return *((float *)&f);
	}

} /* namespace math_util */

#endif /* MATH_UTIL_IMPLEMENTATION */

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
