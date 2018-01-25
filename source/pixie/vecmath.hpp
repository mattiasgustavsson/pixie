/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

vecmath.hpp - v0.1 - simple HLSL style vector math library for C++.
*/

#ifndef vecmath_hpp
#define vecmath_hpp

#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

namespace vecmath {

// POD types

struct float2_t { float x, y; };
struct float3_t { float x, y, z; };
struct float4_t { float x, y, z, w; };
struct float2x2_t { /* rows */ float2_t x, y; };
struct float2x3_t { /* rows */ float3_t x, y, z; };
struct float3x2_t { /* rows */ float2_t x, y, z; };
struct float3x3_t { /* rows */ float3_t x, y, z; };
struct float2x4_t { /* rows */ float4_t x, y; };
struct float3x4_t { /* rows */ float4_t x, y, z; };
struct float4x2_t { /* rows */ float2_t x, y, z, w; };
struct float4x3_t { /* rows */ float3_t x, y, z, w; };
struct float4x4_t { /* rows */ float4_t x, y, z, w; };


// swizzling helpers

struct swizzle2
	{
	inline swizzle2( float& xr, float& yg ) : x( xr ), y( yg ) {}
	inline swizzle2& operator=( struct float2 const& v );
	inline swizzle2& operator=( swizzle2 const& v );
	inline swizzle2& operator=( float s ) { x = s; y = s; return *this; }
	inline float& operator[]( int index ) { return *( (float**) this )[ index ]; }
	inline operator float2_t() { float2_t r = { x, y }; return r; }

	float& x;
	float& y;
	};

struct swizzle3
	{
	inline swizzle3( float& xr, float& yg, float& zb ) : x( xr ), y( yg ), z( zb ) {}
	inline swizzle3& operator=( struct float3 const& v );
	inline swizzle3& operator=( swizzle3 const& v );
	inline swizzle3& operator=( float s ) { x = s; y = s; z = s; return *this; }
	inline float& operator[]( int index ) { return *( (float**) this )[ index ]; }
	inline operator float3_t() { float3_t r = { x, y, z }; return r; }

	float& x;
	float& y;
	float& z;
	};

struct swizzle4
	{
	inline swizzle4( float& xr, float& yg, float& zb, float& wa ) : x( xr ), y( yg ), z( zb ), w( wa ) {}
	inline swizzle4& operator=( struct float4 const& v );
	inline swizzle4& operator=( swizzle4 const& v );
	inline swizzle4& operator=( float s ) { x = s; y = s; z = s; w = s; return *this; }
	inline float& operator[]( int index ) { return *( (float**) this )[ index ]; }
	inline operator float4_t() { float4_t r = { x, y, z, w }; return r; }

	float& x;
	float& y;
	float& z;
	float& w;
	};


// internal math functions
namespace internal { 
float acosf( float ); float asinf( float ); float atanf( float ); float atan2f( float, float ); float ceilf( float ); 
float cosf( float ); float coshf( float ); float expf( float ); float fabsf( float ); float floorf( float ); 
float fmodf( float, float ); float ldexpf( float, int ); float logf( float ); float log2f( float ); float log10f( float ); 
float modff( float, float* ); float powf( float, float ); float roundf( float ); float sqrtf( float ); float sinf( float ); 
float sinhf( float ); float tanf( float ); float tanhf( float ); float truncf( float );
} /* namespace internal */


// functions
inline float abs( float v ) { return float( internal::fabsf( v ) ); }
inline float acos( float v ) { return float( internal::acosf( v ) ); }
inline bool all( float v ) { return v != 0.0f; }
inline bool any( float v ) { return v != 0.0f; }
inline float asin( float v ) { return float( internal::asinf( v ) ); }
inline float atan( float v ) { return float( internal::atanf( v ) ); }
inline float atan2( float y, float x ) { return float( internal::atan2f( y, x ) ); }
inline float ceil( float v ) { return float( internal::ceilf( v ) ); }
inline float clamp( float v, float min, float max ) { return float( v < min ? min : v > max ? max : v ); }
inline float cos( float v ) { return float( internal::cosf( v ) ); }
inline float cosh( float v ) { return float( internal::coshf( v ) ); }
inline float degrees( float v ) { float const f = 57.295779513082320876846364344191f; return float( v * f ); } 
inline float distancesq( float a, float b ) { float x = b - a; return x * x; }
inline float distance( float a, float b ) { float x = b - a; return internal::sqrtf( x * x ); }
inline float dot( float a, float b ) { return a * b;  }
inline float exp( float v ) { return float( internal::expf( v ) ); }
inline float exp2( float v ) { return float( internal::powf( 2.0f, v ) ); }
inline float floor( float v ) { return float( internal::floorf( v ) ); }
inline float fmod( float a, float b ) { return float( internal::fmodf( a, b ) ); }
inline float frac( float v ) { float t; return float( internal::fabsf( internal::modff( v, &t ) ) ); }
inline float lengthsq( float v ) { return v * v; }
inline float length( float v ) { return internal::sqrtf( v * v ); }
inline float lerp( float a, float b, float s ) { return float( a + ( b - a ) * s ); }
inline float log( float v ) { return float( internal::logf( v ) ); }
inline float log2( float v ) { return float( internal::log2f( v ) ); return v; }
inline float log10( float v ) { return float( internal::log10f( v ) ); }
inline float mad( float a, float b, float c ) { return a * b + c; }
inline float max( float a, float b ) { return float( a > b ? a : b ); }
inline float min( float a, float b ) { return float( a < b ? a : b ); }
inline float normalize( float v ) { float l = internal::sqrtf( v * v ); return l == 0.0f ? v : float( v / l ); }
inline float pow( float a, float b ) { return float( internal::powf( a, b ) ); }
inline float radians( float v ) { float const f = 0.01745329251994329576922222222222f; return float( v * f ); } 
inline float rcp( float v ) { return float( 1.0f / v ); }
inline float reflect( float i, float n ) {  return i - 2.0f * n * dot( i, n ); }
inline float refract( float i, float n, float r ) { float n_i = dot( n, i ); float k = 1.0f - r * r * ( 1.0f - n_i * n_i ); return ( k < 0.0f ) ? float( 0.0f ) : ( r * i - ( r * n_i + internal::sqrtf( k ) ) * n ); }
inline float round( float v ) { return float( internal::roundf( v ) ); }
inline float rsqrt( float v ) { return float( 1.0f / internal::sqrtf( v ) ); }
inline float saturate( float v ) { return float( v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v ); }
inline float sign( float v ) { return float( v < 0.0f ? -1.0f : v > 0.0f ? 1.0f : 0.0f ); }
inline float sin( float v ) { return float( internal::sinf( v ) ); }
inline float sinh( float v ) { return float( internal::sinhf( v ) ); }
inline float smoothstep( float min, float max, float v ) { v = ( v - min ) / ( max - min ); v = float( v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v ); return float( v * v * ( 3.0f - 2.0f * v ) ); }
inline float smootherstep( float min, float max, float v ) { v = ( v - min ) / ( max - min ); v = float( v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v ); return float( v * v * v * ( v * ( v * 6.0f - 15.0f ) + 10.0f ) ); }
inline float sqrt( float v ) { return float( internal::sqrtf( v ) ); }
inline float step( float a, float b ) { return float( b >= a ? 1.0f : 0.0f ); }
inline float tan( float v ) { return float( internal::tanf( v ) ); }
inline float tanh( float v ) { return float( internal::tanhf( v ) ); }
inline float trunc( float v ) { return float( internal::truncf( v ) ); }


struct float2
	{
	float x;
	float y;

	// constructors
	inline float2() { }
	inline float2( float f ) : x( f ), y( f )  { }
	inline explicit float2( float f[2] ) : x( f[0] ), y( f[1] ) { }
	inline float2( float xr, float yg ) : x( xr ), y( yg ) { }
	inline float2( swizzle2 s ) : x( s.x ), y( s.y ) { }
	
	// conversions
	inline float2( float2_t v ) : x( v.x ), y( v.y ) { }
	inline operator float2_t() const { float2_t v = { x, y }; return v; };

	// indexing
	inline float& operator[]( int index ) { return ( (float*) this )[ index ]; }
	inline const float& operator[]( int index ) const { return ( (float*) this )[ index ]; }
	
	// aliases
	inline float& r() { return x; }
	inline float& g() { return y; }

	// swizzling permutations: v.rg(), v.xwzz() etc.
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a, b ); }
	S(x,x); S(x,y); S(y,x); S(y,y);  
	#undef S	
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a(), b() ); }
	S(r,r); S(r,g); S(g,r); S(g,g);  
	#undef S	
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a, b, c ); }
	S(x,x,x); S(x,x,y); S(x,y,x); S(x,y,y);  
	S(y,x,x); S(y,x,y); S(y,y,x); S(y,y,y);  
	#undef S	
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a(), b(), c() ); }
	S(r,r,r); S(r,r,g); S(r,g,r); S(r,g,g);  
	S(g,r,r); S(g,r,g); S(g,g,r); S(g,g,g);  
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a, b, c, d ); }
	S(x,x,x,x); S(x,x,x,y); S(x,x,y,x); S(x,x,y,y);
	S(x,y,x,x); S(x,y,x,y); S(x,y,y,x); S(x,y,y,y);
	S(y,x,x,x); S(y,x,x,y); S(y,x,y,x); S(y,x,y,y);
	S(y,y,x,x); S(y,y,x,y); S(y,y,y,x); S(y,y,y,y);
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a(), b(), c(), d() ); }
	S(r,r,r,r); S(r,r,r,g); S(r,r,g,r); S(r,r,g,g);
	S(r,g,r,r); S(r,g,r,g); S(r,g,g,r); S(r,g,g,g);
	S(g,r,r,r); S(g,r,r,g); S(g,r,g,r); S(g,r,g,g);
	S(g,g,r,r); S(g,g,r,g); S(g,g,g,r); S(g,g,g,g);
	#undef S
	};

// operators
inline float2 operator-( float2 v ) { return float2( -v.x, -v.y ); }
inline bool operator==( float2 a, float2 b ) { return a.x == b.x && a.y == b.y; }
inline bool operator!=( float2 a, float2 b ) { return a.x != b.x || a.y != b.y; }
inline float2& operator+=( float2& a, float2 b ) { a.x += b.x; a.y += b.y; return a; };
inline float2& operator-=( float2& a, float2 b ) { a.x -= b.x; a.y -= b.y; return a; };
inline float2& operator*=( float2& a, float2 b ) { a.x *= b.x; a.y *= b.y; return a; };
inline float2& operator/=( float2& a, float2 b ) { a.x /= b.x; a.y /= b.y; return a; };
inline float2& operator+=( float2& a, float s ) { a.x += s; a.y += s; return a; };
inline float2& operator-=( float2& a, float s ) { a.x -= s; a.y -= s; return a; };
inline float2& operator*=( float2& a, float s ) { a.x *= s; a.y *= s; return a; };
inline float2& operator/=( float2& a, float s ) { a.x /= s; a.y /= s; return a; };
inline float2 operator+( float2 a, float2 b ) { return float2( a.x + b.x, a.y + b.y ); }
inline float2 operator-( float2 a, float2 b ) { return float2( a.x - b.x, a.y - b.y ); }
inline float2 operator*( float2 a, float2 b ) { return float2( a.x * b.x, a.y * b.y ); }
inline float2 operator/( float2 a, float2 b ) { return float2( a.x / b.x, a.y / b.y ); }
inline float2 operator+( float2 a, float b ) { return float2( a.x + b, a.y + b ); }
inline float2 operator-( float2 a, float b ) { return float2( a.x - b, a.y - b ); }
inline float2 operator*( float2 a, float b ) { return float2( a.x * b, a.y * b ); }
inline float2 operator/( float2 a, float b ) { return float2( a.x / b, a.y / b ); }
inline float2 operator+( float a, float2 b ) { return float2( a + b.x, a + b.y ); }
inline float2 operator-( float a, float2 b ) { return float2( a - b.x, a - b.y ); }
inline float2 operator*( float a, float2 b ) { return float2( a * b.x, a * b.y ); }
inline float2 operator/( float a, float2 b ) { return float2( a / b.x, a / b.y ); }

// functions
inline float2 abs( float2 v ) { return float2( abs( v.x ), abs( v.y ) ); }
inline float2 acos( float2 v ) { return float2( acos( v.x ), acos( v.y ) ); }
inline bool all( float2 v ) { return v.x != 0.0f && v.y != 0.0f; }
inline bool any( float2 v ) { return v.x != 0.0f || v.y != 0.0f; }
inline float2 asin( float2 v ) { return float2( asin( v.x ), asin( v.y ) ); }
inline float2 atan( float2 v ) { return float2( atan( v.x ), atan( v.y ) ); }
inline float2 atan2( float2 y, float2 x ) { return float2( atan2( y.x, x.x ), atan2( y.y, x.y ) ); }
inline float2 ceil( float2 v ) { return float2( ceil( v.x ), ceil( v.y ) ); }
inline float2 clamp( float2 v, float2 min, float2 max ) { return float2( clamp( v.x, min.x, max.x ), clamp( v.y, min.y, max.y ) ); }
inline float2 cos( float2 v ) { return float2( cos( v.x ), cos( v.y ) ); }
inline float2 cosh( float2 v ) { return float2( cosh( v.x ), cosh( v.y ) ); }
inline float2 degrees( float2 v ) { return float2( degrees( v.x ), degrees( v.y ) ); } 
inline float distancesq( float2 a, float2 b ) { float x = b.x - a.x; float y = b.y - a.y; return x * x + y * y; }
inline float distance( float2 a, float2 b ) { float x = b.x - a.x; float y = b.y - a.y; return sqrt( x * x + y * y ); }
inline float dot( float2 a, float2 b ) { return a.x * b.x + a.y * b.y;  }
inline float2 exp( float2 v ) { return float2( exp( v.x ), exp( v.y ) ); }
inline float2 exp2( float2 v ) { return float2( exp2( v.x ), exp2( v.y ) ); }
inline float2 floor( float2 v ) { return float2( floor( v.x ), floor( v.y ) ); }
inline float2 fmod( float2 a, float2 b ) { return float2( fmod( a.x, b.x ), fmod( a.y, b.y ) ); }
inline float2 frac( float2 v ) { return float2( frac( v.x ), frac( v.y ) ); }
inline float lengthsq( float2 v ) { return v.x * v.x + v.y * v.y; }
inline float length( float2 v ) { return sqrt( v.x * v.x + v.y * v.y ); }
inline float2 lerp( float2 a, float2 b, float s ) { return float2( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ) ); }
inline float2 log( float2 v ) { return float2( log( v.x ), log( v.y ) ); }
inline float2 log2( float2 v ) { return float2( log2( v.x ), log2( v.y ) ); }
inline float2 log10( float2 v ) { return float2( log10( v.x ), log10( v.y ) ); }
inline float2 mad( float2 a, float2 b, float2 c ) { return a * b + c; }
inline float2 max( float2 a, float2 b ) { return float2( max( a.x, b.x ), max( a.y, b.y ) ); }
inline float2 min( float2 a, float2 b ) { return float2( min( a.x, b.x ), min( a.y, b.y ) ); }
inline float2 normalize( float2 v ) { float l = sqrt( v.x * v.x + v.y * v.y ); return l == 0.0f ? v : float2( v.x / l, v.y / l ); }
inline float2 pow( float2 a, float2 b ) { return float2( pow( a.x, b.x ), pow( a.y, b.y ) ); }
inline float2 radians( float2 v ) { return float2( radians( v.x ), radians( v.y ) ); } 
inline float2 rcp( float2 v ) { return float2( rcp( v.x ), rcp( v.y ) ); }
inline float2 reflect( float2 i, float2 n ) {  return i - 2.0f * n * dot( i, n ) ; }
inline float2 refract( float2 i, float2 n, float r ) { float n_i = dot( n, i ); float k = 1.0f - r * r * ( 1.0f - n_i * n_i ); return ( k < 0.0f ) ? float2( 0.0f, 0.0f ) : ( r * i - ( r * n_i + sqrt( k ) ) * n ); }
inline float2 round( float2 v ) { return float2( round( v.x ), round( v.y ) ); }
inline float2 rsqrt( float2 v ) { return float2( rcp( sqrt( v.x ) ), rcp( sqrt( v.y ) ) ); }
inline float2 saturate( float2 v ) { return float2( saturate( v.x ), saturate( v.y ) ); }
inline float2 sign( float2 v ) { return float2( sign( v.x ), sign( v.y ) ); }
inline float2 sin( float2 v ) { return float2( sin( v.x ), sin( v.y ) ); }
inline float2 sinh( float2 v ) { return float2( sinh( v.x ), sinh( v.y ) ); }
inline float2 smoothstep( float2 min, float2 max, float2 v ) { return float2( smoothstep( min.x, max.x, v.x ), smoothstep( min.y, max.y, v.y ) ); }
inline float2 smootherstep( float2 min, float2 max, float2 v ) { return float2( smootherstep( min.x, max.x, v.x ), smootherstep( min.y, max.y, v.y ) ); }
inline float2 sqrt( float2 v ) { return float2( sqrt( v.x ), sqrt( v.y ) ); }
inline float2 step( float2 a, float2 b ) { return float2( step( a.x, b.x ), step( a.y, b.y ) ); }
inline float2 tan( float2 v ) { return float2( tan( v.x ), tan( v.y ) ); }
inline float2 tanh( float2 v ) { return float2( tanh( v.x ), tanh( v.y ) ); }
inline float2 trunc( float2 v ) { return float2( trunc( v.x ), trunc( v.y ) ); }


