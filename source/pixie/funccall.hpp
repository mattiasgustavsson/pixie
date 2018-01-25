/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

funccall.hpp - v0.1 - C++ wrapper for delayed function/method calls.

Dependencies: 
    refcount.hpp
*/

#ifndef funccall_hpp
#define funccall_hpp

#include "refcount.hpp"

namespace funccall {

struct func_call
	{
	virtual void operator()() = 0;
	virtual void call() = 0;
	virtual ~func_call() { }
	};


#if defined(_MSC_VER) && _MSC_VER >= 1600

// lambda

template< typename F > 
refcount::ref<func_call> make_func_call( F f ); 

template< typename F, typename P0 > 
refcount::ref<func_call> make_func_call( F f, P0 p0 ); 

template< typename F, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1 ); 

template< typename F, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ); 

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ); 

#endif /* defined(_MSC_VER) && _MSC_VER >= 1600 */


// cdeclcall

template< typename R >
refcount::ref<func_call> make_func_call( R (*f)() ); 

template< typename R, typename P0 > 
refcount::ref<func_call> make_func_call( R (*f)( P0 ), P0 p0 ); 

template< typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1 ), P0 p0, P1 p1 ); 

template< typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ); 

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ); 


// thiscall

template< typename T, typename R > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)() ); 

template< typename T, typename R, typename P0 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0 ), P0 p0 ); 

template< typename T, typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1 ), P0 p0, P1 p1 ); 

template< typename T, typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ); 


// thiscall refcount::ref

template< typename T, typename R > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)() ); 

template< typename T, typename R, typename P0 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0 ), P0 p0 ); 

template< typename T, typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1 ), P0 p0, P1 p1 ); 

template< typename T, typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ); 

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ); 

} /* namespace funccall */

#endif /* funccall_hpp */


/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef funccall_impl
#define funccall_impl

