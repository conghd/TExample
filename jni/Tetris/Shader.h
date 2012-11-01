/*
 * Shader.h
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include "Engine.h"

#define GL_VERTEX_SHADER_NAME "GL_VERTEX_SHADER"
#define GL_FRAGMENT_SHADER_NAME "GL_FRAGMENT_SHADER"

class Shader {
public:
	char name[MAX_CHAR];
	unsigned int type;
private:
	GLuint id;

public:

	Shader(char *name, unsigned int type);
	GLuint getId();
	~Shader();
	GLuint compile(const char *code, unsigned char debug);
};
#endif
