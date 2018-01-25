/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

audiosys.h - v0.1 - Sound and music playback (mixing only) for C/C++.

Do this:
	#define AUDIOSYS_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/

#ifndef audiosys_h
#define audiosys_h

#ifndef AUDIOSYS_S16
    #define AUDIOSYS_S16 signed short
#endif

#ifndef AUDIOSYS_U64
    #define AUDIOSYS_U64 unsigned long long
#endif

#define AUDIOSYS_DEFAULT_BUFFERED_SAMPLE_PAIRS_COUNT 5880 // 8 frames worth of buffering at 60hz
#define AUDIOSYS_DEFAULT_VOICE_COUNT 16

#define AUDIOSYS_FEATURE_USE_SOFT_CLIP 0x0001
#define AUDIOSYS_FEATURE_MUSIC 0x0002
#define AUDIOSYS_FEATURE_MUSIC_CROSSFADE 0x0004
#define AUDIOSYS_FEATURE_AMBIENCE 0x0008
#define AUDIOSYS_FEATURE_AMBIENCE_CROSSFADE 0x0010
#define AUDIOSYS_FEATURES_ALL 0xffff

typedef struct audiosys_audio_source_t
    {
    void* instance;
    void (*release)( void* instance );
    int (*read_samples)( void* instance, float* sample_pairs, int sample_pairs_count );
    void (*restart)( void* instance );
    void (*set_position)( void* instance, int position_in_sample_pairs );
    int (*get_position)( void* instance );
    } audiosys_audio_source_t;


typedef struct audiosys_t audiosys_t;
audiosys_t* audiosys_create( int active_voice_count, int buffered_sample_pairs_count, int features, void* memctx );
void audiosys_destroy( audiosys_t* audiosys );

void audiosys_update( audiosys_t* audiosys );
int audiosys_consume( audiosys_t* audiosys, int sample_pairs_to_advance, 
    AUDIOSYS_S16* output_sample_pairs, int output_sample_pairs_count );

void audiosys_master_volume_set( audiosys_t* audiosys, float volume );
float audiosys_master_volume( audiosys_t* audiosys );

void audiosys_gain_set( audiosys_t* audiosys, float gain );
float audiosys_gain( audiosys_t* audiosys );

void audiosys_pause( audiosys_t* audiosys );
void audiosys_resume( audiosys_t* audiosys );

void audiosys_stop_all( audiosys_t* audiosys );

typedef enum audiosys_paused_t
    {
    AUDIOSYS_NOT_PAUSED,
    AUDIOSYS_PAUSED,
    } audiosys_paused_t;

audiosys_paused_t audiosys_paused( audiosys_t* audiosys );


typedef enum audiosys_loop_t
    {
    AUDIOSYS_LOOP_OFF,
    AUDIOSYS_LOOP_ON,
    } audiosys_loop_t;

void audiosys_music_play( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_in_time );
void audiosys_music_stop( audiosys_t* audiosys, float fade_out_time );
void audiosys_music_pause( audiosys_t* audiosys );
void audiosys_music_resume( audiosys_t* audiosys );
void audiosys_music_switch( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_out_time, float fade_in_time );
void audiosys_music_cross_fade( audiosys_t* audiosys, audiosys_audio_source_t source, float cross_fade_time );
void audiosys_music_position_set( audiosys_t* audiosys, float position );
float audiosys_music_position( audiosys_t* audiosys );
audiosys_audio_source_t audiosys_music_source( audiosys_t* audiosys );
void audiosys_music_loop_set( audiosys_t* audiosys, audiosys_loop_t loop );
audiosys_loop_t audiosys_music_loop( audiosys_t* audiosys );
void audiosys_music_volume_set( audiosys_t* audiosys, float volume );
float audiosys_music_volume( audiosys_t* audiosys );
void audiosys_music_pan_set( audiosys_t* audiosys, float pan );
float audiosys_music_pan( audiosys_t* audiosys );

void audiosys_ambience_play( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_in_time );
void audiosys_ambience_stop( audiosys_t* audiosys, float fade_out_time );
void audiosys_ambience_pause( audiosys_t* audiosys );
void audiosys_ambience_resume( audiosys_t* audiosys );
void audiosys_ambience_switch( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_out_time, float fade_in_time );
void audiosys_ambience_cross_fade( audiosys_t* audiosys, audiosys_audio_source_t source, float cross_fade_time );
void audiosys_ambience_position_set( audiosys_t* audiosys, float position );
float audiosys_ambience_position( audiosys_t* audiosys );
audiosys_audio_source_t audiosys_ambience_source( audiosys_t* audiosys );
void audiosys_ambience_loop_set( audiosys_t* audiosys, audiosys_loop_t loop );
audiosys_loop_t audiosys_ambience_loop( audiosys_t* audiosys );
void audiosys_ambience_volume_set( audiosys_t* audiosys, float volume );
float audiosys_ambience_volume( audiosys_t* audiosys );
void audiosys_ambience_pan_set( audiosys_t* audiosys, float pan );
float audiosys_ambience_pan( audiosys_t* audiosys );

AUDIOSYS_U64 audiosys_sound_play( audiosys_t* audiosys, audiosys_audio_source_t source, float priority, float fade_in_time );
void audiosys_sound_stop( audiosys_t* audiosys, AUDIOSYS_U64 handle, float fade_out_time );
void audiosys_sound_pause( audiosys_t* audiosys, AUDIOSYS_U64 handle );
void audiosys_sound_resume( audiosys_t* audiosys, AUDIOSYS_U64 handle );
void audiosys_sound_position_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float position );
float audiosys_sound_position( audiosys_t* audiosys, AUDIOSYS_U64 handle );
audiosys_audio_source_t audiosys_sound_source( audiosys_t* audiosys, AUDIOSYS_U64 handle );
void audiosys_sound_loop_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, audiosys_loop_t loop );
audiosys_loop_t audiosys_sound_loop( audiosys_t* audiosys, AUDIOSYS_U64 handle );
void audiosys_sound_volume_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float volume );
float audiosys_sound_volume( audiosys_t* audiosys, AUDIOSYS_U64 handle );
void audiosys_sound_pan_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float pan );
float audiosys_sound_pan( audiosys_t* audiosys, AUDIOSYS_U64 handle );


typedef enum audiosys_sound_valid_t
    {
    AUDIOSYS_SOUND_INVALID,
    AUDIOSYS_SOUND_VALID,
    } audiosys_sound_valid_t;

audiosys_sound_valid_t audiosys_sound_valid(audiosys_t* audiosys, AUDIOSYS_U64 handle );