namespace funccall { namespace internal {

#if defined(_MSC_VER) && _MSC_VER >= 1600

// lambda

template< typename F > 
struct func_lambda_call0 : func_call
	{
	void operator()() { f(); }
	void call() { f(); }
    func_lambda_call0& operator=( func_lambda_call0& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call0>;
		func_lambda_call0( F f ) : 
			f( f ) { }
		F f;
	};

template< typename F, typename P0 > 
struct func_lambda_call1 : func_call
	{
	void operator()() { f( p0 ); }
	void call() { f( p0 ); }
    func_lambda_call1& operator=( func_lambda_call1& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call1>;
		func_lambda_call1( F f, P0 p0 ) : 
			f( f ), p0( p0 ) { }
		F f;
		P0 p0;
	};

template< typename F, typename P0, typename P1 > 
struct func_lambda_call2 : func_call
	{
	void operator()() { f( p0, p1 ); }
	void call() { f( p0, p1 ); }
    func_lambda_call2& operator=( func_lambda_call2& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call2>;
		func_lambda_call2( F f, P0 p0, P1 p1 ) : 
			f( f ), p0( p0 ), p1( p1 ) { }
		F f;
		P0 p0; P1 p1;
	};

template< typename F, typename P0, typename P1, typename P2 >
struct func_lambda_call3 : func_call
	{
	void operator()() { f( p0, p1, p2 ); }
	void call() { f( p0, p1, p2 ); }
    func_lambda_call3& operator=( func_lambda_call3& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call3>;
		func_lambda_call3( F f, P0 p0, P1 p1, P2 p2 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ) { }
		F f;
		P0 p0; P1 p1; P2 p2;
	};

template< typename F, typename P0, typename P1, typename P2, typename P3 > 
struct func_lambda_call4 : func_call
	{
	void operator()() { f( p0, p1, p2, p3 ); }
	void call() { f( p0, p1, p2, p3 ); }
    func_lambda_call4& operator=( func_lambda_call4& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call4>;
		func_lambda_call4( F f, P0 p0, P1 p1, P2 p2, P3 p3 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3;
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
struct func_lambda_call5 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4 ); }
	void call() { f( p0, p1, p2, p3, p4 ); }
    func_lambda_call5& operator=( func_lambda_call5& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call5>;
		func_lambda_call5( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4;
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
struct func_lambda_call6 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5 ); }
	void call() { f( p0, p1, p2, p3, p4, p5 ); }
    func_lambda_call6& operator=( func_lambda_call6& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call6>;
		func_lambda_call6( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5;
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
struct func_lambda_call7 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6 ); }
    func_lambda_call7& operator=( func_lambda_call7& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call7>;
		func_lambda_call7( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; 
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
struct func_lambda_call8 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7 ); }
    func_lambda_call8& operator=( func_lambda_call8& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call8>;
		func_lambda_call8( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7;
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
struct func_lambda_call9 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
    func_lambda_call9& operator=( func_lambda_call9& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call9>;
		func_lambda_call9( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8; 
	};

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9  > 
struct func_lambda_call10 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
    func_lambda_call10& operator=( func_lambda_call10& ) = delete;
	private:
		friend struct refcount::ref<func_lambda_call10>;
		func_lambda_call10( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ), p9( p9 ) { }
		F f;
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8; P9 p9; 
	};

#endif /* defined(_MSC_VER) && _MSC_VER >= 1600 */


// cdeclcall

template< typename R > 
struct func_cdecl_call0 : func_call
	{
	void operator()() { f(); }
	void call() { f(); }
	private:
		friend struct refcount::ref<func_cdecl_call0>;
		func_cdecl_call0( R (*f)() ) : 
			f( f ) { }
		R (*f)();
	};

template< typename R, typename P0 > 
struct func_cdecl_call1 : func_call
	{
	void operator()() { f( p0 ); }
	void call() { f( p0 ); }
	private:
		friend struct refcount::ref<func_cdecl_call1>;
		func_cdecl_call1( R (*f)( P0 ), P0 p0 ) : 
			f( f ), p0( p0 ) { }
		R (*f)( P0 );
		P0 p0;
	};

template< typename R, typename P0, typename P1 > 
struct func_cdecl_call2 : func_call
	{
	void operator()() { f( p0, p1 ); }
	void call() { f( p0, p1 ); }
	private:
		friend struct refcount::ref<func_cdecl_call2>;
		func_cdecl_call2( R (*f)( P0, P1 ), P0 p0, P1 p1 ) : 
			f( f ), p0( p0 ), p1( p1 ) { }
		R (*f)( P0, P1 );
		P0 p0; P1 p1;
	};

template< typename R, typename P0, typename P1, typename P2 > 
struct func_cdecl_call3 : func_call
	{
	void operator()() { f( p0, p1, p2 ); }
	void call() { f( p0, p1, p2 ); }
	private:
		friend struct refcount::ref<func_cdecl_call3>;
		func_cdecl_call3( R (*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ) { }
		R (*f)( P0, P1, P2 );
		P0 p0; P1 p1; P2 p2;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3 > 
struct func_cdecl_call4 : func_call
	{
	void operator()() { f( p0, p1, p2, p3 ); }
	void call() { f( p0, p1, p2, p3 ); }
	private:
		friend struct refcount::ref<func_cdecl_call4>;
		func_cdecl_call4( R (*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ) { }
		R (*f)( P0, P1, P2, P3 );
		P0 p0; P1 p1; P2 p2; P3 p3;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
struct func_cdecl_call5 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4 ); }
	void call() { f( p0, p1, p2, p3, p4 ); }
	private:
		friend struct refcount::ref<func_cdecl_call5>;
		func_cdecl_call5( R (*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ) { }
		R (*f)( P0, P1, P2, P3, P4 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
struct func_cdecl_call6 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5 ); }
	void call() { f( p0, p1, p2, p3, p4, p5 ); }
	private:
		friend struct refcount::ref<func_cdecl_call6>;
		func_cdecl_call6( R (*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ) { }
		R (*f)( P0, P1, P2, P3, P4, P5 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
struct func_cdecl_call7 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6 ); }
	private:
		friend struct refcount::ref<func_cdecl_call7>;
		func_cdecl_call7( R (*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ) { }
		R (*f)( P0, P1, P2, P3, P4, P5, P6 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
struct func_cdecl_call8 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7 ); }
	private:
		friend struct refcount::ref<func_cdecl_call8>;
		func_cdecl_call8( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ) { }
		R (*f)( P0, P1, P2, P3, P4, P5, P6, P7 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
struct func_cdecl_call9 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
	private:
		friend struct refcount::ref<func_cdecl_call9>;
		func_cdecl_call9( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ) { }
		R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8;
	};

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
struct func_cdecl_call10 : func_call
	{
	void operator()() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
	void call() { f( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
	private:
		friend struct refcount::ref<func_cdecl_call10>;
		func_cdecl_call10( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) : 
			f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ), p9( p9 ) { }
		R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8; P9 p9;
	};


// thiscall

template< typename T, typename R > 
struct func_this_call0 : func_call
	{
	void operator()() { (t->*f)(); }
	void call() { (t->*f)(); }
	private:
		friend struct refcount::ref<func_this_call0>;
		func_this_call0( T* t, R (T::*f)() ) : 
			t( t ), f( f ) { }
		T* t;
		R (T::*f)();
	};

template< typename T, typename R, typename P0 > 
struct func_this_call1 : func_call
	{
	void operator()() { (t->*f)( p0 ); }
	void call() { (t->*f)( p0 ); }
	private:
		friend struct refcount::ref<func_this_call1>;
		func_this_call1( T* t, R (T::*f)( P0 ), P0 p0 ) : 
			t( t ), f( f ), p0( p0 ) { }
		T* t;
		R (T::*f)( P0 );
		P0 p0; 
	};

template< typename T, typename R, typename P0, typename P1 > 
struct func_this_call2 : func_call
	{
	void operator()() { (t->*f)( p0, p1 ); }
	void call() { (t->*f)( p0, p1 ); }
	private:
		friend struct refcount::ref<func_this_call2>;
		func_this_call2( T* t, R (T::*f)( P0, P1 ), P0 p0, P1 p1 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ) { }
		T* t;
		R (T::*f)( P0, P1 );
		P0 p0; P1 p1;
	};

template< typename T, typename R, typename P0, typename P1, typename P2 > 
struct func_this_call3 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2 ); }
	void call() { (t->*f)( p0, p1, p2 ); }
	private:
		friend struct refcount::ref<func_this_call3>;
		func_this_call3( T* t, R (T::*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ) { }
		T* t;
		R (T::*f)( P0, P1, P2 );
		P0 p0; P1 p1; P2 p2;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3 > 
struct func_this_call4 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3 ); }
	void call() { (t->*f)( p0, p1, p2, p3 ); }
	private:
		friend struct refcount::ref<func_this_call4>;
		func_this_call4( T* t, R (T::*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3 );
		P0 p0; P1 p1; P2 p2; P3 p3;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
struct func_this_call5 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4 ); }
	private:
		friend struct refcount::ref<func_this_call5>;
		func_this_call5( T* t, R (T::*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
struct func_this_call6 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4, p5 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4, p5 ); }
	private:
		friend struct refcount::ref<func_this_call6>;
		func_this_call6( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4, P5 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
struct func_this_call7 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4, p5, p6 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4, p5, p6 ); }
	private:
		friend struct refcount::ref<func_this_call7>;
		func_this_call7( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4, P5, P6 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
struct func_this_call8 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7 ); }
	private:
		friend struct refcount::ref<func_this_call8>;
		func_this_call8( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
struct func_this_call9 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7, p8 ); }
	private:
		friend struct refcount::ref<func_this_call9>;
		func_this_call9( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8;
	};

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
struct func_this_call10 : func_call
	{
	void operator()() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
	void call() { (t->*f)( p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); }
	private:
		friend struct refcount::ref<func_this_call10>;
		func_this_call10( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) : 
			t( t ), f( f ), p0( p0 ), p1( p1 ), p2( p2 ), p3( p3 ), p4( p4 ), p5( p5 ), p6( p6 ), p7( p7 ), p8( p8 ), p9( p9 ) { }
		T* t;
		R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 );
		P0 p0; P1 p1; P2 p2; P3 p3; P4 p4; P5 p5; P6 p6; P7 p7; P8 p8; P9 p9;
	};

} /* namespace internal */ } /* namespace funccall */


namespace funccall {


#if defined(_MSC_VER) && _MSC_VER >= 1600

// lambda

template< typename F > 
refcount::ref<func_call> make_func_call( F f ) 
	{ 
	return refcount::ref< internal::func_lambda_call0< F > >::make_new( f );
	}

template< typename F, typename P0 > 
refcount::ref<func_call> make_func_call( F f, P0 p0 ) 
	{ 
	return refcount::ref< internal::func_lambda_call1< F, P0 > >::make_new( f, p0 );
	}

template< typename F, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1 ) 
	{ 
	return refcount::ref< internal::func_lambda_call2< F, P0, P1 > >::make_new( f, p0, p1 );
	}

template< typename F, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2 ) 
	{ 
	return refcount::ref< internal::func_lambda_call3< F, P0, P1, P2 > >::make_new( f, p0, p1, p2 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return refcount::ref< internal::func_lambda_call4< F, P0, P1, P2, P3 > >::make_new( f, p0, p1, p2, p3 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return refcount::ref< internal::func_lambda_call5< F, P0, P1, P2, P3, P4 > >::make_new( f, p0, p1, p2, p3, p4 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return refcount::ref< internal::func_lambda_call6< F, P0, P1, P2, P3, P4, P5 > >::make_new( f, p0, p1, p2, p3, p4, p5 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return refcount::ref< internal::func_lambda_call7< F, P0, P1, P2, P3, P4, P5, P6 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return refcount::ref< internal::func_lambda_call8< F, P0, P1, P2, P3, P4, P5, P6, P7 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return refcount::ref< internal::func_lambda_call9< F, P0, P1, P2, P3, P4, P5, P6, P7, P8 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7, p8 );
	}

template< typename F, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( F f, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return refcount::ref< internal::func_lambda_call10< F, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
	}

#endif /* defined(_MSC_VER) && _MSC_VER >= 1600 */


// cdeclcall

template< typename R > 
refcount::ref<func_call> make_func_call( R (*f)() ) 
	{ 
	return refcount::ref<internal::func_cdecl_call0< R > >::make_new( f );
	}

template< typename R, typename P0 > 
refcount::ref<func_call> make_func_call( R (*f)( P0 ), P0 p0 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call1< R, P0 > >::make_new( f, p0 );
	}

template< typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1 ), P0 p0, P1 p1 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call2< R, P0, P1 > >::make_new( f, p0, p1 );
	}

template< typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call3< R, P0, P1, P2 > >::make_new( f, p0, p1, p2 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call4< R, P0, P1, P2, P3 > >::make_new( f, p0, p1, p2, p3 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call5< R, P0, P1, P2, P3, P4 > >::make_new( f, p0, p1, p2, p3, p4 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call6< R, P0, P1, P2, P3, P4, P5 > >::make_new( f, p0, p1, p2, p3, p4, p5 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call7< R, P0, P1, P2, P3, P4, P5, P6 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call8< R, P0, P1, P2, P3, P4, P5, P6, P7 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call9< R, P0, P1, P2, P3, P4, P5, P6, P7, P8 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7, p8 );
	}

template< typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( R (*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return refcount::ref< internal::func_cdecl_call10< R, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 > >::make_new( f, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 );
	}


// thiscall

template< typename T, typename R > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)() ) 
	{ 
	return refcount::ref< internal::func_this_call0< T, R > >::make_new( t, f ); 
	}

template< typename T, typename R, typename P0 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0 ), P0 p0 ) 
	{ 
	return refcount::ref< internal::func_this_call1< T, R, P0 > >::make_new( t, f, p0 ); 
	}

template< typename T, typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1 ), P0 p0, P1 p1 ) 
	{ 
	return refcount::ref< internal::func_this_call2< T, R, P0, P1 > >::make_new( t, f, p0, p1 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ) 
	{ 
	return refcount::ref< internal::func_this_call3< T, R, P0, P1, P2 > >::make_new( t, f, p0, p1, p2 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return refcount::ref< internal::func_this_call4< T, R, P0, P1, P2, P3 > >::make_new( t, f, p0, p1, p2, p3 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return refcount::ref< internal::func_this_call5< T, R, P0, P1, P2, P3, P4 > >::make_new( t, f, p0, p1, p2, p3, p4 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return refcount::ref< internal::func_this_call6< T, R, P0, P1, P2, P3, P4, P5 > >::make_new( t, f, p0, p1, p2, p3, p4, p5 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return refcount::ref< internal::func_this_call7< T, R, P0, P1, P2, P3, P4, P5, P6 > >::make_new( t, f, p0, p1, p2, p3, p4, p5, p6 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return refcount::ref< internal::func_this_call8< T, R, P0, P1, P2, P3, P4, P5, P6, P7 > >::make_new( t, f, p0, p1, p2, p3, p4, p5, p6, p7 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return refcount::ref< internal::func_this_call9< T, R, P0, P1, P2, P3, P4, P5, P6, P7, P8 > >::make_new( t, f, p0, p1, p2, p3, p4, p5, p6, p7, p8 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( T* t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return refcount::ref< internal::func_this_call10< T, R, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 > >::make_new( t, f, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); 
	}


// thiscall refcount::ref

template< typename T, typename R > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)() ) 
	{ 
	return refcount::ref< internal::func_this_call0< T, R > >::make_new( (T*) t, f ); 
	}

template< typename T, typename R, typename P0 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0 ), P0 p0 ) 
	{ 
	return refcount::ref< internal::func_this_call1< T, R, P0 > >::make_new( (T*) t, f, p0 ); 
	}

template< typename T, typename R, typename P0, typename P1 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1 ), P0 p0, P1 p1 ) 
	{ 
	return refcount::ref< internal::func_this_call2< T, R, P0, P1 > >::make_new( (T*) t, f, p0, p1 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2 ), P0 p0, P1 p1, P2 p2 ) 
	{ 
	return refcount::ref< internal::func_this_call3< T, R, P0, P1, P2 > >::make_new( (T*) t, f, p0, p1, p2 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3 ), P0 p0, P1 p1, P2 p2, P3 p3 ) 
	{ 
	return refcount::ref< internal::func_this_call4< T, R, P0, P1, P2, P3 > >::make_new( (T*) t, f, p0, p1, p2, p3 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4 ) 
	{ 
	return refcount::ref< internal::func_this_call5< T, R, P0, P1, P2, P3, P4 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) 
	{ 
	return refcount::ref< internal::func_this_call6< T, R, P0, P1, P2, P3, P4, P5 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4, p5 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) 
	{ 
	return refcount::ref< internal::func_this_call7< T, R, P0, P1, P2, P3, P4, P5, P6 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4, p5, p6 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) 
	{ 
	return refcount::ref< internal::func_this_call8< T, R, P0, P1, P2, P3, P4, P5, P6, P7 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4, p5, p6, p7 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) 
	{ 
	return refcount::ref< internal::func_this_call9< T, R, P0, P1, P2, P3, P4, P5, P6, P7, P8 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4, p5, p6, p7, p8 ); 
	}

template< typename T, typename R, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 > 
refcount::ref<func_call> make_func_call( refcount::ref<T> const& t, R (T::*f)( P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 ), P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9 ) 
	{ 
	return refcount::ref< internal::func_this_call10< T, R, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 > >::make_new( (T*) t, f, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9 ); 
	}

} /* namespace funccall */

#endif /* funccall_impl */

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
