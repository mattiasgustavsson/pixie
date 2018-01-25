/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

inputmap.h - v0.1 - 
*/

#ifndef inputmap_h
#define inputmap_h

typedef enum inputmap_key_t { INPUTMAP_KEY_INVALID, INPUTMAP_KEY_LBUTTON, INPUTMAP_KEY_RBUTTON, INPUTMAP_KEY_CANCEL, 
	INPUTMAP_KEY_MBUTTON, INPUTMAP_KEY_XBUTTON1, INPUTMAP_KEY_XBUTTON2, INPUTMAP_KEY_BACK, INPUTMAP_KEY_TAB, 
	INPUTMAP_KEY_CLEAR, INPUTMAP_KEY_RETURN, INPUTMAP_KEY_SHIFT, INPUTMAP_KEY_CONTROL, INPUTMAP_KEY_MENU, 
	INPUTMAP_KEY_PAUSE, INPUTMAP_KEY_CAPITAL, INPUTMAP_KEY_KANA, INPUTMAP_KEY_HANGUL, INPUTMAP_KEY_JUNJA, 
	INPUTMAP_KEY_FINAL, INPUTMAP_KEY_HANJA, INPUTMAP_KEY_KANJI, INPUTMAP_KEY_ESCAPE, INPUTMAP_KEY_CONVERT, 
	INPUTMAP_KEY_NONCONVERT, INPUTMAP_KEY_ACCEPT, INPUTMAP_KEY_MODECHANGE, INPUTMAP_KEY_SPACE, INPUTMAP_KEY_PRIOR, 
	INPUTMAP_KEY_NEXT, INPUTMAP_KEY_END, INPUTMAP_KEY_HOME, INPUTMAP_KEY_LEFT, INPUTMAP_KEY_UP, INPUTMAP_KEY_RIGHT, 
	INPUTMAP_KEY_DOWN, INPUTMAP_KEY_SELECT, INPUTMAP_KEY_PRINT, INPUTMAP_KEY_EXEC, INPUTMAP_KEY_SNAPSHOT, 
	INPUTMAP_KEY_INSERT, INPUTMAP_KEY_DELETE, INPUTMAP_KEY_HELP, INPUTMAP_KEY_0, INPUTMAP_KEY_1, INPUTMAP_KEY_2, 
	INPUTMAP_KEY_3, INPUTMAP_KEY_4, INPUTMAP_KEY_5, INPUTMAP_KEY_6, INPUTMAP_KEY_7, INPUTMAP_KEY_8, INPUTMAP_KEY_9, 
	INPUTMAP_KEY_A, INPUTMAP_KEY_B, INPUTMAP_KEY_C, INPUTMAP_KEY_D, INPUTMAP_KEY_E, INPUTMAP_KEY_F, INPUTMAP_KEY_G, 
	INPUTMAP_KEY_H, INPUTMAP_KEY_I, INPUTMAP_KEY_J, INPUTMAP_KEY_K, INPUTMAP_KEY_L, INPUTMAP_KEY_M, INPUTMAP_KEY_N, 
	INPUTMAP_KEY_O, INPUTMAP_KEY_P, INPUTMAP_KEY_Q, INPUTMAP_KEY_R, INPUTMAP_KEY_S, INPUTMAP_KEY_T, INPUTMAP_KEY_U, 
	INPUTMAP_KEY_V, INPUTMAP_KEY_W, INPUTMAP_KEY_X, INPUTMAP_KEY_Y, INPUTMAP_KEY_Z, INPUTMAP_KEY_LWIN, 
	INPUTMAP_KEY_RWIN, INPUTMAP_KEY_APPS, INPUTMAP_KEY_SLEEP, INPUTMAP_KEY_NUMPAD0, INPUTMAP_KEY_NUMPAD1, 
	INPUTMAP_KEY_NUMPAD2, INPUTMAP_KEY_NUMPAD3, INPUTMAP_KEY_NUMPAD4, INPUTMAP_KEY_NUMPAD5, INPUTMAP_KEY_NUMPAD6, 
	INPUTMAP_KEY_NUMPAD7, INPUTMAP_KEY_NUMPAD8, INPUTMAP_KEY_NUMPAD9, INPUTMAP_KEY_MULTIPLY, INPUTMAP_KEY_ADD, 
	INPUTMAP_KEY_SEPARATOR, INPUTMAP_KEY_SUBTRACT, INPUTMAP_KEY_DECIMAL, INPUTMAP_KEY_DIVIDE, INPUTMAP_KEY_F1, 
	INPUTMAP_KEY_F2, INPUTMAP_KEY_F3, INPUTMAP_KEY_F4, INPUTMAP_KEY_F5, INPUTMAP_KEY_F6, INPUTMAP_KEY_F7, 
	INPUTMAP_KEY_F8, INPUTMAP_KEY_F9, INPUTMAP_KEY_F10, INPUTMAP_KEY_F11, INPUTMAP_KEY_F12, INPUTMAP_KEY_F13, 
	INPUTMAP_KEY_F14, INPUTMAP_KEY_F15, INPUTMAP_KEY_F16, INPUTMAP_KEY_F17, INPUTMAP_KEY_F18, INPUTMAP_KEY_F19, 
	INPUTMAP_KEY_F20, INPUTMAP_KEY_F21, INPUTMAP_KEY_F22, INPUTMAP_KEY_F23, INPUTMAP_KEY_F24, INPUTMAP_KEY_NUMLOCK, 
	INPUTMAP_KEY_SCROLL, INPUTMAP_KEY_LSHIFT, INPUTMAP_KEY_RSHIFT, INPUTMAP_KEY_LCONTROL, INPUTMAP_KEY_RCONTROL, 
	INPUTMAP_KEY_LMENU, INPUTMAP_KEY_RMENU, INPUTMAP_KEY_BROWSER_BACK, INPUTMAP_KEY_BROWSER_FORWARD, 
	INPUTMAP_KEY_BROWSER_REFRESH, INPUTMAP_KEY_BROWSER_STOP, INPUTMAP_KEY_BROWSER_SEARCH, INPUTMAP_KEY_BROWSER_FAVORITES, 
	INPUTMAP_KEY_BROWSER_HOME, INPUTMAP_KEY_VOLUME_MUTE, INPUTMAP_KEY_VOLUME_DOWN, INPUTMAP_KEY_VOLUME_UP, 
	INPUTMAP_KEY_MEDIA_NEXT_TRACK, INPUTMAP_KEY_MEDIA_PREV_TRACK, INPUTMAP_KEY_MEDIA_STOP, INPUTMAP_KEY_MEDIA_PLAY_PAUSE, 
	INPUTMAP_KEY_LAUNCH_MAIL, INPUTMAP_KEY_LAUNCH_MEDIA_SELECT, INPUTMAP_KEY_LAUNCH_APP1, INPUTMAP_KEY_LAUNCH_APP2, 
	INPUTMAP_KEY_OEM_1, INPUTMAP_KEY_OEM_PLUS, INPUTMAP_KEY_OEM_COMMA, INPUTMAP_KEY_OEM_MINUS, INPUTMAP_KEY_OEM_PERIOD, 
	INPUTMAP_KEY_OEM_2, INPUTMAP_KEY_OEM_3, INPUTMAP_KEY_OEM_4, INPUTMAP_KEY_OEM_5, INPUTMAP_KEY_OEM_6, 
	INPUTMAP_KEY_OEM_7, INPUTMAP_KEY_OEM_8, INPUTMAP_KEY_OEM_102, INPUTMAP_KEY_PROCESSKEY, INPUTMAP_KEY_ATTN, 
	INPUTMAP_KEY_CRSEL, INPUTMAP_KEY_EXSEL, INPUTMAP_KEY_EREOF, INPUTMAP_KEY_PLAY, INPUTMAP_KEY_ZOOM, 
	INPUTMAP_KEY_NONAME, INPUTMAP_KEY_PA1, INPUTMAP_KEY_OEM_CLEAR, INPUTMAP_KEYCOUNT
	} inputmap_key_t;

