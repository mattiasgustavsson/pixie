#include "pixie/pixie.hpp"

using namespace pixie;

int mygame()
	{
	title( "My game" );
	screen_size( 320, 200 );
	fullscreen( true );
	crt_mode( true ); // turn on cathode ray tube emulation shader

	load_palette( "data/palette.pal" );
	play_music( "data/bitpolka.xm" );

	sprite background;
	background
		.bitmap( "data/background.pix" )
		.position_y( -200 )
		;

	pixie::tween( 1.0f )
		.delay( 2.0f )
		.property( pixie::property_position_y( &background ), 0.0f )
		.ease( pixie::ease_bounce_out )
		.on_complete( 
			[&background]() 
				{ 
				pixie::tween( 1.0f )
					.delay( 12.0f )
					.property( pixie::property_position_y( &background ), 200.0f )
					.ease( pixie::ease_back_in )
					;
				} 
			)
		;

	label title;
	title
		.text( "Pixie retro game dev library" )
		.font( "data/Deltoid-sans.fnt" )
		.position( -160.0f, 10.0f )
		.align( TEXT_ALIGN_CENTER )
		.color( brightest_color() )
		.outline( 17 )
		.bold( true )
		.shadow( 0, 2.0f, 2.0f )
		;

	pixie::tween( 1.0f )
		.delay( 1.0f )
		.property( pixie::property_position_x( &title ), 160.0f )
		.ease( pixie::ease_quad_out )
		;
	
	label intro;
	intro
		.font( "data/Volter__28Goldfish_29.fnt" )
		.position( 40.0f, 50.0f )
		.wrap( 240 )
		.align( TEXT_ALIGN_CENTER )
		.color( 8 )
		.outline( darkest_color() )
		.shadow( darkest_color() )
		;

	pixie::tween( 5.0f )
		.on_complete( 
			[&intro]() 
				{ 
				slowprint( &intro, "This is a small demo for the Pixie library, showing just a few features. The whole library is still very much in an early pre-beta stage - there are bugs, incomplete and untested features and weird behaviour everywhere, and there is no documentation at all. It might be interesting to have a look at, but I wouldn't recommend using it in it's current stage, and I have no idea when there will be a stable release.\n\n                        /Mattias Gustavsson", 0.015f );
				}
			)
		;

	while( is_running() )
		{
		execute_frame();
		clear();

		u32 seed = (u32) ( clock() / 100 );
		random_seed( seed );
		for( int i = 0; i < 100; ++i )
			{
			int x = pixie::random( 0, 319 );
			int y = pixie::random( 0, 199 );
			int r = pixie::random( 1, 40 );
			int c = pixie::random( 1, 31 );
			pixie::circle_fill( x, y, r, c );
			pixie::circle( x, y, r, 0 );
			}
		
		if( exit_requested() ) end(); // exit immediately if user closes window
		if( key_was_pressed( KEY_ESCAPE ) ) end(); // exit with no error
		if( key_was_pressed( KEY_SPACE ) ) end(); // exit with no error
		if( key_was_pressed( KEY_RETURN ) && key_is_down( KEY_MENU ) ) fullscreen( !fullscreen() );
		if( key_was_pressed( KEY_TAB ) ) crt_mode( !crt_mode() );
		}

	return 0;
	}