struct float3
	{
	float x;
	float y;
	float z;

	// constructors
	inline float3() { }
	inline float3( float f ) : x( f ), y( f ), z( f )  { }
	inline explicit float3( float f[3] ) : x( f[0] ), y( f[1] ), z( f[2] ) { }
	inline float3( float xr, float yg, float zb ) : x( xr ), y( yg ), z( zb ) { }
	inline float3( float a, float2 b ) : x( a ), y( b.x ), z( b.y )  { }
	inline float3( float2 a, float b ) : x( a.x ), y( a.y ), z( b )  { }
	inline float3( swizzle3 s ) : x( s.x ), y( s.y ), z( s.z ) { }

	// conversions
	inline float3( float3_t v ) : x( v.x ), y( v.y ), z( v.z ) { }
	inline operator float3_t() const { float3_t v = { x, y, z }; return v; };

	// indexing
	inline float& operator[]( int index ) { return ( (float*) this )[ index ]; }
	inline const float& operator[]( int index ) const { return ( (float*) this )[ index ]; }

	// aliases
	inline float& r() { return x; }
	inline float& g() { return y; }
	inline float& b() { return z; }

	// swizzling permutations: v.rg(), v.xwzz() etc.
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a, b ); }
	S(x,x); S(x,y); S(x,z); S(y,x); S(y,y); S(y,z); S(z,x); S(z,y); S(z,z);  
	#undef S	
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a(), b() ); }
	S(r,r); S(r,g); S(r,b); S(g,r); S(g,g); S(g,b); S(b,r); S(b,g); S(b,b);  
	#undef S	
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a, b, c ); }
	S(x,x,x); S(x,x,y); S(x,x,z); S(x,y,x); S(x,y,y); S(x,y,z); S(x,z,x); S(x,z,y); S(x,z,z); 
	S(y,x,x); S(y,x,y); S(y,x,z); S(y,y,x); S(y,y,y); S(y,y,z); S(y,z,x); S(y,z,y); S(y,z,z); 
	S(z,x,x); S(z,x,y); S(z,x,z); S(z,y,x); S(z,y,y); S(z,y,z); S(z,z,x); S(z,z,y); S(z,z,z); 
	#undef S	
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a(), b(), c() ); }
	S(r,r,r); S(r,r,g); S(r,r,b); S(r,g,r); S(r,g,g); S(r,g,b); S(r,b,r); S(r,b,g); S(r,b,b); 
	S(g,r,r); S(g,r,g); S(g,r,b); S(g,g,r); S(g,g,g); S(g,g,b); S(g,b,r); S(g,b,g); S(g,b,b); 
	S(b,r,r); S(b,r,g); S(b,r,b); S(b,g,r); S(b,g,g); S(b,g,b); S(b,b,r); S(b,b,g); S(b,b,b); 
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a, b, c, d ); }
	S(x,x,x,x); S(x,x,x,y); S(x,x,x,z); S(x,x,y,x); S(x,x,y,y); S(x,x,y,z); S(x,x,z,x); S(x,x,z,y); S(x,x,z,z);
	S(x,y,x,x); S(x,y,x,y); S(x,y,x,z); S(x,y,y,x); S(x,y,y,y); S(x,y,y,z); S(x,y,z,x); S(x,y,z,y); S(x,y,z,z);
	S(x,z,x,x); S(x,z,x,y); S(x,z,x,z); S(x,z,y,x); S(x,z,y,y); S(x,z,y,z); S(x,z,z,x); S(x,z,z,y); S(x,z,z,z);
	S(y,x,x,x); S(y,x,x,y); S(y,x,x,z); S(y,x,y,x); S(y,x,y,y); S(y,x,y,z); S(y,x,z,x); S(y,x,z,y); S(y,x,z,z);
	S(y,y,x,x); S(y,y,x,y); S(y,y,x,z); S(y,y,y,x); S(y,y,y,y); S(y,y,y,z); S(y,y,z,x); S(y,y,z,y); S(y,y,z,z);
	S(y,z,x,x); S(y,z,x,y); S(y,z,x,z); S(y,z,y,x); S(y,z,y,y); S(y,z,y,z); S(y,z,z,x); S(y,z,z,y); S(y,z,z,z);
	S(z,x,x,x); S(z,x,x,y); S(z,x,x,z); S(z,x,y,x); S(z,x,y,y); S(z,x,y,z); S(z,x,z,x); S(z,x,z,y); S(z,x,z,z);
	S(z,y,x,x); S(z,y,x,y); S(z,y,x,z); S(z,y,y,x); S(z,y,y,y); S(z,y,y,z); S(z,y,z,x); S(z,y,z,y); S(z,y,z,z);
	S(z,z,x,x); S(z,z,x,y); S(z,z,x,z); S(z,z,y,x); S(z,z,y,y); S(z,z,y,z); S(z,z,z,x); S(z,z,z,y); S(z,z,z,z);
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a(), b(), c(), d() ); }
	S(r,r,r,r); S(r,r,r,g); S(r,r,r,b); S(r,r,g,r); S(r,r,g,g); S(r,r,g,b); S(r,r,b,r); S(r,r,b,g); S(r,r,b,b);
	S(r,g,r,r); S(r,g,r,g); S(r,g,r,b); S(r,g,g,r); S(r,g,g,g); S(r,g,g,b); S(r,g,b,r); S(r,g,b,g); S(r,g,b,b);
	S(r,b,r,r); S(r,b,r,g); S(r,b,r,b); S(r,b,g,r); S(r,b,g,g); S(r,b,g,b); S(r,b,b,r); S(r,b,b,g); S(r,b,b,b);
	S(g,r,r,r); S(g,r,r,g); S(g,r,r,b); S(g,r,g,r); S(g,r,g,g); S(g,r,g,b); S(g,r,b,r); S(g,r,b,g); S(g,r,b,b);
	S(g,g,r,r); S(g,g,r,g); S(g,g,r,b); S(g,g,g,r); S(g,g,g,g); S(g,g,g,b); S(g,g,b,r); S(g,g,b,g); S(g,g,b,b);
	S(g,b,r,r); S(g,b,r,g); S(g,b,r,b); S(g,b,g,r); S(g,b,g,g); S(g,b,g,b); S(g,b,b,r); S(g,b,b,g); S(g,b,b,b);
	S(b,r,r,r); S(b,r,r,g); S(b,r,r,b); S(b,r,g,r); S(b,r,g,g); S(b,r,g,b); S(b,r,b,r); S(b,r,b,g); S(b,r,b,b);
	S(b,g,r,r); S(b,g,r,g); S(b,g,r,b); S(b,g,g,r); S(b,g,g,g); S(b,g,g,b); S(b,g,b,r); S(b,g,b,g); S(b,g,b,b);
	S(b,b,r,r); S(b,b,r,g); S(b,b,r,b); S(b,b,g,r); S(b,b,g,g); S(b,b,g,b); S(b,b,b,r); S(b,b,b,g); S(b,b,b,b);
	#undef S
	};

// operators
inline float3 operator-( float3 v ) { return float3( -v.x, -v.y, -v.z ); }
inline bool operator==( float3 a, float3 b ) { return a.x == b.x && a.y == b.y && a.z == b.z; }
inline bool operator!=( float3 a, float3 b ) { return a.x != b.x || a.y != b.y || a.z != b.z; }
inline float3& operator+=( float3& a, float3 b ) { a.x += b.x; a.y += b.y; a.z += b.z; return a; };
inline float3& operator-=( float3& a, float3 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; };
inline float3& operator*=( float3& a, float3 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; };
inline float3& operator/=( float3& a, float3 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; };
inline float3& operator+=( float3& a, float s ) { a.x += s; a.y += s; a.z += s; return a; };
inline float3& operator-=( float3& a, float s ) { a.x -= s; a.y -= s; a.z -= s; return a; };
inline float3& operator*=( float3& a, float s ) { a.x *= s; a.y *= s; a.z *= s; return a; };
inline float3& operator/=( float3& a, float s ) { a.x /= s; a.y /= s; a.z /= s; return a; };
inline float3 operator+( float3 a, float3 b ) { return float3( a.x + b.x, a.y + b.y, a.z + b.z ); }
inline float3 operator-( float3 a, float3 b ) { return float3( a.x - b.x, a.y - b.y, a.z - b.z ); }
inline float3 operator*( float3 a, float3 b ) { return float3( a.x * b.x, a.y * b.y, a.z * b.z ); }
inline float3 operator/( float3 a, float3 b ) { return float3( a.x / b.x, a.y / b.y, a.z / b.z ); }
inline float3 operator+( float3 a, float b ) { return float3( a.x + b, a.y + b, a.z + b ); }
inline float3 operator-( float3 a, float b ) { return float3( a.x - b, a.y - b, a.z - b ); }
inline float3 operator*( float3 a, float b ) { return float3( a.x * b, a.y * b, a.z * b ); }
inline float3 operator/( float3 a, float b ) { return float3( a.x / b, a.y / b, a.z / b ); }
inline float3 operator+( float a, float3 b ) { return float3( a + b.x, a + b.y, a + b.z ); }
inline float3 operator-( float a, float3 b ) { return float3( a - b.x, a - b.y, a - b.z ); }
inline float3 operator*( float a, float3 b ) { return float3( a * b.x, a * b.y, a * b.z ); }
inline float3 operator/( float a, float3 b ) { return float3( a / b.x, a / b.y, a / b.z ); }

// functions
inline float3 abs( float3 v ) { return float3( abs( v.x ), abs( v.y ), abs( v.z ) ); }
inline float3 acos( float3 v ) { return float3( acos( v.x ), acos( v.y ), acos( v.z ) ); }
inline bool all( float3 v ) { return v.x != 0.0f && v.y != 0.0f && v.z != 0.0f; }
inline bool any( float3 v ) { return v.x != 0.0f || v.y != 0.0f || v.z != 0.0f; }
inline float3 asin( float3 v ) { return float3( asin( v.x ), asin( v.y ), asin( v.z ) ); }
inline float3 atan( float3 v ) { return float3( atan( v.x ), atan( v.y ), atan( v.z ) ); }
inline float3 atan2( float3 y, float3 x ) { return float3( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ) ); }
inline float3 ceil( float3 v ) { return float3( ceil( v.x ), ceil( v.y ), ceil( v.z ) ); }
inline float3 clamp( float3 v, float3 min, float3 max ) { return float3( clamp( v.x, min.x, max.x ), clamp( v.y, min.y, max.y ), clamp( v.z, min.z, max.z ) ); }
inline float3 cos( float3 v ) { return float3( cos( v.x ), cos( v.y ), cos( v.z ) ); }
inline float3 cosh( float3 v ) { return float3( cosh( v.x ), cosh( v.y ), cosh( v.z ) ); }
inline float3 cross( float3 a, float3 b ) { return float3( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x ); }
inline float3 degrees( float3 v ) { return float3( degrees( v.x ), degrees( v.y ), degrees( v.z ) ); } 
inline float distancesq( float3 a, float3 b ) { float x = b.x - a.x; float y = b.y - a.y; float z = b.z - a.z; return x * x + y * y + z * z; }
inline float distance( float3 a, float3 b ) { float x = b.x - a.x; float y = b.y - a.y; float z = b.z - a.z; return sqrt( x * x + y * y + z * z ); }
inline float dot( float3 a, float3 b ) { return a.x * b.x + a.y * b.y + a.z * b.z;  }
inline float3 exp( float3 v ) { return float3( exp( v.x ), exp( v.y ), exp( v.z ) ); }
inline float3 exp2( float3 v ) { return float3( exp2( v.x ), exp2( v.y ), exp2( v.z ) ); }
inline float3 floor( float3 v ) { return float3( floor( v.x ), floor( v.y ), floor( v.z ) ); }
inline float3 fmod( float3 a, float3 b ) { return float3( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ) ); }
inline float3 frac( float3 v ) { return float3( frac( v.x ), frac( v.y ), frac( v.z ) ); }
inline float lengthsq( float3 v ) { return v.x * v.x + v.y * v.y + v.z * v.z; }
inline float length( float3 v ) { return sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); }
inline float3 lerp( float3 a, float3 b, float s ) { return float3( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ) ); }
inline float3 log( float3 v ) { return float3( log( v.x ), log( v.y ), log( v.z ) ); }
inline float3 log2( float3 v ) { return float3( log2( v.x ), log2( v.y ), log2( v.z ) ); }
inline float3 log10( float3 v ) { return float3( log10( v.x ), log10( v.y ), log10( v.z ) ); }
inline float3 mad( float3 a, float3 b, float3 c ) { return a * b + c; }
inline float3 max( float3 a, float3 b ) { return float3( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ) ); }
inline float3 min( float3 a, float3 b ) { return float3( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ) ); }
inline float3 normalize( float3 v ) { float l = sqrt( v.x * v.x + v.y * v.y + v.z * v.z ); return l == 0.0f ? v : float3( v.x / l, v.y / l, v.z / l ); }
inline float3 pow( float3 a, float3 b ) { return float3( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ) ); }
inline float3 radians( float3 v ) { return float3( radians( v.x ), radians( v.y ), radians( v.z ) ); } 
inline float3 rcp( float3 v ) { return float3( rcp( v.x ), rcp( v.y ), rcp( v.z ) ); }
inline float3 reflect( float3 i, float3 n ) {  return i - 2.0f * n * dot( i, n ) ; }
inline float3 refract( float3 i, float3 n, float r ) { float n_i = dot( n, i ); float k = 1.0f - r * r * ( 1.0f - n_i * n_i ); return ( k < 0.0f ) ? float3( 0.0f, 0.0f, 0.0f ) : ( r * i - ( r * n_i + sqrt( k ) ) * n ); }
inline float3 round( float3 v ) { return float3( round( v.x ), round( v.y ), round( v.z ) ); }
inline float3 rsqrt( float3 v ) { return float3( rcp( sqrt( v.x ) ), rcp( sqrt( v.y ) ), rcp( sqrt( v.z ) ) ); }
inline float3 saturate( float3 v ) { return float3( saturate( v.x ), saturate( v.y ), saturate( v.z ) ); }
inline float3 sign( float3 v ) { return float3( sign( v.x ), sign( v.y ), sign( v.z ) ); }
inline float3 sin( float3 v ) { return float3( sin( v.x ), sin( v.y ), sin( v.z ) ); }
inline float3 sinh( float3 v ) { return float3( sinh( v.x ), sinh( v.y ), sinh( v.z ) ); }
inline float3 smoothstep( float3 min, float3 max, float3 v ) { return float3( smoothstep( min.x, max.x, v.x ), smoothstep( min.y, max.y, v.y ), smoothstep( min.z, max.z, v.z ) ); }
inline float3 smootherstep( float3 min, float3 max, float3 v ) { return float3( smootherstep( min.x, max.x, v.x ), smootherstep( min.y, max.y, v.y ), smootherstep( min.z, max.z, v.z ) ); }
inline float3 sqrt( float3 v ) { return float3( sqrt( v.x ), sqrt( v.y ), sqrt( v.z ) ); }
inline float3 step( float3 a, float3 b ) { return float3( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ) ); }
inline float3 tan( float3 v ) { return float3( tan( v.x ), tan( v.y ), tan( v.z ) ); }
inline float3 tanh( float3 v ) { return float3( tanh( v.x ), tanh( v.y ), tanh( v.z ) ); }
inline float3 trunc( float3 v ) { return float3( trunc( v.x ), trunc( v.y ), trunc( v.z ) ); }