typedef enum inputmap_mouseaxis_t { INPUTMAP_MOUSEAXIS_LEFT_RIGHT, INPUTMAP_MOUSEAXIS_FORWARD_BACK, 
	INPUTMAP_MOUSEAXIS_WHEEL, INPUTMAP_MOUSEAXISCOUNT,} inputmap_mouseaxis_t;

typedef enum inputmap_gamepadaxis_t { INPUTMAP_GAMEPADAXIS_LEFT_TRIGGER, INPUTMAP_GAMEPADAXIS_RIGHT_TRIGGER, 
	INPUTMAP_GAMEPADAXIS_LEFTSTICK_X, INPUTMAP_GAMEPADAXIS_LEFTSTICK_Y, INPUTMAP_GAMEPADAXIS_RIGHTSTICK_X, 
	INPUTMAP_GAMEPADAXIS_RIGHTSTICK_Y, INPUTMAP_GAMEPADAXISCOUNT } inputmap_gamepadaxis_t;

typedef enum inputmap_gamepadbutton_t { INPUTMAP_GAMEPADBUTTON_DPAD_UP, INPUTMAP_GAMEPADBUTTON_DPAD_DOWN, 
	INPUTMAP_GAMEPADBUTTON_DPAD_LEFT, INPUTMAP_GAMEPADBUTTON_DPAD_RIGHT, INPUTMAP_GAMEPADBUTTON_START, 
	INPUTMAP_GAMEPADBUTTON_BACK, INPUTMAP_GAMEPADBUTTON_STICK_LEFT, INPUTMAP_GAMEPADBUTTON_STICK_RIGHT, 
	INPUTMAP_GAMEPADBUTTON_SHOULDER_LEFT, INPUTMAP_GAMEPADBUTTON_SHOULDER_RIGHT, INPUTMAP_GAMEPADBUTTON_A,
	INPUTMAP_GAMEPADBUTTON_B, INPUTMAP_GAMEPADBUTTON_X, INPUTMAP_GAMEPADBUTTON_Y, INPUTMAP_GAMEPADBUTTONCOUNT 
	} inputmap_gamepadbutton_t;
	
