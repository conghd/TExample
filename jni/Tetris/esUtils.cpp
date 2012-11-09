/*
 * esUtils.cpp
 * Copyright (c) 2012, Hanoilabs
 *
 */

#include "esUtils.h"

void EsUtils::loadIdentity(mat4 *matrix) {
	memset(matrix, 0x0, sizeof(mat4));
	matrix->m[0].x = 1.0f;
	matrix->m[1].y = 1.0f;
	matrix->m[2].z = 1.0f;
	matrix->m[3].w = 1.0f;
}

void EsUtils::matrixMultiply(mat4 *result, mat4 *m0, mat4 *m1) {
	mat4 mat;

	mat.m[ 0 ].x = m0->m[ 0 ].x * m1->m[ 0 ].x + m0->m[ 1 ].x * m1->m[ 0 ].y + m0->m[ 2 ].x * m1->m[ 0 ].z + m0->m[ 3 ].x * m1->m[ 0 ].w;
	mat.m[ 0 ].y = m0->m[ 0 ].y * m1->m[ 0 ].x + m0->m[ 1 ].y * m1->m[ 0 ].y + m0->m[ 2 ].y * m1->m[ 0 ].z + m0->m[ 3 ].y * m1->m[ 0 ].w;
	mat.m[ 0 ].z = m0->m[ 0 ].z * m1->m[ 0 ].x + m0->m[ 1 ].z * m1->m[ 0 ].y + m0->m[ 2 ].z * m1->m[ 0 ].z + m0->m[ 3 ].z * m1->m[ 0 ].w;
	mat.m[ 0 ].w = m0->m[ 0 ].w * m1->m[ 0 ].x + m0->m[ 1 ].w * m1->m[ 0 ].y + m0->m[ 2 ].w * m1->m[ 0 ].z + m0->m[ 3 ].w * m1->m[ 0 ].w;

	mat.m[ 1 ].x = m0->m[ 0 ].x * m1->m[ 1 ].x + m0->m[ 1 ].x * m1->m[ 1 ].y + m0->m[ 2 ].x * m1->m[ 1 ].z + m0->m[ 3 ].x * m1->m[ 1 ].w;
	mat.m[ 1 ].y = m0->m[ 0 ].y * m1->m[ 1 ].x + m0->m[ 1 ].y * m1->m[ 1 ].y + m0->m[ 2 ].y * m1->m[ 1 ].z + m0->m[ 3 ].y * m1->m[ 1 ].w;
	mat.m[ 1 ].z = m0->m[ 0 ].z * m1->m[ 1 ].x + m0->m[ 1 ].z * m1->m[ 1 ].y + m0->m[ 2 ].z * m1->m[ 1 ].z + m0->m[ 3 ].z * m1->m[ 1 ].w;
	mat.m[ 1 ].w = m0->m[ 0 ].w * m1->m[ 1 ].x + m0->m[ 1 ].w * m1->m[ 1 ].y + m0->m[ 2 ].w * m1->m[ 1 ].z + m0->m[ 3 ].w * m1->m[ 1 ].w;

	mat.m[ 2 ].x = m0->m[ 0 ].x * m1->m[ 2 ].x + m0->m[ 1 ].x * m1->m[ 2 ].y + m0->m[ 2 ].x * m1->m[ 2 ].z + m0->m[ 3 ].x * m1->m[ 2 ].w;
	mat.m[ 2 ].y = m0->m[ 0 ].y * m1->m[ 2 ].x + m0->m[ 1 ].y * m1->m[ 2 ].y + m0->m[ 2 ].y * m1->m[ 2 ].z + m0->m[ 3 ].y * m1->m[ 2 ].w;
	mat.m[ 2 ].z = m0->m[ 0 ].z * m1->m[ 2 ].x + m0->m[ 1 ].z * m1->m[ 2 ].y + m0->m[ 2 ].z * m1->m[ 2 ].z + m0->m[ 3 ].z * m1->m[ 2 ].w;
	mat.m[ 2 ].w = m0->m[ 0 ].w * m1->m[ 2 ].x + m0->m[ 1 ].w * m1->m[ 2 ].y + m0->m[ 2 ].w * m1->m[ 2 ].z + m0->m[ 3 ].w * m1->m[ 2 ].w;

	mat.m[ 3 ].x = m0->m[ 0 ].x * m1->m[ 3 ].x + m0->m[ 1 ].x * m1->m[ 3 ].y + m0->m[ 2 ].x * m1->m[ 3 ].z + m0->m[ 3 ].x * m1->m[ 3 ].w;
	mat.m[ 3 ].y = m0->m[ 0 ].y * m1->m[ 3 ].x + m0->m[ 1 ].y * m1->m[ 3 ].y + m0->m[ 2 ].y * m1->m[ 3 ].z + m0->m[ 3 ].y * m1->m[ 3 ].w;
	mat.m[ 3 ].z = m0->m[ 0 ].z * m1->m[ 3 ].x + m0->m[ 1 ].z * m1->m[ 3 ].y + m0->m[ 2 ].z * m1->m[ 3 ].z + m0->m[ 3 ].z * m1->m[ 3 ].w;
	mat.m[ 3 ].w = m0->m[ 0 ].w * m1->m[ 3 ].x + m0->m[ 1 ].w * m1->m[ 3 ].y + m0->m[ 2 ].w * m1->m[ 3 ].z + m0->m[ 3 ].w * m1->m[ 3 ].w;

	memcpy(result, &mat, sizeof(mat4));
}

