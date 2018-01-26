/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

gamepad.h - v0.1 - 
*/

#ifndef gamepad_h
#define gamepad_h

#ifndef GAMEPAD_I16
	#define GAMEPAD_I16 short
#endif
#ifndef GAMEPAD_U16
	#define GAMEPAD_U16 unsigned short 
#endif
#ifndef GAMEPAD_U8
	#define GAMEPAD_U8 unsigned char
#endif

typedef enum gamepad_result_t
	{
	GAMEPAD_RESULT_NOT_CONNECTED,
	GAMEPAD_RESULT_OK,
	} gamepad_result_t;


typedef struct gamepad_state_t
	{
	GAMEPAD_U16 buttons;
	GAMEPAD_U8  trigger_left;
	GAMEPAD_U8  trigger_right;
	GAMEPAD_I16 stick_left_x;
	GAMEPAD_I16 stick_left_y;
	GAMEPAD_I16 stick_right_x;
	GAMEPAD_I16 stick_right_y;
	} gamepad_state_t;


typedef enum gamepad_button_t
	{
	GAMEPAD_DPAD_UP = 0x0001,
	GAMEPAD_DPAD_DOWN = 0x0002,
	GAMEPAD_DPAD_LEFT = 0x0004,
	GAMEPAD_DPAD_RIGHT = 0x0008,
	GAMEPAD_START = 0x0010,
	GAMEPAD_BACK = 0x0020,
	GAMEPAD_STICK_LEFT = 0x0040,
	GAMEPAD_STICK_RIGHT = 0x0080,
	GAMEPAD_SHOULDER_LEFT = 0x0100,
	GAMEPAD_SHOULDER_RIGHT = 0x0200,
	GAMEPAD_A = 0x1000,
	GAMEPAD_B = 0x2000,
	GAMEPAD_X = 0x4000,
	GAMEPAD_Y = 0x8000,
	} gamepad_button_t;


typedef struct gamepad_t gamepad_t;


gamepad_t* gamepad_create( void* memctx );

void gamepad_destroy( gamepad_t* gamepad );

gamepad_result_t gamepad_read( gamepad_t* gamepad, int index, gamepad_state_t* state );


#endif /* gamepad_h */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef GAMEPAD_IMPLEMENTATION
#undef GAMEPAD_IMPLEMENTATION


#ifndef GAMEPAD_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#if defined(__cplusplus)
		#define GAMEPAD_MALLOC( ctx, size ) ( ::malloc( size ) )
		#define GAMEPAD_FREE( ctx, ptr ) ( ::free( ptr ) )
	#else
		#define GAMEPAD_MALLOC( ctx, size ) ( malloc( size ) )
		#define GAMEPAD_FREE( ctx, ptr ) ( free( ptr ) )
	#endif
#endif


typedef struct gamepad_internal_XINPUT_GAMEPAD
	{
	WORD                                wButtons;
	BYTE                                bLeftTrigger;
	BYTE                                bRightTrigger;
	SHORT                               sThumbLX;
	SHORT                               sThumbLY;
	SHORT                               sThumbRX;
	SHORT                               sThumbRY;
	} gamepad_internal_XINPUT_GAMEPAD;


typedef struct gamepad_internal_XINPUT_STATE
	{
	DWORD                               dwPacketNumber;
	gamepad_internal_XINPUT_GAMEPAD     Gamepad;
	} gamepad_internal_XINPUT_STATE;


typedef DWORD (WINAPI *gamepad_internal_XInputGetState_t)( DWORD, gamepad_internal_XINPUT_STATE* );


typedef struct gamepad_t
	{
	void* memctx;
	HMODULE dll;
	gamepad_internal_XInputGetState_t get_state;
	} gamepad_t;


gamepad_t* gamepad_create( void* memctx )
	{
	(void) memctx;

	HMODULE dll = 0;
	int version = 4;
	char const* dll_name[] = { "xinput1_0.dll", "xinput1_1.dll", "xinput1_2.dll", "xinput1_3.dll", "xinput1_4.dll" };
	char const* dll_name9[] = { "xinput9_1_0.dll", "xinput9_1_1.dll", "xinput9_1_2.dll", "xinput9_1_3.dll", "xinput9_1_4.dll" };
	while( !dll && version >= 0 )
		{
		dll = LoadLibraryA( dll_name[ version ] );
		if( !dll ) dll = LoadLibraryA( dll_name9[ version ] );
		--version;
		}
		
	if( !dll ) return 0;

	FARPROC proc = GetProcAddress( dll, "XInputGetState" );
	if( !proc)
		{
		FreeLibrary( dll );
		return 0;
		}

	gamepad_t* gamepad = (gamepad_t*) GAMEPAD_MALLOC( memctx, sizeof( gamepad_t ) );
	gamepad->memctx = memctx;
	gamepad->dll = dll;
	gamepad->get_state = (gamepad_internal_XInputGetState_t) (uintptr_t) proc;
	return gamepad;
	}


void gamepad_destroy( gamepad_t* gamepad )
	{
	FreeLibrary( gamepad->dll );
	GAMEPAD_FREE( gamepad->memctx, gamepad );
	}


gamepad_result_t gamepad_read( gamepad_t* gamepad, int index, gamepad_state_t* state )
	{
	if( index < 0 || index > 3 ) 
		{
		return GAMEPAD_RESULT_NOT_CONNECTED;
		}
	else
		{
		gamepad_internal_XINPUT_STATE xstate;
		DWORD result = gamepad->get_state( (DWORD) index, &xstate );
		if( result == ERROR_SUCCESS )
			{
			if( state )
				{
				state->buttons = xstate.Gamepad.wButtons;
				state->trigger_left = xstate.Gamepad.bLeftTrigger;
				state->trigger_right = xstate.Gamepad.bRightTrigger;
				state->stick_left_x = xstate.Gamepad.sThumbLX;
				state->stick_left_y = xstate.Gamepad.sThumbLY;
				state->stick_right_x = xstate.Gamepad.sThumbRX;
				state->stick_right_y = xstate.Gamepad.sThumbRY;
				}
			return GAMEPAD_RESULT_OK;
			}
		else
			{
			return GAMEPAD_RESULT_NOT_CONNECTED;
			}
		}
	}


#endif /* GAMEPAD_IMPLEMENTATION */

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
