/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

gamestate.hpp - v0.1 - Generic game state management for C++.

*/

#ifndef gamestate_hpp
#define gamestate_hpp

namespace gamestate {

namespace internal { struct system_t; }


enum transition
	{
	TRANSITION_NONE,
	TRANSITION_IN,
	TRANSITION_OUT,
	};


template< typename CTX = void > struct game_state_system
	{
	game_state_system( CTX* context, void* memctx = 0 );
	~game_state_system();

    // Leave all active gamestates, over trans_out seconds, and enter the specified gamestate STATE, over trans_in seconds.
	template< typename STATE > void set( float trans_out = 0.0f, float trans_in = 0.0f );

    // Enter the specified gamestate STATE, over trans_in seconds. Keep all currently active gamestates running.
	template< typename STATE > void push( float trans_in = 0.0f );

    // Leave the last activated gamestate, over trans_out seconds
	void pop( float trans_out = 0.0f, int count = 1 ); // count -1 to pop all

    // Gamestate consisting of init/term function pair.
	template< typename STATE > void add( void (*init)( CTX* ), void (*term)( CTX* ), void (*update)( CTX* ) = 0);

    // Gamestate consisting of init/term function pair and a custom user data pointer.
	template< typename STATE, typename T > void add( void (*init)( CTX*, T* ), void (*term)( CTX*, T* ), void (*update)( CTX*, T* ) = 0, T* user_data = 0 );

    // Gamestate consisting of a class to be dynamically instantiated (constructor/destructor does init and cleanup).
	template< typename STATE > void add();
	template< typename STATE, void (STATE::*UPDATE)( CTX* ) > void add();
	template< typename STATE, typename T > void add();
	template< typename STATE, typename T, void (T::*UPDATE)( CTX* ) > void add();

    // Gamestate consisting of a class instance, and init/term member functions
	template< typename STATE, void (STATE::*INIT)( CTX* ), void (STATE::*TERM)( CTX* ) > void add( STATE* instance );
	template< typename STATE, void (STATE::*INIT)( CTX* ), void (STATE::*TERM)( CTX* ), void (STATE::*UPDATE)( CTX* ) > void add( STATE* instance );
	template< typename STATE, typename T, void (T::*INIT)( CTX* ), void (T::*TERM)( CTX* ) > void add( T* instance );
	template< typename STATE, typename T, void (T::*INIT)( CTX* ), void (T::*TERM)( CTX* ), void (T::*UPDATE)( CTX* ) > void add( T* instance );

	template< typename STATE > void remove();


    // Manage transition timing and execute requested gamestate activation changes
	void update( float delta_time );
	
	transition transition_type() const;
	float transition_progress() const;

	private:
		internal::system_t system_;
	};


template<> struct game_state_system<void>
	{
	inline game_state_system( void* memctx = 0 );
	inline ~game_state_system();

    // Leave all active gamestates, over trans_out seconds, and enter the specified gamestate STATE, over trans_in seconds.
	template< typename STATE > void set( float trans_out = 0.0f, float trans_in = 0.0f );

    // Enter the specified gamestate STATE, over trans_in seconds. Keep all currently active gamestates running.
    template< typename STATE > void push( float trans_in = 0.0f );

    // Leave the last activated gamestate, over trans_out seconds
	inline void pop( float trans_out = 0.0f, int count = 1 );  // count -1 to pop all

    // Gamestate consisting of init/term function pair.
    template< typename STATE > void add( void (*init)(), void (*term)(), void (*update)() = 0 );

    // Gamestate consisting of init/term function pair and a custom user data pointer.
    template< typename STATE, typename T > void add( void (*init)( T* ), void (*term)( T* ), void (*update)( T* ) = 0, T* user_data = 0 );

    // Gamestate consisting of a class to be dynamically instantiated (constructor/destructor does init and cleanup).
	template< typename STATE > void add();
	template< typename STATE, void (STATE::*UPDATE)() > void add();
	template< typename STATE, typename T > void add();
	template< typename STATE, typename T, void (T::*UPDATE)() > void add();

    // Gamestate consisting of a class instance, and init/term member functions
	template< typename STATE, void (STATE::*INIT)(), void (STATE::*TERM)() > void add( STATE* instance );
	template< typename STATE, void (STATE::*INIT)(), void (STATE::*TERM)(), void (STATE::*UPDATE)() > void add( STATE* instance );
	template< typename STATE, typename T, void (T::*INIT)(), void (T::*TERM)() > void add( T* instance );
	template< typename STATE, typename T, void (T::*INIT)(), void (T::*TERM)(), void (T::*UPDATE)() > void add( T* instance );

    template< typename STATE > void remove();

    // Manage transition timing and execute requested gamestate activation changes
    inline void update( float delta_time );

	inline transition transition_type() const;
	inline float transition_progress() const;

    private:
		internal::system_t* system_;
        int storage_[ 20 ];
	};



} /* namespace gamestate */