typedef enum inputmap_inverted_t { INPUTMAP_NOT_INVERTED, INPUTMAP_INVERTED, } inputmap_inverted_t;


// create/destroy inputmap system

typedef struct inputmap_t inputmap_t;

inputmap_t* inputmap_create( void* memctx );
void inputmap_destroy( inputmap_t* inputmap );


// set up action mappings

#define INPUTMAP_INVALID_ACTION -1

typedef struct inputmap_mapping_t { int handle; } inputmap_mapping_t;

inputmap_mapping_t inputmap_map_axis_mouseaxis( inputmap_t* inputmap, int action, inputmap_mouseaxis_t axis, 
	inputmap_inverted_t inverted, float scale );
	
inputmap_mapping_t inputmap_map_axis_gamepadaxis( inputmap_t* inputmap, int action, int pad_index, 
inputmap_gamepadaxis_t axis, inputmap_inverted_t inverted, float scale );
	
inputmap_mapping_t inputmap_map_axis_gamepadbuttons( inputmap_t* inputmap, int action, int pad_index, 
	inputmap_gamepadbutton_t button_neg, inputmap_gamepadbutton_t button_pos, float scale );
	
inputmap_mapping_t inputmap_map_axis_keyboard( inputmap_t* inputmap, int action, inputmap_key_t key_neg, 
inputmap_key_t key_pos, float scale );
			 
inputmap_mapping_t inputmap_map_button_keyboard( inputmap_t* inputmap, int action, inputmap_key_t key );

inputmap_mapping_t inputmap_map_button_gamepadbutton( inputmap_t* inputmap, int action, int pad_index,
	inputmap_gamepadbutton_t button );

inputmap_mapping_t inputmap_map_button_gamepadaxis( inputmap_t* inputmap, int action, int pad_index,
	inputmap_gamepadaxis_t axis, inputmap_inverted_t inverted, float threshold );

inputmap_mapping_t inputmap_map_button_mouseaxis( inputmap_t* inputmap, int action, inputmap_mouseaxis_t axis, 
	inputmap_inverted_t inverted, float threshold );


void inputmap_unmap( inputmap_t* inputmap, inputmap_mapping_t mapping );
void inputmap_remove( inputmap_t* inputmap, int action );


// feed input events to inputmap system

void inputmap_update_begin( inputmap_t* inputmap );

void inputmap_update_keydown( inputmap_t* inputmap, inputmap_key_t key );
void inputmap_update_keyup( inputmap_t* inputmap, inputmap_key_t key );

void inputmap_update_mouseaxis( inputmap_t* inputmap, inputmap_mouseaxis_t axis, float value );

void inputmap_update_gamepadbuttondown( inputmap_t* inputmap, int pad_index, inputmap_gamepadbutton_t button );
void inputmap_update_gamepadbuttonup( inputmap_t* inputmap, int pad_index, inputmap_gamepadbutton_t button );
void inputmap_update_gamepadaxis( inputmap_t* inputmap, int pad_index, inputmap_gamepadaxis_t axis, float value );

