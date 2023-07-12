#pragma once
#pragma warning ( disable : 4244 )

#include "util.h"
#include <cmath>
#include <math.h>

#define RAD_PI 57.295779513082
#define PI 3.14159265358979323846
#define TAU PI * 2.
#define DEG_TO_RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD_TO_DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )

typedef float matrix_3x4[ 3 ][ 4 ];

class view_matrix {
public:
	inline const matrix_3x4& as_3x4( ) const {
		return *( ( const matrix_3x4* )this );
	}

public:
	float m_mat[ 4 ][ 4 ];
};

namespace math {
	inline double __declspec ( naked ) __fastcall fast_sqrt( double n ) {
		_asm fld qword ptr[ esp + 4 ]
			_asm fsqrt
		_asm ret 8
	}
}

class vector {
public:
	vector( float x = 0.0f, float y = 0.0f, float z = 0.0f ) {
		m_x = x; m_y = y; m_z = z;
	}

	vector& operator=( const vector& v ) {
		this->m_x = v.m_x; this->m_y = v.m_y; this->m_z = v.m_z;
		return *this;
	}

	vector& operator=( float v ) {
		this->m_x = v; this->m_y = v; this->m_z = v;
		return *this;
	}

	float& operator[ ]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[ ]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	vector& operator+=( const vector& v ) {
		this->m_x += v.m_x; this->m_y += v.m_y; this->m_z += v.m_z;
		return *this;
	}

	vector& operator-=( const vector& v ) {
		this->m_x -= v.m_x; this->m_y -= v.m_y; this->m_z -= v.m_z;
		return *this;
	}

	vector& operator*=( const vector& v ) {
		this->m_x *= v.m_x; this->m_y *= v.m_y; this->m_z *= v.m_z;
		return *this;
	}

	vector& operator/=( const vector& v ) {
		this->m_x /= v.m_x;	this->m_y /= v.m_y; this->m_z /= v.m_z;
		return *this;
	}

	vector& operator+=( float v ) {
		this->m_x += v; this->m_y += v; this->m_z += v;
		return *this;
	}

	vector& operator-=( float v ) {
		this->m_x -= v; this->m_y -= v; this->m_z -= v;
		return *this;
	}

	vector& operator*=( float v ) {
		this->m_x *= v; this->m_y *= v; this->m_z *= v;
		return *this;
	}

	vector& operator/=( float v ) {
		this->m_x /= v; this->m_y /= v; this->m_z /= v;
		return *this;
	}

	vector operator+( const vector& v ) const {
		return vector( this->m_x + v.m_x, this->m_y + v.m_y, this->m_z + v.m_z );
	}

	vector operator-( const vector& v ) const {
		return vector( this->m_x - v.m_x, this->m_y - v.m_y, this->m_z - v.m_z );
	}

	vector operator*( const vector& v ) const {
		return vector( this->m_x * v.m_x, this->m_y * v.m_y, this->m_z * v.m_z );
	}

	vector operator/( const vector& v ) const {
		return vector( this->m_x / v.m_x, this->m_y / v.m_y, this->m_z / v.m_z );
	}

	vector operator+( float v ) const {
		return vector( this->m_x + v, this->m_y + v, this->m_z + v );
	}

	vector operator-( float v ) const {
		return vector( this->m_x - v, this->m_y - v, this->m_z - v );
	}

	vector operator*( float v ) const {
		return vector( this->m_x * v, this->m_y * v, this->m_z * v );
	}

	vector operator/( float v ) const {
		return vector( this->m_x / v, this->m_y / v, this->m_z / v );
	}

	void set( float x = 0.0f, float y = 0.0f, float z = 0.0f ) {
		this->m_x = x; this->m_y = y; this->m_z = z;
	}

	float length( void ) const {
		return math::fast_sqrt( this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z );
	}

	float length_sqr( void ) const {
		return ( this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z );
	}

	float length_2d( void ) const {
		return math::fast_sqrt( this->m_x * this->m_x + this->m_y * this->m_y );
	}

	float length_2d_sqr( void ) const {
		return ( this->m_x * this->m_x + this->m_y * this->m_y );
	}

	float dist_to( const vector& v ) const {
		return ( *this - v ).length( );
	}

	float dist_to_sqr( const vector& v ) const {
		return ( *this - v ).length_sqr( );
	}