#endif /* gamestate_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef gamestate_impl
#define gamestate_impl

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>

namespace gamestate { namespace internal {

void* gamestate_malloc( void* ctx, size_t size );
void gamestate_free( void* ctx, void* ptr );

typedef void const* type_id_t;
template< typename STATE > struct system_type_id_helper { static int* id() { static int t; return &t; }; };
template< typename STATE > type_id_t type_id() { return (type_id_t) &system_type_id_helper<STATE>::id; }
template< typename STATE > type_id_t type_id( STATE const& ) { return (type_id_t) &system_type_id_helper<STATE>::id; }

typedef void* (*init_func_t)( void*, void*, void*, void*, void* );
typedef void (*term_func_t)( void*, void*, void*, void*, void* );
typedef void (*update_func_t)( void*, void*, void*, void*, void* );

struct system_t
	{
	void* context;
    void* memctx;

    transition transition_type;
    float transition_progress;
    float transition_step;
    int pop_count;

	struct registered_state_t
		{
		type_id_t state_id;
		void* instance;
		init_func_t init;
		term_func_t term;
		update_func_t update;
		void* init_func;
		void* term_func;
		void* update_func;
		void* usr;
		};
	
	registered_state_t* registered_states;
	int registered_states_count;
	int registered_states_capacity;

	struct active_state_t
		{
		type_id_t state_id;
		registered_state_t* state;
		void* instance;
		};
	
	active_state_t* active_states_stack;
	int active_states_stack_count;
	int active_states_stack_capacity;

	struct queued_operation_t
		{
        int pop_count;
		type_id_t new_state_id;
		float transition_time;
		};

	queued_operation_t* queued_operations;
	int queued_operations_count;
	int queued_operations_capacity;
	};


void init( system_t* sys, void* context, void* memctx );
void term( system_t* sys );
void queue_switch( system_t* sys, type_id_t state_id, float trans_out, float trans_in );
void queue_push( system_t* sys, type_id_t state_id, float trans_in );
void queue_pop( system_t* sys, float trans_out, int count );

void reg( system_t* sys, type_id_t state_id, void* instance, init_func_t init, term_func_t term, update_func_t update, void* init_func, void* term_func, void* update_func, void* usr );
void unreg( system_t* sys, type_id_t state_id );

void update(system_t* sys, float delta_time );

transition transition_type( system_t const* sys );
float transition_progress( system_t const* sys );


template< typename CTX > 
void* init_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance; (void) user_data;
    ( (void (*)(CTX*)) func )( (CTX*) context ); 
    return 0;
    }


inline void* init_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance; (void) user_data;
    ( (void (*)()) func )(); 
    return 0;
    }


template< typename CTX > 
void term_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance; (void) user_data;
    ( (void (*)(CTX*)) func )( (CTX*) context ); 
    }


inline void term_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance; (void) user_data;
    ( (void (*)()) func )(); 
    }


template< typename CTX > 
void update_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance; (void) user_data;
    ( (void (*)(CTX*)) func )( (CTX*) context ); 
    }