void inputmap_update_end( inputmap_t* inputmap );


// poll mapped actions

float inputmap_action( inputmap_t* inputmap, int action );



#endif /* inputmap_h */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef INPUTMAP_IMPLEMENTATION
#undef INPUTMAP_IMPLEMENTATION

#ifndef INPUTMAP_ASSERT
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
	#include <assert.h>
	#define INPUTMAP_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

#ifndef INPUTMAP_MALLOC
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#if defined(__cplusplus)
		#define INPUTMAP_MALLOC( ctx, size ) ( ::malloc( size ) )
		#define INPUTMAP_FREE( ctx, ptr ) ( ::free( ptr ) )
	#else
		#define INPUTMAP_MALLOC( ctx, size ) ( malloc( size ) )
		#define INPUTMAP_FREE( ctx, ptr ) ( free( ptr ) )
	#endif
#endif

#ifndef INPUTMAP_MAX_GAMEPAD_COUNT
	#define INPUTMAP_MAX_GAMEPAD_COUNT 4
#endif



typedef enum internal_inputmap_mapping_type_t 
	{ 
	INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_MOUSEAXIS,
	INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADAXIS,
	INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADBUTTONS,
	INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_KEYBOARD,
	INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_KEYBOARD,
	INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADBUTTON,
	INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADAXIS,
	INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_MOUSEAXIS,
	} internal_inputmap_mapping_type_t;


typedef struct internal_inputmap_mapping_t
	{
	int freelist_next;
	int action;
	internal_inputmap_mapping_type_t mapping_type;
	union
		{
		struct { inputmap_mouseaxis_t axis; inputmap_inverted_t inverted; float scale; } axis_mouseaxis; 
		struct { int pad_index; inputmap_gamepadaxis_t axis; inputmap_inverted_t inverted; float scale; } axis_gamepadaxis; 
		struct { int pad_index; inputmap_gamepadbutton_t button_neg; inputmap_gamepadbutton_t button_pos; float scale; } axis_gamepadbuttons; 
		struct { inputmap_key_t key_neg; inputmap_key_t key_pos; float scale; } axis_keyboard; 
		struct { inputmap_key_t key; } button_keyboard; 
		struct { int pad_index; inputmap_gamepadbutton_t button; } button_gamepadbutton; 
		struct { int pad_index; inputmap_gamepadaxis_t axis; inputmap_inverted_t inverted; float threshold; } button_gamepadaxis; 
		struct { inputmap_mouseaxis_t axis; inputmap_inverted_t inverted; float threshold; } button_mouseaxis; 
		};
	} internal_inputmap_mapping_t;


typedef struct internal_inputmap_action_state_t
	{
	int action;
	float state;
	} internal_inputmap_action_state_t;


struct inputmap_t
	{
    void* memctx;
	int is_updating;

	int mappings_count;
	int mappings_capacity;
	internal_inputmap_mapping_t* mappings;
	int mappings_freelist;

	int actions_state_count;
	int actions_state_capacity;
	internal_inputmap_action_state_t* actions_state;
	
	struct 
		{
		int keyboard[ INPUTMAP_KEYCOUNT ];
		float mouse_axis[ INPUTMAP_MOUSEAXISCOUNT ];
		int gamepad_buttons[INPUTMAP_MAX_GAMEPAD_COUNT][ INPUTMAP_GAMEPADBUTTONCOUNT ];
		float gamepad_axis[INPUTMAP_MAX_GAMEPAD_COUNT][ INPUTMAP_GAMEPADAXISCOUNT ];
		} input_state;
	};
	
	
inputmap_t* inputmap_create( void* memctx ) 
	{ 
	inputmap_t* inputmap = (inputmap_t*) INPUTMAP_MALLOC( memctx, sizeof( inputmap_t ) );

    inputmap->memctx = memctx;
	inputmap->is_updating = 0;

	inputmap->mappings_count = 0;
	inputmap->mappings_capacity = 256;
	inputmap->mappings = (internal_inputmap_mapping_t*) INPUTMAP_MALLOC( 
		inputmap->memctx, sizeof( *inputmap->mappings ) * inputmap->mappings_capacity );
	inputmap->mappings_freelist = -1;

	inputmap->actions_state_count = 0;
	inputmap->actions_state_capacity = 256;
	inputmap->actions_state = (internal_inputmap_action_state_t*) INPUTMAP_MALLOC( 
		inputmap->memctx, sizeof( *inputmap->actions_state ) * inputmap->actions_state_capacity );

	memset( &inputmap->input_state, 0, sizeof( inputmap->input_state ) );
	
	return inputmap;
	}