struct float4
	{
	float x;
	float y;
	float z;
	float w;

	// constructors
	inline float4() { }
	inline float4( float f ) : x( f ), y( f ), z( f ), w( f )  { }
	inline explicit float4( float f[4] ) : x( f[0] ), y( f[1] ), z( f[2] ), w( f[3] ) { }
	inline float4( float xr, float yg, float zb, float wa ) : x( xr ), y( yg ), z( zb ), w( wa ) { }
	inline float4( float2 a, float b, float c ) : x( a.x ), y( a.y ), z( b ), w( c )  { }
	inline float4( float a, float2 b, float c ) : x( a ), y( b.x ), z( b.y ), w( c )  { }
	inline float4( float a, float b, float2 c ) : x( a ), y( b ), z( c.x ), w( c.y )  { }
	inline float4( float2 a, float2 b ) : x( a.x ), y( a.y ), z( b.x ), w( b.y )  { }
	inline float4( float a, float3 b ) : x( a ), y( b.x ), z( b.y ), w( b.z )  { }
	inline float4( float3 a, float b ) : x( a.x ), y( a.y ), z( a.z ), w( b )  { }
	inline float4( swizzle4 s ) : x( s.x ), y( s.y ), z( s.z ), w( s.w ) { }

	// conversions
	inline float4( float4_t v ) : x( v.x ), y( v.y ), z( v.z ), w( v.w ) { }
	inline operator float4_t() const { float4_t v = { x, y, z, w }; return v; };

	// indexing
	inline float& operator[]( int index ) { return ( (float*) this )[ index ]; }
	inline const float& operator[]( int index ) const { return ( (float*) this )[ index ]; }

	// aliases
	inline float& r() { return x; }
	inline float& g() { return y; }
	inline float& b() { return z; }
	inline float& a() { return w; }

	// swizzling permutations: v.rg(), v.xwzz() etc.
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a, b ); }
	S(x,x); S(x,y); S(x,z); S(x,w); S(y,x); S(y,y); S(y,z); S(y,w); S(z,x); S(z,y); S(z,z); S(z,w); S(w,x); S(w,y); S(w,z); S(w,w); 
	#undef S	
	#define S( a, b ) inline swizzle2 a##b() { return swizzle2( a(), b() ); }
	S(r,r); S(r,g); S(r,b); S(r,a); S(g,r); S(g,g); S(g,b); S(g,a); S(b,r); S(b,g); S(b,b); S(b,a); S(a,r); S(a,g); S(a,b); S(a,a); 
	#undef S	
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a, b, c ); }
	S(x,x,x); S(x,x,y); S(x,x,z); S(x,x,w); S(x,y,x); S(x,y,y); S(x,y,z); S(x,y,w); S(x,z,x); S(x,z,y); S(x,z,z); S(x,z,w); S(x,w,x); S(x,w,y); S(x,w,z); S(x,w,w);
	S(y,x,x); S(y,x,y); S(y,x,z); S(y,x,w); S(y,y,x); S(y,y,y); S(y,y,z); S(y,y,w); S(y,z,x); S(y,z,y); S(y,z,z); S(y,z,w); S(y,w,x); S(y,w,y); S(y,w,z); S(y,w,w);
	S(z,x,x); S(z,x,y); S(z,x,z); S(z,x,w); S(z,y,x); S(z,y,y); S(z,y,z); S(z,y,w); S(z,z,x); S(z,z,y); S(z,z,z); S(z,z,w); S(z,w,x); S(z,w,y); S(z,w,z); S(z,w,w);
	S(w,x,x); S(w,x,y); S(w,x,z); S(w,x,w); S(w,y,x); S(w,y,y); S(w,y,z); S(w,y,w); S(w,z,x); S(w,z,y); S(w,z,z); S(w,z,w); S(w,w,x); S(w,w,y); S(w,w,z); S(w,w,w);
	#undef S
	#define S( a, b, c ) inline swizzle3 a##b##c() { return swizzle3( a(), b(), c() ); }
	S(r,r,r); S(r,r,g); S(r,r,b); S(r,r,a); S(r,g,r); S(r,g,g); S(r,g,b); S(r,g,a); S(r,b,r); S(r,b,g); S(r,b,b); S(r,b,a); S(r,a,r); S(r,a,g); S(r,a,b); S(r,a,a);
	S(g,r,r); S(g,r,g); S(g,r,b); S(g,r,a); S(g,g,r); S(g,g,g); S(g,g,b); S(g,g,a); S(g,b,r); S(g,b,g); S(g,b,b); S(g,b,a); S(g,a,r); S(g,a,g); S(g,a,b); S(g,a,a);
	S(b,r,r); S(b,r,g); S(b,r,b); S(b,r,a); S(b,g,r); S(b,g,g); S(b,g,b); S(b,g,a); S(b,b,r); S(b,b,g); S(b,b,b); S(b,b,a); S(b,a,r); S(b,a,g); S(b,a,b); S(b,a,a);
	S(a,r,r); S(a,r,g); S(a,r,b); S(a,r,a); S(a,g,r); S(a,g,g); S(a,g,b); S(a,g,a); S(a,b,r); S(a,b,g); S(a,b,b); S(a,b,a); S(a,a,r); S(a,a,g); S(a,a,b); S(a,a,a);
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a, b, c, d ); }
	S(x,x,x,x); S(x,x,x,y); S(x,x,x,z); S(x,x,x,w); S(x,x,y,x); S(x,x,y,y); S(x,x,y,z); S(x,x,y,w); S(x,x,z,x); S(x,x,z,y); S(x,x,z,z); S(x,x,z,w); S(x,x,w,x); S(x,x,w,y); S(x,x,w,z); S(x,x,w,w);
	S(x,y,x,x); S(x,y,x,y); S(x,y,x,z); S(x,y,x,w); S(x,y,y,x); S(x,y,y,y); S(x,y,y,z); S(x,y,y,w); S(x,y,z,x); S(x,y,z,y); S(x,y,z,z); S(x,y,z,w); S(x,y,w,x); S(x,y,w,y); S(x,y,w,z); S(x,y,w,w);
	S(x,z,x,x); S(x,z,x,y); S(x,z,x,z); S(x,z,x,w); S(x,z,y,x); S(x,z,y,y); S(x,z,y,z); S(x,z,y,w); S(x,z,z,x); S(x,z,z,y); S(x,z,z,z); S(x,z,z,w); S(x,z,w,x); S(x,z,w,y); S(x,z,w,z); S(x,z,w,w);
	S(x,w,x,x); S(x,w,x,y); S(x,w,x,z); S(x,w,x,w); S(x,w,y,x); S(x,w,y,y); S(x,w,y,z); S(x,w,y,w); S(x,w,z,x); S(x,w,z,y); S(x,w,z,z); S(x,w,z,w); S(x,w,w,x); S(x,w,w,y); S(x,w,w,z); S(x,w,w,w);
	S(y,x,x,x); S(y,x,x,y); S(y,x,x,z); S(y,x,x,w); S(y,x,y,x); S(y,x,y,y); S(y,x,y,z); S(y,x,y,w); S(y,x,z,x); S(y,x,z,y); S(y,x,z,z); S(y,x,z,w); S(y,x,w,x); S(y,x,w,y); S(y,x,w,z); S(y,x,w,w);
	S(y,y,x,x); S(y,y,x,y); S(y,y,x,z); S(y,y,x,w); S(y,y,y,x); S(y,y,y,y); S(y,y,y,z); S(y,y,y,w); S(y,y,z,x); S(y,y,z,y); S(y,y,z,z); S(y,y,z,w); S(y,y,w,x); S(y,y,w,y); S(y,y,w,z); S(y,y,w,w);
	S(y,z,x,x); S(y,z,x,y); S(y,z,x,z); S(y,z,x,w); S(y,z,y,x); S(y,z,y,y); S(y,z,y,z); S(y,z,y,w); S(y,z,z,x); S(y,z,z,y); S(y,z,z,z); S(y,z,z,w); S(y,z,w,x); S(y,z,w,y); S(y,z,w,z); S(y,z,w,w);
	S(y,w,x,x); S(y,w,x,y); S(y,w,x,z); S(y,w,x,w); S(y,w,y,x); S(y,w,y,y); S(y,w,y,z); S(y,w,y,w); S(y,w,z,x); S(y,w,z,y); S(y,w,z,z); S(y,w,z,w); S(y,w,w,x); S(y,w,w,y); S(y,w,w,z); S(y,w,w,w);
	S(z,x,x,x); S(z,x,x,y); S(z,x,x,z); S(z,x,x,w); S(z,x,y,x); S(z,x,y,y); S(z,x,y,z); S(z,x,y,w); S(z,x,z,x); S(z,x,z,y); S(z,x,z,z); S(z,x,z,w); S(z,x,w,x); S(z,x,w,y); S(z,x,w,z); S(z,x,w,w);
	S(z,y,x,x); S(z,y,x,y); S(z,y,x,z); S(z,y,x,w); S(z,y,y,x); S(z,y,y,y); S(z,y,y,z); S(z,y,y,w); S(z,y,z,x); S(z,y,z,y); S(z,y,z,z); S(z,y,z,w); S(z,y,w,x); S(z,y,w,y); S(z,y,w,z); S(z,y,w,w);
	S(z,z,x,x); S(z,z,x,y); S(z,z,x,z); S(z,z,x,w); S(z,z,y,x); S(z,z,y,y); S(z,z,y,z); S(z,z,y,w); S(z,z,z,x); S(z,z,z,y); S(z,z,z,z); S(z,z,z,w); S(z,z,w,x); S(z,z,w,y); S(z,z,w,z); S(z,z,w,w);
	S(z,w,x,x); S(z,w,x,y); S(z,w,x,z); S(z,w,x,w); S(z,w,y,x); S(z,w,y,y); S(z,w,y,z); S(z,w,y,w); S(z,w,z,x); S(z,w,z,y); S(z,w,z,z); S(z,w,z,w); S(z,w,w,x); S(z,w,w,y); S(z,w,w,z); S(z,w,w,w);
	S(w,x,x,x); S(w,x,x,y); S(w,x,x,z); S(w,x,x,w); S(w,x,y,x); S(w,x,y,y); S(w,x,y,z); S(w,x,y,w); S(w,x,z,x); S(w,x,z,y); S(w,x,z,z); S(w,x,z,w); S(w,x,w,x); S(w,x,w,y); S(w,x,w,z); S(w,x,w,w);
	S(w,y,x,x); S(w,y,x,y); S(w,y,x,z); S(w,y,x,w); S(w,y,y,x); S(w,y,y,y); S(w,y,y,z); S(w,y,y,w); S(w,y,z,x); S(w,y,z,y); S(w,y,z,z); S(w,y,z,w); S(w,y,w,x); S(w,y,w,y); S(w,y,w,z); S(w,y,w,w);
	S(w,z,x,x); S(w,z,x,y); S(w,z,x,z); S(w,z,x,w); S(w,z,y,x); S(w,z,y,y); S(w,z,y,z); S(w,z,y,w); S(w,z,z,x); S(w,z,z,y); S(w,z,z,z); S(w,z,z,w); S(w,z,w,x); S(w,z,w,y); S(w,z,w,z); S(w,z,w,w);
	S(w,w,x,x); S(w,w,x,y); S(w,w,x,z); S(w,w,x,w); S(w,w,y,x); S(w,w,y,y); S(w,w,y,z); S(w,w,y,w); S(w,w,z,x); S(w,w,z,y); S(w,w,z,z); S(w,w,z,w); S(w,w,w,x); S(w,w,w,y); S(w,w,w,z); S(w,w,w,w);
	#undef S
	#define S( a, b, c, d ) inline swizzle4 a##b##c##d() { return swizzle4( a(), b(), c(), d() ); }
	S(r,r,r,r); S(r,r,r,g); S(r,r,r,b); S(r,r,r,a); S(r,r,g,r); S(r,r,g,g); S(r,r,g,b); S(r,r,g,a); S(r,r,b,r); S(r,r,b,g); S(r,r,b,b); S(r,r,b,a); S(r,r,a,r); S(r,r,a,g); S(r,r,a,b); S(r,r,a,a);
	S(r,g,r,r); S(r,g,r,g); S(r,g,r,b); S(r,g,r,a); S(r,g,g,r); S(r,g,g,g); S(r,g,g,b); S(r,g,g,a); S(r,g,b,r); S(r,g,b,g); S(r,g,b,b); S(r,g,b,a); S(r,g,a,r); S(r,g,a,g); S(r,g,a,b); S(r,g,a,a);
	S(r,b,r,r); S(r,b,r,g); S(r,b,r,b); S(r,b,r,a); S(r,b,g,r); S(r,b,g,g); S(r,b,g,b); S(r,b,g,a); S(r,b,b,r); S(r,b,b,g); S(r,b,b,b); S(r,b,b,a); S(r,b,a,r); S(r,b,a,g); S(r,b,a,b); S(r,b,a,a);
	S(r,a,r,r); S(r,a,r,g); S(r,a,r,b); S(r,a,r,a); S(r,a,g,r); S(r,a,g,g); S(r,a,g,b); S(r,a,g,a); S(r,a,b,r); S(r,a,b,g); S(r,a,b,b); S(r,a,b,a); S(r,a,a,r); S(r,a,a,g); S(r,a,a,b); S(r,a,a,a);
	S(g,r,r,r); S(g,r,r,g); S(g,r,r,b); S(g,r,r,a); S(g,r,g,r); S(g,r,g,g); S(g,r,g,b); S(g,r,g,a); S(g,r,b,r); S(g,r,b,g); S(g,r,b,b); S(g,r,b,a); S(g,r,a,r); S(g,r,a,g); S(g,r,a,b); S(g,r,a,a);
	S(g,g,r,r); S(g,g,r,g); S(g,g,r,b); S(g,g,r,a); S(g,g,g,r); S(g,g,g,g); S(g,g,g,b); S(g,g,g,a); S(g,g,b,r); S(g,g,b,g); S(g,g,b,b); S(g,g,b,a); S(g,g,a,r); S(g,g,a,g); S(g,g,a,b); S(g,g,a,a);
	S(g,b,r,r); S(g,b,r,g); S(g,b,r,b); S(g,b,r,a); S(g,b,g,r); S(g,b,g,g); S(g,b,g,b); S(g,b,g,a); S(g,b,b,r); S(g,b,b,g); S(g,b,b,b); S(g,b,b,a); S(g,b,a,r); S(g,b,a,g); S(g,b,a,b); S(g,b,a,a);
	S(g,a,r,r); S(g,a,r,g); S(g,a,r,b); S(g,a,r,a); S(g,a,g,r); S(g,a,g,g); S(g,a,g,b); S(g,a,g,a); S(g,a,b,r); S(g,a,b,g); S(g,a,b,b); S(g,a,b,a); S(g,a,a,r); S(g,a,a,g); S(g,a,a,b); S(g,a,a,a);
	S(b,r,r,r); S(b,r,r,g); S(b,r,r,b); S(b,r,r,a); S(b,r,g,r); S(b,r,g,g); S(b,r,g,b); S(b,r,g,a); S(b,r,b,r); S(b,r,b,g); S(b,r,b,b); S(b,r,b,a); S(b,r,a,r); S(b,r,a,g); S(b,r,a,b); S(b,r,a,a);
	S(b,g,r,r); S(b,g,r,g); S(b,g,r,b); S(b,g,r,a); S(b,g,g,r); S(b,g,g,g); S(b,g,g,b); S(b,g,g,a); S(b,g,b,r); S(b,g,b,g); S(b,g,b,b); S(b,g,b,a); S(b,g,a,r); S(b,g,a,g); S(b,g,a,b); S(b,g,a,a);
	S(b,b,r,r); S(b,b,r,g); S(b,b,r,b); S(b,b,r,a); S(b,b,g,r); S(b,b,g,g); S(b,b,g,b); S(b,b,g,a); S(b,b,b,r); S(b,b,b,g); S(b,b,b,b); S(b,b,b,a); S(b,b,a,r); S(b,b,a,g); S(b,b,a,b); S(b,b,a,a);
	S(b,a,r,r); S(b,a,r,g); S(b,a,r,b); S(b,a,r,a); S(b,a,g,r); S(b,a,g,g); S(b,a,g,b); S(b,a,g,a); S(b,a,b,r); S(b,a,b,g); S(b,a,b,b); S(b,a,b,a); S(b,a,a,r); S(b,a,a,g); S(b,a,a,b); S(b,a,a,a);
	S(a,r,r,r); S(a,r,r,g); S(a,r,r,b); S(a,r,r,a); S(a,r,g,r); S(a,r,g,g); S(a,r,g,b); S(a,r,g,a); S(a,r,b,r); S(a,r,b,g); S(a,r,b,b); S(a,r,b,a); S(a,r,a,r); S(a,r,a,g); S(a,r,a,b); S(a,r,a,a);
	S(a,g,r,r); S(a,g,r,g); S(a,g,r,b); S(a,g,r,a); S(a,g,g,r); S(a,g,g,g); S(a,g,g,b); S(a,g,g,a); S(a,g,b,r); S(a,g,b,g); S(a,g,b,b); S(a,g,b,a); S(a,g,a,r); S(a,g,a,g); S(a,g,a,b); S(a,g,a,a);
	S(a,b,r,r); S(a,b,r,g); S(a,b,r,b); S(a,b,r,a); S(a,b,g,r); S(a,b,g,g); S(a,b,g,b); S(a,b,g,a); S(a,b,b,r); S(a,b,b,g); S(a,b,b,b); S(a,b,b,a); S(a,b,a,r); S(a,b,a,g); S(a,b,a,b); S(a,b,a,a);
	S(a,a,r,r); S(a,a,r,g); S(a,a,r,b); S(a,a,r,a); S(a,a,g,r); S(a,a,g,g); S(a,a,g,b); S(a,a,g,a); S(a,a,b,r); S(a,a,b,g); S(a,a,b,b); S(a,a,b,a); S(a,a,a,r); S(a,a,a,g); S(a,a,a,b); S(a,a,a,a);
	#undef S
	};

// operators
inline float4 operator-( float4 v ) { return float4( -v.x, -v.y, -v.z, -v.w ); }
inline bool operator==( float4 a, float4 b ) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
inline bool operator!=( float4 a, float4 b ) { return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w; }
inline float4& operator+=( float4& a, float4 b ) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; };
inline float4& operator-=( float4& a, float4 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; };
inline float4& operator*=( float4& a, float4 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; };
inline float4& operator/=( float4& a, float4 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; };
inline float4& operator+=( float4& a, float s ) { a.x += s; a.y += s; a.z += s; a.w += s; return a; };
inline float4& operator-=( float4& a, float s ) { a.x -= s; a.y -= s; a.z -= s; a.w -= s; return a; };
inline float4& operator*=( float4& a, float s ) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; };
inline float4& operator/=( float4& a, float s ) { a.x /= s; a.y /= s; a.z /= s; a.w /= s; return a; };
inline float4 operator+( float4 a, float4 b ) { return float4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }
inline float4 operator-( float4 a, float4 b ) { return float4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }
inline float4 operator*( float4 a, float4 b ) { return float4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w ); }
inline float4 operator/( float4 a, float4 b ) { return float4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w ); }
inline float4 operator+( float4 a, float b ) { return float4( a.x + b, a.y + b, a.z + b, a.w + b ); }
inline float4 operator-( float4 a, float b ) { return float4( a.x - b, a.y - b, a.z - b, a.w - b ); }
inline float4 operator*( float4 a, float b ) { return float4( a.x * b, a.y * b, a.z * b, a.w * b ); }
inline float4 operator/( float4 a, float b ) { return float4( a.x / b, a.y / b, a.z / b, a.w / b ); }
inline float4 operator+( float a, float4 b ) { return float4( a + b.x, a + b.y, a + b.z, a + b.w ); }
inline float4 operator-( float a, float4 b ) { return float4( a - b.x, a - b.y, a - b.z, a - b.w ); }
inline float4 operator*( float a, float4 b ) { return float4( a * b.x, a * b.y, a * b.z, a * b.w ); }
inline float4 operator/( float a, float4 b ) { return float4( a / b.x, a / b.y, a / b.z, a / b.w ); }

// functions
inline float4 abs( float4 v ) { return float4( abs( v.x ), abs( v.y ), abs( v.z ), abs( v.w ) ); }
inline float4 acos( float4 v ) { return float4( acos( v.x ), acos( v.y ), acos( v.z ), acos( v.w ) ); }
inline bool all( float4 v ) { return v.x != 0.0f && v.y != 0.0f && v.z != 0.0f && v.w != 0.0f; }
inline bool any( float4 v ) { return v.x != 0.0f || v.y != 0.0f || v.z != 0.0f || v.w != 0.0f; }
inline float4 asin( float4 v ) { return float4( asin( v.x ), asin( v.y ), asin( v.z ), asin( v.w ) ); }
inline float4 atan( float4 v ) { return float4( atan( v.x ), atan( v.y ), atan( v.z ), atan( v.w ) ); }
inline float4 atan2( float4 y, float4 x ) { return float4( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ), atan2( y.w, x.w ) ); }
inline float4 ceil( float4 v ) { return float4( ceil( v.x ), ceil( v.y ), ceil( v.z ), ceil( v.w ) ); }
inline float4 clamp( float4 v, float4 min, float4 max ) { return float4( clamp( v.x, min.x, max.x ), clamp( v.y, min.y, max.y ), clamp( v.z, min.z, max.z ), clamp( v.w, min.w, max.w ) ); }
inline float4 cos( float4 v ) { return float4( cos( v.x ), cos( v.y ), cos( v.z ), cos( v.w ) ); }
inline float4 cosh( float4 v ) { return float4( cosh( v.x ), cosh( v.y ), cosh( v.z ), cosh( v.w ) ); }
inline float4 degrees( float4 v ) { return float4( degrees( v.x ), degrees( v.y ), degrees( v.z ), degrees( v.w ) ); } 
inline float distancesq( float4 a, float4 b ) { float x = b.x - a.x; float y = b.y - a.y; float z = b.z - a.z; float w = b.w - a.w; return x * x + y * y + z * z + w * w; }
inline float distance( float4 a, float4 b ) { float x = b.x - a.x; float y = b.y - a.y; float z = b.z - a.z; float w = b.w - a.w; return sqrt( x * x + y * y + z * z + w * w ); }
inline float dot( float4 a, float4 b ) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;  }
inline float4 exp( float4 v ) { return float4( exp( v.x ), exp( v.y ), exp( v.z ), exp( v.w ) ); }
inline float4 exp2( float4 v ) { return float4( exp2( v.x ), exp2( v.y ), exp2( v.z ), exp2( v.w ) ); }
inline float4 floor( float4 v ) { return float4( floor( v.x ), floor( v.y ), floor( v.z ), floor( v.w ) ); }
inline float4 fmod( float4 a, float4 b ) { return float4( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ), fmod( a.w, b.w ) ); }
inline float4 frac( float4 v ) { return float4( frac( v.x ), frac( v.y ), frac( v.z ), frac( v.w ) ); }
inline float lengthsq( float4 v ) { return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w; }
inline float length( float4 v ) { return sqrt( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w ); }
inline float4 lerp( float4 a, float4 b, float s ) { return float4( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ), lerp( a.w, b.w, s ) ); }
inline float4 log( float4 v ) { return float4( log( v.x ), log( v.y ), log( v.z ), log( v.w ) ); }
inline float4 log2( float4 v ) { return float4( log2( v.x ), log2( v.y ), log2( v.z ), log2( v.w ) ); }
inline float4 log10( float4 v ) { return float4( log10( v.x ), log10( v.y ), log10( v.z ), log10( v.w ) ); }
inline float4 mad( float4 a, float4 b, float4 c ) { return a * b + c; }
inline float4 max( float4 a, float4 b ) { return float4( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ), max( a.w, b.w ) ); }
inline float4 min( float4 a, float4 b ) { return float4( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ), min( a.w, b.w ) ); }
inline float4 normalize( float4 v ) { float l = sqrt( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w ); return l == 0.0f ? v : float4( v.x / l, v.y / l, v.z / l, v.w / l ); }
inline float4 pow( float4 a, float4 b ) { return float4( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ), pow( a.w, b.w ) ); }
inline float4 radians( float4 v ) { return float4( radians( v.x ), radians( v.y ), radians( v.z ), radians( v.w ) ); } 
inline float4 rcp( float4 v ) { return float4( rcp( v.x ), rcp( v.y ), rcp( v.z ), rcp( v.w ) ); }
inline float4 reflect( float4 i, float4 n ) {  return i - 2.0f * n * dot( i, n ) ; }
inline float4 refract( float4 i, float4 n, float r ) { float n_i = dot( n, i ); float k = 1.0f - r * r * ( 1.0f - n_i * n_i ); return ( k < 0.0f ) ? float4( 0.0f, 0.0f, 0.0f, 0.0f ) : ( r * i - ( r * n_i + sqrt( k ) ) * n ); }
inline float4 round( float4 v ) { return float4( round( v.x ), round( v.y ), round( v.z ), round( v.w ) ); }
inline float4 rsqrt( float4 v ) { return float4( rcp( sqrt( v.x ) ), rcp( sqrt( v.y ) ), rcp( sqrt( v.z ) ), rcp( sqrt( v.w ) ) ); }
inline float4 saturate( float4 v ) { return float4( saturate( v.x ), saturate( v.y ), saturate( v.z ), saturate( v.w ) ); }
inline float4 sign( float4 v ) { return float4( sign( v.x ), sign( v.y ), sign( v.z ), sign( v.w ) ); }
inline float4 sin( float4 v ) { return float4( sin( v.x ), sin( v.y ), sin( v.z ), sin( v.w ) ); }
inline float4 sinh( float4 v ) { return float4( sinh( v.x ), sinh( v.y ), sinh( v.z ), sinh( v.w ) ); }
inline float4 smoothstep( float4 min, float4 max, float4 v ) { return float4( smoothstep( min.x, max.x, v.x ), smoothstep( min.y, max.y, v.y ), smoothstep( min.z, max.z, v.z ), smoothstep( min.w, max.w, v.w ) ); }
inline float4 smootherstep( float4 min, float4 max, float4 v ) { return float4( smootherstep( min.x, max.x, v.x ), smootherstep( min.y, max.y, v.y ), smootherstep( min.z, max.z, v.z ), smootherstep( min.w, max.w, v.w ) ); }
inline float4 sqrt( float4 v ) { return float4( sqrt( v.x ), sqrt( v.y ), sqrt( v.z ), sqrt( v.w ) ); }
inline float4 step( float4 a, float4 b ) { return float4( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ), step( a.w, b.w ) ); }
inline float4 tan( float4 v ) { return float4( tan( v.x ), tan( v.y ), tan( v.z ), tan( v.w ) ); }
inline float4 tanh( float4 v ) { return float4( tanh( v.x ), tanh( v.y ), tanh( v.z ), tanh( v.w ) ); }
inline float4 trunc( float4 v ) { return float4( trunc( v.x ), trunc( v.y ), trunc( v.z ), trunc( v.w ) ); }


struct float2x2
	{
	// rows
	float2 x;
	float2 y;

	// constructors
	inline float2x2() { }
	inline float2x2( float f ) : x( float2( f ) ), y( float2( f ) ) { } 
	inline explicit float2x2( float m[4] ) : x( m[0], m[1] ), y( m[2], m[3] ) { } 
	inline float2x2( float m00, float m01, float m10, float m11) : x( m00, m01 ), y( m10, m11 ) { } 
	inline float2x2( float2 x_, float2 y_ ) : x( x_ ), y( y_ ) { }

	// conversions
	inline float2x2( float2x2_t m ) : x( m.x ), y( m.y ) { }
	inline operator float2x2_t() const { float2x2_t m = { x, y }; return m; };

	// indexing
	inline float2& operator[]( int row ) { return ( (float2*) this )[ row ]; }

	// constants
	static inline float2x2 identity() { return float2x2( float2( 1.0f, 0.0f ), float2( 0.0f, 1.0f ) ); }
	};

