/*
 * Program.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "Program.h"

Program::Program(const char* pVertexSource, const char* pFragmentSource) {
	this->id = 0;

	vertexShader = new Shader((char *)GL_VERTEX_SHADER_NAME, GL_VERTEX_SHADER);
	LOGD("NAME: %s", pVertexSource);
	vertexShader->compile(pVertexSource, 1);
	if (!vertexShader->getId()) return;

	fragmentShader = new Shader((char *)GL_FRAGMENT_SHADER_NAME, GL_FRAGMENT_SHADER);
	LOGD("NAME: %s", pFragmentSource);
	fragmentShader->compile(pFragmentSource, 1);
	if (!fragmentShader->getId()) return;

	this->id = glCreateProgram();
	if (this->id) {
		glAttachShader(this->id, vertexShader->getId());
		checkGlError("glAttachShader");
		glAttachShader(this->id, fragmentShader->getId());
		checkGlError("glAttachShader");
		glLinkProgram(this->id);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(this->id, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(this->id, bufLength, NULL, buf);
					LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(this->id);
			this->id= 0;
		}
	}
}

GLuint Program::getId() {
	return this->id;
}
//Program::Program(char *name, char *vertex_shader_filename, char *fragment_shader_filename, unsigned char relative_path,
//			unsigned char debug_shader, PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback) {
//	strcpy(this->name, name);
//}
//unsigned char Program::link(unsigned char debug) {
//
//}

//void Program::setDrawCallback(PROGRAM_DRAW_CALLBACK *program_draw_callback) {
//
//}

//void Program::setBindAttribLocationCallback(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback) {
//
//}

GLuint Program::getVertexAttribLocation(const char *name) {
	if (name == NULL || id == 0) return 0;
	return glGetAttribLocation(id, name);
}

GLuint Program::getUniformLocation(const char *name) {
	unsigned char i = 0;
	while (i != numUniforms) {
		if (!strcmp(uniforms[i].name, name)) {
			return uniforms[i].location;
		}
		i++;
	}

	return -1;
}

//void Program::draw() {
//
//}

//void Program::reset() {
//
//}

//unsigned char Program::loadGfx(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback, PROGRAM_DRAW_CALLBACK *program_draw_callback,
//			char *filename, unsigned char debug_shader, unsigned char relative_path) {

//}

Program::~Program() {
	if (this->id) {
		glDeleteProgram(this->id);
		this->id = 0;
	}

	if (fragmentShader) {
		delete fragmentShader;
	}

	if (vertexShader) {
		delete vertexShader;
	}
}
