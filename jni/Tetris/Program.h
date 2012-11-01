/*
 * Program.h.
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Engine.h"
#include "Shader.h"

typedef struct {
	char name[MAX_CHAR];
	unsigned int type;
	int location;
	unsigned char constant;
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
//	char name[MAX_CHAR];
	Shader *vertexShader;
	Shader *fragmentShader;
	GLuint id;
//	unsigned char uniform_count;

//	UNIFORM *uniform_array;
//	unsigned char vertex_attrib_count;
//	VERTEX_ATTRIB *vertex_attrib_array;

//	PROGRAM_DRAW_CALLBACK *program_draw_callback;
//	PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback;

public:
//	Program(char *name, char *vertex_shader_filename, char *fragment_shader_filename,
//			unsigned char relative_path,
//			unsigned char debug_shader, PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback);
//	unsigned char link(unsigned char debug);
//	void setDrawCallback(PROGRAM_DRAW_CALLBACK *program_draw_callback);
//	void setBindAttribLocationCallback(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback);
//	char getVertexAttribLocation(char *name);
//	char getUniformLocation(char *name);
//	void draw();
//	void reset();
//	unsigned char loadGfx(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback,
//			char *filename, unsigned char debug_shader, unsigned char relative_path);

	Program(const char* pVertexSource, const char* pFragmentSource);
	GLuint getId();
	~Program();
};

#endif