#endif /* audiosys_h */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifdef AUDIOSYS_IMPLEMENTATION
#undef AUDIOSYS_IMPLEMENTATION

#if defined( _WIN32 )
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS

    #if !defined( _WIN32_WINNT ) || _WIN32_WINNT < 0x0501 
        #undef _WIN32_WINNT
        #define _WIN32_WINNT 0x501// requires Windows XP minimum
    #endif

    #define _WINSOCKAPI_
    #pragma warning( push )
    #pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
    #pragma warning( disable: 4255 ) // 'function' : no function prototype given: converting '()' to '(void)'
    #include <windows.h>
    #pragma warning( pop )
   
#elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )

    #include <pthread.h>

#else 
    #error Unknown platform.
#endif


#ifndef AUDIOSYS_MALLOC
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define AUDIOSYS_MALLOC( ctx, size ) ( malloc( size ) )
	#define AUDIOSYS_FREE( ctx, ptr ) ( free( ptr ) )
#endif

#ifndef AUDIOSYS_ASSERT
    #undef _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #undef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
    #include <assert.h>
    #define AUDIOSYS_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

#ifndef AUDIOSYS_MEMCPY
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <string.h>
    #define AUDIOSYS_MEMCPY( dst, src, cnt ) ( memcpy( (dst), (src), (cnt) ) )
#endif 

#ifndef AUDIOSYS_MEMSET
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <string.h>
    #define AUDIOSYS_MEMSET( dst, val, cnt ) ( memset( (dst), (val), (cnt) ) )
#endif 

#ifndef AUDIOSYS_MEMMOVE
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <string.h>
    #define AUDIOSYS_MEMMOVE( dst, src, cnt ) ( memmove((dst), (src), (cnt) ) )
#endif 

#if ( defined( _M_IX86_FP ) && ( _M_IX86_FP > 0 ) ) || defined( _M_X64 )
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <xmmintrin.h>
#endif


struct audiosys_internal_handles_data_t
    {
    int index;
    int counter;
    };


struct audiosys_internal_handles_t
    {
    void* memctx;
    struct audiosys_internal_handles_data_t* data;
    int capacity;
    int count;
    int freelist_head;
    int freelist_tail;
    };


static void audiosys_internal_handles_init( audiosys_internal_handles_t* handles, int initial_capacity, void* memctx )
    {
    handles->memctx = memctx;
    handles->count = 0;
    handles->capacity = initial_capacity <= 0 ? 1 : initial_capacity;
    handles->freelist_head = -1;
    handles->freelist_tail = -1;
    handles->data = (struct audiosys_internal_handles_data_t*) AUDIOSYS_MALLOC( memctx, handles->capacity * sizeof( *handles->data ) );
    AUDIOSYS_ASSERT( handles->data, "Allocation failed" );
    }


static void audiosys_internal_handles_term( audiosys_internal_handles_t* handles )
    {
    AUDIOSYS_FREE( handles->memctx, handles->data );
    }


static int audiosys_internal_handles_alloc( audiosys_internal_handles_t* handles, int index )
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
        struct audiosys_internal_handles_data_t* new_data = (struct audiosys_internal_handles_data_t*) AUDIOSYS_MALLOC( handles->memctx, handles->capacity * sizeof( *handles->data ) );
        AUDIOSYS_ASSERT( new_data, "Allocation failed" );
        AUDIOSYS_MEMCPY( new_data, handles->data, handles->count * sizeof( *handles->data ) );
        AUDIOSYS_FREE( handles->memctx, handles->data );
        handles->data = new_data;
        handle = handles->count;
        handles->data[ handles->count ].counter = 0;
        ++handles->count;           
        }

    handles->data[ handle ].index = index;
    return handle;
    }


