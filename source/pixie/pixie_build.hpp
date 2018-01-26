/*
------------------------------------------------------------------------------
		  Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

pixie_build.hpp - v0.1 - 

*/

#ifndef pixie_build_hpp
#define pixie_build_hpp

#include <stddef.h>
#include "cpp_compat.hpp"

namespace pixie_build {

typedef int8_t i8; typedef int16_t i16; typedef int32_t i32; typedef int64_t i64;
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;

}

#include "array.hpp"
#include "binary_rw.h"
#include "dictionary.hpp"
#include "math_util.hpp"
#include "refcount.hpp"
#include "sort.hpp"
#include "strpool.hpp"
#include "strpool_util.hpp"
#include "vecmath.hpp"

namespace pixie_build {

namespace internal {
struct PIXIE_BUILD_STRING_POOL;
struct PIXIE_BUILD_STRING_ID_POOL;
} /* namespace internal */

typedef strpool::string_type<internal::PIXIE_BUILD_STRING_POOL> string;
typedef strpool::string_type<internal::PIXIE_BUILD_STRING_ID_POOL> string_id;

#pragma warning( push ) 
#pragma warning( disable: 4619 ) // pragma warning : there is no warning number 'number'
#pragma warning( disable: 4217 ) // nonstandard extension used : function declaration from a previous block

template< typename T, int CAPACITY = 16 > struct array : array_ns::array_type< T, CAPACITY, array_ns::NOT_POD >
	{ 
	explicit array( int initial_capacity = CAPACITY );
	template< typename U > array( U const& other );
	template< typename U > explicit array( U const* items, int count );
	};


template< typename T, int CAPACITY = 16 > struct pod_array : array_ns::array_type< T, CAPACITY, array_ns::IS_POD >
	{ 
	explicit pod_array( int initial_capacity = CAPACITY );
	template< typename U > pod_array( U const& other );
	template< typename U > explicit pod_array( U const* items, int count );
	};

#pragma warning( pop ) 

struct compilation_result
	{
	int succeeded;
	int failed;
	int uptodate;
	};


struct compiler_param
	{
	string_id name;
	string_id value;
	};


struct compile_context
	{
	string input_root;
	string build_root;
	string output_root;
	string path;
	string input;
	array<compiler_param> parameters;
	};


struct compiler_list
	{
	char const* id;
	compilation_result (*compiler)( compile_context const* context );
	};
	

compilation_result compiler_pixie_copy( compile_context const* context );	
compilation_result compiler_pixie_palette( compile_context const* context );
compilation_result compiler_pixie_bitmap( compile_context const* context );
compilation_result compiler_pixie_font( compile_context const* context );

static compiler_list default_compilers[] =
	{
	{ "pixie_copy", compiler_pixie_copy, },
	{ "pixie_palette", compiler_pixie_palette, },
	{ "pixie_bitmap", compiler_pixie_bitmap, },
//	{ "pixie_font", compiler_pixie_font, },
	};


enum build_action
	{
	BUILD_ACTION_UNDEFINED,
	BUILD_ACTION_BUILD,
	BUILD_ACTION_REBUILD,
	BUILD_ACTION_CLEAN,
	};

int build( build_action action, char const* input_path, char const* build_path, char const* output_path, compiler_list* compilers = 0, int compilers_count = 0 );

using strpool::str; using strpool::trim; using strpool::ltrim; 
using strpool::rtrim; using strpool::left; using strpool::right; using strpool::mid	; using strpool::instr; 
using strpool::any; using strpool::upper; using strpool::lower; 
using strpool::val; using strpool::integer; using strpool::space; using strpool::flip; using strpool::repeat; 
using strpool::chr; using strpool::asc; using strpool::len;
using refcount::ref;
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
using math_util::PI; using math_util::TWO_PI;
using dictionary_ns::dictionary;


inline string str( int x ) { return strpool::str<pixie_build::internal::PIXIE_BUILD_STRING_POOL>( x ); }
inline string str( float x ) { return strpool::str<pixie_build::internal::PIXIE_BUILD_STRING_POOL>( x ); }

#define str_switch( x ) pixie_build::string_id const& multiple_str_switch_not_allowed_within_the_same_scope( x );
#define str_case( x ) if( multiple_str_switch_not_allowed_within_the_same_scope == pixie_build::string_id( x ) )


template< typename T > void swap( T* a, T* b );

void random_seed( u32 seed );
float random();
int random( int min, int max );
float random_bell_curve( int iterations = 3 );
int random_bell_curve( int min, int max, int iterations = 3 );
template< typename T > void shuffle( T* elements, int count );
template< typename T > void shuffle( array<T>* arr );
template< typename T > void shuffle( pod_array<T>* arr );
float3 random_unit_vector();

template< typename T > void sort( T* elements, int count );
template< typename T > void sort( array<T>* arr );
template< typename T > void sort( pod_array<T>* arr );

template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( T* array, int count );
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( array<T>* arr );
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void custom_sort( pod_array<T>* arr );

template< typename T > int find( T const* haystack_elements, int haystack_count, T const& needle );
template< typename T > int find( array<T> const& haystack, T const& needle );
template< typename T > int find( pod_array<T> const& haystack, T const& needle );

int abs( int x );
int min( int x, int y );
int max( int x, int y );
int clamp( int x, int min_val, int max_val );

struct binary { size_t size; void* data; };

ref<binary> bload( string const& filename );
ref<binary> bnew( size_t size );
ref<binary> bresize( ref<binary> const& bin, size_t new_size );

string basename( string a );
string extname( string a );
string dirname( string a );

string path_join( string const& a, string const& b );
string path_join( string const& a, string const& b, string const& c );
string path_join( string const& a, string const& b, string const& c, string const& d );
string path_join( string const& a, string const& b, string const& c, string const& d, string const& e );

void logf( string str, ... );

bool file_exists( string const& filename );

} /* namespace pixie_build */


#endif // pixie_build_hpp



/*
----------------------
	IMPLEMENTATION
----------------------
*/


#ifndef pixie_build_impl
#define pixie_build_impl

namespace pixie_build { namespace internal {

strpool::internal::string_pool& string_pool();
strpool::internal::string_pool& string_id_pool();

} /* namespace internal */ } /* namespace pixie */



