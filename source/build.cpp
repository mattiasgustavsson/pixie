#ifdef BUILD_DATA


#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#pragma warning( push )
#pragma warning( disable: 4548 ) // expression before comma has no effect; expected expression with side-effect
#include <malloc.h>
#pragma warning( pop )

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef NDEBUG
	#pragma warning( push ) 
	#pragma warning( disable: 4619 ) // pragma warning : there is no warning number 'number'
	#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
	#include <crtdbg.h>
	#pragma warning( pop ) 
#endif

#include "pixie/pixie_build.hpp"

int main( int argc, char** argv )
	{
	(void) argc, argv;
	#ifndef NDEBUG
		int flag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); // Get current flag
		flag ^= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
		_CrtSetDbgFlag( flag ); // Set flag to the new value
//        _CrtSetBreakAlloc( 0 );
	#endif
	
	// run asset builder on commandline switches -build, -rebuild, clean
	pixie_build::build_action build = pixie_build::BUILD_ACTION_UNDEFINED;
	for( int i = 1; i < argc; ++i ) 
		{
		if( stricmp( argv[ i ], "-build" ) == 0 ) build = pixie_build::BUILD_ACTION_BUILD;
		if( stricmp( argv[ i ], "-rebuild" ) == 0 ) build = pixie_build::BUILD_ACTION_REBUILD;
		if( stricmp( argv[ i ], "-clean" ) == 0 ) build = pixie_build::BUILD_ACTION_CLEAN;
		}
	if( build != pixie_build::BUILD_ACTION_UNDEFINED ) //return pixie_build::build( build, "../source_data", "../.buildtemp/data", "data" );
		{
		pixie_build::compiler_list compiler_list[] = 
			{
			{ "pixie_copy", pixie_build::compiler_pixie_copy, },
			{ "pixie_palette", pixie_build::compiler_pixie_palette, },
			{ "pixie_bitmap", pixie_build::compiler_pixie_bitmap, },
		//	{ "pixie_font", compiler_pixie_font, },
		//	{ "afterworld_texture", afterworld_build::compiler_afterworld_texture, },
			};
		return pixie_build::build( build, "../source_data", "../.build_temp/data", "data", 
			compiler_list, sizeof( compiler_list ) / sizeof( *compiler_list ) );
		}
	}

extern "C" int __stdcall WinMain( struct HINSTANCE__*, struct HINSTANCE__*, char*, int ) { return main( __argc, __argv ); }

#define PIXIE_BUILD_IMPLEMENTATION
#include "pixie/pixie_build.hpp"


#endif /*BUILD_DATA*/