	float dot_product( const vector& v ) const {
		return ( this->m_x * v.m_x + this->m_y * v.m_y + this->m_z * v.m_z );
	}

	vector cross_product( const vector& v ) const {
		return vector( this->m_y * v.m_z - this->m_z * v.m_y, this->m_z * v.m_x - this->m_x * v.m_z, this->m_x * v.m_y - this->m_y * v.m_x );
	}

	bool is_zero( float tolerance = 0.01f ) const {
		return ( this->m_x > -tolerance && this->m_x < tolerance && this->m_y > -tolerance && this->m_y < tolerance && this->m_z > -tolerance && this->m_z < tolerance );
	}

	vector clamped()
	{
		float pitch = m_x;
		float jaw = m_y;

		while (jaw > 180.0f)
			jaw -= 360.0f;

		while (jaw < -180.0f)
			jaw += 360.0f;

		return vector(std::max(-89.f, std::min(89.f, pitch)), jaw, 0.f);
	}

	float normalize_in_place()
	{
		const float flLength = this->length();
		const float flRadius = 1.0f / (flLength + std::numeric_limits<float>::epsilon());

		this->m_x *= flRadius;
		this->m_y *= flRadius;
		this->m_z *= flRadius;

		return flLength;
	}

	float m_x, m_y, m_z;
};

class vector_2d {
public:
	vector_2d( float x = 0.0f, float y = 0.0f) {
		m_x = x; m_y = y;
	}

	vector_2d& operator=( const vector_2d& v ) {
		this->m_x = v.m_x; this->m_y = v.m_y;
		return *this;
	}

	vector_2d& operator=( float v ) {
		this->m_x = v; this->m_y = v;
		return *this;
	}

	float& operator[ ]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[ ]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	vector_2d& operator+=( const vector_2d& v ) {
		this->m_x += v.m_x; this->m_y += v.m_y;
		return *this;
	}

	vector_2d& operator-=( const vector_2d& v ) {
		this->m_x -= v.m_x; this->m_y -= v.m_y;
		return *this;
	}

	vector_2d& operator*=( const vector_2d& v ) {
		this->m_x *= v.m_x; this->m_y *= v.m_y;
		return *this;
	}

	vector_2d& operator/=( const vector_2d& v ) {
		this->m_x /= v.m_x;	this->m_y /= v.m_y;
		return *this;
	}

	vector_2d& operator+=( float v ) {
		this->m_x += v; this->m_y += v;
		return *this;
	}

	vector_2d& operator-=( float v ) {
		this->m_x -= v; this->m_y -= v;
		return *this;
	}

	vector_2d& operator*=( float v ) {
		this->m_x *= v; this->m_y *= v;
		return *this;
	}

	vector_2d& operator/=( float v ) {
		this->m_x /= v; this->m_y /= v;
		return *this;
	}

	vector_2d operator+( const vector_2d& v ) const {
		return vector_2d( this->m_x + v.m_x, this->m_y + v.m_y );
	}

	vector_2d operator-( const vector_2d& v ) const {
		return vector_2d( this->m_x - v.m_x, this->m_y - v.m_y );
	}

	vector_2d operator*( const vector_2d& v ) const {
		return vector_2d( this->m_x * v.m_x, this->m_y * v.m_y );
	}

	vector_2d operator/( const vector_2d& v ) const {
		return vector_2d( this->m_x / v.m_x, this->m_y / v.m_y );
	}

	vector_2d operator+( float v ) const {
		return vector_2d( this->m_x + v, this->m_y + v );
	}

	vector_2d operator-( float v ) const {
		return vector_2d( this->m_x - v, this->m_y - v );
	}

	vector_2d operator*( float v ) const {
		return vector_2d( this->m_x * v, this->m_y * v );
	}

	vector_2d operator/( float v ) const {
		return vector_2d( this->m_x / v, this->m_y / v );
	}

	void set( float x = 0.0f, float y = 0.0f ) {
		this->m_x = x; this->m_y = y;
	}

	float length( void ) const {
		return math::fast_sqrt( this->m_x * this->m_x + this->m_y * this->m_y );
	}

	float length_sqr( void ) const {
		return ( this->m_x * this->m_x + this->m_y * this->m_y );
	}

	float dist_to( const vector_2d& v ) const {
		return ( *this - v ).length( );
	}

	float dist_to_sqr( const vector_2d& v ) const {
		return ( *this - v ).length_sqr( );
	}