template<> inline strpool::internal::string_pool& strpool::internal::pool_instance<pixie_build::internal::PIXIE_BUILD_STRING_POOL>( bool )
	{
	return pixie_build::internal::string_pool();
	}
	
template<> inline strpool::internal::string_pool& strpool::internal::pool_instance<pixie_build::internal::PIXIE_BUILD_STRING_ID_POOL>( bool )
	{
	return pixie_build::internal::string_id_pool();
	}


template< typename T > void pixie_build::swap( T* a, T* b )
	{
	// expressed using only copy constructor, no assignment operator, for consistency with container classes
	T t( *a ); // t = a
	a->~T(); new ( a ) T( *b ); // a = b
	b->~T(); new ( b ) T( t ); // b = t
	}
	

template< typename T, int CAPACITY > pixie_build::array<T, CAPACITY>::array( int initial_capacity = CAPACITY ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( initial_capacity, 0 ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie_build::array<T, CAPACITY>::array( U const& other ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( other ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie_build::array<T, CAPACITY>::array( U const* items, int count ) : 
	array_ns::array_type<T, CAPACITY, array_ns::NOT_POD>( items, count, 0 ) 
	{ }


template< typename T, int CAPACITY > pixie_build::pod_array<T, CAPACITY>::pod_array( int initial_capacity = CAPACITY ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( initial_capacity, 0 ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie_build::pod_array<T, CAPACITY>::pod_array( U const& other ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( other ) 
	{ }

template< typename T, int CAPACITY > template< typename U > pixie_build::pod_array<T, CAPACITY>::pod_array( U const* items, int count ) : 
	array_ns::array_type<T, CAPACITY, array_ns::IS_POD>( items, count, 0 ) 
	{ }


template< typename T > void pixie_build::shuffle( T* elements, int count )
	{
	for( int i = 0; i < count; ++i )
		{
		int const r = random( i, count - 1 );
		swap( &elements[ i ], &elements[ r ] );
		}
	}
	
	
template< typename T > void pixie_build::shuffle( array<T>* arr )
	{
	shuffle( arr->data(), arr->count() );
	}


template< typename T > void pixie_build::shuffle( pod_array<T>* arr )
	{
	shuffle( arr->data(), arr->count() );
	}
	
template< typename T > void pixie_build::sort( T* elements, int count )
	{
	::sort_ns::sort( elements, count );
	}

template< typename T > void pixie_build::sort( array<T>* arr )
	{
	::sort_ns::sort( arr->data(), arr->count() );
	}

template< typename T > void pixie_build::sort( pod_array<T>* arr )
	{
	::sort_ns::sort( arr->data(), arr->count() );
	}
		
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie_build::custom_sort( T* elements, int count )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( array, count );
	}
	
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie_build::custom_sort( array<T>* arr )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( arr->data(), arr->count() );
	}
	
template< typename T, int (*COMPARE_FUNC)( T const&, T const& ) > void pixie_build::custom_sort( pod_array<T>* arr )
	{
	::sort_ns::sort<T, COMPARE_FUNC>( arr->data(), arr->count() );
	}


template< typename T > int pixie_build::find( T const* haystack_elements, int haystack_count, T const& needle ) 
	{ 
	for( int i = 0; i < haystack_count; ++i )
		if( haystack_elements[ i ] == needle ) return i;
	return -1;
	}

template< typename T > int pixie_build::find( array<T> const& haystack, T const& needle )
	{
	return find( haystack.data(), haystack.count(), needle );
	}

template< typename T > int pixie_build::find( pod_array<T> const& haystack, T const& needle )
	{
	return find( haystack.data(), haystack.count(), needle );
	}



#endif /* pixie_build_impl */


#ifdef PIXIE_BUILD_IMPLEMENTATION
#undef PIXIE_BUILD_IMPLEMENTATION

#include "dir.h"
#include "file.h"
#include "file_util.h"
#include "ini.h"
#include "log.h"
#include "paldither.h"
#include "palettize.h"
#include "rnd.h"
#include "thread.h"

#include "stb_image.h"
#include "stb_perlin.h"

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdarg.h>


namespace pixie_build { namespace internal { 

static thread_tls_t internals_tls;
struct internals_t; 
internals_t* internals(); 

} /* namespace internal */ } /* namespace pixie_build */


pixie_build::internal::internals_t* pixie_build::internal::internals()
	{
	assert( internals_tls && "Attempt to call a Pixie build function from outside a pixie_build::build block." );
	void* ptr = thread_tls_get( internals_tls );
	assert( ptr && "Attempt to call a Pixie build function from a thread which it is not running on." );
	return (internals_t*) ptr;
	}
	
struct pixie_build::internal::internals_t final    
	{
	internals_t();
	
	log_t* log;
	char* log_buffer;
	size_t log_capacity;

	strpool::internal::string_pool string_pool;
	strpool::internal::string_pool string_id_pool;
	rnd_pcg_t rng_instance;
	};


pixie_build::internal::internals_t::internals_t() :
	string_pool( true ),
	string_id_pool( false )
	{ 
	rnd_pcg_seed( &rng_instance, 0 );
	}


strpool::internal::string_pool& pixie_build::internal::string_pool()
	{
	return internals()->string_pool;
	}
	
	
strpool::internal::string_pool& pixie_build::internal::string_id_pool()
	{
	return internals()->string_id_pool;
	}


float pixie_build::random()
	{
	internal::internals_t* internals = internal::internals();
	return rnd_pcg_nextf( &internals->rng_instance);
	}
	
	

int pixie_build::random( int min, int max )
	{
	internal::internals_t* internals = internal::internals();
	return rnd_pcg_range( &internals->rng_instance, min, max );
	}

	
void pixie_build::random_seed( u32 seed )
	{
	internal::internals_t* internals = internal::internals();
	rnd_pcg_seed( &internals->rng_instance, seed );
	}
	
	
float pixie_build::random_bell_curve( int iterations )
	{
	float sum = 0.0f;
	for( int i = 0; i < iterations; ++i )
		sum += random();
	return sum / (float) iterations;
	}


int pixie_build::random_bell_curve( int min, int max, int iterations )
	{
	int const range = ( max - min ) + 1;
	if( range <= 0 ) return min;
	int const value = (int) ( random_bell_curve( iterations ) * range );
	return min + value; 
	}
	
		
pixie_build::float3 pixie_build::random_unit_vector()
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


namespace pixie_build { namespace internal {

void binary_delete( void* instance )
	{
	free( instance ); 
	}

} /* namespace internal */ } /*namespace pixie */


pixie_build::ref<pixie_build::binary> pixie_build::bload( string const& filename )
	{
	file_t* file = file_load( filename.c_str(), FILE_MODE_BINARY, 0 );
	if( !file ) return ref<binary>::ref();
	size_t file_size = file->size;
	void* storage = malloc( sizeof( binary ) + sizeof( int ) + file_size ); 
	void* file_data = (void*)( (uintptr_t)storage + sizeof( binary ) + sizeof( int ) );
	memcpy( file_data, file->data, file_size );
	file_destroy( file );

	binary* bin = (binary*)storage;
	bin->data = (u8*)file_data;
	bin->size = file_size;
	return refcount::make_ref( bin, internal::binary_delete, (int*)( (uintptr_t)storage + sizeof( binary ) ), 0 );
	}

	
pixie_build::ref<pixie_build::binary> pixie_build::bnew( size_t size )
	{
	void* storage = malloc( sizeof( binary ) + sizeof( int ) + size ); 
	binary* bin = (binary*)storage;
	bin->data = (u8*)( (uintptr_t)storage + sizeof( binary ) + sizeof( int ) );
	bin->size = (size_t)size;
	return refcount::make_ref( bin, internal::binary_delete, (int*)( (uintptr_t)storage + sizeof( binary ) ), 0 );
	}


pixie_build::ref<pixie_build::binary> pixie_build::bresize( ref<binary> const& bin, size_t new_size )
	{
	ref<binary> new_binary = bnew( new_size );
	memcpy( new_binary->data, bin->data, new_size < bin->size ? new_size : bin->size );
	return new_binary;
	}




namespace pixie_build {

string path_join( string const& a, string const& b )
	{
	string r = a;
	if( len( a ) > 0 && len( b ) > 0 ) r += "/";
	r += b;
	return r;
	}

string path_join( string const& a, string const& b, string const& c )
	{
	return path_join( path_join( a, b ), c );
	}

string path_join( string const& a, string const& b, string const& c, string const& d )
	{
	return path_join( path_join( path_join( a, b ), c ), d );
	}

string path_join( string const& a, string const& b, string const& c, string const& d, string const& e )
	{
	return path_join( path_join( path_join( path_join( a, b ), c ), d ), e );
	}
	

void logf( string str, ... )
	{
	#pragma warning( push )
	#pragma warning( disable: 4619 ) // there is no warning number '4840'
	#pragma warning( disable: 4840 ) // non-portable use of class 'strpool::string_type<pixie_build::internal::PIXIE_BUILD_STRING_POOL>' as an argument to a variadic function
	pixie_build::internal::internals_t* internals = pixie_build::internal::internals();    
	va_list args;
	va_start( args, str );
	size_t count = (size_t) _vsnprintf( internals->log_buffer, internals->log_capacity, str.c_str(), args );
	va_end( args );
	if( count >= internals->log_capacity )
		{
		if( internals->log_capacity == 0 )
			internals->log_capacity = 1024;
		else
			internals->log_capacity = ( internals->log_capacity * 2 <= count ) ? count + 1 : internals->log_capacity * 2;
		internals->log_buffer = (char*) malloc( internals->log_capacity );
		va_start (args, str);
		count = (size_t) _vsnprintf( internals->log_buffer, internals->log_capacity, str.c_str(), args );
		va_end (args);
		}

	log_print( internals->log, internals->log_buffer );
	#pragma warning( pop )
	}


bool file_exists( string const& filename )
	{
	return ::file_exists( filename.c_str() ) != 0;
	}

	
struct compile_counts
	{
	int succeeded;
	int failed;
	int uptodate;

	compile_counts() : succeeded( 0 ), failed( 0 ), uptodate( 0 ) {}

	void operator+=( compile_counts other )
		{
		succeeded += other.succeeded;
		failed += other.failed;
		uptodate += other.uptodate;
		}
	};
	
struct file_location
	{
	string_id filename;
	int line;
	};
	
struct missing_buildstep
	{
	string_id buildstep;
	file_location location;
	};
	
	
struct build_t
	{
	string root_input;
	string root_build;
	string root_output;
	compiler_list* compilers;
	int compilers_count;
	array<missing_buildstep> missing_buildsteps_reported;
	};


struct config_buildstep
	{
	string_id id;
	string_id compiler;
	array<compiler_param> parameters;
	file_location location;
	};

struct build_mapping
	{
	string_id name;
	string_id buildstep;
	file_location location;
	};

struct config
	{
	config() : valid( false ) {}
	
	bool valid;
	build_mapping folder_mapping;
	file_location folder_mapping_location;
	array<build_mapping> file_mappings;
	array<config_buildstep> buildsteps;
	};	


config read_config( build_t* build, string const& path )
	{
	(void) build;
	config cfg;
	cfg.valid = false;
	
	string relative_path = dirname( path.c_str() );
	if( right( relative_path, 1 ) == "/" || right( relative_path, 1 ) == "\\" ) relative_path = left( relative_path, len( relative_path ) -1 );
	// TODO: append relative path to file name

	file_t* file = file_load( path.c_str(), FILE_MODE_TEXT, 0 );
	if( !file ) return cfg;
	
	ini_t* ini = ini_load( file->data, 0 );
	file_destroy( file );
	if( !ini ) return cfg;
	
	// TODO: check for duplicate mappings and buildsteps
	
	// file mappings
	int pcount = ini_property_count( ini, INI_GLOBAL_SECTION );
	for( int i = 0; i < pcount; ++i )
		{
		string_id name = ini_property_name( ini, INI_GLOBAL_SECTION, i );
		string_id value = ini_property_value( ini, INI_GLOBAL_SECTION, i );
		name = trim( name );
		value = trim( value );
		if( name == "folder" )
			{
			if( cfg.folder_mapping.name != "" ) (void)i; // TODO: error handling
			cfg.folder_mapping.name = "folder";
			cfg.folder_mapping.buildstep = value;
			cfg.folder_mapping_location.filename = path;
			cfg.folder_mapping_location.line = 0; 
			}
		else
			{
			build_mapping mapping;
			if( left( name, 1 ) != "." ) name = path_join( relative_path,  name );
			mapping.name = name;
			mapping.buildstep = value;
			cfg.file_mappings.add( mapping );
			}
		}
		
	// buildsteps		
	int scount = ini_section_count( ini );
	for( int i = 0; i < scount; ++i )
		{
		string_id section = ini_section_name( ini, i );
		if( section == "" ) continue;
		
		config_buildstep step;
		step.id = section;
		int prop_count = ini_property_count( ini, i );
		for( int j = 0; j < prop_count; ++j )
			{
			string_id name = ini_property_name( ini, i, j );
			string_id value = ini_property_value( ini, i, j );
			name = trim( name );
			value = trim( value );
			if( name == "compiler" )
				{
				if( step.compiler != "" ) (void)i; // TODO: error handling
				step.compiler = value;
				}
			else
				{
				compiler_param param;
				param.name = name;
				param.value = value;
				step.parameters.add( param );
				}
			}
		cfg.buildsteps.add( step );
		}
	
	ini_destroy( ini );	
	cfg.valid = true;
	return cfg;
	}
	
	
config merge_cfg( config const& a, config const& b )	
	{
	config cfg;
	cfg.valid = false;
	if( !a.valid && !b.valid ) return cfg;
	if( !a.valid ) return b;
	cfg = a;
	if( b.valid )
		{
		if( b.folder_mapping.name != "" ) cfg.folder_mapping = b.folder_mapping;

		for( int i = 0; i < b.file_mappings.count(); ++i )
			{
			build_mapping m = b.file_mappings[ i ];
			for( int j = 0; cfg.file_mappings.count(); ++j )
				{
				if( cfg.file_mappings[ j ].name == m.name )
					{
					cfg.file_mappings.remove( j );
					break;
					}
				}
			if( m.buildstep != "" ) cfg.file_mappings.add( m );
			}

		for( int i = 0; i < b.buildsteps.count(); ++i )
			{
			config_buildstep s = b.buildsteps[ i ];
			for( int j = 0; j < cfg.buildsteps.count(); ++j )
				{
				if( cfg.buildsteps[ j ].id == s.id )
					{
					cfg.buildsteps.remove( j );
					break;
					}
				}
			if( s.compiler != "" ) cfg.buildsteps.add( s );
			}
		}
	
	return cfg;
	}

compile_counts build_file( build_t* build, config cfg, string buildstep, string filename, string const& build_path, string const& out_path  )
	{
	(void) build, cfg, filename, build_path, out_path;
//	printf( "%s: %s\n", buildstep.c_str(), filename.c_str() + len( build->root_input ) + 1 );
	filename = filename.c_str() + len( build->root_input ) + 1;
	for( int i = 0; i < cfg.buildsteps.count(); ++i )
		{
		config_buildstep s = cfg.buildsteps[ i ];
		if( s.id == buildstep )
			{
			bool found = false;
			for( int j = 0; j < build->compilers_count; ++j )
				{
				if( s.compiler == build->compilers[ j ].id )
					{
					compile_context context;
					context.input_root = build->root_input;
					context.build_root = build->root_build;
					context.output_root = build->root_output;
					context.path = dirname( filename.c_str() );
					context.path = left( context.path, len( context.path ) - 1 );
					context.input = filename.c_str() + len( context.path ) + ( len( context.path ) == 0 ? 0 : 1 );
					context.parameters = s.parameters;
					build->compilers[ j ].compiler( &context );
					found = true;
					}
				}
			if( !found ) 
				{
				//logf( "%s(%d) : error: build step '%s' not found when compiling '%s'\n", __FILE__, __LINE__, buildstep.c_str(), filename.c_str() );
				}
			break;
			}
		}
		
	return compile_counts();
	}
	
	
compile_counts build_folder( build_t* build, config cfg, string buildstep, string foldername, string const& build_path, string const& out_path )
	{
	(void) build, cfg, foldername, build_path, out_path;
//	printf( "%s: %s\n", buildstep.c_str(), filename.c_str() + len( build->root_input ) + 1 );
	foldername = foldername.c_str() + len( build->root_input ) + 1;
	for( int i = 0; i < cfg.buildsteps.count(); ++i )
		{
		config_buildstep s = cfg.buildsteps[ i ];
		if( s.id == buildstep )
			{
			bool found = false;
			for( int j = 0; j < build->compilers_count; ++j )
				{
				if( s.compiler == build->compilers[ j ].id )
					{
					compile_context context;
					context.input_root = build->root_input;
					context.build_root = build->root_build;
					context.output_root = build->root_output;
					context.path = dirname( foldername.c_str() );
					context.path = left( context.path, len( context.path ) - 1 );
					context.input = foldername.c_str() + len( context.path ) + ( len( context.path ) == 0 ? 0 : 1 );
					context.parameters = s.parameters;
					build->compilers[ j ].compiler( &context );
					found = true;
					}
				}
			if( !found ) 
				{
				//logf( "%s(%d) : error: build step '%s' not found when compiling '%s'\n", __FILE__, __LINE__, buildstep.c_str(), filename.c_str() );
				}
			break;
			}
		}
		
	return compile_counts();
	}
	

compile_counts build_dir( build_t* build, config cfg, string const& input, string const& build_path, string const& output )
	{
	compile_counts counts;
	cfg = merge_cfg( cfg, read_config( build, input + "/build.ini" ) );
	
	// subdirs
	dir_t* dir = dir_open( input.c_str() );
	if( !dir ) { /* TODO: error handling */ return counts; }
	dir_entry_t* ent = dir_read( dir );
	while( ent )
	    {
	    if( dir_is_folder( ent ) && strcmp( dir_name( ent ), "." ) != 0 && strcmp( dir_name( ent ), ".." ) != 0 )
	        {
	        if( cfg.folder_mapping.name != "folder" )
				{
				string new_input = path_join( input, dir_name( ent ) );
				string new_build_path = path_join( build_path, dir_name( ent ) );
				string new_output = path_join( output, dir_name( ent ) );
				build_dir( build, cfg, new_input, new_build_path, new_output );
				}
			}
	    ent = dir_read( dir );
	    }
	dir_close( dir );

	// files
	dir = dir_open( input.c_str() );
	if( !dir ) { /* TODO: error handling */ return counts; }
	ent = dir_read( dir );
	while( ent )
	    {
	    if( dir_is_folder( ent ) && strcmp( dir_name( ent ), "." ) != 0 && strcmp( dir_name( ent ), ".." ) != 0 )
	        {
	        if( cfg.folder_mapping.name == "folder" )
				{
				string foldername = dir_name( ent );
				build_folder( build, cfg, cfg.folder_mapping.buildstep, path_join( input, foldername ), build_path, output );
				}
	        }
	    else if( dir_is_file( ent )  )
	        {
	        string filename = path_join( input, dir_name( ent ) );
	        bool found = false;
			for( int i = 0; i < cfg.file_mappings.count(); ++i )
				{
				build_mapping m = cfg.file_mappings[ i ];
				if( filename == m.name )
					{
					build_file( build, cfg, m.buildstep, filename, build_path, output );
					found = true;
					break;
					}
				}

			if( !found )
				{
				string extension = extname( dir_name( ent ) );
				for( int i = 0; i < cfg.file_mappings.count(); ++i )
					{
					build_mapping m = cfg.file_mappings[ i ];
					if( extension == m.name )
						{
						build_file( build, cfg, m.buildstep, filename, build_path, output );
						found = true;
						break;
						}
					}
				}			
	        }

	    ent = dir_read( dir );
	    }
	dir_close( dir );

	return counts;
	}

/*	        
	        const char* asset_type = dir_name( ent );
	        compiler_t* compiler = find_compiler( conditioner, asset_type );
	        if( compiler )
	            {
				char source_path[ MAX_PATH ]; 
				char build_path[ MAX_PATH ];
				char output_path[ MAX_PATH ];
				strcat( strcat( strcpy( source_path, conditioner->source_path ), "/" ), asset_type );
				strcat( strcat( strcpy( build_path, conditioner->build_path ), "/" ), asset_type );
				strcat( strcat( strcpy( output_path, conditioner->output_path ), "/" ), asset_type );
				compile_context_t context;
				context.asset_type = asset_type;
				context.source_path = source_path;
				context.build_path = build_path;
				context.output_path = output_path;
				context.log = conditioner->log;
				log_queue( conditioner->log, "\nCompiling asset type '%s'...\n", asset_type );                
				if( compiler->compile )
					{
		            counts += compiler->compile( &context );
					}
				else
					{
					log_print( conditioner->log, "%s(%d) : error: no compiler registered for asset type '%s'\n", __FILE__, __LINE__, asset_type );
					++counts.failed;
					}
				log_cancel_queued( conditioner->log );               
	            }
	        else
	            {
				log_print( conditioner->log, "%s(%d) : error: no compiler registered for asset type '%s'\n", __FILE__, __LINE__, asset_type );
	            ++counts.failed;
	            }
*/


compilation_result compiler_pixie_copy( compile_context const* context )
	{
	compilation_result result = { 0 };
	string input_file = path_join( context->input_root, context->path, context->input );
	string output_file = path_join( context->output_root, context->path, context->input );
	if( !file_exists( output_file.c_str() ) || file_more_recent( input_file.c_str(), output_file.c_str() ) )
		{
		logf( path_join( context->path, context->input ) + "\n" );
		create_path( path_join( context->output_root,context->path ).c_str() );
		copy_file( input_file.c_str(), output_file.c_str() );
		}
	return result;
	}

string basename( string a )
	{
	return ::basename( a.c_str(), ::extname( a.c_str() ) );
	}

string extname( string a )
	{
	return ::extname( a.c_str() );
	}

string dirname( string a )
	{
	return ::dirname( a.c_str() );
	}


void build_palette_lookup( string const& input_file, string const& output_file )
	{
	int w, h, c;
	stbi_uc* img = stbi_load( input_file.c_str(), &w, &h, &c, 4 );
	u32 palette[ 256 ];		
	memset( palette, 0, 256 * sizeof( u32 ) );
	int count = 0;		
	for( int y = 0; y < h; ++y )
		{
		for( int x = 0; x < w; ++x )	
			{
			u32 pixel = ((u32*)img)[ x + y * w ];
			if( ( pixel & 0xff000000 ) == 0 ) goto skip;
			pixel = ( pixel & 0x00ffffff ) | 0xff000000;
			if( count < 256 ) 
				{
				for( int i = 0; i < count; ++i )
					{
					if( palette[ i ] == pixel )
						goto skip;
					}
					palette[ count ] = pixel;		
				}
			++count;
		skip:
			;
			}
		}
	if( count > 256 ) 
		{
		memset( palette, 0, 256 * sizeof( u32 ) );
		count = palettize_generate_palette_xbgr32( (PALETTIZE_U32*) img, w, h, palette, 256, 0 );        
		}

	stbi_image_free( img );

	size_t size = 0;
	paldither_palette_t* pal = paldither_palette_create( palette, count, &size, 0 );
	create_path( dirname( output_file ).c_str() );
	file_save_data( pal, size, output_file.c_str(), FILE_MODE_BINARY );
	paldither_palette_destroy( pal );
	}


compilation_result compiler_pixie_palette( compile_context const* context )
	{
	compilation_result result = { 0 };

	string input_file = path_join( context->input_root, context->path, context->input );

	bool file_printed = false;
	string output_file = path_join( context->output_root, context->path, basename( context->input ) ) + ".pal";
	if( !file_exists( output_file.c_str() ) || file_more_recent( input_file.c_str(), output_file.c_str() ) )
		{
		string build_file = path_join( context->build_root, context->path, basename( context->input ) ) + ".plut";
		if( !file_exists( build_file.c_str() ) || file_more_recent( input_file.c_str(), build_file.c_str() ) )
			{
			logf( path_join( context->path, context->input ) + "\n" );
			file_printed = true;
			build_palette_lookup( input_file, build_file );
			}

		if( !file_printed ) logf( path_join( context->path, context->input ) + "\n" );
		int w, h, c;
		stbi_uc* img = stbi_load( input_file.c_str(), &w, &h, &c, 4 );

		char const header[] = "PIXIE_PAL";
		int version = 1;
		u8 storage[ sizeof( header ) + sizeof( version ) + 256 * sizeof( u32 ) ];
		memcpy( storage, header, sizeof( header ) );
		memcpy( storage + sizeof( header ), &version, sizeof( version) );
		u32* palette = (u32*)( storage + sizeof( header ) + sizeof( version ) );		
		memset( palette, 0, 256 * sizeof( u32 ) );
		int count = 0;		
		for( int y = 0; y < h; ++y )
			{
			for( int x = 0; x < w; ++x )	
				{
				u32 pixel = ((u32*)img)[ x + y * w ];
				if( ( pixel & 0xff000000 ) == 0 ) goto skip;
				pixel = ( pixel & 0x00ffffff ) | 0xff000000;
				if( count < 256 ) 
					{
					for( int i = 0; i < count; ++i )
						{
						if( palette[ i ] == pixel )
							goto skip;
						}
						palette[ count ] = pixel;		
					}
				++count;
			skip:
				;
				}
			}	
		if( count > 256 ) 
			{
			memset( palette, 0, 256 * sizeof( u32 ) );
			count = palettize_generate_palette_xbgr32( (PALETTIZE_U32*) img, w, h, palette, 256, 0 );        
			}

		stbi_image_free( img );
		
		create_path( dirname( output_file ).c_str() );
		file_save_data( storage, sizeof( storage ), output_file.c_str(), FILE_MODE_BINARY );		
		}

	return result;
	}


compilation_result compiler_pixie_bitmap_single( compile_context const* context )
	{		
	compilation_result result = { 0 };

	string format;
	string palette;
	string dither;
	for( int i = 0; i < context->parameters.count(); ++i )
		{
		string_id name( context->parameters[ i ].name );
		string value( context->parameters[ i ].value );
		str_switch( name )
			{
			str_case( "format" )
				{
				format = value;
				}
			str_case( "palette" )
				{
				palette = value;
				}
			str_case( "dither" )
				{
				dither = value;
				}
			}
		}
	
	string input_file = path_join( context->input_root, context->path, context->input );

	string output_file = path_join( context->output_root, context->path, basename( context->input ) ) + ".pix";
	if( !file_exists( output_file.c_str() ) || file_more_recent( input_file.c_str(), output_file.c_str() ) )
		{
		string palette_file = path_join( context->build_root, dirname( palette ), basename( palette ) ) + ".plut";
		string palette_input = path_join( context->input_root, palette );
		if( !file_exists( palette_file.c_str() ) || file_more_recent( palette_input.c_str(), palette_file.c_str() ) )
			{
			logf( palette + "\n" );
			build_palette_lookup( palette_input, palette_file );
			}

		logf( path_join( context->path, context->input ) + "\n" );
		
		file_t* file = file_load( palette_file.c_str(), FILE_MODE_BINARY, 0 );
		if( !file ) { return result; /* TODO: error handling */}
		paldither_palette_t* pal = paldither_palette_create_from_data( file->data, file->size, 0 );
		file_destroy( file );
		
		int w, h, c;
		stbi_uc* img = stbi_load( input_file.c_str(), &w, &h, &c, 4 );
		
		char const header[] = "PIXIE_PIX";
		int version = 1;
		size_t size = 5 * sizeof ( int ) + 2 * w * h + sizeof( header ) + sizeof( version ) + 4 * sizeof( int );
		u8* output = (u8*) malloc( size );
		memcpy( output, header, sizeof( header ) );
		memcpy( output + sizeof( header ), &version, sizeof( version ) );
		
		int* offset_and_pitch = (int*)( output + sizeof( header ) + sizeof( version ) + 5 * sizeof ( int ) );
		
		paldither_type_t dither_type = PALDITHER_TYPE_DEFAULT;
		if( dither == "none" )
			dither_type = PALDITHER_TYPE_NONE;
		else if( dither == "bayer" )
			dither_type = PALDITHER_TYPE_BAYER;

		u8* pixels = output + sizeof( header ) + sizeof( version ) + 5 * sizeof ( int ) + 4 * sizeof( int ) ;
		if( dither == "remap" )
			palettize_remap_xbgr32( (PALDITHER_U32*)img, w, h, pal->colortable, pal->color_count, pixels );	
		else
		    paldither_palettize( (PALDITHER_U32*)img, w, h, pal, dither_type, pixels );	

		u8* mask = pixels + w * h;
		bool is_masked = false; 
		int x_min = w;
		int x_max = -1;
		int y_min = h;
		int y_max = -1;
		for( int y = 0; y < h; ++y ) 
			{
			for( int x = 0; x < w; ++x ) 
				{
				u8 m = (u8)( ( ((u32*) img)[ x + w * y ] ) >> 24 );
				mask[ x + w * y ] = m;
				is_masked |= m < 0xff;			
				if( m )
					{
					x_min = x < x_min ? x : x_min;
					y_min = y < y_min ? y : y_min;
					x_max = x > x_max ? x : x_max;
					y_max = y > y_max ? y : y_max;
					}
				}
			}
		stbi_image_free( img );
		int offset_x = x_min;
		int offset_y = y_min;
		int pitch_x = x_max - x_min + 1;
		int pitch_y = y_max - y_min + 1;
		if( x_max < x_min || y_max < y_min )
			{
			offset_x = 0;
			offset_y = 0;
			pitch_x = 0;
			pitch_y = 0;
			}

		if( pitch_x < w || pitch_y < h )
			{
			size -= 2 * w * h;
			size += pitch_x * pitch_y;

			for( int y = 0; y < pitch_y; ++y ) 
				for( int x = 0; x < pitch_x; ++x ) 
					pixels[ x + pitch_x * y ] = pixels[ ( x + offset_x ) + ( y + offset_y ) * w ];

			if( is_masked ) 
				{
				size += pitch_x * pitch_y;
				u8* mask_target = pixels + pitch_x * pitch_y;
				for( int y = 0; y < pitch_y; ++y ) 
					for( int x = 0; x < pitch_x; ++x ) 
						mask_target[ x + pitch_x * y ] = mask[ ( x + offset_x ) + ( y + offset_y ) * w ];
				}
			}
		else if( !is_masked ) size -= w * h;

			
		offset_and_pitch[ 0 ] = offset_x;
		offset_and_pitch[ 1 ] = offset_y;
		offset_and_pitch[ 2 ] = pitch_x;
		offset_and_pitch[ 3 ] = pitch_y;

		int* info = (int*)( output + sizeof( header ) + sizeof( version ) );
		info[ 0 ] = 0; // raw
		info[ 1 ] = w;
		info[ 2 ] = h;
		info[ 3 ] = 1; // cel_count
		info[ 4 ] = is_masked ? 1 : 0;
		
		create_path( path_join( context->output_root, context->path ).c_str() );
		file_save_data( output, size, output_file.c_str(), FILE_MODE_BINARY );
		free( output );
		paldither_palette_destroy( pal );		
		}
	return result;
	}


compilation_result compiler_pixie_bitmap_strip( compile_context const* context )
	{		
	array<string> inputs;

	compilation_result result = { 0 };
	string ext = extname( context->input );
	char const* underscore = strrchr( basename( context->input ).c_str(), '_' );	
	string stripped_name( basename( context->input ).c_str(), underscore + 1 );
	
	dir_t* dir = dir_open( path_join( context->input_root, context->path ).c_str() );
	assert( dir );
	dir_entry_t* ent = dir_read( dir );

	while( ent )
		{
		if( dir_is_file( ent ) )
			{
			if( (int)strlen( dir_name( ent ) ) == len( context->input ) && left( string( dir_name( ent ) ), len( stripped_name ) ) == stripped_name )
				{
				inputs.add( dir_name( ent ) );
				}
			}
		ent = dir_read( dir );
		}
	dir_close( dir );

	pixie_build::sort( &inputs );

	for( int i = 0; i < inputs.count(); ++i )
		{
		compile_context single_context = *context;
		single_context.output_root = single_context.build_root;
		single_context.input = inputs[ i ];
		compiler_pixie_bitmap_single( &single_context );
		}	
		
	string output_file = path_join( context->output_root, context->path, left( stripped_name, len( stripped_name ) -1 ) ) + ".pix";	
	bool need_to_build = !file_exists( output_file.c_str() );
	if( !need_to_build )
		{
		for( int i = 0; i < inputs.count(); ++i )
			{
			string build_file = path_join( context->build_root, context->path, basename( context->input ) ) + ".pix";	
			if( file_more_recent( build_file.c_str(), output_file.c_str() ) )
				{
				need_to_build = true;
				break;
				}
			}
		}
		
	if( need_to_build )
		{
		array<pixie_build::ref<pixie_build::binary> > files;
		for( int i = 0; i < inputs.count(); ++i )
			{
			string build_file = path_join( context->build_root, context->path, basename( inputs[ i ] ) ) + ".pix";	
			pixie_build::ref<pixie_build::binary> file = pixie_build::bload( build_file );
			// TODO: error handling, file == 0, size == 0
			files.add( file );
			}
		
	

		char const header[] = "PIXIE_PIX";
		int version = 1;
		int w = -1;
		int h = -1;
		int is_masked = -1;
		for( int i = 0; i < files.count(); ++i )
			{
			u8* data = (u8*)files[ i ]->data;
			int* info = (int*)( data + sizeof( header ) + sizeof( version ) );
			if( w >= 0 && w != info[ 1 ] ) (void)w; // TODO: error handling
			if( h >= 0 && h != info[ 2 ] ) (void)h; // TODO: error handling
			if( is_masked >= 0 && is_masked != info[ 4 ] ) (void)is_masked; // TODO: error handling
			w = info[ 1 ];
			h = info[ 2 ];
			is_masked = info[ 4 ];
			}
		assert( w > 0 && h > 0 && is_masked >= 0 );

		size_t alloc_size = 5 * sizeof ( int ) + sizeof( header ) + sizeof( version ) + ( w * h * ( is_masked ? 2 : 1 ) + sizeof( int ) * 4 ) * files.count();
		u8* output = (u8*) malloc( alloc_size );
		memcpy( output, header, sizeof( header ) );
		memcpy( output + sizeof( header ), &version, sizeof( version ) );
		int* info = (int*)( output + sizeof( header ) + sizeof( version ) );
		info[ 0 ] = 0; // raw
		info[ 1 ] = w;
		info[ 2 ] = h;
		info[ 3 ] = files.count(); // cel_count
		info[ 4 ] = is_masked;
				
		size_t size = 5 * sizeof ( int ) + sizeof( header ) + sizeof( version ) + sizeof( int ) * 4 * files.count();
		u8* data = (u8*)( info + 5 );
		for( int i = 0; i < files.count(); ++i )
			{
			u8* src = (u8*)files[ i ]->data;
			src += 5 * sizeof ( int ) + sizeof( header ) + sizeof( version );
			memcpy( data, src, sizeof( int ) * 4 ); data += sizeof( int ) * 4; size += sizeof( int ) * 4;
			src += sizeof( int );
			src += sizeof( int );
			int pitch_x = *(int*) src; src += sizeof( int );
			int pitch_y = *(int*) src; src += sizeof( int );
			memcpy( data, src, (size_t) pitch_x * pitch_y * ( is_masked ? 2 : 1 ) );
			data += pitch_x * pitch_y * ( is_masked ? 2 : 1 );
			size += pitch_x * pitch_y * ( is_masked ? 2 : 1 );
			}
		create_path( path_join( context->output_root, context->path ).c_str() );
		file_save_data( output, size, output_file.c_str(), FILE_MODE_BINARY );
		free( output );
		}
	
	return result;
	}
	
	
compilation_result compiler_pixie_bitmap( compile_context const* context )
	{
	string name = basename( context->input );
	int digit_count = 0;
	char const* underscore = strrchr( name.c_str(), '_' );	
	string stripped_name( name.c_str(), underscore );
	if( underscore )
		{	
		++underscore;
		while( *underscore )
			{
			if( *underscore >= '0' && *underscore <= '9' )
				{
				++digit_count;
				}
			else
				{
				digit_count = -1;
				break;
				}
				
			++underscore;
			}
		}

	if( digit_count > 1 )
		{
		
		int frame_num = integer( mid( name, len( stripped_name ) + 1 ) );
		bool is_first = true;
		dir_t* dir = dir_open( path_join( context->input_root, context->path ).c_str() );
		assert( dir );
		dir_entry_t* ent = dir_read( dir );
		while( ent )
			{
			if( dir_is_file( ent ) )
				{
				if( left( string( dir_name( ent ) ), len( stripped_name ) + 1 ) == stripped_name + "_" )
					{
					int number = integer( mid( string( dir_name( ent ) ), len ( stripped_name ) + 1 ) );
					if( number < frame_num ) 
						{
						is_first = false;
						break;
						}
					}
				}
			ent = dir_read( dir );
			}
		dir_close( dir );

		// if not the first image of the strip, just silently skip it (as this file will be built when the first image of the strip is built)
		if( !is_first )
			{
			compilation_result result = { 0 };
			return result;
			}

		// there needs to be at least two images in sequence for it to count as a strip		
		string next_frame = str( frame_num + 1 );
		while( len( next_frame ) < digit_count ) next_frame = "0" + next_frame;
		next_frame = stripped_name + "_" + next_frame;
		next_frame = path_join( context->input_root, context->path, next_frame ) + extname( context->input );
		if( file_exists( next_frame.c_str() ) )
			return compiler_pixie_bitmap_strip( context );		
		}
	
	return compiler_pixie_bitmap_single( context );		
	}
	

int build( build_action action, char const* input_path, char const* build_path, char const* output_path, compiler_list* compilers, int compilers_count )
	{
	(void) action, input_path, build_path, output_path, compilers, compilers_count;

	static thread_atomic_int_t init_count; 
	if( thread_atomic_int_inc( &init_count ) == 0 ) pixie_build::internal::internals_tls = thread_tls_create();

	u8* internals_storage = (u8*) malloc( sizeof( pixie_build::internal::internals_t ) );
	memset( internals_storage, 0, sizeof( pixie_build::internal::internals_t ) );
	thread_tls_set( pixie_build::internal::internals_tls, internals_storage );
	pixie_build::internal::internals_t* internals = new (internals_storage) pixie_build::internal::internals_t();

	int retval = 0;
	
	{
	
	if( compilers == 0 || compilers_count <= 0 )
		{
		compilers = default_compilers;
		compilers_count = sizeof( default_compilers ) / sizeof( *default_compilers );		
		}
	
	string input( input_path );
	string builddir( build_path );
	string output( output_path );
	if( right( input, 1 ) == "/" || right( input, 1 ) == "\\" ) input = left( input, len( input ) -1 );
	if( right( builddir, 1 ) == "/" || right( builddir, 1 ) == "\\" ) input = left( builddir, len( input ) -1 );
	if( right( output, 1 ) == "/" || right( output, 1 ) == "\\" ) output = left( output, len( output ) -1 );
	
	internals->log = log_create( path_join( builddir, "build.log" ).c_str(), 0 );
	
	build_t build;
	build.root_input = input;
	build.root_build = builddir;
	build.root_output = output;
	build.compilers = compilers;
	build.compilers_count = compilers_count;
		
	if( action == BUILD_ACTION_CLEAN || action == BUILD_ACTION_REBUILD )
		{
		assert( !"Not implemented yet." ); // TODO: implement clean
		}

	if( action == BUILD_ACTION_BUILD || action == BUILD_ACTION_REBUILD )
		{
		config cfg;
		compile_counts counts = build_dir( &build, cfg, input, builddir, output );
		retval = ( counts.failed > 0 ? -1 : 0 );
		}
		
	log_destroy( internals->log );
	free( internals->log_buffer );
	}

	internals->~internals_t();
	thread_tls_set( pixie_build::internal::internals_tls, 0 );
	free( internals_storage );
	if( thread_atomic_int_dec( &init_count ) == 1 )thread_tls_destroy( pixie_build::internal::internals_tls );

	return retval;
	}




} /* namespace pixie_build */


int pixie_build::abs( int x )
	{
	return x < 0 ? -x : x;
	}


int pixie_build::min( int x, int y )
	{
	return x < y ? x : y;
	}


int pixie_build::max( int x, int y )
	{
	return x > y ? x : y;
	}


#undef clamp
int pixie_build::clamp( int x, int min_val, int max_val )
	{
	return x > max_val ? max_val : x < min_val ? min_val : x;
	}




#undef final
#undef override
#undef STATIC_ASSERT

#define ARRAY_IMPLEMENTATION
#include "array.hpp"

#define DIR_IMPLEMENTATION
#define DIR_WINDOWS
#include "dir.h"

#define FILE_IMPLEMENTATION
#include "file.h"

#define FILE_UTIL_IMPLEMENTATION
#include "file_util.h"

#define INI_IMPLEMENTATION
#include "ini.h"

#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"

#define LOG_IMPLEMENTATION
#include "log.h"

#define MATH_UTIL_IMPLEMENTATION
#include "math_util.hpp"

#define PALDITHER_IMPLEMENTATION
#include "paldither.h"

#define PALETTIZE_IMPLEMENTATION
#include "palettize.h"

#define RND_IMPLEMENTATION
#include "rnd.h"

#define STRPOOL_IMPLEMENTATION
#include "strpool.h"

#define STRPOOL_HPP_IMPLEMENTATION
#include "strpool.hpp"

#define STRPOOL_UTIL_IMPLEMENTATION
#include "strpool_util.hpp"

#define THREAD_IMPLEMENTATION
#include "thread.h"

#define VECMATH_IMPLEMENTATION
#include "vecmath.hpp"


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

#define STB_IMAGE_IMPLEMENTATION
#pragma push_macro("L")
#undef L
#include "stb_image.h"
#pragma pop_macro("L")
#undef STB_IMAGE_IMPLEMENTATION

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#undef STB_PERLIN_IMPLEMENTATION

#pragma warning( pop )

#endif // PIXIE_BUILD_IMPLEMENTATION


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
