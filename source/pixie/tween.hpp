/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

tween.hpp - v0.1 - Generic interpolation library for C++.

Dependencies: 
    handles.h
    funccall.hpp
    refcount.hpp
*/

#ifndef tween_hpp
#define tween_hpp

#include "funccall.hpp"
#include "refcount.hpp"

namespace tween {

#ifndef TWEEN_U64
    #define TWEEN_U64 unsigned long long 
#endif

namespace internal { struct system_t; }

struct tweener;

struct tween_system
	{
	tween_system( void* memctx = 0 );
	~tween_system();

	void update( float delta_time );
	
	tweener tween( float duration );

	void stop_all();

	private:
		internal::system_t* internals_;
	};


template< typename T > struct property
	{
	virtual ~property() { }
	

	virtual T get() const = 0;
	virtual void set( T const& ) = 0;
	};


struct tweener
	{
    tweener();

    bool completed() const;

	template< typename T > 
	tweener property( tween::property<T>* prop, T const& target, T (*lerp_func)( T, T, float ) = 0 );

	template< typename T > 
	tweener property( refcount::ref< tween::property<T> > const& prop, T const& target, T (*lerp_func)( T, T, float ) = 0  );

	tweener delay( float duration );

	typedef float (*ease_func_t)( float );
	tweener ease( ease_func_t ease_func );
    tweener repeat( int times = -1 );
	tweener pingpong( bool value = true );
	tweener reverse( bool value = true );
	
	tweener on_complete( refcount::ref<funccall::func_call> const& handler );
	tweener on_repeat( refcount::ref<funccall::func_call> const& handler );
	tweener on_update( refcount::ref<funccall::func_call> const& handler );


    template<typename F > 
    tweener on_complete( F handler );

    template<typename F, typename P0 > 
    tweener on_complete( F handler, P0 p0 );

    template<typename F, typename P0, typename P1 > 
    tweener on_complete( F handler, P0 p0, P1 p1 );

    template<typename F, typename P0, typename P1, typename P2 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2 );

    template<typename F, typename P0, typename P1, typename P2, typename P3 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
    tweener on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 );


    template<typename F > 
    tweener on_repeat( F handler );

    template<typename F, typename P0 > 
    tweener on_repeat( F handler, P0 p0 );

    template<typename F, typename P0, typename P1 > 
    tweener on_repeat( F handler, P0 p0, P1 p1 );

    template<typename F, typename P0, typename P1, typename P2 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2 );

    template<typename F, typename P0, typename P1, typename P2, typename P3 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
    tweener on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 );


    template<typename F > 
    tweener on_update( F handler );

    template<typename F, typename P0 > 
    tweener on_update( F handler, P0 p0 );

    template<typename F, typename P0, typename P1 > 
    tweener on_update( F handler, P0 p0, P1 p1 );

    template<typename F, typename P0, typename P1, typename P2 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2 );

    template<typename F, typename P0, typename P1, typename P2, typename P3 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 );

    template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
    tweener on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 );

    private:
		friend tweener tween_system::tween( float );
		tweener( internal::system_t* system, float duration );

		struct instance
			{
			~instance();
			TWEEN_U64 handle;
			internal::system_t* system;
			};
		refcount::ref<instance> instance_;
		internal::system_t* system_;
	};



template< typename T > refcount::ref< property<T> > make_property( T* variable );
template< typename T > refcount::ref< property<T> > make_property( T (*get)(), void (*set)( T ) );


template< typename T, typename U > refcount::ref< property<T> > make_property( T (*get)( U* ), void (*set)( T, U* ), U* usr );
template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T U::*member );
template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)(), void (U::*set)( T ) );
template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)() const, void (U::*set)( T ) );
template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)() const, U& (U::*set)( T ) );

template< typename T, typename U > refcount::ref< property<T> > make_property( T (*get)( U* ), void (*set)( T,  U* ), refcount::ref<U> const& usr );
template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T U::*member );
template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)(), void (U::*set)( T ) );
template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)() const, void (U::*set)( T ) );
template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)() const, U& (U::*set)( T ) );

} /* namespace tween */

#endif /* tween_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef tween_impl
#define tween_impl

