/*
 * Vector.cpp
 * Copyright (c) 2012, Hanoilabs
 */

#include "Vector.h"


void Vector::vec2_add( vec2 *dst, vec2 *v0, vec2 *v1 )
{
	dst->x = v0->x + v1->x;
	dst->y = v0->y + v1->y;
}


void Vector::vec2_diff( vec2 *dst, vec2 *v0, vec2 *v1 )
{
	dst->x = v0->x - v1->x;
	dst->y = v0->y - v1->y;
}


void Vector::vec3_add( vec3 *dst, vec3 *v0, vec3 *v1 )
{
	dst->x = v0->x + v1->x;
	dst->y = v0->y + v1->y;
	dst->z = v0->z + v1->z;
}


void Vector::vec3_diff( vec3 *dst, vec3 *v0, vec3 *v1 )
{
	dst->x = v0->x - v1->x;
	dst->y = v0->y - v1->y;
	dst->z = v0->z - v1->z;
}


void Vector::vec3_mul( vec3 *dst, vec3 *v0, vec3 *v1 )
{
	dst->x = v0->x * v1->x;
	dst->y = v0->y * v1->y;
	dst->z = v0->z * v1->z;
}


float Vector::vec3_dot( vec3 *v )
{
	return ( v->x * v->x ) +
		   ( v->y * v->y ) +
		   ( v->z * v->z );
}


float Vector::vec3_dot_vec3( vec3 *v0, vec3 *v1 )
{
	return ( v0->x * v1->x ) +
		   ( v0->y * v1->y ) +
		   ( v0->z * v1->z );
}


float Vector::vec3_length( vec3 *v )
{ return sqrtf( vec3_dot( v ) ); }


float Vector::vec3_normalize( vec3 *dst, vec3 *v )
{
	float l = vec3_length( v );

	if( l )
	{
		float m = 1.0f / l;

		dst->x = v->x * m;
		dst->y = v->y * m;
		dst->z = v->z * m;
	}

	return l;
}


void Vector::vec3_cross( vec3 *dst, vec3 *v0, vec3 *v1 )
{
	dst->x = ( v0->y * v1->z ) - ( v1->y * v0->z );
	dst->y = ( v0->z * v1->x ) - ( v1->z * v0->x );
	dst->z = ( v0->x * v1->y ) - ( v1->x * v0->y );
}


float Vector::vec3_dist( vec3 *v0, vec3 *v1 )
{
	vec3 v;

	vec3_diff( &v, v0, v1 );

	return vec3_length( &v );
}


void Vector::vec3_mid( vec3 *dst, vec3 *v0, vec3 *v1 )
{
	dst->x = ( v0->x + v1->x ) * 0.5f;
	dst->y = ( v0->y + v1->y ) * 0.5f;
	dst->z = ( v0->z + v1->z ) * 0.5f;
}


void Vector::vec3_invert( vec3 *dst, vec3 *v )
{
	dst->x = -v->x;
	dst->y = -v->y;
	dst->z = -v->z;
}


void Vector::vec3_lerp( vec3 *dst, vec3 *v0, vec3 *v1, float t )
{
	if( t == 1.0f )
	{
		dst->x = v1->x;
		dst->y = v1->y;
		dst->z = v1->z;

		return;
	}
	else if( t == 0.0f )
	{
		dst->x = v0->x;
		dst->y = v0->y;
		dst->z = v0->z;

		return;
	}

	dst->x = v0->x + t * ( v1->x - v0->x );
	dst->y = v0->y + t * ( v1->y - v0->y );
	dst->z = v0->z + t * ( v1->z - v0->z );
}


void Vector::vec3_lerp2( vec3 *dst, vec3 *v0, vec3 *v1, float t )
{
	dst->x = v0->x * t + v1->x * ( 1.0f - t );
	dst->y = v0->y * t + v1->y * ( 1.0f - t );
	dst->z = v0->z * t + v1->z * ( 1.0f - t );
}


void Vector::vec3_rotate_vec4( vec3 *dst, vec3 *v0, vec4 *v1 )
{
	vec4 i, t, f;

	vec4_conjugate( &i, v1 );

	vec4_normalize( &i, &i );

	vec4_multiply_vec3( &t, v1, v0 );

	vec4_multiply_vec4( &f, &t, &i );

	memcpy( dst, &f, sizeof( vec3 ) );
}


void Vector::vec3_to_recast( vec3 *v )
{
	vec3 tmp = {  v->x,
				  v->z,
			     -v->y };

	memcpy( v, &tmp, sizeof( vec3 ) );
}


void Vector::recast_to_vec3( vec3 *v )
{
	vec3 tmp = {  v->x,
			     -v->z,
			      v->y };

	memcpy( v, &tmp, sizeof( vec3 ) );
}


void Vector::vec4_add( vec4 *dst, vec4 *v0, vec4 *v1 )
{
	dst->x = v0->x + v1->x;
	dst->y = v0->y + v1->y;
	dst->z = v0->z + v1->z;
	dst->w = v0->w;// + v1->w;
}


void Vector::vec4_diff( vec4 *dst, vec4 *v0, vec4 *v1 )
{
	dst->x = v0->x - v1->x;
	dst->y = v0->y - v1->y;
	dst->z = v0->z - v1->z;
	dst->w = v0->w;// - v1->w;
}


void Vector::vec4_build_w( vec4 * v )
{
	float l = 1.0f - ( v->x * v->x ) -
					 ( v->y * v->y ) -
					 ( v->z * v->z );

	v->w = ( l < 0.0f ) ? 0.0f : -sqrtf( l );
}


