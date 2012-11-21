/*
 * Director.h
 * Copyright (c) 2012, Hanoilabs
 */

#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Engine.h"
#include "Matrix.h"
#include "esUtils.h"

#define MAX_MODELVIEW_MATRIX	32
#define MAX_PROJECTION_MATRIX	2
#define MAX_TEXTURE_MATRIX		2

enum {
	MODELVIEW_MATRIX	= 0,
	PROJECTION_MATRIX	= 1,
	TEXTURE_MATRIX		= 2
};

class Director {
private:
	unsigned char matrixMode;
	unsigned char modelviewMatrixIndex;
	unsigned char projectionMatrixIndex;
	unsigned char textureMatrixIndex;

	mat4 modelviewMatrix[MAX_MODELVIEW_MATRIX];
	mat4 projectionMatrix[MAX_PROJECTION_MATRIX];
	mat4 textureMatrix[MAX_TEXTURE_MATRIX];

	mat4 modelviewProjectionMatrix;

	mat3 normalMatrix;

public:
	Director();
	~Director();

	void start(void);
	void error(void);
	void setMatrixMode(unsigned char matrixMode);
	void loadIdentity(void);
	void pushMatrix(void);
	void popMatrix(void);
	void loadMatrix(mat4 *m);
	void multiplyMatrix(mat4 *m);

	void translate(float x, float y, float z);
	void rotate(float angle, float x, float y, float z);
	void scale(float x, float y, float z);

	mat4 *getModelviewMatrix(void);
	mat4 *getProjectionMatrix(void);
	mat4 *getTextureMatrix(void);
	mat4 *getModelviewProjectionMatrix(void);
	mat3 *getNormalMatrix(void);

	void ortho(float left, float right, float bottom, float top, float clipStart, float clipEnd);
	void setOrthoGraphic2D(float left, float right, float bottom, float top);
	void setOrthoGraphic(float screenRatio, float scale, float aspectRatior,
			float clipStart, float clipEnd, float screenOrientation);
	void setPerspective(float fovy, float aspectRatio, float clipStart, float clipEnd, float screenOrientation);

	void lookAt(vec3 *eye, vec3 *center, vec3 *up);

	void clearColor(float r, float g, float b, float a);
	int project(float objx, float objy, float objz, mat4 *modelviewMatrix, mat4 *projectionMatrix,
			int *viewportMatrix, float *winx, float *winy, float *winz);
	int unproject(float winx, float winy, float winz, mat4 *modelviewMatrix, mat4 *projectionMatrix,
			int *viewportMatrix, float *objx, float *objy, float *objz);
};

#endif
