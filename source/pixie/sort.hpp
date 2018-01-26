/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

sort.hpp - v1.0 - High quality sort function for C++. 

Based on the implementation from the paper "Engineering a Sort Function" by
Jon L Bentley and M Douglas McIlroy (1993). 
http://cs.fit.edu/~pkc/classes/writing/samples/bentley93engineering.pdf

The code has been restructured and made to be partially iterative (with a 
manual data stack) instead of fully recursive. When run through a large set 
of tests with different initial data organization, it seems to be on about 
the same level as MSVC's std::sort. In the case where a custom compare 
function is used in place of the comparison operator of the type, this 
implementation has significantly better performance, due to inlining of the 
compare function. I am not an expert in sorting though, so tests might be 
faulty. In any case, it works well for my use cases, with a tiny code 
footprint, for those times when STL is not an option.
*/

#ifndef sort_hpp
#define sort_hpp

namespace sort_ns {


template< typename T > void sort( T* array, int count );

template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void sort( T* array, int count );


} /* namespace sort_ns */

#endif /* sort_hpp */

/** 

Example
=======

	#include "sort.hpp"
	using namespace sort_ns;

	int main( int argc, char** argv )
		{
		(void) argc, argv;
		
		int values[ 10 ] = { 7, 6, 3, 9, 5, 4, 8, 2, 0, 1 };
		sort( values, 10 );
		for( int i = 0; i < 10; ++i ) printf( "%d ", values[ i ] );
		return 0;
		}
	



API Documentation
=================

sort
----

	template< typename T > void sort( T* array, int count );
	template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void sort( T* array, int count );

Sorts the given array, containing `count` items. `COMPARE_FUNC` is a custom compare function, used to compare two 
elements for sorting. It must return a negative integer value if the first argument is less than the second, 
a positive integer value if the first argument is greater than the second and zero if the arguments are equal.

**/

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef sort_impl
#define sort_impl

namespace sort_ns {


template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > 
void sort( T* array, int count )
	{
	#define SORT_INTERNAL_MED3( a, b, c ) \
		( COMPARE_FUNC( *(a), *(b) ) < 0 \
			? ( COMPARE_FUNC( *(b), *(c) ) < 0 ? (b) : COMPARE_FUNC( *(a), *(c) ) < 0 ? (c) : (a) ) \
			: ( COMPARE_FUNC( *(b), *(c) ) > 0 ? (b) : COMPARE_FUNC( *(a), *(c) ) > 0 ? (c) : (a)) )

	#define SORT_INTERNAL_SWAP( a, b ) \
		{ T t = *(a); *(a) = *(b); *(b) = t; }
	
	#define SORT_INTERNAL_SWAP_RANGE( a, b, n ) \
		{ int sn = (n); T* sa = (a); T* sb = (b); while( sn > 0 ) { SORT_INTERNAL_SWAP( sa, sb ); ++sa; ++sb; --sn; } }

	#define SORT_INTERNAL_MIN( a, b ) \
		( ( (a) < (b) ) ? (a) : (b) )

	struct { int start; int count; } stack[ 32 ];
	
	int top = 0;
	stack[ top ].start = 0;
	stack[ top ].count = count;

	while ( top >= 0 )    
		{
		T* a = array + stack[ top ].start;
		count = stack[ top-- ].count;
		
		if( count < 24 ) // Insertion sort on smallest arrays
			{
			for( T* pm = a + 1; pm < a + count; ++pm )
				for( T* pl = pm; pl > a && COMPARE_FUNC( *( pl - 1 ), *pl ) > 0; --pl )
					SORT_INTERNAL_SWAP( pl, pl - 1 );
			continue;
			}
		T* pm = a + count / 2; // Small arrays, middle element
		if( count > 40 ) // Big arrays, pseudomedian of 9
			{
			T* pl = a;
			T* pn = a + count - 1;
			int s = count / 8;
			pl = SORT_INTERNAL_MED3( pl, pl + s, pl + 2 * s );
			pm = SORT_INTERNAL_MED3( pm - s, pm, pm + s );
			pn = SORT_INTERNAL_MED3( pn - 2 * s, pn - s, pn );
			pm = SORT_INTERNAL_MED3( pl, pm, pn ); // Mid-size, med of 3
			}
		T* pv = a; SORT_INTERNAL_SWAP( pv, pm ); // pv points to partition value
		T* pa = a;
		T* pb = a;
		T* pc = a + count - 1;
		T* pd = pc;
		for( ;; ) 
			{
			int r;
			while( pb <= pc && ( r = COMPARE_FUNC( *pb, *pv ) ) <= 0 ) 
				{
				if( r == 0 ) { SORT_INTERNAL_SWAP( pa, pb ); ++pa; }
				++pb;
				}
			while( pc >= pb && ( r = COMPARE_FUNC( *pc, *pv ) ) >= 0 ) 
				{
				if( r == 0 ) { SORT_INTERNAL_SWAP( pc, pd ); --pd; }
				--pc;
				}
			if( pb > pc ) break;
			SORT_INTERNAL_SWAP( pb, pc ); 
			++pb; --pc;
			}
		T* pn = a + count;
		int s = (int)SORT_INTERNAL_MIN( pa - a, pb - pa ); SORT_INTERNAL_SWAP_RANGE( a, pb - s, s );
		s = (int)SORT_INTERNAL_MIN( pd - pc, pn - pd - 1 ); SORT_INTERNAL_SWAP_RANGE( pb, pn - s, s );     
		if( ( s = (int)( pb - pa ) ) > 1 ) 
			{
			if( ++top >= sizeof( stack) / sizeof( *stack ) ) { --top; sort<T, COMPARE_FUNC>( a, s ); }
			else { stack[ top ].start = (int)( a - array ); stack[ top ].count = s; }
			}
		if( ( s = (int)( pd - pc ) ) > 1 ) 
			{
			if( ++top >= sizeof( stack) / sizeof( *stack ) ) { --top; sort<T, COMPARE_FUNC>( pn - s, s ); }
			else { stack[ top ].start = (int)( ( pn - s ) - array ); stack[ top ].count = s; }
			}
		}
	
	#undef SORT_INTERNAL_MED3
	#undef SORT_INTERNAL_SWAP
	#undef SORT_INTERNAL_SWAP_RANGE
	#undef SORT_INTERNAL_MIN
	}


template< typename T > 
inline int sort_default_cmp( T const& a, T const& b ) 
	{ 
	return a < b ? -1 : a > b ? 1 : 0; 
	}


template< typename T > 
void sort( T* array, int count ) 
	{ 
	sort< T, &sort_default_cmp<T> >( array, count ); 
	}


} /* namespace sort_ns */


#endif /* sort_impl */

/*
------------------------------------------------------------------------------

This software is available under 2 licenses - you may choose the one you like.

------------------------------------------------------------------------------

ALTERNATIVE A - MIT License

Copyright (c) 2016 Mattias Gustavsson

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

This is free and unencumbered software relpalrled into the public domain.

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

