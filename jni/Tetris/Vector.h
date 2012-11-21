/*
 * Vector.h
 * Copyright (c) 2012, Hanoilabs
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "Engine.h"
#include "Types.h"

class Vector {
public:

	static void vec2_add( vec2 *dst, vec2 *v0, vec2 *v1 );

	static void vec2_diff( vec2 *dst, vec2 *v0, vec2 *v1 );


	static void vec3_add( vec3 *dst, vec3 *v0, vec3 *v1 );

	static void vec3_diff( vec3 *dst, vec3 *v0, vec3 *v1 );

	static void vec3_mul( vec3 *dst, vec3 *v0, vec3 *v1 );

	static float vec3_dot( vec3 *v );

	static float vec3_dot_vec3( vec3 *v0, vec3 *v1 );

	static float vec3_length( vec3 *v );

	static float vec3_normalize( vec3 *dst, vec3 *v );

	static void vec3_cross( vec3 *dst, vec3 *v0, vec3 *v1 );

	static float vec3_dist( vec3 *v0, vec3 *v1 );

	static void vec3_mid( vec3 *dst, vec3 *v0, vec3 *v1 );

	static void vec3_invert( vec3 *dst, vec3 *v );

	static void vec3_lerp( vec3 *dst, vec3 *v0, vec3 *v1, float t );

	static void vec3_lerp2( vec3 *dst, vec3 *v0, vec3 *v1, float t );

	static void vec3_rotate_vec4( vec3 *dst, vec3 *v0, vec4 *v1 );


	static void vec3_to_recast( vec3 *v );

	static void recast_to_vec3( vec3 *v );


	static void vec4_add( vec4 *dst, vec4 *v0, vec4 *v1 );

	static void vec4_diff( vec4 *dst, vec4 *v0, vec4 *v1 );

	static void vec4_build_w( vec4 *v );

	static float vec4_dot( vec4 *v );

	static float vec4_dot_vec4( vec4 *v0, vec4 *v1 );

	static float vec4_length( vec4 *v );

	static float vec4_normalize( vec4 *dst, vec4 *v );

	static void vec4_multiply_vec3( vec4 *dst, vec4 *v0, vec3 *v1 );

	static void vec4_multiply_vec4( vec4 *dst, vec4 *v0, vec4 *v1 );

	static void vec4_conjugate( vec4 *dst, vec4 *v );

	static void vec4_invert( vec4 *dst, vec4 *v );

	static void vec4_lerp( vec4 *dst, vec4 *v0, vec4 *v1, float t );

	static void vec4_slerp( vec4 *dst, vec4 *v0, vec4 *v1, float t );

};
#endif