float Vector::vec4_dot( vec4 *v )
{
	return ( v->x * v->x ) +
		   ( v->y * v->y ) +
		   ( v->z * v->z ) +
		   ( v->w * v->w );
}


float Vector::vec4_dot_vec4( vec4 *v0, vec4 *v1 )
{
	return ( ( v0->x * v1->x ) +
			 ( v0->y * v1->y ) +
			 ( v0->z * v1->z ) +
			 ( v0->w * v1->w ) );
}


float Vector::vec4_length( vec4 *v )
{
	return sqrtf( vec4_dot( v ) );
}


float Vector::vec4_normalize( vec4 *dst, vec4 *v )
{
	float l = vec4_length( v ),
		  m = l ? 1.0f / l: 0.0f;

	dst->x = v->x * m;
	dst->y = v->y * m;
	dst->z = v->z * m;
	dst->w = v->w * m;

	return l;
}


void Vector::vec4_multiply_vec3( vec4 *dst, vec4 *v0, vec3 *v1 )
{
	vec4 v;

	v.x =  ( v0->w * v1->x ) + ( v0->y * v1->z ) - ( v0->z * v1->y );
	v.y =  ( v0->w * v1->y ) + ( v0->z * v1->x ) - ( v0->x * v1->z );
	v.z =  ( v0->w * v1->z ) + ( v0->x * v1->y ) - ( v0->y * v1->x );
	v.w = -( v0->x * v1->x ) - ( v0->y * v1->y ) - ( v0->z * v1->z );

	memcpy( dst, &v, sizeof( vec4 ) );
}



void Vector::vec4_multiply_vec4( vec4 *dst, vec4 *v0, vec4 *v1 )
{
	vec4 v;

	v.x = ( v0->x * v1->w ) + ( v0->w * v1->x ) + ( v0->y * v1->z ) - ( v0->z * v1->y );
	v.y = ( v0->y * v1->w ) + ( v0->w * v1->y ) + ( v0->z * v1->x ) - ( v0->x * v1->z );
	v.z = ( v0->z * v1->w ) + ( v0->w * v1->z ) + ( v0->x * v1->y ) - ( v0->y * v1->x );
	v.w = ( v0->w * v1->w ) - ( v0->x * v1->x ) - ( v0->y * v1->y ) - ( v0->z * v1->z );

	memcpy( dst, &v, sizeof( vec4 ) );
}


void Vector::vec4_conjugate( vec4 *dst, vec4 *v )
{
	dst->x = -v->x;
	dst->y = -v->y;
	dst->z = -v->z;
	dst->w =  v->w;
}


void Vector::vec4_invert( vec4 *dst, vec4 *v )
{
	dst->x = -v->x;
	dst->y = -v->y;
	dst->z = -v->z;
	dst->w = -v->w;
}


void Vector::vec4_lerp( vec4 *dst, vec4 *v0, vec4 *v1, float t )
{
	float dot = vec4_dot_vec4( v0, v1 ),
		  k0,
		  k1;

	vec4 tmp = { v1->x,
				 v1->y,
				 v1->z,
				 v1->w };

	if( t == 1.0f )
	{
		dst->x = v1->x;
		dst->y = v1->y;
		dst->z = v1->z;
		dst->w = v1->w;

		return;
	}
	else if( t == 0.0f )
	{
		dst->x = v0->x;
		dst->y = v0->y;
		dst->z = v0->z;
		dst->w = v0->w;

		return;
	}


	if( dot < 0.0f )
	{
		tmp.x = -tmp.x;
		tmp.y = -tmp.y;
		tmp.z = -tmp.z;
		tmp.w = -tmp.w;

		dot = -dot;
	}


	if( dot > 0.999999f )
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float s  = sqrtf( 1.0f - ( dot * dot ) ),
			  o  = atan2f( s, dot ),
			  o1 = 1.0f / s;

		k0 = sinf( ( 1.0f - t ) * o ) * o1;
		k1 = sinf( t * o ) * o1;
	}

	dst->x = ( k0 * v0->x ) + ( k1 * tmp.x );
	dst->y = ( k0 * v0->y ) + ( k1 * tmp.y );
	dst->z = ( k0 * v0->z ) + ( k1 * tmp.z );
	dst->w = ( k0 * v0->w ) + ( k1 * tmp.w );
}


void Vector::vec4_slerp( vec4 *dst, vec4 *v0, vec4 *v1, float t )
{
	float c = vec4_dot_vec4( v0, v1 ),
		  k0,
		  k1;

	vec4 tmp = { v1->x,
				 v1->y,
				 v1->z,
				 v1->w };

	if( t == 1.0f )
	{
		dst->x = v1->x;
		dst->y = v1->y;
		dst->z = v1->z;
		dst->w = v1->w;

		return;
	}
	else if( t == 0.0f )
	{
		dst->x = v0->x;
		dst->y = v0->y;
		dst->z = v0->z;
		dst->w = v0->w;

		return;
	}


	if( c < 0.0f )
	{
		tmp.x = -tmp.x;
		tmp.y = -tmp.y;
		tmp.z = -tmp.z;
		tmp.w = -tmp.w;

		c = -c;
	}


	if( c > 0.999999f )
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float s  = sqrtf( 1.0f - ( c * c ) ),
			  o  = atan2f( s, c ),
			  o1 = 1.0f / s;

		k0 = sinf( ( 1.0f - t ) * o ) * o1;
		k1 = sinf( t * o ) * o1;
	}

	dst->x = ( k0 * v0->x ) + ( k1 * tmp.x );
	dst->y = ( k0 * v0->y ) + ( k1 * tmp.y );
	dst->z = ( k0 * v0->z ) + ( k1 * tmp.z );
	dst->w = ( k0 * v0->w ) + ( k1 * tmp.w );
}