namespace tween { namespace internal {

struct interpolator
	{
	virtual ~interpolator() { };
	virtual void update( float t ) = 0;
	};


template< typename T > struct interpolator_ref : interpolator
	{
	private:
		friend refcount::ref<interpolator_ref>;

		virtual void update( float t )
			{
			if( !started_ ) { initial_ = property_->get(); started_ = true; }
			property_->set( lerp_func_( initial_, target_, t ) );
			}

		static T default_lerp( T a, T b, float t )
			{
			return a + ( b - a ) * t;
			}

		interpolator_ref( refcount::ref< tween::property<T> > const& prop, T const& target, T (* const lerp_func )( T, T, float ) ):
			started_( false ),
			property_( prop ),
			target_( target ),
			lerp_func_( lerp_func ? lerp_func : default_lerp )
			{
			}

		T (*lerp_func_)( T, T, float );
		refcount::ref< tween::property<T> > property_;
		T initial_;
		T target_;
		bool started_;
	};


template< typename T > struct interpolator_ptr : interpolator
	{
	private:
		friend refcount::ref<interpolator_ptr>;

		virtual void update( float t )
			{
			if( !started_ ) { initial_ = property_->get(); started_ = true; }
			property_->set( lerp_func_( initial_, target_, t ) );
			}

		static T default_lerp( T a, T b, float t )
			{
			return a + ( b - a ) * t;
			}

		interpolator_ptr( tween::property<T>* const prop, T const& target, T (* const lerp_func)( T, T, float ) ):
			started_( false ),
			property_( prop ),
			target_( target ),
			lerp_func_( lerp_func ? lerp_func : default_lerp )
			{
			}

		T (*lerp_func_)( T, T, float );
		tween::property<T>* property_;
		T initial_;
		T target_;
		bool started_;
	};


void add_interpolator( struct system_t* system, TWEEN_U64 handle, refcount::ref<interpolator> const& interp );


template< typename T > struct variable : property<T>
	{
	virtual T get() const { return *variable_; }
	virtual void set( T const& value ) { *variable_ = value; }	
	private:
		friend refcount::ref<variable>;
		variable( T* var ) : variable_( var ) {  }	
		T* variable_;
	};


template< typename T > struct functions : property<T>
	{
	virtual T get() const { return get_(); }
	virtual void set( T const& value ) { set_( value ); }	
	private:
		friend refcount::ref<functions>;
		functions( T (*get)(), void (*set)( T ) ) : get_( get ), set_( set ) { }
		T (*get_)();
		void (*set_)( T );
	};




template< typename T, typename U > struct functions_usr : property<T>
	{
	virtual T get() const { return get_( usr_ ); }
	virtual void set( T const& value ) { set_( value, usr_ ); }	
	private:
		friend refcount::ref<functions_usr>;
		functions_usr( T (*get)( U* ), void (*set)( T, U* ), U* usr ) : get_( get ), set_( set ), usr_( usr ) { }
		T (*get_)( U* );
		void (*set_)( T, U* );
		U* usr_;
	};


template< typename T, typename U > struct member_var : property<T>
	{
	virtual T get() const { return instance_->*member_; }
	virtual void set( T const& value ) { ( instance_->*member_ ) = value; }	
	private:
		friend refcount::ref<member_var>;
		member_var( U* instance, T U::* member ) : instance_( instance ), member_( member ) { }
		U* instance_;
		T U::* member_;		
	};


template< typename T, typename U > struct member_funcs : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<member_funcs>;
		member_funcs( U* instance, T (U::*get)(), void (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		U* instance_;
		T (U::*get_)();
		void (U::*set_)( T );
	};


template< typename T, typename U > struct member_funcs_const : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<member_funcs_const>;
		member_funcs_const( U* instance, T (U::*get)() const, void (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		U* instance_;
		T (U::*get_)() const;
		void (U::*set_)( T );
	};


template< typename T, typename U > struct member_funcs_const_flow : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<member_funcs_const_flow>;
		member_funcs_const_flow( U* instance, T (U::*get)() const, U& (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		U* instance_;
		T (U::*get_)() const;
		U& (U::*set_)( T );
	};





template< typename T, typename U > struct ref_functions_usr : property<T>
	{
	virtual T get() const { return get_( usr_ ); }
	virtual void set( T const& value ) { set_( value, usr_ ); }	
	private:
		friend refcount::ref<ref_functions_usr>;
		ref_functions_usr( T (*get)( U* ), void (*set)( T, U* ), refcount::ref<U> const& usr ) : get_( get ), set_( set ), usr_( usr ) { }
		T (*get_)( U* );
		void (*set_)( T, U* );
		refcount::ref<U> usr_;
	};


template< typename T, typename U > struct ref_member_var : property<T>
	{
	virtual T get() const { return instance_->*member_; }
	virtual void set( T const& value ) { ( instance_->*member_ ) = value; }	
	private:
		friend refcount::ref<ref_member_var>;
		ref_member_var( refcount::ref<U> const& instance, T U::* member ) : instance_( instance ), member_( member ) { }
		refcount::ref<U> instance_;
		T U::* member_;		
	};


template< typename T, typename U > struct ref_member_funcs : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<ref_member_funcs>;
		ref_member_funcs( refcount::ref<U> const& instance, T (U::*get)(), void (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		refcount::ref<U> instance_;
		T (U::*get_)();
		void (U::*set_)( T );
	};


template< typename T, typename U > struct ref_member_funcs_const : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<ref_member_funcs_const>;
		ref_member_funcs_const( refcount::ref<U> const& instance, T (U::*get)() const, void (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		refcount::ref<U> instance_;
		T (U::*get_)() const;
		void (U::*set_)( T );
	};


template< typename T, typename U > struct ref_member_funcs_const_flow : property<T>
	{
	virtual T get() const { return (instance_->*get_)(); }
	virtual void set( T const& value ) { (instance_->*set_ )( value ); }	
	private:
		friend refcount::ref<ref_member_funcs_const_flow>;
		ref_member_funcs_const_flow( refcount::ref<U> const& instance, T (U::*get)() const, U& (U::*set)( T ) ) : instance_( instance ), get_( get ), set_( set ) { }
		refcount::ref<U> instance_;
		T (U::*get_)() const;
		U& (U::*set_)( T );
	};

} /* namespace internal */ } /* namespace tween */


namespace tween {


template< typename T > tweener tweener::property( tween::property<T>* const prop, T const& target, T (* const lerp_func)( T, T, float ) ) 
	{ 
	refcount::ref<internal::interpolator> interp = 
		refcount::ref< internal::interpolator_ptr<T> >::make_new( prop, target, lerp_func );
	add_interpolator( system_, instance_->handle, interp );
	return *this; 
	}


template< typename T > tweener tweener::property( refcount::ref< tween::property<T> > const& prop, T const& target, T (* const lerp_func)( T, T, float ) ) 
	{ 
	refcount::ref<internal::interpolator> interp = 
		refcount::ref< internal::interpolator_ref<T> >::make_new( prop, target, lerp_func );
	add_interpolator( system_, instance_->handle, interp );
	return *this; 
	}


template<typename F > 
tweener tweener::on_complete( F handler )
    {
    return on_complete( funccall::make_func_call( handler ) );
    }

template<typename F, typename P0 > 
tweener tweener::on_complete( F handler, P0 p0 )
    {
    return on_complete( funccall::make_func_call( handler, p0 ) );
    }

template<typename F, typename P0, typename P1 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1 ) );
    }

template<typename F, typename P0, typename P1, typename P2 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
tweener tweener::on_complete( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 )
    {
    return on_complete( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) );
    }



template<typename F > 
tweener tweener::on_repeat( F handler )
    {
    return on_repeat( funccall::make_func_call( handler ) );
    }

template<typename F, typename P0 > 
tweener tweener::on_repeat( F handler, P0 p0 )
    {
    return on_repeat( funccall::make_func_call( handler, p0 ) );
    }

template<typename F, typename P0, typename P1 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1 ) );
    }

