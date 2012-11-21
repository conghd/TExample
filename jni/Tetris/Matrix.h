/*
 * Matrix.h
 * Copyright (R) Oct 2012, Hanoilabs
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Engine.h"
#include "Types.h"
#include "Vector.h"

class Matrix {
public:
	static void vec3_multiply_mat3( vec3 *dst, vec3 *v, mat3 *m );

	static void vec3_multiply_mat4( vec3 *dst, vec3 *v, mat4 *m );

	static void vec4_multiply_mat4( vec4 *dst, vec4 *v, mat4 *m );

	static void mat3_identity( mat3 *m );

	static void mat3_copy_mat4( mat3 *dst, mat4 *m );

	static void mat4_identity( mat4 *m );

	static void mat4_copy_mat4( mat4 *dst, mat4 *m );

	static void mat4_translate( mat4 *dst, mat4 *m, vec3 *v );

	static void mat4_rotate_fast( mat4 *m, vec4 *v );

	static void mat4_rotate( mat4 *dst, mat4 *m, vec4 *v );

	static void mat4_scale( mat4 *dst, mat4 *m, vec3 *v );

	static unsigned char mat4_invert( mat4 *m );

	static unsigned char mat4_invert_full( mat4 *m );

	static void mat4_transpose( mat4 *m );

	static void mat4_ortho( mat4 *dst, float left, float right, float bottom, float top, float clip_start, float clip_end );

	static void mat4_copy_mat3( mat4 *dst, mat3 *m );

	static void mat4_multiply_mat3( mat4 *dst, mat4 *m0, mat3 *m1 );

	static void mat4_multiply_mat4( mat4 *dst, mat4 *m0, mat4 *m1 );

};

#endif
