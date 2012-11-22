/*
 * Program.h
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Engine.h"
#include "Shader.h"

typedef struct {
	char			name[MAX_CHAR];
	unsigned int	type;
	int 			location;
	unsigned char 	constant;
} UNIFORM;

typedef struct
{
	char			name[ MAX_CHAR ];
	unsigned int	type;
	int				location;

} VERTEX_ATTRIB;

typedef void(PROGRAM_DRAW_CALLBACK(void *));
typedef void(PROGRAM_BIND_ATTRIB_CALLBACK(void*));


class Program {
private:
	char 			name[MAX_CHAR];
	Shader 			*vertexShader;
	Shader 			*fragmentShader;
	GLuint 			id;

	unsigned char 	numUniforms;
	UNIFORM 		*uniforms;

	unsigned char 	numVertexAttribs;
	VERTEX_ATTRIB 	*vertexAttribs;

//	PROGRAM_DRAW_CALLBACK *program_draw_callback;
//	PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback;

private:
	unsigned char addUniform(char *name, unsigned char type);
	unsigned char addVertexAttrib(char *name, unsigned char type);

public:
//	Program(char *name, char *vertex_shader_filename, char *fragment_shader_filename,
//			unsigned char relative_path,
//			unsigned char debug_shader, PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback);
	unsigned char link(unsigned char debug);
//	void setDrawCallback(PROGRAM_DRAW_CALLBACK *program_draw_callback);
//	void setBindAttribLocationCallback(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback);
	GLuint getVertexAttribLocation(const char *name);
	GLuint getUniformLocation(const char *name);
//	void draw();
//	void reset();
//	unsigned char loadGfx(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback,
//			char *filename, unsigned char debug_shader, unsigned char relative_path);

	Program(const char* vShaderFilename, const char* fShaderFilename);
	GLuint getId();
	~Program();
};

#endif