inline void update_no_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance; (void) user_data;
    ( (void (*)()) func )(); 
    }


template< typename CTX, typename T > 
void* init_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance;
    ( (void (*)(CTX*, T*) ) func )( (CTX*) context, (T*) user_data ); 
    return 0;
    }


template< typename T > 
void* init_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance;
    ( (void (*)(T*) ) func )( (T*) user_data ); 
    return 0;
    }


template< typename CTX, typename T > 
void term_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance; 
    ( (void (*)(CTX*, T*)) func )( (CTX*) context, (T*) user_data ); 
    }


template< typename T > 
void term_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance; 
    ( (void (*)(T*)) func )( (T*) user_data ); 
    }


template< typename CTX, typename T > 
void update_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) instance; 
    ( (void (*)(CTX*, T*)) func )( (CTX*) context, (T*) user_data ); 
    }


template< typename T > 
void update_user_data( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) instance; 
    ( (void (*)(T*)) func )( (T*) user_data ); 
    }


template< typename CTX, typename STATE > 
void* init_new_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) instance; (void) func; (void) user_data;
    void* ptr = gamestate_malloc( memctx, sizeof( STATE ) ); 
    return (void*) new (ptr) STATE( (CTX*) context ); 
    }


template< typename STATE > 
void* init_new_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) instance; (void) context; (void) func; (void) user_data;
    void* ptr = gamestate_malloc( memctx, sizeof( STATE ) ); 
    return (void*) new (ptr) STATE(); 
    }


template< typename CTX, typename STATE > 
void term_delete_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) context; (void) instance; (void) func; (void) user_data;
    ( (STATE*)instance )->~STATE(); 
    gamestate_free( memctx, instance ); 
    }


template< typename CTX, typename STATE, void (STATE::*UPDATE)( CTX* ) > 
void update_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
	(void)memctx; (void) context; (void) instance; (void) func; (void) user_data;
    ( ( (STATE*)instance )->*UPDATE )( (CTX*) context ); 
    }


template< typename STATE, void (STATE::*UPDATE)() > 
void update_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void)memctx; (void) context; (void) instance; (void) func; (void) user_data;
    ( ( (STATE*)instance )->*UPDATE )(); 
    }


template< typename CTX, typename T, void (T::*INIT)( CTX* ) > 
void* init_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) func; (void) user_data;
    ( ( (T*) instance )->*INIT )( (CTX*) context ); 
    return instance; 
    }


template< typename T, void (T::*INIT)() > 
void* init_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) func; (void) user_data;
    ( ( (T*) instance )->*INIT )(); 
    return instance; 
    }


template< typename CTX, typename T, void (T::*TERM)( CTX* ) > 
void term_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) func; (void) user_data;
    ( ( (T*) instance )->*TERM )( (CTX*) context ); 
    }


template< typename T, void (T::*TERM)() > 
void term_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) func; (void) user_data;
    ( ( (T*) instance )->*TERM )(); 
    }

template< typename CTX, typename T, void (T::*UPDATE)( CTX* ) > 
void update_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) func; (void) user_data;
    ( ( (T*) instance )->*UPDATE)( (CTX*) context ); 
    }


template< typename T, void (T::*UPDATE)() > 
void update_existing_instance( void* memctx, void* context, void* instance, void* func, void* user_data ) 
    { 
    (void) memctx; (void) context; (void) func; (void) user_data;
    ( ( (T*) instance )->*UPDATE )(); 
    }

} /* namespace internal */ } /* gamestate */