	float dot_product( const vector_2d& v ) const {
		return ( this->m_x * v.m_x + this->m_y * v.m_y );
	}

	bool is_zero( float tolerance = 0.01f ) const {
		return ( this->m_x > -tolerance && this->m_x < tolerance && this->m_y > -tolerance && this->m_y < tolerance );
	}

	float m_x, m_y;
};

struct rect_t {
	int m_x, m_y, m_w, m_h;
};

namespace math {
	inline void sine_cosine( float radians, float* sine, float* cosine ) {
		_asm {
			fld DWORD PTR[ radians ]
			fsincos

			mov edx, DWORD PTR[ cosine ]
			mov eax, DWORD PTR[ sine ]

			fstp DWORD PTR[ edx ]
			fstp DWORD PTR[ eax ]
		}
	}

	inline void sine_cosine( const float& radians, float& sine, float& cosine ) {
		sine = sinf( radians );
		cosine = cosf( radians );
	}

	inline float normalize_rad( float a ) noexcept {
		return std::isfinite( a ) ? std::remainder( a, PI * 2 ) : 0.0f;
	}

	inline float normalize_angle( float angle ) {
		if ( !std::isfinite( angle ) )
			return 0.0f;

		while ( angle > 180.0f )
			angle -= 360.0f;

		while ( angle < -180.0f )
			angle += 360.0f;

		return angle;
	}

	inline void clamp_angle( vector& a ) {
		a.m_x = std::max( -89.f, std::min( 89.f, normalize_angle( a.m_x ) ) );
		a.m_y = normalize_angle( a.m_y );
		a.m_z = 0.f;
	}

	inline float angle_diff_rad( float a1, float a2 ) noexcept {
		double delta = normalize_rad( a1 - a2 );

		if ( a1 > a2 ) {
			if ( delta >= PI )
				delta -= PI * 2;
		}

		else if ( delta <= -PI )
			delta += PI * 2;

		return static_cast< float >( delta );
	}

	inline vector vector_transform( const vector& input, const matrix_3x4& matrix ) {
		auto out = vector( );

		for ( auto i = 0; i < 3; i++ )
			out[ i ] = input.dot_product( ( vector& )matrix[ i ] ) + matrix[ i ][ 3 ];

		return out;
	}

	inline void angle_vectors( const vector& angles, vector* forward ) {
		float pitch_sine, pitch_cosine, yaw_sine, yaw_cosine;

		math::sine_cosine( DEG_TO_RAD( angles.m_x ), &pitch_sine, &pitch_cosine );
		math::sine_cosine( DEG_TO_RAD( angles.m_y ), &yaw_sine, &yaw_cosine );

		if ( forward ) {
			forward->m_x = pitch_cosine * yaw_cosine;
			forward->m_y = pitch_cosine * yaw_sine;
			forward->m_z = -pitch_sine;
		}
	}

	inline void angle_vectors( const vector& angles, vector* forward, vector* right, vector* up ) {
		float pitch_sine, pitch_cosine, yaw_sine, yaw_cosine, roll_sine, roll_cosine;

		math::sine_cosine( DEG_TO_RAD( angles.m_x ), &pitch_sine, &pitch_cosine );
		math::sine_cosine( DEG_TO_RAD( angles.m_y ), &yaw_sine, &yaw_cosine );
		math::sine_cosine( DEG_TO_RAD( angles.m_z ), &roll_sine, &roll_cosine );

		if ( forward ) {
			forward->m_x = pitch_cosine * yaw_cosine;
			forward->m_y = pitch_cosine * yaw_sine;
			forward->m_z = -pitch_sine;
		}

		if ( right ) {
			right->m_x = ( -1.0f * roll_sine * pitch_sine * yaw_cosine + -1.0f * roll_cosine * -yaw_sine );
			right->m_y = ( -1.0f * roll_sine * pitch_sine * yaw_sine + -1.0f * roll_cosine * yaw_cosine );
			right->m_z = -1.0f * roll_sine * pitch_cosine;
		}

		if ( up ) {
			up->m_x = ( roll_cosine * pitch_sine * yaw_cosine + -roll_sine * -yaw_sine );
			up->m_y = ( roll_cosine * pitch_sine * yaw_sine + -roll_sine * yaw_cosine );
			up->m_z = roll_cosine * pitch_cosine;
		}
	}