// operators
inline float2x2& operator+=( float2x2& a, float2x2 b ) { a.x += b.x; a.y += b.y; return a; };
inline float2x2& operator-=( float2x2& a, float2x2 b ) { a.x -= b.x; a.y -= b.y; return a; };
inline float2x2& operator*=( float2x2& a, float2x2 b ) { a.x *= b.x; a.y *= b.y; return a; };
inline float2x2& operator/=( float2x2& a, float2x2 b ) { a.x /= b.x; a.y /= b.y; return a; };
inline float2x2& operator+=( float2x2& a, float s ) { a.x += s; a.y += s; return a; };
inline float2x2& operator-=( float2x2& a, float s ) { a.x -= s; a.y -= s; return a; };
inline float2x2& operator*=( float2x2& a, float s ) { a.x *= s; a.y *= s; return a; };
inline float2x2& operator/=( float2x2& a, float s ) { a.x /= s; a.y /= s; return a; };
inline float2x2 operator+( float2x2 a, float2x2 b ) { return float2x2( a.x + b.x, a.y + b.y ); }
inline float2x2 operator-( float2x2 a, float2x2 b ) { return float2x2( a.x - b.x, a.y - b.y ); }
inline float2x2 operator*( float2x2 a, float2x2 b ) { return float2x2( a.x * b.x, a.y * b.y ); }
inline float2x2 operator/( float2x2 a, float2x2 b ) { return float2x2( a.x / b.x, a.y / b.y ); }
inline float2x2 operator+( float2x2 a, float b ) { return float2x2( a.x + b, a.y + b ); }
inline float2x2 operator-( float2x2 a, float b ) { return float2x2( a.x - b, a.y - b ); }
inline float2x2 operator*( float2x2 a, float b ) { return float2x2( a.x * b, a.y * b ); }
inline float2x2 operator/( float2x2 a, float b ) { return float2x2( a.x / b, a.y / b ); }
inline float2x2 operator+( float a, float2x2 b ) { return float2x2( a + b.x, a + b.y ); }
inline float2x2 operator-( float a, float2x2 b ) { return float2x2( a - b.x, a - b.y ); }
inline float2x2 operator*( float a, float2x2 b ) { return float2x2( a * b.x, a * b.y ); }
inline float2x2 operator/( float a, float2x2 b ) { return float2x2( a / b.x, a / b.y ); }

// functions
inline float2x2 abs( float2x2 m ) { return float2x2( abs( m.x ), abs( m.y ) ); }
inline float2x2 acos( float2x2 m ) { return float2x2( acos( m.x ), acos( m.y ) ); }
inline bool all( float2x2 m ) { return all( m.x ) && all( m.y ); }
inline bool any( float2x2 m ) { return any( m.x ) || any( m.y ); }
inline float2x2 asin( float2x2 m ) { return float2x2( asin( m.x ), asin( m.y ) ); }
inline float2x2 atan( float2x2 m ) { return float2x2( atan( m.x ), atan( m.y ) ); }
inline float2x2 atan2( float2x2 y, float2x2 x ) { return float2x2( atan2( y.x, x.x ), atan2( y.y, x.y ) ); }
inline float2x2 ceil( float2x2 m ) { return float2x2( ceil( m.x ), ceil( m.y ) ); }
inline float2x2 clamp( float2x2 m, float2x2 min, float2x2 max ) { return float2x2( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ) ); }
inline float2x2 cos( float2x2 m ) { return float2x2( cos( m.x ), cos( m.y ) ); }
inline float2x2 cosh( float2x2 m ) { return float2x2( cosh( m.x ), cosh( m.y ) ); }
inline float2x2 degrees( float2x2 m ) { return float2x2( degrees( m.x ), degrees( m.y ) ); } 
inline float2x2 exp( float2x2 m ) { return float2x2( exp( m.x ), exp( m.y ) ); }
inline float2x2 exp2( float2x2 m ) { return float2x2( exp2( m.x ), exp2( m.y ) ); }
inline float2x2 floor( float2x2 m ) { return float2x2( floor( m.x ), floor( m.y ) ); }
inline float2x2 fmod( float2x2 a, float2x2 b ) { return float2x2( fmod( a.x, b.x ), fmod( a.y, b.y ) ); }
inline float2x2 frac( float2x2 m ) { return float2x2( frac( m.x ), frac( m.y ) ); }
inline float2x2 lerp( float2x2 a, float2x2 b, float s ) { return float2x2( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ) ); }
inline float2x2 log( float2x2 m ) { return float2x2( log( m.x ), log( m.y ) ); }
inline float2x2 log2( float2x2 m ) { return float2x2( log2( m.x ), log2( m.y ) ); }
inline float2x2 log10( float2x2 m ) { return float2x2( log10( m.x ), log10( m.y ) ); }
inline float2x2 mad( float2x2 a, float2x2 b, float2x2 c ) { return a * b + c; }
inline float2x2 max( float2x2 a, float2x2 b ) { return float2x2( max( a.x, b.x ), max( a.y, b.y ) ); }
inline float2x2 min( float2x2 a, float2x2 b ) { return float2x2( min( a.x, b.x ), min( a.y, b.y ) ); }
inline float2x2 pow( float2x2 a, float2x2 b ) { return float2x2( pow( a.x, b.x ), pow( a.y, b.y ) ); }
inline float2x2 radians( float2x2 m ) { return float2x2( radians( m.x ), radians( m.y ) ); } 
inline float2x2 rcp( float2x2 m ) { return float2x2( rcp( m.x ), rcp( m.y ) ); }
inline float2x2 round( float2x2 m ) { return float2x2( round( m.x ), round( m.y ) ); }
inline float2x2 rsqrt( float2x2 m ) { return float2x2( rsqrt( m.x ), rsqrt( m.y ) ); }
inline float2x2 saturate( float2x2 m ) { return float2x2( saturate( m.x ), saturate( m.y ) ); }
inline float2x2 sign( float2x2 m ) { return float2x2( sign( m.x ), sign( m.y ) ); }
inline float2x2 sin( float2x2 m ) { return float2x2( sin( m.x ), sin( m.y ) ); }
inline float2x2 sinh( float2x2 m ) { return float2x2( sinh( m.x ), sinh( m.y ) ); }
inline float2x2 smoothstep( float2x2 min, float2x2 max, float2x2 m ) { return float2x2( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ) ); }
inline float2x2 smootherstep( float2x2 min, float2x2 max, float2x2 m ) { return float2x2( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ) ); }
inline float2x2 sqrt( float2x2 m ) { return float2x2( sqrt( m.x ), sqrt( m.y ) ); }
inline float2x2 step( float2x2 a, float2x2 b ) { return float2x2( step( a.x, b.x ), step( a.y, b.y ) ); }
inline float2x2 tan( float2x2 m ) { return float2x2( tan( m.x ), tan( m.y ) ); }
inline float2x2 tanh( float2x2 m ) { return float2x2( tanh( m.x ), tanh( m.y ) ); }
inline float2x2 trunc( float2x2 m ) { return float2x2( trunc( m.x ), trunc( m.y ) ); }


struct float2x3
	{
	// rows
	float3 x;
	float3 y;

	// constructors
	inline float2x3() { }
	inline float2x3( float f ) : x( float3( f ) ), y( float3( f ) ) { } 
	inline explicit float2x3( float m[6] ) : x( m[0], m[1], m[2] ), y( m[3], m[4], m[5] ) { } 
	inline float2x3( float m00, float m01, float m02, float m10, float m11, float m12 ) : x( m00, m01, m02 ), y( m10, m11, m12 ) { } 
	inline float2x3( float3 x_, float3 y_ ) : x( x_ ), y( y_ ) { }

	// conversions
	inline float2x3( float2x3_t m ) : x( m.x ), y( m.y ) { }
	inline operator float2x3_t() const { float2x3_t m = { x, y }; return m; };

	// indexing
	inline float3 operator[]( int row ) { return ( (float3*) this )[ row ]; }
	};

// operators
inline float2x3& operator+=( float2x3& a, float2x3 b ) { a.x += b.x; a.y += b.y; return a; };
inline float2x3& operator-=( float2x3& a, float2x3 b ) { a.x -= b.x; a.y -= b.y; return a; };
inline float2x3& operator*=( float2x3& a, float2x3 b ) { a.x *= b.x; a.y *= b.y; return a; };
inline float2x3& operator/=( float2x3& a, float2x3 b ) { a.x /= b.x; a.y /= b.y; return a; };
inline float2x3& operator+=( float2x3& a, float s ) { a.x += s; a.y += s; return a; };
inline float2x3& operator-=( float2x3& a, float s ) { a.x -= s; a.y -= s; return a; };
inline float2x3& operator*=( float2x3& a, float s ) { a.x *= s; a.y *= s; return a; };
inline float2x3& operator/=( float2x3& a, float s ) { a.x /= s; a.y /= s; return a; };
inline float2x3 operator+( float2x3 a, float2x3 b ) { return float2x3( a.x + b.x, a.y + b.y ); }
inline float2x3 operator-( float2x3 a, float2x3 b ) { return float2x3( a.x - b.x, a.y - b.y ); }
inline float2x3 operator*( float2x3 a, float2x3 b ) { return float2x3( a.x * b.x, a.y * b.y ); }
inline float2x3 operator/( float2x3 a, float2x3 b ) { return float2x3( a.x / b.x, a.y / b.y ); }
inline float2x3 operator+( float2x3 a, float b ) { return float2x3( a.x + b, a.y + b ); }
inline float2x3 operator-( float2x3 a, float b ) { return float2x3( a.x - b, a.y - b ); }
inline float2x3 operator*( float2x3 a, float b ) { return float2x3( a.x * b, a.y * b ); }
inline float2x3 operator/( float2x3 a, float b ) { return float2x3( a.x / b, a.y / b ); }
inline float2x3 operator+( float a, float2x3 b ) { return float2x3( a + b.x, a + b.y ); }
inline float2x3 operator-( float a, float2x3 b ) { return float2x3( a - b.x, a - b.y ); }
inline float2x3 operator*( float a, float2x3 b ) { return float2x3( a * b.x, a * b.y ); }
inline float2x3 operator/( float a, float2x3 b ) { return float2x3( a / b.x, a / b.y ); }

// functions
inline float2x3 abs( float2x3 m ) { return float2x3( abs( m.x ), abs( m.y ) ); }
inline float2x3 acos( float2x3 m ) { return float2x3( acos( m.x ), acos( m.y ) ); }
inline bool all( float2x3 m ) { return all( m.x ) && all( m.y ); }
inline bool any( float2x3 m ) { return any( m.x ) || any( m.y ); }
inline float2x3 asin( float2x3 m ) { return float2x3( asin( m.x ), asin( m.y ) ); }
inline float2x3 atan( float2x3 m ) { return float2x3( atan( m.x ), atan( m.y ) ); }
inline float2x3 atan2( float2x3 y, float2x3 x ) { return float2x3( atan2( y.x, x.x ), atan2( y.y, x.y ) ); }
inline float2x3 ceil( float2x3 m ) { return float2x3( ceil( m.x ), ceil( m.y ) ); }
inline float2x3 clamp( float2x3 m, float2x3 min, float2x3 max ) { return float2x3( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ) ); }
inline float2x3 cos( float2x3 m ) { return float2x3( cos( m.x ), cos( m.y ) ); }
inline float2x3 cosh( float2x3 m ) { return float2x3( cosh( m.x ), cosh( m.y ) ); }
inline float2x3 degrees( float2x3 m ) { return float2x3( degrees( m.x ), degrees( m.y ) ); } 
inline float2x3 exp( float2x3 m ) { return float2x3( exp( m.x ), exp( m.y ) ); }
inline float2x3 exp2( float2x3 m ) { return float2x3( exp2( m.x ), exp2( m.y ) ); }
inline float2x3 floor( float2x3 m ) { return float2x3( floor( m.x ), floor( m.y ) ); }
inline float2x3 fmod( float2x3 a, float2x3 b ) { return float2x3( fmod( a.x, b.x ), fmod( a.y, b.y ) ); }
inline float2x3 frac( float2x3 m ) { return float2x3( frac( m.x ), frac( m.y ) ); }
inline float2x3 lerp( float2x3 a, float2x3 b, float s ) { return float2x3( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ) ); }
inline float2x3 log( float2x3 m ) { return float2x3( log( m.x ), log( m.y ) ); }
inline float2x3 log2( float2x3 m ) { return float2x3( log2( m.x ), log2( m.y ) ); }
inline float2x3 log10( float2x3 m ) { return float2x3( log10( m.x ), log10( m.y ) ); }
inline float2x3 mad( float2x3 a, float2x3 b, float2x3 c ) { return a * b + c; }
inline float2x3 max( float2x3 a, float2x3 b ) { return float2x3( max( a.x, b.x ), max( a.y, b.y ) ); }
inline float2x3 min( float2x3 a, float2x3 b ) { return float2x3( min( a.x, b.x ), min( a.y, b.y ) ); }
inline float2x3 pow( float2x3 a, float2x3 b ) { return float2x3( pow( a.x, b.x ), pow( a.y, b.y ) ); }
inline float2x3 radians( float2x3 m ) { return float2x3( radians( m.x ), radians( m.y ) ); } 
inline float2x3 rcp( float2x3 m ) { return float2x3( rcp( m.x ), rcp( m.y ) ); }
inline float2x3 round( float2x3 m ) { return float2x3( round( m.x ), round( m.y ) ); }
inline float2x3 rsqrt( float2x3 m ) { return float2x3( rsqrt( m.x ), rsqrt( m.y ) ); }
inline float2x3 saturate( float2x3 m ) { return float2x3( saturate( m.x ), saturate( m.y ) ); }
inline float2x3 sign( float2x3 m ) { return float2x3( sign( m.x ), sign( m.y ) ); }
inline float2x3 sin( float2x3 m ) { return float2x3( sin( m.x ), sin( m.y ) ); }
inline float2x3 sinh( float2x3 m ) { return float2x3( sinh( m.x ), sinh( m.y ) ); }
inline float2x3 smoothstep( float2x3 min, float2x3 max, float2x3 m ) { return float2x3( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ) ); }
inline float2x3 smootherstep( float2x3 min, float2x3 max, float2x3 m ) { return float2x3( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ) ); }
inline float2x3 sqrt( float2x3 m ) { return float2x3( sqrt( m.x ), sqrt( m.y ) ); }
inline float2x3 step( float2x3 a, float2x3 b ) { return float2x3( step( a.x, b.x ), step( a.y, b.y ) ); }
inline float2x3 tan( float2x3 m ) { return float2x3( tan( m.x ), tan( m.y ) ); }
inline float2x3 tanh( float2x3 m ) { return float2x3( tanh( m.x ), tanh( m.y ) ); }
inline float2x3 trunc( float2x3 m ) { return float2x3( trunc( m.x ), trunc( m.y ) ); }


struct float3x2
	{
	// rows
	float2 x;
	float2 y;
	float2 z;

	// constructors
	inline float3x2() { }
	inline float3x2( float f ) : x( float2( f ) ), y( float2( f ) ), z( float2( f ) ) { } 
	inline explicit float3x2( float m[6] ) : x( m[0], m[1] ), y( m[2], m[3] ), z( m[4], m[5] ) { } 
	inline float3x2( float m00, float m01, float m10, float m11, float m20, float m21 ) : x( m00, m01 ), y( m10, m11 ), z( m20, m21 ) { } 
	inline float3x2( float2 x_, float2 y_, float2 z_ ) : x( x_ ), y( y_ ), z( z_ ) { }
	
	// conversions
	inline float3x2( float3x2_t m ) : x( m.x ), y( m.y ), z( m.z ) { }
	inline operator float3x2_t() const { float3x2_t m = { x, y, z }; return m; };
	
	// indexing
	inline float2 operator[]( int row ) { return ( (float2*) this )[ row ]; }
	};

// operators
inline float3x2& operator+=( float3x2& a, float3x2 b ) { a.x += b.x; a.y += b.y; a.z += b.z; return a; };
inline float3x2& operator-=( float3x2& a, float3x2 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; };
inline float3x2& operator*=( float3x2& a, float3x2 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; };
inline float3x2& operator/=( float3x2& a, float3x2 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; };
inline float3x2& operator+=( float3x2& a, float s ) { a.x += s; a.y += s; a.z += s; return a; };
inline float3x2& operator-=( float3x2& a, float s ) { a.x -= s; a.y -= s; a.z -= s; return a; };
inline float3x2& operator*=( float3x2& a, float s ) { a.x *= s; a.y *= s; a.z *= s; return a; };
inline float3x2& operator/=( float3x2& a, float s ) { a.x /= s; a.y /= s; a.z /= s; return a; };
inline float3x2 operator+( float3x2 a, float3x2 b ) { return float3x2( a.x + b.x, a.y + b.y, a.z + b.z ); }
inline float3x2 operator-( float3x2 a, float3x2 b ) { return float3x2( a.x - b.x, a.y - b.y, a.z - b.z ); }
inline float3x2 operator*( float3x2 a, float3x2 b ) { return float3x2( a.x * b.x, a.y * b.y, a.z * b.z ); }
inline float3x2 operator/( float3x2 a, float3x2 b ) { return float3x2( a.x / b.x, a.y / b.y, a.z / b.z ); }
inline float3x2 operator+( float3x2 a, float b ) { return float3x2( a.x + b, a.y + b, a.z + b ); }
inline float3x2 operator-( float3x2 a, float b ) { return float3x2( a.x - b, a.y - b, a.z - b ); }
inline float3x2 operator*( float3x2 a, float b ) { return float3x2( a.x * b, a.y * b, a.z * b ); }
inline float3x2 operator/( float3x2 a, float b ) { return float3x2( a.x / b, a.y / b, a.z / b ); }
inline float3x2 operator+( float a, float3x2 b ) { return float3x2( a + b.x, a + b.y, a + b.z ); }
inline float3x2 operator-( float a, float3x2 b ) { return float3x2( a - b.x, a - b.y, a - b.z ); }
inline float3x2 operator*( float a, float3x2 b ) { return float3x2( a * b.x, a * b.y, a * b.z ); }
inline float3x2 operator/( float a, float3x2 b ) { return float3x2( a / b.x, a / b.y, a / b.z ); }