namespace gamestate { 
    

template< typename CTX > 
game_state_system<CTX>::game_state_system( CTX* context, void* memctx )
	{
	internal::init( &system_, context, memctx );
	}


game_state_system<void>::game_state_system( void* memctx )
	{
	struct gamestate_static_assert 
		{ int system_storage_size : !!( ( sizeof( game_state_system<>::storage_ ) >= sizeof( internal::system_t ) ) ); };
    system_ = (internal::system_t*) storage_;
	internal::init( system_, 0, memctx );
	}


template< typename CTX > 
game_state_system<CTX>::~game_state_system()
	{
	internal::term( &system_ );
	}


game_state_system<void>::~game_state_system()
	{
	internal::term( system_ );
	}


template< typename CTX > template< typename STATE > 
void game_state_system<CTX>::set( float trans_out, float trans_in )
	{
	internal::queue_switch( &system_, internal::type_id<STATE>(), trans_out, trans_in );
	}

	
template< typename STATE > 
void game_state_system<void>::set( float trans_out, float trans_in )
	{
	internal::queue_switch( system_, internal::type_id<STATE>(), trans_out, trans_in );
	}

	
template< typename CTX > template< typename STATE > 
void game_state_system<CTX>::push( float trans_in )
	{
	internal::queue_push( &system_, internal::type_id<STATE>(), trans_in );
	}


template< typename STATE > 
void game_state_system<void>::push( float trans_in )
	{
	internal::queue_push( system_, internal::type_id<STATE>(), trans_in );
	}


template< typename CTX > 
void game_state_system<CTX>::pop( float trans_out, int count )
	{
    internal::queue_pop( &system_, trans_out, count < 0 ? ( system_.active_states_stack_count ) : ( count < 1 ? 1 : count ) );
	}


void game_state_system<void>::pop( float trans_out, int count )
	{
    internal::queue_pop( system_, trans_out, count < 0 ? ( system_->active_states_stack_count ) : ( count < 1 ? 1 : count )  );
	}




template< typename CTX > template< typename STATE > 
void game_state_system<CTX>::add( void (*init)( CTX* ), void (*term)( CTX* ), void (*update)( CTX* ) )
	{
    internal::reg( &system_, internal::type_id<STATE>(), 0, 
        internal::init_no_user_data<CTX>, internal::term_no_user_data<CTX>, internal::term_no_user_data<CTX>, internal::update_no_user_data<CTX>, init, term, update, 0);
	}


template< typename STATE > 
void game_state_system<void>::add( void (*init)(), void (*term)(), void (*update)() )
	{
    internal::reg( system_, internal::type_id<STATE>(), 0, 
        internal::init_no_user_data, internal::term_no_user_data, internal::update_no_user_data, init, term, update, 0);
	}


template< typename CTX > template< typename STATE, typename T > 
void game_state_system<CTX>::add( void (*init)( CTX*, T* ), void (*term)( CTX*, T* ), void (*update)( CTX*, T* ), T* usr )
	{
    internal::reg( &system_, internal::type_id<STATE>(), 0, 
        internal::init_user_data<CTX, T>, internal::term_user_data<CTX, T>, internal::update_user_data<CTX, T>, init, term, update, usr );
	}


template< typename STATE, typename T > 
void game_state_system<void>::add( void (*init)( T* ), void (*term)( T* ), void (*update)( T* ), T* usr )
	{
    internal::reg( system_, internal::type_id<STATE>(), 0, 
        internal::init_user_data<T>, internal::term_user_data<T>, internal::update_user_data<T>, init, term, update, usr );
	}


template< typename CTX > template< typename STATE > 
void game_state_system<CTX>::add()
	{
	internal::reg( &system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<CTX, STATE>, internal::term_delete_instance<CTX, STATE>, 0, 0, 0, 0, 0 );
	}


template< typename STATE > 
void game_state_system<void>::add()
	{
	internal::reg( system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<STATE>, internal::term_delete_instance<void,STATE>, 0, 0, 0, 0, 0 );
	}


template< typename CTX > template< typename STATE, void (STATE::*UPDATE)( CTX* ) > 
void game_state_system<CTX>::add()
	{
	internal::reg( &system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<CTX, STATE>, internal::term_delete_instance<CTX, STATE>, internal::update_instance<CTX, STATE, UPDATE>, 0, 0, 0, 0 );
	}


template< typename STATE, void (STATE::*UPDATE)() > 
void game_state_system<void>::add()
	{
	internal::reg( system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<STATE>, internal::term_delete_instance<void,STATE>, internal::update_instance<STATE, UPDATE>, 0, 0, 0, 0 );
	}


template< typename CTX > template< typename STATE, typename T, void (T::*UPDATE)( CTX* ) > 
void game_state_system<CTX>::add()
	{
	internal::reg( &system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<CTX, T>, internal::term_delete_instance<CTX, T>, internal::update_instance<CTX, T, UPDATE>, 0, 0, 0, 0 );
	}


template< typename STATE, typename T, void (T::*UPDATE)() > 
void game_state_system<void>::add()
	{
	internal::reg( system_, internal::type_id<STATE>(), 0, 
        internal::init_new_instance<T>, internal::term_delete_instance<void, T>, internal::update_instance<T, UPDATE>, 0, 0, 0, 0 );
	}


template< typename CTX > template< typename STATE, void (STATE::*INIT)( CTX* ), void (STATE::*TERM)( CTX* ) > 
void game_state_system<CTX>::add( STATE* instance )
	{
    internal::reg( &system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<CTX, STATE, INIT>, internal::term_existing_instance<CTX, STATE, TERM>, 0, 0, 0, 0, 0 );
    }


template< typename STATE, void (STATE::*INIT)(), void (STATE::*TERM)() > 
void game_state_system<void>::add( STATE* instance )
	{
    internal::reg( system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<STATE, INIT>, internal::term_existing_instance<STATE, TERM>, 0, 0, 0, 0, 0 );
    }


template< typename CTX > template< typename STATE, void (STATE::*INIT)( CTX* ), void (STATE::*TERM)( CTX* ), void (STATE::*UPDATE)( CTX* ) > 
void game_state_system<CTX>::add( STATE* instance )
	{
    internal::reg( &system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<CTX, STATE, INIT>, internal::term_existing_instance<CTX, STATE, TERM>, internal::update_existing_instance<CTX, STATE, UPDATE>, 0, 0, 0, 0 );
    }


template< typename STATE, void (STATE::*INIT)(), void (STATE::*TERM)(), void (STATE::*UPDATE)() > 
void game_state_system<void>::add( STATE* instance )
	{
    internal::reg( system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<STATE, INIT>, internal::term_existing_instance<STATE, TERM>, internal::update_existing_instance<STATE, UPDATE>, 0, 0, 0, 0 );
    }


template< typename CTX > template< typename STATE, typename T, void (T::*INIT)( CTX* ), void (T::*TERM)( CTX* ) > 
void game_state_system<CTX>::add( T* instance )
	{
    internal::reg( &system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<CTX, T, INIT>, internal::term_existing_instance<CTX, T, TERM>, 0, 0, 0, 0, 0 );
    }


template< typename STATE, typename T, void (T::*INIT)(), void (T::*TERM)() > 
void game_state_system<void>::add( T* instance )
	{
    internal::reg( system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<T, INIT>, internal::term_existing_instance<T, TERM>, 0, 0, 0, 0, 0 );
    }


template< typename CTX > template< typename STATE, typename T, void (T::*INIT)( CTX* ), void (T::*TERM)( CTX* ), void (T::*UPDATE)( CTX* ) > 
void game_state_system<CTX>::add( T* instance )
	{
    internal::reg( &system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<CTX, T, INIT>, internal::term_existing_instance<CTX, T, TERM>, internal::update_existing_instance<CTX, T, UPDATE>, 0, 0, 0, 0 );
    }


template< typename STATE, typename T, void (T::*INIT)(), void (T::*TERM)(), void (T::*UPDATE)() > 
void game_state_system<void>::add( T* instance )
	{
    internal::reg( system_, internal::type_id<STATE>(), instance, 
        internal::init_existing_instance<T, INIT>, internal::term_existing_instance<T, TERM>, internal::update_existing_instance<T, UPDATE>, 0, 0, 0, 0 );
    }






template< typename CTX > template< typename STATE > 
void game_state_system<CTX>::remove()
	{
    internal::unreg( &system_, internal::type_id<STATE>() );
	}


template< typename STATE > 
void game_state_system<void>::remove()
	{
    internal::unreg( system_, internal::type_id<STATE>() );
	}


template< typename CTX > 
void game_state_system<CTX>::update( float delta_time )
	{
	internal::update( &system_, delta_time );
	}


void game_state_system<void>::update( float delta_time )
	{
	internal::update( system_, delta_time );
	}


template< typename CTX > 
transition game_state_system<CTX>::transition_type() const
	{
	return internal::transition_type( &system_ );
	}
	

transition game_state_system<void>::transition_type() const
	{
	return internal::transition_type( system_ );
	}
	

template< typename CTX > 
float game_state_system<CTX>::transition_progress() const
	{
	return internal::transition_progress( &system_ );
	}


float game_state_system<void>::transition_progress() const
	{
	return internal::transition_progress( system_ );
	}


} /* gamestate */


