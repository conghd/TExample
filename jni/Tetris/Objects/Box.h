/*
 * Box.h.
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef BOX_H
#define BOX_H

#include "../Engine.h"
#include "../Director.h"
#include "../Program.h"

class Box {

private:
	float width;
	float height;

	Program *program;
	GLuint aPosition;
	GLuint aColor;
	GLuint uMVPMatrix;
	float *vertices;
	unsigned short *vertexIndices;
	float *colors;

public:
	static const char *TAG;
	Box(float x, float y, float width, float height);
	~Box();

	void draw();
	void update(void);
};


#endif
