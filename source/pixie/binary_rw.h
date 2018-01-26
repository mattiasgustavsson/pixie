/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

binary_rw.h - v0.1 - Binary serialization of basic data types, for C/C++.


Do this:
	#define BINARY_RW_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef binary_rw_h
#define binary_rw_h

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

#ifndef BINARY_RW_CHAR
	// on older MSVC versions, char is same as i8
	#if !defined(_MSC_VER) || _MSC_VER >= 1600 
		#define BINARY_RW_CHAR char
	#endif
#endif

#ifndef BINARY_RW_I8
	#define BINARY_RW_I8 signed char
#endif

#ifndef BINARY_RW_I16
	#define BINARY_RW_I16 signed short
#endif

#ifndef BINARY_RW_I32
	#define BINARY_RW_I32 signed int
#endif

#ifndef BINARY_RW_I64
	#define BINARY_RW_I64 signed long long
#endif

#ifndef BINARY_RW_U8
	#define BINARY_RW_U8 unsigned char
#endif

#ifndef BINARY_RW_U16
	#define BINARY_RW_U16 unsigned short
#endif

#ifndef BINARY_RW_U32
	#define BINARY_RW_U32 unsigned int
#endif

#ifndef BINARY_RW_U64
	#define BINARY_RW_U64 unsigned long long
#endif

#ifndef BINARY_RW_FLOAT
	#define BINARY_RW_FLOAT float
#endif

#ifndef BINARY_RW_DOUBLE
	#define BINARY_RW_DOUBLE double
#endif

#ifndef BINARY_RW_BOOL
	#define BINARY_RW_BOOL bool
#endif


struct binary_rw_data_t { size_t size; void* data; };


struct binary_rw_reader_t
	{
	binary_rw_data_t const* binary;
	size_t position;
	};

void binary_rw_reader_init( binary_rw_reader_t* reader, binary_rw_data_t const* binary );
void binary_rw_reader_term( binary_rw_reader_t* reader );

void binary_rw_reader_reset( binary_rw_reader_t* reader );

void binary_rw_reader_position_set( binary_rw_reader_t* reader, size_t pos );
size_t binary_rw_reader_position( binary_rw_reader_t* reader );

#ifdef BINARY_RW_CHAR
	int binary_rw_reader_char( binary_rw_reader_t* reader, BINARY_RW_CHAR* value, int count );
#endif
	
#ifdef BINARY_RW_BOOL
	int binary_rw_reader_bool( binary_rw_reader_t* reader, BINARY_RW_BOOL* value, int count );	
#endif

int binary_rw_reader_i8( binary_rw_reader_t* reader, BINARY_RW_I8* value, int count );
int binary_rw_reader_i16( binary_rw_reader_t* reader, BINARY_RW_I16* value, int count );
int binary_rw_reader_i32( binary_rw_reader_t* reader, BINARY_RW_I32* value, int count );
int binary_rw_reader_i64( binary_rw_reader_t* reader, BINARY_RW_I64* value, int count );

int binary_rw_reader_u8( binary_rw_reader_t* reader, BINARY_RW_U8* value, int count );
int binary_rw_reader_u16( binary_rw_reader_t* reader, BINARY_RW_U16* value, int count );
int binary_rw_reader_u32( binary_rw_reader_t* reader, BINARY_RW_U32* value, int count );
int binary_rw_reader_u64( binary_rw_reader_t* reader, BINARY_RW_U64* value, int count );

int binary_rw_reader_float( binary_rw_reader_t* reader, BINARY_RW_FLOAT* value, int count );
int binary_rw_reader_double( binary_rw_reader_t* reader, BINARY_RW_DOUBLE* value, int count );


typedef void (*binary_rw_resize_func_t)( binary_rw_data_t* binary, size_t new_size, void* resize_context ); 

struct binary_rw_writer_t
	{
	binary_rw_data_t* binary;
	size_t position;
	binary_rw_resize_func_t resize;
	void* resize_context;
	};

void binary_rw_writer_init( binary_rw_writer_t* writer, binary_rw_data_t* binary, 
	binary_rw_resize_func_t resize_func, void* resize_context );
void binary_rw_writer_term( binary_rw_writer_t* writer);

void binary_rw_writer_reset( binary_rw_writer_t* writer );

void binary_rw_writer_position_set( binary_rw_writer_t* writer, size_t pos );
size_t binary_rw_writer_position( binary_rw_writer_t* writer );
	
#ifdef BINARY_RW_CHAR
	int binary_rw_writer_char( binary_rw_writer_t* writer, BINARY_RW_CHAR const* value, int count );
#endif
	