void inputmap_destroy( inputmap_t* inputmap ) 
	{
	INPUTMAP_FREE( inputmap->memctx, inputmap->actions_state );
	INPUTMAP_FREE( inputmap->memctx, inputmap->mappings );
	INPUTMAP_FREE( inputmap->memctx, inputmap );
	}


int internal_inputmap_add_mapping( inputmap_t* inputmap )
	{
	if( inputmap->mappings_freelist >= 0 )
		{
		int ret = inputmap->mappings_freelist;
		inputmap->mappings_freelist = inputmap->mappings[ ret ].freelist_next;
		return ret;
		}
	
	if( inputmap->mappings_count >= inputmap->mappings_capacity )
		{
		inputmap->mappings_capacity *= 2;
		internal_inputmap_mapping_t* new_mappings = (internal_inputmap_mapping_t*) INPUTMAP_MALLOC( 
			inputmap->memctx, sizeof( *inputmap->mappings ) * inputmap->mappings_capacity );
		INPUTMAP_ASSERT( new_mappings, "Allocation failed." );
		for( int i = 0; i < inputmap->mappings_count; ++i ) new_mappings[ i ] = inputmap->mappings[ i ];
		INPUTMAP_FREE( inputmap->memctx, inputmap->mappings );
		inputmap->mappings = new_mappings;
		}

	return inputmap->mappings_count++;
	}	


inputmap_mapping_t inputmap_map_axis_mouseaxis( inputmap_t* inputmap, int action, inputmap_mouseaxis_t axis, 
	inputmap_inverted_t inverted, float scale )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_MOUSEAXIS;
	mapping->axis_mouseaxis.axis = axis;
	mapping->axis_mouseaxis.inverted = inverted;
	mapping->axis_mouseaxis.scale = scale;

	return index;
	}


inputmap_mapping_t inputmap_map_axis_gamepadaxis( inputmap_t* inputmap, int action, int pad_index, 
	inputmap_gamepadaxis_t axis, inputmap_inverted_t inverted, float scale )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADAXIS;
	mapping->axis_gamepadaxis.pad_index = pad_index;
	mapping->axis_gamepadaxis.axis = axis;
	mapping->axis_gamepadaxis.inverted = inverted;
	mapping->axis_gamepadaxis.scale = scale;

	return index;
	}


inputmap_mapping_t inputmap_map_axis_gamepadbuttons( inputmap_t* inputmap, int action, int pad_index, 
	inputmap_gamepadbutton_t button_neg, inputmap_gamepadbutton_t button_pos, float scale )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADBUTTONS;
	mapping->axis_gamepadbuttons.pad_index = pad_index;
	mapping->axis_gamepadbuttons.button_neg = button_neg;
	mapping->axis_gamepadbuttons.button_pos = button_pos;
	mapping->axis_gamepadbuttons.scale = scale;

	return index;
	}


inputmap_mapping_t inputmap_map_axis_keyboard( inputmap_t* inputmap, int action, inputmap_key_t key_neg, 
	inputmap_key_t key_pos, float scale )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_KEYBOARD;
	mapping->axis_keyboard.key_neg = key_neg;
	mapping->axis_keyboard.key_pos = key_pos;
	mapping->axis_keyboard.scale = scale;

	return index;
	}
			 

inputmap_mapping_t inputmap_map_button_keyboard( inputmap_t* inputmap, int action, inputmap_key_t key )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_KEYBOARD;
	mapping->button_keyboard.key = key;

	return index;
	}


inputmap_mapping_t inputmap_map_button_gamepadbutton( inputmap_t* inputmap, int action, int pad_index, 
	inputmap_gamepadbutton_t button )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADBUTTON;
	mapping->button_gamepadbutton.pad_index = pad_index;
	mapping->button_gamepadbutton.button = button;

	return index;
	}


inputmap_mapping_t inputmap_map_button_gamepadaxis( inputmap_t* inputmap, int action, int pad_index, 
	inputmap_gamepadaxis_t axis, inputmap_inverted_t inverted, float threshold )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADAXIS;
	mapping->button_gamepadaxis.pad_index = pad_index;
	mapping->button_gamepadaxis.axis = axis;
	mapping->button_gamepadaxis.inverted = inverted;
	mapping->button_gamepadaxis.threshold = threshold;

	return index;
	}