static void audiosys_internal_handles_release( audiosys_internal_handles_t* handles, int handle )
    {
    if( handles->freelist_tail < 0 )
        {
        AUDIOSYS_ASSERT( handles->freelist_head < 0, "Freelist invalid" );
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


static int audiosys_internal_handles_index( audiosys_internal_handles_t* handles, int handle )
    {
    if( handle >= 0 && handle < handles->count )
        return handles->data[ handle ].index;
    else
        return -1;
    }


static void audiosys_internal_handles_update( audiosys_internal_handles_t* handles, int handle, int index )
    {
    handles->data[ handle ].index = index;
    }


static HANDLES_U64 audiosys_internal_to_u64( int handle, int counter )
    {
    HANDLES_U64 i = (HANDLES_U64) ( handle + 1 );
    HANDLES_U64 c = (HANDLES_U64) counter;
    return ( c << 32ull ) | ( i );
    }


static int audiosys_internal_u64_to_counter( HANDLES_U64 u )
    {
    return (int) ( u >> 32ull ) ;
    }
    

static int audiosys_internal_u64_to_handle( HANDLES_U64 u )
    {
    return ( (int) ( u & 0xffffffffull ) ) - 1;
    }


static HANDLES_U64 audiosys_internal_handles_to_u64( audiosys_internal_handles_t* handles, int handle )
    {
    return audiosys_internal_to_u64( handle, handles->data[ handle ].counter );
    }


static int audiosys_internal_handles_from_u64( audiosys_internal_handles_t* handles, HANDLES_U64 u )
    {
    int handle = audiosys_internal_u64_to_handle( u );
    if( handle >= 0 && handle < handles->count && handles->data[ handle ].counter == audiosys_internal_u64_to_counter( u ) )
        {
        return handle;
        }
    else
        {
        return -1;
        }
    }


typedef enum audiosys_internal_voice_state_t
	{
	AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED,
	AUDIOSYS_INTERNAL_VOICE_STATE_PLAYING,
	AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN,
	AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT,
	AUDIOSYS_INTERNAL_VOICE_STATE_CROSSFADING,
	AUDIOSYS_INTERNAL_VOICE_STATE_QUEUED,
	} audiosys_internal_voice_state_t;


typedef struct audiosys_internal_voice_t
	{
	AUDIOSYS_U64 handle;
	audiosys_internal_voice_state_t state;
	audiosys_audio_source_t source;
    int initialized;
	int paused;
	int loop;
	float priority;
	float volume;
	float pan;
	float fade_in_time;
	float fade_out_time;
	float fade_progress;

    float current_fade_volume;
    float current_fade_delta;
    float cached_samples[ 1 ]; // "open" array
	} audiosys_internal_voice_t;


struct audiosys_t
	{
    void* memctx;

    #ifdef _WIN32
        CRITICAL_SECTION mutex;
    #else
        pthread_mutex_t mutex;
    #endif

    int use_soft_clip;
    int active_voice_count;
	float master_volume;
    float gain;
	int paused;
	
	audiosys_internal_voice_t* music;
	audiosys_internal_voice_t* music_crossfade;
	float music_crossfade_time;
	
	audiosys_internal_voice_t* ambience;
	audiosys_internal_voice_t* ambience_crossfade;
	float ambience_crossfade_time;
	
    int sounds_capacity;
    int sounds_count;
    AUDIOSYS_U64* sounds_by_priority;
	void* sounds;
	audiosys_internal_handles_t sounds_handles;
	
    int buffered_sample_pairs_count;
    float* temp_buffer;
    AUDIOSYS_S16* mix_buffer;

    int sample_pairs_to_advance_next_update;
    };


audiosys_internal_voice_t* audiosys_internal_sound_voice( audiosys_t* audiosys, int sound_index )
    {
    if( sound_index < 0 || sound_index >= audiosys->sounds_count ) return NULL;
    size_t sample_buffer_size = audiosys->buffered_sample_pairs_count * 2 * sizeof( float );
    size_t internal_voice_size = sizeof( audiosys_internal_voice_t ) - sizeof( float ) + sample_buffer_size;
    uintptr_t ptr = ( uintptr_t) audiosys->sounds;
    ptr += internal_voice_size * sound_index;
    audiosys_internal_voice_t* voice = (audiosys_internal_voice_t*) ptr;
    return voice;
    }


static void audiosys_internal_release_source( audiosys_audio_source_t* source )
    {
    if( source->release ) source->release( source->instance );
	source->instance = NULL;
    source->release = NULL;
    source->read_samples = NULL;
    source->restart = NULL;
    source->set_position = NULL;
    source->get_position = NULL;
    }


audiosys_t* audiosys_create( int active_voice_count, int buffered_sample_pairs_count, int features, void* memctx )
    {
    size_t sample_buffer_size = buffered_sample_pairs_count * 2 * sizeof( float );
    size_t internal_voice_size = sizeof( audiosys_internal_voice_t ) - sizeof( float ) + sample_buffer_size;
    size_t music_size = ( features & AUDIOSYS_FEATURE_MUSIC ) ? internal_voice_size : 0;
    music_size += ( features & ( AUDIOSYS_FEATURE_MUSIC | AUDIOSYS_FEATURE_MUSIC_CROSSFADE ) ) ? internal_voice_size : 0;
    size_t ambience_size = ( features & AUDIOSYS_FEATURE_AMBIENCE ) ? internal_voice_size : 0;
    ambience_size += ( features & ( AUDIOSYS_FEATURE_AMBIENCE | AUDIOSYS_FEATURE_AMBIENCE_CROSSFADE ) )  ? 
        internal_voice_size : 0;
    size_t temp_buffer_size = buffered_sample_pairs_count * 2 * sizeof( float );
    size_t mix_buffer_size = buffered_sample_pairs_count * 2 * sizeof( AUDIOSYS_S16 );
    size_t size = sizeof( audiosys_t ) + mix_buffer_size + temp_buffer_size + music_size + ambience_size;

    audiosys_t* audiosys = (audiosys_t*) AUDIOSYS_MALLOC( memctx, size );
    AUDIOSYS_MEMSET( audiosys, 0, size );

    audiosys->memctx = memctx;

    #ifdef _WIN32
        InitializeCriticalSectionAndSpinCount( &audiosys->mutex, 32 );
    #else
        pthread_mutex_init( &audiosys->mutex, NULL );
    #endif

    audiosys->use_soft_clip = ( features & AUDIOSYS_FEATURE_USE_SOFT_CLIP ) ? 1 : 0;
    audiosys->active_voice_count= active_voice_count;
    audiosys->master_volume = 1.0f;
    audiosys->gain = 1.0f;
    audiosys->paused = 0;

    audiosys->buffered_sample_pairs_count = buffered_sample_pairs_count;
    audiosys->mix_buffer = (AUDIOSYS_S16*)( audiosys + 1 );

    uintptr_t ptr = ( (uintptr_t) audiosys->mix_buffer ) + mix_buffer_size;
    audiosys->temp_buffer = (float*) ptr; ptr += temp_buffer_size;

    if( features & AUDIOSYS_FEATURE_MUSIC ) 
        {
        audiosys->music = (audiosys_internal_voice_t*) ptr; ptr += internal_voice_size;
        audiosys->music->volume = 1.0f;
        if( features & AUDIOSYS_FEATURE_MUSIC_CROSSFADE ) 
            {
            audiosys->music_crossfade = (audiosys_internal_voice_t*) ptr; ptr += internal_voice_size;
            audiosys->music_crossfade->volume = 1.0f;
            }
        }

    if( features & AUDIOSYS_FEATURE_AMBIENCE ) 
        {
        audiosys->ambience = (audiosys_internal_voice_t*) ptr; ptr += internal_voice_size;
        audiosys->ambience->volume = 1.0f;
        if( features & AUDIOSYS_FEATURE_AMBIENCE_CROSSFADE ) 
            {
            audiosys->ambience_crossfade = (audiosys_internal_voice_t*) ptr; ptr += internal_voice_size;
            audiosys->ambience_crossfade->volume = 1.0f;
            }
        }

    audiosys->sounds_capacity = 64;
    audiosys->sounds_count = 0;
    audiosys->sounds_by_priority = (AUDIOSYS_U64*) AUDIOSYS_MALLOC( memctx, 
        ( internal_voice_size + sizeof( AUDIOSYS_U64 ) ) * audiosys->sounds_capacity );
    AUDIOSYS_MEMSET( audiosys->sounds_by_priority, 0, ( internal_voice_size + sizeof( AUDIOSYS_U64 ) ) * audiosys->sounds_capacity );
    audiosys->sounds = (void*)( audiosys->sounds_by_priority + audiosys->sounds_capacity );
    audiosys_internal_handles_init( &audiosys->sounds_handles, audiosys->sounds_capacity, memctx );   

    return audiosys;
    }


void audiosys_destroy( audiosys_t* audiosys )
	{
    if( audiosys->music ) audiosys_internal_release_source( &audiosys->music->source );
    if( audiosys->music_crossfade ) audiosys_internal_release_source( &audiosys->music_crossfade->source );
    if( audiosys->ambience ) audiosys_internal_release_source( &audiosys->ambience->source );
    if( audiosys->ambience_crossfade ) audiosys_internal_release_source( &audiosys->ambience_crossfade->source );
    for( int i = 0; i < audiosys->sounds_count; ++i )
        audiosys_internal_release_source( &audiosys_internal_sound_voice( audiosys, i )->source );

    audiosys_internal_handles_term( &audiosys->sounds_handles );
    AUDIOSYS_FREE( audiosys->memctx, audiosys->sounds_by_priority );

    #ifdef _WIN32
        DeleteCriticalSection( &audiosys->mutex );
    #else
        pthread_mutex_destroy( &audiosys->mutex );
    #endif

    AUDIOSYS_FREE( audiosys->memctx, audiosys );
	}


static audiosys_internal_voice_t* audiosys_internal_get_sound( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	int index = audiosys_internal_handles_index( &audiosys->sounds_handles, audiosys_internal_handles_from_u64( &audiosys->sounds_handles, handle ) );
	if( index < 0 ) return 0;
	return audiosys_internal_sound_voice( audiosys, index );
	}


static AUDIOSYS_U64 audiosys_internal_add_sound( audiosys_t* audiosys, audiosys_internal_voice_t** sound, float priority )
	{
	if( audiosys->sounds_count >= audiosys->sounds_capacity )
		{
        size_t sample_buffer_size = audiosys->buffered_sample_pairs_count * 2 * sizeof( float );
        size_t internal_voice_size = sizeof( audiosys_internal_voice_t ) - sizeof( float ) + sample_buffer_size;
		int new_capacity = audiosys->sounds_capacity * 2;
		AUDIOSYS_U64* new_sounds_by_priority = (AUDIOSYS_U64*)AUDIOSYS_MALLOC( audiosys->memctx, 
            ( internal_voice_size + sizeof( AUDIOSYS_U64 ) ) * new_capacity );
        void* new_sounds = ( new_sounds_by_priority + new_capacity );
        AUDIOSYS_MEMCPY( new_sounds_by_priority, audiosys->sounds_by_priority, sizeof( AUDIOSYS_U64 ) * audiosys->sounds_count );
		AUDIOSYS_MEMCPY( new_sounds, audiosys->sounds, internal_voice_size * audiosys->sounds_count );
        AUDIOSYS_MEMSET( (void*) ( ( (uintptr_t) new_sounds ) + audiosys->sounds_count * internal_voice_size ), 0, 
            internal_voice_size * ( audiosys->sounds_capacity - audiosys->sounds_count ) );
		AUDIOSYS_FREE( audiosys->memctx, audiosys->sounds_by_priority );
		audiosys->sounds_capacity = new_capacity;
        audiosys->sounds_by_priority = new_sounds_by_priority;
		audiosys->sounds = new_sounds;
		}

	int index = audiosys->sounds_count;
    if( audiosys->sounds_count > 0 )
        {
        int min_index = 0; 
        int max_index = audiosys->sounds_count - 1;
        while( min_index <= max_index )
            {
            int center = ( max_index - min_index ) / 2 + min_index;
            audiosys_internal_voice_t* snd = audiosys_internal_get_sound( audiosys, audiosys->sounds_by_priority[ center ] );
            float center_prio = snd->priority;
            if( center_prio <= priority ) 
                max_index = center - 1;
            else 
                min_index = center + 1;
            }
        index = min_index;
        }
	
    ++audiosys->sounds_count;
	*sound = audiosys_internal_sound_voice( audiosys, audiosys->sounds_count - 1 );
    AUDIOSYS_U64 handle = audiosys_internal_handles_to_u64( &audiosys->sounds_handles, audiosys_internal_handles_alloc( &audiosys->sounds_handles, audiosys->sounds_count - 1 ) );

    for( int i = audiosys->sounds_count - 1; i > index ; --i )
        audiosys->sounds_by_priority[ i ] = audiosys->sounds_by_priority[ i - 1 ];

    audiosys->sounds_by_priority[ index ] = handle;
	return handle;
	}

	
static void audiosys_internal_remove_sound( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	int index = audiosys_internal_handles_index( &audiosys->sounds_handles, audiosys_internal_handles_from_u64( &audiosys->sounds_handles, handle ) );
	if( index < 0 ) return;

	audiosys_internal_handles_release( &audiosys->sounds_handles, audiosys_internal_handles_from_u64( &audiosys->sounds_handles, handle ) );
    audiosys_internal_voice_t* sound_to_remove = audiosys_internal_sound_voice( audiosys, index );
	audiosys_internal_release_source( &sound_to_remove->source );

    for( int j = 0; j < audiosys->sounds_count; ++j )
        {
        if( audiosys->sounds_by_priority[ j ] == handle )
            {
            for( int i = j; i < audiosys->sounds_count - 1; ++i )
                audiosys->sounds_by_priority[ i ] = audiosys->sounds_by_priority[ i + 1 ];
            break;
            }
        }

    audiosys_internal_voice_t* last_sound = audiosys_internal_sound_voice( audiosys, audiosys->sounds_count - 1);
    audiosys_internal_handles_update( &audiosys->sounds_handles, audiosys_internal_handles_from_u64( &audiosys->sounds_handles, last_sound->handle ), index );
    --audiosys->sounds_count;

    size_t sample_buffer_size = audiosys->buffered_sample_pairs_count * 2 * sizeof( float );
    size_t internal_voice_size = sizeof( audiosys_internal_voice_t ) - sizeof( float ) + sample_buffer_size;
    AUDIOSYS_MEMCPY( sound_to_remove, last_sound, internal_voice_size );
	}
	

void audiosys_internal_update_fading( audiosys_internal_voice_t* voice, float delta_time )
    {
    if( !voice ) return;

	float fade_volume = 1.0f;
	float fade_delta = 0.0f;
	if( voice->state == AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT && voice->fade_out_time > 0.0f )
		{
		voice->fade_progress -= delta_time / voice->fade_out_time;
		if( voice->fade_progress <= 0.0f ) 
			{
			voice->fade_progress = 0.0f;
			voice->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
			fade_volume = 0.0f;
            audiosys_internal_release_source( &voice->source );
			}
		else
			{
			float volume_dec_per_second = 1.0f / voice->fade_out_time;
			float volume_dec_per_sample = volume_dec_per_second / 44100.0f;
			fade_volume = voice->fade_progress;
			fade_volume = fade_volume < 0.0f ? 0.0f : fade_volume > 1.0f ? 1.0f : fade_volume;			
			fade_delta = -volume_dec_per_sample;
			}
		}
	else if( voice->state == AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN && voice->fade_in_time > 0.0f )
		{
		voice->fade_progress += delta_time / voice->fade_in_time;
		if( voice->fade_progress >= 1.0f ) 
			{				
			voice->fade_progress = 1.0f;
			voice->state = AUDIOSYS_INTERNAL_VOICE_STATE_PLAYING;
			fade_volume = 1.0f;
			}
		else
			{
			float volume_inc_per_second = 1.0f / voice->fade_in_time;
			float volume_inc_per_sample = volume_inc_per_second / 44100.0f;
			fade_volume = voice->fade_progress;
			fade_volume = fade_volume < 0.0f ? 0.0f : fade_volume > 1.0f ? 1.0f : fade_volume;			
			fade_delta = volume_inc_per_sample;
			}
		}

    voice->current_fade_volume = fade_volume;
    voice->current_fade_delta = fade_delta;
    }


void audiosys_internal_update_from_source( audiosys_t* audiosys, audiosys_internal_voice_t* voice, int advance )
    {
    if( voice == 0 || advance <= 0 ) return;

	float* out = voice->cached_samples;
    int samples_to_write;
	if( !voice->initialized ) 
		{
        audiosys_internal_update_fading( voice, 0.0f );
        samples_to_write = audiosys->buffered_sample_pairs_count;
        voice->initialized = 1;
        }
    else 
        {        
        audiosys_internal_update_fading( voice, advance / 44100.0f );
        samples_to_write = advance > audiosys->buffered_sample_pairs_count ? audiosys->buffered_sample_pairs_count : advance;
        int samples_to_keep = audiosys->buffered_sample_pairs_count - samples_to_write;        
        if( samples_to_keep > 0 ) 
            AUDIOSYS_MEMMOVE( voice->cached_samples, voice->cached_samples + samples_to_write * 2, samples_to_keep * 2 * sizeof( float ) );
    
        out += samples_to_keep * 2;
        }

    if( !voice->source.read_samples || voice->state == AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED )
        {
	    for( int i = 0; i < samples_to_write * 2; ++i ) out[ i ] = 0.0f;	
        return;
        }

    int count_written = voice->source.read_samples( voice->source.instance, out, samples_to_write );
	out += count_written * 2;
	while( count_written < samples_to_write )
		{
		if( voice->loop && voice->source.restart )
			{
            voice->source.restart( voice->source.instance );
            int written = voice->source.read_samples( voice->source.instance, out, samples_to_write - count_written );
			out += written * 2;
            count_written += written;
			}
		else
			{
            audiosys_internal_release_source( &voice->source );
			for( int i = 0; i < ( samples_to_write - count_written ) * 2; ++i ) out[ i ] = 0.0f;	
            return;
			}
		}
    }

   
void audiosys_internal_mix_voice( audiosys_t* audiosys, audiosys_internal_voice_t* voice )
    {
    if( !voice ) return;
					
	float fade_volume = voice->current_fade_volume;
	float fade_delta = voice->current_fade_delta;

    if( voice->pan < 0.0f && fade_delta != 0.0f )
        {
		float a = -voice->pan; 
		float ia = 1.0f - a;
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float l = voice->cached_samples[ i * 2 + 0 ];
		    float r =voice->cached_samples[ i * 2 + 1 ];
			float left = l + a * r;
			float right = r * ia;
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
			fade_volume += fade_delta;
			fade_volume = fade_volume < 0.0f ? 0.0f : fade_volume > 1.0f ? 1.0f : fade_volume;			
		    }
        }
    else if( voice->pan > 0.0f && fade_delta != 0.0f )
        {
		float a = voice->pan;
		float ia = 1.0f - a;
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float l = voice->cached_samples[ i * 2 + 0 ];
		    float r =voice->cached_samples[ i * 2 + 1 ];
			float right = l * a + r;
			float left = l * ia;
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
			fade_volume += fade_delta;
			fade_volume = fade_volume < 0.0f ? 0.0f : fade_volume > 1.0f ? 1.0f : fade_volume;			
		    }
        }
    else if( voice->pan < 0.0f && fade_delta == 0.0f )
        {
		float a = -voice->pan; 
		float ia = 1.0f - a;
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float l = voice->cached_samples[ i * 2 + 0 ];
		    float r =voice->cached_samples[ i * 2 + 1 ];
			float left = l + a * r;
			float right = r * ia;
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
		    }
        }
    else if( voice->pan > 0.0f && fade_delta == 0.0f )
        {
		float a = voice->pan;
		float ia = 1.0f - a;
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float l = voice->cached_samples[ i * 2 + 0 ];
		    float r =voice->cached_samples[ i * 2 + 1 ];
			float right = l * a + r;
			float left = l * ia;
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
		    }
        }
    else if( voice->pan == 0.0f && fade_delta != 0.0f )
        {
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float left = voice->cached_samples[ i * 2 + 0 ];
		    float right =voice->cached_samples[ i * 2 + 1 ];
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
			fade_volume += fade_delta;
			fade_volume = fade_volume < 0.0f ? 0.0f : fade_volume > 1.0f ? 1.0f : fade_volume;			
		    }
        }
    else if( voice->pan == 0.0f && fade_delta == 0.0f )
        {
        for( int i = 0; i < audiosys->buffered_sample_pairs_count; ++i )				
		    {
		    float left = voice->cached_samples[ i * 2 + 0 ];
		    float right =voice->cached_samples[ i * 2 + 1 ];
		    left *= voice->volume * fade_volume * audiosys->master_volume;
		    right *= voice->volume * fade_volume * audiosys->master_volume;
		    audiosys->temp_buffer[ i * 2 + 0 ] += left;
		    audiosys->temp_buffer[ i * 2 + 1 ] += right;
		    }
        }
    else
        {
        PIXIE_ASSERT( false, "Invalid mix parameters" );
        }
    }