#ifdef BINARY_RW_BOOL
	int binary_rw_writer_bool( binary_rw_writer_t* writer, BINARY_RW_BOOL const* value, int count );	
#endif

int binary_rw_writer_i8( binary_rw_writer_t* writer, BINARY_RW_I8 const* value, int count );
int binary_rw_writer_i16( binary_rw_writer_t* writer, BINARY_RW_I16 const* value, int count );
int binary_rw_writer_i32( binary_rw_writer_t* writer, BINARY_RW_I32 const* value, int count );
int binary_rw_writer_i64( binary_rw_writer_t* writer, BINARY_RW_I64 const* value, int count );
int binary_rw_writer_u8( binary_rw_writer_t* writer, BINARY_RW_U8 const* value, int count );
int binary_rw_writer_u16( binary_rw_writer_t* writer, BINARY_RW_U16 const* value, int count );
int binary_rw_writer_u32( binary_rw_writer_t* writer, BINARY_RW_U32 const* value, int count );
int binary_rw_writer_u64( binary_rw_writer_t* writer, BINARY_RW_U64 const* value, int count );
int binary_rw_writer_float( binary_rw_writer_t* writer, BINARY_RW_FLOAT const* value, int count );
int binary_rw_writer_double( binary_rw_writer_t* writer, BINARY_RW_DOUBLE const* value, int count );
	

#endif /* binary_rw_h */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef BINARY_RW_IMPLEMENTATION
#undef BINARY_RW_IMPLEMENTATION


void binary_rw_reader_init( binary_rw_reader_t* reader, binary_rw_data_t const* binary )
	{
	reader->binary = binary;
	reader->position = 0;
	}


void binary_rw_reader_term( binary_rw_reader_t* reader )
	{
	(void) reader;
	}


void binary_rw_reader_reset( binary_rw_reader_t* reader )
	{
	reader->position = 0;
	}


void binary_rw_reader_position_set( binary_rw_reader_t* reader, size_t pos )
	{
	reader->position = pos;
	}


size_t binary_rw_reader_position( binary_rw_reader_t* reader )
	{
	return reader->position;
	}


#ifdef BINARY_RW_CHAR
	int binary_rw_reader_char( binary_rw_reader_t* reader, BINARY_RW_CHAR* value, int count )
		{
		if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
		BINARY_RW_CHAR* ptr = (BINARY_RW_CHAR*)( ( (uintptr_t)reader->binary->data ) + reader->position );
		for( int i = 0; i < count; ++i ) 
			{
			reader->position += sizeof( *ptr );
			if( reader->position > reader->binary->size ) return i;
			*value++ = *ptr++;
			}
		return count;
		}
#endif		

	
#ifdef BINARY_RW_BOOL
	int binary_rw_reader_bool( binary_rw_reader_t* reader, BINARY_RW_BOOL* value, int count )
	    {
	    if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	    BINARY_RW_U8* ptr = (BINARY_RW_U8*)( ( (uintptr_t)reader->binary->data ) + reader->position ); // BOOL is stored as 8 bit unsigned
	    for( int i = 0; i < count; ++i ) 
		    {
		    reader->position += sizeof( *ptr );
		    if( reader->position > reader->binary->size ) return i;
		    *value++ = ( *ptr++ ) != 0; // translate between bool and u8
		    }
	    return count;
	    }