template<typename F, typename P0, typename P1, typename P2 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
tweener tweener::on_repeat( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 )
    {
    return on_repeat( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) );
    }


template<typename F > 
tweener tweener::on_update( F handler )
    {
    return on_update( funccall::make_func_call( handler ) );
    }

template<typename F, typename P0 > 
tweener tweener::on_update( F handler, P0 p0 )
    {
    return on_update( funccall::make_func_call( handler, p0 ) );
    }

template<typename F, typename P0, typename P1 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1 ) );
    }

template<typename F, typename P0, typename P1, typename P2 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8 ) );
    }

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
tweener tweener::on_update( F handler, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 )
    {
    return on_update( funccall::make_func_call( handler, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) );
    }

template< typename T > refcount::ref< property<T> > make_property( T* variable )
	{
	return refcount::ref< internal::variable<T> >::make_new( variable );
	}

template< typename T > refcount::ref< property<T> > make_property( T (*get)(), void (*set)( T ) )
	{
	return refcount::ref< internal::functions<T> >::make_new( get, set );
	}



template< typename T, typename U > refcount::ref< property<T> > make_property( T (*get)( U* ), void (*set)( T,  U* ), U* usr )
	{
	return refcount::ref< internal::functions_usr<T, U> >::make_new( get, set, usr );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T U::* member )
	{
	return refcount::ref< internal::member_var<T, U> >::make_new( instance, member );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)(), void (U::*set)( T ) )
	{
	return refcount::ref< internal::member_funcs<T, U> >::make_new( instance, get, set );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)() const, void (U::*set)( T ) )
	{
	return refcount::ref< internal::member_funcs_const<T, U> >::make_new( instance, get, set );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( U* instance, T (U::*get)() const, U& (U::*set)( T ) )
	{
	return refcount::ref< internal::member_funcs_const_flow<T, U> >::make_new( instance, get, set );
	}



template< typename T, typename U > refcount::ref< property<T> > make_property( T (*get)( U* ), void (*set)( T,  U* ), refcount::ref<U> const& usr )
	{
	return refcount::ref< internal::ref_functions_usr<T, U> >::make_new( get, set, usr );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T U::* member )
	{
	return refcount::ref< internal::ref_member_var<T, U> >::make_new( instance, member );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)(), void (U::*set)( T ) )
	{
	return refcount::ref< internal::ref_member_funcs<T, U> >::make_new( instance, get, set );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)() const, void (U::*set)( T ) )
	{
	return refcount::ref< internal::ref_member_funcs_const<T, U> >::make_new( instance, get, set );
	}

