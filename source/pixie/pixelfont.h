/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

pixelfont.h - v0.1 - 

Do this:
	#define PIXELFONT_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef pixelfont_h
#define pixelfont_h

#ifndef PIXELFONT_I8
    #define PIXELFONT_I8 signed char
#endif

#ifndef PIXELFONT_U8
    #define PIXELFONT_U8 unsigned char
#endif

#ifndef PIXELFONT_U16
    #define PIXELFONT_U16 unsigned short
#endif

#ifndef PIXELFONT_U32
    #define PIXELFONT_U32 unsigned int
#endif

typedef struct pixelfont_t
	{
	PIXELFONT_U32 size_in_bytes;
	PIXELFONT_U8 height;
	PIXELFONT_U8 line_spacing;
	PIXELFONT_U8 baseline;
	PIXELFONT_U16 offsets[ 256 ];
	PIXELFONT_U8 glyphs[ 1 ]; // "open" array - ok to access out of bounds (use size_in_bytes to determine the end)
	} pixelfont_t;


typedef enum pixelfont_align_t
	{
	PIXELFONT_ALIGN_LEFT,
	PIXELFONT_ALIGN_RIGHT,
	PIXELFONT_ALIGN_CENTER,
	} pixelfont_align_t;


typedef enum pixelfont_bold_t
    {
    PIXELFONT_BOLD_OFF,
    PIXELFONT_BOLD_ON,
    } pixelfont_bold_t;


typedef enum pixelfont_italic_t
    {
    PIXELFONT_ITALIC_OFF,
    PIXELFONT_ITALIC_ON,
    } pixelfont_italic_t;


typedef enum pixelfont_underline_t
    {
    PIXELFONT_UNDERLINE_OFF,
    PIXELFONT_UNDERLINE_ON,
    } pixelfont_underline_t;


typedef struct pixelfont_bounds_t
    { 
    int width; 
    int height; 
    } pixelfont_bounds_t;

#endif /* pixelfont_h */


#ifndef PIXELFONT_COLOR
    #define PIXELFONT_COLOR PIXELFONT_U8
#endif

#ifndef PIXELFONT_FUNC_NAME 
    #define PIXELFONT_FUNC_NAME pixelfont_blit
#endif

void PIXELFONT_FUNC_NAME( pixelfont_t const* font, int x, int y, char const* text, PIXELFONT_COLOR color, 
    PIXELFONT_COLOR* target, int width, int height, pixelfont_align_t align, int wrap_width, int hspacing, 
    int vspacing, int limit, pixelfont_bold_t bold, pixelfont_italic_t italic, pixelfont_underline_t underline, 
    pixelfont_bounds_t* bounds );


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef PIXELFONT_IMPLEMENTATION
#undef PIXELFONT_IMPLEMENTATION

#ifndef PIXELFONT_PIXEL_FUNC
    #define PIXELFONT_PIXEL_FUNC( dst, src ) *(dst) = (src);
#endif

void PIXELFONT_FUNC_NAME( pixelfont_t const* font, int x, int y, char const* text, PIXELFONT_COLOR color, 
    PIXELFONT_COLOR* target, int width, int height, pixelfont_align_t align, int wrap_width, int hspacing, 
    int vspacing,  int limit, pixelfont_bold_t bold, pixelfont_italic_t italic, pixelfont_underline_t underline, 
    pixelfont_bounds_t* bounds )
	{
	int xp = x;
	int yp = y;
	int max_x = x;
	int last_x_on_line = xp;
	int count = 0;
	char const* str = text;
	while( *str )
		{	
        int line_char_count = 0;
		int line_width = 0;
        int last_space_char_count = 0;
        int last_space_width = 0;
		char const* tstr = str; 
		while( *tstr != '\n' && *tstr != '\0' && ( wrap_width <= 0 || line_width <= wrap_width  ) )
			{
            if( *tstr <= ' ' )
                {
                last_space_char_count = line_char_count;
                last_space_width = line_width;
                }
			PIXELFONT_U8 const* g = font->glyphs + font->offsets[ (int) *tstr ];
			line_width += (PIXELFONT_I8) *g++;
			int w = *g++;
			g += font->height * w;
			line_width += (PIXELFONT_I8) *g++;
			line_width += hspacing + ( bold ? 1 : 0 );
			++tstr;
			int kern = *g++;
			for( int k = 0; k < kern; ++k )
				if( *g++ == *tstr ) { line_width += (PIXELFONT_I8) *g++; break; } else ++g;
            ++line_char_count;
			}
        bool skip_space = false;
        if( wrap_width > 0 && line_width > wrap_width )
            {
            line_char_count = last_space_char_count;
            line_width = last_space_width;
            skip_space = true;
            }

        if( wrap_width > 0 )
            {
            if( align == PIXELFONT_ALIGN_RIGHT ) x += wrap_width - line_width;
            if( align == PIXELFONT_ALIGN_CENTER ) x += ( wrap_width - line_width ) / 2;
            }
        else
            {
            if( align == PIXELFONT_ALIGN_RIGHT ) x -= line_width;
            if( align == PIXELFONT_ALIGN_CENTER ) x -= line_width / 2;
            }

        for( int c = 0; c < line_char_count; ++c )
            {
		    PIXELFONT_U8 const* g = font->glyphs + font->offsets[ (int) *str ];
            x += (PIXELFONT_I8) *g++;
		    int w = *g++;
		    int h = font->height;
		    for( int iy = y; iy < y + h; ++iy )
                {
                int xs = x + ( italic ? ( h - ( iy - y ) ) / 2 - 1 : 0 );
			    for( int ix = xs; ix < xs + w; ++ix )
				    {
				    if( *g++ && target ) 
					    if( limit < 0 || count < limit )
						    if( ix >= 0 && iy >= 0 && ix < width && iy < height )
							    {
							    last_x_on_line = ix >= last_x_on_line ? ix + ( bold ? 1 : 0 ) : last_x_on_line;
							    PIXELFONT_PIXEL_FUNC( ( &target[ ix + iy * width ] ), color );
							    if( bold && ix + 1 < width ) 
                                    PIXELFONT_PIXEL_FUNC( ( &target[ ix + 1 + iy * width ] ), color );
							    }
				    }
                }
   			
		    x += (PIXELFONT_I8) *g++;
            x += hspacing + ( bold ? 1 : 0 );
		    ++str;
		    ++count;

            int kern = *g++;
            for( int k = 0; k < kern; ++k )
                if( *g++ == *str ) { x += (PIXELFONT_I8) *g++; break; } else ++g;
		
            }

            if( underline && target && y + font->baseline + 1 >= 0 && y + font->baseline + 1 < height && last_x_on_line > xp ) 
				for( int ix = xp; ix <= last_x_on_line; ++ix ) 
                    if( ix >= 0 && ix < width ) 
                        PIXELFONT_PIXEL_FUNC( ( &target[ ix + ( y + font->baseline + 1 ) * width ] ), color );
			last_x_on_line = xp;
			max_x = x > max_x ? x : max_x; 
			x = xp; 
			y += font->line_spacing + vspacing;  
            if( *str == '\n' ) ++str;
            if( *str && skip_space && *str <= ' ' ) ++str;
		}

    if( bounds )
        {
	    bounds->width = wrap_width > 0 ? wrap_width : ( max_x - xp );
	    bounds->height = y - yp;
	    }
	}
    
#endif /* PIXELFONT_IMPLEMENTATION */


#undef PIXELFONT_COLOR
#undef PIXELFONT_FUNC_NAME

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