void EsUtils::transpose(mat4 *m) {
	float t;

	t			= m->m[ 0 ].y;
	m->m[ 0 ].y = m->m[ 1 ].x;
	m->m[ 1 ].x = t;

	t			= m->m[ 0 ].z;
	m->m[ 0 ].z = m->m[ 2 ].x;
	m->m[ 2 ].x = t;

	t			= m->m[ 0 ].w;
	m->m[ 0 ].w = m->m[ 3 ].x;
	m->m[ 3 ].x = t;

	t			= m->m[ 1 ].z;
	m->m[ 1 ].z = m->m[ 2 ].y;
	m->m[ 2 ].y = t;

	t			= m->m[ 1 ].w ;
	m->m[ 1 ].w = m->m[ 3 ].y ;
	m->m[ 3 ].y = t;

	t			= m->m[ 2 ].w ;
	m->m[ 2 ].w = m->m[ 3 ].z ;
	m->m[ 3 ].z = t;
}

void EsUtils::translate(mat4 *dst_m, mat4 *m, GLfloat tx, GLfloat ty, GLfloat tz) {
	dst_m->m[ 3 ].x = m->m[ 0 ].x * tx + m->m[ 1 ].x * ty + m->m[ 2 ].x * tz + m->m[ 3 ].x;
	dst_m->m[ 3 ].y = m->m[ 0 ].y * tx + m->m[ 1 ].y * ty + m->m[ 2 ].y * tz + m->m[ 3 ].y;
	dst_m->m[ 3 ].z = m->m[ 0 ].z * tx + m->m[ 1 ].z * ty + m->m[ 2 ].z * tz + m->m[ 3 ].z;
	dst_m->m[ 3 ].w = m->m[ 0 ].w * tx + m->m[ 1 ].w * ty + m->m[ 2 ].w * tz + m->m[ 3 ].w;
}

void EsUtils::translate(mat4 *m, GLfloat tx, GLfloat ty, GLfloat tz) {
	translate(m, m, tx, ty, tz);
}

void EsUtils::translate(mat4 *dst_m, mat4 *m, vec3 *v) {
	translate(dst_m, m, v->x, v->y, v->z);
}

void EsUtils::translate(mat4 *m, vec3 *v) {
	translate(m, m, v->x, v->y, v->z);
}

void EsUtils::scale(mat4 *dst_m, mat4 *m, GLfloat sx, GLfloat sy, GLfloat sz) {
	dst_m->m[ 0 ].x = m->m[ 0 ].x * sx;
	dst_m->m[ 0 ].y = m->m[ 0 ].y * sx;
	dst_m->m[ 0 ].z = m->m[ 0 ].z * sx;
	dst_m->m[ 0 ].w = m->m[ 0 ].w * sx;

	dst_m->m[ 1 ].x = m->m[ 1 ].x * sy;
	dst_m->m[ 1 ].y = m->m[ 1 ].y * sy;
	dst_m->m[ 1 ].z = m->m[ 1 ].z * sy;
	dst_m->m[ 1 ].w = m->m[ 1 ].w * sy;

	dst_m->m[ 2 ].x = m->m[ 2 ].x * sz;
	dst_m->m[ 2 ].y = m->m[ 2 ].y * sz;
	dst_m->m[ 2 ].z = m->m[ 2 ].z * sz;
	dst_m->m[ 2 ].w = m->m[ 2 ].w * sz;
}

void EsUtils::scale(mat4 *m, GLfloat sx, GLfloat sy, GLfloat sz) {
	scale(m, m, sx, sy, sz);
}

void EsUtils::scale(mat4 *m, vec3 *v) {
	scale(m, m, v->x, v->y, v->z);
}

void EsUtils::scale(mat4 *dst_m, mat4 *m, vec3 *v) {
	scale(dst_m, m, v->x, v->y, v->z);
}