inputmap_mapping_t inputmap_map_button_mouseaxis( inputmap_t* inputmap, int action, inputmap_mouseaxis_t axis, 
	inputmap_inverted_t inverted, float threshold )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );

	inputmap_mapping_t index;
	index.handle = internal_inputmap_add_mapping( inputmap );
	
	internal_inputmap_mapping_t* mapping = &inputmap->mappings[ index.handle ];
	mapping->action = action;
	mapping->mapping_type = INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_MOUSEAXIS;
	mapping->button_mouseaxis.axis = axis;
	mapping->button_mouseaxis.inverted = inverted;
	mapping->button_mouseaxis.threshold = threshold;

	return index;
	}


void inputmap_unmap( inputmap_t* inputmap, inputmap_mapping_t mapping )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( mapping.handle >= 0 && mapping.handle < inputmap->mappings_count, "Invalid mapping." );
	int freelist = inputmap->mappings_freelist;
	while( freelist >= 0 )
		{
		INPUTMAP_ASSERT( mapping.handle != freelist, "Invalid mapping." );
		freelist = inputmap->mappings[ freelist ].freelist_next;
		}
	inputmap->mappings[ mapping.handle ].action = INPUTMAP_INVALID_ACTION;
	inputmap->mappings[ mapping.handle ].freelist_next = inputmap->mappings_freelist;
	inputmap->mappings_freelist = mapping.handle;
	}


void inputmap_remove( inputmap_t* inputmap, int action )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	INPUTMAP_ASSERT( action != INPUTMAP_INVALID_ACTION, "Invalid action." );
	for( int i = 0; i < inputmap->mappings_count; ++i )
		{
		if( inputmap->mappings[ i ].action == action )
			{
			inputmap->mappings[ i ].action = INPUTMAP_INVALID_ACTION;
			inputmap->mappings[ i ].freelist_next = inputmap->mappings_freelist;
			inputmap->mappings_freelist = i;
			}
		}
	
	for( int i = 0; i < inputmap->actions_state_count; ++i )	
		{
		if( inputmap->actions_state[ i ].action == action )
			{
			inputmap->actions_state[ i ] = inputmap->actions_state[ --inputmap->actions_state_count ];
			break;
			}
		}
	}


void inputmap_update_begin( inputmap_t* inputmap )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update already in progress." );
	inputmap->is_updating = 1;
	}


void inputmap_update_keydown( inputmap_t* inputmap, inputmap_key_t key )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	inputmap->input_state.keyboard[ key ] = 1;
	}


void inputmap_update_keyup( inputmap_t* inputmap, inputmap_key_t key )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	inputmap->input_state.keyboard[ key ] = 0;
	}


void inputmap_update_mouseaxis( inputmap_t* inputmap, inputmap_mouseaxis_t axis, float value )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	inputmap->input_state.mouse_axis[ axis ] = value;
	}


void inputmap_update_gamepadbuttondown( inputmap_t* inputmap, int pad_index, inputmap_gamepadbutton_t button )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );
	inputmap->input_state.gamepad_buttons[pad_index][ button ] = 1;
	}


void inputmap_update_gamepadbuttonup( inputmap_t* inputmap, int pad_index, inputmap_gamepadbutton_t button )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );
	inputmap->input_state.gamepad_buttons[pad_index][ button ] = 0;
	}


void inputmap_update_gamepadaxis( inputmap_t* inputmap, int pad_index, inputmap_gamepadaxis_t axis, float value )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	INPUTMAP_ASSERT( pad_index >= 0 && pad_index < INPUTMAP_MAX_GAMEPAD_COUNT, "Pad index out of range." );
	inputmap->input_state.gamepad_axis[pad_index][ axis ] = value;
	}