void audiosys_update( audiosys_t* audiosys )
	{
    #if defined( _WIN32 )
        int sample_pairs_to_advance = (int)InterlockedExchange( (long*) &audiosys->sample_pairs_to_advance_next_update, 0 );     
    #else
        int sample_pairs_to_advance = (int)__sync_lock_test_and_set( &audiosys->sample_pairs_to_advance_next_update, 0 );
        __sync_lock_release( &atomic->i );
    #endif

    // update sounds from source
    audiosys_internal_update_from_source( audiosys, audiosys->music, sample_pairs_to_advance );
    audiosys_internal_update_from_source( audiosys, audiosys->music_crossfade, sample_pairs_to_advance );
    audiosys_internal_update_from_source( audiosys, audiosys->ambience, sample_pairs_to_advance );
    audiosys_internal_update_from_source( audiosys, audiosys->ambience_crossfade, sample_pairs_to_advance );
    for( int i = 0; i < audiosys->sounds_count; ++i )
        audiosys_internal_update_from_source( audiosys, audiosys_internal_sound_voice( audiosys, i ), sample_pairs_to_advance );

	// remove sounds which have finished playing
	for( int i = audiosys->sounds_count - 1; i >= 0; --i )
		{
		audiosys_internal_voice_t* voice = audiosys_internal_sound_voice( audiosys, i );
		if( voice->source.read_samples == NULL ) audiosys_internal_remove_sound( audiosys, voice->handle );
		}

    // clear buffer for mixing
    for( int i = 0; i < audiosys->buffered_sample_pairs_count * 2; ++i )
        audiosys->temp_buffer[ i ] = 0.0f;
    
    // mix all active voices
    audiosys_internal_mix_voice( audiosys, audiosys->music );
    audiosys_internal_mix_voice( audiosys, audiosys->music_crossfade );
    audiosys_internal_mix_voice( audiosys, audiosys->ambience );
    audiosys_internal_mix_voice( audiosys, audiosys->ambience_crossfade );

    int voice_count = ( audiosys->music ? 1 : 0 ) + ( audiosys->music_crossfade ? 1 : 0 ) + 
        ( audiosys->ambience ? 1 : 0 ) + ( audiosys->ambience_crossfade ? 1 : 0 );

    int sounds_count = audiosys->active_voice_count - voice_count;
    sounds_count = sounds_count > audiosys->sounds_count ? audiosys->sounds_count : sounds_count;
    for( int i = 0; i < sounds_count; ++i )
       audiosys_internal_mix_voice( audiosys, audiosys_internal_get_sound( audiosys, audiosys->sounds_by_priority[ i ] ) );
                

	// clip and convert to 16 bit
    #ifdef _WIN32
        EnterCriticalSection( &audiosys->mutex );
    #else
        pthread_mutex_lock( &audiosys->mutex );
    #endif

    if( audiosys->use_soft_clip )
        {
        for( int i = 0; i < audiosys->buffered_sample_pairs_count * 2; ++i )
            {
            float s = audiosys->temp_buffer[ i ];
            s *= audiosys->gain;
            s /= ( audiosys->active_voice_count / 8 );
            s = s < -1.0f ? -2.0f / 3.0f : s > 1.0f ? 2.0f / 3.0f : s - ( s * s * s ) / 3; // soft clip 
            s *= 32000.0f;
            
            #if ( defined( _M_IX86_FP ) && ( _M_IX86_FP > 0 ) ) || defined( _M_X64 )
                __m128 m;
                m.m128_f32[ 0 ] = s;
                int o = _mm_cvtss_si32( m );
            #else
                AUDIOSYS_ASSERT( fabs( s )<=0x003fffff, "Only 23 bit values handled" );
                float f = s + ( 3 << 22 );
                int t = *(int*)&f;    
                int o = ( i & 0x007fffff ) - 0x00400000;
            #endif

            audiosys->mix_buffer[ i ] = (AUDIOSYS_S16)( o );
            }
        }
    else
        {
        for( int i = 0; i < audiosys->buffered_sample_pairs_count * 2; ++i )
            {
            float s = audiosys->temp_buffer[ i ];
            s *= audiosys->gain;
            s /= ( audiosys->active_voice_count / 8 );
            s *= 32000.0f;
            
            #if ( defined( _M_IX86_FP ) && ( _M_IX86_FP > 0 ) ) || defined( _M_X64 )
                __m128 m;
                m.m128_f32[ 0 ] = s;
                int o = _mm_cvtss_si32( m );
            #else
                AUDIOSYS_ASSERT( fabs( s )<=0x003fffff, "Only 23 bit values handled" );
                float f = s + ( 3 << 22 );
                int t = *(int*)&f;    
                int o = ( i & 0x007fffff ) - 0x00400000;
            #endif

            audiosys->mix_buffer[ i ] = (AUDIOSYS_S16)( o );
            }
        }

    #ifdef _WIN32
        LeaveCriticalSection( &audiosys->mutex );
    #else
        pthread_mutex_unlock( &audiosys->mutex );
    #endif

	}