// functions
inline float3x2 abs( float3x2 m ) { return float3x2( abs( m.x ), abs( m.y ), abs( m.z ) ); }
inline float3x2 acos( float3x2 m ) { return float3x2( acos( m.x ), acos( m.y ), acos( m.z ) ); }
inline bool all( float3x2 m ) { return all( m.x ) && all( m.y ) && all( m.z ); }
inline bool any( float3x2 m ) { return any( m.x ) || any( m.y ) || any( m.z ); }
inline float3x2 asin( float3x2 m ) { return float3x2( asin( m.x ), asin( m.y ), asin( m.z ) ); }
inline float3x2 atan( float3x2 m ) { return float3x2( atan( m.x ), atan( m.y ), atan( m.z ) ); }
inline float3x2 atan2( float3x2 y, float3x2 x ) { return float3x2( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ) ); }
inline float3x2 ceil( float3x2 m ) { return float3x2( ceil( m.x ), ceil( m.y ), ceil( m.z ) ); }
inline float3x2 clamp( float3x2 m, float3x2 min, float3x2 max ) { return float3x2( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ) ); }
inline float3x2 cos( float3x2 m ) { return float3x2( cos( m.x ), cos( m.y ), cos( m.z ) ); }
inline float3x2 cosh( float3x2 m ) { return float3x2( cosh( m.x ), cosh( m.y ), cosh( m.z ) ); }
inline float3x2 degrees( float3x2 m ) { return float3x2( degrees( m.x ), degrees( m.y ), degrees( m.z ) ); } 
inline float3x2 exp( float3x2 m ) { return float3x2( exp( m.x ), exp( m.y ), exp( m.z ) ); }
inline float3x2 exp2( float3x2 m ) { return float3x2( exp2( m.x ), exp2( m.y ), exp2( m.z ) ); }
inline float3x2 floor( float3x2 m ) { return float3x2( floor( m.x ), floor( m.y ), floor( m.z ) ); }
inline float3x2 fmod( float3x2 a, float3x2 b ) { return float3x2( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ) ); }
inline float3x2 frac( float3x2 m ) { return float3x2( frac( m.x ), frac( m.y ), frac( m.z ) ); }
inline float3x2 lerp( float3x2 a, float3x2 b, float s ) { return float3x2( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ) ); }
inline float3x2 log( float3x2 m ) { return float3x2( log( m.x ), log( m.y ), log( m.z ) ); }
inline float3x2 log2( float3x2 m ) { return float3x2( log2( m.x ), log2( m.y ), log2( m.z ) ); }
inline float3x2 log10( float3x2 m ) { return float3x2( log10( m.x ), log10( m.y ), log10( m.z ) ); }
inline float3x2 mad( float3x2 a, float3x2 b, float3x2 c ) { return a * b + c; }
inline float3x2 max( float3x2 a, float3x2 b ) { return float3x2( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ) ); }
inline float3x2 min( float3x2 a, float3x2 b ) { return float3x2( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ) ); }
inline float3x2 pow( float3x2 a, float3x2 b ) { return float3x2( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ) ); }
inline float3x2 radians( float3x2 m ) { return float3x2( radians( m.x ), radians( m.y ), radians( m.z ) ); } 
inline float3x2 rcp( float3x2 m ) { return float3x2( rcp( m.x ), rcp( m.y ), rcp( m.z ) ); }
inline float3x2 round( float3x2 m ) { return float3x2( round( m.x ), round( m.y ), round( m.z ) ); }
inline float3x2 rsqrt( float3x2 m ) { return float3x2( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ) ); }
inline float3x2 saturate( float3x2 m ) { return float3x2( saturate( m.x ), saturate( m.y ), saturate( m.z ) ); }
inline float3x2 sign( float3x2 m ) { return float3x2( sign( m.x ), sign( m.y ), sign( m.z ) ); }
inline float3x2 sin( float3x2 m ) { return float3x2( sin( m.x ), sin( m.y ), sin( m.z ) ); }
inline float3x2 sinh( float3x2 m ) { return float3x2( sinh( m.x ), sinh( m.y ), sinh( m.z ) ); }
inline float3x2 smoothstep( float3x2 min, float3x2 max, float3x2 m ) { return float3x2( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ) ); }
inline float3x2 smootherstep( float3x2 min, float3x2 max, float3x2 m ) { return float3x2( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ) ); }
inline float3x2 sqrt( float3x2 m ) { return float3x2( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ) ); }
inline float3x2 step( float3x2 a, float3x2 b ) { return float3x2( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ) ); }
inline float3x2 tan( float3x2 m ) { return float3x2( tan( m.x ), tan( m.y ), tan( m.z ) ); }
inline float3x2 tanh( float3x2 m ) { return float3x2( tanh( m.x ), tanh( m.y ), tanh( m.z ) ); }
inline float3x2 trunc( float3x2 m ) { return float3x2( trunc( m.x ), trunc( m.y ), trunc( m.z ) ); }


struct float3x3
	{
	// rows
	float3 x;
	float3 y;
	float3 z;

	// constructors
	inline float3x3() { }
	inline float3x3( float f ) : x( float3( f ) ), y( float3( f ) ), z( float3( f ) ) { } 
	inline explicit float3x3( float m[9] ) : x( m[0], m[1], m[2] ), y( m[3], m[4], m[5] ), z( m[6], m[7], m[8] ) { } 
	inline float3x3( float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22 ) : x( m00, m01, m02 ), y( m10, m11, m12 ), z( m20, m21, m22 ) { } 
	inline float3x3( float3 x_, float3 y_, float3 z_ ) : x( x_ ), y( y_ ), z( z_ ) { }
	
	// conversions
	inline float3x3( float3x3_t m ) : x( m.x ), y( m.y ), z( m.z ) { }
	inline operator float3x3_t() const { float3x3_t m = { x, y, z }; return m; };
	
	// indexing
	inline float3 operator[]( int row ) { return ( (float3*) this )[ row ]; }

	// constants
	static inline float3x3 identity() { return float3x3( float3( 1.0f, 0.0f, 0.0f ), float3( 0.0f, 1.0f, 0.0f ), float3( 0.0f, 0.0f, 1.0f ) ); }
	};

// operators
inline float3x3& operator+=( float3x3& a, float3x3 b ) { a.x += b.x; a.y += b.y; a.z += b.z; return a; };
inline float3x3& operator-=( float3x3& a, float3x3 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; };
inline float3x3& operator*=( float3x3& a, float3x3 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; };
inline float3x3& operator/=( float3x3& a, float3x3 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; };
inline float3x3& operator+=( float3x3& a, float s ) { a.x += s; a.y += s; a.z += s; return a; };
inline float3x3& operator-=( float3x3& a, float s ) { a.x -= s; a.y -= s; a.z -= s; return a; };
inline float3x3& operator*=( float3x3& a, float s ) { a.x *= s; a.y *= s; a.z *= s; return a; };
inline float3x3& operator/=( float3x3& a, float s ) { a.x /= s; a.y /= s; a.z /= s; return a; };
inline float3x3 operator+( float3x3 a, float3x3 b ) { return float3x3( a.x + b.x, a.y + b.y, a.z + b.z ); }
inline float3x3 operator-( float3x3 a, float3x3 b ) { return float3x3( a.x - b.x, a.y - b.y, a.z - b.z ); }
inline float3x3 operator*( float3x3 a, float3x3 b ) { return float3x3( a.x * b.x, a.y * b.y, a.z * b.z ); }
inline float3x3 operator/( float3x3 a, float3x3 b ) { return float3x3( a.x / b.x, a.y / b.y, a.z / b.z ); }
inline float3x3 operator+( float3x3 a, float b ) { return float3x3( a.x + b, a.y + b, a.z + b ); }
inline float3x3 operator-( float3x3 a, float b ) { return float3x3( a.x - b, a.y - b, a.z - b ); }
inline float3x3 operator*( float3x3 a, float b ) { return float3x3( a.x * b, a.y * b, a.z * b ); }
inline float3x3 operator/( float3x3 a, float b ) { return float3x3( a.x / b, a.y / b, a.z / b ); }
inline float3x3 operator+( float a, float3x3 b ) { return float3x3( a + b.x, a + b.y, a + b.z ); }
inline float3x3 operator-( float a, float3x3 b ) { return float3x3( a - b.x, a - b.y, a - b.z ); }
inline float3x3 operator*( float a, float3x3 b ) { return float3x3( a * b.x, a * b.y, a * b.z ); }
inline float3x3 operator/( float a, float3x3 b ) { return float3x3( a / b.x, a / b.y, a / b.z ); }

// functions
inline float3x3 abs( float3x3 m ) { return float3x3( abs( m.x ), abs( m.y ), abs( m.z ) ); }
inline float3x3 acos( float3x3 m ) { return float3x3( acos( m.x ), acos( m.y ), acos( m.z ) ); }
inline bool all( float3x3 m ) { return all( m.x ) && all( m.y ) && all( m.z ); }
inline bool any( float3x3 m ) { return any( m.x ) || any( m.y ) || any( m.z ); }
inline float3x3 asin( float3x3 m ) { return float3x3( asin( m.x ), asin( m.y ), asin( m.z ) ); }
inline float3x3 atan( float3x3 m ) { return float3x3( atan( m.x ), atan( m.y ), atan( m.z ) ); }
inline float3x3 atan2( float3x3 y, float3x3 x ) { return float3x3( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ) ); }
inline float3x3 ceil( float3x3 m ) { return float3x3( ceil( m.x ), ceil( m.y ), ceil( m.z ) ); }
inline float3x3 clamp( float3x3 m, float3x3 min, float3x3 max ) { return float3x3( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ) ); }
inline float3x3 cos( float3x3 m ) { return float3x3( cos( m.x ), cos( m.y ), cos( m.z ) ); }
inline float3x3 cosh( float3x3 m ) { return float3x3( cosh( m.x ), cosh( m.y ), cosh( m.z ) ); }
inline float3x3 degrees( float3x3 m ) { return float3x3( degrees( m.x ), degrees( m.y ), degrees( m.z ) ); } 
inline float3x3 exp( float3x3 m ) { return float3x3( exp( m.x ), exp( m.y ), exp( m.z ) ); }
inline float3x3 exp2( float3x3 m ) { return float3x3( exp2( m.x ), exp2( m.y ), exp2( m.z ) ); }
inline float3x3 floor( float3x3 m ) { return float3x3( floor( m.x ), floor( m.y ), floor( m.z ) ); }
inline float3x3 fmod( float3x3 a, float3x3 b ) { return float3x3( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ) ); }
inline float3x3 frac( float3x3 m ) { return float3x3( frac( m.x ), frac( m.y ), frac( m.z ) ); }
inline float3x3 lerp( float3x3 a, float3x3 b, float s ) { return float3x3( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ) ); }
inline float3x3 log( float3x3 m ) { return float3x3( log( m.x ), log( m.y ), log( m.z ) ); }
inline float3x3 log2( float3x3 m ) { return float3x3( log2( m.x ), log2( m.y ), log2( m.z ) ); }
inline float3x3 log10( float3x3 m ) { return float3x3( log10( m.x ), log10( m.y ), log10( m.z ) ); }
inline float3x3 mad( float3x3 a, float3x3 b, float3x3 c ) { return a * b + c; }
inline float3x3 max( float3x3 a, float3x3 b ) { return float3x3( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ) ); }
inline float3x3 min( float3x3 a, float3x3 b ) { return float3x3( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ) ); }
inline float3x3 pow( float3x3 a, float3x3 b ) { return float3x3( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ) ); }
inline float3x3 radians( float3x3 m ) { return float3x3( radians( m.x ), radians( m.y ), radians( m.z ) ); } 
inline float3x3 rcp( float3x3 m ) { return float3x3( rcp( m.x ), rcp( m.y ), rcp( m.z ) ); }
inline float3x3 round( float3x3 m ) { return float3x3( round( m.x ), round( m.y ), round( m.z ) ); }
inline float3x3 rsqrt( float3x3 m ) { return float3x3( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ) ); }
inline float3x3 saturate( float3x3 m ) { return float3x3( saturate( m.x ), saturate( m.y ), saturate( m.z ) ); }
inline float3x3 sign( float3x3 m ) { return float3x3( sign( m.x ), sign( m.y ), sign( m.z ) ); }
inline float3x3 sin( float3x3 m ) { return float3x3( sin( m.x ), sin( m.y ), sin( m.z ) ); }
inline float3x3 sinh( float3x3 m ) { return float3x3( sinh( m.x ), sinh( m.y ), sinh( m.z ) ); }
inline float3x3 smoothstep( float3x3 min, float3x3 max, float3x3 m ) { return float3x3( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ) ); }
inline float3x3 smootherstep( float3x3 min, float3x3 max, float3x3 m ) { return float3x3( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ) ); }
inline float3x3 sqrt( float3x3 m ) { return float3x3( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ) ); }
inline float3x3 step( float3x3 a, float3x3 b ) { return float3x3( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ) ); }
inline float3x3 tan( float3x3 m ) { return float3x3( tan( m.x ), tan( m.y ), tan( m.z ) ); }
inline float3x3 tanh( float3x3 m ) { return float3x3( tanh( m.x ), tanh( m.y ), tanh( m.z ) ); }
inline float3x3 trunc( float3x3 m ) { return float3x3( trunc( m.x ), trunc( m.y ), trunc( m.z ) ); }


struct float2x4
	{
	// rows
	float4 x;
	float4 y;

	// constructors
	inline float2x4() { }
	inline float2x4( float f ) : x( float4( f ) ), y( float4( f ) ) { } 
	inline explicit float2x4( float m[8] ) : x( m[0], m[1], m[2], m[3] ), y( m[4], m[5], m[6], m[7] ) { } 
	inline float2x4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13 ) : x( m00, m01, m02, m03 ), y( m10, m11, m12, m13 ) { } 
	inline float2x4( float4 x_, float4 y_ ) : x( x_ ), y( y_ ) { }
	
	// conversions
	inline float2x4( float2x4_t m ) : x( m.x ), y( m.y ) { }
	inline operator float2x4_t() const { float2x4_t m = { x, y }; return m; };

	// indexing
	inline float4 operator[]( int row ) { return ( (float4*) this )[ row ]; }
	};

// operators
inline float2x4& operator+=( float2x4& a, float2x4 b ) { a.x += b.x; a.y += b.y; return a; };
inline float2x4& operator-=( float2x4& a, float2x4 b ) { a.x -= b.x; a.y -= b.y; return a; };
inline float2x4& operator*=( float2x4& a, float2x4 b ) { a.x *= b.x; a.y *= b.y; return a; };
inline float2x4& operator/=( float2x4& a, float2x4 b ) { a.x /= b.x; a.y /= b.y; return a; };
inline float2x4& operator+=( float2x4& a, float s ) { a.x += s; a.y += s; return a; };
inline float2x4& operator-=( float2x4& a, float s ) { a.x -= s; a.y -= s; return a; };
inline float2x4& operator*=( float2x4& a, float s ) { a.x *= s; a.y *= s; return a; };
inline float2x4& operator/=( float2x4& a, float s ) { a.x /= s; a.y /= s; return a; };
inline float2x4 operator+( float2x4 a, float2x4 b ) { return float2x4( a.x + b.x, a.y + b.y ); }
inline float2x4 operator-( float2x4 a, float2x4 b ) { return float2x4( a.x - b.x, a.y - b.y ); }
inline float2x4 operator*( float2x4 a, float2x4 b ) { return float2x4( a.x * b.x, a.y * b.y ); }
inline float2x4 operator/( float2x4 a, float2x4 b ) { return float2x4( a.x / b.x, a.y / b.y ); }
inline float2x4 operator+( float2x4 a, float b ) { return float2x4( a.x + b, a.y + b ); }
inline float2x4 operator-( float2x4 a, float b ) { return float2x4( a.x - b, a.y - b ); }
inline float2x4 operator*( float2x4 a, float b ) { return float2x4( a.x * b, a.y * b ); }
inline float2x4 operator/( float2x4 a, float b ) { return float2x4( a.x / b, a.y / b ); }
inline float2x4 operator+( float a, float2x4 b ) { return float2x4( a + b.x, a + b.y ); }
inline float2x4 operator-( float a, float2x4 b ) { return float2x4( a - b.x, a - b.y ); }
inline float2x4 operator*( float a, float2x4 b ) { return float2x4( a * b.x, a * b.y ); }
inline float2x4 operator/( float a, float2x4 b ) { return float2x4( a / b.x, a / b.y ); }

// functions
inline float2x4 abs( float2x4 m ) { return float2x4( abs( m.x ), abs( m.y ) ); }
inline float2x4 acos( float2x4 m ) { return float2x4( acos( m.x ), acos( m.y ) ); }
inline bool all( float2x4 m ) { return all( m.x ) && all( m.y ); }
inline bool any( float2x4 m ) { return any( m.x ) || any( m.y ); }
inline float2x4 asin( float2x4 m ) { return float2x4( asin( m.x ), asin( m.y ) ); }
inline float2x4 atan( float2x4 m ) { return float2x4( atan( m.x ), atan( m.y ) ); }
inline float2x4 atan2( float2x4 y, float2x4 x ) { return float2x4( atan2( y.x, x.x ), atan2( y.y, x.y ) ); }
inline float2x4 ceil( float2x4 m ) { return float2x4( ceil( m.x ), ceil( m.y ) ); }
inline float2x4 clamp( float2x4 m, float2x4 min, float2x4 max ) { return float2x4( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ) ); }
inline float2x4 cos( float2x4 m ) { return float2x4( cos( m.x ), cos( m.y ) ); }
inline float2x4 cosh( float2x4 m ) { return float2x4( cosh( m.x ), cosh( m.y ) ); }
inline float2x4 degrees( float2x4 m ) { return float2x4( degrees( m.x ), degrees( m.y ) ); } 
inline float2x4 exp( float2x4 m ) { return float2x4( exp( m.x ), exp( m.y ) ); }
inline float2x4 exp2( float2x4 m ) { return float2x4( exp2( m.x ), exp2( m.y ) ); }
inline float2x4 floor( float2x4 m ) { return float2x4( floor( m.x ), floor( m.y ) ); }
inline float2x4 fmod( float2x4 a, float2x4 b ) { return float2x4( fmod( a.x, b.x ), fmod( a.y, b.y ) ); }
inline float2x4 frac( float2x4 m ) { return float2x4( frac( m.x ), frac( m.y ) ); }
inline float2x4 lerp( float2x4 a, float2x4 b, float s ) { return float2x4( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ) ); }
inline float2x4 log( float2x4 m ) { return float2x4( log( m.x ), log( m.y ) ); }
inline float2x4 log2( float2x4 m ) { return float2x4( log2( m.x ), log2( m.y ) ); }
inline float2x4 log10( float2x4 m ) { return float2x4( log10( m.x ), log10( m.y ) ); }
inline float2x4 mad( float2x4 a, float2x4 b, float2x4 c ) { return a * b + c; }
inline float2x4 max( float2x4 a, float2x4 b ) { return float2x4( max( a.x, b.x ), max( a.y, b.y ) ); }
inline float2x4 min( float2x4 a, float2x4 b ) { return float2x4( min( a.x, b.x ), min( a.y, b.y ) ); }
inline float2x4 pow( float2x4 a, float2x4 b ) { return float2x4( pow( a.x, b.x ), pow( a.y, b.y ) ); }
inline float2x4 radians( float2x4 m ) { return float2x4( radians( m.x ), radians( m.y ) ); } 
inline float2x4 rcp( float2x4 m ) { return float2x4( rcp( m.x ), rcp( m.y ) ); }
inline float2x4 round( float2x4 m ) { return float2x4( round( m.x ), round( m.y ) ); }
inline float2x4 rsqrt( float2x4 m ) { return float2x4( rsqrt( m.x ), rsqrt( m.y ) ); }
inline float2x4 saturate( float2x4 m ) { return float2x4( saturate( m.x ), saturate( m.y ) ); }
inline float2x4 sign( float2x4 m ) { return float2x4( sign( m.x ), sign( m.y ) ); }
inline float2x4 sin( float2x4 m ) { return float2x4( sin( m.x ), sin( m.y ) ); }
inline float2x4 sinh( float2x4 m ) { return float2x4( sinh( m.x ), sinh( m.y ) ); }
inline float2x4 smoothstep( float2x4 min, float2x4 max, float2x4 m ) { return float2x4( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ) ); }
inline float2x4 smootherstep( float2x4 min, float2x4 max, float2x4 m ) { return float2x4( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ) ); }
inline float2x4 sqrt( float2x4 m ) { return float2x4( sqrt( m.x ), sqrt( m.y ) ); }
inline float2x4 step( float2x4 a, float2x4 b ) { return float2x4( step( a.x, b.x ), step( a.y, b.y ) ); }
inline float2x4 tan( float2x4 m ) { return float2x4( tan( m.x ), tan( m.y ) ); }
inline float2x4 tanh( float2x4 m ) { return float2x4( tanh( m.x ), tanh( m.y ) ); }
inline float2x4 trunc( float2x4 m ) { return float2x4( trunc( m.x ), trunc( m.y ) ); }


struct float3x4
	{
	// rows
	float4 x;
	float4 y;
	float4 z;

	// constructors
	inline float3x4() { }
	inline float3x4( float f ) : x( float4( f ) ), y( float4( f ) ), z( float4( f ) ) { } 
	inline explicit float3x4( float m[12] ) : x( m[0], m[1], m[2], m[3] ), y( m[4], m[5], m[6], m[7] ), z( m[8], m[9], m[10], m[11] ) { } 
	inline float3x4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23 ) : x( m00, m01, m02, m03 ), y( m10, m11, m12, m13 ), z( m20, m21, m22, m23 ) { } 
	inline float3x4( float4 x_, float4 y_, float4 z_ ) : x( x_ ), y( y_ ), z( z_ ) { }

	// conversions
	inline float3x4( float3x4_t m ) : x( m.x ), y( m.y ), z( m.z ) { }
	inline operator float3x4_t() const { float3x4_t m = { x, y, z }; return m; };

	// indexing
	inline float4 operator[]( int row ) { return ( (float4*) this )[ row ]; }
	};