#endif /* gamestate_impl */


#ifdef GAMESTATE_IMPLEMENTATION
#undef GAMESTATE_IMPLEMENTATION

#ifndef GAMESTATE_MALLOC
	#define _CRT_NONSTDC_NO_DEPRECATE 
	#define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define GAMESTATE_MALLOC( ctx, size ) ( malloc( size ) )
	#define GAMESTATE_FREE( ctx, ptr ) ( free( ptr ) )
#endif

#ifndef GAMESTATE_ASSERT
    #undef _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #undef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
    #include <assert.h>
    #define GAMESTATE_ASSERT( expression, message ) assert( ( expression ) && ( message ) )
#endif

namespace gamestate { namespace internal {


void* gamestate_malloc( void* ctx, size_t size )
    {
    (void) ctx;
    return GAMESTATE_MALLOC( ctx, size );
    }


void gamestate_free( void* ctx, void* ptr )
    {
    (void) ctx;
    return GAMESTATE_FREE( ctx, ptr );
    }


void init( system_t* sys, void* context, void* memctx )
	{
	sys->context = context;
    sys->memctx = memctx;

    sys->transition_type = TRANSITION_NONE;
    sys->transition_progress = 0.0f;
    sys->transition_step = 0.0f;
    sys->pop_count = 0;

    sys->registered_states_count = 0;
	sys->registered_states_capacity = 128;
	sys->registered_states = (system_t::registered_state_t*) GAMESTATE_MALLOC( sys->memctx, sys->registered_states_capacity * sizeof( *sys->registered_states ) );

	sys->active_states_stack_count = 0;
	sys->active_states_stack_capacity = 64;
	sys->active_states_stack = (system_t::active_state_t*) GAMESTATE_MALLOC( sys->memctx, sys->active_states_stack_capacity * sizeof( *sys->active_states_stack ) );

	sys->queued_operations_count = 0;
	sys->queued_operations_capacity = 64;
	sys->queued_operations = (system_t::queued_operation_t*) GAMESTATE_MALLOC( sys->memctx, sys->queued_operations_capacity * sizeof( *sys->queued_operations ) );
    }


void pop( system_t* sys );


void term( system_t* sys )
	{
	while( sys->active_states_stack_count > 0 ) 
		pop( sys );

	GAMESTATE_FREE( sys->memctx, sys->active_states_stack );
	GAMESTATE_FREE( sys->memctx, sys->queued_operations );
	GAMESTATE_FREE( sys->memctx, sys->registered_states );
	}


void reg( system_t* sys, type_id_t state_id, void* instance, init_func_t init, term_func_t term, update_func_t update, void* init_func, void* term_func, void* update_func, void* usr )
	{
	if( sys->registered_states_count >= sys->registered_states_capacity )
		{
		sys->registered_states_capacity *= 2;
        system_t::registered_state_t* new_states = (system_t::registered_state_t*) GAMESTATE_MALLOC( sys->memctx, sys->registered_states_capacity * sizeof( *sys->registered_states ) );
        memcpy( new_states, sys->registered_states, sys->registered_states_count * sizeof( *sys->registered_states ) );
        GAMESTATE_FREE( sys->memctx, sys->registered_states );
        sys->registered_states = new_states;
		}
	system_t::registered_state_t* state = &sys->registered_states[ sys->registered_states_count++ ];
	state->state_id = state_id;
	state->instance = instance;
	state->init = init;
	state->term = term;
	state->update = update;
	state->init_func = init_func;
	state->term_func = term_func;
	state->update_func = update_func;
	state->usr = usr;
	}


void unreg( system_t* sys, type_id_t state_id )
	{
    for( int i = 0; i < sys->registered_states_count; ++i )
        {
        if( sys->registered_states[ i ].state_id == state_id )
            {
            sys->registered_states[ i ] = sys->registered_states[ --sys->registered_states_count ];
            break;
            }
        }
	}


void* init_state( system_t* sys, type_id_t state_id, system_t::registered_state_t** ret_state )
	{
	for( int i = 0; i < sys->registered_states_count; ++i )
		{
		system_t::registered_state_t* state = &sys->registered_states[ i ];
		if( state->state_id == state_id )
			{
			*ret_state = state;
			return state->init( sys->memctx, sys->context, state->instance, state->init_func, state->usr );
			}
		}
	GAMESTATE_ASSERT( false, "Invalid state" );
	return 0;
	}


void term_state( system_t* sys, type_id_t state_id, void* instance )
	{
	for( int i = 0; i < sys->registered_states_count; ++i )
		{
		system_t::registered_state_t* state = &sys->registered_states[ i ];
		if( state->state_id == state_id )
			{
			state->term( sys->memctx, sys->context, instance ? instance : state->instance, state->term_func, state->usr );
			}
		}
	}


void push( system_t* sys, type_id_t state_id )
	{
	if( sys->active_states_stack_count >= sys->active_states_stack_capacity )
		{
		sys->active_states_stack_capacity *= 2;
        system_t::active_state_t* new_stack = (system_t::active_state_t*) GAMESTATE_MALLOC( sys->memctx, sys->active_states_stack_capacity * sizeof( *sys->active_states_stack ) );
        memcpy( new_stack, sys->active_states_stack, sys->active_states_stack_count * sizeof( *sys->active_states_stack ) );
        GAMESTATE_FREE( sys->memctx, sys->active_states_stack );
		sys->active_states_stack = new_stack;
		}

	system_t::active_state_t* state = &sys->active_states_stack[ sys->active_states_stack_count++ ];
	state->state_id = state_id;
	state->instance = init_state( sys, state_id, &state->state );
	}


void pop( system_t* sys )
    {
	if( sys->active_states_stack_count <= 0 ) return;

	system_t::active_state_t* state = &sys->active_states_stack[ --sys->active_states_stack_count  ];
    term_state( sys, state->state_id, state->instance );
    }


void queue_clear( system_t* sys )
	{
	sys->queued_operations_count = 0;
	}


void queue_push( system_t* sys, type_id_t state_id, float trans_in )
	{
	bool found = false;
	for( int i = 0; i < sys->registered_states_count; ++i )
		{
		system_t::registered_state_t* state = &sys->registered_states[ i ];
		if( state->state_id == state_id )
			{
			found = true; 
			break;
			}
		}
	GAMESTATE_ASSERT( found, "State not registered" );
	
	if( sys->queued_operations_count >= sys->queued_operations_capacity )
		{
		sys->queued_operations_capacity *= 2;
        system_t::queued_operation_t* new_ops = (system_t::queued_operation_t*) GAMESTATE_MALLOC( sys->memctx, sys->queued_operations_capacity * sizeof( *sys->queued_operations ) );
        memcpy( new_ops, sys->queued_operations, sys->queued_operations_count * sizeof( *sys->queued_operations ) );
        GAMESTATE_FREE( sys->memctx, sys->queued_operations );
        sys->queued_operations = new_ops;
		}
	system_t::queued_operation_t* op = &sys->queued_operations[ sys->queued_operations_count++ ];
    op->pop_count = 0;
	op->new_state_id = state_id;
	op->transition_time = trans_in;
	}


void queue_pop( system_t* sys, float trans_out, int count )
	{
	if( sys->queued_operations_count >= sys->queued_operations_capacity )
		{
		sys->queued_operations_capacity *= 2;
        system_t::queued_operation_t* new_ops = (system_t::queued_operation_t*) GAMESTATE_MALLOC( sys->memctx, sys->queued_operations_capacity * sizeof( *sys->queued_operations ) );
        memcpy( new_ops, sys->queued_operations, sys->queued_operations_count * sizeof( *sys->queued_operations ) );
        GAMESTATE_FREE( sys->memctx, sys->queued_operations );
        sys->queued_operations = new_ops;
		}
	system_t::queued_operation_t* op = &sys->queued_operations[ sys->queued_operations_count++ ];
    op->pop_count = count;
	op->new_state_id = 0;
	op->transition_time = trans_out;
	}


void queue_switch( system_t* sys, type_id_t state_id, float trans_out, float trans_in )
    {
    queue_clear( sys );
    queue_pop( sys, trans_out, -1 );
    queue_push( sys, state_id, trans_in );
    }


void update( system_t* sys, float delta_time )
	{
    while( sys->queued_operations_count > 0 && sys->transition_type == TRANSITION_NONE )
        {
        system_t::queued_operation_t op = sys->queued_operations[ 0 ];

        for( int i = 1; i < sys->queued_operations_count; ++i )
            sys->queued_operations[ i - 1 ] = sys->queued_operations[ i ];
        --sys->queued_operations_count;

        if( op.pop_count == 0 )
            {
            if( op.transition_time != 0.0f )
                {
                sys->transition_step = 1.0f / op.transition_time;
                sys->transition_type = TRANSITION_IN;
                sys->transition_progress = 0.0f;
                }
            push( sys, op.new_state_id );
            return;
            }
        else
            {
            if( op.transition_time != 0.0f )
                {
                sys->pop_count = op.pop_count <= 0 ? sys->active_states_stack_count : op.pop_count;
                sys->transition_step = 1.0f / op.transition_time;
                sys->transition_type = TRANSITION_OUT;
                sys->transition_progress = 1.0f;
                }
            else
                {
                int pop_count = op.pop_count <= 0 ? sys->active_states_stack_count : op.pop_count;
                pop_count = pop_count > sys->active_states_stack_count ? sys->active_states_stack_count : pop_count;
                for( int i = 0; i < pop_count; ++i ) 
                    pop( sys );
                }
            }
        }

    for( int i = 0; i < sys->active_states_stack_count; ++i )
		{
		system_t::active_state_t* state = &sys->active_states_stack[ i ];
		if( state->state->update )
			state->state->update( sys->memctx, sys->context, state->instance, state->state->update_func, state->state->usr );
		}
    if( sys->transition_type == TRANSITION_OUT )
        {
        sys->transition_progress -= sys->transition_step * delta_time;
        if( sys->transition_progress <= 0.0f )
            {
            sys->transition_progress = 0.0f;
            sys->transition_type = TRANSITION_NONE;
            int pop_count = sys->pop_count;
            pop_count = pop_count > sys->active_states_stack_count ? sys->active_states_stack_count : pop_count;
            for( int i = 0; i < pop_count; ++i ) 
                pop( sys );
            sys->pop_count = 0;
            }
        }
    else if( sys->transition_type == TRANSITION_IN )
        {
        sys->transition_progress += sys->transition_step * delta_time;
        if( sys->transition_progress >= 1.0f )
            {
            sys->transition_progress = 1.0f;
            sys->transition_type = TRANSITION_NONE;
            }
        }
	}


transition transition_type( system_t const* sys )
	{
	return sys->transition_type;
	}


float transition_progress( system_t const* sys )
	{
	return sys->transition_progress;
	}


} /* namespace internal */ } /* gamestate */

#endif /* GAMESTATE_IMPLEMENTATION */


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
