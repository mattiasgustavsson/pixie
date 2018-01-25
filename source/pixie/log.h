/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

log.h - v0.1 - Simple file/console logging helper for C/C++.

Do this:
	#define LOG_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef log_h
#define log_h

typedef struct log_t log_t;

log_t* log_create( char const* filename, void* memctx );
void log_destroy( log_t* log );
void log_print( log_t* log, char const* str, ... );
void log_print_pending( log_t* log, char const* str, ... );
void log_discard_pending( log_t* log );
void log_commit_pending( log_t* log );
int log_mute( log_t* log );
int log_unmute( log_t* log );

#endif /* log_h */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef LOG_IMPLEMENTATION
#undef LOG_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef LOG_MALLOC
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <stdlib.h>
    #define LOG_MALLOC( ctx, size ) ( malloc( size ) )
    #define LOG_FREE( ctx, ptr ) ( free( ptr ) )
#endif

struct log_t
	{
    void* memctx;
	char* data;
	size_t capacity;
	size_t size;
	size_t pending_point;
	int muted;
	FILE* fp;
	};


log_t* log_create( char const* const filename, void* memctx )
	{
	log_t* log = (log_t*) LOG_MALLOC( memctx, sizeof( log_t ) );
    log->memctx = memctx;
	log->data = 0;
	log->capacity = 0;
	log->size = 0;
	log->pending_point = ~(size_t) 0;
	log->muted = 0;
	if( filename )
		log->fp = fopen( filename, "w" );
	else
		log->fp = 0;

	return log;
	}


void log_destroy( log_t* const log )
	{
	log_commit_pending( log );
	if( log->fp ) fclose( log->fp );
	if( log->data ) LOG_FREE( log->memctx, log->data );
	LOG_FREE( log->memctx, log );
	}


static void alloc_data( log_t* const log, int const count )
	{
	if( log->data )
		{
		while( count >= (int) ( log->capacity - log->size ) )
			{
			log->capacity *= 2; 
			}
        char* new_data = (char*) LOG_MALLOC( log->memctx, log->capacity );
        memcpy( new_data, log->data, log->size + 1 );
        LOG_FREE( log->memctx, log->data );
		log->data = new_data;
		}
	else
		{
		log->capacity = 256;
		while( count >= (int) ( log->capacity - log->size ) )
			{
			log->capacity *= 2; 
			}
		log->data = (char*) LOG_MALLOC( log->memctx, log->capacity );
		}
	}


void log_print( log_t* const log, char const* const str, ... )
	{
  	if( !log ) return;
	if( log->muted ) return;

	log->pending_point = ~(size_t) 0;
	va_list args;
	va_start (args, str);
	int count = _vsnprintf( log->data + log->size, log->capacity - log->size, str, args );
	va_end (args);
	if( count >= (int) ( log->capacity - log->size ) )
		{
		alloc_data( log, count );
		va_start (args, str);
		count = _vsnprintf( log->data + log->size, log->capacity - log->size, str, args );
		va_end (args);
		}
	log->size += count;
	log_commit_pending( log );
	}


void log_print_pending( log_t* const log, char const* const str, ... )
	{
	if( log->muted ) return;
	
	if( log->pending_point > log->size ) log->pending_point = log->size;
		
	va_list args;
	va_start (args, str);
	int count = _vsnprintf( log->data + log->size, log->capacity - log->size, str, args );
	va_end (args);
	if( count >= (int) ( log->capacity - log->size ) )
		{
		alloc_data( log, count );
		va_start (args, str);
		count = _vsnprintf( log->data + log->size, log->capacity - log->size, str, args );
		va_end (args);
		}
	log->size += count;
	}


void log_discard_pending( log_t* const log )
	{
	if( log->muted ) return;
	
	if( log->pending_point != ~(size_t) 0 ) 
		log->size = log->pending_point;
	
	log->pending_point = ~(size_t) 0;
	}


void log_commit_pending( log_t* const log )
	{
	log->pending_point = ~(size_t) 0;

	if( log->muted ) return;

	if( log->data )
		{
		fprintf( stdout, "%s", log->data );
		if( log->fp )
			{
			fprintf( log->fp, "%s", log->data );
			}
		log->data[ 0 ] = 0;
		}
	fflush( stdout ); 
	if( log->fp )
		fflush( log->fp ); 
	log->size = 0;	
	}


int log_mute( log_t* log )
	{
	++log->muted;
	return log->muted;
	}


int log_unmute( log_t* log )
	{
	--log->muted;
	return log->muted;
	}


#endif /* LOG_IMPLEMENTATION */


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