	inline void vector_angles( const vector& forward, vector& angles ) {
		auto tmp = 0.0f, yaw = 0.0f, pitch = 0.0f;

		if ( !forward.m_y && !forward.m_x ) {
			yaw = 0.0f;

			if ( forward.m_z > 0.0f )
				pitch = 270.0f;

			else
				pitch = 90.0f;
		}

		else {
			yaw = RAD_TO_DEG( atan2f( forward.m_y, forward.m_x ) );

			if ( yaw < 0.0f )
				yaw += 360.0f;

			tmp = forward.length_2d( );
			pitch = RAD_TO_DEG( atan2f( -forward.m_z, tmp ) );

			if ( pitch < 0.0f )
				pitch += 360.0f;
		}

		angles.m_x = pitch;
		angles.m_y = yaw;
		angles.m_z = 0.0f;
	}

	inline vector direction_to_angles( const vector& direction ) {
		auto magnitude = [ & ]( const vector& v ) -> float {
			return math::fast_sqrt( v.dot_product( v ) );
		};

		float yaw, pitch;

		if ( !direction.m_y && !direction.m_x ) {
			yaw = 0.0f;

			if ( direction.m_z > 0.0f )
				pitch = 270.0f;

			else pitch = 90.0f;
		}

		else {
			yaw = RAD_TO_DEG( atan2f( direction.m_y, direction.m_x ) );
			pitch = RAD_TO_DEG( atan2f( -direction.m_z, magnitude( vector( direction ) ) ) );

			if ( yaw < 0.0f )
				yaw += 360.0f;

			if ( pitch < 0.0f )
				pitch += 360.0f;
		}

		return { pitch, yaw, 0.0f };
	}

	inline vector calculate_angle( const vector& source, const vector& destination ) {
		auto angle_out = vector( );

		auto delta = ( source - destination );
		auto hypot = math::fast_sqrt( ( delta.m_x * delta.m_x ) + ( delta.m_y * delta.m_y ) );

		angle_out.m_x = ( atanf( delta.m_z / hypot ) * RAD_PI );
		angle_out.m_y = ( atanf( delta.m_y / delta.m_x ) * RAD_PI );

		if ( delta.m_x >= 0.0f )
			angle_out.m_y += 180.0f;

		return angle_out;
	}

	inline float calculate_fov( const vector& source, const vector& destination ) {
		vector source_forward = vector( );
		math::angle_vectors( source, &source_forward );

		vector destination_forward = vector( );
		math::angle_vectors( destination, &destination_forward );

		auto result = RAD_TO_DEG( acosf( destination_forward.dot_product( source_forward ) / destination_forward.length_sqr( ) ) );

		if ( !isfinite( result ) || isinf( result ) || isnan( result ) )
			result = 0.0f;

		return result;
	}

	inline float get_fraction( const float val, const float max, const float min ) {
		return std::clamp( ( val - min ) / ( max - min ), 0.f, 1.f );
	}

	inline float remap_val_clamped( float val, float a, float b, float c, float d ) {
		if ( a == b )
			return val >= b ? d : c;

		float val_ = ( val - a ) / ( b - a );
		val_ = std::clamp( val_, 0.0f, 1.0f );

		return c + ( d - c ) * val_;
	}

	inline void angle_matrix( const vector& angles, matrix_3x4& matrix ) {
		float sr, sp, sy, cr, cp, cy;

		math::sine_cosine( DEG_TO_RAD( angles.m_y ), &sy, &cy );
		math::sine_cosine( DEG_TO_RAD( angles.m_x ), &sp, &cp );
		math::sine_cosine( DEG_TO_RAD( angles.m_z ), &sr, &cr );

		matrix[ 0 ][ 0 ] = cp * cy;
		matrix[ 1 ][ 0 ] = cp * sy;
		matrix[ 2 ][ 0 ] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;

		matrix[ 0 ][ 1 ] = sp * srcy - crsy;
		matrix[ 1 ][ 1 ] = sp * srsy + crcy;
		matrix[ 2 ][ 1 ] = sr * cp;

		matrix[ 0 ][ 2 ] = ( sp * crcy + srsy );
		matrix[ 1 ][ 2 ] = ( sp * crsy - srcy );
		matrix[ 2 ][ 2 ] = cr * cp;

		matrix[ 0 ][ 3 ] = 0.0f;
		matrix[ 1 ][ 3 ] = 0.0f;
		matrix[ 2 ][ 3 ] = 0.0f;
	}

