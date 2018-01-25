/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

handles.h - v0.1 - Generic handles with validation, for C/C++.

Do this:
    #define HANDLES_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef handles_h
#define handles_h

#ifndef HANDLES_U64
    #define HANDLES_U64 unsigned long long
#endif

typedef struct handles_t handles_t;

void handles_init( handles_t* handles, int initial_capacity, void* memctx );
void handles_term( handles_t* handles );

int handles_alloc( handles_t* handles, int index );
void handles_release( handles_t* handles, int handle );

int handles_index( handles_t* handles, int handle );
void handles_update( handles_t* handles, int handle, int index );

int handles_validate( handles_t* handles, HANDLES_U64 u );
HANDLES_U64 handles_to_u64( handles_t* handles, int handle );
int handles_from_u64( handles_t* handles, HANDLES_U64 u );

#endif /* handles_h */


/*
----------------------
    IMPLEMENTATION
----------------------
*/

#ifndef handles_impl
#define handles_impl

struct handles_internal_data_t
    {
    int index;
    int counter;
    };

struct handles_t
    {
    void* memctx;
    struct handles_internal_data_t* data;
    int capacity;
    int count;
    int freelist_head;
    int freelist_tail;
    };

#endif /* handles_impl */


#ifdef HANDLES_IMPLEMENTATION
#undef HANDLES_IMPLEMENTATION

#ifndef HANDLES_ASSERT
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <assert.h>
    #define HANDLES_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

#ifndef HANDLES_MEMCPY
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <string.h>
    #define HANDLES_MEMCPY( dst, src, cnt ) ( memcpy( dst, src, cnt ) )
#endif 

#ifndef HANDLES_MALLOC
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <stdlib.h>
    #define HANDLES_MALLOC( ctx, size ) ( malloc( size ) )
    #define HANDLES_FREE( ctx, ptr ) ( free( ptr ) )
#endif


void handles_init( handles_t* handles, int initial_capacity, void* memctx )
    {
    handles->memctx = memctx;
    handles->count = 0;
    handles->capacity = initial_capacity <= 0 ? 1 : initial_capacity;
    handles->freelist_head = -1;
    handles->freelist_tail = -1;
    handles->data = (struct handles_internal_data_t*) HANDLES_MALLOC( memctx, handles->capacity * sizeof( *handles->data ) );
    HANDLES_ASSERT( handles->data, "Allocation failed" );
    }


void handles_term( handles_t* handles )
    {
    HANDLES_FREE( handles->memctx, handles->data );
    }


int handles_alloc( handles_t* handles, int index )
    {
    int handle;

    if( handles->count < handles->capacity )
        {
        handle = handles->count;
        handles->data[ handles->count ].counter = 0;
        ++handles->count;           
        }
    else if( handles->freelist_head >= 0 )
        {
        handle = handles->freelist_head;
        if( handles->freelist_tail == handles->freelist_head ) handles->freelist_tail = handles->data[ handles->freelist_head ].index;
        handles->freelist_head = handles->data[ handles->freelist_head ].index;                     
        }
    else
        {
        handles->capacity *= 2;
        struct handles_internal_data_t* new_data = (struct handles_internal_data_t*) HANDLES_MALLOC( handles->memctx, handles->capacity * sizeof( *handles->data ) );
        HANDLES_ASSERT( new_data, "Allocation failed" );
        HANDLES_MEMCPY( new_data, handles->data, handles->count * sizeof( *handles->data ) );
        HANDLES_FREE( handles->memctx, handles->data );
        handles->data = new_data;
        handle = handles->count;
        handles->data[ handles->count ].counter = 0;
        ++handles->count;           
        }

    handles->data[ handle ].index = index;
    return handle;
    }


void handles_release( handles_t* handles, int handle )
    {
    if( handles->freelist_tail < 0 )
        {
        HANDLES_ASSERT( handles->freelist_head < 0, "Freelist invalid" );
        handles->freelist_head = handle;
        handles->freelist_tail = handle;
        }
    else
        {
        handles->data[ handles->freelist_tail ].index = handle;
        handles->freelist_tail = handle;
        }
    ++handles->data[ handle ].counter; // invalidate handle via counter
    handles->data[ handle ].index = -1;
    }


int handles_index( handles_t* handles, int handle )
    {
    if( handle >= 0 && handle < handles->count )
        return handles->data[ handle ].index;
    else
        return -1;
    }


void handles_update( handles_t* handles, int handle, int index )
    {
    handles->data[ handle ].index = index;
    }


static HANDLES_U64 to_u64( int handle, int counter )
    {
    HANDLES_U64 const i = (HANDLES_U64) ( handle + 1 );
    HANDLES_U64 const c = (HANDLES_U64) counter;
    return ( c << 32ull ) | ( i );
    }


static int u64_to_counter( HANDLES_U64 u )
    {
    return (int) ( u >> 32ull ) ;
    }
    

static int u64_to_handle( HANDLES_U64 u )
    {
    return ( (int) ( u & 0xffffffffull ) ) - 1;
    }


HANDLES_U64 handles_to_u64( handles_t* handles, int handle )
    {
    return to_u64( handle, handles->data[ handle ].counter );
    }


int handles_from_u64( handles_t* handles, HANDLES_U64 u )
    {
    int const handle = u64_to_handle( u );
    if( handle >= 0 && handle < handles->count && handles->data[ handle ].counter == u64_to_counter( u ) )
        {
        return handle;
        }
    else
        {
        return -1;
        }
    }


int handles_validate( handles_t* handles, HANDLES_U64 u )
    {
    int const handle = u64_to_handle( u );
    return handle >= 0 && handle < handles->count && handles->data[ handle ].counter == u64_to_counter( u );
    }


#endif /* HANDLES_IMPLEMENTATION */

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

