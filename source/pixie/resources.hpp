/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

resources.hpp - v0.1 - Efficient refcounted resource management for C++.

Do this:
	#define RESOURCES_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.

Dependencies: 
    hashtable.h
*/

#ifndef resources_hpp
#define resources_hpp

namespace resources { 

#ifndef RESOURCES_U64
    typedef unsigned long long RESOURCES_U64;
#endif

namespace internal { struct system_t; }

struct resource_system
	{
	resource_system( void* memctx = 0 );
	~resource_system();

	private:
		template< typename T > friend struct resource;
		internal::system_t* internals_;			
	};
	

typedef void const* type_id_t;
namespace internal {  template< typename T > struct type_id_helper { static int* id() { static int t; return &t; }; }; }
template< typename T > type_id_t type_id() { return (type_id_t) &internal::type_id_helper<T>::id; }
template< typename T > type_id_t type_id( T const& ) { return (type_id_t) &internal::type_id_helper<T>::id; }

struct resource_key
	{
	RESOURCES_U64 handle;
	void (*destroy)( void* );
	void* instance;
	};


template< typename T > struct resource
	{
	resource( resource_system* system );
	~resource();

	template< typename P0 > 
	resource( resource_system* system, P0 const& p0 );
	
	template< typename P0, typename P1 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1 );
	
	template< typename P0, typename P1, typename P2 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2 );
	
	template< typename P0, typename P1, typename P2, typename P3 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8 );
	
	template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
	resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9 );

	resource( resource const& other );
	resource const& operator=( resource const& other );

	operator T*() const;
	T* operator->() const;
	
	bool empty() const { return !instance_; }
	
	struct list
		{
		int count;
		T** items;
		};
	static list resource_list();
			
	private:
		resource_system* system_;
		T* instance_;
		int handle_;
		int type_;
	};

} /* namespace resources */


#endif /* resources_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef resources_impl 
#define resources_impl 

#ifndef RESOURCES_ASSERT
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <assert.h>
    #define RESOURCES_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

namespace resources { namespace internal {


typedef void* (*create_func_t)( char const* filename );
typedef void (*destroy_func_t)( resource_key* key, void* instance );

void** get_resource_list( system_t* system, type_id_t type, int* count );
		
struct info_t
	{
	void** instance;
	int handle;
	int type;
	};
info_t inject( system_t* system, type_id_t type, resource_key const* key, destroy_func_t destroy );
void* get_instance( system_t* system, int type, int handle );
int inc_ref( system_t* system, int type, int handle );
int dec_ref( system_t* system, int type, int handle );

template< typename T > void destroy_template( resource_key* key, void* const instance ) 
	{ 
	resources::resource_destroy( key, (T*) instance ); 
	}

} /* namespace internal */ } /* namespace resources */



namespace resources { 

template< typename T > resource_key make_key( T*, char const* filename )
	{
	(void) filename; 
	RESOURCES_ASSERT( false, "Not implemented yet." ); // TODO: implement default make_key (string pool)
	return resource_key();
	}


template< typename T > resource<T>::resource( resource_system* system ):
	system_( system ), instance_( 0 ), handle_( 0 ), type_( 0 )
	{
	}


template< typename T > template< typename P0 > 
resource<T>::resource( resource_system* system, P0 const& p0 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}


template< typename T > template< typename P0, typename P1 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4, p5 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4, p5 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4, p5, p6 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4, p5, p6 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4, p5, p6, p7 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4, p5, p6, p7 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4, p5, p6, p7, p8 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4, p5, p6, p7, p8 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > template< typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
resource<T>::resource( resource_system* system, P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9 ):
	system_( system )
	{
	resource_key key = make_key( (T*)0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );

	internal::info_t info = internal::inject( system_->internals_, type_id<T>(), &key, (internal::destroy_func_t) internal::destroy_template<T> );
	if( *info.instance == 0 ) resources::resource_create( (T**)info.instance, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
		
	instance_ = (T*) *info.instance;
	handle_ = info.handle;
	type_ = info.type;
	internal::inc_ref( system_->internals_, type_, handle_ );
	}
	

template< typename T > resource<T>::resource( resource const& other ):
	system_( other.system_ ),
	instance_( other.instance_ ),
	handle_( other.handle_ ), 
	type_( other.type_ )
	{
	internal::inc_ref( system_->internals_, type_, handle_ );
	}


template< typename T > resource<T>::~resource() 
	{ 
	internal::dec_ref( system_->internals_, type_, handle_ ); 
	}


template< typename T > resource<T> const& resource<T>::operator=( resource const& other )
	{
	if( other.handle_ != handle_ )
		{
		internal::dec_ref( system_->internals_, type_, handle_ );
		system_ = other.system_;
		instance_ = other.instance_;
		handle_ = other.handle_;
		type_ = other.type_;
		internal::inc_ref( system_->internals_, type_, handle_ );
		}
	return *this;
	}


template< typename T > resource<T>::operator T*() const
	{
	return instance_;
	}


template< typename T > T* resource<T>::operator->() const
	{
	RESOURCES_ASSERT( instance_, "Invalid instance" );
	return instance_;
	}


template< typename T > typename resource<T>::list resource<T>::resource_list()
	{
	list list;
	list.count = 0;
	list.items = (T**) internal::get_resource_list( system_, type_id<T>(), &list.count );	
	return list;
	}


} /* namespace resources */

#endif /* resources_impl */


#ifdef RESOURCES_IMPLEMENTATION
#undef RESOURCES_IMPLEMENTATION

#include "hashtable.h"
#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <string.h>	

#ifndef RESOURCES_U32
    #define RESOURCES_U32 unsigned int
#endif

#ifndef RESOURCES_MALLOC
	#include <stdlib.h>
	#define RESOURCES_MALLOC( ctx, size ) ( ::malloc( size ) )
	#define RESOURCES_FREE( ctx, ptr ) ( ::free( ptr ) )
#endif

namespace resources { namespace internal {

struct list_t
	{
	type_id_t type;