	inline void matrix_set_column( const vector& in, int column, matrix_3x4& out ) {
		out[ 0 ][ column ] = in.m_x;
		out[ 1 ][ column ] = in.m_y;
		out[ 2 ][ column ] = in.m_z;
	}

	inline void matrix_copy( const matrix_3x4& src, matrix_3x4& dst ) {
		if ( &src != &dst )
		{
			memcpy( dst, src, 12 * sizeof( float ) );
		}
	}

	inline void concat_transforms( const matrix_3x4& in1, const matrix_3x4& in2, matrix_3x4& out )
	{
		if ( &in1 == &out ) {
			matrix_3x4 in1b;
			matrix_copy( in1, in1b );
			concat_transforms( in1b, in2, out );
			return;
		}

		if ( &in2 == &out ) {
			matrix_3x4 in2b;
			matrix_copy( in2, in2b );
			concat_transforms( in1, in2b, out );
			return;
		}

		out[ 0 ][ 0 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 0 ] +
			in1[ 0 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 0 ][ 1 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 1 ] +
			in1[ 0 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 0 ][ 2 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 2 ] +
			in1[ 0 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 0 ][ 3 ] = in1[ 0 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 0 ][ 1 ] * in2[ 1 ][ 3 ] +
			in1[ 0 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 0 ][ 3 ];
		out[ 1 ][ 0 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 0 ] +
			in1[ 1 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 1 ][ 1 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 1 ] +
			in1[ 1 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 1 ][ 2 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 2 ] +
			in1[ 1 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 1 ][ 3 ] = in1[ 1 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 1 ][ 1 ] * in2[ 1 ][ 3 ] +
			in1[ 1 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 1 ][ 3 ];
		out[ 2 ][ 0 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 0 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 0 ] +
			in1[ 2 ][ 2 ] * in2[ 2 ][ 0 ];
		out[ 2 ][ 1 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 1 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 1 ] +
			in1[ 2 ][ 2 ] * in2[ 2 ][ 1 ];
		out[ 2 ][ 2 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 2 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 2 ] +
			in1[ 2 ][ 2 ] * in2[ 2 ][ 2 ];
		out[ 2 ][ 3 ] = in1[ 2 ][ 0 ] * in2[ 0 ][ 3 ] + in1[ 2 ][ 1 ] * in2[ 1 ][ 3 ] +
			in1[ 2 ][ 2 ] * in2[ 2 ][ 3 ] + in1[ 2 ][ 3 ];
	}

	inline void matrix_angles( const matrix_3x4& matrix, vector& angles ) {
		//Vec3 forward, left, up;

		// extract the basis vectors from the matrix. since we only need the z
		// component of the up vector, we don't get x and y.
		const vector forward = { matrix[ 0 ][ 0 ], matrix[ 1 ][ 0 ], matrix[ 2 ][ 0 ] };
		const vector left = { matrix[ 0 ][ 1 ], matrix[ 1 ][ 1 ], matrix[ 2 ][ 1 ] };
		const vector up = { 0.f, 0.f, matrix[ 2 ][ 2 ] };

		float len = forward.length_2d( );

		// enough here to get angles?
		if ( len > 0.001f ) {
			angles.m_x = RAD_TO_DEG( std::atan2( -forward.m_z, len ) );
			angles.m_y = RAD_TO_DEG( std::atan2( forward.m_y, forward.m_x ) );
			angles.m_z = RAD_TO_DEG( std::atan2( left.m_z, up.m_z ) );
		}

		else {
			angles.m_x = RAD_TO_DEG( std::atan2( -forward.m_z, len ) );
			angles.m_y = RAD_TO_DEG( std::atan2( -left.m_x, left.m_y ) );
			angles.m_z = 0.f;
		}
	}

	inline void get_matrix_origin( const matrix_3x4& source, vector& target ) {
		target.m_x = source[ 0 ][ 3 ];
		target.m_y = source[ 1 ][ 3 ];
		target.m_z = source[ 2 ][ 3 ];
	}

	inline vector get_rotated_position( vector start, const float rotation, const float distance ) {
		const auto rad = DEG_TO_RAD( rotation );
		start.m_x += cosf( rad ) * distance;
		start.m_y += sinf( rad ) * distance;
		return start;
	}
}