int audiosys_consume( audiosys_t* audiosys, int sample_pairs_to_advance, AUDIOSYS_S16* output_sample_pairs, int output_sample_pairs_count )
    {
    #ifdef _WIN32
        EnterCriticalSection( &audiosys->mutex );
    #else
        pthread_mutex_lock( &audiosys->mutex );
    #endif

    #if defined( _WIN32 )
        InterlockedExchangeAdd( (long*)&audiosys->sample_pairs_to_advance_next_update, sample_pairs_to_advance );
    #else
        __sync_fetch_and_add( &audiosys->sample_pairs_to_advance_next_update, sample_pairs_to_advance );
    #endif

    int count = output_sample_pairs_count <= audiosys->buffered_sample_pairs_count ? 
        output_sample_pairs_count : audiosys->buffered_sample_pairs_count;
    memcpy( output_sample_pairs, audiosys->mix_buffer, count * 2 * sizeof( AUDIOSYS_S16 ) );

    #ifdef _WIN32
        LeaveCriticalSection( &audiosys->mutex );
    #else
        pthread_mutex_unlock( &audiosys->mutex );
    #endif

    return count;
    }


void audiosys_master_volume_set( audiosys_t* audiosys, float volume )
	{
    audiosys->master_volume = volume < 0.0f ? 0.0f : volume > 1.0f ? 1.0f : volume;
	}