	struct info_t
		{
		resource_key key;
		destroy_func_t destroy;
		int ref_count;
		int handle;
		};

	info_t* info;
	void** instances;
	int count;
	int capacity;

	hashtable_t lookup;
	};

struct system_t
	{
	void* memctx;
	
	list_t* lists;
	int list_count;
	int list_capacity;

	int* handles;
	int handle_count;
	int handle_capacity;

	int handles_freelist;
	};


static void initialize( system_t* system, void* memctx )
	{
	system->memctx = memctx;
	system->list_count = 0;
	system->list_capacity = 16;
	system->handle_count = 0;
	system->handle_capacity = 256;
	system->handles_freelist = -1;

	system->lists = (list_t*) RESOURCES_MALLOC( system->memctx, system->list_capacity * sizeof( *system->lists ) );
	RESOURCES_ASSERT( system->lists, "Allocation failed" );

	system->handles = (int*) RESOURCES_MALLOC( system->memctx, system->handle_capacity * sizeof( *system->handles ) );
	RESOURCES_ASSERT( system->handles, "Allocation failed" );
	}


static void terminate( system_t* system )
	{
	RESOURCES_FREE( system->memctx, system->handles );

	for( int i = 0; i < system->list_count; ++i )
		{
		list_t& list = system->lists[ i ];
		for( int j = 0; j < list.count; ++j )
			{
			list.info[ j ].destroy( &list.info[ j ].key, list.instances[ j ] );
			if( list.info[ j ].key.destroy ) list.info[ j ].key.destroy( list.info[ j ].key.instance );
			}
		RESOURCES_FREE( system->memctx, list.info );
		RESOURCES_FREE( system->memctx, list.instances );
		hashtable_term( &list.lookup );
		}

	RESOURCES_FREE( system->memctx, system->lists );
	}


void** get_resource_list( system_t* system, type_id_t const type, int* count ) 
	{
	for( int i = 0; i < system->list_count; ++i )
		{
		list_t& current_list = system->lists[ i ];
		if( current_list.type == type )
			{
			*count = current_list.count;
			return current_list.instances;
			}
		}

	return 0;
	}


HASHTABLE_U64 murmur_hash_64( const void * key, size_t len, HASHTABLE_U64 seed )
	{
	const HASHTABLE_U64 m = 0xc6a4a7935bd1e995ULL;
	const int r = 47;

	HASHTABLE_U64 h = seed ^ (len * m);

	const HASHTABLE_U64 * data = (const HASHTABLE_U64 *)key;
	const HASHTABLE_U64 * end = data + (len/8);

	while( data != end )
		{
		#ifdef PLATFORM_BIG_ENDIAN
			HASHTABLE_U64 k = *data++;
			char *p = (char *)&k;
			char c;
			c = p[0]; p[0] = p[7]; p[7] = c;
			c = p[1]; p[1] = p[6]; p[6] = c;
			c = p[2]; p[2] = p[5]; p[5] = c;
			c = p[3]; p[3] = p[4]; p[4] = c;
		#else
			HASHTABLE_U64 k = *data++;
		#endif

		k *= m;
		k ^= k >> r;
		k *= m;
		
		h ^= k;
		h *= m;
		}

	const unsigned char * data2 = (const unsigned char*)data;

	switch( len & 7 )
		{
		case 7: h ^= HASHTABLE_U64(data2[6]) << 48;
		case 6: h ^= HASHTABLE_U64(data2[5]) << 40;
		case 5: h ^= HASHTABLE_U64(data2[4]) << 32;
		case 4: h ^= HASHTABLE_U64(data2[3]) << 24;
		case 3: h ^= HASHTABLE_U64(data2[2]) << 16;
		case 2: h ^= HASHTABLE_U64(data2[1]) << 8;
		case 1: h ^= HASHTABLE_U64(data2[0]);
				h *= m;
		};
 
	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
	}


info_t inject( system_t* system, type_id_t type, resource_key const* key, destroy_func_t destroy )
	{
	// find the list for this resource type
	list_t* list = 0;
	int list_index = -1;
	for( int i = 0; i < system->list_count; ++i )
		{
		list_t* current_list = &system->lists[ i ];
		if( current_list->type == type )
			{
			list = current_list;
			list_index = i;
			break;
			}
		}

	// if there is not already a list, create it and supporting data structures
	if( !list )
		{
		if( system->list_count >= system->list_capacity )
			{
			system->list_capacity *= 2;
			list_t* new_list = (list_t*) RESOURCES_MALLOC( system->memctx, system->list_capacity * sizeof( *system->lists ) );
			RESOURCES_ASSERT( new_list, "Allocation failed" );
            memcpy( new_list, system->lists, system->list_count * sizeof( *system->lists ) );
            RESOURCES_FREE( system->memctx, system->lists );
			system->lists = new_list;
			}
	
		list_index = system->list_count++;
		list_t* current_list = &system->lists[ list_index ];
		current_list->type = type;
		current_list->count = 0;
		current_list->capacity = 256;
		current_list->instances = (void**) RESOURCES_MALLOC( system->memctx, current_list->capacity * sizeof( *current_list->instances ) );
		RESOURCES_ASSERT( current_list->instances, "Allocation failed" );
		current_list->info = (list_t::info_t*) RESOURCES_MALLOC( system->memctx, current_list->capacity * sizeof( *current_list->info ) );
		RESOURCES_ASSERT( current_list->info, "Allocation failed" );
		hashtable_init( &current_list->lookup, sizeof( int ), current_list->capacity, system->memctx );
		list = current_list;
		}

	// unless the key is an "anonymous" key (handle is 0), return existing resource if it exists
	if( key->handle != 0 )
		{
		int* item_index = (int*) hashtable_find( &list->lookup, key->handle );
		if( item_index )
			{
			info_t ret;
			ret.instance = &list->instances[ *item_index ];
			ret.handle = list->info[ *item_index ].handle + 1;
			ret.type = list_index;
			return ret;
			}
		}
		
	// resource does not exist, so create it

	// acquire a handle for the new resource
	int handle = system->handles_freelist;
	if( handle == -1 )
		{
		// no handle left in freelist, allocate a new one (resizing storage if necessary)
		if( system->handle_count >= system->handle_capacity )
			{
			system->handle_capacity *= 2;
            int* new_handles = (int*) RESOURCES_MALLOC( system->memctx, system->handle_capacity * sizeof( *system->handles ) );
			RESOURCES_ASSERT( new_handles, "Allocation failed" );
            memcpy( new_handles, system->handles, system->handle_count * sizeof( *system->handles ) );
			RESOURCES_FREE( system->memctx, system->handles );
            system->handles = new_handles;
			}
		
		handle = system->handle_count++;
		}
	else
		{
		// reuse handle from freelist
		handle = system->handles_freelist;
		system->handles_freelist = system->handles[ system->handles_freelist ];
		}

	// allocate storage for new resource, if necessary
	if( list->count >= list->capacity )
		{
		list->capacity *= 2;
        
        void** new_instances = (void**) RESOURCES_MALLOC( system->memctx, list->capacity * sizeof( *list->instances ) );
		RESOURCES_ASSERT( new_instances, "Allocation failed" );
        memcpy( new_instances, list->instances, list->count * sizeof( *list->instances ) );
		RESOURCES_FREE( system->memctx, list->instances );
        list->instances = new_instances;

		list_t::info_t* new_info = (list_t::info_t*) RESOURCES_MALLOC( system->memctx,list->capacity * sizeof( *list->info ) );
		RESOURCES_ASSERT( new_info, "Allocation failed" );
        memcpy( new_info, list->info, list->count * sizeof( *list->info ) );
		RESOURCES_FREE( system->memctx, list->info );        
		list->info = new_info;
		}

	// allocate the new resource
	int const index = list->count++;
	list->instances[ index ] = 0; // the instance pointer is set to 0 to signal to the caller that resource_create must be called
	system->handles[ handle ] = index; // point the handle to the correct index - will allow moving of list entries
	
	list_t::info_t& info = list->info[ index ];
	info.key = *key;
	info.destroy = destroy;
	info.ref_count = 0;
	info.handle = handle;

	// unless the key is an "anonymous" key (handle is 0), insert it into lookup table
	if( key->handle != 0 )
		hashtable_insert( &list->lookup, key->handle, (void*) &index ); // the local "index" variable will be copied by hashtable_insert

	info_t ret;
	ret.instance = &list->instances[ index ];
	ret.handle = handle + 1;
	ret.type = list_index;
	return ret;
	}


void* get_instance( system_t* system, int const type, int const handle )
	{
	if( handle == 0 ) return 0;
	RESOURCES_ASSERT( handle - 1 >= 0 && handle - 1 < system->handle_count, "Invalid handle" );

	int const index = system->handles[ handle - 1 ];
	RESOURCES_ASSERT( type >= 0 && type < system->list_count, "Invalid type" );
	RESOURCES_ASSERT( index >= 0 && index < system->lists[ type ].count, "Invalid index" );

	return system->lists[ type ].instances[ index ];
	}


int inc_ref( system_t* system, int const type, int const handle )
	{
	if( handle == 0 ) return 0;
	RESOURCES_ASSERT( handle - 1 >= 0 && handle - 1 < system->handle_count, "Invalid handle" );

	int const index = system->handles[ handle - 1 ];
	RESOURCES_ASSERT( type >= 0 && type < system->list_count, "Invalid type" );
	RESOURCES_ASSERT( index >= 0 && index < system->lists[ type ].count, "Invalid index" );

	return ++system->lists[ type ].info[ index ].ref_count;
	}


int dec_ref( system_t* system, int const type, int const handle )
	{
	if( handle == 0 ) return 0;
	RESOURCES_ASSERT( handle - 1 >= 0 && handle - 1 < system->handle_count, "Invalid handle" );

	int const index = system->handles[ handle - 1 ];
	RESOURCES_ASSERT( type >= 0 && type < system->list_count, "Invalid type" );
	list_t& list = system->lists[ type ];
	RESOURCES_ASSERT( index >= 0 && index < list.count, "Invalid index" );

	int& ref_count = list.info[ index ].ref_count;
	RESOURCES_ASSERT( ref_count > 0, "Invalid ref count" );
	--ref_count;
	if( ref_count <= 0 )
		{
		// remove item by swapping in last item
		
		// destroy instances (key and resource)
		if( list.info[ index ].destroy && list.instances[ index ] ) 
			list.info[ index ].destroy( &list.info[ index ].key, list.instances[ index ] );
		if( list.info[ index ].key.destroy && list.info[ index ].key.instance ) 
			list.info[ index ].key.destroy( list.info[ index ].key.instance );

		// unless the key is an "anonymous" key (handle is 0), remove it from lookup table
		resource_key* key = &list.info[ index ].key;
		if( key->handle != 0 )
			hashtable_remove( &list.lookup, key->handle );
			
		// update lookup table for last item (to be swapped)
		resource_key* last_key = &list.info[ list.count - 1 ].key;
		if( last_key->handle != 0 )
			{
			int* last_index = (int*)hashtable_find( &list.lookup, last_key->handle );
			if( last_index ) *last_index = index; // now points to the element we are about to remove
			}

		// store the handle of the items being swapped
		int removed_handle = list.info[ index ].handle;
		int swapped_handle = list.info[ list.count - 1 ].handle;

		// swap items, replacing the element we are removing with the last element
		list.info[ index ] = list.info[ list.count - 1 ];
		list.instances[ index ] = list.instances[ list.count - 1 ];
		--list.count;

		// update the handle for the swapped item
		system->handles[ swapped_handle ] = index;

		// release the handle used by the removed item
		system->handles[ removed_handle ] = system->handles_freelist;
		system->handles_freelist = removed_handle;
		
		return 0;
		}

	return ref_count;
	}

} /* namespace internal */ } /* namespace resources */


namespace resources {


resource_system::resource_system( void* memctx )
	{
	internals_ = (internal::system_t*) RESOURCES_MALLOC( memctx, sizeof( internal::system_t ) );
	internal::initialize( internals_, memctx );
	}


resource_system::~resource_system()
	{
	internal::terminate( internals_ );
	RESOURCES_FREE( internals_->memctx, internals_ );
	}


} /* namespace resources */


#endif /*  RESOURCES_IMPLEMENTATION */

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