template< typename T, typename U > refcount::ref< property<T> > make_property( refcount::ref<U> const& instance, T (U::*get)() const, U& (U::*set)( T ) )
	{
	return refcount::ref< internal::ref_member_funcs_const_flow<T, U> >::make_new( instance, get, set );
	}

} /* namespace tween */


#endif /* tween_impl */


#ifdef TWEEN_IMPLEMENTATION
#undef TWEEN_IMPLEMENTATION

#ifndef TWEEN_MALLOC
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
	#include <stdlib.h>
	#define TWEEN_MALLOC( ctx, size ) ( (void)ctx,::malloc( size ) )
	#define TWEEN_FREE( ctx, ptr ) ( (void)ctx,::free( ptr ) )
#endif

#include "handles.h"

namespace tween { namespace internal {
	
struct instance_t
	{
	TWEEN_U64 handle;
	tweener::ease_func_t ease;
	bool done;
	bool is_safe_to_remove;
	bool pingpong;
	bool reverse;
	float elapsed_time;
	float elapsed_delay;
	float duration;
	float delay;
	int repeat;
	int interpolators_capacity;
	int interpolators_count;
	refcount::ref<interpolator> interpolators[ 8 ];
	refcount::ref<interpolator>* interpolators_large;
	refcount::ref<funccall::func_call> on_complete;
	refcount::ref<funccall::func_call> on_repeat;
	refcount::ref<funccall::func_call> on_update;
	};

	
struct system_t
	{
    void* memctx;
	handles_t handles;
	
	instance_t* instances;
	int instances_capacity;
	int instances_count;
	};


static float default_ease( float t ) 
	{ 
	return t; 
	}


static void init( instance_t* instance )
	{
	memset( instance, 0, sizeof( instance_t ) );
	instance->ease = default_ease;
	instance->interpolators_capacity = sizeof( instance->interpolators ) / sizeof( *(instance->interpolators) );
	}


static void deinit( instance_t* instance, bool free_mem, void* memctx )
	{
	instance->on_complete = refcount::ref<funccall::func_call>();
	instance->on_repeat = refcount::ref<funccall::func_call>();
	instance->on_update = refcount::ref<funccall::func_call>();

	refcount::ref<interpolator>* interpolators = 
		instance->interpolators_large ? instance->interpolators_large : instance->interpolators;
		
	for( int j = 0; j < instance->interpolators_count; ++j )
		interpolators[ j ] = refcount::ref<interpolator>();
		
	if( free_mem ) if( instance->interpolators_large ) TWEEN_FREE( memctx, instance->interpolators_large );
	}


static TWEEN_U64 reg( system_t* system )
	{
	if( system->instances_count >= system->instances_capacity )
		{
		system->instances_capacity *= 2;
        instance_t* new_instances = (instance_t*) TWEEN_MALLOC( system->memctx, system->instances_capacity * sizeof( instance_t ) );
        memcpy( new_instances, system->instances, system->instances_count * sizeof( instance_t ) );
        TWEEN_FREE( system->memctx, system->instances );
        system->instances = new_instances;
		}
	int index = system->instances_count++;
	TWEEN_U64 handle = handles_to_u64( &system->handles, handles_alloc( &system->handles, index ) );

	init( &system->instances[ index ] );

	system->instances[ index ].handle = handle;

	return handle;
	}


static void remove( system_t* system, int index )
	{
	--system->instances_count;

	handles_release( &system->handles, handles_from_u64( &system->handles, system->instances[ index ].handle ) );

	if( index != system->instances_count )
		{
		deinit( &system->instances[ index ], true, system->memctx );
		system->instances[ index ] = system->instances[ system->instances_count ];
		deinit( &system->instances[ system->instances_count ], false, system->memctx );
		handles_update( &system->handles, handles_from_u64( &system->handles, system->instances[ index ].handle ), index );
		}
	else
		{
		deinit( &system->instances[ system->instances_count ], true, system->memctx );
		}
	}


static void unregister( system_t* system, TWEEN_U64 const handle )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;