float audiosys_master_volume( audiosys_t* audiosys )
	{
    return audiosys->master_volume;
	}


void audiosys_gain_set( audiosys_t* audiosys, float gain )
	{
    audiosys->gain = gain;
	}


float audiosys_gain( audiosys_t* audiosys )
	{
    return audiosys->gain;
	}


void audiosys_pause( audiosys_t* audiosys )
	{
    audiosys->paused = 1;
	}


void audiosys_resume( audiosys_t* audiosys )
	{
    audiosys->paused = 0;
	}


void audiosys_stop_all( audiosys_t* audiosys )
	{
	audiosys_music_stop( audiosys, 0.0f );
	audiosys_ambience_stop( audiosys, 0.0f );

	for( int i = 0; i < audiosys->sounds_count; ++i )
		{
		audiosys_internal_voice_t* sound = audiosys_internal_sound_voice( audiosys, i );
		sound->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		audiosys_internal_remove_sound( audiosys, sound->handle );
		audiosys_internal_release_source( &sound->source );
		}
	}


audiosys_paused_t audiosys_paused( audiosys_t* audiosys )
	{
    return audiosys->paused ? AUDIOSYS_PAUSED : AUDIOSYS_NOT_PAUSED;
	}


static void audiosys_internal_init_voice( audiosys_internal_voice_t* voice, audiosys_audio_source_t source, int is_sound )
	{
	voice->handle = 0;
	voice->initialized = 0;
	voice->paused = 0;
	voice->state = AUDIOSYS_INTERNAL_VOICE_STATE_PLAYING;
    voice->source = source;
    if( is_sound )
        {
	    voice->loop = 0;
	    voice->volume = 1.0f;
	    voice->pan = 0.0f;
        }
	voice->fade_in_time = 0.0f;
	voice->fade_out_time = 0.0f;
	voice->priority = 0.0f;
	voice->fade_progress = 1.0f;
    voice->current_fade_volume = 1.0f;
    voice->current_fade_delta = 0.0f;
	}


