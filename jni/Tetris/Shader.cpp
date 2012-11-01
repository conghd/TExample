/*
 * Shader.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "Shader.h"

Shader::Shader(char *name, unsigned int type) {
	strcpy(this->name, name);
	this->type = type;
	this->id = 0;
}

GLuint Shader::getId() {
	return this->id;
}

Shader::~Shader() {
	if (this->id) {
		glDeleteShader(this->id);
		this->id = 0;
	}
}

GLuint Shader::compile(const char *code, unsigned char debug) {
	if ((this->id) || code == NULL) {
		if (debug) {
			char shaderName[MAX_CHAR] = {""};
			if (this->type == GL_VERTEX_SHADER)
				strcpy(shaderName, GL_VERTEX_SHADER_NAME);
			else
				strcpy(shaderName, GL_FRAGMENT_SHADER_NAME);
			LOGD("[ %s:%s ] Compilation failed, source: %s\n", this->name, shaderName, code);
		}
		return 0;
	}
	this->id = glCreateShader(this->type);

	if (this->id) {
		glShaderSource(this->id, 1, &code, NULL);
		glCompileShader(this->id);
		if (debug) {
			char shaderName[MAX_CHAR] = {""};
			if (this->type == GL_VERTEX_SHADER)
				strcpy(shaderName, GL_VERTEX_SHADER_NAME);
			else
				strcpy(shaderName, GL_FRAGMENT_SHADER_NAME);

			GLint compiled = 0;
			glGetShaderiv(this->id, GL_COMPILE_STATUS, &compiled);
			GLint infoLen = 0;
			glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char *buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(this->id, infoLen, NULL, buf);
//					#ifdef __IPHONE_4_0
//						print("[ %s:%s ]\n%s", this->name, shaderName, buf);
//					#else
						LOGD("[ %s:%s ]\n%s", this->name, shaderName, buf);
//					#endif
					free(buf);
				}
			}
			if (!compiled) {
			} else {

			}
		}
	}

	return this->id;
}