// operators
inline float3x4& operator+=( float3x4& a, float3x4 b ) { a.x += b.x; a.y += b.y; a.z += b.z; return a; };
inline float3x4& operator-=( float3x4& a, float3x4 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; };
inline float3x4& operator*=( float3x4& a, float3x4 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; };
inline float3x4& operator/=( float3x4& a, float3x4 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; };
inline float3x4& operator+=( float3x4& a, float s ) { a.x += s; a.y += s; a.z += s; return a; };
inline float3x4& operator-=( float3x4& a, float s ) { a.x -= s; a.y -= s; a.z -= s; return a; };
inline float3x4& operator*=( float3x4& a, float s ) { a.x *= s; a.y *= s; a.z *= s; return a; };
inline float3x4& operator/=( float3x4& a, float s ) { a.x /= s; a.y /= s; a.z /= s; return a; };
inline float3x4 operator+( float3x4 a, float3x4 b ) { return float3x4( a.x + b.x, a.y + b.y, a.z + b.z ); }
inline float3x4 operator-( float3x4 a, float3x4 b ) { return float3x4( a.x - b.x, a.y - b.y, a.z - b.z ); }
inline float3x4 operator*( float3x4 a, float3x4 b ) { return float3x4( a.x * b.x, a.y * b.y, a.z * b.z ); }
inline float3x4 operator/( float3x4 a, float3x4 b ) { return float3x4( a.x / b.x, a.y / b.y, a.z / b.z ); }
inline float3x4 operator+( float3x4 a, float b ) { return float3x4( a.x + b, a.y + b, a.z + b ); }
inline float3x4 operator-( float3x4 a, float b ) { return float3x4( a.x - b, a.y - b, a.z - b ); }
inline float3x4 operator*( float3x4 a, float b ) { return float3x4( a.x * b, a.y * b, a.z * b ); }
inline float3x4 operator/( float3x4 a, float b ) { return float3x4( a.x / b, a.y / b, a.z / b ); }
inline float3x4 operator+( float a, float3x4 b ) { return float3x4( a + b.x, a + b.y, a + b.z ); }
inline float3x4 operator-( float a, float3x4 b ) { return float3x4( a - b.x, a - b.y, a - b.z ); }
inline float3x4 operator*( float a, float3x4 b ) { return float3x4( a * b.x, a * b.y, a * b.z ); }
inline float3x4 operator/( float a, float3x4 b ) { return float3x4( a / b.x, a / b.y, a / b.z ); }

// functions
inline float3x4 abs( float3x4 m ) { return float3x4( abs( m.x ), abs( m.y ), abs( m.z ) ); }
inline float3x4 acos( float3x4 m ) { return float3x4( acos( m.x ), acos( m.y ), acos( m.z ) ); }
inline bool all( float3x4 m ) { return all( m.x ) && all( m.y ) && all( m.z ); }
inline bool any( float3x4 m ) { return any( m.x ) || any( m.y ) || any( m.z ); }
inline float3x4 asin( float3x4 m ) { return float3x4( asin( m.x ), asin( m.y ), asin( m.z ) ); }
inline float3x4 atan( float3x4 m ) { return float3x4( atan( m.x ), atan( m.y ), atan( m.z ) ); }
inline float3x4 atan2( float3x4 y, float3x4 x ) { return float3x4( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ) ); }
inline float3x4 ceil( float3x4 m ) { return float3x4( ceil( m.x ), ceil( m.y ), ceil( m.z ) ); }
inline float3x4 clamp( float3x4 m, float3x4 min, float3x4 max ) { return float3x4( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ) ); }
inline float3x4 cos( float3x4 m ) { return float3x4( cos( m.x ), cos( m.y ), cos( m.z ) ); }
inline float3x4 cosh( float3x4 m ) { return float3x4( cosh( m.x ), cosh( m.y ), cosh( m.z ) ); }
inline float3x4 degrees( float3x4 m ) { return float3x4( degrees( m.x ), degrees( m.y ), degrees( m.z ) ); } 
inline float3x4 exp( float3x4 m ) { return float3x4( exp( m.x ), exp( m.y ), exp( m.z ) ); }
inline float3x4 exp2( float3x4 m ) { return float3x4( exp2( m.x ), exp2( m.y ), exp2( m.z ) ); }
inline float3x4 floor( float3x4 m ) { return float3x4( floor( m.x ), floor( m.y ), floor( m.z ) ); }
inline float3x4 fmod( float3x4 a, float3x4 b ) { return float3x4( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ) ); }
inline float3x4 frac( float3x4 m ) { return float3x4( frac( m.x ), frac( m.y ), frac( m.z ) ); }
inline float3x4 lerp( float3x4 a, float3x4 b, float s ) { return float3x4( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ) ); }
inline float3x4 log( float3x4 m ) { return float3x4( log( m.x ), log( m.y ), log( m.z ) ); }
inline float3x4 log2( float3x4 m ) { return float3x4( log2( m.x ), log2( m.y ), log2( m.z ) ); }
inline float3x4 log10( float3x4 m ) { return float3x4( log10( m.x ), log10( m.y ), log10( m.z ) ); }
inline float3x4 mad( float3x4 a, float3x4 b, float3x4 c ) { return a * b + c; }
inline float3x4 max( float3x4 a, float3x4 b ) { return float3x4( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ) ); }
inline float3x4 min( float3x4 a, float3x4 b ) { return float3x4( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ) ); }
inline float3x4 pow( float3x4 a, float3x4 b ) { return float3x4( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ) ); }
inline float3x4 radians( float3x4 m ) { return float3x4( radians( m.x ), radians( m.y ), radians( m.z ) ); } 
inline float3x4 rcp( float3x4 m ) { return float3x4( rcp( m.x ), rcp( m.y ), rcp( m.z ) ); }
inline float3x4 round( float3x4 m ) { return float3x4( round( m.x ), round( m.y ), round( m.z ) ); }
inline float3x4 rsqrt( float3x4 m ) { return float3x4( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ) ); }
inline float3x4 saturate( float3x4 m ) { return float3x4( saturate( m.x ), saturate( m.y ), saturate( m.z ) ); }
inline float3x4 sign( float3x4 m ) { return float3x4( sign( m.x ), sign( m.y ), sign( m.z ) ); }
inline float3x4 sin( float3x4 m ) { return float3x4( sin( m.x ), sin( m.y ), sin( m.z ) ); }
inline float3x4 sinh( float3x4 m ) { return float3x4( sinh( m.x ), sinh( m.y ), sinh( m.z ) ); }
inline float3x4 smoothstep( float3x4 min, float3x4 max, float3x4 m ) { return float3x4( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ) ); }
inline float3x4 smootherstep( float3x4 min, float3x4 max, float3x4 m ) { return float3x4( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ) ); }
inline float3x4 sqrt( float3x4 m ) { return float3x4( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ) ); }
inline float3x4 step( float3x4 a, float3x4 b ) { return float3x4( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ) ); }
inline float3x4 tan( float3x4 m ) { return float3x4( tan( m.x ), tan( m.y ), tan( m.z ) ); }
inline float3x4 tanh( float3x4 m ) { return float3x4( tanh( m.x ), tanh( m.y ), tanh( m.z ) ); }
inline float3x4 trunc( float3x4 m ) { return float3x4( trunc( m.x ), trunc( m.y ), trunc( m.z ) ); }


struct float4x2
	{
	// rows
	float2 x;
	float2 y;
	float2 z;
	float2 w;

	// constructors
	inline float4x2() { }
	inline float4x2( float f ) : x( f ), y( f ), z( f ), w( f ) { } 
	inline explicit float4x2( float m[8] ) : x( m[0], m[1] ), y( m[2], m[3] ), z( m[4], m[5] ), w( m[6], m[7] ) { } 
	inline float4x2( float m00, float m01, float m10, float m11, float m20, float m21, float m30, float m31) : x( m00, m01 ), y( m10, m11 ), z( m20, m21 ), w( m30, m31 ) { } 
	inline float4x2( float2 x_, float2 y_, float2 z_, float2 w_ ) : x( x_ ), y( y_ ), z( z_ ), w( w_ ) { }

	// conversions
	inline float4x2( float4x2_t m ) : x( m.x ), y( m.y ), z( m.z ), w( m.w ) { }
	inline operator float4x2_t() const { float4x2_t m = { x, y, z, w }; return m; };

	// indexing
	inline float2 operator[]( int row ) { return ( (float2*) this )[ row ]; }
	};

// operators
inline float4x2& operator+=( float4x2& a, float4x2 b ) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; };
inline float4x2& operator-=( float4x2& a, float4x2 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; };
inline float4x2& operator*=( float4x2& a, float4x2 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; };
inline float4x2& operator/=( float4x2& a, float4x2 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; };
inline float4x2& operator+=( float4x2& a, float s ) { a.x += s; a.y += s; a.z += s; a.w += s; return a; };
inline float4x2& operator-=( float4x2& a, float s ) { a.x -= s; a.y -= s; a.z -= s; a.w -= s; return a; };
inline float4x2& operator*=( float4x2& a, float s ) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; };
inline float4x2& operator/=( float4x2& a, float s ) { a.x /= s; a.y /= s; a.z /= s; a.w /= s; return a; };
inline float4x2 operator+( float4x2 a, float4x2 b ) { return float4x2( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }
inline float4x2 operator-( float4x2 a, float4x2 b ) { return float4x2( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }
inline float4x2 operator*( float4x2 a, float4x2 b ) { return float4x2( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w ); }
inline float4x2 operator/( float4x2 a, float4x2 b ) { return float4x2( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w ); }
inline float4x2 operator+( float4x2 a, float b ) { return float4x2( a.x + b, a.y + b, a.z + b, a.w + b ); }
inline float4x2 operator-( float4x2 a, float b ) { return float4x2( a.x - b, a.y - b, a.z - b, a.w - b ); }
inline float4x2 operator*( float4x2 a, float b ) { return float4x2( a.x * b, a.y * b, a.z * b, a.w * b ); }
inline float4x2 operator/( float4x2 a, float b ) { return float4x2( a.x / b, a.y / b, a.z / b, a.w / b ); }
inline float4x2 operator+( float a, float4x2 b ) { return float4x2( a + b.x, a + b.y, a + b.z, a + b.w ); }
inline float4x2 operator-( float a, float4x2 b ) { return float4x2( a - b.x, a - b.y, a - b.z, a - b.w ); }
inline float4x2 operator*( float a, float4x2 b ) { return float4x2( a * b.x, a * b.y, a * b.z, a * b.w ); }
inline float4x2 operator/( float a, float4x2 b ) { return float4x2( a / b.x, a / b.y, a / b.z, a / b.w ); }

// functions
inline float4x2 abs( float4x2 m ) { return float4x2( abs( m.x ), abs( m.y ), abs( m.z ), abs( m.w ) ); }
inline float4x2 acos( float4x2 m ) { return float4x2( acos( m.x ), acos( m.y ), acos( m.z ), acos( m.w ) ); }
inline bool all( float4x2 m ) { return all( m.x ) && all( m.y ) && all( m.z ) && all( m.w ); }
inline bool any( float4x2 m ) { return any( m.x ) || any( m.y ) || any( m.z ) || any( m.w ); }
inline float4x2 asin( float4x2 m ) { return float4x2( asin( m.x ), asin( m.y ), asin( m.z ), asin( m.w ) ); }
inline float4x2 atan( float4x2 m ) { return float4x2( atan( m.x ), atan( m.y ), atan( m.z ), atan( m.w ) ); }
inline float4x2 atan2( float4x2 y, float4x2 x ) { return float4x2( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ), atan2( y.w, x.w ) ); }
inline float4x2 ceil( float4x2 m ) { return float4x2( ceil( m.x ), ceil( m.y ), ceil( m.z ), ceil( m.w ) ); }
inline float4x2 clamp( float4x2 m, float4x2 min, float4x2 max ) { return float4x2( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ), clamp( m.w, min.w, max.w ) ); }
inline float4x2 cos( float4x2 m ) { return float4x2( cos( m.x ), cos( m.y ), cos( m.z ), cos( m.w ) ); }
inline float4x2 cosh( float4x2 m ) { return float4x2( cosh( m.x ), cosh( m.y ), cosh( m.z ), cosh( m.w ) ); }
inline float4x2 degrees( float4x2 m ) { return float4x2( degrees( m.x ), degrees( m.y ), degrees( m.z ), degrees( m.w ) ); } 
inline float4x2 exp( float4x2 m ) { return float4x2( exp( m.x ), exp( m.y ), exp( m.z ), exp( m.w ) ); }
inline float4x2 exp2( float4x2 m ) { return float4x2( exp2( m.x ), exp2( m.y ), exp2( m.z ), exp2( m.w ) ); }
inline float4x2 floor( float4x2 m ) { return float4x2( floor( m.x ), floor( m.y ), floor( m.z ), floor( m.w ) ); }
inline float4x2 fmod( float4x2 a, float4x2 b ) { return float4x2( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ), fmod( a.w, b.w ) ); }
inline float4x2 frac( float4x2 m ) { return float4x2( frac( m.x ), frac( m.y ), frac( m.z ), frac( m.w ) ); }
inline float4x2 lerp( float4x2 a, float4x2 b, float s ) { return float4x2( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ), lerp( a.w, b.w, s ) ); }
inline float4x2 log( float4x2 m ) { return float4x2( log( m.x ), log( m.y ), log( m.z ), log( m.w ) ); }
inline float4x2 log2( float4x2 m ) { return float4x2( log2( m.x ), log2( m.y ), log2( m.z ), log2( m.w ) ); }
inline float4x2 log10( float4x2 m ) { return float4x2( log10( m.x ), log10( m.y ), log10( m.z ), log10( m.w ) ); }
inline float4x2 mad( float4x2 a, float4x2 b, float4x2 c ) { return a * b + c; }
inline float4x2 max( float4x2 a, float4x2 b ) { return float4x2( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ), max( a.w, b.w ) ); }
inline float4x2 min( float4x2 a, float4x2 b ) { return float4x2( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ), min( a.w, b.w ) ); }
inline float4x2 pow( float4x2 a, float4x2 b ) { return float4x2( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ), pow( a.w, b.w ) ); }
inline float4x2 radians( float4x2 m ) { return float4x2( radians( m.x ), radians( m.y ), radians( m.z ), radians( m.w ) ); } 
inline float4x2 rcp( float4x2 m ) { return float4x2( rcp( m.x ), rcp( m.y ), rcp( m.z ), rcp( m.w ) ); }
inline float4x2 round( float4x2 m ) { return float4x2( round( m.x ), round( m.y ), round( m.z ), round( m.w ) ); }
inline float4x2 rsqrt( float4x2 m ) { return float4x2( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ), rsqrt( m.w ) ); }
inline float4x2 saturate( float4x2 m ) { return float4x2( saturate( m.x ), saturate( m.y ), saturate( m.z ), saturate( m.w ) ); }
inline float4x2 sign( float4x2 m ) { return float4x2( sign( m.x ), sign( m.y ), sign( m.z ), sign( m.w ) ); }
inline float4x2 sin( float4x2 m ) { return float4x2( sin( m.x ), sin( m.y ), sin( m.z ), sin( m.w ) ); }
inline float4x2 sinh( float4x2 m ) { return float4x2( sinh( m.x ), sinh( m.y ), sinh( m.z ), sinh( m.w ) ); }
inline float4x2 smoothstep( float4x2 min, float4x2 max, float4x2 m ) { return float4x2( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ), smoothstep( min.w, max.w, m.w ) ); }
inline float4x2 smootherstep( float4x2 min, float4x2 max, float4x2 m ) { return float4x2( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ), smootherstep( min.w, max.w, m.w ) ); }
inline float4x2 sqrt( float4x2 m ) { return float4x2( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ), sqrt( m.w ) ); }
inline float4x2 step( float4x2 a, float4x2 b ) { return float4x2( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ), step( a.w, b.w ) ); }
inline float4x2 tan( float4x2 m ) { return float4x2( tan( m.x ), tan( m.y ), tan( m.z ), tan( m.w ) ); }
inline float4x2 tanh( float4x2 m ) { return float4x2( tanh( m.x ), tanh( m.y ), tanh( m.z ), tanh( m.w ) ); }
inline float4x2 trunc( float4x2 m ) { return float4x2( trunc( m.x ), trunc( m.y ), trunc( m.z ), trunc( m.w ) ); }


struct float4x3
	{
	// rows
	float3 x;
	float3 y;
	float3 z;
	float3 w;

	// constructors
	inline float4x3() { }
	inline float4x3( float f ) : x( f ), y( f ), z( f ), w( f ) { } 
	inline explicit float4x3( float m[12] ) : x( m[0], m[1], m[2] ), y( m[3], m[4], m[5] ), z( m[6], m[7], m[8] ), w( m[9], m[10], m[11] ) { } 
	inline float4x3( float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22, float m30, float m31, float m32 ) : x( m00, m01, m02 ), y( m10, m11, m12 ), z( m20, m21, m22 ), w( m30, m31, m32 ) { } 
	inline float4x3( float3 x_, float3 y_, float3 z_, float3 w_ ) : x( x_ ), y( y_ ), z( z_ ), w( w_ ) { }
	
	// conversions
	inline float4x3( float4x3_t m ) : x( m.x ), y( m.y ), z( m.z ), w( m.w ) { }
	inline operator float4x3_t() const { float4x3_t m = { x, y, z, w }; return m; };

	// indexing
	inline float3 operator[]( int row ) { return ( (float3*) this )[ row ]; }
	};