void audiosys_music_play( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_in_time )
	{
    if( !audiosys->music ) return;
    audiosys_internal_release_source( &audiosys->music->source );
	audiosys_internal_init_voice( audiosys->music, source, 0 );
	audiosys->music->fade_in_time = fade_in_time;
	if( fade_in_time > 0.0f ) 
		{
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN;
		audiosys->music->fade_progress = 0.0f;
		}
	}


void audiosys_music_stop( audiosys_t* audiosys, float fade_out_time )
	{
    if( !audiosys->music ) return;
	if( fade_out_time > 0.0f ) 
		{
		audiosys->music->fade_out_time = fade_out_time;
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->music->source );
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		}
	}


void audiosys_music_pause( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return;
    if( audiosys->music->paused == 1 ) return;
    audiosys->music->paused = 1;
	}


void audiosys_music_resume( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return;
    if( audiosys->music->paused == 0 ) return;
    audiosys->music->paused = 0;
	}


void audiosys_music_switch( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_out_time, float fade_in_time )
	{
    if( !audiosys->music ) return;
	if( fade_out_time > 0.0f ) 
		{
		audiosys->music->fade_out_time = fade_out_time;
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->music->source );
		audiosys_music_play( audiosys, source, fade_in_time );
		return;
		}
    audiosys_internal_voice_t temp = *audiosys->music;
    *audiosys->music = *audiosys->music_crossfade;
    *audiosys->music_crossfade = temp;

    audiosys_internal_init_voice( audiosys->music, source, 0 );
	audiosys->music->fade_in_time = fade_in_time;
	if( fade_in_time > 0.0f ) audiosys->music->fade_progress = 0.0f;
	audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_QUEUED;
	}


void audiosys_music_cross_fade( audiosys_t* audiosys, audiosys_audio_source_t source, float cross_fade_time )
	{
    if( !audiosys->music || !audiosys->music_crossfade ) return;
	if( cross_fade_time > 0.0f ) 
		{
		audiosys->music->fade_out_time = cross_fade_time;
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->music->source );
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		}
    audiosys_internal_voice_t temp = *audiosys->music;
    *audiosys->music = *audiosys->music_crossfade;
    *audiosys->music_crossfade = temp;

    audiosys_internal_init_voice( audiosys->music, source, 0 );
	audiosys->music->fade_in_time = cross_fade_time;
	if( cross_fade_time > 0.0f ) 
		{
		audiosys->music->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN;
		audiosys->music->fade_progress = 0.0f;
		}
	}


void audiosys_music_position_set( audiosys_t* audiosys, float position )
	{
    if( !audiosys->music ) return;
    if( !audiosys->music->source.set_position ) return;

    audiosys->music->source.set_position( audiosys->music->source.instance, (int)( position * 44100.0f ) );
	}


float audiosys_music_position( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return 0.0f;
    if( !audiosys->music->source.get_position ) return 0.0f;

    return audiosys->music->source.get_position( audiosys->music->source.instance ) / 44100.0f;
    }


audiosys_audio_source_t audiosys_music_source( audiosys_t* audiosys )
	{
    if( !audiosys->music ) { audiosys_audio_source_t source = { NULL }; return source; }
    return audiosys->music->source;
	}


void audiosys_music_loop_set( audiosys_t* audiosys, audiosys_loop_t loop )
    {
    if( !audiosys->music ) return;
	audiosys->music->loop = loop == AUDIOSYS_LOOP_ON ? 1 : 0;	
	}


audiosys_loop_t audiosys_music_loop( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return AUDIOSYS_LOOP_OFF;
    return audiosys->music->loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF;
	}


void audiosys_music_volume_set( audiosys_t* audiosys, float volume )
	{
    if( !audiosys->music ) return;
	audiosys->music->volume = volume;
	}


float audiosys_music_volume( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return 1.0f;
    return audiosys->music->volume;
    }


void audiosys_music_pan_set( audiosys_t* audiosys, float pan )
	{
    if( !audiosys->music ) return;
	audiosys->music->pan = pan < -1.0f ? -1.0f : pan > 1.0f ? 1.0f : pan;
	}


float audiosys_music_pan( audiosys_t* audiosys )
	{
    if( !audiosys->music ) return 0.0f;
    return audiosys->music->pan;
	}


void audiosys_ambience_play( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_in_time )
	{
    if( !audiosys->ambience ) return;
    audiosys_internal_release_source( &audiosys->ambience->source );
	audiosys_internal_init_voice( audiosys->ambience, source, 0 );
	audiosys->ambience->fade_in_time = fade_in_time;
	if( fade_in_time > 0.0f ) 
		{
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN;
		audiosys->ambience->fade_progress = 0.0f;
		}
	}


void audiosys_ambience_stop( audiosys_t* audiosys, float fade_out_time )
	{
    if( !audiosys->ambience ) return;
	if( fade_out_time > 0.0f ) 
		{
		audiosys->ambience->fade_out_time = fade_out_time;
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->ambience->source );
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		}
	}


void audiosys_ambience_pause( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return;
    if( audiosys->ambience->paused == 1 ) return;
    audiosys->ambience->paused = 1;
	}


void audiosys_ambience_resume( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return;
    if( audiosys->ambience->paused == 0 ) return;
    audiosys->ambience->paused = 0;
	}