	instance_t* instance = &system->instances[ index ];
	if( instance->done )	
		remove( system, index );
	else
		instance->is_safe_to_remove = true;
	}


void add_interpolator( struct system_t* system, TWEEN_U64 const handle, refcount::ref<interpolator> const& interp )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;

	instance_t* instance = &system->instances[ index ];
	if( instance->interpolators_count >= instance->interpolators_capacity )
		{
		instance->interpolators_capacity *= 2;
		if( instance->interpolators_large )
            {
            refcount::ref<interpolator>* new_large = (refcount::ref<interpolator>*) TWEEN_MALLOC( system->memctx, instance->interpolators_capacity * sizeof( refcount::ref<interpolator> ) );
            memcpy( new_large, instance->interpolators_large, instance->interpolators_count * sizeof( refcount::ref<interpolator> ) );
            TWEEN_FREE( system->memctx, instance->interpolators_large );
            instance->interpolators_large = new_large;
            }
		else
            {
			instance->interpolators_large = (refcount::ref<interpolator>*) TWEEN_MALLOC( system->memctx, instance->interpolators_capacity * sizeof( refcount::ref<interpolator> ) );
            memcpy( instance->interpolators_large, instance->interpolators, instance->interpolators_count * sizeof( refcount::ref<interpolator> ) );
            }
		}

	refcount::ref<interpolator>* interpolators = instance->interpolators_large ? instance->interpolators_large : instance->interpolators;
	interpolators[ instance->interpolators_count++ ] = interp;
	}


static bool completed( system_t* system, TWEEN_U64 handle )
    {
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
    if( index < 0 ) return true;
	return system->instances[ index ].done;
    }


static void duration_set( system_t* system, TWEEN_U64 handle, float duration )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].duration = duration;
	}


static void delay_set( system_t* system, TWEEN_U64 handle, float duration )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].delay = duration;
	}


static void ease_set( system_t* system, TWEEN_U64 handle, tweener::ease_func_t ease )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].ease = ease;
	}


static void on_complete_set( system_t* system, TWEEN_U64 handle, refcount::ref<funccall::func_call> const& handler )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].on_complete = handler;
	}


static void on_repeat_set( system_t* system, TWEEN_U64 handle, refcount::ref<funccall::func_call> const& handler )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].on_repeat = handler;
	}


static void on_update_set( system_t* system, TWEEN_U64 handle, refcount::ref<funccall::func_call> const& handler )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].on_update = handler;
	}


static void repeat_set( system_t* system, TWEEN_U64 handle, int times )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].repeat = times;
	}


static void pingpong_set( system_t* system, TWEEN_U64 handle, bool value )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].pingpong = value;
	}


static void reverse_set( system_t* system, TWEEN_U64 handle, bool value )
	{
	int index = handles_index( &system->handles, handles_from_u64( &system->handles, handle ) );
	if( index < 0 ) return;
	system->instances[ index ].reverse = value;
	}

} /* namespace internal */ } /* namespace tween */