#endif		
		
	
int binary_rw_reader_i8( binary_rw_reader_t* reader, BINARY_RW_I8* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_I8* ptr = (BINARY_RW_I8*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_i16( binary_rw_reader_t* reader, BINARY_RW_I16* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_I16* ptr = (BINARY_RW_I16*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_i32( binary_rw_reader_t* reader, BINARY_RW_I32* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_I32* ptr = (BINARY_RW_I32*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_i64( binary_rw_reader_t* reader, BINARY_RW_I64* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_I64* ptr = (BINARY_RW_I64*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_u8( binary_rw_reader_t* reader, BINARY_RW_U8* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_U8* ptr = (BINARY_RW_U8*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_u16( binary_rw_reader_t* reader, BINARY_RW_U16* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_U16* ptr = (BINARY_RW_U16*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_u32( binary_rw_reader_t* reader, BINARY_RW_U32* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_U32* ptr = (BINARY_RW_U32*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_u64( binary_rw_reader_t* reader, BINARY_RW_U64* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_U64* ptr = (BINARY_RW_U64*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_float( binary_rw_reader_t* reader, BINARY_RW_FLOAT* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_FLOAT* ptr = (BINARY_RW_FLOAT*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	
	
int binary_rw_reader_double( binary_rw_reader_t* reader, BINARY_RW_DOUBLE* value, int count )
	{
	if( reader->binary->data == 0 || reader->binary->size == 0 ) return 0;
	BINARY_RW_DOUBLE* ptr = (BINARY_RW_DOUBLE*)( ( (uintptr_t)reader->binary->data ) + reader->position );
	for( int i = 0; i < count; ++i ) 
		{
		reader->position += sizeof( *ptr );
		if( reader->position > reader->binary->size ) return i;
		*value++ = *ptr++;
		}
	return count;
	}
	


void binary_rw_writer_init( binary_rw_writer_t* writer, binary_rw_data_t* binary, 
	binary_rw_resize_func_t resize_func, void* resize_context )
	{
	writer->binary = binary;
	writer->position = 0;
	writer->resize = resize_func;
	writer->resize_context = resize_context;
	}


void binary_rw_writer_term( binary_rw_writer_t* writer)
	{
	(void) writer;
	}


void binary_rw_writer_reset( binary_rw_writer_t* writer )
	{
	writer->position = 0;
	}


void binary_rw_writer_position_set( binary_rw_writer_t* writer, size_t pos )
	{
	writer->position = pos;
	}


size_t binary_rw_writer_position( binary_rw_writer_t* writer )
	{
	return writer->position;
	}



#ifdef BINARY_RW_CHAR
	int binary_rw_writer_char( binary_rw_writer_t* writer, BINARY_RW_CHAR const* value, int count )
		{
		if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
		
		BINARY_RW_CHAR* ptr = (BINARY_RW_CHAR*)( ( (uintptr_t)writer->binary->data ) + writer->position );
		for( int i = 0; i < count; ++i ) 
			{
			writer->position += sizeof( *ptr );
			if( writer->position > writer->binary->size ) 
				{
				if( writer->resize )
					writer->resize( writer->binary, writer->position, writer->resize_context );
				else
					return i;
				}
			*ptr++ = *value++;
			}
		return count;
		}
#endif		
	

#ifdef BINARY_RW_BOOL
	int binary_rw_writer_bool( binary_rw_writer_t* writer, BINARY_RW_BOOL const* value, int count )
	    {
	    if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	    BINARY_RW_U8* ptr = (BINARY_RW_U8*)( ( (uintptr_t)writer->binary->data ) + writer->position ); // BOOL is stored as 8 bit unsigned
	    for( int i = 0; i < count; ++i ) 
		    {
		    writer->position += sizeof( *ptr );
			if( writer->position > writer->binary->size ) 
				{
				if( writer->resize )
					writer->resize( writer->binary, writer->position, writer->resize_context );
				else
					return i;
				}
		    *ptr++ = (BINARY_RW_U8)( (*value++) == 0 ? 0 : 1 ); // translate between bool and u8
		    }
	    return count;
	    }	
#endif		


int binary_rw_writer_i8( binary_rw_writer_t* writer, BINARY_RW_I8 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_I8* ptr = (BINARY_RW_I8*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_i16( binary_rw_writer_t* writer, BINARY_RW_I16 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_I16* ptr = (BINARY_RW_I16*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_i32( binary_rw_writer_t* writer, BINARY_RW_I32 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_I32* ptr = (BINARY_RW_I32*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_i64( binary_rw_writer_t* writer, BINARY_RW_I64 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_I64* ptr = (BINARY_RW_I64*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_u8( binary_rw_writer_t* writer, BINARY_RW_U8 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_U8* ptr = (BINARY_RW_U8*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_u16( binary_rw_writer_t* writer, BINARY_RW_U16 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_U16* ptr = (BINARY_RW_U16*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_u32( binary_rw_writer_t* writer, BINARY_RW_U32 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_U32* ptr = (BINARY_RW_U32*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_u64( binary_rw_writer_t* writer, BINARY_RW_U64 const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_U64* ptr = (BINARY_RW_U64*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_float( binary_rw_writer_t* writer, BINARY_RW_FLOAT const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_FLOAT* ptr = (BINARY_RW_FLOAT*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
int binary_rw_writer_double( binary_rw_writer_t* writer, BINARY_RW_DOUBLE const* value, int count )
	{
	if( writer->binary->data == 0 || writer->binary->size == 0 ) return 0;
	BINARY_RW_DOUBLE* ptr = (BINARY_RW_DOUBLE*)( ( (uintptr_t)writer->binary->data ) + writer->position );
	for( int i = 0; i < count; ++i ) 
		{
		writer->position += sizeof( *ptr );
		if( writer->position > writer->binary->size ) 
			{
			if( writer->resize )
				writer->resize( writer->binary, writer->position, writer->resize_context );
			else
				return i;
			}
		*ptr++ = *value++;
		}
	return count;
	}
	
	
	
#endif /* BINARY_RW_IMPLEMENTATION */

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
