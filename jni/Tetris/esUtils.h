/*
 * esUtils.h
 * Copyright (c) 2012, Hanoilabs
 */

#ifndef ES_UTILS_H
#define ES_UTILS_H

#include "Engine.h"

class EsUtils {
public:
	static void loadIdentity(mat4 *matrix);
	static void matrixMultiply(mat4 *result, mat4 *srcA, mat4 *srcB);
	static void transpose(mat4 *m);

	static void translate(mat4 *dst_m, mat4 *m, GLfloat tx, GLfloat ty, GLfloat tz);
	static void translate(mat4 *m, GLfloat tx, GLfloat ty, GLfloat tz);
	static void translate(mat4 *dst_m, mat4 *m, vec3 *v);
	static void translate(mat4 *m, vec3 *v);

	static void scale(mat4 *matrix, GLfloat sx, GLfloat sy, GLfloat sz);
	static void scale(mat4 *dst_m, mat4 *m, GLfloat sx, GLfloat sy, GLfloat sz);
	static void scale(mat4 *matrix, vec3 *v);
	static void scale(mat4 *dst_m, mat4 *m, vec3 *v);

	static void rotate(mat4 *matrix, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

	static void frustum(mat4 *matrix, float left, float right, float bottom, float top, float nearZ, float farZ);
	static void perspective(mat4 *matrix, float fovy, float aspect, float nearZ, float farZ);
	static void orthor(mat4 *matrix, float left, float right, float bottom, float top, float nearZ, float farZ);
};

#endif
