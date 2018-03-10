/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

pixie.hpp - v0.1 - 

*/

#ifndef pixie_hpp
#define pixie_hpp

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

// placement new
#if !defined( PLACEMENT_NEW_OPERATOR_DEFINED ) && !defined( __PLACEMENT_NEW_INLINE )
#define PLACEMENT_NEW_OPERATOR_DEFINED
#define __PLACEMENT_NEW_INLINE
inline void* operator new( size_t, void* p ) throw() { return p; } inline void operator delete(void*, void*) throw() { }
#endif 

#include <stddef.h>
#include "cpp_compat.hpp"

namespace pixie {
typedef int8_t i8; typedef int16_t i16; typedef int32_t i32; typedef int64_t i64;
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;
} /* namespace pixie */

namespace pixie { namespace internal { 
bool display_assert_message( char const* expression, char const* message, char const* file, int line );
char const* format_assert_message( char const* format, ... );
} /* namespace internal */ } /* namespace pixie */

#ifndef PIXIE_ASSERT
	#if defined NDEBUG && !defined( PIXIE_ASSERT_IN_RELEASE_BUILD )
		#define PIXIE_ASSERT( expression, message )
	#else
		#ifdef _WIN32
			#define PIXIE_ASSERT( expression, message ) \
		        __pragma( warning( push ) ) \
		        __pragma( warning( disable: 4127 ) ) \
				do { \
					if( !( expression ) ) \
						if( pixie::internal::display_assert_message( #expression, message, __FILE__, __LINE__ ) ) \
							__debugbreak(); \
				} while( 0 ) \
				__pragma( warning( pop ) )
		#else   
			#error Platform not supported
		#endif
	#endif
#endif

#define PIXIE_ASSERTF( expression, message ) PIXIE_ASSERT( expression, pixie::internal::format_assert_message message )

#define ARRAY_ASSERT PIXIE_ASSERT
#define DICTIONARY_ASSERT PIXIE_ASSERT
#define GAMESTATE_ASSERT PIXIE_ASSERT
#define MATH_UTIL_ASSERT PIXIE_ASSERT
#define MEMPOOL_ASSERT PIXIE_ASSERT
#define OBJREPO_ASSERT PIXIE_ASSERT
#define RESOURCES_ASSERT PIXIE_ASSERT

#define DICTIONARY_U64 pixie::u64
#define STRPOOL_U64 pixie::u64
#define TWEEN_U64 pixie::u64

#include "array.hpp"
#include "dictionary.hpp"
#include "gamestate.hpp"
#include "math_util.hpp"
#include "mempool.hpp"
#include "objrepo.hpp"
#include "refcount.hpp"
#include "resources.hpp"
#include "sort.hpp"
#include "strpool.hpp"
#include "strpool_util.hpp"
#include "tween.hpp"
#include "vecmath.hpp"

namespace pixie { namespace internal { struct PIXIE_STRING_POOL; struct PIXIE_STRING_ID_POOL; struct internals_t; void resize_screen(); } } 

namespace strpool { namespace internal {
template<> string_pool& pool_instance<pixie::internal::PIXIE_STRING_POOL>( bool destroy );
template<> string_pool& pool_instance<pixie::internal::PIXIE_STRING_ID_POOL>( bool destroy );
} /* namespace internal */ } /* namespace strpool */  

namespace pixie {

typedef strpool::string_type<internal::PIXIE_STRING_POOL> string;
typedef strpool::string_type<internal::PIXIE_STRING_ID_POOL> string_id;
using strpool::str; using strpool::trim; using strpool::ltrim; using strpool::rtrim; using strpool::left; 
using strpool::right; using strpool::mid; using strpool::instr; using strpool::any; using strpool::upper; 
using strpool::lower; using strpool::val; using strpool::integer; using strpool::space; using strpool::flip; 
using strpool::repeat; using strpool::chr; using strpool::asc; using strpool::len; using strpool::format;
using tween_ns::tweener; using refcount::ref; using tween_ns::make_property; using tween_ns::property;
using vecmath::float2; using vecmath::float3; using vecmath::float4; using vecmath::float2x2;
using vecmath::float2x3; using vecmath::float3x2; using vecmath::float3x3; using vecmath::float2x4; 
using vecmath::float3x4; using vecmath::float4x2; using vecmath::float4x3; using vecmath::float4x4; using vecmath::abs; 
using vecmath::acos; using vecmath::all; using vecmath::any; using vecmath::asin; using vecmath::atan; 
using vecmath::atan2; using vecmath::ceil; using vecmath::clamp; using vecmath::cos; using vecmath::cosh; 
using vecmath::degrees; using vecmath::distancesq; using vecmath::distance; using vecmath::dot; using vecmath::exp; 
using vecmath::exp2; using vecmath::floor; using vecmath::fmod; using vecmath::frac; using vecmath::lengthsq; 
using vecmath::length; using vecmath::lerp; using vecmath::log; using vecmath::log10; using vecmath::mad; 
using vecmath::max; using vecmath::min; using vecmath::normalize; using vecmath::pow; using vecmath::radians; 
using vecmath::rcp; using vecmath::reflect; using vecmath::refract; using vecmath::round; using vecmath::rsqrt; 
using vecmath::saturate; using vecmath::sign; using vecmath::sin; using vecmath::sinh; using vecmath::smoothstep; 
using vecmath::smootherstep; using vecmath::sqrt; using vecmath::step; using vecmath::tan; using vecmath::tanh;
using math_util::PI; using math_util::TWO_PI; using math_util::to_radians; using math_util::to_degrees;
using math_util::angle_diff; using math_util::angle_lerp; using math_util::pow2_ceil; using math_util::fast_round;
using dictionary_ns::dictionary; using funccall::make_func_call; using mempool_ns::mempool;


typedef int (*game_main_func_t)();

int run( game_main_func_t game_main, void* memctx = 0 );

struct async_handle final { void* thread_handle; };
async_handle run_async( game_main_func_t game_main, void* memctx = 0 );
int join_async( async_handle handle );

void execute_frame();
bool is_running();
void wait( int jiffys );
void wait( float time );
void wait_key();

void request_exit();
bool exit_requested();
void cancel_exit_request();

void end( int return_value = 0 );
void system();

#define str_switch( x ) pixie::string_id const& multiple_str_switch_not_allowed_within_the_same_scope( x );
#define str_case( x ) if( multiple_str_switch_not_allowed_within_the_same_scope == pixie::string_id( x ) )

inline string str( int x ) { return strpool::str<pixie::internal::PIXIE_STRING_POOL>( x ); }
inline string str( float x ) { return strpool::str<pixie::internal::PIXIE_STRING_POOL>( x ); }

typedef void const* type_id_t;
template< typename T > type_id_t type_id();
template< typename T > type_id_t type_id( T const& );

#pragma warning( push ) 
#pragma warning( disable: 4619 ) // pragma warning : there is no warning number 'number'
#pragma warning( disable: 4217 ) // nonstandard extension used : function declaration from a previous block

template< typename T, int CAPACITY = 16 > struct array final : array_ns::array_type< T, CAPACITY, array_ns::NOT_POD >
	{ 
	explicit array( int initial_capacity = CAPACITY );
	template< typename U > array( U const& other );
	template< typename U > explicit array( U const* items, int count );
	};


template< typename T, int CAPACITY = 16 > struct pod_array final : array_ns::array_type< T, CAPACITY, array_ns::IS_POD >
	{ 
	explicit pod_array( int initial_capacity = CAPACITY );
	template< typename U > pod_array( U const& other );
	template< typename U > explicit pod_array( U const* items, int count );
	};

template< typename T > struct resource final : resources::resource<T>
	{
	resource() : resources::resource<T>( internal::resource_system() ) {} ;
	template< typename P0 > resource( P0 const& p0 ) : resources::resource<T>( internal::resource_system(), p0 ) {} ;
	template< typename P0, typename P1 > resource( P0 const& p0, P1 const& p1 ) : resources::resource<T>( internal::resource_system(), p0, p1 ) {} ;
	template< typename P0, typename P1, typename P2 > resource( P0 const& p0, P1 const& p1, P2 const& p2 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4, p5 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4, p5, p6 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4, p5, p6, p7 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4, p5, p6, p7, p8 ) {} ;
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > resource( P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9 ) : resources::resource<T>( internal::resource_system(), p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) {} ;
	};

#pragma warning( pop ) 

template< typename T > void pin_resource( resource< T > const& res, string_id group = "" );
template< typename T > void unpin_resource( resource< T > const& res, string_id group = "" );
void unpin_resource( string_id group = "" );
void unpin_resources();

template< typename T > ref<T> new_ref();
template< typename T, typename P0 > ref<T> new_ref( P0 );
template< typename T, typename P0, typename P1 > ref<T> new_ref( P0, P1 );
template< typename T, typename P0, typename P1, typename P2 > ref<T> new_ref( P0, P1, P2 );
template< typename T, typename P0, typename P1, typename P2, typename P3 > ref<T> new_ref( P0, P1, P2, P3 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > ref<T> new_ref( P0, P1, P2, P3, P4 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > ref<T> new_ref( P0, P1, P2, P3, P4, P5 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > ref<T> new_ref( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );

template< typename T > void add_system( T* system );
template< typename T > void remove_system();
template< typename T > T* system();

template< typename T > void swap( T* a, T* b );

struct event_handler { virtual void on_event( string_id const& event, void* user_data ) = 0; };


enum key_id 
	{ 
	KEY_INVALID, KEY_LBUTTON, KEY_RBUTTON, KEY_CANCEL, KEY_MBUTTON,  KEY_XBUTTON1, KEY_XBUTTON2, KEY_BACK, KEY_TAB, 
	KEY_CLEAR, KEY_RETURN, KEY_SHIFT,  KEY_CONTROL, KEY_MENU, KEY_PAUSE, KEY_CAPITAL, KEY_KANA, KEY_HANGUL = KEY_KANA, 
	KEY_JUNJA, KEY_FINAL, KEY_HANJA, KEY_KANJI = KEY_HANJA, KEY_ESCAPE, KEY_CONVERT, KEY_NONCONVERT, KEY_ACCEPT, 
	KEY_MODECHANGE, KEY_SPACE, KEY_PRIOR, KEY_NEXT, KEY_END,  KEY_HOME, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN, 
	KEY_SELECT, KEY_PRINT, KEY_EXEC, KEY_SNAPSHOT, KEY_INSERT, KEY_DELETE, KEY_HELP, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, 
	KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, 
	KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LWIN, 
	KEY_RWIN, KEY_APPS, KEY_SLEEP, KEY_NUMPAD0, KEY_NUMPAD1, KEY_NUMPAD2, KEY_NUMPAD3, KEY_NUMPAD4, KEY_NUMPAD5, 
	KEY_NUMPAD6, KEY_NUMPAD7, KEY_NUMPAD8, KEY_NUMPAD9, KEY_MULTIPLY, KEY_ADD, KEY_SEPARATOR, KEY_SUBTRACT, KEY_DECIMAL, 
	KEY_DIVIDE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 
	KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24, 
	KEY_NUMLOCK, KEY_SCROLL, KEY_LSHIFT, KEY_RSHIFT, KEY_LCONTROL, KEY_RCONTROL, KEY_LMENU, KEY_RMENU, KEY_BROWSER_BACK, 
	KEY_BROWSER_FORWARD, KEY_BROWSER_REFRESH, KEY_BROWSER_STOP, KEY_BROWSER_SEARCH, KEY_BROWSER_FAVORITES, 
	KEY_BROWSER_HOME, KEY_VOLUME_MUTE, KEY_VOLUME_DOWN, KEY_VOLUME_UP, KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_PREV_TRACK, 
	KEY_MEDIA_STOP, KEY_MEDIA_PLAY_PAUSE, KEY_LAUNCH_MAIL, KEY_LAUNCH_MEDIA_SELECT, KEY_LAUNCH_APP1, KEY_LAUNCH_APP2, 
	KEY_OEM_1, KEY_OEM_PLUS, KEY_OEM_COMMA, KEY_OEM_MINUS, KEY_OEM_PERIOD, KEY_OEM_2, KEY_OEM_3, KEY_OEM_4, KEY_OEM_5, 
	KEY_OEM_6, KEY_OEM_7, KEY_OEM_8, KEY_OEM_102, KEY_PROCESSKEY, KEY_ATTN, KEY_CRSEL, KEY_EXSEL, KEY_EREOF, KEY_PLAY, 
	KEY_ZOOM, KEY_NONAME, KEY_PA1, KEY_OEM_CLEAR, KEY_PEN_TOUCH, KEY_PEN_LOWER_BUTTON, KEY_PEN_UPPER_BUTTON, KEYCOUNT 
	};


enum mouseaxis_id { MOUSEAXIS_LEFTRIGHT, MOUSEAXIS_FORWARDBACK, MOUSEAXIS_WHEEL, };


enum gamepadaxis_id 
	{ 
	GAMEPADAXIS_LEFT_TRIGGER, GAMEPADAXIS_RIGHT_TRIGGER, GAMEPADAXIS_LEFTSTICK_X, GAMEPADAXIS_LEFTSTICK_Y, 
	GAMEPADAXIS_RIGHTSTICK_X, GAMEPADAXIS_RIGHTSTICK_Y, 
	};


enum gamepadbutton_id 
	{ 
	GAMEPADBUTTON_DPAD_UP, GAMEPADBUTTON_DPAD_DOWN, GAMEPADBUTTON_DPAD_LEFT, GAMEPADBUTTON_DPAD_RIGHT, 
	GAMEPADBUTTON_START, GAMEPADBUTTON_BACK, GAMEPADBUTTON_STICK_LEFT, GAMEPADBUTTON_STICK_RIGHT, 
	GAMEPADBUTTON_SHOULDER_LEFT, GAMEPADBUTTON_SHOULDER_RIGHT, GAMEPADBUTTON_A, GAMEPADBUTTON_B, 
	GAMEPADBUTTON_X, GAMEPADBUTTON_Y, 
	};



void mount_resources( string const& path );
void mount_resources( string const& primary, string const& secondary );

enum day_id { DAY_MONDAY, DAY_TUESDAY, DAY_WEDNESDAY, DAY_THURSDAY, DAY_FRIDAY, DAY_SATURDAY, DAY_SUNDAY, };
struct datetime final { int year; int month; int day; int hour; int minute; int second; day_id day_of_week; };
datetime now();
	
int abs( int x );
int min( int x, int y );
int max( int x, int y );
int clamp( int x, int min_val, int max_val );

i64 time();
int clock();
float delta_time();
size_t mem_used( int* alloc_count = 0, size_t* peak_use = 0 );
void stdprint( string format, ... );

void title( string const& text );
string title();
void window_pos( int x, int y );
int window_x();
int window_y();
void window_size( int width, int height );
int window_width();
int window_height();
void border_size( int width, int height );
int border_width();
int border_height();
void screen_size( int width, int height );
int screen_width();
int screen_height();
void fullscreen( bool use_fullscreen );
bool fullscreen();
void crt_mode( bool use_crt );
bool crt_mode();

struct display { string id; int x; int y; int width; int height; };
array<display> const& displays();

struct bitmap;
struct audio;
struct font;

bitmap* screen_bitmap();


enum color_resolution_t
	{
	COLOR_RESOLUTION_GRAY1, COLOR_RESOLUTION_GRAY2, COLOR_RESOLUTION_GRAY4, COLOR_RESOLUTION_GRAY8, 
	COLOR_RESOLUTION_RGB3, COLOR_RESOLUTION_RGB6, COLOR_RESOLUTION_RGB8, COLOR_RESOLUTION_RGB9, COLOR_RESOLUTION_RGB12,
	COLOR_RESOLUTION_RGB15, COLOR_RESOLUTION_RGB16, COLOR_RESOLUTION_RGB18, COLOR_RESOLUTION_RGB24,
	};

void color_resolution( color_resolution_t res );
color_resolution_t color_resolution();

struct rgb final
	{
	u8 r, g, b; 
	
	rgb();
	rgb( int r_, int g_, int b_ );
	
	rgb( u32 xbgr );
	operator u32();
	
	rgb( float3 rgb );
	operator float3();

	rgb( float4 rgb );
	operator float4();
	};

void default_palette();

void load_palette( string const& filename );
void load_palette( string const& filename, rgb colors[ 256 ] );
rgb const* palette();
void palette( rgb const* colors, int count, int start = 0 );
rgb palette_color( int index);
void palette_color( int index, rgb color ); 
void palette_color( int index, u8 r, u8 g, u8 b ); 

void palette_split( int y_pos );
void remove_palette_split( int y_pos );
rgb* palette( int y_pos );
void palette( int y_pos, rgb const* colors, int count, int start = 0 );
rgb palette_color( int y_pos, int index);
void palette_color( int y_pos, int index, rgb color );
void palette_color( int y_pos, int index, u8 r, u8 g, u8 b );

int brightest_color();
int darkest_color();

rgb rgb9( u16 xrgb ); // 0x000 - 0x777
rgb rgb9( u8 r, u8 g, u8 b ); // 0x0 - 0x7
rgb rgb12( u16 xrgb ); // 0x000 - 0xfff
rgb rgb12( u8 r, u8 g, u8 b );  // 0x0 - 0xf
rgb rgb18( u32 xrgb );  // 0x000000 - 0x3f3f3f
rgb rgb18( u8 r, u8 g, u8 b ); // 0x00 - 0x3f


void cpu_bars_enabled( bool enabled );
bool cpu_bars_enabled();
void cpu_bar( rgb color );
void cpu_bar( u8 r, u8 g, u8 b );
void cpu_bar();

bool file_exists( string const& filename );

struct dir_info final { string filename; bool is_folder; size_t size; };
array<dir_info> dir( string const& path, bool recursive = false );

void* mem_alloc( size_t size );
void mem_free( void* ptr );

struct binary { size_t size; void* data; };

ref<binary> bload( string const& filename );
ref<binary> bnew( size_t size );
ref<binary> bresize( ref<binary> const& bin, size_t new_size );

void bsave( void* data, size_t size, string filename );
void bsave( ref<binary> const& bin, string filename );

struct binary_reader final
	{
	binary_reader( ref<binary> const& bin );
	~binary_reader();
	
	ref<binary> bin();
	void reset();
	void position( size_t pos );
	size_t position() const;
	
	// on older MSVC versions, char is same as i8
	#if !defined(_MSC_VER) || _MSC_VER >= 1600 
		int read( char* value, int count = 1 );
	#endif
	int read( i8* value, int count = 1 );
	int read( i16* value, int count = 1 );
	int read( i32* value, int count = 1 );
	int read( i64* value, int count = 1 );
	int read( u8* value, int count = 1 );
	int read( u16* value, int count = 1 );
	int read( u32* value, int count = 1 );
	int read( u64* value, int count = 1 );
	int read( float* value, int count = 1 );
	int read( double* value, int count = 1 );
	int read( bool* value, int count = 1 ); 
	
	private:
		ref<binary> bin_;
		u8 internals_[ 32 ];
	};


struct binary_writer final
	{
	binary_writer( ref<binary> const& bin, bool resize = true );
	~binary_writer();
	
	ref<binary> bin();
	void reset();
	void position( size_t pos );
	size_t position() const;
	
	// on older MSVC versions, char is same as i8
	#if !defined(_MSC_VER) || _MSC_VER >= 1600 
		int write( char const* value, int count = 1 );
	#endif
	
	int write( i8 const* value, int count = 1 );
	int write( i16 const* value, int count = 1 );
	int write( i32 const* value, int count = 1 );
	int write( i64 const* value, int count = 1 );
	int write( u8 const* value, int count = 1 );
	int write( u16 const* value, int count = 1 );
	int write( u32 const* value, int count = 1 );
	int write( u64 const* value, int count = 1 );
	int write( float const* value, int count = 1 );
	int write( double const* value, int count = 1 );
	int write( bool const* value, int count = 1 );  
	
	private:
		ref<binary> bin_;
		bool resize_;
		u8 internals_[ 48 ];
	};
	

typedef dictionary<string_id, string> ini_section;

struct ini_file
	{
	ini_section global;
	dictionary<string_id, ini_section> sections;
	};

ini_file ini_load( ref<binary> const& bin );
ini_file ini_load( string const& filename );

ref<binary> ini_save( ini_file const& ini );
void ini_save( ini_file const& ini, string const& filename );

void mouse_pointer( bitmap const* bitmap, int hotspot_x = 0, int hotspot_y = 0 );
void mouse_pointer( u8 const* pixels, u8 const* mask, int width, int height, int hotspot_x = 0, int hotspot_y = 0 );
int mouse_x();
int mouse_y();
void mouse_position( int x, int y );
void limit_mouse( int x1, int y1, int x2, int y2 );
void limit_mouse();
void auto_scale_mouse_pointer( bool auto_scale );
bool auto_scale_mouse_pointer();

int pen_x();
int pen_y();
float pen_pressure();

void time_event( event_handler* handler, float seconds, string_id const& event_id, void* user_data = 0 );
void repeating_time_event( event_handler* handler, float seconds, string_id const& event_id, void* user_data = 0 );

bool gamepad_connected( int pad_index );
float gamepad_axis( int pad_index, gamepadaxis_id axis );
bool gamepad_is_down( int pad_index, gamepadbutton_id button );
bool gamepad_was_pressed( int pad_index, gamepadbutton_id button );
bool gamepad_was_released( int pad_index, gamepadbutton_id button );

void gamepad_pressed_event( event_handler* handler, int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data = 0 );
void gamepad_released_event( event_handler* handler, int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data = 0 );
void gamepad_axis_event( event_handler* handler, int pad_index, gamepadaxis_id axis, float threshold, string_id const& event_id, void* user_data = 0 );
	
bool key_is_down( key_id key );
bool key_was_pressed( key_id key );
bool key_was_released( key_id key );

void key_pressed_event( event_handler* handler, key_id key, string_id const& event_id, void* user_data = 0 );
void key_released_event( event_handler* handler, key_id key, string_id const& event_id, void* user_data = 0 );
void ascii_event( event_handler* handler, char ascii, string_id const& event_id, void* user_data = 0 );

int action_axis( string_id const& action, key_id key_neg, key_id key_pos, float scale = 1.0f );
int action_axis( string_id const& action, mouseaxis_id axis, bool invert = false, float scale = 1.0f );
int action_axis( string_id const& action, int pad_index, gamepadaxis_id axis, bool invert = false, float scale = 1.0f );
int action_axis( string_id const& action, int pad_index, gamepadbutton_id button_neg, gamepadbutton_id button_pos, float scale = 1.0f );
			 
int action_button( string_id const& action, key_id key );
int action_button( string_id const& action, mouseaxis_id axis, bool invert, float threshold );
int action_button( string_id const& action, int pad_index, gamepadaxis_id axis, bool invert, float threshold );
int action_button( string_id const& action, int pad_index, gamepadbutton_id button );

void action_unmap( int handle );
void action_remove( string_id const& action );

float action( string_id const& action );
void action_event( event_handler* handler, string_id const& action, string_id const& event_id, void* user_data = 0 );
void action_event( event_handler* handler, string_id const& action, float threshold, 
	string_id const& event_id, void* user_data = 0 );

void remove_event_handler( event_handler* handler );

tweener tween( float duration );
void stop_all_tweeners();
void pause_all_tweeners();
void resume_all_tweeners();


template< typename T > void register_state();
template< typename T > void switch_state( float trans_out = 0.0f, float trans_in = 0.0f );

void random_seed( u32 seed );
float random();
int random( int min, int max );
float random_bell_curve( int iterations = 3 );
int random_bell_curve( int min, int max, int iterations = 3 );
template< typename T > void shuffle( T* elements, int count );
template< typename T > void shuffle( array<T>* arr );
template< typename T > void shuffle( pod_array<T>* arr );
float3 random_unit_vector();


// This function computes a random value at the coordinate (x,y,z). Adjacent random values are continuous but the noise 
// fluctuates its randomness with period 1, i.e. takes on wholly unrelated values at integer points. 
// The "wrap" parameters can be used to create wraparound noise that wraps at powers of two. Specify 0 to mean "don't 
// care". (The noise always wraps every 256 due details of the implementation, even if you ask for larger or no 
// wrapping.)

float perlin_noise( float3 pos, int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );
float perlin_noise( float x, float y, float z, int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );


// Three common fractal noise functions, which produce a wide variety of nice effects depending on the parameters: 
//     octaves    - number of "octaves" of perlin_noise to sum
//     lacunarity - spacing between successive octaves (use exactly 2.0 for wrapping output)
//     gain       - relative weighting applied to each successive octave
//     offset     - used to invert the ridges, may need to be larger, not sure

float fractal_noise_ridge( float3 pos, float lacunarity = 2.0f, float gain = 0.5f, float offset = 1.0f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );

float fractal_noise_ridge( float x, float y, float z, float lacunarity = 2.0f, float gain = 0.5f, float offset = 1.0f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );

float fractal_noise_fbm( float3 pos, float lacunarity = 2.0f, float gain = 0.5f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );

float fractal_noise_fbm( float x, float y, float z, float lacunarity = 2.0f, float gain = 0.5f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );
	
float fractal_noise_turbulence( float3 pos, float lacunarity = 2.0f, float gain = 0.5f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );

float fractal_noise_turbulence( float x, float y, float z, float lacunarity = 2.0f, float gain = 0.5f, int octaves = 6, 
	int wrap_x = 0, int wrap_y = 0, int wrap_z = 0 );


template< typename T > void sort( T* elements, int count );
template< typename T > void sort( array<T>* arr );
template< typename T > void sort( pod_array<T>* arr );

template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( T* array, int count );
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( array<T>* arr );
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( pod_array<T>* arr );

template< typename T > int find( T const* haystack_elements, int haystack_count, T const& needle );
template< typename T > int find( array<T> const& haystack, T const& needle );
template< typename T > int find( pod_array<T> const& haystack, T const& needle );

void master_volume( float volume );
float master_volume();

void pause_audio();
void resume_audio();

void play_music( resource<audio> audio_resource, float fade_in_time = 0.0f, float delay = 0.0f );
void stop_music( float fade_out_time = 0.5f );
void pause_music();
void resume_music();
void switch_music( resource<audio> audio_resource, float fade_out_time = 0.5f, float fade_in_time = 0.0f, float delay = 0.0f );
void cross_fade_music( resource<audio> audio_resource, float cross_fade_time = 1.0f, float delay = 0.0f );
void music_position( float position );
float music_position();
resource<audio> current_music();
void music_loop( bool loop );
bool music_loop();
void music_volume( float volume );
float music_volume();
void music_pan( float pan );
float music_pan();

void play_ambience( resource<audio> audio_resource, float fade_in_time = 0.0f, float delay = 0.0f );
void stop_ambience( float fade_out_time = 0.5f );
void pause_ambience();
void resume_ambience();
void switch_ambience( resource<audio> audio_resource, float fade_out_time = 0.5f, float fade_in_time = 0.0f, float delay = 0.0f );
void cross_fade_ambience( resource<audio> audio_resource, float cross_fade_time = 1.0f, float delay = 0.0f );
void ambience_position( float position );
float ambience_position();
resource<audio> current_ambience();
void ambience_loop( bool loop );
bool ambience_loop();
void ambience_volume( float volume );
float ambience_volume();
void ambience_pan( float pan );
float ambience_pan();

struct sound final
	{ 
	sound loop( bool loop );
	sound volume( float volume );
	sound pan( float pan );
	sound stop( float fade_out_time = 0.5f );
	sound pause();
	sound resume();
	sound position( float pos );

	resource<audio> audio_resource();
	float position();
	bool loop();
	float volume();
	float pan();

	sound();
	private:
		friend sound play_sound( resource<audio>, float, float, float );
		u64 handle; 
	};

sound play_sound( resource<audio> audio_resource, float priority = 0.0f, float fade_in_time = 0.0f, float delay = 0.0f );

bool starts_with( string str, string start );
bool starts_with( string_id str, string_id start );

ref<bitmap> load_bitmap( string const& filename );

enum fill_pattern 
	{ 
	FILL_PATTERN_SOLID,
	FILL_PATTERN_EMPTY,
	};

void fill_style( fill_pattern pattern, int background_color = 0 );

struct point final { int x; int y; };
enum text_align { TEXT_ALIGN_LEFT, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER, };

void clear();
void clear( bitmap* target );
void fill( int color );
void fill( bitmap* target, int color );
void pset( int x, int y, int color );
void pset( bitmap* target, int x, int y, int color );
void line( int x1, int y1, int x2, int y2, int color );
void line( bitmap* target, int x1, int y1, int x2, int y2, int color );
void box( int x1, int y1, int x2, int y2, int color );
void box( bitmap* target, int x1, int y1, int x2, int y2, int color );
void box_fill( int x1, int y1, int x2, int y2, int color );
void box_fill( bitmap* target, int x1, int y1, int x2, int y2, int color );
void circle( int x, int y, int r, int color );
void circle( bitmap* target, int x, int y, int r, int color );
void circle_fill( int x, int y, int r, int color );
void circle_fill( bitmap* target, int x, int y, int r, int color );
void ellipse( int x, int y, int rx, int ry, int color );
void ellipse( bitmap* target, int x, int y, int rx, int ry, int color );
void ellipse_fill( int x, int y, int rx, int ry, int color );
void ellipse_fill( bitmap* target, int x, int y, int rx, int ry, int color );
void polygon( point const* points, int count, int color );
void polygon( bitmap* target, point const* points, int count, int color );
void polygon_fill( point const* points, int count, int color );
void polygon_fill( bitmap* target, point const* points, int count, int color );
void text( int x, int y, string const& str, int color, resource<font> const& font_resource, 
	text_align align = TEXT_ALIGN_LEFT, int wrap_width = -1, int hspacing = 0, int vspacing = 0, int limit = -1, 
	bool bold = false, bool italic = false, bool underlined = false );
void text( bitmap* target, int x, int y, string const& str, int color, resource<font> const& font_resource, 
	text_align align = TEXT_ALIGN_LEFT, int wrap_width = -1, int hspacing = 0, int vspacing = 0, int limit = -1, 
	bool bold = false, bool italic = false, bool underlined = false );

void text_bounds( int x, int y, string const& str, resource<font> const& font_resource, 
	text_align align = TEXT_ALIGN_LEFT, int wrap_width = -1, int hspacing = 0, int vspacing = 0, bool bold = false, 
	bool italic = false, int* width = 0, int* height = 0);

struct game_state : event_handler
	{
	game_state();
	virtual ~game_state();

	virtual void tick() { };
	virtual void on_event( string_id const& event, void* user_data ) { (void) event; (void) user_data; }

	void time_event( float seconds, string_id const& event_id, void* user_data = 0 );
	void repeating_time_event( float seconds, string_id const& event_id, void* user_data = 0 );
	void gamepad_pressed_event( int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data = 0 );
	void gamepad_released_event( int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data = 0 );
	void gamepad_axis_event( int pad_index, gamepadaxis_id axis, float threshold, string_id const& event_id, void* user_data = 0 );
	void key_pressed_event( key_id key, string_id const& event_id, void* user_data = 0 );
	void key_released_event( key_id key, string_id const& event_id, void* user_data = 0 );
	void ascii_event( char ascii, string_id const& event_id, void* user_data = 0 );
	void action_event( string_id const& action, string_id const& event_id, void* user_data = 0 );
	void action_event( string_id const& action, float threshold, string_id const& event_id, void* user_data = 0 );
	};
	
	
struct bitmap final
	{
	bitmap();

	explicit bitmap( int width, int height );
	explicit bitmap( int width, int height, u8* pixels, int transparent_index = -1 );
	explicit bitmap( int width, int height, u8* pixels, u8* mask );

	explicit bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y );
	explicit bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y, u8* pixels, int transparent_index = -1 );
	explicit bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y, u8* pixels, u8* mask );

	explicit bitmap( int width, int height, int cel_count );
	explicit bitmap( int width, int height, int cel_count, u8* pixels[], int transparent_index = -1 );
	explicit bitmap( int width, int height, int cel_count, u8* pixels[], u8* masks[] );

	explicit bitmap( int width, int height, int cel_count, int offsets_x[], int offsets_y[], int pitches_x[], int pitches_y[] );
	explicit bitmap( int width, int height, int cel_count, int offsets_x[], int offsets_y[], int pitches_x[], int pitches_y[], u8* pixels[], int transparent_index = -1 );
	explicit bitmap( int width, int height, int cel_count, int offsets_x[], int offsets_y[], int pitches_x[], int pitches_y[], u8* pixels[], u8* masks[] );

	~bitmap();

	bitmap( bitmap const& other );
	bitmap const& operator=( bitmap const& other ); 
	
	int cel_count() const;
	
	int width() const;
	int height() const;

	void pixel( int cel, int x, int y, int color );
	int pixel( int cel, int x, int y ) const;
		
	void mask( int cel, int x, int y, bool opaque );
	bool mask( int cel, int x, int y ) const;

	struct lock_data final
		{
		int offset_x;
		int offset_y;
		int pitch_x;
		int pitch_y;
		u8* pixels;
		u8* mask;
		};
		
	void lock( lock_data* data );
	void lock( int cel, lock_data* data );
	void unlock();
	
	void blit( bitmap* target, int x = 0, int y = 0 );
	void blit( int x1, int y1, int x2, int y2, bitmap* target, int x = 0, int y = 0 );

	void blit( int cel, bitmap* target, int x = 0, int y = 0 );
	void blit( int cel, int x1, int y1, int x2, int y2, bitmap* target, int x = 0, int y = 0 );
	
	int offset_x( int cel = 0 ) const;
	int offset_y( int cel = 0 ) const;
	int pitch_x( int cel = 0 ) const;
	int pitch_y( int cel = 0 ) const;

	private:
		friend struct internal::internals_t;
		friend void internal::resize_screen();

		struct internal_t final
			{
			int lock_count;
			int cel_count;
			int width;
			int height;
			void* storage;

			struct normal_cel final { int offset_x; int offset_y; int pitch_x; int pitch_y; u8* pixels; u8* mask; };
			enum data_type { DATA_TYPE_NONE, DATA_TYPE_NORMAL, } type;
			union 
				{
				normal_cel* cels_normal;
				};
		} internal;
	};
	

struct font final
	{
	font();
	explicit font( void const* data, size_t size );
	~font();
	
	font( font const& other );
	font const& operator=( font const& other ); 

	int height() const;
	int line_spacing() const;
	int baseline() const;

	struct bounds_t final { int width; int height; };

	enum alignment_enum
		{
		ALIGNMENT_LEFT,
		ALIGNMENT_RIGHT,
		ALIGNMENT_CENTER,
		};

	void blit( int x, int y, string const& str, u8 color, u8* target, int width, int height, 
		alignment_enum align = ALIGNMENT_LEFT, int wrap_width = -1, int hspacing = 0, int vspacing = 0, int limit = -1, 
		bool bold = false, bool italic = false, bool underlined = false, bounds_t* bounds = 0 ) const;
	
	void blit( int x, int y, string const& str, u32 color, u32* target, int width, int height, 
		alignment_enum align = ALIGNMENT_LEFT, int wrap_width = -1, int hspacing = 0, int vspacing = 0, int limit = -1, 
		bool bold = false, bool italic = false, bool underlined = false, bounds_t* bounds = 0 ) const;

	private:
		struct
			{
			void* pixelfont;
			} internal;
	};


struct audio_instance
	{
	void (*release)( audio_instance* instance );
	int (*read_samples)( audio_instance* instance, float* sample_pairs, int sample_pairs_count );
	void (*restart)( audio_instance* instance );
	void (*set_position)( audio_instance* instance, int offset_in_sample_pairs_from_start );
	int (*get_position_in_sample_pairs_from_start)( audio_instance* instance );
	int (*get_length_in_sample_pairs)( audio_instance* instance );
	};

typedef audio_instance* (*audio_format_t)( void* data, size_t size );

void register_audio_format( audio_format_t format );

struct audio final
	{
	audio();
	explicit audio( ref<binary> bin );        
	explicit audio( float* sample_pairs, int sample_pairs_count, bool take_ownership_of_memory = false );
	~audio();

	float length() const;
			
	audio_instance* create_instance();
	void destroy_instance( audio_instance* instance );

	private:
		struct  
			{
			ref<binary> bin;
			audio_format_t format;
			float length;
			int instance_count;
			} internal;
	};    
	

struct internal_sprite;


struct sprite_manager final
	{
	sprite_manager();
	~sprite_manager();

	sprite_manager& add( internal_sprite* spr );
	sprite_manager& remove( internal_sprite* spr );

	int count() const;
	internal_sprite* sprite( int index ) const;

	void add_event_handler( event_handler* handler );
	void remove_event_handler( event_handler* handler );

	sprite_manager& origin( float x, float y );

	sprite_manager& origin_x( float x );
	float origin_x() const;

	sprite_manager& origin_y( float y );
	float origin_y() const;

	private:
		void internal_update();
		void internal_render();

		struct 
			{
			pod_array<internal_sprite*, 256> sprites;
			pod_array<event_handler*> event_handlers;
			float origin_x;
			float origin_y;
			float zorder;
			internal_sprite* current_highlighted;
			bool activated_highlighted;
			} internal;
	};


struct internal_sprite
	{
	internal_sprite();
	explicit internal_sprite( sprite_manager* manager );
	virtual ~internal_sprite();
	
	internal_sprite( internal_sprite const& other );
	internal_sprite const& operator=( internal_sprite const& other );
	
	sprite_manager* internal_manager() const;

	virtual internal_sprite& internal_position( float x, float y );

	virtual internal_sprite& internal_position_x( float x );
	virtual float internal_position_x() const;

	virtual internal_sprite& internal_position_y( float y );
	virtual float internal_position_y() const;

	virtual internal_sprite& internal_origin( float x, float y );

	virtual internal_sprite& internal_origin_x( float x );
	virtual float internal_origin_x() const;

	virtual internal_sprite& internal_origin_y( float y );
	virtual float internal_origin_y() const;
	
	virtual internal_sprite& internal_visible( bool is_visible );
	virtual bool internal_visible() const;

	virtual internal_sprite& internal_zorder( float z );
	virtual float internal_zorder() const;

	virtual internal_sprite& internal_cel( float index );
	virtual float internal_cel() const;

	virtual internal_sprite& internal_selection_index( int index );
	virtual int internal_selection_index() const;

	virtual internal_sprite& internal_bitmap( resource<pixie::bitmap> const& bitmap_resource );
	virtual resource<pixie::bitmap> const& internal_bitmap() const;

	virtual internal_sprite& internal_event( string_id const& event_id, void* user_data = 0 );

	virtual internal_sprite& internal_event_id( string_id const& event_id );
	virtual string_id const& internal_event_id() const;

	virtual internal_sprite& internal_event_user_data( void* user_data );
	virtual void* internal_event_user_data() const;

	private:
		friend sprite_manager;

		virtual void internal_render();
		virtual bool internal_pointer_over( int x, int y, bool button_down, bool forcehit );

		struct 
			{
			sprite_manager* manager;
			float position_x;
			float position_y;
			float origin_x;
			float origin_y;
			bool visible;
			float zorder;
			float cel;
			int selection_index;
			resource<pixie::bitmap> bitmap;
			string_id event_id;
			void* event_user_data;
		} internal;
	};


template< typename T> struct sprite_base : internal_sprite
	{
	sprite_base() { }
	explicit sprite_base( sprite_manager* manager ) : internal_sprite( manager ) { } 
	virtual ~sprite_base() { }
	
	sprite_base( sprite_base const& other ) : internal_sprite( other ) { }
	sprite_base const& operator=( sprite_base const& other ) { internal_sprite::operator=( other ); return *this; }
	
	sprite_manager* manager() const { return internal_manager(); }

	virtual T& position( float x, float y ) { return *(T*)&internal_position( x, y ); }

	virtual T& position_x( float x ) { return *(T*)&internal_position_x( x ); }
	virtual float position_x() const { return internal_position_x(); }

	virtual T& position_y( float y ) { return *(T*)&internal_position_y( y ); }
	virtual float position_y() const { return internal_position_y(); }

	virtual T& origin( float x, float y ) { return *(T*)&internal_origin( x, y ); }

	virtual T& origin_x( float x ) { return *(T*)&internal_origin_x( x ); }
	virtual float origin_x() const { return internal_origin_x(); }

	virtual T& origin_y( float y ) { return *(T*)&internal_origin_y( y ); }
	virtual float origin_y() const { return internal_origin_y(); }
	
	virtual T& visible( bool is_visible ) { return *(T*)&internal_visible( is_visible ); }
	virtual bool visible() const { return internal_visible(); }

	virtual T& zorder( float z ) { return *(T*)&internal_zorder( z ); }
	virtual float zorder() const { return internal_zorder(); }

	virtual T& cel( float index ) { return *(T*)&internal_cel( index ); };
	virtual float cel() const { return internal_cel(); }

	virtual T& selection_index( int index ) { return *(T*)&internal_selection_index( index ); };
	virtual int selection_index() const { return internal_selection_index(); }

	virtual T& bitmap( resource<pixie::bitmap> const& bitmap_resource ) { return *(T*)&internal_bitmap( bitmap_resource ); }
	virtual resource<pixie::bitmap> const& bitmap() const { return internal_bitmap(); }

	virtual T& event( string_id const& event_id, void* user_data = 0 ) { return *(T*)&internal_event( event_id, user_data ); }

	virtual T& event_id( string_id const& event_id ) { return *(T*)&internal_event_id( event_id ); }
	virtual string_id const& event_id() const { return internal_event_id(); }

	virtual T& event_user_data( void* user_data ) { return *(T*)&internal_event_user_data( user_data ); }
	virtual void* event_user_data() const { return internal_event_user_data(); }

	};


struct sprite final : sprite_base<sprite>
	{
	};


struct rendercall;


struct rendercall_handler 
	{
	virtual void render( rendercall* call, bitmap* target ) = 0;
	};


struct rendercall final : sprite_base<rendercall>
	{
	rendercall();
	explicit rendercall( sprite_manager* manager );
	virtual ~rendercall();
	
	rendercall( rendercall const& other );
	rendercall const& operator=( rendercall const& other );

	virtual rendercall& handler( rendercall_handler* new_handler );
	virtual rendercall_handler* handler() const;

	private:
		virtual void internal_render();

		struct
			{
			rendercall_handler* handler;
			} internal;
	};


struct label final : sprite_base<label>
	{
	label();
	explicit label( sprite_manager* manager );
	virtual ~label();
	
	label( label const& other );
	label const& operator=( label const& other );

	virtual label& text( string str );
	virtual string text() const;

	virtual label& font( resource<pixie::font> const& font_resource );
	virtual resource<pixie::font> const& font() const;

	virtual label& color( int index );
	virtual int color() const;

	virtual label& wrap( int width = -1 );
	virtual int wrap() const;

	virtual label& hspacing( int spacing );
	virtual int hspacing() const;
	
	virtual label& vspacing( int spacing );
	virtual int vspacing() const;

	virtual label& limit( float lim );
	virtual float limit() const;
	
	virtual label& align( text_align new_align );
	virtual text_align align() const;
	
	virtual label& bold( bool use_bold );
	virtual bool bold() const;

	virtual label& italic( bool use_italic );
	virtual bool italic() const;

	virtual label& underline( bool use_underline );
	virtual bool underline() const;

	virtual label& outline( int color ); // no outline: color = -1
	virtual int outline() const;

	virtual label& shadow( int color = -1, float offset_x = 1.0f, float offset_y = 1.0f );

	virtual label& shadow_color( int color );
	virtual int shadow_color() const;

	virtual label& shadow_offset_x( float offset );
	virtual float shadow_offset_x() const;

	virtual label& shadow_offset_y( float offset );
	virtual float shadow_offset_y() const;
	
	virtual int width() const;
	virtual int height() const;
	
	private:
		virtual void internal_render();

		struct
			{
			string text;
			resource<pixie::font> font;
			int color;
			int wrap;
			int hspacing;
			int vspacing;
			float limit;
			text_align align;
			bool bold;
			bool italic;
			bool underline;
			int outline_color;
			int shadow_color;
			float shadow_offset_x;
			float shadow_offset_y;
			} internal;
	};


struct button final : sprite_base<button>
	{
	button();
	explicit button( sprite_manager* manager );
	virtual ~button();
	
	button( button const& other );
	button const& operator=( button const& other );

	virtual button& enabled( bool is_enabled ); 
	virtual bool enabled() const;

	virtual button& bitmap_disabled( resource<pixie::bitmap> const& bitmap_resource );
	virtual resource<pixie::bitmap> const& bitmap_disabled() const;

	virtual button& bitmap_highlighted( resource<pixie::bitmap> const& bitmap_resource );
	virtual resource<pixie::bitmap> const& bitmap_highlighted() const;

	virtual button& bitmap_activated( resource<pixie::bitmap> const& bitmap_resource );
	virtual resource<pixie::bitmap> const& bitmap_activated() const;

	virtual button& pixel_picking( bool use_pixel_picking );
	virtual bool pixel_picking() const;


	virtual void simulate_actived( float pressed_time = 0.15f );

	private:
		virtual void internal_render();
		virtual bool internal_pointer_over( int x, int y, bool button_down, bool forcehit );

		struct internal_t
			{
			bool enabled;
			bool highlighted;
			enum button_state { STATE_NORMAL, STATE_HIGHLIGHTED, STATE_ACTIVATED, STATE_DISABLED, };
			button_state state;
			resource<pixie::bitmap> bitmap_disabled;
			resource<pixie::bitmap> bitmap_highlighted;
			resource<pixie::bitmap> bitmap_activated;
			bool pixel_picking;
			float activated_override;
			} internal;
	};


struct shape final : sprite_base<shape>
	{
	shape();
	explicit shape( sprite_manager* manager );
	virtual ~shape();
	
	shape( shape const& other );
	shape const& operator=( shape const& other );

	virtual shape& filled( bool is_filled );
	virtual bool filled() const;

	virtual shape& color( int index );
	virtual int color() const;

	virtual shape& point( float x, float y );
	virtual shape& line( float x1, float y1, float x2, float y2 );
	virtual shape& line( float x2, float y2 );
	virtual shape& box( float x1, float y1, float x2, float y2 );
	virtual shape& box( float width, float height );
	virtual shape& circle( float x, float y, float r );
	virtual shape& circle( float r );
	virtual shape& ellipse( float x, float y, float rx, float ry );
	virtual shape& ellipse( float rx, float ry );
	virtual shape& polygon( int count, float const* points );

	enum shape_type { SHAPE_TYPE_NONE, SHAPE_TYPE_POINT, SHAPE_TYPE_LINE, SHAPE_TYPE_BOX, SHAPE_TYPE_CIRCLE, 
		SHAPE_TYPE_ELLIPSE, SHAPE_TYPE_POLYGON, };
	
	struct shape_data
		{
		shape_type type;
		union 
			{
			struct { float x; float y; } point;
			struct { float x1; float y1; float x2; float y2; } line;
			struct { float x1; float y1; float x2; float y2; } box;
			struct { float x; float y; float r; } circle;
			struct { float x; float y; float rx; float ry; } ellipse;
			struct { int count; float const* points; } polygon;
			} data;
		};

	virtual shape& data( shape_data const& data );
	virtual shape_data const& data() const;

	private:
		virtual void internal_render();

		struct
			{
			bool filled;
			int color;
			shape_data data;
			array<float> polygon_points;
			array<int> int_polygon_points;
			} internal;
	};


ref< property<float> > property_position_x( internal_sprite* sprite );
ref< property<float> > property_position_y( internal_sprite* sprite );
ref< property<float> > property_origin_x( internal_sprite* sprite );
ref< property<float> > property_origin_y( internal_sprite* sprite );
ref< property<bool> > property_visible( internal_sprite* sprite );
ref< property<float> > property_zorder( internal_sprite* sprite );
ref< property<float> > property_cel( internal_sprite* sprite );
ref< property<int> > property_selection_index( internal_sprite* sprite );
ref< property< resource<bitmap> const& > > property_bitmap( internal_sprite* sprite );
ref< property<string_id const&> > property_event_id( internal_sprite* sprite );
ref< property<void*> > property_event_user_data( internal_sprite* sprite );

ref< property<rendercall_handler*> > property_handler( rendercall* sprite );

ref< property<string> > property_text( label* sprite );
ref< property< resource<font> const& > > property_font( label* sprite );
ref< property<int> > property_color( label* sprite );
ref< property<int> > property_wrap( label* sprite );
ref< property<int> > property_hspacing( label* sprite );
ref< property<int> > property_vspacing( label* sprite );
ref< property<float> > property_limit( label* sprite );
ref< property<text_align> > property_align( label* sprite );
ref< property<bool> > property_bold( label* sprite );
ref< property<bool> > property_italic( label* sprite );
ref< property<bool> > property_underline( label* sprite );
ref< property<int> > property_outline( label* sprite );
ref< property<int> > property_shadow_color( label* sprite );
ref< property<float> > property_shadow_offset_x( label* sprite );
ref< property<float> > property_shadow_offset_y( label* sprite );

ref< property<bool> > property_enabled( button* sprite );
ref< property< resource<bitmap> const& > > property_bitmap_disabled( button* sprite );
ref< property< resource<bitmap> const& > > property_bitmap_highlighted( button* sprite );
ref< property< resource<bitmap> const& > > property_bitmap_activated( button* sprite );
ref< property<bool> > property_pixel_picking( button* sprite );

ref< property<bool> > property_filled( shape* sprite );
ref< property<int> > property_color( shape* sprite );
ref< property<shape::shape_data const&> > property_shape_data( shape* sprite );


float ease_linear( float t );
		
float ease_smoothstep( float t );
float ease_smootherstep( float t );
		
float ease_quad_out( float t );
float ease_quad_in( float t );
float ease_quad_in_out( float t );
		
float ease_back_out( float t );
float ease_back_in( float t );
float ease_back_in_out( float t );
		
float ease_bounce_out( float t );
float ease_bounce_in( float t );
float ease_bounce_in_out( float t );
		
float ease_sine_out( float t );
float ease_sine_in( float t );
float ease_sine_in_out( float t );
		
float ease_elastic_out( float t );
float ease_elastic_in( float t );
float ease_elastic_in_out( float t );
		
float ease_expo_out( float t );
float ease_expo_in( float t );
float ease_expo_in_out( float t );
		
float ease_cubic_out( float t );
float ease_cubic_in( float t );
float ease_cubic_in_out( float t );
		
float ease_quart_out( float t );
float ease_quart_in( float t );
float ease_quart_in_out( float t );
		
float ease_quint_out( float t );
float ease_quint_in( float t );
float ease_quint_in_out( float t );
		
float ease_circle_out( float t );
float ease_circle_in( float t );
float ease_circle_in_out( float t );

tweener slowprint( label* lbl, string text, float delay = 0.1f );
	

template< typename T > ref<T> pool_ref( mempool<T>* pool_instance );
template< typename T, typename P0 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0 );
template< typename T, typename P0, typename P1 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1 );
template< typename T, typename P0, typename P1, typename P2 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2 );
template< typename T, typename P0, typename P1, typename P2, typename P3 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 );
template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > ref<T> pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 );

} /* namespace pixie */


#endif // pixie_hpp



/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef pixie_impl
#define pixie_impl

namespace pixie { namespace internal {

struct internals_t;
internals_t* internals();
void* memctx();
void* systems_alloc( size_t size );
void systems_free( void* p );
strpool::internal::string_pool& string_pool();
strpool::internal::string_pool& string_id_pool();
gamestate::game_state_system<>* game_states();
objrepo::object_repo* object_repo();

template< typename T > void placement_new( void* storage ) { new (storage) T(); }    
template< typename T > struct game_state_wrapper { T state; void tick() { state.tick(); } };
resources::resource_system* resource_system();

template< typename T > void ref_copy( void* dst, void const* src ) { new (dst) ref<T>( *(ref<T>*) src );  }
void free_ref_key( void* instance );
	
template< typename T > void destroy_ref_key( void* instance )
	{
	ref<T>* refcopy = (pixie::ref<T>*) instance;
	refcopy->~ref();
	free_ref_key( instance );
	}
	
resources::resource_key make_ref_key( void (*copy_func)( void*, void const*), void const* ref, size_t size, void (*destroy_func)( void* ) );

resources::resource_key make_string_key( string const& filename );

} /* namespace internal */ } /* namespace pixie */


namespace resources {

inline resource_key make_key( pixie::bitmap*, char const* filename ) { return pixie::internal::make_string_key( pixie::string( filename ) ); }
void resource_create( pixie::bitmap** instance, pixie::string const& filename );
void resource_destroy( resource_key* key, pixie::bitmap* instance );

inline resource_key make_key( pixie::font*, char const* filename ) { return pixie::internal::make_string_key( pixie::string( filename ) ); }
void resource_create( pixie::font** instance, pixie::string const& filename );
void resource_destroy( resource_key* key, pixie::font* instance );

inline resource_key make_key( pixie::audio*, char const* filename ) { return pixie::internal::make_string_key( pixie::string( filename ) ); }
void resource_create( pixie::audio** instance, pixie::string const& filename );
void resource_destroy( resource_key* key, pixie::audio* instance );

inline resource_key make_key( pixie::audio*, float* sample_pairs, int sample_pairs_count, bool take_ownership_of_memory = false ) { (void) sample_pairs, sample_pairs_count, take_ownership_of_memory; return pixie::internal::make_string_key( pixie::string( "" ) ); }
void resource_create( pixie::audio** instance, float* sample_pairs, int sample_pairs_count, bool take_ownership_of_memory = false );

template< typename T > void resource_create( T** instance, pixie::ref<T> const& ref_obj ) { *instance = (T*)ref_obj; }
template< typename T > void resource_create( T** instance, char const* filename ) { resource_create( instance, pixie::string( filename ) ); }

template< typename T > resource_key make_key( T*, pixie::string const& filename ) { return pixie::internal::make_string_key( filename ); }
template< typename T > resource_key make_key( T*, pixie::ref<T> instance ) { return pixie::internal::make_ref_key( pixie::internal::ref_copy<T>, &instance, sizeof( instance ), pixie::internal::destroy_ref_key<T> );  }

} /* namespace resources */


namespace pixie { namespace internal {
	
template< typename T > void copy_resource( void* dst, void const* src )
	{
	resource<T> const* src_res = (resource<T> const*) src;
	new (dst) resource<T>( *src_res );
	}

template< typename T > void destroy_resource( void* instance )
	{
	resource<T>* res = (resource<T>*) instance;
	res->~resource<T>();
	}

template< typename T > void compare_resource( void const* a, void const* b )
	{
	resource<T> const* a_res = (resource<T> const*) a;
	resource<T> const* b_res = (resource<T> const*) b;
	return (*a_res) == (*b_res);
	}

void pin_resource( type_id_t type, void (*copy)( void*, void const* ), void (*destroy)( void* ), void const* instance, string_id group );

void unpin_resource( type_id_t type, bool (*cmp)( void const*, void const* ), void const* instance, string_id group );

} /* namespace internal */ } /* namespace pixie */


template< typename T > void pixie::pin_resource( resource<T> const& res, string_id group )
	{
	internal::pin_resource( type_id<T>(), internal::copy_resource<T>, internal::destroy_resource<T>, &res, group );
	}


template< typename T > void pixie::unpin_resource( resource<T> const& res, string_id group )
	{
	internal::unpin_resource( type_id<T>(), internal::compare_resource<T>, &res, group );
	}

template<> inline strpool::internal::string_pool& strpool::internal::pool_instance<pixie::internal::PIXIE_STRING_POOL>( bool )
	{
	return pixie::internal::string_pool();
	}
	
template<> inline strpool::internal::string_pool& strpool::internal::pool_instance<pixie::internal::PIXIE_STRING_ID_POOL>( bool )
	{
	return pixie::internal::string_id_pool();
	}



template< typename T > void pixie::add_system( T* system )
	{
	internal::object_repo()->add( system );
	}
	
	
template< typename T > void pixie::remove_system()
	{
	T* sys = system<T>();
	if( sys )
		internal::object_repo()->remove( sys );
	}
	

template< typename T > T* pixie::system()
	{
	if( !internal::object_repo() ) return 0;
	return internal::object_repo()->get<T>();
	}


template< typename T > void pixie::register_state()
	{
	static_cast<pixie::game_state*>( (T*) 0 ); // ensure T is derived from pixie::game_state
	internal::game_states()->add<T, internal::game_state_wrapper<T>, &internal::game_state_wrapper<T>::tick>();
	}


template< typename T > void pixie::switch_state( float trans_out, float trans_in)
	{ 
	internal::game_states()->set<T>( trans_out, trans_in );
	}


template< typename T > void pixie::swap( T* a, T* b )
	{
	// expressed using only copy constructor, no assignment operator, for consistency with container classes
	T t( *a ); // t = a
	a->~T(); new ( a ) T( *b ); // a = b
	b->~T(); new ( b ) T( t ); // b = t
	}
	

template< typename T, int CAPACITY > pixie::array<T, CAPACITY>::array( int initial_capacity = CAPACITY ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( initial_capacity, internal::memctx() ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie::array<T, CAPACITY>::array( U const& other ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( other ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie::array<T, CAPACITY>::array( U const* items, int count ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( items, count, internal::memctx() ) 
	{ }


template< typename T, int CAPACITY > pixie::pod_array<T, CAPACITY>::pod_array( int initial_capacity = CAPACITY ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( initial_capacity, internal::memctx() ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie::pod_array<T, CAPACITY>::pod_array( U const& other ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( other ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie::pod_array<T, CAPACITY>::pod_array( U const* items, int count ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( items, count, internal::memctx() ) 
	{ }


template< typename T > void pixie::shuffle( T* elements, int count )
	{
	for( int i = 0; i < count; ++i )
		{
		int const r = random( i, count - 1 );
		swap( &elements[ i ], &elements[ r ] );
		}
	}
	
	
template< typename T > void pixie::shuffle( array<T>* arr ) { shuffle( arr->data(), arr->count() ); }


template< typename T > void pixie::shuffle( pod_array<T>* arr ) { shuffle( arr->data(), arr->count() ); }
	
template< typename T > void pixie::sort( T* elements, int count ) { ::sort_ns::sort( elements, count ); }

template< typename T > void pixie::sort( array<T>* arr ) { ::sort_ns::sort( arr->data(), arr->count() ); }

template< typename T > void pixie::sort( pod_array<T>* arr ) { ::sort_ns::sort( arr->data(), arr->count() ); }
		
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie::custom_sort( T* elements, int count )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( array, count );
	}
	
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie::custom_sort( array<T>* arr )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( arr->data(), arr->count() );
	}
	
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie::custom_sort( pod_array<T>* arr )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( arr->data(), arr->count() );
	}


template< typename T > int pixie::find( T const* haystack_elements, int haystack_count, T const& needle ) 
	{ 
	for( int i = 0; i < haystack_count; ++i )
		if( haystack_elements[ i ] == needle ) return i;
	return -1;
	}

template< typename T > int pixie::find( array<T> const& haystack, T const& needle )
	{
	return find( haystack.data(), haystack.count(), needle );
	}

template< typename T > int pixie::find( pod_array<T> const& haystack, T const& needle )
	{
	return find( haystack.data(), haystack.count(), needle );
	}


template< typename T > 
pixie::ref<T> pixie::new_ref() 
	{ 
	return ref<T>::make_new(); 
	}


template< typename T, typename P0 > 
pixie::ref<T> pixie::new_ref( P0 p0 ) 
	{ 
	return ref<T>::make_new( p0 ); 
	}


template< typename T, typename P0, typename P1 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1 ) 
	{ 
	return ref<T>::make_new( p0, p1 );
	}


template< typename T, typename P0, typename P1, typename P2 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); 
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
pixie::ref<T> pixie::new_ref( P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return ref<T>::make_new( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); 
	}


namespace pixie { namespace internal { 
	template< typename T > 
	struct type_id_helper { 
		static int* id() 
			{ 
			static int t; 
			return &t; 
			} 
		}; 
} /* namespace internal */ } /* namespace pixie */


template< typename T > pixie::type_id_t pixie::type_id() 
	{ 
	return (type_id_t) &internal::type_id_helper<T>::id; 
	}


template< typename T > pixie::type_id_t pixie::type_id( T const& ) 
	{ 
	return (type_id_t) &internal::type_id_helper<T>::id; 
	}


	
namespace pixie { namespace internal { 

template< typename T > void destroy_instance( void* instance ) 
	{ 
	mempool<T>::item_t* item = (mempool<T>::item_t*) instance;
	item->owner->destroy( &(item->item) );
	}

inline void destroy_count( int* ) { /* do nothing - refcount is stored along with instance */ }

} /* namespace internal */ } /* namespace pixie */


template< typename T >
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create();
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4, p5 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4, p5, p6 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4, p5, p6, p7 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4, p5, p6, p7, p8 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


template< typename T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
pixie::ref<T> pixie::pool_ref( mempool<T>* pool_instance, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 )
	{
	mempool<T>::item_t* item = (mempool<T>::item_t*) pool_instance->create( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
	return refcount::make_ref( &item->item, internal::destroy_instance<T>, &item->ref_count, internal::destroy_count );
	}


#endif /* pixie_impl */


#ifdef PIXIE_IMPLEMENTATION
#undef PIXIE_IMPLEMENTATION

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#define APP_S16 pixie::i16
#define APP_U32 pixie::u32
#define APP_U64 pixie::u64
#define ASSETSYS_U64 pixie::u64
#define AUDIOSYS_S16 pixie::i16
#define AUDIOSYS_U64 pixie::u64
#define CRT_FRAME_U8 pixie::u8
#define CRT_FRAME_U32 pixie::u32
#define CRT_FRAME_U64 pixie::u64
#define CRTEMU_U32 pixie::u32
#define CRTEMU_U64 pixie::u64
#define FRAMETIMER_U64 pixie::u64
#define GAMEPAD_S16 pixie::i16
#define GAMEPAD_U16 pixie::u16
#define GAMEPAD_U8 pixie::u8
#define HANDLES_U64 pixie::u64
#define PALDITHER_U32 pixie::u32
#define PALETTIZE_U8 pixie::u8
#define PALETTIZE_U16 pixie::u16
#define PALETTIZE_U32 pixie::u32
#define PIXELFONT_I8 pixie::i8
#define PIXELFONT_U8 pixie::u8
#define PIXELFONT_U16 pixie::u16
#define PIXELFONT_U32 pixie::u32
#define RANDOM_U32 pixie::u32
#define RANDOM_U64 pixie::u64
#define RESOURCES_U32 pixie::u32
#define THREAD_U64 pixie::u64

// on older MSVC versions, char is same as i8
#if !defined(_MSC_VER) || _MSC_VER >= 1600 
	#define BINARY_RW_CHAR char
#endif
#define BINARY_RW_BOOL bool
#define BINARY_RW_I8 pixie::i8
#define BINARY_RW_I16 pixie::i16
#define BINARY_RW_I32 pixie::i32
#define BINARY_RW_I64 pixie::i64
#define BINARY_RW_U8 pixie::u8
#define BINARY_RW_U16 pixie::u16
#define BINARY_RW_U32 pixie::u32
#define BINARY_RW_U64 pixie::u64
#define BINARY_RW_FLOAT float
#define BINARY_RW_DOUBLE double

#include "app.h"
#include "assetsys.h"
#include "audiosys.h"
#include "binary_rw.h"
#include "crt_frame.h"
#include "crtemu.h"
#include "dir.h"
#include "ease.h"
#include "file.h"
#include "file_util.h"
#include "frametimer.h"
#include "gamepad.h"
#include "gamestate.hpp"
#include "graph.hpp"
#include "handles.h"
#include "hashtable.h"
#include "ini.h"
#include "inputmap.h"
#include "log.h"
#include "math_util.hpp"
#include "paldither.h"
#include "palettize.h"
#include "rnd.h"
#include "strpool_util.hpp"
#include "thread.h"

#define PIXELFONT_COLOR pixie::u8
#define PIXELFONT_FUNC_NAME pixelfont_blit_u8
#include "pixelfont.h"
#undef PIXELFONT_COLOR 
#undef PIXELFONT_FUNC_NAME 

#define PIXELFONT_COLOR pixie::u32
#define PIXELFONT_FUNC_NAME pixelfont_blit_u32
#include "pixelfont.h"
#undef PIXELFONT_COLOR 
#undef PIXELFONT_FUNC_NAME 

#include "dr_wav.h"

#pragma warning( push )
#pragma warning( disable: 4018 ) // 'expression' : signed/unsigned mismatch
#pragma warning( disable: 4244 ) // conversion, possible loss of data
#pragma warning( disable: 4365 ) // conversion, signed/unsigned mismatch
#pragma warning( disable: 4388 ) // signed/unsigned mismatch

#include "jar_mod.h"
bool jar_mod_load( jar_mod_context_t * modctx, void * mod_data, int mod_data_size );

#include "jar_xm.h"

#pragma warning( pop )

#define STB_VORBIS_HEADER_ONLY
#define STB_VORBIS_NO_PUSHDATA_API
#define STB_VORBIS_NO_STDIO
#define STB_VORBIS_NO_INTEGER_CONVERSION
#include "stb_vorbis.h"

#include "stb_image.h"
#include "stb_perlin.h"


#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
	#pragma warning( push )
	#pragma warning( disable: 4548 ) // expression before comma has no effect; expected expression with side-effect
	#include <malloc.h>
	#pragma warning( pop )
#endif

#include <string.h>
#include <time.h>
#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#include <math.h>
#pragma warning( pop )
#include <sys/stat.h>

#ifndef PIXIE_MALLOC
	#include <stdlib.h>
	#define PIXIE_MALLOC( ctx, size ) ( (void) ctx, malloc( size ) )
	#define PIXIE_FREE( ctx, ptr ) ( (void) ctx, free( ptr ) )
#endif

namespace pixie { namespace internal { 

struct memtrack_t
	{
	void* external_ctx;
	u64 current;
	u64 peak;
	int count;
	};

void* tracked_malloc( void* memctx, size_t size, void* ptr );
void* tracked_free( void* memctx, void* ptr );

} /* namespace internal */ } /*namespace pixie */

#define TRACKED_MALLOC( ctx, size ) pixie::internal::tracked_malloc( ctx, size, PIXIE_MALLOC( ( (pixie::internal::memtrack_t*)ctx )->external_ctx, size + sizeof( pixie::u64 ) ) )
#define TRACKED_FREE( ctx, ptr ) PIXIE_FREE( ( (pixie::internal::memtrack_t*)ctx )->external_ctx, pixie::internal::tracked_free( ctx, ptr ) )


//----------
//  helpers
//----------

namespace pixie { namespace internal { 

struct mouse_pointer_t
	{
	u32 pixels[ 256 * 256 ];  
	int width;
	int height;
	int hotspot_x;
	int hotspot_y;
	bool auto_scale;
	bool changed;
	};


struct frame_data_t
	{
	struct
		{
		void* storage;
		size_t capacity;

		int screen_width;
		int screen_height;
		int border_width;
		int border_height;
		int splits_count;
		int cpu_bars_count;

		color_resolution_t color_res;

		char title[ 256 ];
		app_screenmode_t screenmode;

		bool win_pos_changed;
		int win_pos_x;
		int win_pos_y;

		bool win_size_changed;
		int win_w;
		int win_h;

		bool mouse_pos_changed;
		int mouse_set_x;
		int mouse_set_y;

		bool mouse_limit_changed;
		bool mouse_limit_enabled;
		int mouse_limit_x1;
		int mouse_limit_y1;
		int mouse_limit_x2;
		int mouse_limit_y2; 

		bool use_crtmode;
		bool exit_flag;

		mouse_pointer_t mouse_pointer;
		} from_update_thread;

	struct
		{
		void* storage;
		size_t capacity;

		app_input_event_t* input_events;
		int input_events_count;

		int win_pos_x;
		int win_pos_y;

		int win_w;
		int win_h;

		int mouse_x;
		int mouse_y;

		bool exit_flag;
		bool exit_requested;
		} from_app_thread;
	};


enum audio_command_type_t
	{
	AUDIO_COMMAND_TYPE_INVALID,
	AUDIO_COMMAND_TYPE_MASTER_VOLUME,
	AUDIO_COMMAND_TYPE_PAUSE_AUDIO,
	AUDIO_COMMAND_TYPE_RESUME_AUDIO,
	AUDIO_COMMAND_TYPE_PLAY_MUSIC,
	AUDIO_COMMAND_TYPE_STOP_MUSIC,
	AUDIO_COMMAND_TYPE_PAUSE_MUSIC,
	AUDIO_COMMAND_TYPE_RESUME_MUSIC,
	AUDIO_COMMAND_TYPE_SWITCH_MUSIC,
	AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC,
	AUDIO_COMMAND_TYPE_MUSIC_POSITION,
	AUDIO_COMMAND_TYPE_MUSIC_LOOP,
	AUDIO_COMMAND_TYPE_MUSIC_VOLUME,
	AUDIO_COMMAND_TYPE_MUSIC_PAN,
	AUDIO_COMMAND_TYPE_PLAY_AMBIENCE,
	AUDIO_COMMAND_TYPE_STOP_AMBIENCE,
	AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE,
	AUDIO_COMMAND_TYPE_RESUME_AMBIENCE,
	AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE,
	AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE,
	AUDIO_COMMAND_TYPE_AMBIENCE_POSITION,
	AUDIO_COMMAND_TYPE_AMBIENCE_LOOP,
	AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME,
	AUDIO_COMMAND_TYPE_AMBIENCE_PAN,
	AUDIO_COMMAND_TYPE_PLAY_SOUND,
	AUDIO_COMMAND_TYPE_STOP_SOUND,
	AUDIO_COMMAND_TYPE_PAUSE_SOUND,
	AUDIO_COMMAND_TYPE_RESUME_SOUND,
	AUDIO_COMMAND_TYPE_SOUND_POSITION,
	AUDIO_COMMAND_TYPE_SOUND_LOOP,
	AUDIO_COMMAND_TYPE_SOUND_VOLUME,
	AUDIO_COMMAND_TYPE_SOUND_PAN,
	};


struct audio_command_t
	{
	audio_command_type_t type;
	u64 handle;
	union
		{
		struct 
			{
			audio_instance* instance;
			float fade_in_time;
			float delay;
			float priority;
			} play;
		struct 
			{
			audio_instance* instance;
			float fade_in_time;
			float fade_out_time;
			float delay;
			} switch_;
		struct 
			{
			audio_instance* instance;
			float cross_fade_time ;
			float delay;
			} cross_fade;
		float fade_out_time;
		float volume;
		float position;
		bool loop;
		float pan;
		} data;
	};


struct finished_audio_t
	{
	u64 handle;
	audio_instance* instance;
	};

struct audio_position_t
	{
	u64 handle;
	float position;
	};


struct audio_frame_data_t
	{
	struct
		{
		bool exit_flag; // audio thread should exit
		audio_command_t* commands;
		int commands_capacity;
		int commands_count;
		} from_update_thread;

	struct
		{
		bool exit_done; // audio thread have exited
		
		finished_audio_t* finished;
		int finished_capacity;
		int finished_count;

		audio_position_t* positions;
		int positions_capacity;
		int positions_count;
		} from_audio_thread;
	};


void send_audio_command( audio_frame_data_t* data, void* memctx, audio_command_t const* command )
	{
	if( data->from_update_thread.commands_count >= data->from_update_thread.commands_capacity )
		{
		data->from_update_thread.commands_capacity *= 2;
		audio_command_t* new_data = (audio_command_t*) TRACKED_MALLOC( memctx, data->from_update_thread.commands_capacity * sizeof( audio_command_t ) );
		memcpy( new_data, data->from_update_thread.commands, data->from_update_thread.commands_count * sizeof( audio_command_t ) );
		TRACKED_FREE( memctx, data->from_update_thread.commands );
		data->from_update_thread.commands = new_data;
		}
	
	data->from_update_thread.commands[ data->from_update_thread.commands_count++ ] = *command;
	}



template< typename T > void clear( T* t ) { memset( t, 0, sizeof( T ) ); }


void* tracked_malloc( void* memctx, size_t size, void* ptr ) 
	{
	pixie::internal::memtrack_t* memtrack = (pixie::internal::memtrack_t*) memctx;
	++memtrack->count;
	memtrack->current += size;
	memtrack->peak = memtrack->current > memtrack->peak ? memtrack->current : memtrack->peak;   
	u64* p = (u64*) ptr;
	*p = size;
	return p + 1; 
	}
	

void* tracked_free( void* memctx, void* ptr ) 
	{ 
	if( !ptr ) return 0;
	u64* p = ( (u64*) ptr ) - 1;

	pixie::internal::memtrack_t* memtrack = (pixie::internal::memtrack_t*) memctx;
	memtrack->current -= *p;    
	return p;
	}

} /* namespace internal */ } /*namespace pixie */



//-------------
//  pal_screen
//-------------

namespace pixie { namespace internal { 

struct pal_screen
	{
	u8* screen;
	int width;
	int height;

	inline void pset( int x, int y, u8 ink )
		{
		if( x >= 0 && y >= 0 && x < width && y < height )
			screen[ x + y * width ] = ink;
		}

	inline u8 pget( int x, int y )
		{
		if( x >= 0 && y >= 0 && x < width && y < height )
			return screen[ x + y * width ];
		else
			return 0;
		}

	inline void hline( int x, int y, int len, u8 ink )
		{
		if( y < 0 || y >= height ) return;
		if( x < 0 ) { len += x; x = 0; }
		if( x + len > width ) len = width - x;

		u8* scr = screen + y * width + x;
		u8* end = scr + len;
		while( scr < end ) *scr++ = ink;
		}
	};


struct pal_screen_pattern
	{
	u8* screen;
	int width;
	int height;
	u8 fill_pattern[ 64 ];

	void set_fill_pattern( u8 pattern[ 64 ], u8 ink, u8 bg )
		{
		for( int i = 0; i < 64; ++i )
			fill_pattern[ i ] = (u8)( pattern[ i ] * ink + ( 1 - pattern[ i ] ) * bg );
		}

	inline void pset( int x, int y, u8 ink )
		{
		if( x >= 0 && y >= 0 && x < width && y < height )
			screen[ x + y * width ] = ink;
		}

	inline u8 pget( int x, int y )
		{
		if( x >= 0 && y >= 0 && x < width && y < height )
			return screen[ x + y * width ];
		else
			return 0;
		}

	inline void hline( int x, int y, int len, u8 ink )
		{
		(void) ink;
		if( y < 0 || y >= height ) return;
		if( x < 0 ) { len += x; x = 0; }
		if( x + len > width ) len = width - x;
		u8* pattern = fill_pattern + ( y & 7 ) * 8;
		u8* scr = screen + y * width;
		int end = x + len;
		while( x < end ) scr[ x ] = pattern[ ( x++ ) & 7 ];
		}
	};
} /* namespace internal */ } /*namespace pixie */


//------------------
//  key conversions
//------------------

namespace pixie { namespace internal {

app_key_t app_key_from_pixie_key( key_id key )
	{
	int index = (int) key;
	if( key < 0 || key >= KEYCOUNT ) return APP_KEY_INVALID;
	
	int map[ KEYCOUNT * 2 ] = { KEY_INVALID, APP_KEY_INVALID, KEY_LBUTTON, APP_KEY_LBUTTON, KEY_RBUTTON, APP_KEY_RBUTTON, KEY_CANCEL, 
		APP_KEY_CANCEL, KEY_MBUTTON, APP_KEY_MBUTTON, KEY_XBUTTON1, APP_KEY_XBUTTON1, KEY_XBUTTON2, APP_KEY_XBUTTON2, KEY_BACK, 
		APP_KEY_BACK, KEY_TAB, APP_KEY_TAB, KEY_CLEAR, APP_KEY_CLEAR, KEY_RETURN, APP_KEY_RETURN, KEY_SHIFT, APP_KEY_SHIFT, KEY_CONTROL, 
		APP_KEY_CONTROL, KEY_MENU, APP_KEY_MENU, KEY_PAUSE, APP_KEY_PAUSE, KEY_CAPITAL, APP_KEY_CAPITAL, KEY_KANA, APP_KEY_KANA,
		KEY_JUNJA, APP_KEY_JUNJA, KEY_FINAL, APP_KEY_FINAL, KEY_HANJA, APP_KEY_HANJA, KEY_ESCAPE, APP_KEY_ESCAPE, KEY_CONVERT, 
		APP_KEY_CONVERT, KEY_NONCONVERT, APP_KEY_NONCONVERT, KEY_ACCEPT, APP_KEY_ACCEPT, KEY_MODECHANGE, APP_KEY_MODECHANGE, KEY_SPACE, 
		APP_KEY_SPACE, KEY_PRIOR, APP_KEY_PRIOR, KEY_NEXT, APP_KEY_NEXT, KEY_END, APP_KEY_END, KEY_HOME, APP_KEY_HOME, KEY_LEFT, 
		APP_KEY_LEFT, KEY_UP, APP_KEY_UP, KEY_RIGHT, APP_KEY_RIGHT, KEY_DOWN, APP_KEY_DOWN, KEY_SELECT, APP_KEY_SELECT, KEY_PRINT, 
		APP_KEY_PRINT, KEY_EXEC, APP_KEY_EXEC, KEY_SNAPSHOT, APP_KEY_SNAPSHOT, KEY_INSERT, APP_KEY_INSERT, KEY_DELETE, APP_KEY_DELETE,
		KEY_HELP, APP_KEY_HELP, KEY_0, APP_KEY_0, KEY_1, APP_KEY_1, KEY_2, APP_KEY_2, KEY_3, APP_KEY_3, KEY_4, APP_KEY_4, KEY_5, 
		APP_KEY_5, KEY_6, APP_KEY_6, KEY_7, APP_KEY_7, KEY_8, APP_KEY_8, KEY_9, APP_KEY_9, KEY_A, APP_KEY_A, KEY_B, APP_KEY_B, KEY_C, 
		APP_KEY_C, KEY_D, APP_KEY_D, KEY_E, APP_KEY_E, KEY_F, APP_KEY_F, KEY_G, APP_KEY_G, KEY_H, APP_KEY_H, KEY_I, APP_KEY_I, KEY_J, 
		APP_KEY_J, KEY_K, APP_KEY_K, KEY_L, APP_KEY_L, KEY_M, APP_KEY_M, KEY_N, APP_KEY_N, KEY_O, APP_KEY_O, KEY_P, APP_KEY_P, KEY_Q, 
		APP_KEY_Q, KEY_R, APP_KEY_R, KEY_S, APP_KEY_S, KEY_T, APP_KEY_T, KEY_U, APP_KEY_U, KEY_V, APP_KEY_V, KEY_W, APP_KEY_W, KEY_X, 
		APP_KEY_X, KEY_Y, APP_KEY_Y, KEY_Z, APP_KEY_Z, KEY_LWIN, APP_KEY_LWIN, KEY_RWIN, APP_KEY_RWIN, KEY_APPS, APP_KEY_APPS, 
		KEY_SLEEP, APP_KEY_SLEEP, KEY_NUMPAD0, APP_KEY_NUMPAD0, KEY_NUMPAD1, APP_KEY_NUMPAD1, KEY_NUMPAD2, APP_KEY_NUMPAD2, KEY_NUMPAD3, 
		APP_KEY_NUMPAD3, KEY_NUMPAD4, APP_KEY_NUMPAD4, KEY_NUMPAD5, APP_KEY_NUMPAD5, KEY_NUMPAD6, APP_KEY_NUMPAD6, KEY_NUMPAD7, 
		APP_KEY_NUMPAD7, KEY_NUMPAD8, APP_KEY_NUMPAD8, KEY_NUMPAD9, APP_KEY_NUMPAD9, KEY_MULTIPLY, APP_KEY_MULTIPLY, KEY_ADD, 
		APP_KEY_ADD, KEY_SEPARATOR, APP_KEY_SEPARATOR, KEY_SUBTRACT, APP_KEY_SUBTRACT, KEY_DECIMAL, APP_KEY_DECIMAL, KEY_DIVIDE, 
		APP_KEY_DIVIDE, KEY_F1, APP_KEY_F1, KEY_F2, APP_KEY_F2, KEY_F3, APP_KEY_F3, KEY_F4, APP_KEY_F4, KEY_F5, APP_KEY_F5, KEY_F6, 
		APP_KEY_F6, KEY_F7, APP_KEY_F7, KEY_F8, APP_KEY_F8, KEY_F9, APP_KEY_F9, KEY_F10, APP_KEY_F10, KEY_F11, APP_KEY_F11, KEY_F12, 
		APP_KEY_F12, KEY_F13, APP_KEY_F13, KEY_F14, APP_KEY_F14, KEY_F15, APP_KEY_F15, KEY_F16, APP_KEY_F16, KEY_F17, APP_KEY_F17, 
		KEY_F18, APP_KEY_F18, KEY_F19, APP_KEY_F19, KEY_F20, APP_KEY_F20, KEY_F21, APP_KEY_F21, KEY_F22, APP_KEY_F22, KEY_F23, 
		APP_KEY_F23, KEY_F24, APP_KEY_F24, KEY_NUMLOCK, APP_KEY_NUMLOCK, KEY_SCROLL, APP_KEY_SCROLL, KEY_LSHIFT, APP_KEY_LSHIFT, 
		KEY_RSHIFT, APP_KEY_RSHIFT, KEY_LCONTROL, APP_KEY_LCONTROL, KEY_RCONTROL, APP_KEY_RCONTROL, KEY_LMENU, APP_KEY_LMENU, KEY_RMENU, 
		APP_KEY_RMENU, KEY_BROWSER_BACK, APP_KEY_BROWSER_BACK, KEY_BROWSER_FORWARD, APP_KEY_BROWSER_FORWARD, KEY_BROWSER_REFRESH, 
		APP_KEY_BROWSER_REFRESH, KEY_BROWSER_STOP, APP_KEY_BROWSER_STOP, KEY_BROWSER_SEARCH, APP_KEY_BROWSER_SEARCH, 
		KEY_BROWSER_FAVORITES, APP_KEY_BROWSER_FAVORITES, KEY_BROWSER_HOME, APP_KEY_BROWSER_HOME, KEY_VOLUME_MUTE, APP_KEY_VOLUME_MUTE,
		KEY_VOLUME_DOWN, APP_KEY_VOLUME_DOWN, KEY_VOLUME_UP, APP_KEY_VOLUME_UP, KEY_MEDIA_NEXT_TRACK, APP_KEY_MEDIA_NEXT_TRACK, 
		KEY_MEDIA_PREV_TRACK, APP_KEY_MEDIA_PREV_TRACK, KEY_MEDIA_STOP, APP_KEY_MEDIA_STOP, KEY_MEDIA_PLAY_PAUSE, 
		APP_KEY_MEDIA_PLAY_PAUSE, KEY_LAUNCH_MAIL, APP_KEY_LAUNCH_MAIL, KEY_LAUNCH_MEDIA_SELECT, APP_KEY_LAUNCH_MEDIA_SELECT, 
		KEY_LAUNCH_APP1, APP_KEY_LAUNCH_APP1, KEY_LAUNCH_APP2, APP_KEY_LAUNCH_APP2, KEY_OEM_1, APP_KEY_OEM_1, KEY_OEM_PLUS, 
		APP_KEY_OEM_PLUS, KEY_OEM_COMMA, APP_KEY_OEM_COMMA, KEY_OEM_MINUS, APP_KEY_OEM_MINUS, KEY_OEM_PERIOD, APP_KEY_OEM_PERIOD, 
		KEY_OEM_2, APP_KEY_OEM_2, KEY_OEM_3, APP_KEY_OEM_3, KEY_OEM_4, APP_KEY_OEM_4, KEY_OEM_5, APP_KEY_OEM_5, KEY_OEM_6, 
		APP_KEY_OEM_6, KEY_OEM_7, APP_KEY_OEM_7, KEY_OEM_8, APP_KEY_OEM_8, KEY_OEM_102, APP_KEY_OEM_102, KEY_PROCESSKEY, 
		APP_KEY_PROCESSKEY, KEY_ATTN, APP_KEY_ATTN, KEY_CRSEL, APP_KEY_CRSEL, KEY_EXSEL, APP_KEY_EXSEL, KEY_EREOF, APP_KEY_EREOF, 
		KEY_PLAY, APP_KEY_PLAY, KEY_ZOOM, APP_KEY_ZOOM, KEY_NONAME, APP_KEY_NONAME, KEY_PA1, APP_KEY_PA1, KEY_OEM_CLEAR, 
		APP_KEY_OEM_CLEAR, KEY_PEN_TOUCH, APP_KEY_INVALID, KEY_PEN_LOWER_BUTTON, APP_KEY_INVALID, KEY_PEN_UPPER_BUTTON, APP_KEY_INVALID,
		};

	PIXIE_ASSERT( map[ index * 2 ] == key, "Invalid mapping from pixie key to app_key" );
	if( map[ index * 2 ] != key ) return APP_KEY_INVALID;

	return (app_key_t) map[ index * 2 + 1 ];
	}
	

key_id pixie_key_from_app_key( app_key_t key )
	{
	int index = (int) key;
	if( key < 0 || key >= APP_KEYCOUNT ) return KEY_INVALID;
	
	int map[ APP_KEYCOUNT * 2 ] = { 
		APP_KEY_INVALID, KEY_INVALID, APP_KEY_LBUTTON, KEY_LBUTTON, APP_KEY_RBUTTON, KEY_RBUTTON, APP_KEY_CANCEL, KEY_CANCEL, 
		APP_KEY_MBUTTON, KEY_MBUTTON, APP_KEY_XBUTTON1, KEY_XBUTTON1, APP_KEY_XBUTTON2, KEY_XBUTTON2, APP_KEY_BACK, KEY_BACK, 
		APP_KEY_TAB, KEY_TAB, APP_KEY_CLEAR, KEY_CLEAR, APP_KEY_RETURN, KEY_RETURN, APP_KEY_SHIFT, KEY_SHIFT, APP_KEY_CONTROL, 
		KEY_CONTROL, APP_KEY_MENU, KEY_MENU, APP_KEY_PAUSE, KEY_PAUSE, APP_KEY_CAPITAL, KEY_CAPITAL, APP_KEY_KANA, KEY_KANA, 
		APP_KEY_JUNJA, KEY_JUNJA, APP_KEY_FINAL, KEY_FINAL, APP_KEY_HANJA, KEY_HANJA, APP_KEY_ESCAPE, KEY_ESCAPE, APP_KEY_CONVERT, 
		KEY_CONVERT, APP_KEY_NONCONVERT, KEY_NONCONVERT, APP_KEY_ACCEPT, KEY_ACCEPT, APP_KEY_MODECHANGE, KEY_MODECHANGE, APP_KEY_SPACE, 
		KEY_SPACE, APP_KEY_PRIOR, KEY_PRIOR, APP_KEY_NEXT, KEY_NEXT, APP_KEY_END, KEY_END, APP_KEY_HOME, KEY_HOME, APP_KEY_LEFT, 
		KEY_LEFT, APP_KEY_UP, KEY_UP, APP_KEY_RIGHT, KEY_RIGHT, APP_KEY_DOWN, KEY_DOWN, APP_KEY_SELECT, KEY_SELECT, APP_KEY_PRINT, 
		KEY_PRINT, APP_KEY_EXEC, KEY_EXEC, APP_KEY_SNAPSHOT, KEY_SNAPSHOT, APP_KEY_INSERT, KEY_INSERT,
		APP_KEY_DELETE, KEY_DELETE, APP_KEY_HELP, KEY_HELP, APP_KEY_0, KEY_0, APP_KEY_1, KEY_1, APP_KEY_2, KEY_2, APP_KEY_3, KEY_3, 
		APP_KEY_4, KEY_4, APP_KEY_5, KEY_5, APP_KEY_6, KEY_6, APP_KEY_7, KEY_7, APP_KEY_8, KEY_8, APP_KEY_9, KEY_9, APP_KEY_A, KEY_A, 
		APP_KEY_B, KEY_B, APP_KEY_C, KEY_C, APP_KEY_D, KEY_D, APP_KEY_E, KEY_E, APP_KEY_F, KEY_F, APP_KEY_G, KEY_G, APP_KEY_H, KEY_H,
		APP_KEY_I, KEY_I, APP_KEY_J, KEY_J, APP_KEY_K, KEY_K, APP_KEY_L, KEY_L, APP_KEY_M, KEY_M, APP_KEY_N, KEY_N, APP_KEY_O, KEY_O,
		APP_KEY_P, KEY_P, APP_KEY_Q, KEY_Q, APP_KEY_R, KEY_R, APP_KEY_S, KEY_S, APP_KEY_T, KEY_T, APP_KEY_U, KEY_U, APP_KEY_V, KEY_V,
		APP_KEY_W, KEY_W, APP_KEY_X, KEY_X, APP_KEY_Y, KEY_Y, APP_KEY_Z, KEY_Z, APP_KEY_LWIN, KEY_LWIN, APP_KEY_RWIN, KEY_RWIN, 
		APP_KEY_APPS, KEY_APPS, APP_KEY_SLEEP, KEY_SLEEP, APP_KEY_NUMPAD0, KEY_NUMPAD0, APP_KEY_NUMPAD1, KEY_NUMPAD1, APP_KEY_NUMPAD2, 
		KEY_NUMPAD2, APP_KEY_NUMPAD3, KEY_NUMPAD3, APP_KEY_NUMPAD4, KEY_NUMPAD4, APP_KEY_NUMPAD5, KEY_NUMPAD5, APP_KEY_NUMPAD6, 
		KEY_NUMPAD6, APP_KEY_NUMPAD7, KEY_NUMPAD7, APP_KEY_NUMPAD8, KEY_NUMPAD8, APP_KEY_NUMPAD9, KEY_NUMPAD9, APP_KEY_MULTIPLY, 
		KEY_MULTIPLY, APP_KEY_ADD, KEY_ADD, APP_KEY_SEPARATOR, KEY_SEPARATOR, APP_KEY_SUBTRACT, KEY_SUBTRACT, APP_KEY_DECIMAL, 
		KEY_DECIMAL, APP_KEY_DIVIDE, KEY_DIVIDE, APP_KEY_F1, KEY_F1, APP_KEY_F2, KEY_F2, APP_KEY_F3, KEY_F3, APP_KEY_F4, KEY_F4, 
		APP_KEY_F5, KEY_F5, APP_KEY_F6, KEY_F6, APP_KEY_F7, KEY_F7, APP_KEY_F8, KEY_F8, APP_KEY_F9, KEY_F9, APP_KEY_F10, KEY_F10, 
		APP_KEY_F11, KEY_F11, APP_KEY_F12, KEY_F12, APP_KEY_F13, KEY_F13, APP_KEY_F14, KEY_F14, APP_KEY_F15, KEY_F15, APP_KEY_F16, 
		KEY_F16, APP_KEY_F17, KEY_F17, APP_KEY_F18, KEY_F18, APP_KEY_F19, KEY_F19, APP_KEY_F20, KEY_F20, APP_KEY_F21, KEY_F21, 
		APP_KEY_F22, KEY_F22, APP_KEY_F23, KEY_F23, APP_KEY_F24, KEY_F24, APP_KEY_NUMLOCK, KEY_NUMLOCK, APP_KEY_SCROLL, KEY_SCROLL,
		APP_KEY_LSHIFT, KEY_LSHIFT, APP_KEY_RSHIFT, KEY_RSHIFT, APP_KEY_LCONTROL, KEY_LCONTROL, APP_KEY_RCONTROL, KEY_RCONTROL,
		APP_KEY_LMENU, KEY_LMENU, APP_KEY_RMENU, KEY_RMENU, APP_KEY_BROWSER_BACK, KEY_BROWSER_BACK, APP_KEY_BROWSER_FORWARD, 
		KEY_BROWSER_FORWARD, APP_KEY_BROWSER_REFRESH, KEY_BROWSER_REFRESH, APP_KEY_BROWSER_STOP, KEY_BROWSER_STOP, 
		APP_KEY_BROWSER_SEARCH, KEY_BROWSER_SEARCH, APP_KEY_BROWSER_FAVORITES, KEY_BROWSER_FAVORITES, APP_KEY_BROWSER_HOME, 
		KEY_BROWSER_HOME, APP_KEY_VOLUME_MUTE, KEY_VOLUME_MUTE, APP_KEY_VOLUME_DOWN, KEY_VOLUME_DOWN, APP_KEY_VOLUME_UP, KEY_VOLUME_UP, 
		APP_KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_NEXT_TRACK, APP_KEY_MEDIA_PREV_TRACK, KEY_MEDIA_PREV_TRACK, APP_KEY_MEDIA_STOP, 
		KEY_MEDIA_STOP, APP_KEY_MEDIA_PLAY_PAUSE, KEY_MEDIA_PLAY_PAUSE, APP_KEY_LAUNCH_MAIL, KEY_LAUNCH_MAIL, 
		APP_KEY_LAUNCH_MEDIA_SELECT, KEY_LAUNCH_MEDIA_SELECT, APP_KEY_LAUNCH_APP1, KEY_LAUNCH_APP1, APP_KEY_LAUNCH_APP2, 
		KEY_LAUNCH_APP2, APP_KEY_OEM_1, KEY_OEM_1, APP_KEY_OEM_PLUS, KEY_OEM_PLUS, APP_KEY_OEM_COMMA, KEY_OEM_COMMA, APP_KEY_OEM_MINUS, 
		KEY_OEM_MINUS, APP_KEY_OEM_PERIOD, KEY_OEM_PERIOD, APP_KEY_OEM_2, KEY_OEM_2, APP_KEY_OEM_3, KEY_OEM_3, APP_KEY_OEM_4, KEY_OEM_4,
		APP_KEY_OEM_5, KEY_OEM_5, APP_KEY_OEM_6, KEY_OEM_6, APP_KEY_OEM_7, KEY_OEM_7, APP_KEY_OEM_8, KEY_OEM_8, APP_KEY_OEM_102, 
		KEY_OEM_102, APP_KEY_PROCESSKEY, KEY_PROCESSKEY, APP_KEY_ATTN, KEY_ATTN, APP_KEY_CRSEL, KEY_CRSEL, APP_KEY_EXSEL, KEY_EXSEL,
		APP_KEY_EREOF, KEY_EREOF, APP_KEY_PLAY, KEY_PLAY, APP_KEY_ZOOM, KEY_ZOOM, APP_KEY_NONAME, KEY_NONAME, APP_KEY_PA1, KEY_PA1, 
		APP_KEY_OEM_CLEAR, KEY_OEM_CLEAR, };

	PIXIE_ASSERT( map[ index * 2 ] == key, "Invalid mapping from app_key to pixie key" );
	if( map[ index * 2 ] != key ) return KEY_INVALID;

	return (key_id) map[ index * 2 + 1 ];
	}


inputmap_key_t inputmap_key_from_pixie_key( key_id key )
	{
	int index = (int) key;
	if( key < 0 || key >= KEYCOUNT ) return INPUTMAP_KEY_INVALID;
	
	int map[ KEYCOUNT * 2 ] = { KEY_INVALID, INPUTMAP_KEY_INVALID, KEY_LBUTTON, INPUTMAP_KEY_LBUTTON, KEY_RBUTTON, INPUTMAP_KEY_RBUTTON,
		KEY_CANCEL, INPUTMAP_KEY_CANCEL, KEY_MBUTTON, INPUTMAP_KEY_MBUTTON, KEY_XBUTTON1, INPUTMAP_KEY_XBUTTON1, KEY_XBUTTON2, 
		INPUTMAP_KEY_XBUTTON2, KEY_BACK, INPUTMAP_KEY_BACK, KEY_TAB, INPUTMAP_KEY_TAB, KEY_CLEAR, INPUTMAP_KEY_CLEAR, KEY_RETURN, 
		INPUTMAP_KEY_RETURN, KEY_SHIFT, INPUTMAP_KEY_SHIFT, KEY_CONTROL, INPUTMAP_KEY_CONTROL, KEY_MENU, INPUTMAP_KEY_MENU, KEY_PAUSE, 
		INPUTMAP_KEY_PAUSE, KEY_CAPITAL, INPUTMAP_KEY_CAPITAL, KEY_KANA, INPUTMAP_KEY_KANA, KEY_JUNJA, INPUTMAP_KEY_JUNJA, KEY_FINAL, 
		INPUTMAP_KEY_FINAL, KEY_HANJA, INPUTMAP_KEY_HANJA, KEY_ESCAPE, INPUTMAP_KEY_ESCAPE, KEY_CONVERT, INPUTMAP_KEY_CONVERT, 
		KEY_NONCONVERT, INPUTMAP_KEY_NONCONVERT, KEY_ACCEPT, INPUTMAP_KEY_ACCEPT, KEY_MODECHANGE, INPUTMAP_KEY_MODECHANGE, KEY_SPACE, 
		INPUTMAP_KEY_SPACE, KEY_PRIOR, INPUTMAP_KEY_PRIOR, KEY_NEXT, INPUTMAP_KEY_NEXT, KEY_END, INPUTMAP_KEY_END, KEY_HOME, 
		INPUTMAP_KEY_HOME, KEY_LEFT, INPUTMAP_KEY_LEFT, KEY_UP, INPUTMAP_KEY_UP, KEY_RIGHT, INPUTMAP_KEY_RIGHT, KEY_DOWN, 
		INPUTMAP_KEY_DOWN, KEY_SELECT, INPUTMAP_KEY_SELECT, KEY_PRINT, INPUTMAP_KEY_PRINT, KEY_EXEC, INPUTMAP_KEY_EXEC, KEY_SNAPSHOT, 
		INPUTMAP_KEY_SNAPSHOT, KEY_INSERT, INPUTMAP_KEY_INSERT, KEY_DELETE, INPUTMAP_KEY_DELETE, KEY_HELP, INPUTMAP_KEY_HELP, KEY_0, 
		INPUTMAP_KEY_0, KEY_1, INPUTMAP_KEY_1, KEY_2, INPUTMAP_KEY_2, KEY_3, INPUTMAP_KEY_3, KEY_4, INPUTMAP_KEY_4, KEY_5, 
		INPUTMAP_KEY_5, KEY_6, INPUTMAP_KEY_6, KEY_7, INPUTMAP_KEY_7, KEY_8, INPUTMAP_KEY_8, KEY_9, INPUTMAP_KEY_9, KEY_A, 
		INPUTMAP_KEY_A, KEY_B, INPUTMAP_KEY_B, KEY_C, INPUTMAP_KEY_C, KEY_D, INPUTMAP_KEY_D, KEY_E, INPUTMAP_KEY_E, KEY_F, 
		INPUTMAP_KEY_F, KEY_G, INPUTMAP_KEY_G, KEY_H, INPUTMAP_KEY_H, KEY_I, INPUTMAP_KEY_I, KEY_J, INPUTMAP_KEY_J, KEY_K, 
		INPUTMAP_KEY_K, KEY_L, INPUTMAP_KEY_L, KEY_M, INPUTMAP_KEY_M, KEY_N, INPUTMAP_KEY_N, KEY_O, INPUTMAP_KEY_O, KEY_P, 
		INPUTMAP_KEY_P, KEY_Q, INPUTMAP_KEY_Q, KEY_R, INPUTMAP_KEY_R, KEY_S, INPUTMAP_KEY_S, KEY_T, INPUTMAP_KEY_T, KEY_U, 
		INPUTMAP_KEY_U, KEY_V, INPUTMAP_KEY_V, KEY_W, INPUTMAP_KEY_W, KEY_X, INPUTMAP_KEY_X, KEY_Y, INPUTMAP_KEY_Y, KEY_Z, 
		INPUTMAP_KEY_Z, KEY_LWIN, INPUTMAP_KEY_LWIN, KEY_RWIN, INPUTMAP_KEY_RWIN, KEY_APPS, INPUTMAP_KEY_APPS, KEY_SLEEP, 
		INPUTMAP_KEY_SLEEP, KEY_NUMPAD0, INPUTMAP_KEY_NUMPAD0, KEY_NUMPAD1, INPUTMAP_KEY_NUMPAD1, KEY_NUMPAD2, INPUTMAP_KEY_NUMPAD2, 
		KEY_NUMPAD3, INPUTMAP_KEY_NUMPAD3, KEY_NUMPAD4, INPUTMAP_KEY_NUMPAD4, KEY_NUMPAD5, INPUTMAP_KEY_NUMPAD5, KEY_NUMPAD6, 
		INPUTMAP_KEY_NUMPAD6, KEY_NUMPAD7, INPUTMAP_KEY_NUMPAD7, KEY_NUMPAD8, INPUTMAP_KEY_NUMPAD8, KEY_NUMPAD9, INPUTMAP_KEY_NUMPAD9,
		KEY_MULTIPLY, INPUTMAP_KEY_MULTIPLY, KEY_ADD, INPUTMAP_KEY_ADD, KEY_SEPARATOR, INPUTMAP_KEY_SEPARATOR, KEY_SUBTRACT, 
		INPUTMAP_KEY_SUBTRACT, KEY_DECIMAL, INPUTMAP_KEY_DECIMAL, KEY_DIVIDE, INPUTMAP_KEY_DIVIDE, KEY_F1, INPUTMAP_KEY_F1, KEY_F2, 
		INPUTMAP_KEY_F2, KEY_F3, INPUTMAP_KEY_F3, KEY_F4, INPUTMAP_KEY_F4, KEY_F5, INPUTMAP_KEY_F5, KEY_F6, INPUTMAP_KEY_F6, KEY_F7, 
		INPUTMAP_KEY_F7, KEY_F8, INPUTMAP_KEY_F8, KEY_F9, INPUTMAP_KEY_F9, KEY_F10, INPUTMAP_KEY_F10, KEY_F11, INPUTMAP_KEY_F11, 
		KEY_F12, INPUTMAP_KEY_F12, KEY_F13, INPUTMAP_KEY_F13, KEY_F14, INPUTMAP_KEY_F14, KEY_F15, INPUTMAP_KEY_F15, KEY_F16, 
		INPUTMAP_KEY_F16, KEY_F17, INPUTMAP_KEY_F17, KEY_F18, INPUTMAP_KEY_F18, KEY_F19, INPUTMAP_KEY_F19, KEY_F20, INPUTMAP_KEY_F20,       
		KEY_F21, INPUTMAP_KEY_F21, KEY_F22, INPUTMAP_KEY_F22, KEY_F23, INPUTMAP_KEY_F23, KEY_F24, INPUTMAP_KEY_F24, KEY_NUMLOCK, 
		INPUTMAP_KEY_NUMLOCK, KEY_SCROLL, INPUTMAP_KEY_SCROLL, KEY_LSHIFT, INPUTMAP_KEY_LSHIFT, KEY_RSHIFT, INPUTMAP_KEY_RSHIFT, 
		KEY_LCONTROL, INPUTMAP_KEY_LCONTROL, KEY_RCONTROL, INPUTMAP_KEY_RCONTROL, KEY_LMENU, INPUTMAP_KEY_LMENU, KEY_RMENU, 
		INPUTMAP_KEY_RMENU, KEY_BROWSER_BACK, INPUTMAP_KEY_BROWSER_BACK, KEY_BROWSER_FORWARD, INPUTMAP_KEY_BROWSER_FORWARD, 
		KEY_BROWSER_REFRESH, INPUTMAP_KEY_BROWSER_REFRESH, KEY_BROWSER_STOP, INPUTMAP_KEY_BROWSER_STOP, KEY_BROWSER_SEARCH, 
		INPUTMAP_KEY_BROWSER_SEARCH, KEY_BROWSER_FAVORITES, INPUTMAP_KEY_BROWSER_FAVORITES, KEY_BROWSER_HOME, 
		INPUTMAP_KEY_BROWSER_HOME, KEY_VOLUME_MUTE, INPUTMAP_KEY_VOLUME_MUTE, KEY_VOLUME_DOWN, INPUTMAP_KEY_VOLUME_DOWN, KEY_VOLUME_UP, 
		INPUTMAP_KEY_VOLUME_UP, KEY_MEDIA_NEXT_TRACK, INPUTMAP_KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_PREV_TRACK, 
		INPUTMAP_KEY_MEDIA_PREV_TRACK, KEY_MEDIA_STOP, INPUTMAP_KEY_MEDIA_STOP, KEY_MEDIA_PLAY_PAUSE, INPUTMAP_KEY_MEDIA_PLAY_PAUSE, 
		KEY_LAUNCH_MAIL, INPUTMAP_KEY_LAUNCH_MAIL, KEY_LAUNCH_MEDIA_SELECT, INPUTMAP_KEY_LAUNCH_MEDIA_SELECT, KEY_LAUNCH_APP1, 
		INPUTMAP_KEY_LAUNCH_APP1, KEY_LAUNCH_APP2, INPUTMAP_KEY_LAUNCH_APP2, KEY_OEM_1, INPUTMAP_KEY_OEM_1, KEY_OEM_PLUS, 
		INPUTMAP_KEY_OEM_PLUS, KEY_OEM_COMMA, INPUTMAP_KEY_OEM_COMMA, KEY_OEM_MINUS, INPUTMAP_KEY_OEM_MINUS, KEY_OEM_PERIOD, 
		INPUTMAP_KEY_OEM_PERIOD, KEY_OEM_2, INPUTMAP_KEY_OEM_2, KEY_OEM_3, INPUTMAP_KEY_OEM_3, KEY_OEM_4, INPUTMAP_KEY_OEM_4, KEY_OEM_5, 
		INPUTMAP_KEY_OEM_5, KEY_OEM_6, INPUTMAP_KEY_OEM_6, KEY_OEM_7, INPUTMAP_KEY_OEM_7, KEY_OEM_8, INPUTMAP_KEY_OEM_8, KEY_OEM_102, 
		INPUTMAP_KEY_OEM_102, KEY_PROCESSKEY, INPUTMAP_KEY_PROCESSKEY, KEY_ATTN, INPUTMAP_KEY_ATTN, KEY_CRSEL, INPUTMAP_KEY_CRSEL, 
		KEY_EXSEL, INPUTMAP_KEY_EXSEL, KEY_EREOF, INPUTMAP_KEY_EREOF, KEY_PLAY, INPUTMAP_KEY_PLAY, KEY_ZOOM, INPUTMAP_KEY_ZOOM, 
		KEY_NONAME, INPUTMAP_KEY_NONAME, KEY_PA1, INPUTMAP_KEY_PA1, KEY_OEM_CLEAR, INPUTMAP_KEY_OEM_CLEAR, KEY_PEN_TOUCH, 
		INPUTMAP_KEY_INVALID, KEY_PEN_LOWER_BUTTON, INPUTMAP_KEY_INVALID, KEY_PEN_UPPER_BUTTON, INPUTMAP_KEY_INVALID, };

	PIXIE_ASSERT( map[ index * 2 ] == key, "Invalid mapping from pixie key to inputmap_key" );
	if( map[ index * 2 ] != key ) return INPUTMAP_KEY_INVALID;

	return (inputmap_key_t) map[ index * 2 + 1 ];    }

} /* namespace internal */ } /* namespace pixie */


//--------------
//  internals_t
//--------------

namespace pixie { namespace internal {

audio_instance* audioformat_samples( void* data, size_t size );
audio_instance* audioformat_ogg( void* data, size_t size );
audio_instance* audioformat_wav( void* data, size_t size );
audio_instance* audioformat_mod( void* data, size_t size );
audio_instance* audioformat_xm( void* data, size_t size );

static thread_atomic_ptr_t internals_tls;
void internals_init( internal::internals_t* internals, void* memctx );
void internals_term( internal::internals_t* internals );
void resize_screen();
void add_sprite_manager( sprite_manager* manager, void (sprite_manager::*render_func)(), void (sprite_manager::*update_func)() );
void remove_sprite_manager( sprite_manager* manager );
extern u32 default_palette[ 256 ];

struct time_event_t { event_handler* handler; float seconds; float repeat; string_id event_id; void* user_data; };
struct key_event_t { event_handler* handler; key_id key; string_id event_id; void* user_data; };
struct ascii_event_t { event_handler* handler; char ascii; string_id event_id; void* user_data; };
struct action_event_t { event_handler* handler; string_id action; bool using_threshold; float threshold; string_id event_id; void* user_data; };
struct gamepadbutton_event_t { event_handler* handler; int pad_index; gamepadbutton_id button; string_id event_id; void* user_data; };
struct gamepadaxis_event_t { event_handler* handler; int pad_index; gamepadaxis_id axis; float threshold; string_id event_id; void* user_data; };


void update_color_indices( int start, rgb* colors, int count );

struct pinned_resource
	{
	pinned_resource() : type( 0 ), copy( 0 ), destroy( 0 ) { }
	~pinned_resource() { if( destroy ) destroy( instance ); } 
	pinned_resource( pinned_resource const& other ) 
		{ 
		if( destroy ) destroy( instance ); 
		type = other.type;
		copy = other.copy;
		destroy = other.destroy;
		if( other.copy ) other.copy( instance, other.instance );
		group = other.group;
		} 

	pinned_resource( type_id_t type_, void (*copy_)( void*, void const* ), void (*destroy_)( void* ), void const* instance_, string_id group_ ):
		type( type_ ), copy( copy_ ), destroy( destroy_ ), group( group_ )
		{
		if( copy ) copy( instance, instance_ );
		}

	type_id_t type;
	void (*copy)( void*, void const* );
	void (*destroy)( void* );
	u8 instance[ sizeof( resource<void> ) ];
	string_id group;
	};

struct bitmap_and_refcount
	{
	u8 bmp[ sizeof( bitmap ) ];
	int count;
	};


struct ref_size
	{
	u8 storage[ sizeof( ref<void> ) ];
	};

struct small_ref_inst_size
	{
	u8 storage[ 128 ];
	};
	

void init_default_mouse_pointer( mouse_pointer_t* mouse_pointer )
	{

	#define I 0xFFFFFFFF
	#define B 0xFF000000
	#define T 0x00000000

	u32 default_mouse_pointer_data[ 11 * 16 ] = 
		{
		B,B,T,T,T,T,T,T,T,T,T,
		B,I,B,T,T,T,T,T,T,T,T,
		B,I,I,B,T,T,T,T,T,T,T,
		B,I,I,I,B,T,T,T,T,T,T,
		B,I,I,I,I,B,T,T,T,T,T,
		B,I,I,I,I,I,B,T,T,T,T,
		B,I,I,I,I,I,I,B,T,T,T,
		B,I,I,I,I,I,I,I,B,T,T,
		B,I,I,I,I,I,I,I,I,B,T,
		B,I,I,I,I,I,B,B,B,B,B,
		B,I,I,B,I,I,B,T,T,T,T,
		B,I,B,T,B,I,I,B,T,T,T,
		B,B,T,T,B,I,I,B,T,T,T,
		B,T,T,T,T,B,I,I,B,T,T,
		T,T,T,T,T,B,I,I,B,T,T,
		T,T,T,T,T,T,B,B,B,T,T,
		};
	#undef T
	#undef B
	#undef I
	
	memcpy( mouse_pointer->pixels, default_mouse_pointer_data, sizeof( u32 ) * 11 * 16 );
	mouse_pointer->width = 11;
	mouse_pointer->height = 16;
	mouse_pointer->hotspot_x = 0;
	mouse_pointer->hotspot_y = 0;
	mouse_pointer->auto_scale = true;
	mouse_pointer->changed = false;
	}


struct sound_instance
	{
	u64 handle;
	bool loop;
	float position;
	float volume;
	float pan;
	resource<audio> audio_resource;
	};

struct update_thread_data_t;

} /* namespace internal */ } /* namespace pixie */


struct pixie::internal::internals_t final    
	{
	internals_t( void* memctx, frame_data_t* frame_data, audio_frame_data_t* audio_frame_data, update_thread_data_t* update_thread_data, app_displays_t app_displays );
	~internals_t();
	
	void* memctx;
	log_t* log;
	char* log_buffer;
	size_t log_capacity;
	bool exit_flag;
	int return_value;
	float delta_time;
	int frame_count;

	strpool::internal::string_pool string_pool;
	strpool::internal::string_pool string_id_pool;

	array<display> displays;

	char title[ 256 ];
	app_screenmode_t screenmode;

	int win_pos_x;
	int win_pos_y;

	int win_w;
	int win_h;

	bool mouse_limit_enabled;
	int mouse_limit_x1;
	int mouse_limit_y1;
	int mouse_limit_x2;
	int mouse_limit_y2; 


	mempool<audio> pool_audio;
	mempool<font> pool_font;
	mempool<bitmap_and_refcount> pool_bitmap_and_refcount;
	mempool<ref_size> pool_ref;
	mempool<small_ref_inst_size> pool_small_ref_inst;

	struct cpu_bar_t
		{
		APP_U64 counter;
		rgb color;
		bool enabled;
		};

	array<cpu_bar_t> cpu_bars;
	bool cpu_bars_enabled;

	bool use_crtmode;

	void* screen_storage;
	size_t screen_capacity;

	bitmap screen_bitmap;
	bitmap::internal_t::normal_cel screen_bitmap_cels;
	u8* screen_pixels;
	int screen_width;
	int screen_height;
	int border_width;
	int border_height;

	fill_pattern fill_style_pattern;
	int fill_style_bgcolor;

	int mouse_x;
	int mouse_y;
	int pen_x;
	int pen_y;
	float pen_pressure;
	bool key_states[ KEYCOUNT ];
	bool previous_key_states[ KEYCOUNT ];

	gamepad_t* gamepad;
	struct
		{
		gamepad_result_t result;
		gamepad_state_t state;
		gamepad_state_t previous_state;
		} gamepad_data[ 4 ];
	

	mouse_pointer_t mouse_pointer;

	color_resolution_t color_res;

	rgb palette[ 256 ];
	
	struct palette_split_t
		{
		int ypos;
		rgb palette[ 256 ];
		};
	array<palette_split_t> palette_splits;

	int brightest_color;
	int darkest_color;


	assetsys_t* assetsys;

	dictionary<string, int /*, dictionary_ns::no_hash*/> resource_filenames;       
	bool resources_mounted;
	resources::resource_system resource_sys;

	array<audio_format_t> audio_formats;

	float master_volume;
	u64 next_audio_handle;
	
	u64 current_music_handle;
	bool music_loop;
	float music_volume;
	float music_pan;
	u64 current_ambience_handle;    
	bool ambience_loop;
	float ambience_volume;
	float ambience_pan;
	dictionary<u64, sound_instance> current_sounds;

	struct sprite_manager_entry_t { sprite_manager* manager; void (sprite_manager::*render_func)(); void (sprite_manager::*update_func)(); };
	pod_array<sprite_manager_entry_t> sprite_managers;
	
	gamestate::game_state_system<> game_states;
	rnd_pcg_t rng_instance;
	tween_ns::tween_system tween_system;
	float tween_scale;
	objrepo::object_repo systems;

	sprite_manager default_sprite_manager;
	inputmap_t* inputmap;

	int next_action_index;
	dictionary<string, int> action_to_index;
	
	array<time_event_t> time_events;
	array<key_event_t> key_pressed_events;
	array<key_event_t> key_released_events;
	array<ascii_event_t> ascii_events;
	array<action_event_t> action_events;
	array<gamepadbutton_event_t> gamepad_pressed_events;
	array<gamepadbutton_event_t> gamepad_released_events;
	array<gamepadaxis_event_t> gamepad_axis_events;

	array<pinned_resource,1024> pinned_resources;

	bool exit_requested;

	update_thread_data_t* update_thread_data;
	frame_data_t* frame_data;
	audio_frame_data_t* audio_frame_data;
	};


pixie::internal::internals_t::internals_t( void* memctx_, frame_data_t* frame_data_, audio_frame_data_t* audio_frame_data_, update_thread_data_t* update_thread_data_, app_displays_t app_displays ) :
	memctx( memctx_ ),
	update_thread_data( update_thread_data_ ),
	frame_data( frame_data_ ),
	audio_frame_data( audio_frame_data_ ),
	game_states( memctx_ ),
	systems( memctx_ ),
	string_pool( true, memctx_ ),
	string_id_pool( false, memctx_ ),
	fill_style_pattern( FILL_PATTERN_SOLID ),
	fill_style_bgcolor( 0 ),
	use_crtmode( false ),
	exit_flag( false ),
	color_res( COLOR_RESOLUTION_RGB24 ),
	cpu_bars_enabled( true ),
	resource_sys( memctx_ ),
	tween_system( memctx_ ),
	screenmode( APP_SCREENMODE_FULLSCREEN ),
	tween_scale( 1.0f ),
	next_audio_handle( 0 ),
	master_volume( 1.0f ),
	music_volume( 1.0f ),
	ambience_volume( 1.0f ),
	pool_audio( 256, memctx_ ),
	pool_font( 256, memctx_ ),
	pool_bitmap_and_refcount( 256, memctx_ ),
	pool_ref( 256, memctx_ ),
	pool_small_ref_inst( 256, memctx_ )
	{ 
	screen_capacity = 1024 * 1024;
	screen_storage = TRACKED_MALLOC( memctx, screen_capacity );
	memset( screen_storage, 0, screen_capacity );

	for( int i = 0; i < app_displays.count; ++i )
		{
		display disp;
		disp.id = app_displays.displays[ i ].id;
		disp.x = app_displays.displays[ i ].x;
		disp.y = app_displays.displays[ i ].y;
		disp.width = app_displays.displays[ i ].width;
		disp.height = app_displays.displays[ i ].height;
		displays.add( disp );
		}

	for( int i = 0; i < 256; ++i )
		{
		palette[ i ].b = (u8)( default_palette[ i ] & 0xff );
		palette[ i ].g = (u8)( ( default_palette[ i ] >> 8 ) & 0xff );
		palette[ i ].r = (u8)( ( default_palette[ i ] >> 16 ) & 0xff );
		}
	brightest_color = 255;
	darkest_color = 0;
	update_color_indices( 0, palette, 256 );

	register_audio_format( internal::audioformat_ogg );
	register_audio_format( internal::audioformat_wav );
	register_audio_format( internal::audioformat_mod );
	register_audio_format( internal::audioformat_xm );

	rnd_pcg_seed( &rng_instance, 0 );

	assetsys = assetsys_create( memctx );
	
	resources_mounted = false;

	border_width = 32;
	border_height = 44;
	screen_size( 320, 200 );

	gamepad = gamepad_create( memctx );
	inputmap = inputmap_create( memctx );
	
	strcpy( title, "Pixie" );

	init_default_mouse_pointer( &mouse_pointer );
	}


pixie::internal::internals_t::~internals_t() 
	{ 
	PIXIE_ASSERT( current_sounds.count() == 0, "Sound cleanup not finished" );

	game_states.pop( -1 );
	game_states.update( 0.0f );
	tween_system.stop_all();    

	pinned_resources.clear();
	gamepad_destroy( gamepad );
	inputmap_destroy( inputmap );
	assetsys_destroy( assetsys );

	TRACKED_FREE( memctx, screen_storage );
	}
	

pixie::internal::internals_t* pixie::internal::internals()
	{
	thread_tls_t tls = thread_atomic_ptr_load( &internals_tls );
	PIXIE_ASSERT( tls, "Attempt to call a Pixie function from outside a pixie::run block." );
	void* ptr = thread_tls_get( tls );
	PIXIE_ASSERT( ptr, "Attempt to call a Pixie function from a thread which it is not running on." );
	return (internals_t*) ptr;
	}
	


//-----------
//  app_proc
//-----------

namespace pixie { namespace internal {

int lookup_action_index( string_id const& action );

void process_input( internals_t* internals, app_input_event_t* input_events, int input_events_count )
	{
	PIXIE_ASSERT( sizeof( internals->key_states ) / sizeof( *internals->key_states ) == sizeof( internals->previous_key_states ) / sizeof( *internals->previous_key_states ), "Key states size mismatch" );
	for( int i = 0; i < sizeof( internals->key_states ) / sizeof( *internals->key_states ); ++i )
		internals->previous_key_states[ i ] = internals->key_states[ i ];

	inputmap_update_begin( internals->inputmap );
	for( int i = 0; i < input_events_count; ++i )
		{
		app_input_event_t* event = &input_events[ i ];
		switch( event->type )
			{
			case APP_INPUT_KEY_DOWN:
				{
				key_id key = pixie_key_from_app_key( event->data.key );
				if( key >= 0 && key < sizeof( internals->key_states ) / sizeof( *internals->key_states ) )
					internals->key_states[ key ] = true;                          
				inputmap_update_keydown( internals->inputmap, inputmap_key_from_pixie_key( key ) );
				} break;
			case APP_INPUT_KEY_UP:
				{
				key_id key = pixie_key_from_app_key( event->data.key );
				if( key >= 0 && key < sizeof( internals->key_states ) / sizeof( *internals->key_states ) )
					internals->key_states[ key ] = false;                          
				inputmap_update_keyup( internals->inputmap, inputmap_key_from_pixie_key( key ) );
				} break;
			case APP_INPUT_CHAR:
				{
				for( int j = 0; j < internals->ascii_events.count(); ++j )
					{
					ascii_event_t* ascii_event = &internals->ascii_events[ j ];
					if( ascii_event->ascii == event->data.char_code )
						ascii_event->handler->on_event( ascii_event->event_id, ascii_event->user_data );
					}
				} break;
			case APP_INPUT_MOUSE_MOVE:
				{
				internals->mouse_x = event->data.mouse_pos.x;
				internals->mouse_y = event->data.mouse_pos.y;
				} break;
			case APP_INPUT_MOUSE_DELTA:
				{
				if( event->data.mouse_delta.x != 0.0f )
					inputmap_update_mouseaxis( internals->inputmap, INPUTMAP_MOUSEAXIS_LEFT_RIGHT, 
						event->data.mouse_delta.x );
				if( event->data.mouse_delta.y != 0.0f )
					inputmap_update_mouseaxis( internals->inputmap, INPUTMAP_MOUSEAXIS_FORWARD_BACK, 
						event->data.mouse_delta.y );
				} break;
			case APP_INPUT_SCROLL_WHEEL:
				{
				inputmap_update_mouseaxis( internals->inputmap, INPUTMAP_MOUSEAXIS_WHEEL, event->data.wheel_delta );
				} break;
			case APP_INPUT_TABLET:
				{
				internals->pen_x = event->data.tablet.x;
				internals->pen_y = event->data.tablet.y;
				internals->pen_pressure = event->data.tablet.pressure;
				internals->key_states[ KEY_PEN_TOUCH ] = event->data.tablet.tip != 0;
				internals->key_states[ KEY_PEN_LOWER_BUTTON ] = event->data.tablet.lower == APP_PRESSED;
				internals->key_states[ KEY_PEN_UPPER_BUTTON ] = event->data.tablet.upper == APP_PRESSED;
				} break;

			case APP_INPUT_DOUBLE_CLICK:
				break;
			}
		}

	for( int i = 0; i < sizeof( internals->gamepad_data ) / sizeof( *internals->gamepad_data ); ++i )
		{
		gamepad_state_t* state = &internals->gamepad_data[ i ].state;
		gamepad_state_t* prev_state = &internals->gamepad_data[ i ].previous_state;
		*prev_state = *state;
		internals->gamepad_data[ i ].result = gamepad_read( internals->gamepad, i, state );
		if( internals->gamepad_data[ i ].result == GAMEPAD_RESULT_OK )
			{
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_LEFT_TRIGGER, state->trigger_left / 255.0f );
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_RIGHT_TRIGGER, state->trigger_right / 255.0f );
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_LEFTSTICK_X, state->stick_left_x / 32767.0f );
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_LEFTSTICK_Y, state->stick_left_y / 32767.0f );
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_RIGHTSTICK_X, state->stick_right_x / 32767.0f );
			inputmap_update_gamepadaxis( internals->inputmap, i, INPUTMAP_GAMEPADAXIS_RIGHTSTICK_Y, state->stick_right_y / 32767.0f );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_DPAD_UP ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_UP );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_DPAD_UP ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_UP );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_DPAD_DOWN ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_DOWN );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_DPAD_DOWN ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_DOWN );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_DPAD_LEFT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_LEFT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_DPAD_LEFT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_LEFT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_DPAD_RIGHT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_RIGHT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_DPAD_RIGHT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_DPAD_RIGHT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_START ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_START );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_START ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_START );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_BACK ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_BACK );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_BACK ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_BACK );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_STICK_LEFT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_STICK_LEFT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_STICK_LEFT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_STICK_LEFT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_STICK_RIGHT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_STICK_RIGHT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_STICK_RIGHT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_STICK_RIGHT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_SHOULDER_LEFT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_SHOULDER_LEFT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_SHOULDER_LEFT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_SHOULDER_LEFT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_SHOULDER_RIGHT ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_SHOULDER_RIGHT );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_SHOULDER_RIGHT ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_SHOULDER_RIGHT );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_A ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_A );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_A ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_A );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_B ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_B );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_B ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_B );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_X ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_X );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_X ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_X );

			if( ( state->buttons & GAMEPAD_DPAD_UP ) && !( prev_state->buttons & GAMEPAD_Y ) )
				inputmap_update_gamepadbuttondown( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_Y );
			else if( !( state->buttons & GAMEPAD_DPAD_UP ) && ( prev_state->buttons & GAMEPAD_Y ) )
				inputmap_update_gamepadbuttonup( internals->inputmap, i, INPUTMAP_GAMEPADBUTTON_Y );

			}
		else
			{
			memset( state, 0, sizeof( *state ) );
			}
		}

	inputmap_update_end( internals->inputmap );
	}


void send_events( internals_t* internals )
	{
	for( int i = 0; i < internals->key_released_events.count(); ++i )
		{
		key_event_t* key_event = &internals->key_released_events[ i ];
		key_id key = key_event->key;
		if( !internals->key_states[ key ] && internals->previous_key_states[ key ] )
			key_event->handler->on_event( key_event->event_id, key_event->user_data );
		}

	for( int i = 0; i < internals->key_pressed_events.count(); ++i )
		{
		key_event_t* key_event = &internals->key_pressed_events[ i ];
		key_id key = key_event->key;
		if( internals->key_states[ key ] && !internals->previous_key_states[ key ] )
			key_event->handler->on_event( key_event->event_id, key_event->user_data );
		}

	for( int i = 0; i < internals->gamepad_released_events.count(); ++i )
		{
		gamepadbutton_event_t* gamepad_event = &internals->gamepad_released_events[ i ];
		int pad_index = gamepad_event->pad_index;
		gamepad_button_t button = (gamepad_button_t) 0;
		switch( gamepad_event->button )
			{       
			case GAMEPADBUTTON_DPAD_UP: button = GAMEPAD_DPAD_UP; break;
			case GAMEPADBUTTON_DPAD_DOWN: button = GAMEPAD_DPAD_DOWN; break;
			case GAMEPADBUTTON_DPAD_LEFT: button = GAMEPAD_DPAD_LEFT; break;
			case GAMEPADBUTTON_DPAD_RIGHT: button = GAMEPAD_DPAD_RIGHT; break;
			case GAMEPADBUTTON_START: button = GAMEPAD_START; break;
			case GAMEPADBUTTON_BACK: button = GAMEPAD_BACK; break;
			case GAMEPADBUTTON_STICK_LEFT: button = GAMEPAD_STICK_LEFT; break;
			case GAMEPADBUTTON_STICK_RIGHT: button = GAMEPAD_STICK_RIGHT; break;
			case GAMEPADBUTTON_SHOULDER_LEFT: button = GAMEPAD_SHOULDER_LEFT; break;
			case GAMEPADBUTTON_SHOULDER_RIGHT: button = GAMEPAD_SHOULDER_RIGHT; break;
			case GAMEPADBUTTON_A: button = GAMEPAD_A; break;
			case GAMEPADBUTTON_B: button = GAMEPAD_B; break;
			case GAMEPADBUTTON_X: button = GAMEPAD_X; break;
			case GAMEPADBUTTON_Y: button = GAMEPAD_Y; break;
			}
		if( internals->gamepad_data[ pad_index ].result == GAMEPAD_RESULT_OK )
			{
			if( !( internals->gamepad_data[ pad_index ].state.buttons & button ) && 
				( internals->gamepad_data[ pad_index ].previous_state.buttons & button ) )
					gamepad_event->handler->on_event( gamepad_event->event_id, gamepad_event->user_data );
			}
		}

	for( int i = 0; i < internals->gamepad_pressed_events.count(); ++i )
		{
		gamepadbutton_event_t* gamepad_event = &internals->gamepad_pressed_events[ i ];
		int pad_index = gamepad_event->pad_index;
		gamepad_button_t button = (gamepad_button_t) 0;
		switch( gamepad_event->button )
			{       
			case GAMEPADBUTTON_DPAD_UP: button = GAMEPAD_DPAD_UP; break;
			case GAMEPADBUTTON_DPAD_DOWN: button = GAMEPAD_DPAD_DOWN; break;
			case GAMEPADBUTTON_DPAD_LEFT: button = GAMEPAD_DPAD_LEFT; break;
			case GAMEPADBUTTON_DPAD_RIGHT: button = GAMEPAD_DPAD_RIGHT; break;
			case GAMEPADBUTTON_START: button = GAMEPAD_START; break;
			case GAMEPADBUTTON_BACK: button = GAMEPAD_BACK; break;
			case GAMEPADBUTTON_STICK_LEFT: button = GAMEPAD_STICK_LEFT; break;
			case GAMEPADBUTTON_STICK_RIGHT: button = GAMEPAD_STICK_RIGHT; break;
			case GAMEPADBUTTON_SHOULDER_LEFT: button = GAMEPAD_SHOULDER_LEFT; break;
			case GAMEPADBUTTON_SHOULDER_RIGHT: button = GAMEPAD_SHOULDER_RIGHT; break;
			case GAMEPADBUTTON_A: button = GAMEPAD_A; break;
			case GAMEPADBUTTON_B: button = GAMEPAD_B; break;
			case GAMEPADBUTTON_X: button = GAMEPAD_X; break;
			case GAMEPADBUTTON_Y: button = GAMEPAD_Y; break;
			}
		if( internals->gamepad_data[ pad_index ].result == GAMEPAD_RESULT_OK )
			{
			if( ( internals->gamepad_data[ pad_index ].state.buttons & button ) && 
				!( internals->gamepad_data[ pad_index ].previous_state.buttons & button ) )
					gamepad_event->handler->on_event( gamepad_event->event_id, gamepad_event->user_data );
			}
		}

	for( int i = 0; i < internals->gamepad_axis_events.count(); ++i )
		{
		gamepadaxis_event_t* gamepad_event = &internals->gamepad_axis_events[ i ];
		int pad_index = gamepad_event->pad_index;
		gamepadaxis_id axis = gamepad_event->axis;
		float threshold = gamepad_event->threshold;
		if( internals->gamepad_data[ pad_index ].result == GAMEPAD_RESULT_OK )
			{
			float value = 0.0f;
			float prev_value = 0.0f;
			switch( axis )
				{       
				case GAMEPADAXIS_LEFT_TRIGGER:
					value = internals->gamepad_data[ pad_index ].state.trigger_left / 255.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.trigger_left / 255.0f;
					break;
				case GAMEPADAXIS_RIGHT_TRIGGER:
					value = internals->gamepad_data[ pad_index ].state.trigger_right / 255.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.trigger_right / 255.0f;
					break;
				case GAMEPADAXIS_LEFTSTICK_X:
					value = internals->gamepad_data[ pad_index ].state.stick_left_x / 32767.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.stick_left_x / 32767.0f;
					break;
				case GAMEPADAXIS_LEFTSTICK_Y:
					value = internals->gamepad_data[ pad_index ].state.stick_left_y / 32767.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.stick_left_y / 32767.0f;
					break;
				case GAMEPADAXIS_RIGHTSTICK_X:
					value = internals->gamepad_data[ pad_index ].state.stick_right_x / 32767.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.stick_right_x / 32767.0f;
					break;
				case GAMEPADAXIS_RIGHTSTICK_Y:
					value = internals->gamepad_data[ pad_index ].state.stick_right_y / 32767.0f;
					prev_value = internals->gamepad_data[ pad_index ].previous_state.stick_right_y / 32767.0f;
					break;
				}
			if( value > threshold && prev_value <= threshold )
				gamepad_event->handler->on_event( gamepad_event->event_id, gamepad_event->user_data );
			}
		}

	for( int i = 0; i < internals->action_events.count(); ++i )
		{
		action_event_t* action_event = &internals->action_events[ i ];
		int action_index = internal::lookup_action_index( action_event->action );
		float value = inputmap_action( internals->inputmap, action_index );
		float threshold = action_event->using_threshold ? action_event->threshold : 0.0f;
		if( value > threshold )
			action_event->handler->on_event( action_event->event_id, action_event->user_data );
		}

	for( int i = 0; i < internals->time_events.count(); ++i )
		{
		time_event_t* time_event = &internals->time_events[ i ];
		time_event->seconds -= internals->delta_time;
		if( time_event->seconds <= 0.0f )
			{
			time_event->handler->on_event( time_event->event_id, time_event->user_data );
			if( time_event->repeat > 0.0f )
				{
				time_event->seconds = time_event->repeat;
				}
			else
				{
				internals->time_events.remove( i );
				--i;
				}
			}
		}
	}
	

void sound_callback( APP_S16* sample_pairs, int sample_pairs_count, void* user_data )
	{
	audiosys_t* audiosys = (audiosys_t*) user_data;
	audiosys_consume( audiosys, sample_pairs_count, sample_pairs, sample_pairs_count );
	}



struct audio_thread_sound_t
	{
	u64 update_handle;
	u64 audiosys_handle;
	audio_instance* instance;
	struct audio_thread_context_t* context;
	};


struct audio_thread_context_t
	{
	void* memctx;
	audio_thread_sound_t* finished;
	int finished_count;
	int finished_capacity;
	};


int audio_read_samples( void* instance, float* sample_pairs, int sample_pairs_count )
	{
	if( !instance ) return 0;
	audio_thread_sound_t* sound = (audio_thread_sound_t*) instance;
	if( !sound->instance->read_samples ) return 0;
	return sound->instance->read_samples( sound->instance, sample_pairs, sample_pairs_count );
	}


void audio_restart( void* instance )
	{
	if( !instance ) return;
	audio_thread_sound_t* sound = (audio_thread_sound_t*) instance;
	if( sound->instance->restart ) sound->instance->restart( sound->instance );
	}


void audio_set_position( void* instance, int position_in_sample_pairs )
	{
	if( !instance ) return;
	audio_thread_sound_t* sound = (audio_thread_sound_t*) instance;
	if( sound->instance->set_position ) sound->instance->set_position( sound->instance, position_in_sample_pairs );
	}


int audio_get_position( void* instance )
	{
	if( !instance ) return 0;
	audio_thread_sound_t* sound = (audio_thread_sound_t*) instance;
	if( !sound->instance->get_position_in_sample_pairs_from_start ) return 0;
	return sound->instance->get_position_in_sample_pairs_from_start( sound->instance );
	}


void audio_add_to_finished_list( audio_thread_context_t* context, audio_thread_sound_t* sound )
	{
	if( context->finished_count >= context->finished_capacity )
		{
		context->finished_capacity *= 2;
		audio_thread_sound_t* new_finished = (audio_thread_sound_t*) 
			TRACKED_MALLOC( context->memctx, sizeof( audio_thread_sound_t ) * context->finished_capacity );
		memcpy( new_finished, context->finished, sizeof( audio_thread_sound_t ) * context->finished_count );
		TRACKED_FREE( context->memctx, context->finished );
		context->finished = new_finished;
		}
	context->finished[ context->finished_count++ ] = *sound;
	}


void audio_release( void* instance )
	{
	if( !instance ) return;
	audio_thread_sound_t* sound = (audio_thread_sound_t*) instance;
	audio_thread_context_t* context = (audio_thread_context_t*) sound->context;
	audio_add_to_finished_list( context, sound );
	}


struct app_proc_data_t
	{
	game_main_func_t game_main;
	void* memctx;
	};


struct audio_thread_data_t
	{
	app_proc_data_t* app_proc_data;
	bool exit_flag;
	audiosys_t* audiosys;
	thread_queue_t* audio_frame_data_from_audio_thread_queue;
	thread_queue_t* audio_frame_data_from_update_thread_queue;
	thread_signal_t* audio_thread_ended_signal;
	};


struct audio_delayed_sound_t
	{
	audio_command_type_t type;
	u64 handle;
	audio_instance* instance;
	float fade_in_time;
	float fade_out_time;
	float cross_fade_time;
	float delay;
	float priority;
	float volume;
	float position;
	float pan;
	bool loop;
	bool paused;
	};

void clear_delayed( audio_thread_context_t* context, audio_delayed_sound_t* delayed )
	{
	if( delayed->type != AUDIO_COMMAND_TYPE_INVALID )
		{
		audio_thread_sound_t sound;
		sound.update_handle = delayed->handle;
		sound.audiosys_handle = 0;
		sound.instance = delayed->instance;
		sound.context = context;
		audio_add_to_finished_list( context, &sound );
		delayed->type = AUDIO_COMMAND_TYPE_INVALID;
		}
	}


void remove_delayed_music( audio_thread_context_t* context, hashtable_t* delayed_sounds )
	{
	audio_delayed_sound_t* delayed_sounds_items = (audio_delayed_sound_t*) hashtable_items( delayed_sounds );
	for( int i = 0; i < hashtable_count( delayed_sounds ); ++i )
		{
		audio_delayed_sound_t* delayed = &delayed_sounds_items[ i ];
		if( delayed->type == AUDIO_COMMAND_TYPE_PLAY_MUSIC ||
			delayed->type == AUDIO_COMMAND_TYPE_SWITCH_MUSIC ||
			delayed->type == AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC )
			{
			clear_delayed( context, delayed );
			hashtable_remove( delayed_sounds, delayed->handle );
			}
		}
	}


void remove_delayed_ambience( audio_thread_context_t* context, hashtable_t* delayed_sounds )
	{
	audio_delayed_sound_t* delayed_sounds_items = (audio_delayed_sound_t*) hashtable_items( delayed_sounds );
	for( int i = 0; i < hashtable_count( delayed_sounds ); ++i )
		{
		audio_delayed_sound_t* delayed = &delayed_sounds_items[ i ];
		if( delayed->type == AUDIO_COMMAND_TYPE_PLAY_AMBIENCE ||
			delayed->type == AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE ||
			delayed->type == AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE )
			{
			clear_delayed( context, delayed );
			hashtable_remove( delayed_sounds, delayed->handle );
			}
		}
	}


audio_delayed_sound_t audio_delayed_sound_from_command( audio_command_t* command )
	{
	audio_delayed_sound_t sound;
	sound.type = command->type;
	sound.handle = command->handle;
	sound.instance = 0;
	sound.fade_in_time = 0.0f;
	sound.fade_out_time = 0.0f;
	sound.cross_fade_time = 0.0f;
	sound.delay = 0.0f;
	sound.priority = 0.0f;
	sound.volume = 1.0f;
	sound.position = 0;
	sound.pan = 0.0f;
	sound.loop = false;
	sound.paused = false;

	switch( command->type )
		{
		case AUDIO_COMMAND_TYPE_PLAY_MUSIC:
		case AUDIO_COMMAND_TYPE_PLAY_AMBIENCE:
		case AUDIO_COMMAND_TYPE_PLAY_SOUND:
			sound.instance = command->data.play.instance;
			sound.fade_in_time = command->data.play.fade_in_time;
			sound.delay = command->data.play.delay;
			sound.priority = command->data.play.priority;
			break;
		case AUDIO_COMMAND_TYPE_SWITCH_MUSIC:
		case AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE:
			sound.instance = command->data.switch_.instance;
			sound.fade_in_time = command->data.switch_.fade_in_time;
			sound.fade_out_time = command->data.switch_.fade_out_time;
			sound.delay = command->data.switch_.delay;
			break;
		case AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC:
		case AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE:
			sound.instance = command->data.cross_fade.instance;
			sound.cross_fade_time = command->data.cross_fade.cross_fade_time;
			sound.delay = command->data.cross_fade.delay;
			break;
		case AUDIO_COMMAND_TYPE_INVALID:
		case AUDIO_COMMAND_TYPE_MASTER_VOLUME:
		case AUDIO_COMMAND_TYPE_PAUSE_AUDIO:
		case AUDIO_COMMAND_TYPE_RESUME_AUDIO:
		case AUDIO_COMMAND_TYPE_STOP_MUSIC:
		case AUDIO_COMMAND_TYPE_PAUSE_MUSIC:
		case AUDIO_COMMAND_TYPE_RESUME_MUSIC:
		case AUDIO_COMMAND_TYPE_MUSIC_POSITION:
		case AUDIO_COMMAND_TYPE_MUSIC_LOOP:
		case AUDIO_COMMAND_TYPE_MUSIC_VOLUME:
		case AUDIO_COMMAND_TYPE_MUSIC_PAN:
		case AUDIO_COMMAND_TYPE_STOP_AMBIENCE:
		case AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE:
		case AUDIO_COMMAND_TYPE_RESUME_AMBIENCE:
		case AUDIO_COMMAND_TYPE_AMBIENCE_POSITION:
		case AUDIO_COMMAND_TYPE_AMBIENCE_LOOP:
		case AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME:
		case AUDIO_COMMAND_TYPE_AMBIENCE_PAN:
		case AUDIO_COMMAND_TYPE_STOP_SOUND:
		case AUDIO_COMMAND_TYPE_PAUSE_SOUND:
		case AUDIO_COMMAND_TYPE_RESUME_SOUND:
		case AUDIO_COMMAND_TYPE_SOUND_POSITION:
		case AUDIO_COMMAND_TYPE_SOUND_LOOP:
		case AUDIO_COMMAND_TYPE_SOUND_VOLUME:
		case AUDIO_COMMAND_TYPE_SOUND_PAN:
		default:
			PIXIE_ASSERT( false, "Invalid audio command" );
			break;
		};

	return sound;
	}


int audio_thread_proc( void* user_data )
	{
	thread_set_high_priority(); // audio thread needs to run high priority

	audio_thread_data_t* audio_thread_data = (audio_thread_data_t*) user_data;
	audiosys_t* audiosys = audio_thread_data->audiosys;
	
	audio_thread_context_t audio_thread_context;
	audio_thread_context.memctx = audio_thread_data->app_proc_data->memctx;
	audio_thread_context.finished_count = 0;
	audio_thread_context.finished_capacity = 256;
	audio_thread_context.finished = (audio_thread_sound_t*) TRACKED_MALLOC( 
		audio_thread_context.memctx, sizeof( audio_thread_sound_t ) * audio_thread_context.finished_capacity );
	
	hashtable_t delayed_sounds;
	hashtable_init( &delayed_sounds, (int) sizeof( audio_delayed_sound_t ), 256, audio_thread_context.memctx );

	u64 music_update_handle = 0;
	u64 ambience_update_handle = 0;
	
	mempool<audio_thread_sound_t> sounds_pool( 256, audio_thread_context.memctx );
	hashtable_t sounds;
	hashtable_init( &sounds, (int) sizeof( audio_thread_sound_t* ), 256, audio_thread_context.memctx );

	frametimer_t* timer = frametimer_create( audio_thread_context.memctx );
	frametimer_lock_rate( timer, 60 );
	
	audio_frame_data_t* audio_frame_data = 0;
	while( !audio_thread_data->exit_flag )
		{
		// get an audio frame data buffer from update thread
		audio_frame_data = (audio_frame_data_t*) thread_queue_consume( audio_thread_data->audio_frame_data_from_update_thread_queue, 0 );
		if( audio_frame_data )
			{
			if( audio_frame_data->from_update_thread.exit_flag ) 
				break;

			// process all play commands
			for( int i = 0; i < audio_frame_data->from_update_thread.commands_count; ++i )
				{
				audio_command_t* command = &audio_frame_data->from_update_thread.commands[ i ];
				switch( command->type )
					{
					case AUDIO_COMMAND_TYPE_PLAY_MUSIC:
					case AUDIO_COMMAND_TYPE_SWITCH_MUSIC:
					case AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC:
						{
						remove_delayed_music( &audio_thread_context, &delayed_sounds );
						audio_delayed_sound_t delayed_sound = audio_delayed_sound_from_command( command );
						hashtable_insert( &delayed_sounds, command->handle, &delayed_sound );
						} break;
					case AUDIO_COMMAND_TYPE_STOP_MUSIC: 
						remove_delayed_music( &audio_thread_context, &delayed_sounds );
						audiosys_music_stop( audiosys, command->data.fade_out_time ); 
						break;

					case AUDIO_COMMAND_TYPE_PLAY_AMBIENCE:
					case AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE:
					case AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE:
						{
						remove_delayed_ambience( &audio_thread_context, &delayed_sounds );
						audio_delayed_sound_t delayed_sound = audio_delayed_sound_from_command( command );
						hashtable_insert( &delayed_sounds, command->handle, &delayed_sound );
						} break;
					case AUDIO_COMMAND_TYPE_STOP_AMBIENCE: 
						remove_delayed_ambience( &audio_thread_context, &delayed_sounds );
						audiosys_ambience_stop( audiosys, command->data.fade_out_time ); 
						break;

					case AUDIO_COMMAND_TYPE_PLAY_SOUND:                     
						{
						audio_delayed_sound_t delayed_sound = audio_delayed_sound_from_command( command );
						hashtable_insert( &delayed_sounds, command->handle, &delayed_sound );
						} break;
					case AUDIO_COMMAND_TYPE_STOP_SOUND:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_stop( audiosys, (*sound_ptr)->audiosys_handle, command->data.fade_out_time );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								{
								clear_delayed( &audio_thread_context, delayed_sound );
								hashtable_remove( &delayed_sounds, command->handle );
								}
							}
						} break;
					case AUDIO_COMMAND_TYPE_PAUSE_SOUND:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_pause( audiosys, (*sound_ptr)->audiosys_handle );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->paused = true;
							}
						} break;
					case AUDIO_COMMAND_TYPE_RESUME_SOUND:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{   
							audiosys_sound_resume( audiosys, (*sound_ptr)->audiosys_handle );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->paused = false;
							}
						} break;
					case AUDIO_COMMAND_TYPE_SOUND_POSITION:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_position_set( audiosys, (*sound_ptr)->audiosys_handle, command->data.position );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->position = command->data.position;
							}
						} break;
					case AUDIO_COMMAND_TYPE_SOUND_LOOP:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_loop_set( audiosys, (*sound_ptr)->audiosys_handle, command->data.loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->loop = command->data.loop;
							}
						} break;
					case AUDIO_COMMAND_TYPE_SOUND_VOLUME:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_volume_set( audiosys, (*sound_ptr)->audiosys_handle, command->data.volume );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->volume = command->data.volume;
							}
						} break;
					case AUDIO_COMMAND_TYPE_SOUND_PAN:
						{
						audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, command->handle );
						if( sound_ptr ) 
							{
							audiosys_sound_pan_set( audiosys, (*sound_ptr)->audiosys_handle, command->data.pan );
							}
						else
							{
							audio_delayed_sound_t* delayed_sound = (audio_delayed_sound_t*) hashtable_find( &delayed_sounds, command->handle );
							if( delayed_sound )
								delayed_sound->pan = command->data.pan;
							}
						} break;
					case AUDIO_COMMAND_TYPE_INVALID:
					case AUDIO_COMMAND_TYPE_MASTER_VOLUME:
					case AUDIO_COMMAND_TYPE_PAUSE_AUDIO:
					case AUDIO_COMMAND_TYPE_RESUME_AUDIO:
					case AUDIO_COMMAND_TYPE_PAUSE_MUSIC:
					case AUDIO_COMMAND_TYPE_RESUME_MUSIC:
					case AUDIO_COMMAND_TYPE_MUSIC_POSITION:
					case AUDIO_COMMAND_TYPE_MUSIC_LOOP:
					case AUDIO_COMMAND_TYPE_MUSIC_VOLUME:
					case AUDIO_COMMAND_TYPE_MUSIC_PAN:
					case AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE:
					case AUDIO_COMMAND_TYPE_RESUME_AMBIENCE:
					case AUDIO_COMMAND_TYPE_AMBIENCE_POSITION:
					case AUDIO_COMMAND_TYPE_AMBIENCE_LOOP:
					case AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME:
					case AUDIO_COMMAND_TYPE_AMBIENCE_PAN:
						break;
					}
				}
			}

		float delta_time = frametimer_update( timer );

		// process delayed sounds
		audio_delayed_sound_t* delayed_sounds_items = (audio_delayed_sound_t*) hashtable_items( &delayed_sounds );
		for( int i = 0; i < hashtable_count( &delayed_sounds ); ++i )
			{
			audio_delayed_sound_t* delayed_sound = &delayed_sounds_items[ i ];
			delayed_sound->delay -= delta_time;
			if( delayed_sound->delay <= 0.0f )
				{
				audio_thread_sound_t* sound = sounds_pool.allocate();
				sound->update_handle = delayed_sound->handle;
				sound->instance = delayed_sound->instance;
				sound->context = &audio_thread_context;
				sound->audiosys_handle = 0;

				audiosys_audio_source_t source;
				source.instance = sound;
				source.release = sound->instance->release ? audio_release : 0;
				source.read_samples = sound->instance->read_samples ? audio_read_samples : 0;
				source.restart = sound->instance->restart ? audio_restart : 0;
				source.set_position = sound->instance->set_position ? audio_set_position : 0;
				source.get_position = sound->instance->get_position_in_sample_pairs_from_start ? audio_get_position : 0;

				switch( delayed_sound->type )
					{
					case AUDIO_COMMAND_TYPE_PLAY_MUSIC:
						{
						audiosys_music_play( audiosys, source, delayed_sound->fade_in_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						music_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_SWITCH_MUSIC:
						{
						audiosys_music_switch( audiosys, source, delayed_sound->fade_out_time, delayed_sound->fade_in_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						music_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC:
						{
						audiosys_music_cross_fade( audiosys, source, delayed_sound->cross_fade_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						music_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_PLAY_AMBIENCE:
						{
						audiosys_ambience_play( audiosys, source, delayed_sound->fade_in_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						ambience_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE:
						{
						audiosys_ambience_switch( audiosys, source, delayed_sound->fade_out_time, delayed_sound->fade_in_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						ambience_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE:
						{
						audiosys_ambience_cross_fade( audiosys, source, delayed_sound->cross_fade_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );
						ambience_update_handle = sound->update_handle;
						} break;

					case AUDIO_COMMAND_TYPE_PLAY_SOUND:
						{
						sound->audiosys_handle = audiosys_sound_play( audiosys, source, delayed_sound->priority, delayed_sound->fade_in_time );
						hashtable_insert( &sounds, sound->update_handle, &sound );

						audiosys_sound_volume_set( audiosys, sound->audiosys_handle, delayed_sound->volume );
						audiosys_sound_pan_set( audiosys, sound->audiosys_handle, delayed_sound->pan );
						audiosys_sound_loop_set( audiosys, sound->audiosys_handle, delayed_sound->loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF );
						if( delayed_sound->paused ) audiosys_sound_pause( audiosys, sound->audiosys_handle );
						} break;
					case AUDIO_COMMAND_TYPE_INVALID:
					case AUDIO_COMMAND_TYPE_MASTER_VOLUME:
					case AUDIO_COMMAND_TYPE_PAUSE_AUDIO:
					case AUDIO_COMMAND_TYPE_RESUME_AUDIO:
					case AUDIO_COMMAND_TYPE_STOP_MUSIC:
					case AUDIO_COMMAND_TYPE_PAUSE_MUSIC:
					case AUDIO_COMMAND_TYPE_RESUME_MUSIC:
					case AUDIO_COMMAND_TYPE_MUSIC_POSITION:
					case AUDIO_COMMAND_TYPE_MUSIC_LOOP:
					case AUDIO_COMMAND_TYPE_MUSIC_VOLUME:
					case AUDIO_COMMAND_TYPE_MUSIC_PAN:
					case AUDIO_COMMAND_TYPE_STOP_AMBIENCE:
					case AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE:
					case AUDIO_COMMAND_TYPE_RESUME_AMBIENCE:
					case AUDIO_COMMAND_TYPE_AMBIENCE_POSITION:
					case AUDIO_COMMAND_TYPE_AMBIENCE_LOOP:
					case AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME:
					case AUDIO_COMMAND_TYPE_AMBIENCE_PAN:
					case AUDIO_COMMAND_TYPE_STOP_SOUND:
					case AUDIO_COMMAND_TYPE_PAUSE_SOUND:
					case AUDIO_COMMAND_TYPE_RESUME_SOUND:
					case AUDIO_COMMAND_TYPE_SOUND_POSITION:
					case AUDIO_COMMAND_TYPE_SOUND_LOOP:
					case AUDIO_COMMAND_TYPE_SOUND_VOLUME:
					case AUDIO_COMMAND_TYPE_SOUND_PAN:
						PIXIE_ASSERT( false, "Unexpected audio command" );
					}
				hashtable_remove( &delayed_sounds, delayed_sound->handle );
				--i;
				}
			}

		if( audio_frame_data )
			{
			// process all remaining audio commands
			for( int i = 0; i < audio_frame_data->from_update_thread.commands_count; ++i )
				{
				audio_command_t* command = &audio_frame_data->from_update_thread.commands[ i ];
				switch( command->type )
					{
					case AUDIO_COMMAND_TYPE_INVALID:
						break;
					case AUDIO_COMMAND_TYPE_MASTER_VOLUME:
						audiosys_master_volume_set( audiosys, command->data.volume );
						break;
					case AUDIO_COMMAND_TYPE_PAUSE_AUDIO: 
						audiosys_pause( audiosys ); 
						break;
					case AUDIO_COMMAND_TYPE_RESUME_AUDIO: 
						audiosys_resume( audiosys ); 
						break;

					case AUDIO_COMMAND_TYPE_PAUSE_MUSIC: 
						audiosys_music_pause( audiosys ); 
						break;
					case AUDIO_COMMAND_TYPE_RESUME_MUSIC: 
						audiosys_music_resume( audiosys );
						break;
					case AUDIO_COMMAND_TYPE_MUSIC_POSITION:
						audiosys_music_position_set( audiosys, command->data.position );
						break;
					case AUDIO_COMMAND_TYPE_MUSIC_LOOP:
						audiosys_music_loop_set( audiosys, command->data.loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF );
						break;
					case AUDIO_COMMAND_TYPE_MUSIC_VOLUME:
						audiosys_music_volume_set( audiosys, command->data.volume );
						break;
					case AUDIO_COMMAND_TYPE_MUSIC_PAN:
						audiosys_music_pan_set( audiosys, command->data.pan );
						break;

					case AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE: 
						audiosys_ambience_pause( audiosys ); 
						break;
					case AUDIO_COMMAND_TYPE_RESUME_AMBIENCE: 
						audiosys_ambience_resume( audiosys );
						break;
					case AUDIO_COMMAND_TYPE_AMBIENCE_POSITION:
						audiosys_ambience_position_set( audiosys, command->data.position );
						break;
					case AUDIO_COMMAND_TYPE_AMBIENCE_LOOP:
						audiosys_ambience_loop_set( audiosys, command->data.loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF );
						break;
					case AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME:
						audiosys_ambience_volume_set( audiosys, command->data.volume );
						break;
					case AUDIO_COMMAND_TYPE_AMBIENCE_PAN:
						audiosys_ambience_pan_set( audiosys, command->data.pan );
						break;
					case AUDIO_COMMAND_TYPE_PLAY_MUSIC:
					case AUDIO_COMMAND_TYPE_STOP_MUSIC:
					case AUDIO_COMMAND_TYPE_SWITCH_MUSIC:
					case AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC:
					case AUDIO_COMMAND_TYPE_PLAY_AMBIENCE:
					case AUDIO_COMMAND_TYPE_STOP_AMBIENCE:
					case AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE:
					case AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE:
					case AUDIO_COMMAND_TYPE_PLAY_SOUND:
					case AUDIO_COMMAND_TYPE_STOP_SOUND:
					case AUDIO_COMMAND_TYPE_PAUSE_SOUND:
					case AUDIO_COMMAND_TYPE_RESUME_SOUND:
					case AUDIO_COMMAND_TYPE_SOUND_POSITION:
					case AUDIO_COMMAND_TYPE_SOUND_LOOP:
					case AUDIO_COMMAND_TYPE_SOUND_VOLUME:
					case AUDIO_COMMAND_TYPE_SOUND_PAN:
						break;
					}
				}

				
			audio_frame_data->from_update_thread.commands_count = 0;
			}   


		// remix sound buffers
		audiosys_update( audiosys );

		// send data back to update thread
		if( audio_frame_data )
			{
			if( audio_frame_data->from_audio_thread.finished_capacity < audio_thread_context.finished_count )
				{
				audio_frame_data->from_audio_thread.finished_capacity = (int) math_util::pow2_ceil( (u32) audio_thread_context.finished_count );
				TRACKED_FREE( audio_thread_context.memctx, audio_frame_data->from_audio_thread.finished );
				audio_frame_data->from_audio_thread.finished = (finished_audio_t*) TRACKED_MALLOC( 
					audio_thread_context.memctx, audio_frame_data->from_audio_thread.finished_capacity * sizeof( finished_audio_t ) );
				}

			audio_frame_data->from_audio_thread.finished_count = 0;
			for( int i = 0; i < audio_thread_context.finished_count; ++i )
				{
				audio_thread_sound_t* finished = &audio_thread_context.finished[ i ];
				if( finished->audiosys_handle != 0 )
					{
					audio_thread_sound_t** sound_ptr = (audio_thread_sound_t**) hashtable_find( &sounds, finished->update_handle );
					PIXIE_ASSERT( sound_ptr && (*sound_ptr)->instance == finished->instance, "Sound not found" );

					finished_audio_t* finished_audio = &audio_frame_data->from_audio_thread.finished[ audio_frame_data->from_audio_thread.finished_count++ ];
					finished_audio->handle = (*sound_ptr)->update_handle;
					finished_audio->instance = (*sound_ptr)->instance;

					audio_thread_sound_t* ptr = (*sound_ptr);
					hashtable_remove( &sounds, (*sound_ptr)->update_handle );
					sounds_pool.deallocate( ptr );
					}
				else
					{
					finished_audio_t* finished_audio = &audio_frame_data->from_audio_thread.finished[ audio_frame_data->from_audio_thread.finished_count++ ];
					finished_audio->handle = finished->update_handle;
					finished_audio->instance = finished->instance;
					}
				}
			audio_thread_context.finished_count = 0;

			audio_thread_sound_t** sounds_items = (audio_thread_sound_t**) hashtable_items( &sounds );
			int sounds_count = hashtable_count( &sounds );
			if( audio_frame_data->from_audio_thread.positions_capacity < sounds_count + 2 )
				{
				audio_frame_data->from_audio_thread.positions_capacity = (int) math_util::pow2_ceil( (u32) sounds_count + 2);
				TRACKED_FREE( audio_thread_context.memctx, audio_frame_data->from_audio_thread.positions );
				audio_frame_data->from_audio_thread.positions = (audio_position_t*) TRACKED_MALLOC( 
					audio_thread_context.memctx, audio_frame_data->from_audio_thread.positions_capacity * sizeof( audio_position_t ) );
				}

			for( int i = 0; i < sounds_count; ++i )
				{
				audio_position_t* position = &audio_frame_data->from_audio_thread.positions[ i ];
				position->handle = sounds_items[ i ]->update_handle;
				position->position = audiosys_sound_position( audiosys, sounds_items[ i ]->audiosys_handle );
				}

			audio_position_t* music_position = &audio_frame_data->from_audio_thread.positions[ sounds_count++ ];
			music_position->handle = music_update_handle;
			music_position->position = audiosys_music_position( audiosys );
			
			audio_position_t* ambience_position = &audio_frame_data->from_audio_thread.positions[ sounds_count++ ];
			ambience_position->handle = ambience_update_handle;
			ambience_position->position = audiosys_ambience_position( audiosys );

			audio_frame_data->from_audio_thread.positions_count = sounds_count;
		   
			thread_queue_produce( audio_thread_data->audio_frame_data_from_audio_thread_queue, audio_frame_data, THREAD_QUEUE_WAIT_INFINITE );
			audio_frame_data = 0;
			}
		}

	audiosys_stop_all( audiosys );
	audio_delayed_sound_t* delayed = (audio_delayed_sound_t*) hashtable_items( &delayed_sounds );
	for( int i = 0; i < hashtable_count( &delayed_sounds ); ++i )
		clear_delayed( &audio_thread_context, &delayed[ i ] );

	if( !audio_frame_data ) audio_frame_data = (audio_frame_data_t*) thread_queue_consume( audio_thread_data->audio_frame_data_from_update_thread_queue, THREAD_QUEUE_WAIT_INFINITE );
	if( audio_frame_data->from_audio_thread.finished_capacity < audio_thread_context.finished_count )
		{
		audio_frame_data->from_audio_thread.finished_capacity = (int) math_util::pow2_ceil( (u32) audio_thread_context.finished_count );
		TRACKED_FREE( audio_thread_context.memctx, audio_frame_data->from_audio_thread.finished );
		audio_frame_data->from_audio_thread.finished = (finished_audio_t*) TRACKED_MALLOC( 
			audio_thread_context.memctx, audio_frame_data->from_audio_thread.finished_capacity * sizeof( finished_audio_t ) );
		}

	audio_frame_data->from_audio_thread.finished_count = 0;
	for( int i = 0; i < audio_thread_context.finished_count; ++i )
		{
		audio_thread_sound_t* finished = &audio_thread_context.finished[ i ];
		finished_audio_t* finished_audio = &audio_frame_data->from_audio_thread.finished[ audio_frame_data->from_audio_thread.finished_count++ ];
		finished_audio->handle = finished->update_handle;
		finished_audio->instance = finished->instance;
		}

	thread_queue_produce( audio_thread_data->audio_frame_data_from_audio_thread_queue, audio_frame_data, THREAD_QUEUE_WAIT_INFINITE );
	audio_frame_data = 0;

	frametimer_destroy( timer );
	sounds_pool.clear();
	hashtable_term( &delayed_sounds );
	hashtable_term( &sounds );
	TRACKED_FREE( audio_thread_context.memctx, audio_thread_context.finished );
	thread_signal_raise( audio_thread_data->audio_thread_ended_signal );
	return 0;
	}


struct update_thread_data_t
	{
	bool exit_flag;
	app_proc_data_t* app_proc_data;
	thread_queue_t* frame_data_from_app_thread_queue;
	thread_queue_t* frame_data_from_update_thread_queue;
	thread_queue_t* audio_frame_data_from_audio_thread_queue;
	thread_queue_t* audio_frame_data_from_update_thread_queue;
	thread_signal_t* audio_thread_ended_signal;
	app_displays_t displays;
	};


int update_thread_proc( void* user_data )
	{
	thread_set_high_priority(); // want update thread to run uninterrupted, but use a manual yield instead

	update_thread_data_t* update_thread_data = (update_thread_data_t*) user_data;
	app_proc_data_t* app_proc_data = update_thread_data->app_proc_data;

	// create and initialize internal engine state
	u8* internals_storage = (u8*) TRACKED_MALLOC( app_proc_data->memctx, sizeof( internals_t ) );
	memset( internals_storage, 0, sizeof( internals_t ) );
	( (internals_t*)internals_storage )->memctx = app_proc_data->memctx;
	thread_tls_t tls = thread_atomic_ptr_load( &internals_tls );
	thread_tls_set( tls, internals_storage ); // make internals available through thread-local storage
	internals_t* internals = new (internals_storage) internals_t( app_proc_data->memctx, 
		(frame_data_t*) thread_queue_consume( update_thread_data->frame_data_from_app_thread_queue, THREAD_QUEUE_WAIT_INFINITE ),
		(audio_frame_data_t*) thread_queue_consume( update_thread_data->audio_frame_data_from_audio_thread_queue, THREAD_QUEUE_WAIT_INFINITE ),
		update_thread_data, update_thread_data->displays );   

	// run game
	int return_value = app_proc_data->game_main();

	// destroy game instance
	internals->game_states.pop( -1 );
	internals->game_states.update( 0.0f );
	internals->tween_system.stop_all();    

	// release frame data
	if( internals->frame_data )
		{
		internals->frame_data->from_update_thread.exit_flag = true;
		thread_queue_produce( update_thread_data->frame_data_from_update_thread_queue, internals->frame_data, THREAD_QUEUE_WAIT_INFINITE );
		internals->frame_data = 0;
		}
	if( !internals->audio_frame_data ) internals->audio_frame_data = (internal::audio_frame_data_t*) thread_queue_consume( update_thread_data->audio_frame_data_from_audio_thread_queue, THREAD_QUEUE_WAIT_INFINITE );
	internals->audio_frame_data->from_update_thread.exit_flag = true;
	thread_queue_produce( update_thread_data->audio_frame_data_from_update_thread_queue, internals->audio_frame_data, THREAD_QUEUE_WAIT_INFINITE );
	thread_signal_wait( update_thread_data->audio_thread_ended_signal, THREAD_SIGNAL_WAIT_INFINITE );

	// clear audio
	if( !internals->audio_frame_data )
		internals->audio_frame_data = (internal::audio_frame_data_t*) thread_queue_consume( update_thread_data->audio_frame_data_from_audio_thread_queue, THREAD_QUEUE_WAIT_INFINITE );
	while( internals->audio_frame_data )
		{
		for( int i = 0; i < internals->audio_frame_data->from_audio_thread.finished_count; ++i )
			{
			internal::sound_instance* instance = internals->current_sounds.find( internals->audio_frame_data->from_audio_thread.finished[ i ].handle );
			if( instance )
				{
				instance->audio_resource->destroy_instance( internals->audio_frame_data->from_audio_thread.finished[ i ].instance );
				internals->current_sounds.remove( internals->audio_frame_data->from_audio_thread.finished[ i ].handle );
				}
			}
		internals->audio_frame_data->from_audio_thread.finished_count = 0;
		thread_queue_produce( update_thread_data->audio_frame_data_from_update_thread_queue, internals->audio_frame_data, 100 );
		internals->audio_frame_data = 0;
		internals->audio_frame_data = (internal::audio_frame_data_t*) thread_queue_consume( update_thread_data->audio_frame_data_from_audio_thread_queue, 100 );
		}

	// destroy internal state
	internals->~internals_t();
	TRACKED_FREE( app_proc_data->memctx, internals_storage );
	thread_tls_set( tls, 0 );   

	return return_value;
	}

} /* namespace internal */ } /* namespace pixie */


void pixie::execute_frame()
	{
	internal::internals_t* internals = internal::internals();
	internal::update_thread_data_t* update_thread_data = internals->update_thread_data;

	internals->game_states.update( internals->delta_time );

	for( int i = 0; i < internals->sprite_managers.count(); ++i )
		{
		sprite_manager* mgr = internals->sprite_managers[ i ].manager;
		void (sprite_manager::*update_func)() = internals->sprite_managers[ i ].update_func;
		(mgr->*update_func)();
		void (sprite_manager::*render_func)() = internals->sprite_managers[ i ].render_func;
		(mgr->*render_func)();
		}
					  
	cpu_bar(); // end any profiling currently in progress

	// hand audio frame_data over to audio thread
	thread_queue_produce( update_thread_data->audio_frame_data_from_update_thread_queue, internals->audio_frame_data, THREAD_QUEUE_WAIT_INFINITE );
	internals->audio_frame_data = 0;

	// queue frame for rendering
	{
		strcpy( internals->frame_data->from_update_thread.title, internals->title );
		internals->frame_data->from_update_thread.screenmode = internals->screenmode;
		internals->frame_data->from_update_thread.mouse_pointer = internals->mouse_pointer; internals->mouse_pointer.changed = false;
		internals->frame_data->from_update_thread.use_crtmode = internals->use_crtmode;
		internals->frame_data->from_update_thread.exit_flag = internals->exit_flag;
		internals->frame_data->from_update_thread.color_res = internals->color_res;

		int screen_width = internals->screen_width;
		int screen_height = internals->screen_height;
		int border_width = internals->border_width;
		int border_height = internals->border_height;   
		int splits_count = internals->palette_splits.count();
		int cpu_bars_count = internals->cpu_bars_enabled ? internals->cpu_bars.count() : 0;
		internals->frame_data->from_update_thread.screen_width = screen_width;
		internals->frame_data->from_update_thread.screen_height = screen_height;
		internals->frame_data->from_update_thread.border_width = border_width;
		internals->frame_data->from_update_thread.border_height = border_height;
		internals->frame_data->from_update_thread.splits_count = splits_count;
		internals->frame_data->from_update_thread.cpu_bars_count = cpu_bars_count;
		
		size_t required_capacity = 
			+ screen_width * screen_height * sizeof( u8 )
			+ 256 * sizeof( rgb )
			+ splits_count * sizeof( internal::internals_t::palette_split_t )
			+ cpu_bars_count * sizeof( internal::internals_t::cpu_bar_t );
		if( internals->frame_data->from_update_thread.capacity < required_capacity )
			{
			internals->frame_data->from_update_thread.capacity = math_util::pow2_ceil( (u32) required_capacity );
			TRACKED_FREE( internals->memctx, internals->frame_data->from_update_thread.storage );
			internals->frame_data->from_update_thread.storage = TRACKED_MALLOC( internals->memctx, 
				internals->frame_data->from_update_thread.capacity );
			}
		u8* screen_copy = (u8*)( internals->frame_data->from_update_thread.storage );
		rgb* pal_copy = (rgb*)( screen_copy + screen_width * screen_height ); 
		internal::internals_t::palette_split_t* splits_copy = (internal::internals_t::palette_split_t*)( pal_copy + 256 ); 
		internal::internals_t::cpu_bar_t* cpu_bars_copy = (internal::internals_t::cpu_bar_t*)( splits_copy + splits_count ); 

		memcpy( screen_copy, internals->screen_pixels, screen_width * screen_height * sizeof( u8 ) );
		memcpy( pal_copy, internals->palette, 256 * sizeof( rgb ) );
		memcpy( splits_copy, internals->palette_splits.data(), splits_count * sizeof( internal::internals_t::palette_split_t ) );
		memcpy( cpu_bars_copy, internals->cpu_bars.data(), cpu_bars_count * sizeof( internal::internals_t::cpu_bar_t ) );
	}

	// hand frame_data over to app thread
	thread_queue_produce( update_thread_data->frame_data_from_update_thread_queue, internals->frame_data, THREAD_QUEUE_WAIT_INFINITE );
	internals->frame_data = 0;

	// get a new frame data buffer from app thread
	internals->frame_data = (internal::frame_data_t*) thread_queue_consume( update_thread_data->frame_data_from_app_thread_queue, THREAD_QUEUE_WAIT_INFINITE );

	if( internals->frame_data->from_app_thread.exit_requested ) internals->exit_requested = true;
	internals->frame_data->from_app_thread.exit_requested = false;

	// get a new audio frame data buffer from audio thread
	internals->audio_frame_data = (internal::audio_frame_data_t*) thread_queue_consume( update_thread_data->audio_frame_data_from_audio_thread_queue, THREAD_QUEUE_WAIT_INFINITE );

	for( int i = 0; i < internals->audio_frame_data->from_audio_thread.finished_count; ++i )
		{
		internal::sound_instance* instance = internals->current_sounds.find( internals->audio_frame_data->from_audio_thread.finished[ i ].handle );
		if( instance )
			{
			instance->audio_resource->destroy_instance( internals->audio_frame_data->from_audio_thread.finished[ i ].instance );
			internals->current_sounds.remove( internals->audio_frame_data->from_audio_thread.finished[ i ].handle );
			}
		}
	internals->audio_frame_data->from_audio_thread.finished_count = 0;

	for( int i = 0; i < internals->audio_frame_data->from_audio_thread.positions_count; ++i )
		{
		internal::sound_instance* instance = internals->current_sounds.find( internals->audio_frame_data->from_audio_thread.positions[ i ].handle );
		if( instance )
			instance->position = internals->audio_frame_data->from_audio_thread.positions[ i ].position;
		}
	internals->audio_frame_data->from_audio_thread.positions_count = 0;



	if( internals->frame_data->from_app_thread.exit_flag ) internals->exit_flag = true;       
	if( update_thread_data->exit_flag ) internals->exit_flag = true;
	if( internals->exit_flag )
		{
		internals->game_states.pop();
		internals->game_states.update( 0.0f );
		internals->tween_system.stop_all();    
		}

	// END OF ORIGINAL UPDATE LOOP - NEW FRAME STARTING

	// update frame time/count
	internals->delta_time = 1.0f / 60.0f; // update runs on fixed 60hz, limited by app_proc_thread (via frame_data queue)
	++internals->frame_count;

	// process input
	process_input( internals, internals->frame_data->from_app_thread.input_events, internals->frame_data->from_app_thread.input_events_count );
	internals->frame_data->from_app_thread.input_events_count = 0;
		
	internals->win_pos_x = internals->frame_data->from_app_thread.win_pos_x;
	internals->win_pos_y = internals->frame_data->from_app_thread.win_pos_y;
	internals->win_w = internals->frame_data->from_app_thread.win_w;
	internals->win_h = internals->frame_data->from_app_thread.win_h;

	// init cpu profiling bars
	internals->cpu_bars.clear();
	cpu_bar(); // add initial entry for frame start time
		
	// send events
	send_events( internals );
		
	// update game 
	internals->tween_system.update( internals->delta_time * internals->tween_scale );    

	}


namespace pixie { namespace internal {

u32 apply_color_res( rgb color, color_resolution_t res )
	{
	u32 r = color.r;
	u32 g = color.g;
	u32 b = color.b;
	u32 i = 0;
	switch( res )
		{
		case COLOR_RESOLUTION_GRAY1:
			i = ( 54 * r + 182 * g + 19 * b ) / 256;
			i = ( i / 128 ) * 255;
			r = g = b = i;
			break;
		case COLOR_RESOLUTION_GRAY2: 
			i = ( 54 * r + 182 * g + 19 * b ) / 256;
			i = ( i / 64 ) * 85;
			r = g = b = i;
			break;
		case COLOR_RESOLUTION_GRAY4: 
			i = ( 54 * r + 182 * g + 19 * b ) / 256;
			i = ( i / 16 ) * 17;
			r = g = b = i;
			break;
		case COLOR_RESOLUTION_GRAY8:
			i = ( 54 * r + 182 * g + 19 * b ) / 256;
			r = g = b = i;
			break;
		case COLOR_RESOLUTION_RGB3:
			b = ( b / 128 ) * 255;
			g = ( g / 128 ) * 255;
			r = ( r / 128 ) * 255;
			break;
		case COLOR_RESOLUTION_RGB6:
			b = ( b / 64 ) * 85;
			g = ( g / 64 ) * 85;
			r = ( r / 64 ) * 85;
			break;
		case COLOR_RESOLUTION_RGB8:
			b = ( b / 64 ) * 85;
			g = ( g / 32 ) * 36;
			r = ( r / 32 ) * 36;
			break;
		case COLOR_RESOLUTION_RGB9:
			b = ( b / 32 ) * 36;
			g = ( g / 32 ) * 36;
			r = ( r / 32 ) * 36;
			break;
		case COLOR_RESOLUTION_RGB12:
			b = ( b / 16 ) * 17;
			g = ( g / 16 ) * 17;
			r = ( r / 16 ) * 17;
			break;
		case COLOR_RESOLUTION_RGB15:
			b = ( b / 8 ) * 8;
			g = ( g / 8 ) * 8;
			r = ( r / 8 ) * 8;
			break;
		case COLOR_RESOLUTION_RGB16:
			b = ( b / 8 ) * 8;
			g = ( g / 4 ) * 4;
			r = ( r / 8 ) * 8;
			break;
		case COLOR_RESOLUTION_RGB18:
			b = ( b / 4 ) * 4;
			g = ( g / 4 ) * 4;
			r = ( r / 4 ) * 4;
			break;
		case COLOR_RESOLUTION_RGB24:
			break;
		}
	return ( b << 16 ) | ( g << 8 ) | ( r );
	}

int app_proc( app_t* app, void* user_data ) 
	{
	app_proc_data_t* app_proc_data = (app_proc_data_t*) user_data;
	crtemu_t* crtemu = crtemu_create( app_proc_data->memctx );
	
	
	app_interpolation( app, APP_INTERPOLATION_NONE );
	app_title( app, "Pixie" );

	static u32 frame[ CRT_FRAME_WIDTH * CRT_FRAME_HEIGHT ];
	if( crtemu )
		{
		crt_frame( frame );
		crtemu_frame( crtemu, frame, CRT_FRAME_WIDTH, CRT_FRAME_HEIGHT ); 
		}

	size_t screen_xbgr_capacity = math_util::pow2_ceil( (u32) 4 * 1024 * 1024 );
	APP_U32* screen_xbgr = (APP_U32*) TRACKED_MALLOC( app_proc_data->memctx, screen_xbgr_capacity );
	memset( screen_xbgr, 0, screen_xbgr_capacity );

	// frame queue
	int const FRAME_DATA_BUFFER_COUNT = 2;
	frame_data_t* frame_data_slots = (frame_data_t*) TRACKED_MALLOC( app_proc_data->memctx, sizeof( frame_data_t) * FRAME_DATA_BUFFER_COUNT );
	memset( frame_data_slots, 0, sizeof( frame_data_t ) * FRAME_DATA_BUFFER_COUNT );
	for( int i = 0; i < FRAME_DATA_BUFFER_COUNT; ++i )
		{
		frame_data_slots[ i ].from_update_thread.capacity = math_util::pow2_ceil( (u32) 1024 * 1024 );
		frame_data_slots[ i ].from_update_thread.storage = 
			TRACKED_MALLOC( app_proc_data->memctx, frame_data_slots[ i ].from_update_thread.capacity );
		frame_data_slots[ i ].from_app_thread.capacity = math_util::pow2_ceil( (u32) 64 * 1024 );
		frame_data_slots[ i ].from_app_thread.storage = 
			TRACKED_MALLOC( app_proc_data->memctx, frame_data_slots[ i ].from_app_thread.capacity );
		}
	
	frame_data_t* frame_data_from_app_thread_queue_storage[ FRAME_DATA_BUFFER_COUNT ];
	for( int i = 0; i < FRAME_DATA_BUFFER_COUNT; ++i ) frame_data_from_app_thread_queue_storage[ i ] = &frame_data_slots[ i ];
	thread_queue_t frame_data_from_app_thread_queue;
	thread_queue_init( &frame_data_from_app_thread_queue, FRAME_DATA_BUFFER_COUNT, (void**)&frame_data_from_app_thread_queue_storage, FRAME_DATA_BUFFER_COUNT );

	frame_data_t* frame_data_from_update_thread_queue_storage[ FRAME_DATA_BUFFER_COUNT ];
	thread_queue_t frame_data_from_update_thread_queue;
	thread_queue_init( &frame_data_from_update_thread_queue, FRAME_DATA_BUFFER_COUNT, (void**)&frame_data_from_update_thread_queue_storage, 0 );

	//audio frame queue
	int const AUDIO_FRAME_DATA_BUFFER_COUNT = 2;
	audio_frame_data_t audio_frame_data_slots[ AUDIO_FRAME_DATA_BUFFER_COUNT ];
	memset( audio_frame_data_slots, 0, sizeof( audio_frame_data_t ) * AUDIO_FRAME_DATA_BUFFER_COUNT );

	for( int i = 0; i < AUDIO_FRAME_DATA_BUFFER_COUNT; ++i )
		{
		audio_frame_data_slots[ i ].from_update_thread.commands_capacity = 1024;
		audio_frame_data_slots[ i ].from_update_thread.commands = (audio_command_t*) TRACKED_MALLOC( 
			app_proc_data->memctx, audio_frame_data_slots[ i ].from_update_thread.commands_capacity * sizeof( audio_command_t ) );

		audio_frame_data_slots[ i ].from_audio_thread.finished_capacity = 1024;
		audio_frame_data_slots[ i ].from_audio_thread.finished = (finished_audio_t*) TRACKED_MALLOC( 
			app_proc_data->memctx, audio_frame_data_slots[ i ].from_audio_thread.finished_capacity * sizeof( finished_audio_t ) );
		
		audio_frame_data_slots[ i ].from_audio_thread.positions_capacity = 1024;
		audio_frame_data_slots[ i ].from_audio_thread.positions = (audio_position_t*) TRACKED_MALLOC( 
			app_proc_data->memctx, audio_frame_data_slots[ i ].from_audio_thread.positions_capacity * sizeof( audio_position_t ) );
		}
	
	audio_frame_data_t* audio_frame_data_from_audio_thread_queue_storage[ AUDIO_FRAME_DATA_BUFFER_COUNT ];
	for( int i = 0; i < AUDIO_FRAME_DATA_BUFFER_COUNT - 1; ++i ) audio_frame_data_from_audio_thread_queue_storage[ i ] = &audio_frame_data_slots[ i ];
	thread_queue_t audio_frame_data_from_audio_thread_queue;
	thread_queue_init( &audio_frame_data_from_audio_thread_queue, AUDIO_FRAME_DATA_BUFFER_COUNT, (void**)&audio_frame_data_from_audio_thread_queue_storage, AUDIO_FRAME_DATA_BUFFER_COUNT - 1 );

	audio_frame_data_t* audio_frame_data_from_update_thread_queue_storage[ AUDIO_FRAME_DATA_BUFFER_COUNT ];
	audio_frame_data_from_update_thread_queue_storage[ 0 ] = &audio_frame_data_slots[ AUDIO_FRAME_DATA_BUFFER_COUNT - 1 ];

	thread_queue_t audio_frame_data_from_update_thread_queue;
	thread_queue_init( &audio_frame_data_from_update_thread_queue, AUDIO_FRAME_DATA_BUFFER_COUNT, (void**)&audio_frame_data_from_update_thread_queue_storage, 1 );

	// audio sys
	thread_mutex_t audiosys_mutex;
	thread_mutex_init( &audiosys_mutex );
	
	thread_mutex_t audio_resource_mutex;
	thread_mutex_init( &audio_resource_mutex );

	thread_signal_t audio_thread_ended_signal;
	thread_signal_init( &audio_thread_ended_signal );

	audiosys_t* audiosys = audiosys_create( AUDIOSYS_DEFAULT_VOICE_COUNT, AUDIOSYS_DEFAULT_BUFFERED_SAMPLE_PAIRS_COUNT, AUDIOSYS_FEATURES_ALL, app_proc_data->memctx );
	
	// create update thread
	update_thread_data_t update_thread_data;
	update_thread_data.exit_flag = false;
	update_thread_data.app_proc_data = app_proc_data;
	update_thread_data.frame_data_from_app_thread_queue = &frame_data_from_app_thread_queue;
	update_thread_data.frame_data_from_update_thread_queue = &frame_data_from_update_thread_queue;
	update_thread_data.audio_frame_data_from_audio_thread_queue = &audio_frame_data_from_audio_thread_queue;
	update_thread_data.audio_frame_data_from_update_thread_queue = &audio_frame_data_from_update_thread_queue;
	update_thread_data.audio_thread_ended_signal = &audio_thread_ended_signal;
	update_thread_data.displays = app_displays( app );

	thread_ptr_t update_thread = thread_create( update_thread_proc, &update_thread_data, 0, THREAD_STACK_SIZE_DEFAULT );
	
	// create audio thread
	audio_thread_data_t audio_thread_data;
	audio_thread_data.app_proc_data = app_proc_data;
	audio_thread_data.exit_flag = false;
	audio_thread_data.audiosys = audiosys;
	audio_thread_data.audio_frame_data_from_audio_thread_queue = &audio_frame_data_from_audio_thread_queue;
	audio_thread_data.audio_frame_data_from_update_thread_queue = &audio_frame_data_from_update_thread_queue;
	audio_thread_data.audio_thread_ended_signal = &audio_thread_ended_signal;
	thread_ptr_t audio_thread = thread_create( audio_thread_proc, &audio_thread_data, 0, THREAD_STACK_SIZE_DEFAULT );

	app_sound( app, 4410, sound_callback, audiosys );

	color_resolution_t color_res = COLOR_RESOLUTION_RGB24;

	char title[ 256 ];
	strcpy( title, "Pixie" );
	app_screenmode_t screenmode = APP_SCREENMODE_FULLSCREEN;

	app_screenmode( app, screenmode );

	bool use_crt = false;
	int previous_window_width = app_window_width( app );
	int previous_window_height = app_window_height( app );

	u32 mouse_pointer_scaled[ 256 * 256 ];  
	mouse_pointer_t mouse_pointer;
	init_default_mouse_pointer( &mouse_pointer );
	
	u64 time_start = app_time_count( app );

	frametimer_t* frametimer = frametimer_create( app_proc_data->memctx );
	frametimer_lock_rate( frametimer, 60 );

	int xbgr_width = 0;
	int xbgr_height = 0;

	bool exit_flag = false;
	bool update_producing_frames = false;
	
	// input/render loop
	while( !exit_flag ) 
		{       
		bool exit_requested = false;
		if( update_producing_frames )
			{
			if( app_yield( app ) == APP_STATE_EXIT_REQUESTED ) 
				exit_requested = true;
			}

		int window_width = app_window_width( app );
		int window_height = app_window_height( app );

		// get a frame data buffer from update thread
		frame_data_t* frame_data = (frame_data_t*) thread_queue_consume( &frame_data_from_update_thread_queue, 0 );
		if( !frame_data ) goto skip_frame;
		update_producing_frames = true;

		int screen_width = frame_data->from_update_thread.screen_width;
		int screen_height = frame_data->from_update_thread.screen_height;
		int border_width = frame_data->from_update_thread.border_width;
		int border_height = frame_data->from_update_thread.border_height;

		xbgr_width = screen_width + border_width * 2;
		xbgr_height = screen_height + border_height * 2;

				
		
		// read mouse pointer and crtemu
		mouse_pointer = frame_data->from_update_thread.mouse_pointer;
		bool reapply_mouse_pointer = mouse_pointer.changed;
		if( frame_data->from_update_thread.use_crtmode != use_crt )
			{
			use_crt = frame_data->from_update_thread.use_crtmode;
			reapply_mouse_pointer = true;
			}
		if( window_width != previous_window_width || window_height != previous_window_height )
			{
			reapply_mouse_pointer = true;
			previous_window_width = window_width;
			previous_window_height = window_height;
			}

		if( frame_data->from_update_thread.exit_flag ) exit_flag = true;

		// read input queue
		app_input_t input = app_input( app );

		size_t required_capacity = input.count * sizeof( app_input_event_t );       
		if( frame_data->from_app_thread.capacity < required_capacity )
			{
			frame_data->from_app_thread.capacity = math_util::pow2_ceil( (u32) required_capacity );
			TRACKED_FREE( app_proc_data->memctx, frame_data->from_app_thread.storage );
			frame_data->from_app_thread.storage = TRACKED_MALLOC( app_proc_data->memctx, 
				frame_data->from_app_thread.capacity );
			}

		frame_data->from_app_thread.input_events = (app_input_event_t*) frame_data->from_app_thread.storage;
		memcpy( frame_data->from_app_thread.input_events, input.events, sizeof( app_input_event_t ) * input.count );
		frame_data->from_app_thread.input_events_count = input.count;
		
		// transform screen coordinates
		for( int i = 0; i < input.count; ++i )
			{
			app_input_event_t* event = &frame_data->from_app_thread.input_events[ i ];
			switch( event->type )
				{
				case APP_INPUT_MOUSE_MOVE:
					{
					int width = screen_width + border_width * 2;
					int height = screen_height + border_height * 2;
					if( crtemu && use_crt )
						crtemu_coordinates_window_to_bitmap( crtemu, width, height, &event->data.mouse_pos.x, &event->data.mouse_pos.y );
					else
						app_coordinates_window_to_bitmap( app, width, height, &event->data.mouse_pos.x, &event->data.mouse_pos.y );
					} break;
				case APP_INPUT_TABLET:
					{
					int width = screen_width + border_width * 2;
					int height = screen_height + border_height * 2;
					if( crtemu && use_crt )
						crtemu_coordinates_window_to_bitmap( crtemu, width, height, &event->data.tablet.x, &event->data.tablet.y );
					else
						app_coordinates_window_to_bitmap( app, width, height, &event->data.tablet.x, &event->data.tablet.y );
					} break;
				case APP_INPUT_KEY_DOWN:
				case APP_INPUT_KEY_UP:
				case APP_INPUT_DOUBLE_CLICK:
				case APP_INPUT_CHAR: 
				case APP_INPUT_MOUSE_DELTA:
				case APP_INPUT_SCROLL_WHEEL:
				default:
					break;
				}
			}
		
		if( frame_data->from_update_thread.color_res != color_res )
			color_res = frame_data->from_update_thread.color_res;

		// set screen mode
		if( frame_data->from_update_thread.screenmode != screenmode )
			{
			screenmode = frame_data->from_update_thread.screenmode;
			app_screenmode( app, screenmode );
			}

		// set title
		if( strcmp( frame_data->from_update_thread.title, title ) != 0 )
			{
			strcpy( title, frame_data->from_update_thread.title );
			app_title( app, title );
			}

		// set window pos           
		if( frame_data->from_update_thread.win_pos_changed )
			{
			frame_data->from_update_thread.win_pos_changed = false;
			app_window_pos( app, frame_data->from_update_thread.win_pos_x, frame_data->from_update_thread.win_pos_y );
			}
		else
			{
			frame_data->from_app_thread.win_pos_x = app_window_x( app );
			frame_data->from_app_thread.win_pos_y = app_window_y( app );
			}

		// set window size
		if( frame_data->from_update_thread.win_size_changed )
			{
			frame_data->from_update_thread.win_size_changed = false;
			app_window_size( app, frame_data->from_update_thread.win_w, frame_data->from_update_thread.win_h );
			}
		else
			{
			frame_data->from_app_thread.win_w = app_window_width( app );
			frame_data->from_app_thread.win_h = app_window_height( app );
			}

		// apply mouse pointer
		if( reapply_mouse_pointer )
			{
			if( use_crt ) 
				{
				app_pointer( app, 0, 0, 0, 0, 0 );
				}
			else
				{
				if( mouse_pointer.auto_scale )
					{
					int pixel_scale = window_width / xbgr_width < window_height / xbgr_height ? window_width / xbgr_width : window_height / xbgr_height;
					int new_width = mouse_pointer.width * pixel_scale;
					int new_height = mouse_pointer.height * pixel_scale;
					while( ( new_width > 256 || new_height > 256 ) && pixel_scale > 1 )
						{
						--pixel_scale;
						new_width = mouse_pointer.width * pixel_scale;
						new_height = mouse_pointer.height * pixel_scale;
						}
					
					for( int y = 0; y < mouse_pointer.height; ++y )
						{
						for( int x = 0; x < mouse_pointer.width; ++x )
							{                       
							u32 c = mouse_pointer.pixels[ x + y * mouse_pointer.width ];            
							for( int v = 0; v < pixel_scale; ++v )
								{
								for( int h = 0; h < pixel_scale; ++h )
									{
									int ofs = ( x * pixel_scale + h ) + ( y * pixel_scale + v ) * new_width;
									mouse_pointer_scaled[ ofs ] = c;
									}
								}                               
							}
						}

					app_pointer( app, new_width, new_height, mouse_pointer_scaled, 
						mouse_pointer.hotspot_x * pixel_scale, 
						mouse_pointer.hotspot_y * pixel_scale);
				
					}
				else
					{
					app_pointer( app, 
						mouse_pointer.width, 
						mouse_pointer.height, 
						mouse_pointer.pixels, 
						mouse_pointer.hotspot_x, 
						mouse_pointer.hotspot_y
						);
					}
				}
			}


		// set mouse pos
		if( frame_data->from_update_thread.mouse_pos_changed )
			{
			int width = screen_width + border_width * 2;
			int height = screen_height + border_height * 2;
			if( crtemu && use_crt )
				crtemu_coordinates_bitmap_to_window( crtemu, width, height, &frame_data->from_update_thread.mouse_set_x, &frame_data->from_update_thread.mouse_set_y );
			else
				app_coordinates_bitmap_to_window( app, width, height, &frame_data->from_update_thread.mouse_set_x, &frame_data->from_update_thread.mouse_set_y );
			app_pointer_pos( app, frame_data->from_update_thread.mouse_set_x, frame_data->from_update_thread.mouse_set_y );
			}

		// set mouse limit
		if(frame_data->from_update_thread.mouse_limit_changed )
			{
			if( frame_data->from_update_thread.mouse_limit_enabled )
				{               
				int width = screen_width + border_width * 2;
				int height = screen_height + border_height * 2;
				if( crtemu && use_crt )
					{
					crtemu_coordinates_bitmap_to_window( crtemu, width, height, &frame_data->from_update_thread.mouse_limit_x1, &frame_data->from_update_thread.mouse_limit_y1 );
					crtemu_coordinates_bitmap_to_window( crtemu, width, height, &frame_data->from_update_thread.mouse_limit_x2, &frame_data->from_update_thread.mouse_limit_y2 );
					}
				else
					{
					app_coordinates_bitmap_to_window( app, width, height, &frame_data->from_update_thread.mouse_limit_x1, &frame_data->from_update_thread.mouse_limit_y1 );
					app_coordinates_bitmap_to_window( app, width, height, &frame_data->from_update_thread.mouse_limit_x2, &frame_data->from_update_thread.mouse_limit_y2 );
					}
				app_pointer_limit( app, frame_data->from_update_thread.mouse_limit_x1, frame_data->from_update_thread.mouse_limit_y1, 
					frame_data->from_update_thread.mouse_limit_x2 - frame_data->from_update_thread.mouse_limit_x1, frame_data->from_update_thread.mouse_limit_y2 - frame_data->from_update_thread.mouse_limit_y1 );
				}
			else
				{
				app_pointer_limit_off( app );       
				}
			}

		frame_data->from_app_thread.exit_requested = exit_requested;
		
		int splits_count = frame_data->from_update_thread.splits_count;
		int cpu_bars_count = frame_data->from_update_thread.cpu_bars_count;
		

		size_t required_xbgr_capacity =  xbgr_width * xbgr_height * sizeof( u32 );
		if( screen_xbgr_capacity < required_xbgr_capacity )
			{
			screen_xbgr_capacity = math_util::pow2_ceil( (u32) required_xbgr_capacity );
			TRACKED_FREE( app_proc_data->memctx, screen_xbgr );
			screen_xbgr = (APP_U32*) TRACKED_MALLOC( app_proc_data->memctx, screen_xbgr_capacity );
			}

		// render   
		{
			u8* screen_copy = (u8*) frame_data->from_update_thread.storage;
			rgb* pal_copy = (rgb*)( screen_copy + screen_width * screen_height ); 
			internals_t::palette_split_t* splits_copy = (internals_t::palette_split_t*)( pal_copy + 256 ); 
			internals_t::cpu_bar_t* cpu_bars_copy = (internals_t::cpu_bar_t*)( splits_copy + splits_count ); 

			u64 freq = app_time_freq( app );
			u64 ticks_per_scanline = freq / ( 60 * ( xbgr_height == 0 ? 1 : xbgr_height ) );
		
			u64 cpu_bars_start_count = cpu_bars_count > 0 ? cpu_bars_copy[ 0 ].counter : 0;
			bool cpu_bar_enabled = false;
			int cpu_bar_index = 1;
			rgb cpu_bar_color( 0, 0, 0 );

			for( int i = 0; i < cpu_bars_count; ++i )
				cpu_bars_copy[ i ].counter = ( cpu_bars_copy[ i ].counter - cpu_bars_start_count ) / ticks_per_scanline;

			bool cpu_overload = false;        
			if( cpu_bars_count > 0 && cpu_bars_copy[ cpu_bars_count - 1 ].counter > (APP_U64) xbgr_height )
				{
				cpu_overload = true;
				cpu_bar_enabled = true;
				cpu_bar_color = cpu_bars_copy[ ( (u8) cpu_bars_start_count ) % cpu_bars_count ].color;
				}


			u32 palette[ 256 ];
			for( int i = 0; i < 256; ++i ) palette[ i ] = apply_color_res( pal_copy[ i ], color_res );

			int ysplit = 0;
			for( int y = 0; y < xbgr_height; ++y )
				{        
				if( ysplit < splits_count ) 
					{
					internals_t::palette_split_t* split = &splits_copy[ ysplit ];
					if( y == split->ypos )
						{
						++ysplit;
						for( int i = 0; i < 256; ++i ) palette[ i ] = apply_color_res( split->palette[ i ], color_res );
						}
					}

				if( !cpu_overload && cpu_bar_index < cpu_bars_count )
					{
					internals_t::cpu_bar_t* bar = &cpu_bars_copy[ cpu_bar_index ];
					while( cpu_bar_index < cpu_bars_count && y == (int) bar->counter )
						{
						cpu_bar_enabled = bar->enabled;
						cpu_bar_color = bar->color;
						++cpu_bar_index;
						if( cpu_bar_index < cpu_bars_count )
							bar = &cpu_bars_copy[ cpu_bar_index ];
						}
					}

				if( cpu_bar_enabled )
					{
					for( int x = 0; x < border_width; ++x )
						{
						int ofs = x + y * xbgr_width;
						screen_xbgr[ ofs ] = cpu_bar_color;
						}
					}
				else
					{
					for( int x = 0; x < border_width; ++x )
						{
						int ofs = x + y * xbgr_width;
						screen_xbgr[ ofs ] = palette[ 0 ];
						}
					}

				if( y > border_height && y < xbgr_height - border_height )
					{
					if( cpu_bar_enabled )
						{
						for( int x = 0; x < screen_width; ++x )
							{
							int ofs = border_width + x + y * xbgr_width;
							int index = screen_copy[ x + ( y - border_height ) * screen_width ];
							screen_xbgr[ ofs ] = index == 0 ? cpu_bar_color : palette[ index ];
							}
						}
					else
						{
						for( int x = 0; x < screen_width; ++x )
							{
							int ofs = border_width + x + y * xbgr_width;
							screen_xbgr[ ofs ] = palette[ screen_copy[ x + ( y - border_height ) * screen_width ] ];
							}
						}
					}
				else
					{
					if( cpu_bar_enabled )
						{
						for( int x = 0; x < screen_width; ++x )
							{
							int ofs = border_width + x + y * xbgr_width;
							screen_xbgr[ ofs ] = cpu_bar_color;
							}
						}
					else
						{
						for( int x = 0; x < screen_width; ++x )
							{
							int ofs = border_width + x + y * xbgr_width;
							screen_xbgr[ ofs ] = palette[ 0 ];
							}
						}
					}
				if( cpu_bar_enabled )
					{
					for( int x = 0; x < border_width; ++x )
						{
						int ofs = border_width + screen_width + x + y * xbgr_width;
						screen_xbgr[ ofs ] = cpu_bar_color;
						}
					}
				else
					{
					for( int x = 0; x < border_width; ++x )
						{
						int ofs = border_width + screen_width + x + y * xbgr_width;
						screen_xbgr[ ofs ] = palette[ 0 ];
						}
					}
				}
		}

		// send frame data to update_thread
		thread_queue_produce( &frame_data_from_app_thread_queue, frame_data, THREAD_QUEUE_WAIT_INFINITE );

	skip_frame:

		if( xbgr_width * xbgr_height <= 0 ) goto skip_render;
		int width = xbgr_width;
		int height = xbgr_height;

		u64 delta_time = app_time_count( app ) - time_start;
		u64 time_us = ( delta_time / ( app_time_freq( app ) / 1000000 ) );
		if( delta_time > 100000000000ULL )
			time_start = app_time_count( app );

		if( crtemu && use_crt )
			{            
			// render mouse pointer
			int mouse_x = app_pointer_x( app );
			int mouse_y = app_pointer_y( app );
			crtemu_coordinates_window_to_bitmap( crtemu, width, height, &mouse_x, &mouse_y );
			int x1 = mouse_x - mouse_pointer.hotspot_x;
			int y1 = mouse_y - mouse_pointer.hotspot_y;
			int x2 = x1 + mouse_pointer.width;
			int y2 = y1 + mouse_pointer.height;

			if( x1 < 0 ) x1 = 0;
			if( y1 < 0 ) y1 = 0;
			if( x2 > width ) x2 = width;
			if( y2 > height ) y2 = height;

			// save background
			APP_U32 temp[ 256 * 256 ];
			for( int y = y1; y < y2; ++y )
				for( int x = x1; x < x2; ++x )
					temp[ ( x - x1 ) + ( y - y1 ) * 256 ] = ( (APP_U32*) screen_xbgr )[ x + y * width ];

			// render pointer
			for( int y = y1; y < y2; ++y )
				for( int x = x1; x < x2; ++x )
					{
					APP_U32 c = mouse_pointer.pixels[ ( x - mouse_x + mouse_pointer.hotspot_x ) 
						+ ( y - mouse_y + mouse_pointer.hotspot_y ) * mouse_pointer.width ];
					APP_U32 a = ( c >> 24 ) & 0xff;
					if( a == 255 )
						{
						( (APP_U32*) screen_xbgr )[ x + y * width ] = c;
						}
					else if( a > 0 )
						{
						APP_U32 ia = 255 - a;
						APP_U32 d = screen_xbgr[ x + y * width ];
						APP_U32 sr = ( c >> 16 ) & 0xff;
						APP_U32 sg = ( c >>  8 ) & 0xff;
						APP_U32 sb = ( c       ) & 0xff;
						APP_U32 dr = ( d >> 16 ) & 0xff;
						APP_U32 dg = ( d >>  8 ) & 0xff;
						APP_U32 db = ( d       ) & 0xff;
						APP_U32 r = ( sr * a + dr * ia ) >> 8;
						APP_U32 g = ( sg * a + dg * ia ) >> 8;
						APP_U32 b = ( sb * a + db * ia ) >> 8;
						APP_U32 o = 0xff000000 | ( r << 16 ) | ( g << 8 ) | b;
						( (APP_U32*) screen_xbgr )[ x + y * width ] = o;
						}
					}

			// run crt shader
			crtemu_present( crtemu, time_us, screen_xbgr, width, height, 0xffffff, 0x000000 );

			// restore background
			for( int y = y1; y < y2; ++y )
				for( int x = x1; x < x2; ++x )
					( (APP_U32*) screen_xbgr )[ x + y * width ] = temp[ ( x - x1 ) + ( y - y1 ) * 256 ];
				   
			// display backbuffer
			app_present( app, 0, 0, 0, 0xffffff, 0x000000 );
			}
		else
			{
			// display backbuffer
			app_present( app, screen_xbgr, width, height, 0xffffff, 0x000000 );
			}
			
		frametimer_update( frametimer );

	skip_render:    
		;
		}

	// cleanup of app before terminating internals
	update_thread_data.exit_flag = true;    
	app_sound( app, 0, 0, 0 );
	audiosys_stop_all( audiosys );
	audio_thread_data.exit_flag = true; 

	// wait for update thread to end
	while( thread_queue_count( &frame_data_from_update_thread_queue ) ) 
		{
		frame_data_t* frame_data = (frame_data_t*) thread_queue_consume( &frame_data_from_update_thread_queue, THREAD_QUEUE_WAIT_INFINITE );
		frame_data->from_app_thread.exit_flag = true;
		thread_queue_produce( &frame_data_from_app_thread_queue, frame_data, THREAD_QUEUE_WAIT_INFINITE );
		}
	int return_value = thread_join( update_thread );

	thread_join( audio_thread );

	thread_mutex_term( &audio_resource_mutex );
	thread_mutex_term( &audiosys_mutex );
	thread_signal_term( &audio_thread_ended_signal );
	thread_queue_term( &frame_data_from_app_thread_queue );
	thread_queue_term( &frame_data_from_update_thread_queue );
	thread_queue_term( &audio_frame_data_from_audio_thread_queue );
	thread_queue_term( &audio_frame_data_from_update_thread_queue );
	frametimer_destroy( frametimer );
	audiosys_destroy( audiosys );

	for( int i = 0; i < FRAME_DATA_BUFFER_COUNT; ++i )
		{
		TRACKED_FREE( app_proc_data->memctx, frame_data_slots[ i ].from_app_thread.storage );  
		TRACKED_FREE( app_proc_data->memctx, frame_data_slots[ i ].from_update_thread.storage );  
		}

	TRACKED_FREE( app_proc_data->memctx, frame_data_slots );

	for( int i = 0; i < AUDIO_FRAME_DATA_BUFFER_COUNT; ++i )
		{
		TRACKED_FREE( app_proc_data->memctx, audio_frame_data_slots[ i ].from_audio_thread.positions );  
		TRACKED_FREE( app_proc_data->memctx, audio_frame_data_slots[ i ].from_audio_thread.finished );  
		TRACKED_FREE( app_proc_data->memctx, audio_frame_data_slots[ i ].from_update_thread.commands );  
		}    

	TRACKED_FREE( app_proc_data->memctx, screen_xbgr );
	if( crtemu ) crtemu_destroy( crtemu );

	return return_value;
	}

} /* namespace internal */ } /* namespace pixie */


//------
//  run
//------


int pixie::run( game_main_func_t game_main, void* external_memctx ) 
	{ 
	// one-time init of thread-local storage, by the first "run" call to get here
	thread_tls_t tls = thread_tls_create();
	if( !tls ) return 1;
	if( thread_atomic_ptr_compare_and_swap( &internal::internals_tls, NULL, tls ) != NULL )
		thread_tls_destroy( tls );

	// init memory allocation context
	pixie::internal::memtrack_t memtrack;
	memtrack.external_ctx = external_memctx;
	memtrack.current = 0;
	memtrack.peak = 0;
	memtrack.count = 0;

	// run app
	internal::app_proc_data_t app_proc_data;
	app_proc_data.game_main = game_main;
	app_proc_data.memctx = &memtrack;  
	return app_run( internal::app_proc, &app_proc_data, &memtrack, 0, 0 );
	}


namespace pixie { namespace internal {

struct run_async_thread_data_t
	{
	void* external_memctx;
	game_main_func_t game_main;
	};
	
	
int run_async_thread_proc( void* user_data )
	{
	run_async_thread_data_t run_async_thread_data = *(run_async_thread_data_t*) user_data;
	PIXIE_FREE( run_async_thread_data.external_memctx, user_data );
	int result = run( run_async_thread_data.game_main, run_async_thread_data.external_memctx );
	return result;
	}
	
} /* namespace internal */ } /* namespace pixie */ 


pixie::async_handle pixie::run_async( game_main_func_t game_main, void* external_memctx ) 
	{ 
	internal::run_async_thread_data_t* run_async_thread_data = (internal::run_async_thread_data_t*) PIXIE_MALLOC( external_memctx, sizeof( internal::run_async_thread_data_t ) );
	run_async_thread_data->external_memctx = external_memctx;
	run_async_thread_data->game_main = game_main;
	thread_ptr_t thread_handle = thread_create( internal::run_async_thread_proc, run_async_thread_data, 0, 0 );
	async_handle handle;
	handle.thread_handle = (void*)thread_handle;
	return handle;
	}


int pixie::join_async( async_handle handle )
	{
	return thread_join( handle.thread_handle );
	}


bool pixie::is_running()
	{
	internal::internals_t* internals = internal::internals();
	return !internals->exit_flag;
	}


void pixie::wait( int jiffys )
	{
	for( int i = 0; i < jiffys; ++i )
		{   
		execute_frame();
		if( !is_running() ) return;
		}
	}


void pixie::wait( float time )
	{
	int jiffys = (int)( time * 60.0f );
	wait( jiffys );
	}


void pixie::wait_key()
	{
	while( is_running () )
		{
		execute_frame();
		for( int i = 0; i < KEYCOUNT; ++i )
			if( key_was_pressed( (key_id) i ) )
				return;
		}
	}


//------------
//  functions
//------------
   
void pixie::internal::update_color_indices( int start, rgb* colors, int count )
	{
	internal::internals_t* internals = internal::internals();
	
	rgb b = internals->palette[ internals->brightest_color ];
	rgb d = internals->palette[ internals->darkest_color ];
	
	int brightest_value = 54 * b.r + 182 * b.g + 19 * b.b;
	int darkest_value = 54 * d.r + 182 * d.g + 19 * d.b;
	for( int i = 0; i < count; ++i )
		{
		int value = 54 * colors[ i ].r + 182 * colors[ i ].g + 19 * colors[ i ].b;  
		if( value > brightest_value ) 
			{
			brightest_value = value;
			internals->brightest_color = start + i;
			}
		if( value < darkest_value ) 
			{
			darkest_value = value;
			internals->darkest_color = start + i;
			}
		}
	}    

void* pixie::internal::memctx()
	{
	return internals()->memctx;
	}


void* pixie::internal::systems_alloc( size_t size )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	return TRACKED_MALLOC( internals->memctx, size );
	}


void pixie::internal::systems_free( void* p )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	TRACKED_FREE( internals->memctx, p );
	}


strpool::internal::string_pool& pixie::internal::string_pool()
	{
	return internals()->string_pool;
	}
	
	
strpool::internal::string_pool& pixie::internal::string_id_pool()
	{
	return internals()->string_id_pool;
	}

gamestate::game_state_system<>* pixie::internal::game_states()
	{
	return &internals()->game_states;
	}


objrepo::object_repo* pixie::internal::object_repo()
	{
	internals_t* internals = internal::internals();   
	return &internals->systems;
	}
	

resources::resource_system* pixie::internal::resource_system()
	{
	internals_t* internals = internal::internals();   
	return &internals->resource_sys;
	}


void pixie::internal::add_sprite_manager( sprite_manager* manager, void (sprite_manager::*render_func)(), void (sprite_manager::*update_func)() )
	{
	internals_t* internals = internal::internals();

	internals_t::sprite_manager_entry_t& entry = internals->sprite_managers.add();
	entry.manager = manager;
	entry.render_func = render_func;
	entry.update_func = update_func;
	}


void pixie::internal::remove_sprite_manager( sprite_manager* manager )
	{
	internals_t* internals = internal::internals();
	for( int i = 0; i < internals->sprite_managers.count(); ++ i )
		{
		if( internals->sprite_managers[ i ].manager == manager )
			{
			internals->sprite_managers.remove( i );
			return;
			}
		}
	}


void pixie::mount_resources( string const& path )
	{
	internal::internals_t* internals = internal::internals();
	PIXIE_ASSERT( !internals->resources_mounted, "resources already mounted" );
	string mount_as = 
		is_folder( path.c_str() ) 
			? string( "/resources/" ) + basename( path.c_str(), extname( path.c_str() ) ) 
			: "/resources";
	assetsys_error_t error = assetsys_mount( internals->assetsys, path.c_str(), mount_as.c_str() );
	PIXIE_ASSERTF( error == ASSETSYS_SUCCESS, ( "Failed to mount resources: %s", path.c_str() ) ); (void) error;
	internals->resources_mounted = true;
	}


void pixie::mount_resources( string const& primary, string const& secondary )
	{
	internal::internals_t* internals = internal::internals();
	PIXIE_ASSERT( !internals->resources_mounted, "resources already mounted" );

	string primary_mount_as = 
		is_folder( primary.c_str() ) 
			? string( "/resources/" ) + basename( primary.c_str(), extname( primary.c_str() ) ) 
			: "/resources";
	assetsys_error_t error_primary = assetsys_mount( internals->assetsys, primary.c_str(), primary_mount_as.c_str() );

	string secondary_mount_as = 
		is_folder( secondary.c_str() ) 
			? string( "/resources/" ) + basename( secondary.c_str(), extname( secondary.c_str() ) ) 
			: "/resources";
	assetsys_error_t error_secondary = assetsys_mount( internals->assetsys, secondary.c_str(), secondary_mount_as.c_str() );

	PIXIE_ASSERTF( ( error_primary == ASSETSYS_SUCCESS || error_secondary == ASSETSYS_SUCCESS ), 
		( "Failed to mount resources: %s and %s", primary.c_str(), secondary.c_str() ) );
	(void) error_primary; (void) error_secondary;
	internals->resources_mounted = true;
	}


pixie::datetime pixie::now()
	{
	time_t t = ::time( NULL );
	struct tm* dt = ::localtime( &t );
	
	pixie::datetime result;
	result.year = dt->tm_year + 1900; 
	result.month = dt->tm_mon + 1; 
	result.day = dt->tm_mday; 
	result.hour = dt->tm_hour; 
	result.minute = dt->tm_min; 
	result.second = dt->tm_sec; 
	switch( dt->tm_wday )
		{
		case 0: result.day_of_week = DAY_SUNDAY; break;
		case 1: result.day_of_week = DAY_MONDAY; break;
		case 2: result.day_of_week = DAY_TUESDAY; break;
		case 3: result.day_of_week = DAY_WEDNESDAY; break;
		case 4: result.day_of_week = DAY_THURSDAY; break;
		case 5: result.day_of_week = DAY_FRIDAY; break;
		case 6: result.day_of_week = DAY_SATURDAY; break;
		}

	return result;
	}


pixie::i64 pixie::time() 
	{ 
	return (i64) ::time( 0 ); 
	}


int pixie::clock() 
	{ 
	internal::internals_t* internals = internal::internals();
	return internals->frame_count;
	}


float pixie::delta_time() 
	{ 
	internal::internals_t* internals = internal::internals();
	return internals->delta_time; 
	}


size_t pixie::mem_used( int* alloc_count, size_t* peak_use )
	{
	internal::internals_t* internals = internal::internals();
	pixie::internal::memtrack_t* memtrack = (pixie::internal::memtrack_t*) internals->memctx;
	if( alloc_count ) *alloc_count = memtrack->count;
	if( peak_use ) *peak_use = (size_t) memtrack->peak; 
	return (size_t) memtrack->current;
	}

void pixie::request_exit()
	{
	internal::internals_t* internals = internal::internals();
	internals->exit_requested = true;
	}

bool pixie::exit_requested()
	{
	internal::internals_t* internals = internal::internals();
	return internals->exit_requested;
	}


void pixie::cancel_exit_request()
	{
	internal::internals_t* internals = internal::internals();
	internals->exit_requested = false;
	}


void pixie::end( int return_value ) 
	{ 
	internal::internals_t* internals = internal::internals();

	internals->return_value = return_value; 
	internals->exit_flag = true; 
	}


void pixie::system() 
	{ 
	// Turn off memory leak reports for faster exit
	#ifndef NDEBUG
		int flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); // Get current flag
		flag ^= _CRTDBG_LEAK_CHECK_DF; // Turn off leak-checking bit
		_CrtSetDbgFlag( flag ); // Set flag to the new value
	#endif
	_exit( 0 );
	}


void pixie::stdprint( string format, ... )
	{
	#pragma warning( push )
	#pragma warning( disable: 4619 ) // there is no warning number '4840'
	#pragma warning( disable: 4840 ) // non-portable use of class 'strpool::string_type<pixie::internal::PIXIE_STRING_POOL>' as an argument to a variadic function
	va_list args;
	va_start( args, format );
	printf( "%s", strpool::format( format, args ).c_str() );
	va_end( args );
	#pragma warning( pop )
	}


void pixie::title( string const& text )
	{
	internal::internals_t* internals = internal::internals();
	strncpy( internals->title, text.c_str(), sizeof( internals->title ) );
	internals->title[ sizeof( internals->title ) - 1 ] = 0;
	strcpy( internals->frame_data->from_update_thread.title, internals->title );
	}


pixie::string pixie::title()
	{
	internal::internals_t* internals = internal::internals();
	string text = internals->title;
	return text;
	}


void pixie::window_pos( int x, int y ) 
	{
	internal::internals_t* internals = internal::internals();    
	internals->frame_data->from_update_thread.win_pos_x = x;
	internals->frame_data->from_update_thread.win_pos_y = y;
	internals->frame_data->from_update_thread.win_pos_changed = true;
	internals->win_pos_x = x;
	internals->win_pos_y = y;
	}


int pixie::window_x()
	{
	internal::internals_t* internals = internal::internals();
	return internals->win_pos_x;
	}
	
	
int pixie::window_y()
	{
	internal::internals_t* internals = internal::internals();
	return internals->win_pos_y;
	}


void pixie::window_size( int width, int height ) 
	{
	internal::internals_t* internals = internal::internals();    
	internals->frame_data->from_update_thread.win_w = width;
	internals->frame_data->from_update_thread.win_h = height;
	internals->frame_data->from_update_thread.win_size_changed = true;
	internals->win_w = width;
	internals->win_h = height;
	}


int pixie::window_width()
	{
	internal::internals_t* internals = internal::internals();
	return internals->win_w;
	}
	
	
int pixie::window_height()
	{
	internal::internals_t* internals = internal::internals();
	return internals->win_h;
	}


void pixie::internal::resize_screen() 
	{
	internals_t* internals = internal::internals();
	
	size_t required_capacity = 2 * internals->screen_width * internals->screen_height * sizeof( u8 );
	if( internals->screen_capacity < required_capacity )
		{
		internals->screen_capacity = math_util::pow2_ceil( (u32) required_capacity );
		TRACKED_FREE( internals->memctx, internals->screen_storage );
		internals->screen_storage = TRACKED_MALLOC( internals->memctx, internals->screen_capacity );
		memset( internals->screen_storage, 0, internals->screen_capacity );
		}
	internals->screen_pixels = (u8*)internals->screen_storage;
	internals->screen_bitmap.internal.lock_count = 0;
	internals->screen_bitmap.internal.cel_count = 1;
	internals->screen_bitmap.internal.width = internals->screen_width;
	internals->screen_bitmap.internal.height = internals->screen_height;
	internals->screen_bitmap.internal.storage = 0;
	internals->screen_bitmap.internal.cels_normal = &internals->screen_bitmap_cels;
	internals->screen_bitmap.internal.type = bitmap::internal_t::DATA_TYPE_NORMAL;
	internals->screen_bitmap.internal.cels_normal->offset_x = 0;
	internals->screen_bitmap.internal.cels_normal->offset_y = 0; 
	internals->screen_bitmap.internal.cels_normal->pitch_x = internals->screen_width; 
	internals->screen_bitmap.internal.cels_normal->pitch_y = internals->screen_height; 
	internals->screen_bitmap.internal.cels_normal->pixels = internals->screen_pixels; 
	internals->screen_bitmap.internal.cels_normal->mask = 0;
	}
	
	
void pixie::screen_size( int width, int height ) 
	{
	internal::internals_t* internals = internal::internals();
	
	if( width == internals->screen_width && height == internals->screen_height ) return;

	internals->screen_width = width;
	internals->screen_height = height;
	internal::resize_screen();
	}


int pixie::screen_width()
	{
	internal::internals_t* internals = internal::internals();
	return internals->screen_width;
	}
	
	
int pixie::screen_height()
	{
	internal::internals_t* internals = internal::internals();
	return internals->screen_height;
	}


void pixie::border_size( int width, int height ) 
	{
	internal::internals_t* internals = internal::internals();
	
	if( width == internals->border_width && height == internals->border_height ) return;

	internals->border_width = width;
	internals->border_height = height;
	internal::resize_screen();
	}


int pixie::border_width()
	{
	internal::internals_t* internals = internal::internals();
	return internals->border_width;
	}
	
	
int pixie::border_height()
	{
	internal::internals_t* internals = internal::internals();
	return internals->border_height;
	}


void pixie::fullscreen( bool use_fullscreen )
	{
	internal::internals_t* internals = internal::internals();
	internals->screenmode = use_fullscreen ? APP_SCREENMODE_FULLSCREEN : APP_SCREENMODE_WINDOW;
	internals->frame_data->from_update_thread.screenmode = internals->screenmode;
	}


bool pixie::fullscreen()
	{
	internal::internals_t* internals = internal::internals();
	return internals->screenmode == APP_SCREENMODE_FULLSCREEN;;
	}


void pixie::crt_mode( bool use_crt )
	{
	internal::internals_t* internals = internal::internals();
	internals->use_crtmode = use_crt;
	}


bool pixie::crt_mode()
	{
	internal::internals_t* internals = internal::internals();
	return internals->use_crtmode;
	}


pixie::array<pixie::display> const& pixie::displays()
	{
	internal::internals_t* internals = internal::internals();
	return internals->displays;
	}


pixie::bitmap* pixie::screen_bitmap()
	{
	internal::internals_t* internals = internal::internals();
	return &internals->screen_bitmap;

	}

	
void pixie::color_resolution( color_resolution_t res )
	{
	internal::internals_t* internals = internal::internals();
	internals->color_res = res;
	}


pixie::color_resolution_t pixie::color_resolution()
	{
	internal::internals_t* internals = internal::internals();
	return internals->color_res;
	}


pixie::rgb::rgb() : 
	r( 0 ), 
	g( 0 ), 
	b( 0 ) 
	{ } 


pixie::rgb::rgb( int r_, int g_, int b_ ) : 
	r( (u8) clamp( r_, 0, 255 ) ), 
	g( (u8) clamp( g_, 0, 255 ) ), 
	b( (u8) clamp( b_, 0, 255 ) ) 
	{ }


pixie::rgb::rgb( u32 xbgr ) : 
	r( (u8)( ( xbgr       ) & 0xff ) ), 
	g( (u8)( ( xbgr >>  8 ) & 0xff ) ), 
	b( (u8)( ( xbgr >> 16 ) & 0xff ) ) 
	{ } 


pixie::rgb::operator pixie::u32() 
	{ 
	return ( (u32) r ) | ( ( (u32) g ) << 8 ) | ( ( (u32) b ) << 16 ); 
	}


pixie::rgb::rgb( float3 rgb ) :
	r( (u8) clamp( fast_round( rgb.r() * 255.0f ), 0, 255 ) ), 
	g( (u8) clamp( fast_round( rgb.g() * 255.0f ), 0, 255 ) ), 
	b( (u8) clamp( fast_round( rgb.b() * 255.0f ), 0, 255 ) )
	{ }


pixie::rgb::operator pixie::float3() 
	{ 
	return float3( r / 255.0f, g / 255.0f, b / 255.0f ); 
	}


pixie::rgb::rgb( float4 rgb ) :
	r( (u8) clamp( fast_round( rgb.r() * 255.0f ), 0, 255 ) ), 
	g( (u8) clamp( fast_round( rgb.g() * 255.0f ), 0, 255 ) ), 
	b( (u8) clamp( fast_round( rgb.b() * 255.0f ), 0, 255 ) )
	{ }


pixie::rgb::operator pixie::float4() 
	{ 
	return float4( r / 255.0f, g / 255.0f, b / 255.0f, 0.0f ); 
	}


void pixie::default_palette()
	{
	internal::internals_t* internals = internal::internals();
	for( int i = 0; i < 256; ++i )
		{
		internals->palette[ i ].b = (u8)( internal::default_palette[ i ] & 0xff );
		internals->palette[ i ].g = (u8)( ( internal::default_palette[ i ] >> 8 ) & 0xff );
		internals->palette[ i ].r = (u8)( ( internal::default_palette[ i ] >> 16 ) & 0xff );
		}
	internal::update_color_indices( 0, internals->palette, 256 );
	}
	

void pixie::load_palette( string const& filename )
	{
	internal::internals_t* internals = internal::internals();
	load_palette( filename, internals->palette );
	internal::update_color_indices( 0, internals->palette, 256 );
	}
	
	
void pixie::load_palette( string const& filename, rgb colors[ 256 ] )   
	{
	internal::internals_t* internals = internal::internals();
	internals->palette_splits.clear();
	ref<binary> bin = bload( filename.c_str() );
	PIXIE_ASSERTF( bin, ( "Failed to load palette: %s", filename.c_str() ) );
	if( !bin ) return;
	char const header[] = "PIXIE_PAL";
	int version = 1;
	size_t expected_size = sizeof( header ) + sizeof( version ) + 256 * sizeof( u32 );
	PIXIE_ASSERTF( bin->size == expected_size, ( "Palette file corrupt: %s", filename.c_str() ) );
	if( bin->size != expected_size ) return; 
	if( memcmp( bin->data, header, sizeof( header ) ) != 0 || version != *(int*)( (u8*) bin->data + sizeof( header ) ) )
		{
		PIXIE_ASSERTF( false, ( "Palette file corrupt: %s", filename.c_str() ) );
		return;
		}
		
	u32* palette = (u32*)( (u8*) bin->data + sizeof( header ) + sizeof( version ) ); 
	for( int i = 0; i < 256; ++i )
		{
		u32 p = palette[ i ];
		rgb c;
		c.b = (u8)( ( p >> 16 ) & 0xff );
		c.g = (u8)( ( p >>  8 ) & 0xff );
		c.r = (u8)( ( p       ) & 0xff );
		colors[ i ] = c;
		}
	}


pixie::rgb const* pixie::palette()
	{
	internal::internals_t* internals = internal::internals();
	return internals->palette;
	}
	
	
void pixie::palette( rgb const* colors, int count, int start )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = 0; i < count; ++i )
		{
		if( i + start >= 0 && i + start < 256 ) internals->palette[ i + start ] = colors[ i ];
		}
	internal::update_color_indices( start, internals->palette, count );
	}
	
	
pixie::rgb pixie::palette_color( int index )
	{
	internal::internals_t* internals = internal::internals();
	if( index >= 0 && index < 256 ) return internals->palette[ index ];
	rgb c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return c;
	}

	
void pixie::palette_color( int index, rgb rgb )
	{
	internal::internals_t* internals = internal::internals();
	if( index >= 0 && index < 256 ) internals->palette[ index ]= rgb;
	internal::update_color_indices( index, internals->palette, 1 );
	}
	
	
void pixie::palette_color( int index, u8 r, u8 g, u8 b )
	{
	palette_color( index, rgb( r, g, b ) );
	}
	
	
void pixie::palette_split( int y_pos )
	{
	internal::internals_t* internals = internal::internals();
	int index = internals->palette_splits.count();
	for( int i = 0; i < internals->palette_splits.count(); ++i )
		{   
		if( internals->palette_splits[ i ].ypos == y_pos ) return;
		if( internals->palette_splits[ i ].ypos > y_pos )
			{
			index = i;
			break;
			}
		}
	internal::internals_t::palette_split_t& split = internals->palette_splits.insert( index );
	split.ypos = y_pos;
	for( int i = 0; i < 256; ++i ) split.palette[ i ] = internals->palette[ i ];
	}
	
	
void pixie::remove_palette_split( int y_pos )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = 0; i < internals->palette_splits.count(); ++i )
		{   
		if( internals->palette_splits[ i ].ypos == y_pos ) 
			{
			internals->palette_splits.remove( i );
			return;
			}
		}
	}
	
	
pixie::rgb* pixie::palette( int y_pos )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = 0; i < internals->palette_splits.count(); ++i )
		{   
		if( internals->palette_splits[ i ].ypos == y_pos ) 
			return internals->palette_splits[ i ].palette;
		}
	return 0;
	}
	
	
void pixie::palette( int y_pos, rgb const* colors, int count, int start )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = 0; i < internals->palette_splits.count(); ++i )
		{   
		if( internals->palette_splits[ i ].ypos == y_pos ) 
			{
			for( int j = 0; j < count; ++j )
				{
				if( j + start >= 0 && j + start < 256 )
					internals->palette_splits[ i ].palette[ j + start ] = colors[ j ];
				}
			return;
			}
		}
	}
	
	
pixie::rgb pixie::palette_color( int y_pos, int index)
	{
	internal::internals_t* internals = internal::internals();
	if( index >= 0 && index < 256 ) 
		{
		for( int i = 0; i < internals->palette_splits.count(); ++i )
			{   
			if( internals->palette_splits[ i ].ypos == y_pos ) 
				return internals->palette_splits[ i ].palette[ index ];
			}
		}

	rgb c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	return c;
	}
	
	
void pixie::palette_color( int y_pos, int index, rgb rgb )
	{
	internal::internals_t* internals = internal::internals();
	if( index >= 0 && index < 256 ) 
		{
		for( int i = 0; i < internals->palette_splits.count(); ++i )
			{   
			if( internals->palette_splits[ i ].ypos == y_pos ) 
				{
				internals->palette_splits[ i ].palette[ index ]  = rgb;
				break;
				}
			}
		}
	}
	

void pixie::palette_color( int y_pos, int index, u8 r, u8 g, u8 b )
	{
	palette_color( y_pos, index, rgb( r, g, b ) );
	}
	

int pixie::brightest_color() { return internal::internals()->brightest_color; }

int pixie::darkest_color() { return internal::internals()->darkest_color; }


pixie::rgb pixie::rgb9( u16 xrgb )
	{
	int r = ( ( xrgb >> 6 ) & 7 ) * 36;
	int g = ( ( xrgb >> 3 ) & 7 ) * 36;
	int b = ( ( xrgb      ) & 7 ) * 36;
	return rgb( r, g, b );
	}


pixie::rgb pixie::rgb9( u8 r, u8 g, u8 b )
	{
	return rgb( r * 36, g * 36, b * 36 );
	}


pixie::rgb pixie::rgb12( u16 xrgb )
	{
	int r = ( ( xrgb >> 8 ) & 15 ) * 17;
	int g = ( ( xrgb >> 4 ) & 15 ) * 17;
	int b = ( ( xrgb      ) & 15 ) * 17;
	return rgb( r, g, b );
	}


pixie::rgb pixie::rgb12( u8 r, u8 g, u8 b )
	{
	return rgb( r * 17, g * 17, b * 17 );
	}


pixie::rgb pixie::rgb18( u32 xrgb )
	{
	int r = (int)( ( xrgb >> 12 ) & 63 ) * 4;
	int g = (int)( ( xrgb >>  6 ) & 63 ) * 4;
	int b = (int)( ( xrgb       ) & 63 ) * 4;
	return rgb( r, g, b );
	}


pixie::rgb pixie::rgb18( u8 r, u8 g, u8 b )
	{
	return rgb( r * 4, g * 4, b * 4 );
	}


void pixie::cpu_bars_enabled( bool enabled ) { internal::internals()->cpu_bars_enabled = enabled; }


bool pixie::cpu_bars_enabled() { return internal::internals()->cpu_bars_enabled; }


void pixie::cpu_bar( rgb color )
	{
	internal::internals_t* internals = internal::internals();
	internal::internals_t::cpu_bar_t bar;
	bar.counter = app_time_count( 0 );
	bar.color = color;
	bar.enabled = true;
	internals->cpu_bars.add( bar );
	}


void pixie::cpu_bar( u8 r, u8 g, u8 b )
	{
	cpu_bar( rgb( r, g, b ) );
	}


void pixie::cpu_bar()
	{
	internal::internals_t* internals = internal::internals();
	internal::internals_t::cpu_bar_t bar;
	bar.counter = app_time_count( 0 );
	bar.color = rgb( 0, 0, 0 );
	bar.enabled = false;
	internals->cpu_bars.add( bar );
	}


bool pixie::file_exists( string const& filename )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->resources_mounted ) 
		{
		assetsys_file_t file;
		return assetsys_file( internals->assetsys, ( "/resources/" + filename ).c_str(), &file ) == ASSETSYS_SUCCESS;
		}
	else
		{
		struct stat s;
		return ( stat( filename.c_str(), &s ) == 0 );
		}
	}


namespace pixie { namespace internal {

string path_join( string const& a, string const& b )
	{
	string r = a;
	if( len( a ) > 0 && len( b ) > 0 ) r += "/";
	r += b;
	return r;
	}


} /* namespace internal */ } /* namespace pixie */



pixie::array<pixie::dir_info> pixie::dir( string const& path, bool recursive )
	{
	internal::internals_t* internals = internal::internals();
	
	array<dir_info> result;

	array<string> stack;
	stack.add( path );

	if( internals->resources_mounted ) 
		{
		while( stack.count() > 0 )
			{
			string entry = stack[ 0 ]; 
			stack.remove( 0 );

			int subdir_count = assetsys_subdir_count( internals->assetsys, ( "/resources/" + entry ).c_str() );
			for( int i = 0; i < subdir_count; ++i )
				{
				string subdir_name = assetsys_subdir_name( internals->assetsys, ( "/resources/" + entry ).c_str(), i );
				string subdir_path = internal::path_join( entry, subdir_name );
				stack.add( subdir_path );

				dir_info info;
				info.filename = recursive ? subdir_path : subdir_name;
				info.is_folder = true;
				info.size = 0;
				result.add( info );
				}

			int file_count = assetsys_file_count( internals->assetsys, ( "/resources/" + entry ).c_str() );
			for( int i = 0; i < file_count; ++i )
				{
				string file_name = assetsys_file_name( internals->assetsys, ( "/resources/" + entry ).c_str(), i );
				string file_path = internal::path_join( entry, file_name );
				assetsys_file_t file;
				assetsys_file( internals->assetsys, ( "/resources/" + file_path ).c_str(), &file );
				int file_size = assetsys_file_size( internals->assetsys, file );

				dir_info info;
				info.filename = recursive ? file_path : file_name;
				info.is_folder = false;
				info.size = (size_t) file_size;

				result.add( info );
				}

			if( !recursive ) break;
			}
		}
	else
		{
		while( stack.count() > 0 )
			{
			string entry = stack[ 0 ]; 
			stack.remove( 0 );

			dir_t* dir = dir_open( entry.c_str() );
			if( !dir ) { if( recursive ) continue; else break; }
			
			dir_entry_t* ent = dir_read( dir );
			while( ent )
				{
				if( dir_is_folder( ent ) && strcmp( dir_name( ent ), "." ) != 0 && strcmp( dir_name( ent ), ".." ) != 0 )
					{
					string subdir_name = dir_name( ent );
					string subdir_path = internal::path_join( entry, subdir_name );
					stack.add( subdir_path );

					dir_info info;
					info.filename = recursive ? subdir_path : subdir_name;
					info.is_folder = true;
					info.size = 0;
					result.add( info );
					}
				else if( dir_is_file( ent ) )
					{
					string file_name = dir_name( ent );
					string file_path = internal::path_join( entry, file_name );
					struct stat s;
					if( stat( file_path.c_str(), &s ) == 0 )
						{
						size_t file_size = (size_t)s.st_size;
	
						dir_info info;
						info.filename = recursive ? file_path : file_name;
						info.is_folder = false;
						info.size = file_size;

						result.add( info );
						}
					}

				if( !recursive ) break;
				ent = dir_read( dir );
				}
			dir_close( dir );
			}
		}

	return result;
	}


void* pixie::mem_alloc( size_t size )
	{
	internal::internals_t* internals = internal::internals();
	return TRACKED_MALLOC( internals->memctx, size );
	}


void pixie::mem_free( void* ptr )
	{
	internal::internals_t* internals = internal::internals();
	TRACKED_FREE( internals->memctx, ptr );
	}


namespace pixie { namespace internal {

void binary_delete( void* instance )
	{
	internal::internals_t* internals = internal::internals();
	TRACKED_FREE( internals->memctx, instance ); 
	}

} /* namespace internal */ } /*namespace pixie */


pixie::ref<pixie::binary> pixie::bload( string const& filename )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->resources_mounted )
		{
		assetsys_file_t file;   
		assetsys_error_t error = assetsys_file( internals->assetsys, ( "/resources/" + filename ).c_str(), &file );
		if( error != ASSETSYS_SUCCESS ) ref<binary>::ref();

		int file_size = assetsys_file_size( internals->assetsys, file );        
		void* storage = TRACKED_MALLOC( internals->memctx, sizeof( binary ) + sizeof( int ) + file_size + 1 ); // one extra for zero terminator
		void* file_data = (void*)( (uintptr_t)storage + sizeof( binary ) + sizeof( int ) );
		error = assetsys_file_load( internals->assetsys, file, 0, file_data, file_size );
		PIXIE_ASSERTF( error == ASSETSYS_SUCCESS, ( "Failed to load file: %s", filename.c_str() ) );
		if( error != ASSETSYS_SUCCESS ) 
			{
			TRACKED_FREE( internals->memctx, storage );
			return ref<binary>::ref();
			}
		*( ((char*)file_data) + file_size ) = 0; // add zero terminator in case this is a text file
		
		binary* bin = (binary*)storage;
		bin->data = (u8*)file_data;
		bin->size = (size_t)file_size;
		return refcount::make_ref( bin, internal::binary_delete, (int*)( (uintptr_t)storage + sizeof( binary ) ), 0 );
		}
	else
		{
		struct stat s;
		stat( filename.c_str(), &s );
		size_t file_size = (size_t) s.st_size;
		FILE* file = fopen( filename.c_str(), "rb" );
		PIXIE_ASSERTF( file, ( "Failed to load file: %s", filename.c_str() ) );
		if( !file ) return ref<binary>::ref();
		void* storage = TRACKED_MALLOC( internals->memctx, sizeof( binary ) + sizeof( int ) + file_size + 1 ); // one extra for zero terminator
		void* file_data = (void*)( (uintptr_t)storage + sizeof( binary ) + sizeof( int ) );
		fread( file_data, 1, file_size, file );
		fclose( file );
		*( ((char*)file_data) + file_size ) = 0; // add zero terminator in case this is a text file

		binary* bin = (binary*)storage;
		bin->data = (u8*)file_data;
		bin->size = file_size;
		return refcount::make_ref( bin, internal::binary_delete, (int*)( (uintptr_t)storage + sizeof( binary ) ), 0 );
		}       
	}

	
pixie::ref<pixie::binary> pixie::bnew( size_t size )
	{
	internal::internals_t* internals = internal::internals();
	void* storage = TRACKED_MALLOC( internals->memctx, sizeof( binary ) + sizeof( int ) + size ); 
	binary* bin = (binary*)storage;
	bin->data = (u8*)( (uintptr_t)storage + sizeof( binary ) + sizeof( int ) );
	bin->size = (size_t)size;
	return refcount::make_ref( bin, internal::binary_delete, (int*)( (uintptr_t)storage + sizeof( binary ) ), 0 );
	}


pixie::ref<pixie::binary> pixie::bresize( ref<binary> const& bin, size_t new_size )
	{
	ref<binary> new_binary = bnew( new_size );
	memcpy( new_binary->data, bin->data, new_size < bin->size ? new_size : bin->size );
	return new_binary;
	}



void pixie::bsave( void* data, size_t size, string filename )
	{
	FILE* fp = fopen( filename.c_str(), "wb" );
	fwrite( data, size, 1, fp );
	fclose( fp );
	}


void pixie::bsave( ref<binary> const& bin, string filename )
	{
	if( bin ) bsave( bin->data, bin->size, filename );
	}


namespace pixie { namespace internal {

struct binary_reader_internals_t
	{
	binary_rw_data_t data;
	binary_rw_reader_t reader;
	};

STATIC_ASSERT( sizeof( binary_reader_internals_t ) <= sizeof( binary_reader::internals_ ), "Size mismatch" );

struct binary_writer_internals_t
	{
	binary_rw_data_t data;
	binary_rw_writer_t writer;
	};

STATIC_ASSERT( sizeof( binary_writer_internals_t ) <= sizeof( binary_writer::internals_ ), "Size mismatch" );


void binary_rw_resize_func( binary_rw_data_t* bin, size_t new_size, void* resize_context )
	{
	internal::internals_t* internals = internal::internals();
	new_size = new_size <= bin->size * 2 ? bin->size * 2 : (size_t) pow2_ceil( (u32) new_size );
	void* new_data = TRACKED_MALLOC( internals->memctx, new_size );
	memcpy( new_data, bin->data, bin->size );
	TRACKED_FREE( internals->memctx, bin->data );
	bin->data = new_data;
	bin->size = new_size;
	ref<binary>* refbin = (ref<binary>*) resize_context;
	(*refbin)->data = bin->data;
	(*refbin)->size = bin->size;
	}
	
} /* namespace internal */ } /* namespace pixie */


pixie::binary_reader::binary_reader( ref<binary> const& bin )
	{
	bin_ = bin;
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	rw->data.data = bin->data;
	rw->data.size = bin->size;
	binary_rw_reader_init( &rw->reader, &rw->data );
	}


pixie::binary_reader::~binary_reader()
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	binary_rw_reader_term( &rw->reader );
	}


pixie::ref<pixie::binary> pixie::binary_reader::bin()
	{
	return bin_;
	}


void pixie::binary_reader::reset()
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	binary_rw_reader_reset( &rw->reader );
	}


void pixie::binary_reader::position( size_t pos )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	binary_rw_reader_position_set( &rw->reader, pos );
	}


size_t pixie::binary_reader::position() const
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_position( &rw->reader );
	}


// on older MSVC versions, char is same as i8
#if !defined(_MSC_VER) || _MSC_VER >= 1600 

	int pixie::binary_reader::read( char* value, int count )
		{
		internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
		return binary_rw_reader_char( &rw->reader, value, count );
		}

#endif


int pixie::binary_reader::read( bool* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_bool( &rw->reader, value, count );
	}


int pixie::binary_reader::read( i8* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_i8( &rw->reader, value, count );
	}


int pixie::binary_reader::read( i16* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_i16( &rw->reader, value, count );
	}


int pixie::binary_reader::read( i32* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_i32( &rw->reader, value, count );
	}


int pixie::binary_reader::read( i64* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_i64( &rw->reader, value, count );
	}


int pixie::binary_reader::read( u8* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_u8( &rw->reader, value, count );
	}


int pixie::binary_reader::read( u16* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_u16( &rw->reader, value, count );
	}


int pixie::binary_reader::read( u32* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_u32( &rw->reader, value, count );
	}


int pixie::binary_reader::read( u64* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_u64( &rw->reader, value, count );
	}


int pixie::binary_reader::read( float* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_float( &rw->reader, value, count );
	}


int pixie::binary_reader::read( double* value, int count )
	{
	internal::binary_reader_internals_t* rw = (internal::binary_reader_internals_t*) internals_;
	return binary_rw_reader_double( &rw->reader, value, count );
	}


pixie::binary_writer::binary_writer( ref<binary> const& bin, bool resize )
	{    
	bin_ = bin;
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	rw->data.data = bin->data;
	rw->data.size = bin->size;
	binary_rw_writer_init( &rw->writer, &rw->data, resize ? internal::binary_rw_resize_func : 0, resize ? &bin_ : 0 );
	resize_ = resize;
	}


pixie::binary_writer::~binary_writer()
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	binary_rw_writer_term( &rw->writer );
	}


pixie::ref<pixie::binary> pixie::binary_writer::bin()
	{
	return bin_;
	}


void pixie::binary_writer::reset()
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	binary_rw_writer_reset( &rw->writer );
	}


void pixie::binary_writer::position( size_t pos )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	binary_rw_writer_position_set( &rw->writer, pos );
	}


size_t pixie::binary_writer::position() const
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_position( &rw->writer );
	}
	

// on older MSVC versions, char is same as i8
#if !defined(_MSC_VER) || _MSC_VER >= 1600 

	int pixie::binary_writer::write( char const* value, int count )
		{
		internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
		return binary_rw_writer_char( &rw->writer, value, count );
		}
	
#endif


int pixie::binary_writer::write( bool const* value, int count ) 
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_bool( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( i8 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_i8( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( i16 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_i16( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( i32 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_i32( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( i64 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_i64( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( u8 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_u8( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( u16 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_u16( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( u32 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_u32( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( u64 const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_u64( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( float const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_float( &rw->writer, value, count );
	}
	

int pixie::binary_writer::write( double const* value, int count )
	{
	internal::binary_writer_internals_t* rw = (internal::binary_writer_internals_t*) internals_;
	return binary_rw_writer_double( &rw->writer, value, count );
	}
	

pixie::ini_file pixie::ini_load( ref<binary> const& bin )
	{
	internal::internals_t* internals = internal::internals();
	ini_t* in = ::ini_load( (char const*) bin->data, internals->memctx );
	
	ini_file ini;
	for( int i = 0; i < ini_property_count( in, INI_GLOBAL_SECTION ); ++i )
		ini.global[ ini_property_name( in, INI_GLOBAL_SECTION, i ) ] = ini_property_value( in, INI_GLOBAL_SECTION, i );

	for( int j = 1; j < ini_section_count( in ); ++j )
		{
		ini_section& section = ini.sections[ ini_section_name( in, j ) ];
		for( int i = 0; i < ini_property_count( in, j ); ++i )
			section[ ini_property_name( in, j, i ) ] = ini_property_value( in, j, i );
		}

	ini_destroy( in );
	return ini;
	}


pixie::ini_file pixie::ini_load( string const& filename )
	{
	return ini_load( bload( filename ) );
	}


pixie::ref<pixie::binary> pixie::ini_save( ini_file const& ini )
	{
	internal::internals_t* internals = internal::internals();
	ini_t* out = ini_create( internals->memctx );
	
	for( int i = 0; i < ini.global.count(); ++i )
		{
		string_id key = ini.global.key( i );
		string const& item = ini.global.item( i );
		ini_property_add( out, INI_GLOBAL_SECTION, key.c_str(), key.length(), item.c_str(),item.length() );
		}

	for( int j = 0; j < ini.sections.count(); ++j )
		{
		string_id const& name = ini.sections.key( j );
		int section_index = ini_section_add( out, name.c_str(), name.length() );
		
		ini_section const& section = ini.sections.item( j );
		for( int i = 0; i < section.count(); ++i )
			{
			string_id key = section.key( i );
			string item = section.item( i );
			ini_property_add( out, section_index, key.c_str(), key.length(), item.c_str(),item.length() );
			}
		}

	int size = ::ini_save( out, 0, 0 );
	ref<binary> bin = bnew( (size_t) size );
	::ini_save( out, (char*) bin->data, (int) bin->size );
	ini_destroy( out );
	--bin->size; // Remove null terminator
	return bin;
	}


void pixie::ini_save( ini_file const& ini, string const& filename )
	{
	bsave( ini_save( ini ), filename );
	}


int pixie::abs( int x )
	{
	return x < 0 ? -x : x;
	}


int pixie::min( int x, int y )
	{
	return x < y ? x : y;
	}


int pixie::max( int x, int y )
	{
	return x > y ? x : y;
	}


int pixie::clamp( int x, int min_val, int max_val )
	{
	return x > max_val ? max_val : x < min_val ? min_val : x;
	}


void pixie::mouse_pointer( pixie::bitmap const* bitmap, int hotspot_x, int hotspot_y )
	{
	if( !bitmap ) return mouse_pointer( 0, 0, 0, 0, hotspot_x, hotspot_y );
	bitmap::lock_data lock;
	((pixie::bitmap*)bitmap)->lock( &lock );
	if( lock.pixels ) mouse_pointer( lock.pixels, lock.mask, lock.pitch_x, lock.pitch_y, hotspot_x, hotspot_y );
	((pixie::bitmap*)bitmap)->unlock();
	}


void pixie::mouse_pointer( u8 const* pixels, u8 const* mask, int width, int height, int hotspot_x, int hotspot_y )
	{
	internal::internals_t* internals = internal::internals();
	int w = width > 256 ? 256 : width;
	int h = height > 256 ? 256 : height;
	for( int y = 0; y < h; ++y )
		{
		for( int x = 0; x < w; ++x )
			{
			int p = pixels[ x + y * width ];            
			u32 c = (u32)( internals->palette[ p ].r | ( internals->palette[ p ].g << 8 ) | ( internals->palette[ p ].b << 16 ) );
			if( mask ) c |= ( mask[ x + y * width ] ) << 24;
			else c |= p == 0 ? 0 : 0xff000000;
			internals->mouse_pointer.pixels[ x + y * w ] = c;
			}
		}
	internals->mouse_pointer.width = w;
	internals->mouse_pointer.height = h;
	internals->mouse_pointer.hotspot_x = hotspot_x;
	internals->mouse_pointer.hotspot_y = hotspot_y;
	internals->mouse_pointer.changed = true;
	}


int pixie::mouse_x()
	{
	internal::internals_t* internals = internal::internals();
	return internals->mouse_x - internals->border_width;
	}


int pixie::mouse_y()
	{
	internal::internals_t* internals = internal::internals();
	return internals->mouse_y - internals->border_height;
	}


void pixie::mouse_position( int x, int y )
	{
	internal::internals_t* internals = internal::internals();
	internals->frame_data->from_update_thread.mouse_set_x = x;
	internals->frame_data->from_update_thread.mouse_set_y = y;
	internals->frame_data->from_update_thread.mouse_pos_changed = true;
	internals->mouse_x = x;
	internals->mouse_y = y;
	}


void pixie::limit_mouse( int x1, int y1, int x2, int y2 )
	{
	internal::internals_t* internals = internal::internals();
	internals->frame_data->from_update_thread.mouse_limit_changed = true;
	internals->frame_data->from_update_thread.mouse_limit_enabled = true;
	internals->frame_data->from_update_thread.mouse_limit_x1 = x1;
	internals->frame_data->from_update_thread.mouse_limit_y1 = y1;
	internals->frame_data->from_update_thread.mouse_limit_x2 = x2;
	internals->frame_data->from_update_thread.mouse_limit_y2 = y2;  
	internals->mouse_limit_enabled = true;
	internals->mouse_limit_x1 = x1;
	internals->mouse_limit_y1 = y1;
	internals->mouse_limit_x2 = x2;
	internals->mouse_limit_y2 = y2; 
	}


void pixie::limit_mouse()
	{
	internal::internals_t* internals = internal::internals();
	internals->frame_data->from_update_thread.mouse_limit_changed = true;
	internals->frame_data->from_update_thread.mouse_limit_enabled = false;
	internals->mouse_limit_enabled = false;
	}


void pixie::auto_scale_mouse_pointer( bool auto_scale )
	{
	internal::internals_t* internals = internal::internals();
	internals->mouse_pointer.auto_scale = auto_scale;
	internals->mouse_pointer.changed = true;
	}


bool pixie::auto_scale_mouse_pointer()
	{
	internal::internals_t* internals = internal::internals();
	return internals->mouse_pointer.auto_scale;
	}


int pixie::pen_x()
	{   
	internal::internals_t* internals = internal::internals();
	return internals->pen_x - internals->border_width;
	}


int pixie::pen_y()
	{   
	internal::internals_t* internals = internal::internals();
	return internals->pen_y - internals->border_height;
	}
	
	
float pixie::pen_pressure()
	{
	internal::internals_t* internals = internal::internals();
	return internals->pen_pressure;
	}


void pixie::time_event( event_handler* handler, float seconds, string_id const& event_id, void* user_data )
	{
	internal::internals_t* internals = internal::internals();
	internal::time_event_t& event = internals->time_events.add();
	event.handler = handler;
	event.seconds = seconds;
	event.repeat = 0.0f;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::repeating_time_event( event_handler* handler, float seconds, string_id const& event_id, void* user_data )
	{
	internal::internals_t* internals = internal::internals();
	internal::time_event_t& event = internals->time_events.add();
	event.handler = handler;
	event.seconds = seconds;
	event.repeat = seconds;
	event.event_id = event_id;
	event.user_data = user_data;
	}


bool pixie::gamepad_connected( int pad_index )
	{
	internal::internals_t* internals = internal::internals();
	if( pad_index < 0 || pad_index >= sizeof( internals->gamepad_data ) / sizeof( *internals->gamepad_data ) ) return false;
	return internals->gamepad_data[ pad_index ].result == GAMEPAD_RESULT_OK;
	}


float pixie::gamepad_axis( int pad_index, gamepadaxis_id axis )
	{
	if( !gamepad_connected( pad_index ) ) return 0.0f;
	internal::internals_t* internals = internal::internals();
	switch( axis )
		{   
		case GAMEPADAXIS_LEFT_TRIGGER: return internals->gamepad_data[ pad_index ].state.trigger_left / 255.0f;
		case GAMEPADAXIS_RIGHT_TRIGGER: return internals->gamepad_data[ pad_index ].state.trigger_right / 255.0f;  
		case GAMEPADAXIS_LEFTSTICK_X: return internals->gamepad_data[ pad_index ].state.stick_left_x / 32767.0f;  
		case GAMEPADAXIS_LEFTSTICK_Y: return internals->gamepad_data[ pad_index ].state.stick_left_y / 32767.0f;    
		case GAMEPADAXIS_RIGHTSTICK_X: return internals->gamepad_data[ pad_index ].state.stick_right_x / 32767.0f;    
		case GAMEPADAXIS_RIGHTSTICK_Y: return internals->gamepad_data[ pad_index ].state.stick_right_y / 32767.0f;    
		}
	return 0.0f;
	}


bool pixie::gamepad_is_down( int pad_index, gamepadbutton_id button )
	{
	if( !gamepad_connected( pad_index ) ) return false;
	internal::internals_t* internals = internal::internals();
	GAMEPAD_U16 state = internals->gamepad_data[ pad_index ].state.buttons;
	switch( button )
		{   
		case GAMEPADBUTTON_DPAD_UP: return ( state & GAMEPAD_DPAD_UP ) != 0; 
		case GAMEPADBUTTON_DPAD_DOWN: return ( state & GAMEPAD_DPAD_DOWN ) != 0; 
		case GAMEPADBUTTON_DPAD_LEFT: return ( state & GAMEPAD_DPAD_LEFT ) != 0; 
		case GAMEPADBUTTON_DPAD_RIGHT: return ( state & GAMEPAD_DPAD_RIGHT ) != 0; 
		case GAMEPADBUTTON_START: return ( state & GAMEPAD_START ) != 0; 
		case GAMEPADBUTTON_BACK: return ( state & GAMEPAD_BACK ) != 0; 
		case GAMEPADBUTTON_STICK_LEFT: return ( state & GAMEPAD_STICK_LEFT ) != 0; 
		case GAMEPADBUTTON_STICK_RIGHT: return ( state & GAMEPAD_STICK_RIGHT ) != 0; 
		case GAMEPADBUTTON_SHOULDER_LEFT: return ( state & GAMEPAD_SHOULDER_LEFT ) != 0; 
		case GAMEPADBUTTON_SHOULDER_RIGHT: return ( state & GAMEPAD_SHOULDER_RIGHT ) != 0; 
		case GAMEPADBUTTON_A: return ( state & GAMEPAD_A ) != 0; 
		case GAMEPADBUTTON_B: return ( state & GAMEPAD_B ) != 0; 
		case GAMEPADBUTTON_X: return ( state & GAMEPAD_X ) != 0; 
		case GAMEPADBUTTON_Y: return ( state & GAMEPAD_Y ) != 0; 
		}
	return false;
	}


bool pixie::gamepad_was_pressed( int pad_index, gamepadbutton_id button )
	{
	if( !gamepad_connected( pad_index ) ) return false;
	internal::internals_t* internals = internal::internals();
	GAMEPAD_U16 state = internals->gamepad_data[ pad_index ].state.buttons;
	GAMEPAD_U16 prev = internals->gamepad_data[ pad_index ].previous_state.buttons;
	switch( button )
		{   
		case GAMEPADBUTTON_DPAD_UP: return ( state & GAMEPAD_DPAD_UP ) != 0 && ( prev & GAMEPAD_DPAD_UP ) == 0; 
		case GAMEPADBUTTON_DPAD_DOWN: return ( state & GAMEPAD_DPAD_DOWN ) != 0 && ( prev & GAMEPAD_DPAD_DOWN ) == 0; 
		case GAMEPADBUTTON_DPAD_LEFT: return ( state & GAMEPAD_DPAD_LEFT ) != 0 && ( prev & GAMEPAD_DPAD_LEFT ) == 0; 
		case GAMEPADBUTTON_DPAD_RIGHT: return ( state & GAMEPAD_DPAD_RIGHT ) != 0 && ( prev & GAMEPAD_DPAD_RIGHT ) == 0; 
		case GAMEPADBUTTON_START: return ( state & GAMEPAD_START ) != 0 && ( prev & GAMEPAD_START ) == 0; 
		case GAMEPADBUTTON_BACK: return ( state & GAMEPAD_BACK ) != 0 && ( prev & GAMEPAD_BACK ) == 0; 
		case GAMEPADBUTTON_STICK_LEFT: return ( state & GAMEPAD_STICK_LEFT ) != 0 && ( prev & GAMEPAD_STICK_LEFT ) == 0; 
		case GAMEPADBUTTON_STICK_RIGHT: return ( state & GAMEPAD_STICK_RIGHT ) != 0 && ( prev & GAMEPAD_STICK_RIGHT ) == 0; 
		case GAMEPADBUTTON_SHOULDER_LEFT: return ( state & GAMEPAD_SHOULDER_LEFT ) != 0 && ( prev & GAMEPAD_SHOULDER_LEFT ) == 0; 
		case GAMEPADBUTTON_SHOULDER_RIGHT: return ( state & GAMEPAD_SHOULDER_RIGHT ) != 0 && ( prev & GAMEPAD_SHOULDER_RIGHT ) == 0; 
		case GAMEPADBUTTON_A: return ( state & GAMEPAD_A ) != 0 && ( prev & GAMEPAD_A ) == 0; 
		case GAMEPADBUTTON_B: return ( state & GAMEPAD_B ) != 0 && ( prev & GAMEPAD_B ) == 0; 
		case GAMEPADBUTTON_X: return ( state & GAMEPAD_X ) != 0 && ( prev & GAMEPAD_X ) == 0; 
		case GAMEPADBUTTON_Y: return ( state & GAMEPAD_Y ) != 0 && ( prev & GAMEPAD_Y ) == 0; 
		}
	return false;
	}


bool pixie::gamepad_was_released( int pad_index, gamepadbutton_id button )
	{
	if( !gamepad_connected( pad_index ) ) return false;
	internal::internals_t* internals = internal::internals();
	GAMEPAD_U16 state = internals->gamepad_data[ pad_index ].state.buttons;
	GAMEPAD_U16 prev = internals->gamepad_data[ pad_index ].previous_state.buttons;
	switch( button )
		{   
		case GAMEPADBUTTON_DPAD_UP: return ( state & GAMEPAD_DPAD_UP ) == 0 && ( prev & GAMEPAD_DPAD_UP ) != 0; 
		case GAMEPADBUTTON_DPAD_DOWN: return ( state & GAMEPAD_DPAD_DOWN ) == 0 && ( prev & GAMEPAD_DPAD_DOWN ) != 0; 
		case GAMEPADBUTTON_DPAD_LEFT: return ( state & GAMEPAD_DPAD_LEFT ) == 0 && ( prev & GAMEPAD_DPAD_LEFT ) != 0; 
		case GAMEPADBUTTON_DPAD_RIGHT: return ( state & GAMEPAD_DPAD_RIGHT ) == 0 && ( prev & GAMEPAD_DPAD_RIGHT ) != 0; 
		case GAMEPADBUTTON_START: return ( state & GAMEPAD_START ) == 0 && ( prev & GAMEPAD_START ) != 0; 
		case GAMEPADBUTTON_BACK: return ( state & GAMEPAD_BACK ) == 0 && ( prev & GAMEPAD_BACK ) != 0; 
		case GAMEPADBUTTON_STICK_LEFT: return ( state & GAMEPAD_STICK_LEFT ) == 0 && ( prev & GAMEPAD_STICK_LEFT ) != 0; 
		case GAMEPADBUTTON_STICK_RIGHT: return ( state & GAMEPAD_STICK_RIGHT ) == 0 && ( prev & GAMEPAD_STICK_RIGHT ) != 0; 
		case GAMEPADBUTTON_SHOULDER_LEFT: return ( state & GAMEPAD_SHOULDER_LEFT ) == 0 && ( prev & GAMEPAD_SHOULDER_LEFT ) != 0; 
		case GAMEPADBUTTON_SHOULDER_RIGHT: return ( state & GAMEPAD_SHOULDER_RIGHT ) == 0 && ( prev & GAMEPAD_SHOULDER_RIGHT ) != 0; 
		case GAMEPADBUTTON_A: return ( state & GAMEPAD_A ) == 0 && ( prev & GAMEPAD_A ) != 0; 
		case GAMEPADBUTTON_B: return ( state & GAMEPAD_B ) == 0 && ( prev & GAMEPAD_B ) != 0; 
		case GAMEPADBUTTON_X: return ( state & GAMEPAD_X ) == 0 && ( prev & GAMEPAD_X ) != 0; 
		case GAMEPADBUTTON_Y: return ( state & GAMEPAD_Y ) == 0 && ( prev & GAMEPAD_Y ) != 0; 
		}
	return false;
	}


void pixie::gamepad_pressed_event( event_handler* handler, int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data )
	{
	if( !gamepad_connected( pad_index ) ) return;
	internal::internals_t* internals = internal::internals();
	internal::gamepadbutton_event_t& event = internals->gamepad_pressed_events.add();
	event.handler = handler;
	event.pad_index = pad_index;
	event.button = button;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::gamepad_released_event( event_handler* handler, int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data  )
	{
	if( !gamepad_connected( pad_index ) ) return;
	internal::internals_t* internals = internal::internals();
	internal::gamepadbutton_event_t& event = internals->gamepad_released_events.add();
	event.handler = handler;
	event.pad_index = pad_index;
	event.button = button;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::gamepad_axis_event( event_handler* handler, int pad_index, gamepadaxis_id axis, float threshold, string_id const& event_id, void* user_data )
	{
	if( !gamepad_connected( pad_index ) ) return;
	internal::internals_t* internals = internal::internals();
	internal::gamepadaxis_event_t& event = internals->gamepad_axis_events.add();
	event.handler = handler;
	event.pad_index = pad_index;
	event.axis = axis;
	event.threshold = threshold;
	event.event_id = event_id;
	event.user_data = user_data;
	}
 
	
bool pixie::key_is_down( key_id key ) 
	{ 
	internal::internals_t* internals = internal::internals();
	if( key < 0 || key >= sizeof( internals->key_states ) / sizeof( *internals->key_states ) ) return false;
	return internals->key_states[ key ]; 
	}


bool pixie::key_was_pressed( key_id key ) 
	{ 
	internal::internals_t* internals = internal::internals();
	if( key < 0 || key >= sizeof( internals->key_states ) / sizeof( *internals->key_states ) ) return false;
	return internals->key_states[ key ] && !internals->previous_key_states[ key ] ; 
	}


bool pixie::key_was_released( key_id key ) 
	{ 
	internal::internals_t* internals = internal::internals();
	if( key < 0 || key >= sizeof( internals->key_states ) / sizeof( *internals->key_states ) ) return false;
	return !internals->key_states[ key ] && internals->previous_key_states[ key ] ; 
	}


void pixie::key_pressed_event( event_handler* handler, key_id key, string_id const& event_id, void* user_data ) 
	{
	internal::internals_t* internals = internal::internals();
	internal::key_event_t& event = internals->key_pressed_events.add();
	event.handler = handler;
	event.key = key;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::key_released_event( event_handler* handler, key_id key, string_id const& event_id, void* user_data ) 
	{
	internal::internals_t* internals = internal::internals();
	internal::key_event_t& event = internals->key_released_events.add();
	event.handler = handler;
	event.key = key;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::ascii_event( event_handler* handler, char ascii, string_id const& event_id, void* user_data )
	{
	internal::internals_t* internals = internal::internals();
	internal::ascii_event_t& event = internals->ascii_events.add();
	event.handler = handler;
	event.ascii = ascii;
	event.event_id = event_id;
	event.user_data = user_data;
	}


namespace pixie { namespace internal {


int lookup_action_index( string_id const& action )
	{
	internal::internals_t* internals = internal::internals();
	int* index = internals->action_to_index.find( action );
	if( index ) return *index;
	
	int retval = internals->next_action_index++;
	internals->action_to_index[ action ] = retval;
	return retval;
	}


inputmap_mouseaxis_t inputmap_mouseaxis_from_pixie_mouseaxis( mouseaxis_id axis )
	{
	switch( axis )
		{
		case MOUSEAXIS_LEFTRIGHT: return INPUTMAP_MOUSEAXIS_LEFT_RIGHT;
		case MOUSEAXIS_FORWARDBACK: return INPUTMAP_MOUSEAXIS_FORWARD_BACK;
		case MOUSEAXIS_WHEEL: return INPUTMAP_MOUSEAXIS_WHEEL;
		}

	PIXIE_ASSERT( false, "Invalid parameter." );
	return (inputmap_mouseaxis_t) 0;
	}
	

inputmap_gamepadaxis_t inputmap_gamepadaxis_from_pixie_gamepadaxis( gamepadaxis_id axis )
	{
	switch( axis )
		{
		case GAMEPADAXIS_LEFT_TRIGGER: return INPUTMAP_GAMEPADAXIS_LEFT_TRIGGER; break;
		case GAMEPADAXIS_RIGHT_TRIGGER: return INPUTMAP_GAMEPADAXIS_RIGHT_TRIGGER; break;
		case GAMEPADAXIS_LEFTSTICK_X: return INPUTMAP_GAMEPADAXIS_LEFTSTICK_X; break;
		case GAMEPADAXIS_LEFTSTICK_Y: return INPUTMAP_GAMEPADAXIS_LEFTSTICK_Y; break;
		case GAMEPADAXIS_RIGHTSTICK_X: return INPUTMAP_GAMEPADAXIS_RIGHTSTICK_X; break;
		case GAMEPADAXIS_RIGHTSTICK_Y: return INPUTMAP_GAMEPADAXIS_RIGHTSTICK_Y; break;
		}

	PIXIE_ASSERT( false, "Invalid parameter." );
	return (inputmap_gamepadaxis_t) 0;
	}


inputmap_gamepadbutton_t inputmap_gamepadbutton_from_pixie_gamepadbutton( gamepadbutton_id button )
	{
	switch( button )
		{
		case GAMEPADBUTTON_DPAD_UP: return INPUTMAP_GAMEPADBUTTON_DPAD_UP; break;
		case GAMEPADBUTTON_DPAD_DOWN: return INPUTMAP_GAMEPADBUTTON_DPAD_DOWN; break;
		case GAMEPADBUTTON_DPAD_LEFT: return INPUTMAP_GAMEPADBUTTON_DPAD_LEFT; break;
		case GAMEPADBUTTON_DPAD_RIGHT: return INPUTMAP_GAMEPADBUTTON_DPAD_RIGHT; break;
		case GAMEPADBUTTON_START: return INPUTMAP_GAMEPADBUTTON_START; break;
		case GAMEPADBUTTON_BACK: return INPUTMAP_GAMEPADBUTTON_BACK; break;
		case GAMEPADBUTTON_STICK_LEFT: return INPUTMAP_GAMEPADBUTTON_STICK_LEFT; break;
		case GAMEPADBUTTON_STICK_RIGHT: return INPUTMAP_GAMEPADBUTTON_STICK_RIGHT; break;
		case GAMEPADBUTTON_SHOULDER_LEFT: return INPUTMAP_GAMEPADBUTTON_SHOULDER_LEFT; break;
		case GAMEPADBUTTON_SHOULDER_RIGHT: return INPUTMAP_GAMEPADBUTTON_SHOULDER_RIGHT; break;
		case GAMEPADBUTTON_A: return INPUTMAP_GAMEPADBUTTON_A; break;
		case GAMEPADBUTTON_B: return INPUTMAP_GAMEPADBUTTON_B; break;
		case GAMEPADBUTTON_X: return INPUTMAP_GAMEPADBUTTON_X; break;
		case GAMEPADBUTTON_Y: return INPUTMAP_GAMEPADBUTTON_Y; break;
		}

	PIXIE_ASSERT( false, "Invalid parameter." );
	return (inputmap_gamepadbutton_t) 0;
	}


} /* namespace internal */ } /*namespace pixie */


int pixie::action_axis( string_id const& action, key_id key_neg, key_id key_pos, float scale )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_mapping_t mapping = inputmap_map_axis_keyboard( internals->inputmap, action_index, 
		internal::inputmap_key_from_pixie_key( key_neg ), internal::inputmap_key_from_pixie_key( key_pos ), scale );
	return mapping.handle;
	}


int pixie::action_axis( string_id const& action, mouseaxis_id axis, bool invert, float scale )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	
	inputmap_mapping_t mapping = inputmap_map_axis_mouseaxis( internals->inputmap, action_index, 
		internal::inputmap_mouseaxis_from_pixie_mouseaxis( axis ), invert ? INPUTMAP_INVERTED : INPUTMAP_NOT_INVERTED,  scale );
	return mapping.handle;
	}


int pixie::action_axis( string_id const& action, int pad_index, gamepadaxis_id axis, bool invert, float scale )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	
	inputmap_mapping_t mapping = inputmap_map_axis_gamepadaxis( internals->inputmap, action_index, pad_index, 
		internal::inputmap_gamepadaxis_from_pixie_gamepadaxis( axis ), invert ? INPUTMAP_INVERTED : INPUTMAP_NOT_INVERTED, scale );
	return mapping.handle;
	}


int pixie::action_axis( string_id const& action, int pad_index, gamepadbutton_id button_neg, gamepadbutton_id button_pos, float scale )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	
	inputmap_mapping_t mapping = inputmap_map_axis_gamepadbuttons( internals->inputmap, action_index, pad_index, 
		internal::inputmap_gamepadbutton_from_pixie_gamepadbutton( button_neg ), 
		internal::inputmap_gamepadbutton_from_pixie_gamepadbutton( button_pos ), scale );
	return mapping.handle;
	}


int pixie::action_button( string_id const& action, key_id key )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_mapping_t mapping = inputmap_map_button_keyboard( internals->inputmap, action_index, 
		internal::inputmap_key_from_pixie_key( key ) );
	return mapping.handle;
	}


int pixie::action_button( string_id const& action, mouseaxis_id axis, bool invert, float threshold )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_mapping_t mapping = inputmap_map_button_mouseaxis( internals->inputmap, action_index, 
		internal::inputmap_mouseaxis_from_pixie_mouseaxis( axis ), invert ? INPUTMAP_INVERTED : INPUTMAP_NOT_INVERTED, threshold );
	return mapping.handle;
	}


int pixie::action_button( string_id const& action, int pad_index, gamepadaxis_id axis,  bool invert, float threshold )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_mapping_t mapping = inputmap_map_button_gamepadaxis( internals->inputmap, action_index, pad_index, 
		internal::inputmap_gamepadaxis_from_pixie_gamepadaxis( axis ), invert ? INPUTMAP_INVERTED : INPUTMAP_NOT_INVERTED, threshold );
	return mapping.handle;
	}


int pixie::action_button( string_id const& action, int pad_index, gamepadbutton_id button )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_mapping_t mapping = inputmap_map_button_gamepadbutton( internals->inputmap, action_index, pad_index, 
		internal::inputmap_gamepadbutton_from_pixie_gamepadbutton( button ) );
	return mapping.handle;
	}


void pixie::action_unmap( int handle )
	{
	internal::internals_t* internals = internal::internals();
	inputmap_mapping_t mapping;
	mapping.handle = handle;
	inputmap_unmap( internals->inputmap, mapping );
	}


void pixie::action_remove( string_id const& action )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	inputmap_remove( internals->inputmap, action_index );
	}


float pixie::action( string_id const& action )
	{
	internal::internals_t* internals = internal::internals();
	int action_index = internal::lookup_action_index( action );
	return inputmap_action( internals->inputmap, action_index );
	}


void pixie::action_event( event_handler* handler, string_id const& action, string_id const& event_id, void* user_data)
	{
	internal::internals_t* internals = internal::internals();
	internal::action_event_t& event = internals->action_events.add();
	event.handler = handler;
	event.action = action;
	event.using_threshold = false;
	event.threshold = 0.0f;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::action_event( event_handler* handler, string_id const& action, float threshold, string_id const& event_id, void* user_data)
	{
	internal::internals_t* internals = internal::internals();
	internal::action_event_t& event = internals->action_events.add();
	event.handler = handler;
	event.action = action;
	event.using_threshold = true;
	event.threshold = threshold;
	event.event_id = event_id;
	event.user_data = user_data;
	}


void pixie::remove_event_handler( event_handler* handler )
	{
	internal::internals_t* internals = internal::internals();

	for( int i = 0; i < internals->time_events.count(); ++i )
		{
		if( internals->time_events[ i ].handler == handler )
			{
			internals->time_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->key_pressed_events.count(); ++i )
		{
		if( internals->key_pressed_events[ i ].handler == handler )
			{
			internals->key_pressed_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->key_released_events.count(); ++i )
		{
		if( internals->key_released_events[ i ].handler == handler )
			{
			internals->key_released_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->ascii_events.count(); ++i )
		{
		if( internals->ascii_events[ i ].handler == handler )
			{
			internals->ascii_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->action_events.count(); ++i )
		{
		if( internals->action_events[ i ].handler == handler )
			{
			internals->action_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->gamepad_pressed_events.count(); ++i )
		{
		if( internals->gamepad_pressed_events[ i ].handler == handler )
			{
			internals->gamepad_pressed_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->gamepad_released_events.count(); ++i )
		{
		if( internals->gamepad_released_events[ i ].handler == handler )
			{
			internals->gamepad_released_events.remove( i );
			--i;
			}
		}

	for( int i = 0; i < internals->gamepad_axis_events.count(); ++i )
		{
		if( internals->gamepad_axis_events[ i ].handler == handler )
			{
			internals->gamepad_axis_events.remove( i );
			--i;
			}
		}

	}


pixie::tweener pixie::tween( float duration )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	return internals->tween_system.tween( duration );
	}


void pixie::stop_all_tweeners()
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	return internals->tween_system.stop_all();
	}


void pixie::pause_all_tweeners()
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	internals->tween_scale = 0.0f;
	}


void pixie::resume_all_tweeners()
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	internals->tween_scale = 1.0f;
	}


float pixie::random()
	{
	internal::internals_t* internals = internal::internals();
	return rnd_pcg_nextf( &internals->rng_instance);
	}
	
	

int pixie::random( int min, int max )
	{
	internal::internals_t* internals = internal::internals();
	return rnd_pcg_range( &internals->rng_instance, min, max );
	}

	
void pixie::random_seed( u32 seed )
	{
	internal::internals_t* internals = internal::internals();
	rnd_pcg_seed( &internals->rng_instance, seed );
	}
	
	
float pixie::random_bell_curve( int iterations )
	{
	float sum = 0.0f;
	for( int i = 0; i < iterations; ++i )
		sum += random();
	return sum / (float) iterations;
	}


int pixie::random_bell_curve( int min, int max, int iterations )
	{
	int const range = ( max - min ) + 1;
	if( range <= 0 ) return min;
	int const value = (int) ( random_bell_curve( iterations ) * range );
	return min + value; 
	}
	
		
pixie::float3 pixie::random_unit_vector()
	{
	float const TWO_PI_ = 6.283185307179586476925286766559f;

	float phi = random() * TWO_PI_;
	float costheta = random() * 2.0f - 1.0f;
	float theta = acosf( costheta );
 
	float x = sinf( theta ) * cosf( phi );
	float y = sinf( theta ) * sinf( phi );
	float z = cosf( theta );

	return float3( x, y, z );
	}


float pixie::perlin_noise( float3 pos, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_noise3( pos.x, pos.y, pos.z, wrap_x, wrap_y, wrap_z );
	}


float pixie::perlin_noise( float x, float y, float z, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_noise3( x, y, z, wrap_x, wrap_y, wrap_z );
	}


float pixie::fractal_noise_ridge( float3 pos, float lacunarity, float gain, float offset, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_ridge_noise3( pos.x, pos.y, pos.z, lacunarity, gain, offset, octaves, wrap_x, wrap_y, wrap_z );
	}


float pixie::fractal_noise_ridge( float x, float y, float z, float lacunarity, float gain, float offset, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_ridge_noise3( x, y, z, lacunarity, gain, offset, octaves, wrap_x, wrap_y, wrap_z );
	}


float pixie::fractal_noise_fbm( float3 pos, float lacunarity, float gain, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_fbm_noise3( pos.x, pos.y, pos.z, lacunarity, gain, octaves, wrap_x, wrap_y, wrap_z );
	}

	
float pixie::fractal_noise_fbm( float x, float y, float z, float lacunarity, float gain, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_fbm_noise3( x, y, z, lacunarity, gain, octaves, wrap_x, wrap_y, wrap_z );
	}

	
float pixie::fractal_noise_turbulence( float3 pos, float lacunarity, float gain, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_turbulence_noise3( pos.x, pos.y, pos.z, lacunarity, gain, octaves, wrap_x, wrap_y, wrap_z );
	}


float pixie::fractal_noise_turbulence( float x, float y, float z, float lacunarity, float gain, int octaves, int wrap_x, int wrap_y, int wrap_z )
	{
	return stb_perlin_turbulence_noise3( x, y, z, lacunarity, gain, octaves, wrap_x, wrap_y, wrap_z );
	}


void pixie::master_volume( float volume )
	{
	internal::internals_t* internals = internal::internals();
	
	volume = clamp( volume, 0.0f, 1.0f );
	if( volume == internals->master_volume ) return;
	internals->master_volume = volume;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_MASTER_VOLUME;
	command.data.volume = volume;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::master_volume()
	{
	internal::internals_t* internals = internal::internals();
	return internals->master_volume;
	}


void pixie::pause_audio()
	{
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_PAUSE_AUDIO;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::resume_audio()
	{
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_RESUME_AUDIO;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::play_music( resource<audio> audio_resource, float fade_in_time, float delay )
	{
	internal::internals_t* internals = internal::internals();
	
	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_music_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_PLAY_MUSIC;
	command.data.play.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.play.instance, "Failed to instantiate sound" );
	command.data.play.fade_in_time = fade_in_time;
	command.data.play.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_music_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
	}


void pixie::stop_music( float fade_out_time )
	{
	internal::internals_t* internals = internal::internals();
	internals->current_music_handle = 0;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_STOP_MUSIC;
	command.data.fade_out_time = fade_out_time;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::pause_music()
	{
	internal::internals_t* internals = internal::internals();

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_PAUSE_MUSIC;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::resume_music()
	{
	internal::internals_t* internals = internal::internals();

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_RESUME_MUSIC;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::switch_music( resource<audio> audio_resource, float fade_out_time, float fade_in_time, float delay )
	{
	internal::internals_t* internals = internal::internals();

	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_music_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SWITCH_MUSIC;
	command.data.switch_.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.switch_.instance, "Failed to instantiate sound" );
	command.data.switch_.fade_out_time = fade_out_time;
	command.data.switch_.fade_in_time = fade_in_time;
	command.data.switch_.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_music_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
}


void pixie::cross_fade_music( resource<audio> audio_resource, float cross_fade_time, float delay )
	{
	internal::internals_t* internals = internal::internals();

	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_music_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_CROSS_FADE_MUSIC;
	command.data.cross_fade.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.cross_fade.instance, "Failed to instantiate sound" );
	command.data.cross_fade.cross_fade_time = cross_fade_time;
	command.data.cross_fade.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_music_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
	}


void pixie::music_position( float position )
	{
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_MUSIC_POSITION;
	command.data.position = position;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::music_position()
	{
	internal::internals_t* internals = internal::internals();
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_music_handle );
	if( !curr_inst ) return 0.0f;
	return curr_inst->position;
	}


pixie::resource<pixie::audio> pixie::current_music()
	{
	internal::internals_t* internals = internal::internals();
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_music_handle );
	if( curr_inst ) return curr_inst->audio_resource;
	return resource<audio>();
	}


void pixie::music_loop( bool loop )
	{
	internal::internals_t* internals = internal::internals();
	
	if( internals->music_loop == loop ) return;
	internals->music_loop = loop;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_MUSIC_LOOP;
	command.data.loop = loop;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


bool pixie::music_loop()
	{
	internal::internals_t* internals = internal::internals();
	return internals->music_loop;
	}


void pixie::music_volume( float volume )
	{
	internal::internals_t* internals = internal::internals();

	if( internals->music_volume == volume ) return;
	internals->music_volume = volume;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_MUSIC_VOLUME;
	command.data.volume = volume;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::music_volume()
	{
	internal::internals_t* internals = internal::internals();
	return internals->music_volume;
	}


void pixie::music_pan( float pan )
	{
	internal::internals_t* internals = internal::internals();

	if( internals->music_pan == pan ) return;
	internals->music_pan = pan;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_MUSIC_PAN;
	command.data.pan = pan;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::music_pan()
	{
	internal::internals_t* internals = internal::internals();   
	return internals->music_pan;
	}


void pixie::play_ambience( resource<audio> audio_resource, float fade_in_time, float delay )
	{
	internal::internals_t* internals = internal::internals();
	
	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_ambience_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_PLAY_AMBIENCE;
	command.data.play.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.play.instance, "Failed to instantiate sound" );
	command.data.play.fade_in_time = fade_in_time;
	command.data.play.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_ambience_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
	}


void pixie::stop_ambience( float fade_out_time )
	{
	internal::internals_t* internals = internal::internals();
	internals->current_ambience_handle = 0;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_STOP_AMBIENCE;
	command.data.fade_out_time = fade_out_time;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::pause_ambience()
	{
	internal::internals_t* internals = internal::internals();

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_PAUSE_AMBIENCE;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::resume_ambience()
	{
	internal::internals_t* internals = internal::internals();

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_RESUME_AMBIENCE;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


void pixie::switch_ambience( resource<audio> audio_resource, float fade_out_time, float fade_in_time, float delay )
	{
	internal::internals_t* internals = internal::internals();

	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_ambience_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SWITCH_AMBIENCE;
	command.data.switch_.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.switch_.instance, "Failed to instantiate sound" );
	command.data.switch_.fade_out_time = fade_out_time;
	command.data.switch_.fade_in_time = fade_in_time;
	command.data.switch_.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_ambience_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
}


void pixie::cross_fade_ambience( resource<audio> audio_resource, float cross_fade_time, float delay )
	{
	internal::internals_t* internals = internal::internals();

	if( !audio_resource ) return;
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_ambience_handle );
	if( curr_inst && audio_resource == curr_inst->audio_resource ) return;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_CROSS_FADE_AMBIENCE;
	command.data.cross_fade.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.cross_fade.instance, "Failed to instantiate sound" );
	command.data.cross_fade.cross_fade_time = cross_fade_time;
	command.data.cross_fade.delay = delay;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	internals->current_ambience_handle = internals->next_audio_handle;

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;
	}


void pixie::ambience_position( float position )
	{
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_AMBIENCE_POSITION;
	command.data.position = position;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::ambience_position()
	{
	internal::internals_t* internals = internal::internals();
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_ambience_handle );
	if( !curr_inst ) return 0.0f;
	return curr_inst->position;
	}


pixie::resource<pixie::audio> pixie::current_ambience()
	{
	internal::internals_t* internals = internal::internals();
	internal::sound_instance* curr_inst = internals->current_sounds.find( internals->current_ambience_handle );
	if( curr_inst ) return curr_inst->audio_resource;
	return resource<audio>();
	}


void pixie::ambience_loop( bool loop )
	{
	internal::internals_t* internals = internal::internals();
	
	if( internals->ambience_loop == loop ) return;
	internals->ambience_loop = loop;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_AMBIENCE_LOOP;
	command.data.loop = loop;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


bool pixie::ambience_loop()
	{
	internal::internals_t* internals = internal::internals();
	return internals->ambience_loop;
	}


void pixie::ambience_volume( float volume )
	{
	internal::internals_t* internals = internal::internals();

	if( internals->ambience_volume == volume ) return;
	internals->ambience_volume = volume;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_AMBIENCE_VOLUME;
	command.data.volume = volume;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::ambience_volume()
	{
	internal::internals_t* internals = internal::internals();
	return internals->ambience_volume;
	}


void pixie::ambience_pan( float pan )
	{
	internal::internals_t* internals = internal::internals();

	if( internals->ambience_pan == pan ) return;
	internals->ambience_pan = pan;

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.type = internal::AUDIO_COMMAND_TYPE_AMBIENCE_PAN;
	command.data.pan = pan;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	}


float pixie::ambience_pan()
	{
	internal::internals_t* internals = internal::internals();   
	return internals->ambience_pan;
	}


pixie::sound pixie::sound::loop( bool loop )
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SOUND_LOOP;
	command.data.loop = loop;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::volume( float volume )
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SOUND_VOLUME;
	command.data.volume = volume;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::pan( float pan )
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SOUND_PAN;
	command.data.pan = pan;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::stop( float fade_out_time )
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_STOP_SOUND;
	command.data.fade_out_time = fade_out_time;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::pause()
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_PAUSE_SOUND;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::resume()
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_RESUME_SOUND;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::sound pixie::sound::position( float pos )
	{
	if( this->handle == 0 ) return *this;
	internal::internals_t* internals = internal::internals();
	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = this->handle;
	command.type = internal::AUDIO_COMMAND_TYPE_SOUND_POSITION;
	command.data.position = pos;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );
	return *this;
	}


pixie::resource<pixie::audio> pixie::sound::audio_resource()
	{
	if( this->handle == 0 ) return resource<audio>();
	internal::internals_t* internals = internal::internals();
	internal::sound_instance const* instance = internals->current_sounds.find( this->handle );
	if( !instance ) return resource<audio>();
	return instance->audio_resource;
	}


float pixie::sound::position()
	{
	if( this->handle == 0 ) return 0.0f;
	internal::internals_t* internals = internal::internals();
	internal::sound_instance const* instance = internals->current_sounds.find( this->handle );
	if( !instance ) return 0.0f;
	return instance->position;
	}


bool pixie::sound::loop()
	{
	if( this->handle == 0 ) return false;
	internal::internals_t* internals = internal::internals();
	internal::sound_instance const* instance = internals->current_sounds.find( this->handle );
	if( !instance ) return false;
	return instance->loop;
	}


float pixie::sound::volume()
	{
	if( this->handle == 0 ) return 0.0f;
	internal::internals_t* internals = internal::internals();
	internal::sound_instance const* instance = internals->current_sounds.find( this->handle );
	if( !instance ) return 1.0f;
	return instance->volume;
	}


float pixie::sound::pan()
	{
	if( this->handle == 0 ) return 0.0f;
	internal::internals_t* internals = internal::internals();
	internal::sound_instance const* instance = internals->current_sounds.find( this->handle );
	if( !instance ) return 0.0f;
	return instance->pan;
	}


pixie::sound::sound() : handle( 0 )
	{
	}


pixie::sound pixie::play_sound( resource<audio> audio_resource, float priority, float fade_in_time, float delay )
	{
	internal::internals_t* internals = internal::internals();
	
	if( !audio_resource ) { pixie::sound sound; sound.handle = 0; return sound; }

	internal::audio_command_t command;  
	memset( &command, 0, sizeof( command ) );
	command.handle = ++internals->next_audio_handle;
	command.type = internal::AUDIO_COMMAND_TYPE_PLAY_SOUND;
	command.data.play.instance = audio_resource->create_instance();
	PIXIE_ASSERT( command.data.play.instance, "Failed to instantiate sound" );
	command.data.play.fade_in_time = fade_in_time;
	command.data.play.delay = delay;
	command.data.play.priority = priority;
	internal::send_audio_command( internals->audio_frame_data, internals->memctx, &command );

	internal::sound_instance& instance = internals->current_sounds[ internals->next_audio_handle ];
	instance.handle = internals->next_audio_handle;
	instance.loop = false;
	instance.position = 0.0f;
	instance.volume = 1.0f;
	instance.pan = 0.0f;
	instance.audio_resource = audio_resource;

	pixie::sound sound;
	sound.handle = internals->next_audio_handle;
	return sound;
	}


bool pixie::starts_with( string str, string start )
	{
	return left( str, len( start) ) == start;
	}


bool pixie::starts_with( string_id str, string_id start )
	{
	return left( str, len( start) ) == start;
	}


namespace pixie { namespace internal {

bitmap* load_bitmap( string const& filename )
	{
	internal::internals_t* internals = internal::internals();

	bitmap* instance = 0;
	ref<binary> bin = bload( filename );
	PIXIE_ASSERTF( bin, ( "Failed to load bitmap: %s", filename.c_str() ) );
	if( bin )
		{
		char const header[] = "PIXIE_PIX";
		if( memcmp( bin->data, header, sizeof( header ) ) == 0 )
			{
			int* info = (int*)( (uintptr_t)bin->data + sizeof( header ) );
			int supported_version = 1;
			int file_version = *info++;
			PIXIE_ASSERT( file_version == supported_version, "Invalid file version" );
			if( file_version == supported_version )
				{
				int type = info[ 0 ];
				PIXIE_ASSERT( type == 0, "Unknown bitmap type" );
				if( type == 0 )
					{
					int w = info[ 1 ];
					int h = info[ 2 ];
					int cel_count = info[ 3 ];
					bool is_masked = info[ 4 ] != 0;
					
					u8* data = (u8*)( info + 5 );
					if( cel_count > 1 )
						{
						void* cels = TRACKED_MALLOC( internals->memctx, cel_count * ( sizeof( void* ) * 2 + sizeof( int ) * 4 ) ); 
						u8** pixels = (u8**) cels;
						u8** masks = pixels + cel_count; 
						int* offsets_x = (int*) ( masks + cel_count );
						int* offsets_y = offsets_x + cel_count;
						int* pitches_x = offsets_y + cel_count;
						int* pitches_y = pitches_x + cel_count;
						
						for( int i = 0; i < cel_count; ++i )
							{
							offsets_x[ i ] = *(int*) data; data += sizeof( int );
							offsets_y[ i ] = *(int*) data; data += sizeof( int );
							pitches_x[ i ] = *(int*) data; data += sizeof( int );
							pitches_y[ i ] = *(int*) data; data += sizeof( int );
							
							pixels[ i ] = data;
							data += pitches_x[ i ] * pitches_y[ i ];
							if( is_masked ) 
								{
								masks[ i ] = data;
								data += pitches_x[ i ] * pitches_y[ i ];
								}
							}

						void* storage = internals->pool_bitmap_and_refcount.create();
						if( is_masked )
							instance = new (storage) bitmap( w, h, cel_count, offsets_x, offsets_y, pitches_x, pitches_y, pixels, masks );  
						else
							instance = new (storage) bitmap( w, h, cel_count, offsets_x, offsets_y, pitches_x, pitches_y, pixels ); 
							
						TRACKED_FREE( internals->memctx, cels );
						}
					else
						{
						int offset_x = *(int*) data; data += sizeof( int );
						int offset_y = *(int*) data; data += sizeof( int );
						int pitch_x = *(int*) data; data += sizeof( int );
						int pitch_y = *(int*) data; data += sizeof( int );

						void* storage = internals->pool_bitmap_and_refcount.create();
						if( is_masked )
							instance = new (storage) bitmap( w, h, offset_x, offset_y, pitch_x, pitch_y, data, data + pitch_x * pitch_y );  
						else
							instance = new (storage) bitmap( w, h, offset_x, offset_y, pitch_x, pitch_y, data );    
						}
					}
				}
			}
		else
			{
			int w, h, c;
			stbi_uc* img = stbi_load_from_memory( (stbi_uc*) bin->data, (int)bin->size, &w, &h, &c, 4 );
			PIXIE_ASSERTF( img, ( "Failed to load bitmap: %s", filename.c_str() ) );
			if( img )
				{   
				u8* pixels = (u8*) TRACKED_MALLOC( internals->memctx, 2 * w * h * sizeof( u8 ) );
				u8* mask = pixels + w* h;
				for( int i = 0; i < w * h; ++i )
					{
					int best_index = 0;
					int min_distance_sq = 2147483647;
					u32 color = ( (u32*)img )[ i ];
					int cb = (int)( ( color >> 16 ) & 0xff );
					int cg = (int)( ( color >> 8 ) & 0xff );
					int cr = (int)( ( color ) & 0xff );
					int cl = ( 54 * cr + 183 * cg + 19 * cb + 127 ) >> 8;

					for( int j = 0; j < sizeof( internals->palette ) / sizeof( *internals->palette ); ++j ) 
						{
						int pr = (int)internals->palette[ j ].r;
						int pg = (int)internals->palette[ j ].g;
						int pb = (int)internals->palette[ j ].b;
						int pl = ( 54 * pr + 183 * pg + 19 * pb + 127 ) >> 8;
						int dr = cr - pr;
						int dg = cg - pg;
						int db = cb - pb;
						int dl = cl - pl;
						int d = ( ( ( ( dr * dr + dg * dg + db * db ) >> 1 ) + dl * dl ) * 38 + 127 ) >> 8;
						int distance_sq = ( ( ( dr*dr + dg*dg + db*db ) >> 1 ) + dl*dl ) + d;
						if( distance_sq < min_distance_sq ) 
							{
							min_distance_sq = distance_sq;
							best_index = j;
							}
						}
					pixels[ i ] = (u8) best_index;
					}

				for( int i = 0; i < w * h; ++i ) mask[ i ] = (u8)( ( ((u32*) img)[ i ] ) >> 24 );
				void* storage = internals->pool_bitmap_and_refcount.create();
				instance = new (storage) bitmap( w, h, pixels, mask );
				stbi_image_free( img );
				TRACKED_FREE( internals->memctx, pixels );
				}
			}
		}
		
	return instance;
	}
	
	
void free_bitmap( bitmap* bmp )
	{
	internal::internals_t* internals = internal::internals();
	bmp->~bitmap();
	internals->pool_bitmap_and_refcount.destroy( (bitmap_and_refcount*) bmp );
	}   
	

void destroy_bitmap( void* bmp )
	{
	free_bitmap( (bitmap*) bmp );
	}   

} /* namespace internal */ } /* namespace pixie */


pixie::ref<pixie::bitmap> pixie::load_bitmap( string const& filename )
	{
	bitmap* bmp = internal::load_bitmap( filename );
	return refcount::make_ref( bmp, internal::destroy_bitmap, (int*)( bmp + 1 ), 0 );   
	}

//-------------
//  game_state
//-------------

pixie::game_state::game_state()
	{
	internal::internals_t* internals = internal::internals();
	internals->default_sprite_manager.add_event_handler( this );
	}


pixie::game_state::~game_state()
	{
	internal::internals_t* internals = internal::internals();
	internals->default_sprite_manager.remove_event_handler( this );
	remove_event_handler( this );
	stop_all_tweeners();
	}


void pixie::game_state::time_event( float seconds, string_id const& event_id, void* user_data )
	{
	pixie::time_event( this, seconds, event_id, user_data );
	}


void pixie::game_state::repeating_time_event( float seconds, string_id const& event_id, void* user_data )
	{
	pixie::repeating_time_event( this, seconds, event_id, user_data );
	}


void pixie::game_state::gamepad_pressed_event( int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data )
	{
	pixie::gamepad_pressed_event( this, pad_index, button, event_id, user_data );
	}


void pixie::game_state::gamepad_released_event( int pad_index, gamepadbutton_id button, string_id const& event_id, void* user_data )
	{
	pixie::gamepad_released_event( this, pad_index, button, event_id, user_data );
	}


void pixie::game_state::gamepad_axis_event( int pad_index, gamepadaxis_id axis, float threshold, string_id const& event_id, void* user_data )
	{
	pixie::gamepad_axis_event( this, pad_index, axis, threshold, event_id, user_data );
	}


void pixie::game_state::key_pressed_event( key_id key, string_id const& event_id, void* user_data ) 
	{
	pixie::key_pressed_event( this, key, event_id, user_data );
	}


void pixie::game_state::key_released_event( key_id key, string_id const& event_id, void* user_data ) 
	{
	pixie::key_released_event( this, key, event_id, user_data );
	}


void pixie::game_state::ascii_event( char ascii, string_id const& event_id, void* user_data ) 
	{
	pixie::ascii_event( this, ascii, event_id, user_data );
	}


void pixie::game_state::action_event( string_id const& action, string_id const& event_id, void* user_data )
	{
	pixie::action_event( this, action, event_id, user_data );
	}


void pixie::game_state::action_event( string_id const& action, float threshold, string_id const& event_id, void* user_data )
	{
	pixie::action_event( this, action, threshold, event_id, user_data );
	}


//---------
//  bitmap
//---------

pixie::bitmap::bitmap()
	{
	internal::clear( &internal );
	}


pixie::bitmap::bitmap( int width, int height )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		storage += width * height;
		}
	}


pixie::bitmap::bitmap( int width, int height, u8* pixels, int transparent_index )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels, width * height * sizeof( u8 ) );
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		for( int j = 0; j < width * height; ++j )
			storage[ j ] = ( pixels[ j ] == transparent_index ) ? (u8)0 : (u8)255;
		storage += width * height;
		}
	}


pixie::bitmap::bitmap( int width, int height, u8* pixels, u8* mask )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels, width * height * sizeof( u8 ) );
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		memcpy( storage, mask, width * height * sizeof( u8 ) );
		storage += width * height;
		}
	}


pixie::bitmap::bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = pitch_x * pitch_y * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x;
		internal.cels_normal[ i ].offset_y = offset_y;
		internal.cels_normal[ i ].pitch_x = pitch_x;
		internal.cels_normal[ i ].pitch_y = pitch_y;
		internal.cels_normal[ i ].pixels = storage;
		storage += pitch_x * pitch_y;
		internal.cels_normal[ i ].mask = storage;   
		storage += pitch_x * pitch_y;
		}
	}


pixie::bitmap::bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y, u8* pixels, int transparent_index )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = pitch_x * pitch_y * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x;
		internal.cels_normal[ i ].offset_y = offset_y;
		internal.cels_normal[ i ].pitch_x = pitch_x;
		internal.cels_normal[ i ].pitch_y = pitch_y;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels, pitch_x * pitch_y * sizeof( u8 ) );
		storage += pitch_x * pitch_y;
		internal.cels_normal[ i ].mask = storage;   
		for( int j = 0; j < pitch_x * pitch_y; ++j )
			storage[ j ] = ( pixels[ j ] == transparent_index ) ? (u8)0 : (u8)255;
		storage += pitch_x * pitch_y;
		}
	}


pixie::bitmap::bitmap( int width, int height, int offset_x, int offset_y, int pitch_x, int pitch_y, u8* pixels, u8* mask )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	int const cel_count = 1;
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = pitch_x * pitch_y * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x;
		internal.cels_normal[ i ].offset_y = offset_y;
		internal.cels_normal[ i ].pitch_x = pitch_x;
		internal.cels_normal[ i ].pitch_y = pitch_y;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels, pitch_x * pitch_y * sizeof( u8 ) );
		storage += pitch_x * pitch_y;
		internal.cels_normal[ i ].mask = storage;   
		memcpy( storage, mask, pitch_x * pitch_y * sizeof( u8 ) );
		storage += pitch_x * pitch_y;
		}
	}


pixie::bitmap::bitmap( int width, int height, int cel_count )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		storage += width * height;
		}
	}


pixie::bitmap::bitmap( int width, int height, int cel_count, u8* pixels[], int transparent_index )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels[ i ], width * height * sizeof( u8 ) );
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		for( int j = 0; j < width * height; ++j )
			storage[ j ] = ( pixels[ i ][ j ] == transparent_index ) ? (u8)0 : (u8)255;
		storage += width * height;
		}
	}


pixie::bitmap::bitmap( int width, int height, int cel_count, u8* pixels[], u8* masks[] )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = width * height * sizeof( u8 ) * 2 * cel_count + sizeof( internal_t::normal_cel ) * cel_count;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = 0;
		internal.cels_normal[ i ].offset_y = 0;
		internal.cels_normal[ i ].pitch_x = width;
		internal.cels_normal[ i ].pitch_y = height;
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels[ i ], width * height * sizeof( u8 ) );
		storage += width * height;
		internal.cels_normal[ i ].mask = storage;   
		memcpy( storage, masks[ i ], width * height * sizeof( u8 ) );
		storage += width * height;
		}
	}

pixie::bitmap::bitmap( int width, int height, int cel_count, int offset_x[], int offset_y[], int pitch_x[], int pitch_y[] )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		size += pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) * 2;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	memset( storage, 0, size ); 
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x[ i ];
		internal.cels_normal[ i ].offset_y = offset_y[ i ];
		internal.cels_normal[ i ].pitch_x = pitch_x[ i ];
		internal.cels_normal[ i ].pitch_y = pitch_y[ i ];
		internal.cels_normal[ i ].pixels = storage;
		storage += pitch_x[ i ] * pitch_y[ i ];
		internal.cels_normal[ i ].mask = storage;   
		storage += pitch_x[ i ] * pitch_y[ i ];
		}
	}


pixie::bitmap::bitmap( int width, int height, int cel_count, int offset_x[], int offset_y[], int pitch_x[], int pitch_y[], u8* pixels[], int transparent_index )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		size += pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) * ( transparent_index >= 0 && transparent_index <= 255 ? 2 : 1 );
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x[ i ];
		internal.cels_normal[ i ].offset_y = offset_y[ i ];
		internal.cels_normal[ i ].pitch_x = pitch_x[ i ];
		internal.cels_normal[ i ].pitch_y = pitch_y[ i ];
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels[ i ], pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) );
		storage += pitch_x[ i ] * pitch_y[ i ];
		internal.cels_normal[ i ].mask = storage;   
		for( int j = 0; j < pitch_x[ i ] * pitch_y[ i ]; ++j )
			storage[ j ] = ( pixels[ i ][ j ] == transparent_index ) ? (u8)0 : (u8)255;
		storage += pitch_x[ i ] * pitch_y[ i ];
		}
	}


pixie::bitmap::bitmap( int width, int height, int cel_count, int offset_x[], int offset_y[], int pitch_x[], int pitch_y[], u8* pixels[], u8* masks[] )
	{
	internal::internals_t* internals = internal::internals();

	internal::clear( &internal );
	internal.cel_count = cel_count;
	internal.width = width;
	internal.height = height;    
	size_t size = sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		size += pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) * 2;
	u8* storage = (u8*) TRACKED_MALLOC( internals->memctx, size );
	internal.storage = storage;
	internal.type = internal_t::DATA_TYPE_NORMAL;
	internal.cels_normal = (internal_t::normal_cel*) storage;
	storage += sizeof( internal_t::normal_cel ) * cel_count;
	for( int i = 0; i < cel_count; ++i )
		{       
		internal.cels_normal[ i ].offset_x = offset_x[ i ];
		internal.cels_normal[ i ].offset_y = offset_y[ i ];
		internal.cels_normal[ i ].pitch_x = pitch_x[ i ];
		internal.cels_normal[ i ].pitch_y = pitch_y[ i ];
		internal.cels_normal[ i ].pixels = storage;
		memcpy( storage, pixels[ i ], pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) );
		storage += pitch_x[ i ] * pitch_y[ i ];
		internal.cels_normal[ i ].mask = storage;   
		memcpy( storage, masks[ i ], pitch_x[ i ] * pitch_y[ i ] * sizeof( u8 ) );
		storage += pitch_x[ i ] * pitch_y[ i ];
		}
	}


pixie::bitmap::~bitmap()
	{
	PIXIE_ASSERT( internal.lock_count == 0, "Bitmap still locked" );
	internal::internals_t* internals = internal::internals();
	if( internal.storage ) TRACKED_FREE( internals->memctx, internal.storage );
	}


int pixie::bitmap::cel_count() const
	{
	return internal.cel_count;
	}


int pixie::bitmap::width() const
	{
	return internal.width;
	}


int pixie::bitmap::height() const
	{
	return internal.height;
	}


void pixie::bitmap::pixel( int cel, int x, int y, int color )
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			break;
		case internal_t::DATA_TYPE_NORMAL:
			x -= internal.cels_normal[ cel ].offset_x;
			y -= internal.cels_normal[ cel ].offset_y;
			if( cel >= 0 && cel < internal.cel_count && x >= 0 && x < internal.cels_normal[ cel ].pitch_x && y >= 0 && y < internal.cels_normal[ cel ].pitch_y )
				internal.cels_normal[ cel ].pixels[ x + y * internal.cels_normal[ cel ].pitch_x ] = (u8) color;
			break;
		}
	}


int pixie::bitmap::pixel( int cel, int x, int y ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			break;
		case internal_t::DATA_TYPE_NORMAL:
			x -= internal.cels_normal[ cel ].offset_x;
			y -= internal.cels_normal[ cel ].offset_y;
			if( cel >= 0 && cel < internal.cel_count && x >= 0 && x < internal.cels_normal[ cel ].pitch_x && y >= 0 && y < internal.cels_normal[ cel ].pitch_y )
				return (int) internal.cels_normal[ cel ].pixels[ x + y * internal.cels_normal[ cel ].pitch_x ];
			break;
		}

	return 0;
	}


void pixie::bitmap::mask( int cel, int x, int y, bool opaque )
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			break;
		case internal_t::DATA_TYPE_NORMAL:
			if( !internal.cels_normal[ cel ].mask ) return;
			x -= internal.cels_normal[ cel ].offset_x;
			y -= internal.cels_normal[ cel ].offset_y;
			if( cel >= 0 && cel < internal.cel_count && internal.cels_normal[ cel ].mask && x >= 0 && x < internal.cels_normal[ cel ].pitch_x && y >= 0 && y < internal.cels_normal[ cel ].pitch_y )
				internal.cels_normal[ cel ].mask[ x + y * internal.cels_normal[ cel ].pitch_x ] = opaque ? (u8)255 : (u8)0;
			break;
		}
	}


bool pixie::bitmap::mask( int cel, int x, int y ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			break;
		case internal_t::DATA_TYPE_NORMAL:
			if( !internal.cels_normal[ cel ].mask ) return true;
			x -= internal.cels_normal[ cel ].offset_x;
			y -= internal.cels_normal[ cel ].offset_y;
			if( cel >= 0 && cel < internal.cel_count && x >= 0 && x < internal.cels_normal[ cel ].pitch_x && y >= 0 && y < internal.cels_normal[ cel ].pitch_y )
				return internal.cels_normal[ cel ].mask[ x + y * internal.cels_normal[ cel ].pitch_x ] != 0;
			break;
		}

	return false;
	}


void pixie::bitmap::lock( lock_data* data )
	{
	++internal.lock_count;
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			data->offset_x = 0;
			data->offset_y = 0;
			data->pitch_x = 0;
			data->pitch_y = 0;
			data->pixels = 0;
			data->mask = 0;
			break;
		case internal_t::DATA_TYPE_NORMAL:
			data->offset_x = internal.cels_normal[ 0 ].offset_x;
			data->offset_y = internal.cels_normal[ 0 ].offset_y;
			data->pitch_x = internal.cels_normal[ 0 ].pitch_x;
			data->pitch_y = internal.cels_normal[ 0 ].pitch_y;
			data->pixels = internal.cels_normal[ 0 ].pixels;
			data->mask = internal.cels_normal[ 0 ].mask;
			break;
		}
	}


void pixie::bitmap::lock( int cel, lock_data* data )
	{
	++internal.lock_count;
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			data->offset_x = 0;
			data->offset_y = 0;
			data->pitch_x = 0;
			data->pitch_y = 0;
			data->pixels = 0;
			data->mask = 0;
			break;
		case internal_t::DATA_TYPE_NORMAL:
			data->offset_x = internal.cels_normal[ cel ].offset_x;
			data->offset_y = internal.cels_normal[ cel ].offset_y;
			data->pitch_x = internal.cels_normal[ cel ].pitch_x;
			data->pitch_y = internal.cels_normal[ cel ].pitch_y;
			data->pixels = internal.cels_normal[ cel ].pixels;
			data->mask = internal.cels_normal[ cel ].mask;
			break;
		}
	}


void pixie::bitmap::unlock()
	{
	--internal.lock_count;
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE:
			break;
		case internal_t::DATA_TYPE_NORMAL:
			// no need to do anything
			break;
		}
	}


void pixie::bitmap::blit( bitmap* target, int x, int y )
	{
	blit( 0, 0, 0, internal.width - 1, internal.height - 1, target, x, y );
	}


void pixie::bitmap::blit( int x1, int y1, int x2, int y2, bitmap* target, int x, int y )
	{
	blit( 0, x1, y1, x2, y2, target, x, y );
	}


void pixie::bitmap::blit( int cel, bitmap* target, int x, int y )
	{
	blit( cel, 0, 0, internal.width - 1, internal.height - 1, target, x, y );
	}


void pixie::bitmap::blit( int cel, int x1, int y1, int x2, int y2, bitmap* target, int x, int y )
	{
	struct local
		{
		struct rect { int x, y, w, h; };

		static rect intersect( rect const& a, rect const& b )
			{
			int x1 = a.x;
			int y1 = a.y;
			int x2 = a.x + a.w - 1;
			int y2 = a.y + a.h - 1;

			int x3 = b.x;
			int y3 = b.y;
			int x4 = b.x + b.w - 1;
			int y4 = b.y + b.h - 1;

			int x5 = pixie::max( x1, x3 );
			int y5 = pixie::max( y1, y3 );
			int x6 = pixie::min( x2, x4 );
			int y6 = pixie::min( y2, y4 );

			rect out;
			out.x = x5;
			out.y = y5;
			out.w = x6 - x5 + 1;
			out.h = y6 - y5 + 1;
			if( out.w <= 0 ) out.w = 0;
			if( out.h <= 0 ) out.h = 0;
			return out;
			}

		static void clip( rect* src_blit, rect* src_data, rect* dst_blit, rect* dst_data )
			{
			rect src = intersect( *src_blit, *src_data );
			dst_blit->x += src.x - src_blit->x;
			dst_blit->y += src.y - src_blit->y;
			dst_blit->w = src.w;
			dst_blit->h = src.h;
			rect dst = intersect( *dst_blit, *dst_data );
			src.x += dst.x - dst_blit->x;
			src.y += dst.y - dst_blit->y;
			src.w = dst.w;
			src.h = dst.h;
			*src_blit = src;
			*dst_blit = dst;
			}
		};

	if( internal.type == internal_t::DATA_TYPE_NORMAL && target->internal.type == internal_t::DATA_TYPE_NORMAL )
		{
		local::rect src_blit = { x1, y1, x2 - x1 + 1, y2 - y1 + 1, };
		local::rect src_data = { internal.cels_normal[ cel ].offset_x, internal.cels_normal[ cel ].offset_y, 
			internal.cels_normal[ cel ].pitch_x, internal.cels_normal[ cel ].pitch_y, };
		local::rect dst_blit = { x, y, src_blit.w, src_blit.h, };
		local::rect dst_data = { target->internal.cels_normal[ 0 ].offset_x, target->internal.cels_normal[ 0 ].offset_y,
			target->internal.cels_normal[ 0 ].pitch_x, target->internal.cels_normal[ 0 ].pitch_y, };

		local::clip( &src_blit, &src_data, &dst_blit, &dst_data );
		if( src_blit.w == 0 || src_blit.h == 0 ) return;

		src_blit.x -= internal.cels_normal[ cel ].offset_x;
		src_blit.y -= internal.cels_normal[ cel ].offset_y;
		dst_blit.x -= target->internal.cels_normal[ 0 ].offset_x;
		dst_blit.y -= target->internal.cels_normal[ 0 ].offset_y;

		u8* src_pixels = internal.cels_normal[ cel ].pixels;
		if( src_pixels ) src_pixels += src_blit.x + src_blit.y * internal.cels_normal[ cel ].pitch_x;

		u8* src_mask = internal.cels_normal[ cel ].mask;
		if( src_mask ) src_mask += src_blit.x + src_blit.y * internal.cels_normal[ cel ].pitch_x;
		
		u8* dst_pixels = target->internal.cels_normal[ 0 ].pixels;
		if( dst_pixels ) dst_pixels += dst_blit.x + dst_blit.y * target->internal.cels_normal[ 0 ].pitch_x;
		
		u8* dst_mask = target->internal.cels_normal[ 0 ].mask;
		if( dst_mask ) dst_mask += dst_blit.x + dst_blit.y * target->internal.cels_normal[ 0 ].pitch_x;

		if( src_mask && dst_mask )
			{
			int src_delta = internal.cels_normal[ cel ].pitch_x - src_blit.w;
			int dst_delta = target->internal.cels_normal[ 0 ].pitch_x - dst_blit.w;
			for( int iy = 0; iy < src_blit.h; ++iy )
				{
				for( int ix = 0; ix < src_blit.w; ++ix )
					{
					if( *src_mask++ > 0x80 )
						{
						*dst_pixels = *src_pixels;
						*dst_mask = 0xff;
						}
					++src_pixels;
					++dst_pixels;
					++dst_mask;
					}
				src_pixels += src_delta;
				src_mask += src_delta;
				dst_pixels += dst_delta;
				dst_mask += dst_delta;
				}
			}
		else if( src_mask )
			{
			int src_delta = internal.cels_normal[ cel ].pitch_x - src_blit.w;
			int dst_delta = target->internal.cels_normal[ 0 ].pitch_x - dst_blit.w;
			for( int iy = 0; iy < src_blit.h; ++iy )
				{
				for( int ix = 0; ix < src_blit.w; ++ix )
					{
					if( *src_mask++ >= 0x80 ) *dst_pixels = *src_pixels;
					++src_pixels;
					++dst_pixels;
					}
				src_pixels += src_delta;
				src_mask += src_delta;
				dst_pixels += dst_delta;
				}
			}
		else if( dst_mask )
			{
			int src_delta = internal.cels_normal[ cel ].pitch_x;
			int dst_delta = target->internal.cels_normal[ 0 ].pitch_x;
			for( int iy = 0; iy < src_blit.h; ++iy )
				{
				memcpy( dst_pixels, src_pixels, (size_t)src_blit.w );
				memset( dst_mask, 0xff, (size_t)src_blit.w );
				src_pixels += src_delta;
				dst_pixels += dst_delta;
				dst_mask += dst_delta;
				}
			}
		else
			{
			int src_delta = internal.cels_normal[ cel ].pitch_x;
			int dst_delta = target->internal.cels_normal[ 0 ].pitch_x;
			for( int iy = 0; iy < src_blit.h; ++iy )
				{
				memcpy( dst_pixels, src_pixels, (size_t)src_blit.w );
				src_pixels += src_delta;
				dst_pixels += dst_delta;
				}
			}
		}
	}


int pixie::bitmap::offset_x( int cel ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE: return 0;
		case internal_t::DATA_TYPE_NORMAL: return internal.cels_normal[ cel ].offset_x;
		}
		
	return 0;
	}
	
	
int pixie::bitmap::offset_y( int cel ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE: return 0;
		case internal_t::DATA_TYPE_NORMAL: return internal.cels_normal[ cel ].offset_y;
		}
		
	return 0;
	}


int pixie::bitmap::pitch_x( int cel ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE: return 0;
		case internal_t::DATA_TYPE_NORMAL: return internal.cels_normal[ cel ].pitch_x;
		}
		
	return 0;
	}
	
	
int pixie::bitmap::pitch_y( int cel ) const
	{
	switch( internal.type )
		{
		case internal_t::DATA_TYPE_NONE: return 0;
		case internal_t::DATA_TYPE_NORMAL: return internal.cels_normal[ cel ].pitch_y;
		}
		
	return 0;
	}


//-------
//  font
//-------

pixie::font::font()
	{
	internal.pixelfont = 0;
	}


pixie::font::font( void const* data, size_t size )
	{
	(void) size;
	internal::internals_t* internals = internal::internals();

	internal.pixelfont = TRACKED_MALLOC( internals->memctx, size );
	memcpy( internal.pixelfont, data, size );   
	}


pixie::font::~font()
	{
	internal::internals_t* internals = internal::internals();
	if( internal.pixelfont ) TRACKED_FREE( internals->memctx, internal.pixelfont );
	}


int pixie::font::height() const
	{
	return ( (pixelfont_t*) internal.pixelfont )->height;
	}


int pixie::font::line_spacing() const
	{
	return ( (pixelfont_t*) internal.pixelfont )->line_spacing;
	}


int pixie::font::baseline() const
	{
	return ( (pixelfont_t*) internal.pixelfont )->baseline;
	}


void pixie::font::blit( int x, int y, string const& text, u8 color, u8* target, int width, int height, 
	alignment_enum align, int wrap_width, int hspacing, int vspacing, int limit, bool bold, bool italic, 
	bool underline, bounds_t* bounds ) const
	{
	pixelfont_align_t pixelfont_align = PIXELFONT_ALIGN_LEFT;
	if( align == ALIGNMENT_RIGHT ) pixelfont_align = PIXELFONT_ALIGN_RIGHT;
	if( align == ALIGNMENT_CENTER ) pixelfont_align = PIXELFONT_ALIGN_CENTER;

	pixelfont_bounds_t pixelfont_bounds;
	pixelfont_bounds.width = 0;
	pixelfont_bounds.height = 0;

	pixelfont_blit_u8( (pixelfont_t*) internal.pixelfont, x, y, text.c_str(), color, target, width, height, 
		pixelfont_align, wrap_width, hspacing, vspacing, limit, bold ? PIXELFONT_BOLD_ON : PIXELFONT_BOLD_OFF, 
		italic ? PIXELFONT_ITALIC_ON : PIXELFONT_ITALIC_OFF, underline ? PIXELFONT_UNDERLINE_ON : PIXELFONT_UNDERLINE_OFF, 
		bounds ? &pixelfont_bounds : 0 );

	if( bounds )
		{
		bounds->width = pixelfont_bounds.width;
		bounds->height = pixelfont_bounds.height;
		}
	}


void pixie::font::blit( int x, int y, string const& text, u32 color, u32* target, int width, int height, 
	alignment_enum align, int wrap_width, int hspacing, int vspacing, int limit, bool bold, bool italic, 
	bool underline, bounds_t* bounds ) const
	{
	pixelfont_align_t pixelfont_align = PIXELFONT_ALIGN_LEFT;
	if( align == ALIGNMENT_RIGHT ) pixelfont_align = PIXELFONT_ALIGN_RIGHT;
	if( align == ALIGNMENT_CENTER ) pixelfont_align = PIXELFONT_ALIGN_CENTER;

	pixelfont_bounds_t pixelfont_bounds;
	pixelfont_bounds.width = 0;
	pixelfont_bounds.height = 0;

	pixelfont_blit_u32( (pixelfont_t*) internal.pixelfont, x, y, text.c_str(), color, target, width, height, 
		pixelfont_align, wrap_width, hspacing, vspacing, limit, bold ? PIXELFONT_BOLD_ON : PIXELFONT_BOLD_OFF, 
		italic ? PIXELFONT_ITALIC_ON : PIXELFONT_ITALIC_OFF, underline ? PIXELFONT_UNDERLINE_ON : PIXELFONT_UNDERLINE_OFF, 
		bounds ? &pixelfont_bounds : 0 );

	if( bounds )
		{
		bounds->width = pixelfont_bounds.width;
		bounds->height = pixelfont_bounds.height;
		}
	}


void pixie::register_audio_format( audio_format_t format )
	{
	internal::internals_t* internals = internal::internals();
	internals->audio_formats.add( format );
	}


namespace pixie { namespace internal {

audio_instance* audioformat_samples( void* data, size_t size )
	{   
	struct samples_instance
		{
		audio_instance instance;
		int position_in_sample_pairs;
		float* sample_pairs;
		int sample_pairs_count;

		static void release( audio_instance* instance )
			{
			samples_instance* samples = (samples_instance*) instance;

			internal::internals_t* internals = internal::internals();
			TRACKED_FREE( internals->memctx, samples );
			}
		
		static int read_samples( audio_instance* instance, float* sample_pairs, int sample_pairs_count )
			{
			samples_instance* samples = (samples_instance*) instance;
			int count_left = samples->sample_pairs_count - samples->position_in_sample_pairs;
			if( count_left <= 0 ) return 0;
			int to_copy = sample_pairs_count > count_left ? count_left : sample_pairs_count;
			memcpy( sample_pairs, samples->sample_pairs + samples->position_in_sample_pairs * 2, sizeof( float ) * 2 * to_copy );
			samples->position_in_sample_pairs += to_copy;
			return to_copy;
			}

		static void restart( audio_instance* instance )
			{
			samples_instance* samples = (samples_instance*) instance;
			samples->position_in_sample_pairs = 0;
			}      
		
		static void set_position( audio_instance* instance, int offset_in_sample_pairs_from_start )
			{
			samples_instance* samples = (samples_instance*) instance;
			samples->position_in_sample_pairs = offset_in_sample_pairs_from_start;
			}
		
		static int get_position_in_sample_pairs_from_start( audio_instance* instance )
			{
			samples_instance* samples = (samples_instance*) instance;
			return samples->position_in_sample_pairs;
			}
		
		static int get_length_in_sample_pairs( audio_instance* instance )
			{
			samples_instance* samples = (samples_instance*) instance;
			return samples->sample_pairs_count;    
			}        
		};

	internal::internals_t* internals = internal::internals();
	
	samples_instance* instance = (samples_instance*) TRACKED_MALLOC( internals->memctx, sizeof( samples_instance ) ); 

	instance->position_in_sample_pairs = 0;
	instance->sample_pairs = (float*) data;
	instance->sample_pairs_count = (int)( size / ( sizeof( float ) * 2 ) );

	instance->instance.release = samples_instance::release;
	instance->instance.read_samples = samples_instance::read_samples;
	instance->instance.restart = samples_instance::restart;
	instance->instance.set_position = samples_instance::set_position;
	instance->instance.get_position_in_sample_pairs_from_start = samples_instance::get_position_in_sample_pairs_from_start;
	instance->instance.get_length_in_sample_pairs = samples_instance::get_length_in_sample_pairs;
	return (audio_instance*) instance;
	}


audio_instance* audioformat_ogg( void* data, size_t size )
	{   
	if( strnicmp( (char const*) data, "OggS", 4 ) != 0 ) return 0;

	struct ogg_instance
		{
		audio_instance instance;
		stb_vorbis* vorbis;

		static void release( audio_instance* instance )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			stb_vorbis_close( ogg->vorbis );

			internal::internals_t* internals = internal::internals();
			TRACKED_FREE( internals->memctx, ogg );
			}
		
		static int read_samples( audio_instance* instance, float* sample_pairs, int sample_pairs_count )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			return stb_vorbis_get_samples_float_interleaved( ogg->vorbis, 2, sample_pairs, sample_pairs_count * 2 );
			}
		
		static void restart( audio_instance* instance )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			stb_vorbis_seek_start( ogg->vorbis );
			}      
		
		static void set_position( audio_instance* instance, int offset_in_sample_pairs_from_start )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			stb_vorbis_seek( ogg->vorbis, (unsigned int) offset_in_sample_pairs_from_start );
			}
		
		static int get_position_in_sample_pairs_from_start( audio_instance* instance )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			return stb_vorbis_get_sample_offset( ogg->vorbis );
			}
		
		static int get_length_in_sample_pairs( audio_instance* instance )
			{
			ogg_instance* ogg = (ogg_instance*) instance;
			return (int) stb_vorbis_stream_length_in_samples( ogg->vorbis );    
			}        
		};


	internal::internals_t* internals = internal::internals();

	size_t alloc_size = 256 * 1024;
	void* alloc_mem = TRACKED_MALLOC( internals->memctx, alloc_size );

	stb_vorbis_alloc ogg_alloc;
	ogg_alloc.alloc_buffer = ( (char*) alloc_mem ) + sizeof( ogg_instance );
	ogg_alloc.alloc_buffer_length_in_bytes = (int)( alloc_size - sizeof( ogg_instance ) );
	
	int ogg_error = 0;
	stb_vorbis* ogg = stb_vorbis_open_memory( (unsigned char const*) data, (int) size, &ogg_error, &ogg_alloc );
	while( ogg_error == VORBIS_outofmem )
		{
		TRACKED_FREE( internals->memctx, alloc_mem );
		alloc_size *= 2;
		alloc_mem = TRACKED_MALLOC( internals->memctx, alloc_size );

		ogg_alloc.alloc_buffer = ( (char*) alloc_mem ) + sizeof( ogg_instance );
		ogg_alloc.alloc_buffer_length_in_bytes = (int)( alloc_size - sizeof( ogg_instance ) );
		ogg = stb_vorbis_open_memory( (unsigned char const*) data, (int) size, &ogg_error, &ogg_alloc );
		}
		
	PIXIE_ASSERT( ogg_error == VORBIS__no_error, "Failed to load ogg file" );
	if( ogg_error != VORBIS__no_error ) { TRACKED_FREE( internals->memctx, alloc_mem ); return 0; }
		
	stb_vorbis_info info = stb_vorbis_get_info( ogg );
	PIXIE_ASSERT( ( info.channels == 2 || info.channels == 1 ) && info.sample_rate == 44100, "Invalid sound format" );
	if( !( info.channels == 2 || info.channels == 1 ) || info.sample_rate != 44100 )
		{
		TRACKED_FREE( internals->memctx, alloc_mem );
		stb_vorbis_close( ogg );
		return 0;
		}

	ogg_instance* instance = (ogg_instance*) alloc_mem;
	instance->vorbis = ogg;

	instance->instance.release = ogg_instance::release;
	instance->instance.read_samples = ogg_instance::read_samples;
	instance->instance.restart = ogg_instance::restart;
	instance->instance.set_position = ogg_instance::set_position;
	instance->instance.get_position_in_sample_pairs_from_start = ogg_instance::get_position_in_sample_pairs_from_start;
	instance->instance.get_length_in_sample_pairs = ogg_instance::get_length_in_sample_pairs;
	return (audio_instance*) instance;
	}


audio_instance* audioformat_wav( void* data, size_t size )
	{   
	if( strncmp( (char const*) data, "RIFF", 4 ) != 0 ) return 0;

	struct wav_instance
		{
		audio_instance instance;
		drwav wav;
		int position_in_sample_pairs;

		static void release( audio_instance* instance )
			{
			wav_instance* wav = (wav_instance*) instance;

			internal::internals_t* internals = internal::internals();
			TRACKED_FREE( internals->memctx, wav );
			}
		
		static int read_samples( audio_instance* instance, float* sample_pairs, int sample_pairs_count )
			{
			wav_instance* wav = (wav_instance*) instance;
			int count = 0;
			if( wav->wav.channels == 2 )
				{
				count = (int) drwav_read_f32( &wav->wav, (drwav_uint64) sample_pairs_count * 2, sample_pairs ) / 2;
				}
			else
				{
				count = (int) drwav_read_f32( &wav->wav, (drwav_uint64) sample_pairs_count, sample_pairs );
				for( int i = count - 1; i >= 0; --i )
					{
					float s = sample_pairs[ i ];
					sample_pairs[ i * 2 + 0 ] = s;
					sample_pairs[ i * 2 + 1 ] = s;
					}               
				}
			wav->position_in_sample_pairs += count;
			return count;
			}
		
		static void restart( audio_instance* instance )
			{
			wav_instance* wav = (wav_instance*) instance;
			drwav_seek_to_sample( &wav->wav, 0 );
			wav->position_in_sample_pairs = 0;
			}      
		
		static void set_position( audio_instance* instance, int offset_in_sample_pairs_from_start )
			{
			wav_instance* wav = (wav_instance*) instance;
			drwav_seek_to_sample( &wav->wav, (drwav_uint64) offset_in_sample_pairs_from_start );
			wav->position_in_sample_pairs = offset_in_sample_pairs_from_start;
			}
		
		static int get_position_in_sample_pairs_from_start( audio_instance* instance )
			{
			wav_instance* wav = (wav_instance*) instance;
			return wav->position_in_sample_pairs;
			}
		
		static int get_length_in_sample_pairs( audio_instance* instance )
			{
			wav_instance* wav = (wav_instance*) instance;
			return (int) wav->wav.totalSampleCount / 2;    
			}        
		};

	internal::internals_t* internals = internal::internals();
	
	wav_instance* instance = (wav_instance*) TRACKED_MALLOC( internals->memctx,  sizeof( wav_instance ) ); 

	if( !drwav_init_memory( &instance->wav, data, size ) ) return 0;
	PIXIE_ASSERT( ( instance->wav.channels == 2 || instance->wav.channels == 1 ) && instance->wav.sampleRate == 44100, 
		"Invalid sound format" );

	instance->position_in_sample_pairs = 0;

	instance->instance.release = wav_instance::release;
	instance->instance.read_samples = wav_instance::read_samples;
	instance->instance.restart = wav_instance::restart;
	instance->instance.set_position = wav_instance::set_position;
	instance->instance.get_position_in_sample_pairs_from_start = wav_instance::get_position_in_sample_pairs_from_start;
	instance->instance.get_length_in_sample_pairs = wav_instance::get_length_in_sample_pairs;
	return (audio_instance*) instance;
	}


audio_instance* audioformat_mod( void* data, size_t size )
	{   
	if( strncmp( (char const*) data, "MOD", 3 ) != 0 ) return 0;

	struct mod_instance
		{
		audio_instance instance;
		jar_mod_context_t modctx;
		int position_in_sample_pairs;
		int length_in_sample_pairs;

		static void release( audio_instance* instance )
			{
			mod_instance* mod = (mod_instance*) instance;
			jar_mod_unload( &mod->modctx );

			internal::internals_t* internals = internal::internals();
			TRACKED_FREE( internals->memctx, mod );
			}
		
		static int read_samples( audio_instance* instance, float* sample_pairs, int sample_pairs_count )
			{
			mod_instance* mod = (mod_instance*) instance;

			int count = mod->length_in_sample_pairs - mod->position_in_sample_pairs;
			PIXIE_ASSERT( count >= 0, "Invalid sound position" );
			if( count > sample_pairs_count ) count = sample_pairs_count;
			
			jar_mod_fillbuffer( &mod->modctx, (short*) sample_pairs, (unsigned long) count, 0 );
			for( int i = count * 2 - 1; i >= 0; --i )
				sample_pairs[ i  ] = ( ( (short*) sample_pairs )[ i ] ) / 32000.0f;

			mod->position_in_sample_pairs += count;
			return count; 
			}

		static void restart( audio_instance* instance )
			{
			mod_instance* mod = (mod_instance*) instance;
			jar_mod_seek_start( &mod->modctx );
			mod->position_in_sample_pairs = 0;
			}      
		
		static int get_position_in_sample_pairs_from_start( audio_instance* instance )
			{
			mod_instance* mod = (mod_instance*) instance;
			return mod->position_in_sample_pairs;
			}
		
		};


	internal::internals_t* internals = internal::internals();
	
	mod_instance* instance = (mod_instance*) TRACKED_MALLOC( internals->memctx, sizeof( mod_instance ) ); 
	if( !jar_mod_init( &instance->modctx ) ) { TRACKED_FREE( internals->memctx, instance ); return 0; }
	if( !jar_mod_setcfg( &instance->modctx, 44100, 16, 2, 0, 0 ) ) { TRACKED_FREE( internals->memctx, instance ); return 0; }
	if( !jar_mod_load( &instance->modctx, data, (int) size ) ) { TRACKED_FREE( internals->memctx, instance ); return 0; }
	
	instance->position_in_sample_pairs = 0;
	instance->length_in_sample_pairs = (int) jar_mod_max_samples( &instance->modctx );

	instance->instance.release = mod_instance::release;
	instance->instance.read_samples = mod_instance::read_samples;
	instance->instance.restart = mod_instance::restart;
	instance->instance.set_position = 0;
	instance->instance.get_position_in_sample_pairs_from_start = mod_instance::get_position_in_sample_pairs_from_start;
	instance->instance.get_length_in_sample_pairs = 0;
	return (audio_instance*) instance;
	}


audio_instance* audioformat_xm( void* data, size_t size )
	{   
	if( strncmp( (char const*) data, "Extended Module: ", 17 ) != 0 ) return 0;

	struct xm_instance
		{
		audio_instance instance;
		size_t size_required;
		jar_xm_context_t* musicptr;
		void* data;
		size_t size;
		int position_in_sample_pairs;

		static void release( audio_instance* instance )
			{
			xm_instance* xm = (xm_instance*) instance;
			jar_xm_free_context( xm->musicptr );

			internal::internals_t* internals = internal::internals();
			TRACKED_FREE( internals->memctx, xm );
			}
		
		static int read_samples( audio_instance* instance, float* sample_pairs, int sample_pairs_count )
			{
			xm_instance* xm = (xm_instance*) instance;
			int count = jar_xm_generate_samples( xm->musicptr, sample_pairs, (size_t) sample_pairs_count );
			xm->position_in_sample_pairs += count;
			return count;
			}
		
		static void restart( audio_instance* instance )
			{
			xm_instance* xm = (xm_instance*) instance;
			jar_xm_free_context( xm->musicptr );
			char* mempool = (char*)( xm + 1 );
			jar_xm_create_context_mempool( &xm->musicptr, (char const*) xm->data, xm->size, 44100, 
				mempool, xm->size_required );
			jar_xm_set_max_loop_count( xm->musicptr, 1 );
			xm->position_in_sample_pairs = 0;
			}      
		
		static int get_position_in_sample_pairs_from_start( audio_instance* instance )
			{
			xm_instance* xm = (xm_instance*) instance;
			return xm->position_in_sample_pairs;
			}
		
		};


	internal::internals_t* internals = internal::internals();

	size_t size_required = jar_xm_get_memory_needed_for_context( (char const*) data, size );
	xm_instance* instance = (xm_instance*) TRACKED_MALLOC( internals->memctx, sizeof( xm_instance ) + size_required );
	char* mempool = (char*)( instance + 1 );
	if( jar_xm_create_context_mempool( &instance->musicptr, (char const*) data, size, 44100, mempool, size_required ) != 0 ) 
		{
		TRACKED_FREE( internals->memctx, instance );
		return 0;
		}
	jar_xm_set_max_loop_count( instance->musicptr, 1 );
	
	instance->size_required = size_required;
	instance->data = data;
	instance->size = size;
	instance->position_in_sample_pairs = 0;

	instance->instance.release = xm_instance::release;
	instance->instance.read_samples = xm_instance::read_samples;
	instance->instance.restart = xm_instance::restart;
	instance->instance.set_position = 0;
	instance->instance.get_position_in_sample_pairs_from_start = xm_instance::get_position_in_sample_pairs_from_start;
	instance->instance.get_length_in_sample_pairs = 0;
	return (audio_instance*) instance;
	}



} /* namespace internal */ } /* namespace pixie */


//--------
//  audio
//--------

namespace pixie { namespace internal {

void samples_delete( void* instance )
	{
	internal::internals_t* internals = internal::internals();
	binary* bin = (binary*) instance;
	TRACKED_FREE( internals->memctx, bin->data ); 
	TRACKED_FREE( internals->memctx, bin ); 
	}

} /* namespace internal */ } /*namespace pixie */


pixie::audio::audio()    
	{
	internal.format = 0;
	internal.length = 0.0f;
	internal.instance_count = 0;
	}
	

pixie::audio::audio( ref<binary> bin )
	{
	internal.format = 0;
	internal.length = 0.0f;
	internal.instance_count = 0;
	if( bin->size < 8 ) return;

	internal::internals_t* internals = internal::internals();

	for( int i = 0; i < internals->audio_formats.count(); ++i )
		{
		pixie::audio_instance* instance = internals->audio_formats[ i ]( bin->data, bin->size );
		if( instance ) 
			{
			internal.bin = bin;
			internal.format = internals->audio_formats[ i ];
			if( instance->get_length_in_sample_pairs ) 
				internal.length = instance->get_length_in_sample_pairs( instance ) / 44100.0f;
			instance->release( instance );
			return;
			}
		}

	// no format recognized the data - assume raw samples
	internal.bin = bin;
	internal.format = internal::audioformat_samples;
	internal.length = ( internal.bin->size / ( sizeof( float ) * 2 ) ) / 44100.0f;
	}


pixie::audio::audio( float* sample_pairs, int sample_pairs_count, bool take_ownership_of_memory )
	{
	internal.format = internal::audioformat_samples;
	internal.length = sample_pairs_count / 44100.0f;
	internal.instance_count = 0;

	internal::internals_t* internals = internal::internals();

	size_t size = sample_pairs_count * sizeof( float ) * 2;        
	if( take_ownership_of_memory )
		{
		binary* bin = (binary*) TRACKED_MALLOC( internals->memctx, sizeof( binary ) + sizeof( int ) ); 
		bin->data = (u8*) sample_pairs;
		bin->size = size;
		internal.bin = refcount::make_ref( bin, internal::samples_delete, (int*)( bin + 1 ), 0 );
		}
	else
		{
		void* storage = TRACKED_MALLOC( internals->memctx, sizeof( binary ) + sizeof( int ) + size ); 
		binary* bin = (binary*)storage;
		bin->data = (u8*) ( ( (uintptr_t) storage ) + sizeof( binary ) + sizeof( int ) );
		bin->size = size;
		memcpy( bin->data, sample_pairs, size );
		internal.bin = refcount::make_ref( bin, internal::binary_delete, (int*)( ( (uintptr_t) storage ) + sizeof( binary ) ), 0 );
		}
	}


pixie::audio::~audio()
	{
	PIXIE_ASSERT( internal.instance_count == 0, "Some audio instances were not destroyed before audio resource was released." );
	}
	

float pixie::audio::length() const 
	{ 
	return internal.length; 
	} 

	
 pixie::audio_instance* pixie::audio::create_instance()
	{
	if( internal.format == 0 ) return 0;

	audio_instance* instance = internal.format( internal.bin->data, internal.bin->size );
	if( instance ) ++internal.instance_count;
	return instance;
	}


void pixie::audio::destroy_instance( audio_instance* instance )
	{
	PIXIE_ASSERT( internal.instance_count > 0, "Invalid instance count" );
	if( instance->release ) instance->release( instance );
	--internal.instance_count;
	}
	

//--------
//  graph
//--------

static pixie::u8 default_fill_patterns[] = 
	{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,
	1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,
	1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,
	0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,
	0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
	0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,
	0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,
	0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,1,0,0,1,0,0,1,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,1,1,
	0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,
	0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,
	1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,1,1,1,0,0,0,1,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1,
	1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,
	0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,
	0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,1,1,1,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,
	0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,
	0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,
	0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,1,1,0,
	1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	};


void pixie::fill_style( fill_pattern pattern, int background_color )
	{
	internal::internals_t* internals = internal::internals();
	internals->fill_style_pattern = pattern;
	internals->fill_style_bgcolor = background_color;
	}


void pixie::clear()
	{
	internal::internals_t* internals = internal::internals();
	clear( &internals->screen_bitmap );
	}


void pixie::fill( int color )
	{
	internal::internals_t* internals = internal::internals();
	fill( &internals->screen_bitmap, color );
	}


void pixie::pset( int x, int y, int color )
	{
	internal::internals_t* internals = internal::internals();
	pset( &internals->screen_bitmap, x, y, color );
	}

void pixie::line( int x1, int y1, int x2, int y2, int color )
	{
	internal::internals_t* internals = internal::internals();
	line( &internals->screen_bitmap, x1, y1, x2, y2, color );
	}


void pixie::box( int x1, int y1, int x2, int y2, int color )
	{
	internal::internals_t* internals = internal::internals();
	box( &internals->screen_bitmap, x1, y1, x2, y2, color );
	}


void pixie::box_fill( int x1, int y1, int x2, int y2, int color )
	{
	internal::internals_t* internals = internal::internals();
	box_fill( &internals->screen_bitmap, x1, y1, x2, y2, color );
	}


void pixie::circle( int x, int y, int r, int color )
	{
	internal::internals_t* internals = internal::internals();
	circle( &internals->screen_bitmap, x, y, r, color );
	}


void pixie::circle_fill( int x, int y, int r, int color )
	{
	internal::internals_t* internals = internal::internals();
	circle_fill( &internals->screen_bitmap, x, y, r, color );
	}


void pixie::ellipse( int x, int y, int rx, int ry, int color )
	{
	internal::internals_t* internals = internal::internals();
	ellipse( &internals->screen_bitmap, x, y, rx, ry, color );
	}


void pixie::ellipse_fill( int x, int y, int rx, int ry, int color )
	{
	internal::internals_t* internals = internal::internals();
	ellipse_fill( &internals->screen_bitmap, x, y, rx, ry, color );
	}


void pixie::polygon( point const* points, int count, int color )
	{
	internal::internals_t* internals = internal::internals();
	polygon( &internals->screen_bitmap, points, count, color );
	}


void pixie::polygon_fill( point const* points, int count, int color )
	{
	internal::internals_t* internals = internal::internals();
	polygon_fill( &internals->screen_bitmap, points, count, color );
	}


void pixie::text( int x, int y, string const& str, int color, resource<font> const& font_resource, text_align align, 
	int wrap_width, int hspacing, int vspacing, int limit, bool bold, bool italic, bool underline )
	{
	internal::internals_t* internals = internal::internals();
	text( &internals->screen_bitmap, x, y, str, color, font_resource, align, wrap_width, hspacing, vspacing, limit, bold,
		italic, underline );
	}


void pixie::clear( bitmap* target )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	memset( lock.pixels, 0, (size_t) lock.pitch_x * lock.pitch_y );

	if( lock.mask ) memset( lock.mask, 0, (size_t) lock.pitch_x * lock.pitch_y );

	target->unlock();
	}


void pixie::fill( bitmap* target, int color )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->fill_style_pattern == FILL_PATTERN_SOLID )
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		memset( lock.pixels, color, (size_t) lock.pitch_x * lock.pitch_y );

		if( lock.mask ) memset( lock.mask, 0xff, (size_t) lock.pitch_x * lock.pitch_y );

		target->unlock();
		}
	else
		{
		box_fill( target, 0, 0, target->width() - 1, target->height() - 1, color );
		}
	}


void pixie::pset( bitmap* target, int x, int y, int color )
	{
	target->pixel( 0, x, y, color );
	target->mask( 0, x, y, true );
	}

void pixie::line( bitmap* target, int x1, int y1, int x2, int y2, int color )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	x1 -= lock.offset_x;
	y1 -= lock.offset_y;
	x2 -= lock.offset_x;
	y2 -= lock.offset_y;

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
	graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
	graph_pixels.line( x1, y1, x2, y2, (u8) color );

	if( lock.mask )
		{
		internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
		graph_mask.line( x1, y1, x2, y2, 255 );
		}

	target->unlock();
	}


void pixie::box( bitmap* target, int x1, int y1, int x2, int y2, int color )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	x1 -= lock.offset_x;
	y1 -= lock.offset_y;
	x2 -= lock.offset_x;
	y2 -= lock.offset_y;

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
	graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
	graph_pixels.box( x1, y1, x2 - x1 + 1, y2 - y1 + 1, (u8) color );

	if( lock.mask )
		{
		internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
		graph_mask.box( x1, y1, x2 - x1 + 1, y2 - y1 + 1, 255 );
		}

	target->unlock();
	}


void pixie::box_fill( bitmap* target, int x1, int y1, int x2, int y2, int color )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->fill_style_pattern == FILL_PATTERN_SOLID )
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x1 -= lock.offset_x;
		y1 -= lock.offset_y;
		x2 -= lock.offset_x;
		y2 -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
		graph_pixels.box_fill( x1, y1, x2 - x1 + 1, y2 - y1 + 1, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
			graph_mask.box_fill( x1, y1, x2 - x1 + 1, y2 - y1 + 1, 255 );
			}

		target->unlock();
		}
	else
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x1 -= lock.offset_x;
		y1 -= lock.offset_y;
		x2 -= lock.offset_x;
		y2 -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen_pattern scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 
			(u8) color, (u8) internals->fill_style_bgcolor );
		graph_ns::graph<internal::pal_screen_pattern, u8> graph_pixels( &scr_pixels );
		graph_pixels.box_fill( x1, y1, x2 - x1 + 1, y2 - y1 + 1, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen_pattern scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 255, 0 );
			graph_ns::graph<internal::pal_screen_pattern, u8> graph_mask( &scr_mask );
			graph_mask.box_fill( x1, y1, x2 - x1 + 1, y2 - y1 + 1, 255 );
			}

		target->unlock();
		}
	}


void pixie::circle( bitmap* target, int x, int y, int r, int color )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	x -= lock.offset_x;
	y -= lock.offset_y;

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
	graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
	graph_pixels.circle( x, y, r, (u8) color );

	if( lock.mask )
		{
		internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
		graph_mask.circle( x, y, r, 255 );
		}

	target->unlock();
	}


void pixie::circle_fill( bitmap* target, int x, int y, int r, int color )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->fill_style_pattern == FILL_PATTERN_SOLID )
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x -= lock.offset_x;
		y -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
		graph_pixels.circle_fill( x, y, r, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
			graph_mask.circle_fill( x, y, r, 255 );
			}

		target->unlock();
		}
	else
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x -= lock.offset_x;
		y -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen_pattern scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 
			(u8) color, (u8) internals->fill_style_bgcolor );
		graph_ns::graph<internal::pal_screen_pattern, u8> graph_pixels( &scr_pixels );
		graph_pixels.circle_fill( x, y, r, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen_pattern scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 255, 0 );
			graph_ns::graph<internal::pal_screen_pattern, u8> graph_mask( &scr_mask );
			graph_mask.circle_fill( x, y, r, 255 );
			}

		target->unlock();
		}
	}


void pixie::ellipse( bitmap* target, int x, int y, int rx, int ry, int color )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	x -= lock.offset_x;
	y -= lock.offset_y;

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
	graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
	graph_pixels.ellipse( x, y, rx, ry, (u8) color );

	if( lock.mask )
		{
		internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
		graph_mask.ellipse( x, y, rx, ry, 255 );
		}

	target->unlock();
	}


void pixie::ellipse_fill( bitmap* target, int x, int y, int rx, int ry, int color )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->fill_style_pattern == FILL_PATTERN_SOLID )
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x -= lock.offset_x;
		y -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
		graph_pixels.ellipse_fill( x, y, rx, ry, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
			graph_mask.ellipse_fill( x, y, rx, ry, 255 );
			}

		target->unlock();
		}
	else
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		x -= lock.offset_x;
		y -= lock.offset_y;

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen_pattern scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 
			(u8) color, (u8) internals->fill_style_bgcolor );
		graph_ns::graph<internal::pal_screen_pattern, u8> graph_pixels( &scr_pixels );
		graph_pixels.ellipse_fill( x, y, rx, ry, (u8) color );

		if( lock.mask )
			{
			internal::pal_screen_pattern scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 255, 0 );
			graph_ns::graph<internal::pal_screen_pattern, u8> graph_mask( &scr_mask );
			graph_mask.ellipse_fill( x, y, rx, ry, 255 );
			}

		target->unlock();
		}
	}


void pixie::polygon( bitmap* target, point const* points, int count, int color )
	{
	bitmap::lock_data lock;
	target->lock( &lock );

	for( int i = 0; i < count; ++i )
		{
		((point*)points)[ i ].x -= lock.offset_x;
		((point*)points)[ i ].y -= lock.offset_y;
		}

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
	graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
	graph_pixels.polygon( (int*)points, count, (u8) color );
  
	if( lock.mask )
		{
		internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
		graph_mask.polygon( (int*)points, count, 255 );
		}

	target->unlock();
	}


void pixie::polygon_fill( bitmap* target, point const* points, int count, int color )
	{
	internal::internals_t* internals = internal::internals();
	if( internals->fill_style_pattern == FILL_PATTERN_SOLID )
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		for( int i = 0; i < count; ++i )
			{
			((point*)points)[ i ].x -= lock.offset_x;
			((point*)points)[ i ].y -= lock.offset_y;
			}

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		graph_ns::graph<internal::pal_screen, u8> graph_pixels( &scr_pixels );
		graph_pixels.polygon_fill<256>( (int*)points, count, (u8) color );
  
		if( lock.mask )
			{
			internal::pal_screen scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			graph_ns::graph<internal::pal_screen, u8> graph_mask( &scr_mask );
			graph_mask.polygon_fill<256>( (int*)points, count, 255 );
			}

		target->unlock();
		}
	else
		{
		bitmap::lock_data lock;
		target->lock( &lock );

		for( int i = 0; i < count; ++i )
			{
			((point*)points)[ i ].x -= lock.offset_x;
			((point*)points)[ i ].y -= lock.offset_y;
			}

		PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
		internal::pal_screen_pattern scr_pixels = { lock.pixels, lock.pitch_x, lock.pitch_y };
		scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 
			(u8) color, (u8) internals->fill_style_bgcolor );
		graph_ns::graph<internal::pal_screen_pattern, u8> graph_pixels( &scr_pixels );
		graph_pixels.polygon_fill<256>( (int*)points, count, (u8) color );
  
		if( lock.mask )
			{
			internal::pal_screen_pattern scr_mask = { lock.mask, lock.pitch_x, lock.pitch_y };
			scr_pixels.set_fill_pattern( &default_fill_patterns[ 64 * (int)internals->fill_style_pattern ], 255, 0 );
			graph_ns::graph<internal::pal_screen_pattern, u8> graph_mask( &scr_mask );
			graph_mask.polygon_fill<256>( (int*)points, count, 255 );
			}

		target->unlock();
		}
	}


void pixie::text( bitmap* target, int x, int y, string const& str, int color, resource<font> const& font_resource, 
	text_align align, int wrap_width, int hspacing, int vspacing, int limit, bool bold, bool italic, bool underline )
	{
	font::alignment_enum font_align = font::ALIGNMENT_LEFT;
	if( align == TEXT_ALIGN_CENTER ) font_align = font::ALIGNMENT_CENTER;
	if( align == TEXT_ALIGN_RIGHT ) font_align = font::ALIGNMENT_RIGHT;

	bitmap::lock_data lock;
	target->lock( &lock );

	x -= lock.offset_x;
	y -= lock.offset_y;

	PIXIE_ASSERT( lock.pixels, "Failed to lock bitmap" );
	font_resource->blit( x, y, str, (u8) color, lock.pixels, lock.pitch_x, lock.pitch_y, font_align, wrap_width, 
		hspacing, vspacing, limit, bold, italic, underline, 0 );

	if( lock.mask )
		font_resource->blit( x, y, str, 0xff, lock.mask, lock.pitch_x, lock.pitch_y, font_align, wrap_width, hspacing, 
			vspacing, limit, bold, italic, underline, 0 );

	target->unlock();
	}


void pixie::text_bounds( int x, int y, string const& str, resource<pixie::font> const& font_resource, text_align align, 
	int wrap_width, int hspacing, int vspacing, bool bold, bool italic, int* width, int* height )
	{
	font::alignment_enum font_align = font::ALIGNMENT_LEFT;
	if( align == TEXT_ALIGN_CENTER ) font_align = font::ALIGNMENT_CENTER;
	if( align == TEXT_ALIGN_RIGHT ) font_align = font::ALIGNMENT_RIGHT;

	font::bounds_t bounds;
	font_resource->blit( x, y, str, (u8)0, (u8)0, 0, 0, font_align, wrap_width, hspacing, vspacing, -1, bold, italic, 
		false, &bounds );
	if( width ) *width = bounds.width;
	if( height ) *height = bounds.height;
	}


//-----------------
//  sprite_manager
//-----------------

pixie::sprite_manager::sprite_manager() 
	{
	internal.origin_x = 0.0f;
	internal.origin_y = 0.0f;
	internal.zorder = 0.0f;
	internal.current_highlighted = 0;
	internal.activated_highlighted = false;
	internal::add_sprite_manager( this, &sprite_manager::internal_render, &sprite_manager::internal_update );
	}


pixie::sprite_manager::~sprite_manager()
	{
	internal::remove_sprite_manager( this );
	}


pixie::sprite_manager& pixie::sprite_manager::add( pixie::internal_sprite* spr )
	{
	for( int i = 0; i < internal.sprites.count(); ++i )
		{
		if( internal.sprites[ i ]->internal_zorder() > spr->internal_zorder() )
			{
			internal.sprites.insert( i, spr );
			return *this;
			}
		}
		
	internal.sprites.add( spr );
	return *this;
	}


pixie::sprite_manager& pixie::sprite_manager::remove( pixie::internal_sprite* spr )
	{    
	for( int i = 0; i < internal.sprites.count(); ++i )
		{
		if( internal.sprites[ i ] == spr ) 
			{
			internal.sprites.remove( i );
			break;
			}
		}
	return *this;
	}


int pixie::sprite_manager::count() const
	{
	return internal.sprites.count();
	}


pixie::internal_sprite* pixie::sprite_manager::sprite( int index ) const
	{
	return internal.sprites[ index ];
	}


void pixie::sprite_manager::add_event_handler( event_handler* handler )
	{
	internal.event_handlers.add( handler );
	}


void pixie::sprite_manager::remove_event_handler( event_handler* handler )
	{
	for( int i = 0; i < internal.event_handlers.count(); ++i )
		{
		if( internal.event_handlers[ i ] == handler ) 
			{
			internal.event_handlers.remove( i );
			return;
			}
		}
	}


pixie::sprite_manager& pixie::sprite_manager::origin( float x, float y )
	{
	internal.origin_x = x;
	internal.origin_y = y;
	return *this;    
	}


pixie::sprite_manager& pixie::sprite_manager::origin_x( float x )
	{
	internal.origin_x = x;
	return *this;
	}


float pixie::sprite_manager::origin_x() const
	{
	return internal.origin_x;
	}


pixie::sprite_manager& pixie::sprite_manager::origin_y( float y )
	{
	internal.origin_y = y;
	return *this;
	}


float pixie::sprite_manager::origin_y() const
	{
	return internal.origin_y;    
	}


void pixie::sprite_manager::internal_update()
	{
	using math_util::fast_round;
	
	float x = (float) mouse_x();
	float y = (float) mouse_y();
	bool button = key_is_down( KEY_LBUTTON );
	bool clicked = key_was_pressed( KEY_LBUTTON ) || internal.activated_highlighted;
	bool found_mouse_over = false;

	for( int i = internal.sprites.count() - 1; i >= 0; --i )
		{
		pixie::internal_sprite* spr = internal.sprites[ i ];
		bool mouse_over = spr->internal_pointer_over( fast_round( x - origin_x() ), fast_round( y - origin_y() ), button, false );
		if( !mouse_over ) continue;
		
		found_mouse_over = true;
		if( clicked && spr->internal_event_id() != "" )
			{
			for( int j = 0; j < internal.event_handlers.count(); ++j )
				internal.event_handlers[ j ]->on_event( spr->internal_event_id(), spr->internal_event_user_data() );            
			break;
			}
		}

	if( !found_mouse_over )
		{
		for( int i = internal.sprites.count() - 1; i >= 0; --i )
			{
			pixie::internal_sprite* spr = internal.sprites[ i ];
			if( internal.current_highlighted && spr->internal_selection_index() == internal.current_highlighted->internal_selection_index() )
				{
				bool mouse_over = spr->internal_pointer_over( fast_round( spr->internal_position_x() + 1.0f - origin_x() ), 
					fast_round( spr->internal_position_y() + 1.0f - origin_y() ), button, true );
				if( !mouse_over ) continue;
				
				if( internal.activated_highlighted && spr->internal_event_id() != "" )
					{
					for( int j = 0; j < internal.event_handlers.count(); ++j )
						internal.event_handlers[ j ]->on_event( spr->internal_event_id(), spr->internal_event_user_data() );            
					break;
					}
				}
			}
		}
	else if( internal.current_highlighted )
		{
		internal.current_highlighted->internal_pointer_over( 0, 0, button, false );
		}

	internal.activated_highlighted = false;
	}


void pixie::sprite_manager::internal_render()
	{
	for( int i = 0; i < internal.sprites.count(); ++i )
		internal.sprites[ i ]->internal_render();
	}
	


//---------
//  sprite
//---------

pixie::internal_sprite::internal_sprite()
	{
	internal::internals_t* internals = internal::internals();
	
	internal.manager = &internals->default_sprite_manager;
	internal.position_x = 0.0f;
	internal.position_y = 0.0f;
	internal.origin_x = 0.0f;
	internal.origin_y = 0.0f;
	internal.visible = true;
	internal.zorder = 0.0f;
	internal.cel = 0.0f;
	internal.selection_index = 0;
	internal.event_user_data = 0;

	if( internal.manager ) internal.manager->add( this );
	}
	
	
pixie::internal_sprite::internal_sprite( sprite_manager* manager )
	{
	internal.manager = manager;
	internal.position_x = 0.0f;
	internal.position_y = 0.0f;
	internal.origin_x = 0.0f;
	internal.origin_y = 0.0f;
	internal.visible = true;
	internal.zorder = 0.0f;
	internal.cel = 0.0f;
	internal.selection_index = 0;
	internal.event_user_data = 0;
	
	if( internal.manager ) internal.manager->add( this );
	}
	
	
pixie::internal_sprite::~internal_sprite()
	{
	if( internal.manager ) internal.manager->remove( this );
	}


pixie::internal_sprite::internal_sprite( internal_sprite const& other )
	{
	internal = other.internal;

	if( internal.manager ) internal.manager->add( this );
	}


pixie::internal_sprite const& pixie::internal_sprite::operator=( internal_sprite const& other )
	{
	if( internal.manager ) internal.manager->remove( this );
	internal = other.internal;
	if( internal.manager ) internal.manager->add( this );
	return *this;
	}


pixie::sprite_manager* pixie::internal_sprite::internal_manager() const
	{
	return internal.manager;
	}


pixie::internal_sprite& pixie::internal_sprite::internal_position( float x, float y ) 
	{ 
	internal.position_x = x;
	internal.position_y = y;
	return *this; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_position_x( float x ) 
	{ 
	internal.position_x = x;
	return *this; 
	}
	
	
float pixie::internal_sprite::internal_position_x() const 
	{ 
	return internal.position_x; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_position_y( float y ) 
	{ 
	internal.position_y = y;
	return *this; 
	}

	
float pixie::internal_sprite::internal_position_y() const 
	{ 
	return internal.position_y; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_origin( float x, float y ) 
	{ 
	internal.origin_x = x;
	internal.origin_y = y;
	return *this; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_origin_x( float x ) 
	{ 
	internal.origin_x = x;
	return *this; 
	}


float pixie::internal_sprite::internal_origin_x() const 
	{ 
	return internal.origin_x; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_origin_y( float y ) 
	{ 
	internal.origin_y = y;
	return *this; 
	}
	
	
float pixie::internal_sprite::internal_origin_y() const 
	{ 
	return internal.origin_y; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_visible( bool is_visible ) 
	{ 
	internal.visible = is_visible;
	return *this; 
	}
	
	
bool pixie::internal_sprite::internal_visible() const 
	{ 
	return internal.visible; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_zorder( float z ) 
	{ 
	if( internal.manager ) internal.manager->remove( this );
	internal.zorder = z;
	if( internal.manager ) internal.manager->add( this );
	return *this; 
	}
	
	
float pixie::internal_sprite::internal_zorder() const 
	{ 
	return internal.zorder; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_cel( float index ) 
	{ 
	internal.cel = index;
	return *this; 
	}
	
	
float pixie::internal_sprite::internal_cel() const 
	{ 
	return internal.cel; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_selection_index( int index ) 
	{ 
	internal.selection_index = index;
	return *this; 
	}
	
	
int pixie::internal_sprite::internal_selection_index() const 
	{ 
	return internal.selection_index; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_bitmap( resource<pixie::bitmap> const& bitmap_resource ) 
	{ 
	internal.bitmap = bitmap_resource;
	return *this; 
	}
	
	
pixie::resource<pixie::bitmap> const& pixie::internal_sprite::internal_bitmap() const 
	{ 
	return internal.bitmap; 
	}


pixie::internal_sprite& pixie::internal_sprite::internal_event( string_id const& event_id, void* user_data )
	{
	internal.event_id = event_id;
	internal.event_user_data = user_data;
	return *this;
	}


pixie::internal_sprite& pixie::internal_sprite::internal_event_id( string_id const& event_id )
	{
	internal.event_id = event_id;
	return *this;
	}


pixie::string_id const& pixie::internal_sprite::internal_event_id() const
	{
	return internal.event_id;
	}


pixie::internal_sprite& pixie::internal_sprite::internal_event_user_data( void* user_data )
	{
	internal.event_user_data = user_data;
	return *this;
	}


void* pixie::internal_sprite::internal_event_user_data() const
	{
	return internal.event_user_data;
	}


void pixie::internal_sprite::internal_render()
	{
	if( !internal_visible() ) return;
	
	using math_util::fast_round;

	internal::internals_t* internals = internal::internals();
	if( (pixie::bitmap*)internal.bitmap )
		{
		int xpos = fast_round( internal_position_x() - internal_origin_x() + internal_manager()->origin_x() );       
		int ypos = fast_round( internal_position_y() - internal_origin_y() + internal_manager()->origin_y() );
		internal.bitmap->blit( fast_round( internal.cel ) % internal.bitmap->cel_count(), &internals->screen_bitmap, xpos, ypos );
		}
	}


bool pixie::internal_sprite::internal_pointer_over( int x, int y, bool button_down, bool forcehit )
	{
	(void) x, y, button_down, forcehit;
	// Do nothing for sprite - derived classes will overide
	return false;
	}



//-------------
//  rendercall
//-------------

pixie::rendercall::rendercall() 
	{
	internal.handler = 0;
	}


pixie::rendercall::rendercall( sprite_manager* manager ) : sprite_base<rendercall>( manager )
	{
	internal.handler = 0;
	}


pixie::rendercall::~rendercall()
	{
	}


pixie::rendercall::rendercall( rendercall const& other ) : sprite_base<rendercall>( other )
	{
	internal = other.internal;
	}


pixie::rendercall const& pixie::rendercall::operator=( rendercall const& other )
	{
	sprite_base<rendercall>::operator=( other );
	internal = other.internal;
	return *this;
	}


pixie::rendercall& pixie::rendercall::handler( rendercall_handler* new_handler )
	{
	internal.handler = new_handler;
	return *this;
	}


pixie::rendercall_handler* pixie::rendercall::handler() const
	{
	return internal.handler;
	}


void pixie::rendercall::internal_render()
	{
	if( !visible() ) return;
	internal::internals_t* internals = internal::internals();
	if( internal.handler )
		internal.handler->render( this, &internals->screen_bitmap );
	}



//---------
//  label
//---------

pixie::label::label()
	{
	internal.color = 15;
	internal.wrap = -1;
	internal.hspacing = 0;
	internal.vspacing = 0;
	internal.limit = -1.0f;
	internal.align= TEXT_ALIGN_LEFT;
	internal.bold = false;
	internal.italic = false;
	internal.underline = false;
	internal.outline_color = -1;
	internal.shadow_color = -1;
	internal.shadow_offset_x = 0.0f;
	internal.shadow_offset_y = 0.0f;
	}
	
	
pixie::label::label( sprite_manager* manager ) : sprite_base<label>( manager )
	{
	internal.color = 15;
	internal.wrap = -1;
	internal.hspacing = 0;
	internal.vspacing = 0;
	internal.limit = -1.0f;
	internal.align = TEXT_ALIGN_LEFT;
	internal.bold = false;
	internal.italic = false;
	internal.underline = false;
	internal.outline_color = -1;
	internal.shadow_color = -1;
	internal.shadow_offset_x = 0.0f;
	internal.shadow_offset_y = 0.0f;
	}
	
	
pixie::label::~label()
	{
	}


pixie::label::label( label const& other ) : sprite_base<label>( other )
	{
	internal = other.internal;
	}


pixie::label const& pixie::label::operator=( label const& other )
	{
	sprite_base<label>::operator=( other );
	internal = other.internal;  return *this;
	}


pixie::label& pixie::label::text( string str )
	{
	internal.text = str;
	return *this;
	}
	
	
pixie::string pixie::label::text() const
	{
	return internal.text;
	}
	
	
pixie::label& pixie::label::font( resource<pixie::font> const& font_resource )
	{
	internal.font = font_resource;
	return *this;
	}
	
	
pixie::resource<pixie::font> const& pixie::label::font() const
	{
	return internal.font;
	}
	
	
pixie::label& pixie::label::color( int index ) 
	{ 
	internal.color = index;
	return *this; 
	}
	
	
int pixie::label::color() const 
	{ 
	return internal.color; 
	}


pixie::label& pixie::label::wrap( int width )
	{
	internal.wrap = width;
	return *this;
	}
	
	
int pixie::label::wrap() const
	{
	return internal.wrap;
	}
	
	
pixie::label& pixie::label::hspacing( int spacing ) 
	{ 
	internal.hspacing = spacing;
	return *this; 
	}
	
	
int pixie::label::hspacing() const 
	{ 
	return internal.hspacing; 
	}


pixie::label& pixie::label::vspacing( int spacing ) 
	{ 
	internal.vspacing = spacing;
	return *this; 
	}
	
	
int pixie::label::vspacing() const 
	{ 
	return internal.vspacing; 
	}


pixie::label& pixie::label::limit( float lim ) 
	{ 
	internal.limit = lim;
	return *this; 
	}
	
	
float pixie::label::limit() const 
	{ 
	return internal.limit; 
	}


pixie::label& pixie::label::align( text_align new_align )
	{
	internal.align = new_align;
	return *this;
	}
	
	
pixie::text_align pixie::label::align() const
	{
	return internal.align;
	}


pixie::label& pixie::label::bold( bool use_bold )
	{
	internal.bold = use_bold;
	return *this;
	}
	
	
bool pixie::label::bold() const
	{
	return internal.bold;
	}


pixie::label& pixie::label::italic( bool use_italic )
	{
	internal.italic = use_italic;
	return *this;
	}
	
	
bool pixie::label::italic() const
	{
	return internal.italic;
	}


pixie::label& pixie::label::underline( bool use_underline )
	{
	internal.underline = use_underline;
	return *this;
	}
	
	
bool pixie::label::underline() const
	{
	return internal.underline;
	}


pixie::label& pixie::label::outline( int color )
	{
	internal.outline_color = color;
	return *this;
	}
	
	
int pixie::label::outline() const
	{
	return internal.outline_color;
	}


pixie::label& pixie::label::shadow( int color, float offset_x, float offset_y )
	{
	internal.shadow_color = color;
	internal.shadow_offset_x = offset_x;
	internal.shadow_offset_y = offset_y;
	return *this;
	}
	
	
pixie::label& pixie::label::shadow_color( int color )
	{
	internal.shadow_color = color;
	return *this;
	}
	
	
int pixie::label::shadow_color() const
	{
	return internal.shadow_color;
	}


pixie::label& pixie::label::shadow_offset_x( float offset )
	{
	internal.shadow_offset_x = offset;
	return *this;
	}
	
	
float pixie::label::shadow_offset_x() const
	{
	return internal.shadow_offset_x;
	}


pixie::label& pixie::label::shadow_offset_y( float offset )
	{
	internal.shadow_offset_y = offset;
	return *this;
	}   

	
float pixie::label::shadow_offset_y() const
	{
	return internal.shadow_offset_y;
	}


int pixie::label::width() const
	{
	using math_util::fast_round;

	int w = 0;
	text_bounds( fast_round( position_x() ), fast_round( position_y() ), internal.text.c_str(), internal.font, 
		internal.align, internal.wrap, internal.hspacing, internal.vspacing, internal.bold, internal.italic, &w, 0 );
	return w;
	}
	
	
int pixie::label::height() const
	{
	using math_util::fast_round;

	int h = 0;
	text_bounds( fast_round( position_x() ), fast_round( position_y() ), internal.text.c_str(), internal.font, 
		internal.align, internal.wrap, internal.hspacing, internal.vspacing, internal.bold, internal.italic, 0, &h );
	return h;
	}
	

void pixie::label::internal_render()
	{
	if( !visible() ) return;
	
	using math_util::fast_round;

	internal::internals_t* internals = internal::internals();
	if( (pixie::font*)internal.font) 
		{
		if( internal.shadow_color >= 0 )
			{
			int xo = fast_round( internal.shadow_offset_x );
			int yo = fast_round( internal.shadow_offset_y );

			if( internal.outline_color >= 0 )
				{
				for( int y = -1; y <= 1; ++y ) for( int x = -1; x <= 1; ++x ) 
					{
					if( x == 0 && y == 0 ) continue;
					
					int xpos = fast_round( position_x() - origin_x() + manager()->origin_x() + x + xo );         
					int ypos = fast_round( position_y() - origin_y() + manager()->origin_y() + y + yo );
					pixie::text( &internals->screen_bitmap, xpos, ypos,          
						internal.text.c_str(), internal.shadow_color, internal.font, internal.align, internal.wrap, 
						internal.hspacing, internal.vspacing, fast_round( internal.limit ), internal.bold, internal.italic, 
						internal.underline );                       
					}
				}
			else
				{
				int xpos = fast_round( position_x() - origin_x() + manager()->origin_x() + xo );         
				int ypos = fast_round( position_y() - origin_y() + manager()->origin_y() + yo );
				pixie::text( &internals->screen_bitmap, xpos, ypos, 
					internal.text.c_str(), internal.shadow_color, internal.font, internal.align, internal.wrap, 
					internal.hspacing, internal.vspacing, fast_round( internal.limit ), internal.bold, internal.italic, 
					internal.underline );                       
				}
			}

		if( internal.outline_color >= 0 )
			{
			for( int y = -1; y <= 1; ++y ) for( int x = -1; x <= 1; ++x ) 
				{
				if( x == 0 && y == 0 ) continue;
				
				int xpos = fast_round( position_x() - origin_x() + manager()->origin_x() + x );      
				int ypos = fast_round( position_y() - origin_y() + manager()->origin_y() + y );
				pixie::text( &internals->screen_bitmap, xpos, ypos,          
					internal.text.c_str(), internal.outline_color, internal.font, internal.align, internal.wrap, 
					internal.hspacing, internal.vspacing, fast_round( internal.limit ), internal.bold, internal.italic, 
					internal.underline );                       
				}
			}
		
		int xpos = fast_round( position_x() - origin_x() + manager()->origin_x() );      
		int ypos = fast_round( position_y() - origin_y() + manager()->origin_y() );
		pixie::text( &internals->screen_bitmap, xpos, ypos, 
			internal.text.c_str(), internal.color, internal.font, internal.align, internal.wrap, internal.hspacing, 
			internal.vspacing, fast_round( internal.limit ), internal.bold, internal.italic, internal.underline );       
								
		}
	}



//---------
//  button
//---------

pixie::button::button()
	{
	internal.enabled = true;
	internal.highlighted = false;
	internal.state = internal_t::STATE_NORMAL;
	internal.pixel_picking = true;
	internal.activated_override = 0.0f;
	}
	
	
pixie::button::button( sprite_manager* manager ) : sprite_base<button>( manager )
	{
	internal.enabled = true;
	internal.highlighted = false;
	internal.state = internal_t::STATE_NORMAL;
	internal.pixel_picking = true;
	internal.activated_override = 0.0f;
	}
	
	
pixie::button::~button()
	{
	}


pixie::button::button( button const& other ) : sprite_base<button>( other )
	{
	internal = other.internal;
	}


pixie::button const& pixie::button::operator=( button const& other )
	{
	sprite_base<button>::operator=( other );
	internal = other.internal;
	return *this;
	}


pixie::button& pixie::button::enabled( bool is_enabled )    
	{
	internal.enabled = is_enabled;
	return *this;
	}


bool pixie::button::enabled() const
	{
	return internal.enabled;
	}


pixie::button& pixie::button::bitmap_disabled( resource<pixie::bitmap> const& bitmap_resource )
	{
	internal.bitmap_disabled = bitmap_resource;
	return *this;
	}


pixie::resource<pixie::bitmap> const& pixie::button::bitmap_disabled() const
	{
	return internal.bitmap_disabled;
	}


pixie::button& pixie::button::bitmap_highlighted( resource<pixie::bitmap> const& bitmap_resource )
	{
	internal.bitmap_highlighted = bitmap_resource;
	return *this;
	}


pixie::resource<pixie::bitmap> const& pixie::button::bitmap_highlighted() const
	{
	return internal.bitmap_highlighted;
	}


pixie::button& pixie::button::bitmap_activated( resource<pixie::bitmap> const& bitmap_resource )
	{
	internal.bitmap_activated = bitmap_resource;
	return *this;
	}


pixie::resource<pixie::bitmap> const& pixie::button::bitmap_activated() const
	{
	return internal.bitmap_activated;
	}


pixie::button& pixie::button::pixel_picking( bool use_pixel_picking )
	{
	internal.pixel_picking= use_pixel_picking;
	return *this;
	}


bool pixie::button::pixel_picking() const
	{
	return internal.pixel_picking;
	}


void pixie::button::simulate_actived( float pressed_time )
	{
	internal.activated_override = pressed_time;
	}


void pixie::button::internal_render()
	{
	if( !visible() ) return;
	
	using math_util::fast_round;

	internal::internals_t* internals = internal::internals();

	if( internal.activated_override > 0.0f )
		{
		internal.activated_override -= delta_time();
		if( enabled() ) internal.state = internal_t::STATE_ACTIVATED;
		}
	else
		{
		if( enabled() && !internal.highlighted && ( internal.state == internal_t::STATE_HIGHLIGHTED || internal.state == internal_t::STATE_ACTIVATED ) )
			internal.state = internal_t::STATE_NORMAL;
		}
		
	internal.highlighted = false;       

	pixie::bitmap* bmp = 0; 
	switch( internal.state ) 
		{
		case internal_t::STATE_NORMAL: bmp = (pixie::bitmap*) bitmap(); break;
		case internal_t::STATE_HIGHLIGHTED: bmp = (pixie::bitmap*) bitmap_highlighted(); break;
		case internal_t::STATE_ACTIVATED: bmp = (pixie::bitmap*) bitmap_activated(); break;
		case internal_t::STATE_DISABLED: bmp = (pixie::bitmap*) bitmap_disabled(); break;
		}
	if( bmp == 0 ) bmp = (pixie::bitmap*) bitmap();
	
	if( bmp ) 
		{
		int xpos = fast_round( position_x() - origin_x() + manager()->origin_x() );      
		int ypos = fast_round( position_y() - origin_y() + manager()->origin_y() );
		bmp->blit( fast_round( cel() ), &internals->screen_bitmap, xpos, ypos );
		}
	}


bool pixie::button::internal_pointer_over( int x, int y, bool button_down, bool forcehit )
	{
	using math_util::fast_round;
	
	if( !enabled() || !visible() || bitmap().empty() || !bitmap()->cel_count() ) return false;

	int xp = x - fast_round( position_x() - origin_x() + manager()->origin_x() );        
	int yp = y - fast_round( position_y() - origin_y() + manager()->origin_y() );
	bool hovering = pixel_picking() ? bitmap()->mask( fast_round( cel() ), xp, yp )
		: xp >= bitmap()->offset_x() && xp < bitmap()->offset_x() + bitmap()->pitch_x() 
			&& yp >= bitmap()->offset_y() && yp < bitmap()->offset_y() + bitmap()->pitch_y();

	if( hovering || forcehit )
		{
		internal.highlighted = true;
		
		if( button_down )
			{
			internal.state = internal_t::STATE_ACTIVATED;
			}
		else
			{
			internal.state = internal_t::STATE_HIGHLIGHTED;
			
			manager()->remove( this );
			manager()->add( this );
			}
			
		return true;
		}

	return false;
	}



//--------
//  shape
//--------

pixie::shape::shape()
	{
	internal.filled = false;
	internal.color = 1;
	internal.data.type = SHAPE_TYPE_NONE;
	}
	
	
pixie::shape::shape( sprite_manager* manager ) : sprite_base<shape>( manager )
	{
	internal.filled = false;
	internal.color = 1;
	internal.data.type = SHAPE_TYPE_NONE;
	}
	
	
pixie::shape::~shape()
	{
	}


pixie::shape::shape( shape const& other ) : sprite_base<shape>( other )
	{
	internal.filled = other.internal.filled;
	internal.color = other.internal.color;
	internal.data = other.internal.data;
	internal.polygon_points = other.internal.polygon_points;
	internal.int_polygon_points.resize( other.internal.polygon_points.count() );
	}


pixie::shape const& pixie::shape::operator=( shape const& other )
	{
	sprite_base<shape>::operator=( other );

	internal.filled = other.internal.filled;
	internal.color = other.internal.color;
	internal.data = other.internal.data;
	internal.polygon_points = other.internal.polygon_points;
	internal.int_polygon_points.resize( other.internal.polygon_points.count() );

	return *this;
	}


pixie::shape& pixie::shape::filled( bool is_filled ) 
	{ 
	internal.filled = is_filled;
	return *this; 
	}
	
	
bool pixie::shape::filled() const 
	{ 
	return internal.filled; 
	}


pixie::shape& pixie::shape::color( int index ) 
	{ 
	internal.color = index;
	return *this; 
	}
	
	
int pixie::shape::color() const 
	{ 
	return internal.color; 
	}


pixie::shape& pixie::shape::point( float x, float y ) 
	{ 
	internal.data.type = SHAPE_TYPE_POINT;
	internal.data.data.point.x = x;
	internal.data.data.point.y = y;
	return *this; 
	}
	

pixie::shape& pixie::shape::line( float x1, float y1, float x2, float y2 ) 
	{ 
	internal.data.type = SHAPE_TYPE_LINE;
	internal.data.data.line.x1 = x1;
	internal.data.data.line.y1 = y1;
	internal.data.data.line.x2 = x2;
	internal.data.data.line.y2 = y2;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::line( float x2, float y2 ) 
	{ 
	internal.data.type = SHAPE_TYPE_LINE;
	internal.data.data.line.x1 = 0.0f;
	internal.data.data.line.y1 = 0.0f;
	internal.data.data.line.x2 = x2;
	internal.data.data.line.y2 = y2;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::box( float x1, float y1, float x2, float y2 ) 
	{ 
	internal.data.type = SHAPE_TYPE_BOX;
	internal.data.data.box.x1 = x1;
	internal.data.data.box.y1 = y1;
	internal.data.data.box.x2 = x2;
	internal.data.data.box.y2 = y2;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::box( float width, float height ) 
	{ 
	internal.data.type = SHAPE_TYPE_BOX;
	internal.data.data.box.x1 = 0.0f;
	internal.data.data.box.y1 = 0.0f;
	internal.data.data.box.x2 = width - 1.0f;
	internal.data.data.box.y2 = height - 1.0f;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::circle( float x, float y, float r ) 
	{ 
	internal.data.type = SHAPE_TYPE_CIRCLE;
	internal.data.data.circle.x = x;
	internal.data.data.circle.y = y;
	internal.data.data.circle.r = r;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::circle( float r ) 
	{ 
	internal.data.type = SHAPE_TYPE_CIRCLE;
	internal.data.data.circle.x = 0.0f;
	internal.data.data.circle.y = 0.0f;
	internal.data.data.circle.r = r;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::ellipse( float x, float y, float rx, float ry ) 
	{ 
	internal.data.type = SHAPE_TYPE_ELLIPSE;
	internal.data.data.ellipse.x = x;
	internal.data.data.ellipse.y = y;
	internal.data.data.ellipse.rx = rx;
	internal.data.data.ellipse.ry = ry;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::ellipse( float rx, float ry ) 
	{ 
	internal.data.type = SHAPE_TYPE_ELLIPSE;
	internal.data.data.ellipse.x = 0.0f;
	internal.data.data.ellipse.y = 0.0f;
	internal.data.data.ellipse.rx = rx;
	internal.data.data.ellipse.ry = ry;
	return *this; 
	}
	
	
pixie::shape& pixie::shape::polygon( int count, float const* points ) 
	{ 
	internal.int_polygon_points.resize( count * 2 );
	internal.polygon_points.clear();
	for( int i = 0; i < count * 2; ++i ) internal.polygon_points.add( points[ i ] );

	internal.data.type = SHAPE_TYPE_POLYGON;
	internal.data.data.polygon.points = internal.polygon_points.data(); 
	internal.data.data.polygon.count = internal.polygon_points.count() / 2;
	return *this; 
	}


pixie::shape& pixie::shape::data( shape_data const& data ) 
	{ 
	switch( data.type )
		{
		case SHAPE_TYPE_NONE: return *this;
		case SHAPE_TYPE_POINT: return point( data.data.point.x, data.data.point.y );
		case SHAPE_TYPE_LINE: return line( data.data.line.x1, data.data.line.y1, data.data.line.x2, data.data.line.y2 );
		case SHAPE_TYPE_BOX: return box( data.data.box.x1, data.data.box.y1, data.data.box.x2, data.data.box.y2 );
		case SHAPE_TYPE_CIRCLE: return circle( data.data.circle.x, data.data.circle.y, data.data.circle.r );
		case SHAPE_TYPE_ELLIPSE: return ellipse( data.data.ellipse.x, data.data.ellipse.y, data.data.ellipse.rx, data.data.ellipse.ry );
		case SHAPE_TYPE_POLYGON: return polygon( data.data.polygon.count, data.data.polygon.points );
		}
	return *this; 
	}


pixie::shape::shape_data const& pixie::shape::data() const 
	{ 
	return internal.data; 
	}


void pixie::shape::internal_render()
	{
	if( !visible() ) return;
	
	using math_util::fast_round;
	internal::internals_t* internals = internal::internals();

	float x = position_x() - origin_x() + manager()->origin_x();         
	float y = position_y() - origin_y() + manager()->origin_y();
   
	switch( internal.data.type )
		{
		case SHAPE_TYPE_NONE: 
			break;
		case SHAPE_TYPE_POINT: 
			pixie::pset( 
				&internals->screen_bitmap,         
				fast_round( x + internal.data.data.point.x ), fast_round( y + internal.data.data.point.y ), 
				internal.color );
			break;
		case SHAPE_TYPE_LINE: 
			pixie::line( 
				&internals->screen_bitmap, 
				fast_round( x + internal.data.data.line.x1 ), fast_round( y + internal.data.data.line.y1 ), 
				fast_round( x + internal.data.data.line.x2 ), fast_round( y + internal.data.data.line.y2 ), 
				internal.color ); 
			break;
		case SHAPE_TYPE_BOX: 
			if( internal.filled )
				pixie::box_fill( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.box.x1 ), fast_round( y + internal.data.data.box.y1 ), 
					fast_round( x + internal.data.data.box.x2 ), fast_round( y + internal.data.data.box.y2 ), 
					internal.color ); 
			else
				pixie::box( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.box.x1 ), fast_round( y + internal.data.data.box.y1 ), 
					fast_round( x + internal.data.data.box.x2 ), fast_round( y + internal.data.data.box.y2 ), 
					internal.color ); 
			break;
		case SHAPE_TYPE_CIRCLE: 
			if( internal.filled )
				pixie::circle_fill( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.circle.x ), fast_round( y + internal.data.data.circle.y ), 
					fast_round( internal.data.data.circle.r ), 
					internal.color ); 
			else
				pixie::circle( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.circle.x ), fast_round( y + internal.data.data.circle.y ), 
					fast_round( x + internal.data.data.circle.r ), 
					internal.color ); 
			break;
		case SHAPE_TYPE_ELLIPSE: 
			if( internal.filled )
				pixie::ellipse_fill( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.ellipse.x ), fast_round( y + internal.data.data.ellipse.y ), 
					fast_round( internal.data.data.ellipse.rx ), fast_round( internal.data.data.ellipse.ry ), 
					internal.color ); 
			else
				pixie::ellipse( 
					&internals->screen_bitmap, 
					fast_round( x + internal.data.data.ellipse.x ), fast_round( y + internal.data.data.ellipse.y ), 
					fast_round( internal.data.data.ellipse.rx ), fast_round( internal.data.data.ellipse.ry ), 
					internal.color ); 
			break;
		case SHAPE_TYPE_POLYGON: 
			for( int i = 0; i < internal.polygon_points.count() / 2; ++i )
				{
				internal.int_polygon_points[ i * 2 + 0 ] = fast_round( x + internal.polygon_points[ i * 2 + 0 ] );
				internal.int_polygon_points[ i * 2 + 1 ] = fast_round( y + internal.polygon_points[ i * 2 + 1 ] );
				}
			if( internal.filled )
				pixie::polygon_fill( 
					&internals->screen_bitmap, 
					(pixie::point*) internal.int_polygon_points.data(), internal.int_polygon_points.count() / 2, 
					internal.color ); 
			else
				pixie::polygon( 
					&internals->screen_bitmap, 
					(pixie::point*) internal.int_polygon_points.data(), internal.int_polygon_points.count() / 2, 
					internal.color ); 

			break;
		}
	}



//-------------
//  properties
//-------------

pixie::ref< pixie::property<float> > pixie::property_position_x( internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_position_x, &internal_sprite::internal_position_x );
	}


pixie::ref< pixie::property<float> > pixie::property_position_y( internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_position_y, &internal_sprite::internal_position_y );
	}


pixie::ref< pixie::property<float> > pixie::property_origin_x(internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_origin_x, &internal_sprite::internal_origin_x );
	}


pixie::ref< pixie::property<float> > pixie::property_origin_y( internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_origin_y, &internal_sprite::internal_origin_y );
	}


pixie::ref< pixie::property<bool> > pixie::property_visible( internal_sprite* sprite )
	{
	return make_property<bool, internal_sprite>( sprite, &internal_sprite::internal_visible, &internal_sprite::internal_visible );
	}


pixie::ref< pixie::property<float> > pixie::property_zorder( internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_zorder, &internal_sprite::internal_zorder );
	}


pixie::ref< pixie::property<float> > pixie::property_cel( internal_sprite* sprite )
	{
	return make_property<float, internal_sprite>( sprite, &internal_sprite::internal_cel, &internal_sprite::internal_cel );
	}



pixie::ref< pixie::property<int> > pixie::property_selection_index( internal_sprite* sprite )
	{
	return make_property<int, internal_sprite>( sprite, &internal_sprite::internal_selection_index, &internal_sprite::internal_selection_index );
	}


pixie::ref< pixie::property< pixie::resource<pixie::bitmap> const& > > pixie::property_bitmap( internal_sprite* sprite )
	{
	return make_property<resource<bitmap> const&, internal_sprite>( sprite, &internal_sprite::internal_bitmap, &internal_sprite::internal_bitmap );
	}


pixie::ref< pixie::property<pixie::string_id const&> > pixie::property_event_id( internal_sprite* sprite )
	{
	return make_property<string_id const&, internal_sprite>( sprite, &internal_sprite::internal_event_id, &internal_sprite::internal_event_id );
	}


pixie::ref< pixie::property<void*> > pixie::property_event_user_data( internal_sprite* sprite )
	{
	return make_property<void*, internal_sprite>( sprite, &internal_sprite::internal_event_user_data, &internal_sprite::internal_event_user_data );
	}



pixie::ref< pixie::property<pixie::rendercall_handler*> > pixie::property_handler( rendercall* sprite )
	{
	return make_property<rendercall_handler*, rendercall>( sprite, &rendercall::handler, &rendercall::handler );
	}



pixie::ref< pixie::property<pixie::string> > pixie::property_text( label* sprite )
	{
	return make_property<string, label>( sprite, &label::text, &label::text );
	}


pixie::ref< pixie::property< pixie::resource<pixie::font> const& > > pixie::property_font( label* sprite )
	{
	return make_property<resource<font> const&, label>( sprite, &label::font, &label::font );
	}


pixie::ref< pixie::property<int> > pixie::property_color( label* sprite )
	{
	return make_property<int, label>( sprite, &label::color, &label::color );
	}


pixie::ref< pixie::property<int> > pixie::property_wrap( label* sprite )
	{
	return make_property<int, label>( sprite, &label::wrap, &label::wrap );
	}


pixie::ref< pixie::property<int> > pixie::property_hspacing( label* sprite )
	{
	return make_property<int, label>( sprite, &label::hspacing, &label::hspacing );
	}


pixie::ref< pixie::property<int> > pixie::property_vspacing( label* sprite )
	{
	return make_property<int, label>( sprite, &label::vspacing, &label::vspacing );
	}


pixie::ref< pixie::property<float> > pixie::property_limit( label* sprite )
	{
	return make_property<float, label>( sprite, &label::limit, &label::limit );
	}


pixie::ref< pixie::property<pixie::text_align> > pixie::property_align( label* sprite )
	{
	return make_property<text_align, label>( sprite, &label::align, &label::align );
	}


pixie::ref< pixie::property<bool> > pixie::property_bold( label* sprite )
	{
	return make_property<bool, label>( sprite, &label::bold, &label::bold );
	}


pixie::ref< pixie::property<bool> > pixie::property_italic( label* sprite )
	{
	return make_property<bool, label>( sprite, &label::italic, &label::italic );
	}


pixie::ref< pixie::property<bool> > pixie::property_underline( label* sprite )
	{
	return make_property<bool, label>( sprite, &label::underline, &label::underline );
	}


pixie::ref< pixie::property<int> > pixie::property_outline( label* sprite )
	{
	return make_property<int, label>( sprite, &label::outline, &label::outline );
	}


pixie::ref< pixie::property<int> > pixie::property_shadow_color( label* sprite )
	{
	return make_property<int, label>( sprite, &label::shadow_color, &label::shadow_color );
	}


pixie::ref< pixie::property<float> > pixie::property_shadow_offset_x( label* sprite )
	{
	return make_property<float, label>( sprite, &label::shadow_offset_x, &label::shadow_offset_x );
	}


pixie::ref< pixie::property<float> > pixie::property_shadow_offset_y( label* sprite )
	{
	return make_property<float, label>( sprite, &label::shadow_offset_y, &label::shadow_offset_y );
	}



pixie::ref< pixie::property<bool> > pixie::property_enabled( button* sprite )
	{
	return make_property<bool, button>( sprite, &button::enabled, &button::enabled );
	}


pixie::ref< pixie::property< pixie::resource<pixie::bitmap> const& > > pixie::property_bitmap_disabled( button* sprite )
	{
	return make_property<resource<bitmap> const&, button>( sprite, &button::bitmap_disabled, &button::bitmap_disabled );
	}


pixie::ref< pixie::property< pixie::resource<pixie::bitmap> const& > > pixie::property_bitmap_highlighted( button* sprite )
	{
	return make_property<resource<bitmap> const&, button>( sprite, &button::bitmap_highlighted, &button::bitmap_highlighted );
	}


pixie::ref< pixie::property< pixie::resource<pixie::bitmap> const& > > pixie::property_bitmap_activated( button* sprite )
	{
	return make_property<resource<bitmap> const&, button>( sprite, &button::bitmap_activated, &button::bitmap_activated );
	}


pixie::ref< pixie::property<bool> > pixie::property_pixel_picking( button* sprite )
	{
	return make_property<bool, button>( sprite, &button::pixel_picking, &button::pixel_picking );
	}



pixie::ref< pixie::property<bool> > pixie::property_filled( shape* sprite )
	{
	return make_property<bool, shape>( sprite, &shape::filled, &shape::filled );
	}


pixie::ref< pixie::property<int> > pixie::property_color( shape* sprite )
	{
	return make_property<int, shape>( sprite, &shape::color, &shape::color );
	}


pixie::ref< pixie::property<pixie::shape::shape_data const&> > pixie::property_shape_data( shape* sprite )
	{
	return make_property<shape::shape_data const&, shape>( sprite, &shape::data, &shape::data );
	}



//-------
//  ease
//-------

float pixie::ease_linear( float t ) { return ::ease_linear( t ); }
float pixie::ease_smoothstep( float t ) { return ::ease_smoothstep( t ); }
float pixie::ease_smootherstep( float t ) { return ::ease_smootherstep( t ); }
float pixie::ease_quad_out( float t ) { return ::ease_quad_out( t ); }
float pixie::ease_quad_in( float t ) { return ::ease_quad_in( t ); }
float pixie::ease_quad_in_out( float t ) { return ::ease_quad_in_out( t ); }
float pixie::ease_back_out( float t ) { return ::ease_back_out( t ); }
float pixie::ease_back_in( float t ) { return ::ease_back_in( t ); }
float pixie::ease_back_in_out( float t ) { return ::ease_back_in_out( t ); }
float pixie::ease_bounce_out( float t ) { return ::ease_bounce_out( t ); }
float pixie::ease_bounce_in( float t ) { return ::ease_bounce_in( t ); }
float pixie::ease_bounce_in_out( float t ) { return ::ease_bounce_out( t ); }
float pixie::ease_sine_out( float t ) { return ::ease_sine_out( t ); }
float pixie::ease_sine_in( float t ) { return ::ease_sine_in( t ); }
float pixie::ease_sine_in_out( float t ) { return ::ease_sine_in_out( t ); }
float pixie::ease_elastic_out( float t ) { return ::ease_elastic_out( t ); }
float pixie::ease_elastic_in( float t ) { return ::ease_elastic_in( t ); }
float pixie::ease_elastic_in_out( float t ) { return ::ease_elastic_in_out( t ); }
float pixie::ease_expo_out( float t ) { return ::ease_expo_out( t ); }
float pixie::ease_expo_in( float t ) { return ::ease_expo_in( t ); }
float pixie::ease_expo_in_out( float t ) { return ::ease_expo_in_out( t ); }        
float pixie::ease_cubic_out( float t ) { return ::ease_cubic_out( t ); }
float pixie::ease_cubic_in( float t ) { return ::ease_cubic_in( t ); }
float pixie::ease_cubic_in_out( float t ) { return ::ease_cubic_in_out( t ); }
float pixie::ease_quart_out( float t ) { return ::ease_quart_out( t ); }
float pixie::ease_quart_in( float t ) { return ::ease_quart_in( t ); }
float pixie::ease_quart_in_out( float t ) { return ::ease_quart_in_out( t ); }      
float pixie::ease_quint_out( float t ) { return ::ease_quint_out( t ); }
float pixie::ease_quint_in( float t ) { return ::ease_quint_in( t ); }
float pixie::ease_quint_in_out( float t ) { return ::ease_quint_in_out( t ); }  
float pixie::ease_circle_out( float t ) { return ::ease_circle_out( t ); }
float pixie::ease_circle_in( float t ) { return ::ease_circle_in( t ); }
float pixie::ease_circle_in_out( float t ) { return ::ease_circle_in_out( t ); }


//----------------
//  tween helpers
//----------------


pixie::tweener pixie::slowprint( label* lbl, string text, float delay )
	{
	lbl->text( text );
	lbl->limit( 0.0f );
	float len = (float) ( text.length() );
	return tween( len * delay )
		.property( property_limit( lbl ), len )
		.ease( ease_linear )
		;
	}


//------------
//  resources
//------------

namespace pixie { namespace internal { 

void destroy_string_key( void* instance )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	pixie::string filename = (char const*) instance;
	int* ref_count = internals->resource_filenames.find( filename );
	PIXIE_ASSERT( ref_count, "resource filename not found" );
	--(*ref_count);
	PIXIE_ASSERT( ref_count > 0, "invalid resource ref count" );
	if( *ref_count == 0 )
		internals->resource_filenames.remove( filename );
	}

} /* namespace pixie */ } /* namespace internal */ 


resources::resource_key pixie::internal::make_string_key( pixie::string const& filename )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	int* ref_count = internals->resource_filenames.find( filename );
	if( ref_count )
		++(*ref_count);
	else
		internals->resource_filenames[ filename ] = 1;
		
	resources::resource_key key;
	key.handle = *(pixie::u64*)&filename;
	key.instance = (void*) filename.c_str();
	key.destroy = destroy_string_key;
	return key;
	}


void pixie::internal::free_ref_key( void* instance )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	internals->pool_ref.destroy( (ref_size*) instance );
	}
	

resources::resource_key pixie::internal::make_ref_key( void (*copy_func)( void*, void const*), void const* refobj, size_t size, void (*destroy_func)( void*) )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	
	PIXIE_ASSERT( size == sizeof( ref_size ), "Size mismatch" ); (void) size;
	void* refcopy = internals->pool_ref.create();
	copy_func( refcopy, refobj );
	
	resources::resource_key key;
	key.handle = 0;
	key.instance = refcopy;
	key.destroy = destroy_func;
	return key;
	}


void resources::resource_create( pixie::bitmap** instance, pixie::string const& filename )
	{
	*instance = pixie::internal::load_bitmap( filename );
	}


void resources::resource_destroy( resource_key* key, pixie::bitmap* instance )
	{
	if( key->handle )
		{
		pixie::internal::destroy_bitmap( instance );
		}
	}


void resources::resource_create( pixie::font** instance, pixie::string const& filename )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();

	pixie::ref<pixie::binary> bin = pixie::bload( filename );
	PIXIE_ASSERTF( bin, ( "Failed to load font: %s", filename.c_str() ) );
	if( bin ) *instance = internals->pool_font.create( bin->data, bin->size );
	}


void resources::resource_destroy( resource_key* key, pixie::font* instance )
	{
	if( key->handle && instance )
		{
		pixie::internal::internals_t* internals = pixie::internal::internals();
		internals->pool_font.destroy( instance );
		}
	}


void resources::resource_create( pixie::audio** instance, pixie::string const& filename )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();

	pixie::ref<pixie::binary> bin = pixie::bload( filename );
	PIXIE_ASSERTF( bin, ( "Failed to load audio: %s", filename.c_str() ) );
	if( bin ) *instance = internals->pool_audio.create( bin );
	}


void resources::resource_create( pixie::audio** instance, float* sample_pairs, int sample_pairs_count, bool take_ownership_of_memory )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();

	*instance = internals->pool_audio.create( sample_pairs, sample_pairs_count, take_ownership_of_memory );
	}


void resources::resource_destroy( resource_key* key, pixie::audio* instance )
	{
	(void) key;
	if( instance )
		{
		pixie::internal::internals_t* internals = pixie::internal::internals();
		internals->pool_audio.destroy( instance );
		}
	}


void pixie::internal::pin_resource( type_id_t type, void (*copy)( void*, void const* ), void (*destroy)( void* ), void const* instance, string_id group )
	{
	internals_t* internals = internal::internals();
	internals->pinned_resources.add( pinned_resource( type, copy, destroy, instance, group ) );
	}


void pixie::internal::unpin_resource( type_id_t type, bool (*cmp)( void const*, void const* ), void const* instance, string_id group )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = internals->pinned_resources.count() -1; i >= 0; --i )
		{
		pinned_resource& res =internals->pinned_resources[ i ];
		if( res.type == type && res.group == group && cmp( &res, instance ) )
			internals->pinned_resources.remove( i );
		}
	}


void pixie::unpin_resource( string_id group )
	{
	internal::internals_t* internals = internal::internals();
	for( int i = internals->pinned_resources.count() -1; i >= 0; --i )
		{
		if( internals->pinned_resources[ i ].group == group )
			internals->pinned_resources.remove( i );
		}
	}


void pixie::unpin_resources()
	{
	internal::internals_t* internals = internal::internals();
	internals->pinned_resources.clear();
	}


//------------------
//  default_palette
//------------------

pixie::u32 pixie::internal::default_palette[ 256 ] = 
	{
	// 0..15 - EGA
	0x000000, 0x0000aa, 0x00aa00, 0x00aaaa, 0xaa0000, 0xaa00aa, 0xaa5500, 0xaaaaaa,
	0x555555, 0x5555ff, 0x55ff55, 0x55ffff, 0xff5555, 0xff55ff, 0xffff55, 0xffffff,
	// 16..31 - Gray scale
	0x000000, 0x141414, 0x202020, 0x2c2c2c, 0x383838, 0x454545, 0x515151, 0x616161,
	0x717171, 0x828282, 0x929292, 0xa2a2a2, 0xb6b6b6, 0xcbcbcb, 0xe3e3e3, 0xffffff,
	// 32..55 - Hue mix
	0x0000ff, 0x4100ff, 0x7d00ff, 0xbe00ff, 0xff00ff, 0xff00be, 0xff007d, 0xff0041,
	0xff0000, 0xff4100, 0xff7d00, 0xffbe00, 0xffff00, 0xbeff00, 0x7dff00, 0x41ff00,
	0x00ff00, 0x00ff41, 0x00ff7d, 0x00ffbe, 0x00ffff, 0x00beff, 0x007dff, 0x0041ff,
	// 56..79 - 49% white mix
	0x7d7dff, 0x9e7dff, 0xbe7dff, 0xdf7dff, 0xff7dff, 0xff7ddf, 0xff7dbe, 0xff7d9e,
	0xff7d7f, 0xff9e7d, 0xffbe7d, 0xffdf7d, 0xffff7d, 0xdfff7d, 0xbeff7d, 0x9eff7d,
	0x7dff7d, 0x7dff9e, 0x7dffbe, 0x7dffdf, 0x7dffff, 0x7ddfff, 0x7dbeff, 0x7d9eff,
	// 80..103 - 72% white mix
	0xb6b6ff, 0xc7b6ff, 0xdbb6ff, 0xebb6ff, 0xffb6ff, 0xffb6eb, 0xffb6db, 0xffb6c7,
	0xffb6b6, 0xffc7b6, 0xffdbb6, 0xffebb6, 0xffffb6, 0xebffb6, 0xdbffb6, 0xc7ffb6,
	0xb6ffb6, 0xb6ffc7, 0xb6ffdb, 0xb6ffeb, 0xb6ffff, 0xb6ebff, 0xb6dbff, 0xb6c7ff,
	// 104..175 - 56% black mix
	0x000071, 0x1c0071, 0x380071, 0x550071, 0x710071, 0x710055, 0x710038, 0x71001c,
	0x710000, 0x711c00, 0x713800, 0x715500, 0x717100, 0x557100, 0x387100, 0x1c7100,
	0x007100, 0x00711c, 0x007138, 0x007155, 0x007171, 0x005571, 0x003871, 0x001c71,

	0x383871, 0x453871, 0x553871, 0x613871, 0x713871, 0x713861, 0x713855, 0x713845,
	0x713838, 0x714538, 0x715538, 0x716138, 0x717138, 0x617138, 0x557138, 0x457138,
	0x387138, 0x387145, 0x387155, 0x387161, 0x387171, 0x386171, 0x385571, 0x384571,
	
	0x515171, 0x595171, 0x615171, 0x695171, 0x715171, 0x715169, 0x715161, 0x715159,
	0x715151, 0x715951, 0x716151, 0x716951, 0x717151, 0x697151, 0x617151, 0x597151,
	0x517151, 0x517159, 0x517161, 0x517169, 0x517171, 0x516971, 0x516171, 0x515971,
	// 176..247 - 75% black mix
	0x000041, 0x100041, 0x200041, 0x300041, 0x410041, 0x410030, 0x410020, 0x410010,
	0x410000, 0x411000, 0x412000, 0x413000, 0x414100, 0x304100, 0x204100, 0x104100,
	0x004100, 0x004110, 0x004120, 0x004130, 0x004141, 0x003041, 0x002041, 0x001041,

	0x202041, 0x282041, 0x302041, 0x382041, 0x412041, 0x412038, 0x412030, 0x412028,
	0x412020, 0x412820, 0x413020, 0x413820, 0x414120, 0x384120, 0x304120, 0x284120,
	0x204120, 0x204128, 0x204130, 0x204138, 0x204141, 0x203841, 0x203041, 0x202841,

	0x2c2c41, 0x302c41, 0x342c41, 0x3c2c41, 0x412c41, 0x412c3c, 0x412c34, 0x412c30,
	0x412c2c, 0x41302c, 0x41342c, 0x413c2c, 0x41412c, 0x3c412c, 0x34412c, 0x30412c,
	0x2c412c, 0x2c4130, 0x2c4134, 0x2c413c, 0x2c4141, 0x2c3c41, 0x2c3441, 0x2c3041,
	// 248..255 - unused
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
	};


//-------
//  LIBS
//-------

#undef final
#undef override
#undef STATIC_ASSERT

#define APP_IMPLEMENTATION
#define APP_WINDOWS
#define APP_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define APP_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#ifndef NDEBUG
	#define APP_REPORT_SHADER_ERRORS
#endif
#include "app.h"

#define ASSETSYS_IMPLEMENTATION
#define ASSETSYS_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define ASSETSYS_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define ASSETSYS_ASSERT PIXIE_ASSERT
#include "assetsys.h"

#define AUDIOSYS_IMPLEMENTATION
#define AUDIOSYS_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define AUDIOSYS_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define AUDIOSYS_ASSERT PIXIE_ASSERT
#include "audiosys.h"

#define ARRAY_IMPLEMENTATION
#define ARRAY_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define ARRAY_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "array.hpp"

#define BINARY_RW_IMPLEMENTATION
#include "binary_rw.h"

#define CRT_FRAME_IMPLEMENTATION
#include "crt_frame.h"

#define CRTEMU_IMPLEMENTATION
#define CRTEMU_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define CRTEMU_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "crtemu.h"

#define DIR_IMPLEMENTATION
#define DIR_WINDOWS
#define DIR_MALLOC( size ) TRACKED_MALLOC( pixie::internal::internals()->memctx, size )
#define DIR_FREE( ptr ) TRACKED_FREE( pixie::internal::internals()->memctx, ptr )
#include "dir.h"

#define EASE_IMPLEMENTATION
#include "ease.h"

#define FILE_IMPLEMENTATION
#define FILE_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define FILE_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "file.h"

#define FILE_UTIL_IMPLEMENTATION
#include "file_util.h"

#define FRAMETIMER_IMPLEMENTATION
#define FRAMETIMER_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define FRAMETIMER_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "frametimer.h"

#define GAMEPAD_IMPLEMENTATION
#define GAMEPAD_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define GAMEPAD_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "gamepad.h"

#define GAMESTATE_IMPLEMENTATION
#define GAMESTATE_MALLOC( ctx, size ) memset( TRACKED_MALLOC( ctx, size ), 0, size );
#define GAMESTATE_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "gamestate.hpp"

#define HANDLES_IMPLEMENTATION
#define HANDLES_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define HANDLES_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define HANDLES_ASSERT PIXIE_ASSERT
#include "handles.h"

#define HASHTABLE_IMPLEMENTATION
#define HASHTABLE_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define HASHTABLE_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define HASHTABLE_ASSERT PIXIE_ASSERT
#include "hashtable.h"

#define INI_IMPLEMENTATION
#define INI_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define INI_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "ini.h"

#define INPUTMAP_IMPLEMENTATION
#define INPUTMAP_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define INPUTMAP_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define INPUTMAP_ASSERT PIXIE_ASSERT
#include "inputmap.h"

#define LOG_IMPLEMENTATION
#define LOG_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define LOG_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "log.h"

#define MATH_UTIL_IMPLEMENTATION
#define MATH_UTIL_ASSERT PIXIE_ASSERT
#include "math_util.hpp"

#define MEMPOOL_IMPLEMENTATION
#define MEMPOOL_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define MEMPOOL_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define MEMPOOL_ASSERT PIXIE_ASSERT
#include "mempool.hpp"

#define OBJREPO_IMPLEMENTATION
#define OBJREPO_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define OBJREPO_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define OBJREPO_ASSERT PIXIE_ASSERT
#include "objrepo.hpp"

#define PALDITHER_IMPLEMENTATION
#define PALDITHER_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define PALDITHER_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define PALDITHER_ASSERT PIXIE_ASSERT
#include "paldither.h"

#define PALETTIZE_IMPLEMENTATION
#define PALETTIZE_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define PALETTIZE_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define PALETTIZE_ASSERT PIXIE_ASSERT
#include "palettize.h"


namespace pixie { namespace internal { 

void* refcount_alloc( size_t size )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	if( size <= sizeof( small_ref_inst_size ) ) 
		return internals->pool_small_ref_inst.create();
	else
		return TRACKED_MALLOC( internals->memctx, size );
	}


void refcount_free( void* p )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	if( internals->pool_small_ref_inst.contains( (small_ref_inst_size*) p ) ) 
		internals->pool_small_ref_inst.destroy( (small_ref_inst_size*) p );
	else 
		TRACKED_FREE( internals->memctx, p );
	}

} /* namespace internal */ } /* namespace pixie */

#define REFCOUNT_IMPLEMENTATION
#define REFCOUNT_MALLOC( size ) pixie::internal::refcount_alloc( size )
#define REFCOUNT_FREE( ptr ) pixie::internal::refcount_free( ptr )
#include "refcount.hpp"

#define RESOURCES_IMPLEMENTATION
#define RESOURCES_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define RESOURCES_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define RESOURCES_ASSERT PIXIE_ASSERT
#include "resources.hpp"

#define RND_IMPLEMENTATION
#include "rnd.h"

#define STRPOOL_IMPLEMENTATION
#define STRPOOL_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define STRPOOL_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#define STRPOOL_ASSERT PIXIE_ASSERT
#include "strpool.h"

#define STRPOOL_HPP_IMPLEMENTATION
#define STRPOOL_HPP_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define STRPOOL_HPP_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "strpool.hpp"

#define STRPOOL_UTIL_IMPLEMENTATION
#include "strpool_util.hpp"

#define THREAD_IMPLEMENTATION
#define THREAD_ASSERT PIXIE_ASSERT
#include "thread.h"

#define TWEEN_IMPLEMENTATION
#define TWEEN_MALLOC( ctx, size ) TRACKED_MALLOC( ctx, size )
#define TWEEN_FREE( ctx, ptr ) TRACKED_FREE( ctx, ptr )
#include "tween.hpp"

#define VECMATH_IMPLEMENTATION
#include "vecmath.hpp"


namespace pixie { namespace internal { 

inline u32 argb32_blend( u32 color1, u32 color2, u8 alpha )
	{
	u8 inv_alpha = (u8)( 255 - alpha );
	return
		( ( ( ( ( color1 & 0x00ff0000 ) >> 16 ) * inv_alpha ) + ( ( color2 & 0xff0000 ) >> 16 ) * alpha ) >> 8) << 16 |
		( ( ( ( ( color1 & 0x0000ff00 ) >> 8  ) * inv_alpha ) + ( ( color2 & 0x00ff00 ) >> 8  ) * alpha ) >> 8) << 8  |
		( ( ( ( ( color1 & 0x000000ff )       ) * inv_alpha ) + ( ( color2 & 0x0000ff )       ) * alpha ) >> 8)       |
		( 0xff000000 );
	}

} /* namespace internal */ } /* namespace pixie */

#define PIXELFONT_IMPLEMENTATION
#define PIXELFONT_COLOR pixie::u8
#define PIXELFONT_FUNC_NAME pixelfont_blit_u8
#define PIXELFONT_PIXEL_FUNC( dst, src ) *(dst) = (pixie::u8)(src);
#include "pixelfont.h"
#undef PIXELFONT_PIXEL_FUNC
#undef PIXELFONT_COLOR 
#undef PIXELFONT_FUNC_NAME 

#define PIXELFONT_IMPLEMENTATION
#define PIXELFONT_COLOR pixie::u32
#define PIXELFONT_FUNC_NAME pixelfont_blit_u32
#define PIXELFONT_PIXEL_FUNC( dst, src ) *(dst) = pixie::internal::argb32_blend( (pixie::u32)*(dst), (pixie::u32)(src), (pixie::u8)( ( (src) >> 24 ) & 0xff ) )
#include "pixelfont.h"
#undef PIXELFONT_PIXEL_FUNC
#undef PIXELFONT_COLOR 
#undef PIXELFONT_FUNC_NAME 


namespace pixie { namespace internal { 

void* mem_sized_realloc( void* p, size_t oldsz, void* n )
	{
	pixie::internal::internals_t* internals = pixie::internal::internals();
	memcpy( n, p, oldsz );
	if( p ) TRACKED_FREE( internals->memctx, p );
	return n;
	}

} /* namespace internal */ } /* namespace pixie */

#pragma warning( push )
#pragma warning( disable: 4365 ) // conversion, signed/unsigned mismatch

#define DR_WAV_IMPLEMENTATION
#define DR_WAV_NO_STDIO
#define DRWAV_ASSERT( x ) PIXIE_ASSERT( x, "dr_wav PIXIE_ASSERT" )
#define DRWAV_MALLOC( sz ) TRACKED_MALLOC( pixie::internal::internals()->memctx, sz )
#define DRWAV_FREE( p ) TRACKED_FREE( pixie::internal::internals()->memctx, p )
#include "dr_wav.h"
#undef DR_WAV_IMPLEMENTATION

#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable: 4018 ) // 'expression' : signed/unsigned mismatch
#pragma warning( disable: 4100 ) // unreferenced formal parameter
#pragma warning( disable: 4127 ) // conditional expression is constant
#pragma warning( disable: 4211 ) // nonstandard extension used: redefined extern to static
#pragma warning( disable: 4242 ) // conversion, possible loss of data
#pragma warning( disable: 4244 ) // conversion, possible loss of data
#pragma warning( disable: 4365 ) // conversion, signed/unsigned mismatch
#pragma warning( disable: 4388 ) // signed/unsigned mismatch
#pragma warning( disable: 4456 ) // declaration hides previous local declaration
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#pragma warning( disable: 4701 ) // potentially uninitialized local variable used
#pragma warning( disable: 4706 ) // assignment within conditional expression
#pragma warning( disable: 4702 ) // unreachable code
#pragma warning( disable: 4619 ) // there is no warning number 'nnnn'
#pragma warning( disable: 4800 ) // 'int': forcing value to bool 'true' or 'false' (performance warning)

#define JAR_MOD_IMPLEMENTATION
#include "jar_mod.h"

#define restrict
#define JAR_XM_IMPLEMENTATION
#include "jar_xm.h"
#undef restrict

#pragma warning( pop )


#pragma warning( push )
#pragma warning( disable: 4619 ) // there is no warning number 'nnnn'
#pragma warning( disable: 4100 ) // unreferenced formal parameter
#pragma warning( disable: 4127 ) // conditional expression is constant
#pragma warning( disable: 4242 ) // conversion, possible loss of data
#pragma warning( disable: 4244 ) // conversion, possible loss of data
#pragma warning( disable: 4245 ) // conversion, signed/unsigned mismatch
#pragma warning( disable: 4302 ) // 'type cast' : truncation from 'type' to 'type'
#pragma warning( disable: 4311 ) // 'variable' : pointer truncation from 'type' to 'type'
#pragma warning( disable: 4365 ) // conversion, signed/unsigned mismatch
#pragma warning( disable: 4456 ) // declaration hides previous local declaration
#pragma warning( disable: 4457 ) // declaration hides function parameter
#pragma warning( disable: 4459 ) // declaration hides global declaration
#pragma warning( disable: 4555 ) // expression has no effect; expected expression with side-effect
#pragma warning( disable: 4701 ) // potentially uninitialized local variable used

#undef STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.h"

#define STB_IMAGE_IMPLEMENTATION
#pragma push_macro("L")
#undef L
#define STBI_MALLOC( sz ) TRACKED_MALLOC( pixie::internal::internals()->memctx, sz )
#define STBI_REALLOC_SIZED( p, oldsz, newsz ) pixie::internal::mem_sized_realloc( p, oldsz, TRACKED_MALLOC( pixie::internal::internals()->memctx, newsz ) )
#define STBI_FREE( p ) TRACKED_FREE( pixie::internal::internals()->memctx, p )
#define STBI_ASSERT( x ) PIXIE_ASSERT( x, "stb_image PIXIE_ASSERT" )
#include "stb_image.h"
#pragma pop_macro("L")
#undef STB_IMAGE_IMPLEMENTATION

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#undef STB_PERLIN_IMPLEMENTATION

#pragma warning( pop )

#if !defined( _WIN32_WINNT ) || _WIN32_WINNT < 0x0501 
	#undef _WIN32_WINNT
	#define _WIN32_WINNT 0x501// requires Windows XP minimum
	// 0x0400=Windows NT 4.0, 0x0500=Windows 2000, 0x0501=Windows XP, 0x0502=Windows Server 2003, 0x0600=Windows Vista, 
	// 0x0601=Windows 7, 0x0602=Windows 8, 0x0603=Windows 8.1, 0x0A00=Windows 10, 
#endif

#define _WINSOCKAPI_
#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#pragma warning( disable: 4255 ) // 'function' : no function prototype given: converting '()' to '(void)'
#include <windows.h>
#pragma warning( pop )

namespace pixie { namespace internal {

char const* format_assert_message( char const* format, ... )
	{
	static char buffer[ 256 ];
	va_list args;
	va_start( args, format );
	_vsnprintf( buffer, sizeof( buffer ), format, args );
	va_end( args );
	return buffer;
	}

#ifdef _WIN32

	bool display_assert_message( char const* expression, char const* message, char const* file, int line )
	    {
	    char buf[ 4096 ];
	    _snprintf( buf, 4095, "ASSERTION FAILED!\n\n%s\n\nExpression: %s\n\n%s(%d)\n", message, expression, file, line );
	    OutputDebugString( "\n******************************************\n" );
	    OutputDebugString( buf );
	    OutputDebugString( "******************************************\n\n" );
		strcat( buf, "\nBreak into debugger?\n" );
	    int result = MessageBox( 0, buf, "Pixie Assert", MB_ICONERROR | MB_YESNOCANCEL );
	    switch( result )
		    {
		    case IDCANCEL:
			    {
			    // Turn off memory leak reports for faster exit
			    #ifndef NDEBUG
				    int flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); // Get current flag
				    flag ^= _CRTDBG_LEAK_CHECK_DF; // Turn off leak-checking bit
				    _CrtSetDbgFlag( flag ); // Set flag to the new value
			    #endif
			    _exit( 3 ); // Exit application immediately, without calling crt's _atexit
			    } break;
		    case IDYES:
			    {
			    return true; // Break to editor
			    } break;
		    case IDNO:		
			    {
			    return false; // Continue execution
			    } break;
		    }

		return false;
	    }

#else /* _WIN32 */

	#error Platform not supported

#endif /* _WIN32 */

} /* namespace internal */ } /* namespace pixie */

#endif // PIXIE_IMPLEMENTATION


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
