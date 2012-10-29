/*
 * Program.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "Program.h"

Program::Program(char *name, char *vertex_shader_filename, char *fragment_shader_filename, unsigned char relative_path,
			unsigned char debug_shader, PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
			PROGRAM_DRAW_CALLBACK *program_draw_callback) {
	strcpy(this->name, name);
}
unsigned char Program::link(unsigned char debug) {

}

void Program::setDrawCallback(PROGRAM_DRAW_CALLBACK *program_draw_callback) {

}

void Program::setBindAttribLocationCallback(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback) {

}

char Program::getVertexAttribLocation(char *name) {

}

char Program::getUniformLocation(char *name) {

}

void Program::draw() {

}

void Program::reset() {

}

unsigned char Program::loadGfx(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback, PROGRAM_DRAW_CALLBACK *program_draw_callback,
			char *filename, unsigned char debug_shader, unsigned char relative_path) {

}

Program::~Program() {
	if (uniform_array)
		free(uniform_array);
	if (vertex_attrib_array)
		free(vertex_attrib_array);

	if (this->id) {
		glDeleteProgram(this->id);
		this->id = 0;
	}
}