// operators
inline float4x3& operator+=( float4x3& a, float4x3 b ) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; };
inline float4x3& operator-=( float4x3& a, float4x3 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; };
inline float4x3& operator*=( float4x3& a, float4x3 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; };
inline float4x3& operator/=( float4x3& a, float4x3 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; };
inline float4x3& operator+=( float4x3& a, float s ) { a.x += s; a.y += s; a.z += s; a.w += s; return a; };
inline float4x3& operator-=( float4x3& a, float s ) { a.x -= s; a.y -= s; a.z -= s; a.w -= s; return a; };
inline float4x3& operator*=( float4x3& a, float s ) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; };
inline float4x3& operator/=( float4x3& a, float s ) { a.x /= s; a.y /= s; a.z /= s; a.w /= s; return a; };
inline float4x3 operator+( float4x3 a, float4x3 b ) { return float4x3( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }
inline float4x3 operator-( float4x3 a, float4x3 b ) { return float4x3( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }
inline float4x3 operator*( float4x3 a, float4x3 b ) { return float4x3( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w ); }
inline float4x3 operator/( float4x3 a, float4x3 b ) { return float4x3( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w ); }
inline float4x3 operator+( float4x3 a, float b ) { return float4x3( a.x + b, a.y + b, a.z + b, a.w + b ); }
inline float4x3 operator-( float4x3 a, float b ) { return float4x3( a.x - b, a.y - b, a.z - b, a.w - b ); }
inline float4x3 operator*( float4x3 a, float b ) { return float4x3( a.x * b, a.y * b, a.z * b, a.w * b ); }
inline float4x3 operator/( float4x3 a, float b ) { return float4x3( a.x / b, a.y / b, a.z / b, a.w / b ); }
inline float4x3 operator+( float a, float4x3 b ) { return float4x3( a + b.x, a + b.y, a + b.z, a + b.w ); }
inline float4x3 operator-( float a, float4x3 b ) { return float4x3( a - b.x, a - b.y, a - b.z, a - b.w ); }
inline float4x3 operator*( float a, float4x3 b ) { return float4x3( a * b.x, a * b.y, a * b.z, a * b.w ); }
inline float4x3 operator/( float a, float4x3 b ) { return float4x3( a / b.x, a / b.y, a / b.z, a / b.w ); }

// functions
inline float4x3 abs( float4x3 m ) { return float4x3( abs( m.x ), abs( m.y ), abs( m.z ), abs( m.w ) ); }
inline float4x3 acos( float4x3 m ) { return float4x3( acos( m.x ), acos( m.y ), acos( m.z ), acos( m.w ) ); }
inline bool all( float4x3 m ) { return all( m.x ) && all( m.y ) && all( m.z ) && all( m.w ); }
inline bool any( float4x3 m ) { return any( m.x ) || any( m.y ) || any( m.z ) || any( m.w ); }
inline float4x3 asin( float4x3 m ) { return float4x3( asin( m.x ), asin( m.y ), asin( m.z ), asin( m.w ) ); }
inline float4x3 atan( float4x3 m ) { return float4x3( atan( m.x ), atan( m.y ), atan( m.z ), atan( m.w ) ); }
inline float4x3 atan2( float4x3 y, float4x3 x ) { return float4x3( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ), atan2( y.w, x.w ) ); }
inline float4x3 ceil( float4x3 m ) { return float4x3( ceil( m.x ), ceil( m.y ), ceil( m.z ), ceil( m.w ) ); }
inline float4x3 clamp( float4x3 m, float4x3 min, float4x3 max ) { return float4x3( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ), clamp( m.w, min.w, max.w ) ); }
inline float4x3 cos( float4x3 m ) { return float4x3( cos( m.x ), cos( m.y ), cos( m.z ), cos( m.w ) ); }
inline float4x3 cosh( float4x3 m ) { return float4x3( cosh( m.x ), cosh( m.y ), cosh( m.z ), cosh( m.w ) ); }
inline float4x3 degrees( float4x3 m ) { return float4x3( degrees( m.x ), degrees( m.y ), degrees( m.z ), degrees( m.w ) ); } 
inline float4x3 exp( float4x3 m ) { return float4x3( exp( m.x ), exp( m.y ), exp( m.z ), exp( m.w ) ); }
inline float4x3 exp2( float4x3 m ) { return float4x3( exp2( m.x ), exp2( m.y ), exp2( m.z ), exp2( m.w ) ); }
inline float4x3 floor( float4x3 m ) { return float4x3( floor( m.x ), floor( m.y ), floor( m.z ), floor( m.w ) ); }
inline float4x3 fmod( float4x3 a, float4x3 b ) { return float4x3( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ), fmod( a.w, b.w ) ); }
inline float4x3 frac( float4x3 m ) { return float4x3( frac( m.x ), frac( m.y ), frac( m.z ), frac( m.w ) ); }
inline float4x3 lerp( float4x3 a, float4x3 b, float s ) { return float4x3( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ), lerp( a.w, b.w, s ) ); }
inline float4x3 log( float4x3 m ) { return float4x3( log( m.x ), log( m.y ), log( m.z ), log( m.w ) ); }
inline float4x3 log2( float4x3 m ) { return float4x3( log2( m.x ), log2( m.y ), log2( m.z ), log2( m.w ) ); }
inline float4x3 log10( float4x3 m ) { return float4x3( log10( m.x ), log10( m.y ), log10( m.z ), log10( m.w ) ); }
inline float4x3 mad( float4x3 a, float4x3 b, float4x3 c ) { return a * b + c; }
inline float4x3 max( float4x3 a, float4x3 b ) { return float4x3( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ), max( a.w, b.w ) ); }
inline float4x3 min( float4x3 a, float4x3 b ) { return float4x3( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ), min( a.w, b.w ) ); }
inline float4x3 pow( float4x3 a, float4x3 b ) { return float4x3( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ), pow( a.w, b.w ) ); }
inline float4x3 radians( float4x3 m ) { return float4x3( radians( m.x ), radians( m.y ), radians( m.z ), radians( m.w ) ); } 
inline float4x3 rcp( float4x3 m ) { return float4x3( rcp( m.x ), rcp( m.y ), rcp( m.z ), rcp( m.w ) ); }
inline float4x3 round( float4x3 m ) { return float4x3( round( m.x ), round( m.y ), round( m.z ), round( m.w ) ); }
inline float4x3 rsqrt( float4x3 m ) { return float4x3( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ), rsqrt( m.w ) ); }
inline float4x3 saturate( float4x3 m ) { return float4x3( saturate( m.x ), saturate( m.y ), saturate( m.z ), saturate( m.w ) ); }
inline float4x3 sign( float4x3 m ) { return float4x3( sign( m.x ), sign( m.y ), sign( m.z ), sign( m.w ) ); }
inline float4x3 sin( float4x3 m ) { return float4x3( sin( m.x ), sin( m.y ), sin( m.z ), sin( m.w ) ); }
inline float4x3 sinh( float4x3 m ) { return float4x3( sinh( m.x ), sinh( m.y ), sinh( m.z ), sinh( m.w ) ); }
inline float4x3 smoothstep( float4x3 min, float4x3 max, float4x3 m ) { return float4x3( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ), smoothstep( min.w, max.w, m.w ) ); }
inline float4x3 smootherstep( float4x3 min, float4x3 max, float4x3 m ) { return float4x3( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ), smootherstep( min.w, max.w, m.w ) ); }
inline float4x3 sqrt( float4x3 m ) { return float4x3( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ), sqrt( m.w ) ); }
inline float4x3 step( float4x3 a, float4x3 b ) { return float4x3( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ), step( a.w, b.w ) ); }
inline float4x3 tan( float4x3 m ) { return float4x3( tan( m.x ), tan( m.y ), tan( m.z ), tan( m.w ) ); }
inline float4x3 tanh( float4x3 m ) { return float4x3( tanh( m.x ), tanh( m.y ), tanh( m.z ), tanh( m.w ) ); }
inline float4x3 trunc( float4x3 m ) { return float4x3( trunc( m.x ), trunc( m.y ), trunc( m.z ), trunc( m.w ) ); }


struct float4x4
	{
	// rows
	float4 x;
	float4 y;
	float4 z;
	float4 w;

	// constructors
	inline float4x4() { }
	inline float4x4( float f ) : x( f ), y( f ), z( f ), w( f ) { } 
	inline explicit float4x4( float m[16] ) : x( m[0], m[1], m[2], m[3] ), y( m[4], m[5], m[6], m[7] ), z( m[8], m[9], m[10], m[11] ), w( m[12], m[13], m[14], m[15] ) { } 
	inline float4x4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 ) : x( m00, m01, m02, m03 ), y( m10, m11, m12, m13 ), z( m20, m21, m22, m23 ), w( m30, m31, m32, m33 ) { } 
	inline float4x4( float4 x_, float4 y_, float4 z_, float4 w_ ) : x( x_ ), y( y_ ), z( z_ ), w( w_ ) { }
	
	// conversions
	inline float4x4( float4x4_t m ) : x( m.x ), y( m.y ), z( m.z ), w( m.w ) { }
	inline operator float4x4_t() const { float4x4_t m = { x, y, z, w }; return m; };

	// indexing
	inline float4 operator[]( int row ) { return ( (float4*) this )[ row ]; }

	// constants
	static inline float4x4 identity() { return float4x4( float4( 1.0f, 0.0f, 0.0f, 0.0f ), float4( 0.0f, 1.0f, 0.0f, 0.0f ), float4( 0.0f, 0.0f, 1.0f, 0.0f ), float4( 0.0f, 0.0f, 0.0f, 1.0f ) ); }
	};

// operators
inline float4x4& operator+=( float4x4& a, float4x4 b ) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; };
inline float4x4& operator-=( float4x4& a, float4x4 b ) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; };
inline float4x4& operator*=( float4x4& a, float4x4 b ) { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; };
inline float4x4& operator/=( float4x4& a, float4x4 b ) { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; };
inline float4x4& operator+=( float4x4& a, float s ) { a.x += s; a.y += s; a.z += s; a.w += s; return a; };
inline float4x4& operator-=( float4x4& a, float s ) { a.x -= s; a.y -= s; a.z -= s; a.w -= s; return a; };
inline float4x4& operator*=( float4x4& a, float s ) { a.x *= s; a.y *= s; a.z *= s; a.w *= s; return a; };
inline float4x4& operator/=( float4x4& a, float s ) { a.x /= s; a.y /= s; a.z /= s; a.w /= s; return a; };
inline float4x4 operator+( float4x4 a, float4x4 b ) { return float4x4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }
inline float4x4 operator-( float4x4 a, float4x4 b ) { return float4x4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }
inline float4x4 operator*( float4x4 a, float4x4 b ) { return float4x4( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w ); }
inline float4x4 operator/( float4x4 a, float4x4 b ) { return float4x4( a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w ); }
inline float4x4 operator+( float4x4 a, float b ) { return float4x4( a.x + b, a.y + b, a.z + b, a.w + b ); }
inline float4x4 operator-( float4x4 a, float b ) { return float4x4( a.x - b, a.y - b, a.z - b, a.w - b ); }
inline float4x4 operator*( float4x4 a, float b ) { return float4x4( a.x * b, a.y * b, a.z * b, a.w * b ); }
inline float4x4 operator/( float4x4 a, float b ) { return float4x4( a.x / b, a.y / b, a.z / b, a.w / b ); }
inline float4x4 operator+( float a, float4x4 b ) { return float4x4( a + b.x, a + b.y, a + b.z, a + b.w ); }
inline float4x4 operator-( float a, float4x4 b ) { return float4x4( a - b.x, a - b.y, a - b.z, a - b.w ); }
inline float4x4 operator*( float a, float4x4 b ) { return float4x4( a * b.x, a * b.y, a * b.z, a * b.w ); }
inline float4x4 operator/( float a, float4x4 b ) { return float4x4( a / b.x, a / b.y, a / b.z, a / b.w ); }

// functions
inline float4x4 abs( float4x4 m ) { return float4x4( abs( m.x ), abs( m.y ), abs( m.z ), abs( m.w ) ); }
inline float4x4 acos( float4x4 m ) { return float4x4( acos( m.x ), acos( m.y ), acos( m.z ), acos( m.w ) ); }
inline bool all( float4x4 m ) { return all( m.x ) && all( m.y ) && all( m.z ) && all( m.w ); }
inline bool any( float4x4 m ) { return any( m.x ) || any( m.y ) || any( m.z ) || any( m.w ); }
inline float4x4 asin( float4x4 m ) { return float4x4( asin( m.x ), asin( m.y ), asin( m.z ), asin( m.w ) ); }
inline float4x4 atan( float4x4 m ) { return float4x4( atan( m.x ), atan( m.y ), atan( m.z ), atan( m.w ) ); }
inline float4x4 atan2( float4x4 y, float4x4 x ) { return float4x4( atan2( y.x, x.x ), atan2( y.y, x.y ), atan2( y.z, x.z ), atan2( y.w, x.w ) ); }
inline float4x4 ceil( float4x4 m ) { return float4x4( ceil( m.x ), ceil( m.y ), ceil( m.z ), ceil( m.w ) ); }
inline float4x4 clamp( float4x4 m, float4x4 min, float4x4 max ) { return float4x4( clamp( m.x, min.x, max.x ), clamp( m.y, min.y, max.y ), clamp( m.z, min.z, max.z ), clamp( m.w, min.w, max.w ) ); }
inline float4x4 cos( float4x4 m ) { return float4x4( cos( m.x ), cos( m.y ), cos( m.z ), cos( m.w ) ); }
inline float4x4 cosh( float4x4 m ) { return float4x4( cosh( m.x ), cosh( m.y ), cosh( m.z ), cosh( m.w ) ); }
inline float4x4 degrees( float4x4 m ) { return float4x4( degrees( m.x ), degrees( m.y ), degrees( m.z ), degrees( m.w ) ); } 
inline float4x4 exp( float4x4 m ) { return float4x4( exp( m.x ), exp( m.y ), exp( m.z ), exp( m.w ) ); }
inline float4x4 exp2( float4x4 m ) { return float4x4( exp2( m.x ), exp2( m.y ), exp2( m.z ), exp2( m.w ) ); }
inline float4x4 floor( float4x4 m ) { return float4x4( floor( m.x ), floor( m.y ), floor( m.z ), floor( m.w ) ); }
inline float4x4 fmod( float4x4 a, float4x4 b ) { return float4x4( fmod( a.x, b.x ), fmod( a.y, b.y ), fmod( a.z, b.z ), fmod( a.w, b.w ) ); }
inline float4x4 frac( float4x4 m ) { return float4x4( frac( m.x ), frac( m.y ), frac( m.z ), frac( m.w ) ); }
inline float4x4 lerp( float4x4 a, float4x4 b, float s ) { return float4x4( lerp( a.x, b.x, s ), lerp( a.y, b.y, s ), lerp( a.z, b.z, s ), lerp( a.w, b.w, s ) ); }
inline float4x4 log( float4x4 m ) { return float4x4( log( m.x ), log( m.y ), log( m.z ), log( m.w ) ); }
inline float4x4 log2( float4x4 m ) { return float4x4( log2( m.x ), log2( m.y ), log2( m.z ), log2( m.w ) ); }
inline float4x4 log10( float4x4 m ) { return float4x4( log10( m.x ), log10( m.y ), log10( m.z ), log10( m.w ) ); }
inline float4x4 mad( float4x4 a, float4x4 b, float4x4 c ) { return a * b + c; }
inline float4x4 max( float4x4 a, float4x4 b ) { return float4x4( max( a.x, b.x ), max( a.y, b.y ), max( a.z, b.z ), max( a.w, b.w ) ); }
inline float4x4 min( float4x4 a, float4x4 b ) { return float4x4( min( a.x, b.x ), min( a.y, b.y ), min( a.z, b.z ), min( a.w, b.w ) ); }
inline float4x4 pow( float4x4 a, float4x4 b ) { return float4x4( pow( a.x, b.x ), pow( a.y, b.y ), pow( a.z, b.z ), pow( a.w, b.w ) ); }
inline float4x4 radians( float4x4 m ) { return float4x4( radians( m.x ), radians( m.y ), radians( m.z ), radians( m.w ) ); } 
inline float4x4 rcp( float4x4 m ) { return float4x4( rcp( m.x ), rcp( m.y ), rcp( m.z ), rcp( m.w ) ); }
inline float4x4 round( float4x4 m ) { return float4x4( round( m.x ), round( m.y ), round( m.z ), round( m.w ) ); }
inline float4x4 rsqrt( float4x4 m ) { return float4x4( rsqrt( m.x ), rsqrt( m.y ), rsqrt( m.z ), rsqrt( m.w ) ); }
inline float4x4 saturate( float4x4 m ) { return float4x4( saturate( m.x ), saturate( m.y ), saturate( m.z ), saturate( m.w ) ); }
inline float4x4 sign( float4x4 m ) { return float4x4( sign( m.x ), sign( m.y ), sign( m.z ), sign( m.w ) ); }
inline float4x4 sin( float4x4 m ) { return float4x4( sin( m.x ), sin( m.y ), sin( m.z ), sin( m.w ) ); }
inline float4x4 sinh( float4x4 m ) { return float4x4( sinh( m.x ), sinh( m.y ), sinh( m.z ), sinh( m.w ) ); }
inline float4x4 smoothstep( float4x4 min, float4x4 max, float4x4 m ) { return float4x4( smoothstep( min.x, max.x, m.x ), smoothstep( min.y, max.y, m.y ), smoothstep( min.z, max.z, m.z ), smoothstep( min.w, max.w, m.w ) ); }
inline float4x4 smootherstep( float4x4 min, float4x4 max, float4x4 m ) { return float4x4( smootherstep( min.x, max.x, m.x ), smootherstep( min.y, max.y, m.y ), smootherstep( min.z, max.z, m.z ), smootherstep( min.w, max.w, m.w ) ); }
inline float4x4 sqrt( float4x4 m ) { return float4x4( sqrt( m.x ), sqrt( m.y ), sqrt( m.z ), sqrt( m.w ) ); }
inline float4x4 step( float4x4 a, float4x4 b ) { return float4x4( step( a.x, b.x ), step( a.y, b.y ), step( a.z, b.z ), step( a.w, b.w ) ); }
inline float4x4 tan( float4x4 m ) { return float4x4( tan( m.x ), tan( m.y ), tan( m.z ), tan( m.w ) ); }
inline float4x4 tanh( float4x4 m ) { return float4x4( tanh( m.x ), tanh( m.y ), tanh( m.z ), tanh( m.w ) ); }
inline float4x4 trunc( float4x4 m ) { return float4x4( trunc( m.x ), trunc( m.y ), trunc( m.z ), trunc( m.w ) ); }


// matrix math

inline float2x2 transpose( float2x2 m ) { return float2x2( float2( m.x.x, m.y.x ), float2( m.x.y, m.y.y ) ); }
inline float3x2 transpose( float2x3 m ) { return float3x2( float2( m.x.x, m.y.x ), float2( m.x.y, m.y.y ), float2( m.x.z, m.y.z ) ); }
inline float2x3 transpose( float3x2 m ) { return float2x3( float3( m.x.x, m.y.x, m.z.x ), float3( m.x.y, m.y.y, m.z.y ) ); }
inline float3x3 transpose( float3x3 m ) { return float3x3( float3( m.x.x, m.y.x, m.z.x ), float3( m.x.y, m.y.y, m.z.y ), float3( m.x.z, m.y.z, m.z.z ) ); }
inline float4x2 transpose( float2x4 m ) { return float4x2( float2( m.x.x, m.y.x ), float2( m.x.y, m.y.y ), float2( m.x.z, m.y.z ), float2( m.x.w, m.y.w ) ); }
inline float4x3 transpose( float3x4 m ) { return float4x3( float3( m.x.x, m.y.x, m.z.x ), float3( m.x.y, m.y.y, m.z.y ), float3( m.x.z, m.y.z, m.z.z ), float3( m.x.w, m.y.w, m.z.w ) ); }
inline float2x4 transpose( float4x2 m ) { return float2x4( float4( m.x.x, m.y.x, m.z.x, m.w.x ), float4( m.x.y, m.y.y, m.z.y, m.w.y ) ); }
inline float3x4 transpose( float4x3 m ) { return float3x4( float4( m.x.x, m.y.x, m.z.x, m.w.x ), float4( m.x.y, m.y.y, m.z.y, m.w.y ), float4( m.x.z, m.y.z, m.z.z, m.w.z ) ); }
inline float4x4 transpose( float4x4 m ) { return float4x4( float4( m.x.x, m.y.x, m.z.x, m.w.x ), float4( m.x.y, m.y.y, m.z.y, m.w.y ), float4( m.x.z, m.y.z, m.z.z, m.w.z ), float4( m.x.w, m.y.w, m.z.w, m.w.w ) ); }

inline float determinant( float2x2 m) { return m.x.x * m.y.y - m.x.y * m.y.x; }
inline float determinant( float3x3 m) { return m.x.x * m.y.y * m.z.z + m.x.y * m.y.z * m.z.x + m.x.z * m.y.x * m.z.y - m.x.x * m.y.z * m.z.y - m.x.y * m.y.x * m.z.z - m.x.z * m.y.y * m.z.x; }
inline float determinant( float4x4 m) { return m.x.w * m.y.z * m.z.y * m.w.x - m.x.z * m.y.w * m.z.y * m.w.x - m.x.w * m.y.y * m.z.z * m.w.x + m.x.y * m.y.w * m.z.z * m.w.x + m.x.z * m.y.y * m.z.w * m.w.x - m.x.y * m.y.z * m.z.w * m.w.x - m.x.w * m.y.z * m.z.x * m.w.y + m.x.z * m.y.w * m.z.x * m.w.y + m.x.w * m.y.x * m.z.z * m.w.y - m.x.x * m.y.w * m.z.z * m.w.y - m.x.z * m.y.x * m.z.w * m.w.y + m.x.x * m.y.z * m.z.w * m.w.y + m.x.w * m.y.y * m.z.x * m.w.z - m.x.y * m.y.w * m.z.x * m.w.z - m.x.w * m.y.x * m.z.y * m.w.z + m.x.x * m.y.w * m.z.y * m.w.z + m.x.y * m.y.x * m.z.w * m.w.z - m.x.x * m.y.y * m.z.w * m.w.z - m.x.z * m.y.y * m.z.x * m.w.w + m.x.y * m.y.z * m.z.x * m.w.w + m.x.z * m.y.x * m.z.y * m.w.w - m.x.x * m.y.z * m.z.y * m.w.w - m.x.y * m.y.x * m.z.z * m.w.w + m.x.x * m.y.y * m.z.z * m.w.w; }