void inputmap_update_end( inputmap_t* inputmap )
	{
	INPUTMAP_ASSERT( inputmap->is_updating, "Inputmap update not in progress." );
	inputmap->is_updating = 0;
	
	for( int i = 0; i < inputmap->mappings_count; ++i )
		{
		internal_inputmap_mapping_t* mapping = &inputmap->mappings[ i ];
		if( mapping->action != INPUTMAP_INVALID_ACTION )
			{
			float value = 0.0f;
			switch( mapping->mapping_type )
				{
				case INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_MOUSEAXIS:
					value = inputmap->input_state.mouse_axis[ mapping->axis_mouseaxis.axis ];
					if( mapping->axis_mouseaxis.inverted == INPUTMAP_INVERTED ) value = -value;
					value *= mapping->axis_mouseaxis.scale;					
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADAXIS:
					value = inputmap->input_state.gamepad_axis[ mapping->axis_gamepadaxis.pad_index ][ mapping->axis_gamepadaxis.axis ];
					if( mapping->axis_gamepadaxis.inverted == INPUTMAP_INVERTED ) value = -value;
					value *= mapping->axis_gamepadaxis.scale;					
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_GAMEPADBUTTONS:
					if( inputmap->input_state.gamepad_buttons[ mapping->axis_gamepadbuttons.pad_index ][ mapping->axis_gamepadbuttons.button_pos ] )
						value = 1.0f;
					else if( inputmap->input_state.gamepad_buttons[ mapping->axis_gamepadbuttons.pad_index ][ mapping->axis_gamepadbuttons.button_neg ] )
						value = -1.0f;
					value *= mapping->axis_gamepadbuttons.scale;					
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_AXIS_KEYBOARD:
					if( inputmap->input_state.keyboard[ mapping->axis_keyboard.key_pos ] )
						value = 1.0f;
					else if( inputmap->input_state.keyboard[ mapping->axis_keyboard.key_neg ] )
						value = -1.0f;
					value *= mapping->axis_keyboard.scale;					
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_KEYBOARD:
					if( inputmap->input_state.keyboard[ mapping->button_keyboard.key ] )
						value = 1.0f;
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADBUTTON:
					if( inputmap->input_state.gamepad_buttons[ mapping->button_gamepadbutton.pad_index ][ mapping->button_gamepadbutton.button ] )
						value = 1.0f;
					break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_GAMEPADAXIS:
					{
					float axis = inputmap->input_state.gamepad_axis[ mapping->button_gamepadaxis.pad_index ][ mapping->button_gamepadaxis.axis ];
					if( mapping->button_gamepadaxis.inverted == INPUTMAP_INVERTED ) axis = -axis;
					if( axis > mapping->button_gamepadaxis.threshold ) value = 1.0f;
					} break;
				case INTERNAL_INPUTMAP_MAPPING_TYPE_BUTTON_MOUSEAXIS:
					{
					float axis = inputmap->input_state.mouse_axis[ mapping->button_mouseaxis.axis ];
					if( mapping->button_mouseaxis.inverted == INPUTMAP_INVERTED ) axis = -axis;
					if( axis > mapping->button_mouseaxis.threshold ) value = 1.0f;
					} break;
				}
				
			int state_index = -1;
			for( int j = 0; j < inputmap->actions_state_count; ++j )				
				if( inputmap->actions_state[ j ].action == mapping->action ) { state_index = j; break; }
	
			if( state_index < 0 )
				{
				if( inputmap->actions_state_count >= inputmap->actions_state_capacity )
					{
					inputmap->actions_state_capacity *= 2;
					internal_inputmap_action_state_t* new_actions_state = (internal_inputmap_action_state_t*) INPUTMAP_MALLOC( 
						inputmap->memctx, sizeof( *inputmap->actions_state ) * inputmap->actions_state_capacity );
					INPUTMAP_ASSERT( new_actions_state, "Allocation failed." );
					for( int j = 0; j < inputmap->actions_state_count; ++j ) new_actions_state[ j ] = inputmap->actions_state[ j ];
					INPUTMAP_FREE( inputmap->memctx, inputmap->actions_state );
					inputmap->actions_state = new_actions_state;
					}
				state_index = inputmap->actions_state_count++;
				}
			inputmap->actions_state[ state_index ].action = mapping->action;
			inputmap->actions_state[ state_index ].state = value;
			}
		}
	}


float inputmap_action( inputmap_t* inputmap, int action )
	{
	INPUTMAP_ASSERT( !inputmap->is_updating, "Inputmap update in progress." );
	
	for( int i = 0; i < inputmap->actions_state_count; ++i )
		{
		if( inputmap->actions_state[ i ].action == action )
			return inputmap->actions_state[ i ].state;
		}
		
	return 0.0f;
	}


#endif /* INPUTMAP_IMPLEMENTATION */

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