void audiosys_ambience_switch( audiosys_t* audiosys, audiosys_audio_source_t source, float fade_out_time, float fade_in_time )
	{
    if( !audiosys->ambience ) return;
	if( fade_out_time > 0.0f ) 
		{
		audiosys->ambience->fade_out_time = fade_out_time;
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->ambience->source );
		audiosys_ambience_play( audiosys, source, fade_in_time );
		return;
		}
    audiosys_internal_voice_t temp = *audiosys->ambience;
    *audiosys->ambience = *audiosys->ambience_crossfade;
    *audiosys->ambience_crossfade = temp;

    audiosys_internal_init_voice( audiosys->ambience, source, 0 );
	audiosys->ambience->fade_in_time = fade_in_time;
	if( fade_in_time > 0.0f ) audiosys->ambience->fade_progress = 0.0f;
	audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_QUEUED;
	}


void audiosys_ambience_cross_fade( audiosys_t* audiosys, audiosys_audio_source_t source, float cross_fade_time )
	{
    if( !audiosys->ambience || !audiosys->ambience_crossfade ) return;
	if( cross_fade_time > 0.0f ) 
		{
		audiosys->ambience->fade_out_time = cross_fade_time;
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
        audiosys_internal_release_source( &audiosys->ambience->source );
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		}
    audiosys_internal_voice_t temp = *audiosys->ambience;
    *audiosys->ambience = *audiosys->ambience_crossfade;
    *audiosys->ambience_crossfade = temp;

    audiosys_internal_init_voice( audiosys->ambience, source, 0 );
	audiosys->ambience->fade_in_time = cross_fade_time;
	if( cross_fade_time > 0.0f ) 
		{
		audiosys->ambience->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN;
		audiosys->ambience->fade_progress = 0.0f;
		}
	}


void audiosys_ambience_position_set( audiosys_t* audiosys, float position )
	{
    if( !audiosys->ambience ) return;
    if( !audiosys->ambience->source.set_position ) return;

    audiosys->ambience->source.set_position( audiosys->ambience->source.instance, (int)( position * 44100.0f ) );
	}


float audiosys_ambience_position( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return 0.0f;
    if( !audiosys->ambience->source.get_position ) return 0.0f;

    return audiosys->ambience->source.get_position( audiosys->ambience->source.instance ) / 44100.0f;
    }

audiosys_audio_source_t audiosys_ambience_source( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) { audiosys_audio_source_t source = { NULL }; return source; }
    return audiosys->ambience->source;
	}


void audiosys_ambience_loop_set( audiosys_t* audiosys, audiosys_loop_t loop )
	{
    if( !audiosys->ambience ) return;
	audiosys->ambience->loop = loop == AUDIOSYS_LOOP_ON ? 1 : 0;	
	}


audiosys_loop_t audiosys_ambience_loop( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return AUDIOSYS_LOOP_OFF;
    return audiosys->ambience->loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF;
	}


void audiosys_ambience_volume_set( audiosys_t* audiosys, float volume )
	{
    if( !audiosys->ambience ) return;
	audiosys->ambience->volume = volume;
	}


float audiosys_ambience_volume( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return 0.0f;
    return audiosys->ambience->volume;
	}


void audiosys_ambience_pan_set( audiosys_t* audiosys, float pan )
	{
    if( !audiosys->ambience ) return;
	audiosys->ambience->pan = pan < -1.0f ? -1.0f : pan > 1.0f ? 1.0f : pan;
	}


float audiosys_ambience_pan( audiosys_t* audiosys )
	{
    if( !audiosys->ambience ) return 0.0f;
    return audiosys->ambience->pan;
	}


AUDIOSYS_U64 audiosys_sound_play( audiosys_t* audiosys, audiosys_audio_source_t source, float priority, float fade_in_time )
	{
	audiosys_internal_voice_t* sound;
	AUDIOSYS_U64 handle = audiosys_internal_add_sound( audiosys, &sound, priority );
	audiosys_internal_init_voice( sound, source, 1 );
	sound->handle = handle;
	sound->priority = priority;
	sound->fade_in_time = fade_in_time;
	if( fade_in_time > 0.0f ) 
		{
		sound->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_IN;
		sound->fade_progress = 0.0f;
		}
	return handle;
    }


void audiosys_sound_stop( audiosys_t* audiosys, AUDIOSYS_U64 handle, float fade_out_time )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;

	if( fade_out_time > 0.0f ) 
		{
		sound->fade_out_time = fade_out_time;
		sound->state = AUDIOSYS_INTERNAL_VOICE_STATE_FADING_OUT;
		}
	else
		{
		sound->state = AUDIOSYS_INTERNAL_VOICE_STATE_STOPPED;
		audiosys_internal_remove_sound( audiosys, handle );
        audiosys_internal_release_source( &sound->source );
		}
	}


void audiosys_sound_pause( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
    if( sound->paused == 1 ) return;
    sound->paused = 1;
	}


void audiosys_sound_resume( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
    if( sound->paused == 0 ) return;
    sound->paused = 0;
	}


void audiosys_sound_position_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float position )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
    if( !sound->source.set_position ) return;

    sound->source.set_position( sound->source.instance, (int)( position * 44100.0f ) );
	}


float audiosys_sound_position( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return 0.0f;
    if( !sound->source.get_position ) return 0.0f;

    return sound->source.get_position( sound->source.instance ) / 44100.0f;
	}


audiosys_audio_source_t audiosys_sound_source( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) 
        {
        audiosys_audio_source_t null_source;
        AUDIOSYS_MEMSET( &null_source, 0, sizeof( null_source ) );
        return null_source;
        }
    return sound->source;
	}


void audiosys_sound_loop_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, audiosys_loop_t loop )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
	sound->loop = loop == AUDIOSYS_LOOP_ON ? 1 : 0;	
	}


audiosys_loop_t audiosys_sound_loop( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return AUDIOSYS_LOOP_OFF;
    return sound->loop ? AUDIOSYS_LOOP_ON : AUDIOSYS_LOOP_OFF;
	}


void audiosys_sound_volume_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float volume )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
	sound->volume = volume;
	}


float audiosys_sound_volume( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return 0.0f;
    return sound->volume;
	}


void audiosys_sound_pan_set( audiosys_t* audiosys, AUDIOSYS_U64 handle, float pan )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return;
	sound->pan = pan < -1.0f ? -1.0f : pan > 1.0f ? 1.0f : pan;
	}


float audiosys_sound_pan( audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return 0.0f;
    return sound->pan;
	}


audiosys_sound_valid_t audiosys_sound_valid(audiosys_t* audiosys, AUDIOSYS_U64 handle )
	{
	audiosys_internal_voice_t* sound = audiosys_internal_get_sound( audiosys, handle );
	if( !sound ) return AUDIOSYS_SOUND_INVALID;
	return AUDIOSYS_SOUND_VALID;
	}

#endif /* AUDIOSYS_IMPLEMENTATION */

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