inline bool is_identity( float2x2 m ) { return m.x.x == 1.0f && m.x.y == 0.0f && m.y.x == 0.0f && m.y.y == 1.0f; }
inline bool is_identity( float3x3 m ) { return m.x.x == 1.0f && m.x.y == 0.0f && m.x.z == 0.0f && m.y.x == 0.0f && m.y.y == 1.0f && m.y.z == 0.0f && m.z.x == 0.0f && m.z.y == 0.0f && m.z.z == 1.0f; }
inline bool is_identity( float4x4 m ) { return m.x.x == 1.0f && m.x.y == 0.0f && m.x.z == 0.0f && m.x.w == 0.0f && m.y.x == 0.0f && m.y.y == 1.0f && m.y.z == 0.0f && m.y.w == 0.0f && m.z.x == 0.0f && m.z.y == 0.0f && m.z.z == 1.0f && m.z.w == 0.0f && m.w.x == 0.0f && m.w.y == 0.0f && m.w.z == 0.0f && m.w.w == 1.0f; }

inline bool inverse( float2x2* out_matrix, float* out_determinant, float2x2 m ) { float d = determinant( m ); if( out_determinant ) *out_determinant = d; if( d != 0.0f && out_matrix ) *out_matrix = float2x2( float2( m.y.y / d, - m.x.y / d), float2( - m.y.x / d, m.x.x / d ) ); return d != 0.0f; }
inline bool inverse( float3x3* out_matrix, float* out_determinant, float3x3 m ) { float d = determinant( m ); if( out_determinant ) *out_determinant = d; if( d != 0.0f && out_matrix ) *out_matrix = float3x3( float3( ( m.y.y * m.z.z - m.y.z * m.z.y ) / d, ( m.x.z * m.z.y - m.x.y * m.z.z ) / d, ( m.x.y * m.y.z - m.x.z * m.y.y ) / d ), float3( ( m.y.z * m.z.x - m.y.x * m.z.z ) / d, ( m.x.x * m.z.z - m.x.z * m.z.x ) / d, ( m.x.z * m.y.x - m.x.x * m.y.z ) / d ), float3( ( m.y.x * m.z.y - m.y.y * m.z.x ) / d, ( m.x.y * m.z.x - m.x.x * m.z.y ) / d, ( m.x.x * m.y.y - m.x.y * m.y.x ) / d ) ); return d != 0.0f; }
inline bool inverse( float4x4* out_matrix, float* out_determinant, float4x4 m ) { float d = determinant( m ); if( out_determinant ) *out_determinant = d; if( d != 0.0f && out_matrix ) *out_matrix = float4x4( float4( ( m.y.z * m.z.w * m.w.y - m.y.w * m.z.z * m.w.y + m.y.w * m.z.y * m.w.z - m.y.y * m.z.w * m.w.z - m.y.z * m.z.y * m.w.w + m.y.y * m.z.z * m.w.w ) / d, ( m.x.w * m.z.z * m.w.y - m.x.z * m.z.w * m.w.y - m.x.w * m.z.y * m.w.z + m.x.y * m.z.w * m.w.z + m.x.z * m.z.y * m.w.w - m.x.y * m.z.z * m.w.w ) / d, ( m.x.z * m.y.w * m.w.y - m.x.w * m.y.z * m.w.y + m.x.w * m.y.y * m.w.z - m.x.y * m.y.w * m.w.z - m.x.z * m.y.y * m.w.w + m.x.y * m.y.z * m.w.w ) / d, ( m.x.w * m.y.z * m.z.y - m.x.z * m.y.w * m.z.y - m.x.w * m.y.y * m.z.z + m.x.y * m.y.w * m.z.z + m.x.z * m.y.y * m.z.w - m.x.y * m.y.z * m.z.w ) / d ), float4( ( m.y.w * m.z.z * m.w.x - m.y.z * m.z.w * m.w.x - m.y.w * m.z.x * m.w.z + m.y.x * m.z.w * m.w.z + m.y.z * m.z.x * m.w.w - m.y.x * m.z.z * m.w.w ) / d, ( m.x.z * m.z.w * m.w.x - m.x.w * m.z.z * m.w.x + m.x.w * m.z.x * m.w.z - m.x.x * m.z.w * m.w.z - m.x.z * m.z.x * m.w.w + m.x.x * m.z.z * m.w.w ) / d, ( m.x.w * m.y.z * m.w.x - m.x.z * m.y.w * m.w.x - m.x.w * m.y.x * m.w.z + m.x.x * m.y.w * m.w.z + m.x.z * m.y.x * m.w.w - m.x.x * m.y.z * m.w.w ) / d, ( m.x.z * m.y.w * m.z.x - m.x.w * m.y.z * m.z.x + m.x.w * m.y.x * m.z.z - m.x.x * m.y.w * m.z.z - m.x.z * m.y.x * m.z.w + m.x.x * m.y.z * m.z.w ) / d ), float4( ( m.y.y * m.z.w * m.w.x - m.y.w * m.z.y * m.w.x + m.y.w * m.z.x * m.w.y - m.y.x * m.z.w * m.w.y - m.y.y * m.z.x * m.w.w + m.y.x * m.z.y * m.w.w ) / d, ( m.x.w * m.z.y * m.w.x - m.x.y * m.z.w * m.w.x - m.x.w * m.z.x * m.w.y + m.x.x * m.z.w * m.w.y + m.x.y * m.z.x * m.w.w - m.x.x * m.z.y * m.w.w ) / d, ( m.x.y * m.y.w * m.w.x - m.x.w * m.y.y * m.w.x + m.x.w * m.y.x * m.w.y - m.x.x * m.y.w * m.w.y - m.x.y * m.y.x * m.w.w + m.x.x * m.y.y * m.w.w ) / d, ( m.x.w * m.y.y * m.z.x - m.x.y * m.y.w * m.z.x - m.x.w * m.y.x * m.z.y + m.x.x * m.y.w * m.z.y + m.x.y * m.y.x * m.z.w - m.x.x * m.y.y * m.z.w ) / d ), float4( ( m.y.z * m.z.y * m.w.x - m.y.y * m.z.z * m.w.x - m.y.z * m.z.x * m.w.y + m.y.x * m.z.z * m.w.y + m.y.y * m.z.x * m.w.z - m.y.x * m.z.y * m.w.z ) / d, ( m.x.y * m.z.z * m.w.x - m.x.z * m.z.y * m.w.x + m.x.z * m.z.x * m.w.y - m.x.x * m.z.z * m.w.y - m.x.y * m.z.x * m.w.z + m.x.x * m.z.y * m.w.z ) / d, ( m.x.z * m.y.y * m.w.x - m.x.y * m.y.z * m.w.x - m.x.z * m.y.x * m.w.y + m.x.x * m.y.z * m.w.y + m.x.y * m.y.x * m.w.z - m.x.x * m.y.y * m.w.z ) / d, ( m.x.y * m.y.z * m.z.x - m.x.z * m.y.y * m.z.x + m.x.z * m.y.x * m.z.y - m.x.x * m.y.z * m.z.y - m.x.y * m.y.x * m.z.z + m.x.x * m.y.y * m.z.z ) / d ) ); return d != 0.0f; }		
		 

// matrix multiplications

inline float mul( float a, float b ) { return a * b; }

inline float2 mul( float a, float2 b ) { return a * b; }
inline float3 mul( float a, float3 b ) { return a * b; }
inline float4 mul( float a, float4 b ) { return a * b; }

inline float2x2 mul( float a, float2x2 b ) { return a * b; }
inline float2x3 mul( float a, float2x3 b ) { return a * b; }
inline float3x2 mul( float a, float3x2 b ) { return a * b; }
inline float3x3 mul( float a, float3x3 b ) { return a * b; }
inline float2x4 mul( float a, float2x4 b ) { return a * b; }
inline float3x4 mul( float a, float3x4 b ) { return a * b; }
inline float4x2 mul( float a, float4x2 b ) { return a * b; }
inline float4x3 mul( float a, float4x3 b ) { return a * b; }
inline float4x4 mul( float a, float4x4 b ) { return a * b; }

inline float2 mul( float2 a, float b ) { return a * b; }
inline float3 mul( float3 a, float b ) { return a * b; }
inline float4 mul( float4 a, float b ) { return a * b; }

inline float mul( float2 a, float2 b ) { return dot( a, b ); }
inline float mul( float3 a, float3 b ) { return dot( a, b ); }
inline float mul( float4 a, float4 b ) { return dot( a, b ); }

inline float2 mul( float2 a, float2x2 b ) { return float2( a.x * b.x.x + a.y * b.y.x, a.x * b.x.y + a.y * b.y.y ); }
inline float3 mul( float2 a, float2x3 b ) { return float3( a.x * b.x.x + a.y * b.y.x, a.x * b.x.y + a.y * b.y.y, a.x * b.x.z + a.y * b.y.z ); }
inline float2 mul( float3 a, float3x2 b ) { return float2( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y ); }
inline float3 mul( float3 a, float3x3 b ) { return float3( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y, a.x * b.x.z + a.y * b.y.z + a.z * b.z.z ); }
inline float4 mul( float2 a, float2x4 b ) { return float4( a.x * b.x.x + a.y * b.y.x, a.x * b.x.y + a.y * b.y.y, a.x * b.x.z + a.y * b.y.z, a.x * b.x.w + a.y * b.y.w ); }
inline float4 mul( float3 a, float3x4 b ) { return float4( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y, a.x * b.x.z + a.y * b.y.z + a.z * b.z.z, a.x * b.x.w + a.y * b.y.w + a.z * b.z.w ); }
inline float2 mul( float4 a, float4x2 b ) { return float2( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x + a.w * b.w.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y + a.w * b.w.y ); }
inline float3 mul( float4 a, float4x3 b ) { return float3( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x + a.w * b.w.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y + a.w * b.w.y, a.x * b.x.z + a.y * b.y.z + a.z * b.z.z + a.w * b.w.z ); }
inline float4 mul( float4 a, float4x4 b ) { return float4( a.x * b.x.x + a.y * b.y.x + a.z * b.z.x + a.w * b.w.x, a.x * b.x.y + a.y * b.y.y + a.z * b.z.y + a.w * b.w.y, a.x * b.x.z + a.y * b.y.z + a.z * b.z.z + a.w * b.w.z, a.x * b.x.w + a.y * b.y.w + a.z * b.z.w + a.w * b.w.w ); }

inline float2x2 mul( float2x2 a, float b ) { return a * b; }
inline float2x3 mul( float2x3 a, float b ) { return a * b; }
inline float3x2 mul( float3x2 a, float b ) { return a * b; }
inline float3x3 mul( float3x3 a, float b ) { return a * b; }
inline float2x4 mul( float2x4 a, float b ) { return a * b; }
inline float3x4 mul( float3x4 a, float b ) { return a * b; }
inline float4x2 mul( float4x2 a, float b ) { return a * b; }
inline float4x3 mul( float4x3 a, float b ) { return a * b; }
inline float4x4 mul( float4x4 a, float b ) { return a * b; }

inline float2 mul( float2x2 a, float2 b ) { return float2( a.x.x * b.x + a.x.y * b.y, a.y.x * b.x + a.y.y * b.y ); }
inline float2 mul( float2x3 a, float3 b ) { return float2( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z ); }
inline float3 mul( float3x2 a, float2 b ) { return float3( a.x.x * b.x + a.x.y * b.y, a.y.x * b.x + a.y.y * b.y, a.z.x * b.x + a.z.y * b.y ); }
inline float3 mul( float3x3 a, float3 b ) { return float3( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z, a.z.x * b.x + a.z.y * b.y + a.z.z * b.z ); }
inline float2 mul( float2x4 a, float4 b ) { return float2( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z + a.x.w * b.w, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z + a.y.w * b.w ); }
inline float3 mul( float3x4 a, float4 b ) { return float3( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z + a.x.w * b.w, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z + a.y.w * b.w, a.z.x * b.x + a.z.y * b.y + a.z.z * b.z + a.z.w * b.w ); }
inline float4 mul( float4x2 a, float2 b ) { return float4( a.x.x * b.x + a.x.y * b.y, a.y.x * b.x + a.y.y * b.y, a.z.x * b.x + a.z.y * b.y, a.w.x * b.x + a.w.y * b.y ); }
inline float4 mul( float4x3 a, float3 b ) { return float4( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z, a.z.x * b.x + a.z.y * b.y + a.z.z * b.z, a.w.x * b.x + a.w.y * b.y + a.w.z * b.z ); }
inline float4 mul( float4x4 a, float4 b ) { return float4( a.x.x * b.x + a.x.y * b.y + a.x.z * b.z + a.x.w * b.w, a.y.x * b.x + a.y.y * b.y + a.y.z * b.z + a.y.w * b.w, a.z.x * b.x + a.z.y * b.y + a.z.z * b.z + a.z.w * b.w, a.w.x * b.x + a.w.y * b.y + a.w.z * b.z + a.w.w * b.w ); }

inline float2x2 mul( float2x2 a, float2x2 b ) { return float2x2( float2( a.x.x * b.x.x + a.x.y * b.y.x, a.x.x * b.x.y + a.x.y * b.y.y ), float2( a.y.x * b.x.x + a.y.y * b.y.x, a.y.x * b.x.y + a.y.y * b.y.y ) ); }
inline float3x3 mul( float3x2 a, float2x3 b ) { return float3x3( float3( a.x.x * b.x.x + a.x.y * b.y.x, a.x.x * b.x.y + a.x.y * b.y.y,  a.x.x * b.x.z + a.x.y * b.y.z ), float3( a.y.x * b.x.x + a.y.y * b.y.x, a.y.x * b.x.y + a.y.y * b.y.y, a.y.x * b.x.z + a.y.y * b.y.z ), float3( a.z.x * b.x.x + a.z.y * b.y.x, a.z.x * b.x.y + a.z.y * b.y.y, a.z.x * b.x.z + a.z.y * b.y.z ) ); }
inline float2x2 mul( float2x3 a, float3x2 b ) { return float2x2( float2( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y ), float2( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y ) ); }
inline float3x3 mul( float3x3 a, float3x3 b ) { return float3x3( float3( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y, a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z ), float3( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y, a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z ), float3( a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x, a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y, a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z ) ); }
inline float4x4 mul( float4x2 a, float2x4 b ) { return float4x4( float4( a.x.x * b.x.x + a.x.y * b.y.x, a.x.x * b.x.y + a.x.y * b.y.y, a.x.x * b.x.z + a.x.y * b.y.z, a.x.x * b.x.w + a.x.y * b.y.w ), float4( a.y.x * b.x.x + a.y.y * b.y.x, a.y.x * b.x.y + a.y.y * b.y.y, a.y.x * b.x.z + a.y.y * b.y.z, a.y.x * b.x.w + a.y.y * b.y.w ), float4( a.z.x * b.x.x + a.z.y * b.y.x, a.z.x * b.x.y + a.z.y * b.y.y, a.z.x * b.x.z + a.z.y * b.y.z, a.z.x * b.x.w + a.z.y * b.y.w ), float4( a.w.x * b.x.x + a.w.y * b.y.x, a.w.x * b.x.y + a.w.y * b.y.y, a.w.x * b.x.z + a.w.y * b.y.z, a.w.x * b.x.w + a.w.y * b.y.w ) ); }
inline float4x4 mul( float4x3 a, float3x4 b ) { return float4x4( float4( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y, a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z, a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w ), float4( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y, a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z, a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w ), float4( a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x, a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y, a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z, a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w ), float4( a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x, a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y, a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z, a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w ) ); }
inline float2x2 mul( float2x4 a, float4x2 b ) { return float2x2( float2( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y ), float2( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y ) ); }
inline float3x3 mul( float3x4 a, float4x3 b ) { return float3x3( float3( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y, a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z ), float3( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y, a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z ), float3( a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x, a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y, a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z ) ); }
inline float4x4 mul( float4x4 a, float4x4 b ) { return float4x4( float4( a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.w.x, a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.w.y, a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.w.z, a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.w.w ), float4( a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.w.x, a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.w.y, a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.w.z, a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.w.w ), float4( a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.w.x, a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.w.y, a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.w.z, a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.w.w ), float4( a.w.x * b.x.x + a.w.y * b.y.x + a.w.z * b.z.x + a.w.w * b.w.x, a.w.x * b.x.y + a.w.y * b.y.y + a.w.z * b.z.y + a.w.w * b.w.y, a.w.x * b.x.z + a.w.y * b.y.z + a.w.z * b.z.z + a.w.w * b.w.z, a.w.x * b.x.w + a.w.y * b.y.w + a.w.z * b.z.w + a.w.w * b.w.w ) ); }

} /* namespace vecmath */

#endif /* vecmath_hpp */

/*
----------------------
	IMPLEMENTATION
----------------------
*/

#ifndef vecmath_impl
#define vecmath_impl

namespace vecmath {

inline swizzle2& swizzle2::operator=( float2 const& v ) { x = v.x; y = v.y; return *this; }
inline swizzle3& swizzle3::operator=( float3 const& v ) { x = v.x; y = v.y; z = v.z; return *this; }
inline swizzle4& swizzle4::operator=( float4 const& v ) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
inline swizzle2& swizzle2::operator=( swizzle2 const& v ) { float2 t = v; x = t.x; y = t.y; return *this; }
inline swizzle3& swizzle3::operator=( swizzle3 const& v ) { float3 t = v; x = t.x; y = t.y; z = t.z; return *this; }
inline swizzle4& swizzle4::operator=( swizzle4 const& v ) { float4 t = v; x = t.x; y = t.y; z = t.z; w = t.w; return *this; }


} /* namespace vecmath */

#endif /* vecmath_impl */


#ifdef VECMATH_IMPLEMENTATION
#undef VECMATH_IMPLEMENTATION

// TODO: customizable math funcs
#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#include <math.h>
#pragma warning( pop )


float vecmath::internal::acosf( float x ) { return (float)::acos( (double) x ); }
float vecmath::internal::asinf( float x ) { return (float)::asin( (double) x ); }
float vecmath::internal::atanf( float x ) { return (float)::atan( (double) x ); }
float vecmath::internal::atan2f( float x, float y ) { return (float)::atan2( (double) x, (double) y ); }
float vecmath::internal::ceilf( float x ) { return (float)::ceil( (double) x ); }
float vecmath::internal::cosf( float x ) { return (float)::cos( (double) x ); }
float vecmath::internal::coshf( float x ) { return (float)::cosh( (double) x ); }
float vecmath::internal::expf( float x ) { return (float)::exp( (double) x ); }
float vecmath::internal::fabsf( float x ) { return (float)::fabs( (double) x ); }
float vecmath::internal::floorf( float x ) { return (float)::floor( (double) x ); }
float vecmath::internal::fmodf( float x, float y ) { return (float)::fmod( (double) x, (double) y ); }
float vecmath::internal::logf( float x ) { return (float)::log( (double) x ); }
float vecmath::internal::log10f( float x ) { return (float)::log10( (double) x ); }
float vecmath::internal::modff( float x, float* y ) { double yy; float r = (float)::modf( (double) x, &yy ); *y = (float) yy; return r; }
float vecmath::internal::powf( float x, float y ) { return (float)::pow( (double) x, (double) y ); }
float vecmath::internal::sqrtf( float x ) { return (float)::sqrt( (double) x ); }
float vecmath::internal::sinf( float x ) { return (float)::sin( (double) x ); }
float vecmath::internal::sinhf( float x ) { return (float)::sinh( (double) x ); }
float vecmath::internal::tanf( float x ) { return (float)::tan( (double) x ); }
float vecmath::internal::tanhf( float x ) { return (float)::tanh( (double) x ); }

#if !defined( _MSC_VER ) || _MSC_VER >= 1800

	float vecmath::internal::log2f( float x ) { return (float)::log2( (double) x ); }
	float vecmath::internal::roundf( float x ) { return (float)::round( (double) x ); }
	float vecmath::internal::truncf( float x ) { return (float)::trunc( (double) x ); }

#else

    float vecmath::internal::log2f( float x ) 
        { 
        return (float)( ::log10( (double) x ) / ::log10( 2.0 ) ); 
        }
	
	float vecmath::internal::roundf( float x ) 
		{ 
        double i, r;
        double fraction = modf( (double) x, &i );
        modf( 2.0 * fraction, &r );
        return (float)( i + r );
        }

    float vecmath::internal::truncf( float x ) 
        { 
        return (float)( x > 0.0f ? ( ::floor( (double) x ) ) : ( ::ceil( (double) x ) ) );
        }
#endif


#endif /* VECMATH_IMPLEMENTATION */
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