namespace tween {

tween_system::tween_system( void* memctx )
	{
	internals_ = (internal::system_t*) TWEEN_MALLOC( memctx, sizeof( internal::system_t ) );
    internals_->memctx = memctx;
	internals_->instances_count = 0;
	internals_->instances_capacity = 256;
	internals_->instances = (internal::instance_t*) TWEEN_MALLOC( internals_->memctx, internals_->instances_capacity * sizeof( internal::instance_t ) );
	
	handles_init( &internals_->handles, internals_->instances_capacity, memctx );	
	}


tween_system::~tween_system()
	{
	handles_term( &internals_->handles );

	for( int i = 0; i < internals_->instances_count; ++i )
		{
		internal::instance_t* instance = &internals_->instances[ i ];
		internal::deinit( instance, true, internals_->memctx );
		}
	
	TWEEN_FREE( internals_->memctx, internals_->instances );
	TWEEN_FREE( internals_->memctx, internals_ );
	}


void tween_system::update( float const delta_time )
	{
	for( int i = 0; i < internals_->instances_count; ++i )
		{
		internal::instance_t* instance = &internals_->instances[ i ];
		if( !instance->done )
			{
			if( instance->elapsed_delay < instance->delay )
				{
				instance->elapsed_delay += delta_time;
				continue;
				}

			if( instance->on_update ) instance->on_update->call();

			instance->elapsed_time += delta_time;

			float t = instance->elapsed_time / instance->duration;
			t = t < 0.0f ? 0.0f : t;
			t = t > 1.0f ? 1.0f : t;
			t = instance->reverse ? t = 1.0f - t : t;
			t = instance->ease( t );

			refcount::ref<internal::interpolator>* interpolators = 
				instance->interpolators_large ? instance->interpolators_large : instance->interpolators;

			for( int j = 0; j < instance->interpolators_count; ++j )
				interpolators[ j ]->update( t );
			
			if( instance->elapsed_time >= instance->duration )
				{
				if( instance->repeat != 0 )
					{
					if( instance->on_repeat ) instance->on_repeat->call();
					instance->elapsed_time = 0.0f;
					instance->reverse = instance->pingpong ? !instance->reverse : instance->reverse;
					if( instance->repeat > 0 ) --instance->repeat;
					}
				else
					{
					instance->done = true;
					if( instance->on_complete ) instance->on_complete->call();

					if( instance->is_safe_to_remove )
						{
						remove( internals_, i );
						--i;
						continue;
						}
					}
				}
			}
		}
	}


tweener tween_system::tween( float const duration )
	{
	return tweener( internals_, duration );
	}


void tween_system::stop_all()
	{
	while( internals_->instances_count > 0 )
		{
		remove( internals_, 0 );
		}
	}


tweener::tweener():
    system_( 0 )
    {
    }


bool tweener::completed() const
    {
    if( !system_ ) return true;
    return internal::completed( system_, instance_->handle );
    }


tweener tweener::delay( float const duration ) 
	{ 
    if( !system_ ) return *this;
	internal::delay_set( system_, instance_->handle, duration );
	return *this; 
	}


tweener tweener::ease( ease_func_t const ease_func ) 
	{ 
    if( !system_ ) return *this;
	internal::ease_set( system_, instance_->handle, ease_func );
	return *this; 
	}


tweener tweener::repeat( int const times ) 
	{ 
    if( !system_ ) return *this;
	internal::repeat_set( system_, instance_->handle, times );
	return *this; 
	}


tweener tweener::pingpong( bool const value ) 
	{ 
    if( !system_ ) return *this;
	internal::pingpong_set( system_, instance_->handle, value );
	return *this; 
	}


tweener tweener::reverse( bool const value ) 
	{ 
    if( !system_ ) return *this;
    internal::reverse_set( system_, instance_->handle, value );
	return *this; 
	}


tweener tweener::on_complete( refcount::ref<funccall::func_call> const& handler ) 
	{ 
    if( !system_ ) return *this;
	internal::on_complete_set( system_, instance_->handle, handler );
	return *this; 
	}


tweener tweener::on_repeat( refcount::ref<funccall::func_call> const& handler ) 
	{ 
    if( !system_ ) return *this;
	internal::on_repeat_set( system_, instance_->handle, handler );
	return *this; 
	}


tweener tweener::on_update( refcount::ref<funccall::func_call> const& handler ) 
	{ 
    if( !system_ ) return *this;
	internal::on_update_set( system_, instance_->handle, handler );
	return *this; 
	}


tweener::tweener( internal::system_t* system, float const duration ) :
	system_( system )
	{
	instance_ = refcount::ref<instance>::make_new();
	instance_->handle = reg( system_ );
	instance_->system = system_;
    internal::duration_set( system_, instance_->handle, duration );
	}


tweener::instance::~instance()
	{
    if( !system ) internal::unregister( system, handle );
	}


} /* namespace tween */

#endif /* TWEEN_IMPLEMENTATION */

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

