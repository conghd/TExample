/*
 * Program.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "Program.h"

Program::Program(const char* pVertexSource, const char* pFragmentSource) {
	this->id = 0;
	this->numUniforms = 0;
	this->numVertexAttribs = 0;

	uniforms = NULL;
	vertexAttribs = NULL;

	vertexShader = new Shader((char *)GL_VERTEX_SHADER_NAME, GL_VERTEX_SHADER);
	LOGD("NAME: %s", pVertexSource);
	vertexShader->compile(pVertexSource, 1);
	if (!vertexShader->getId()) return;

	fragmentShader = new Shader((char *)GL_FRAGMENT_SHADER_NAME, GL_FRAGMENT_SHADER);
	LOGD("NAME: %s", pFragmentSource);
	fragmentShader->compile(pFragmentSource, 1);
	if (!fragmentShader->getId()) return;

	link(1);

//	this->id = glCreateProgram();
//	if (this->id) {
//		glAttachShader(this->id, vertexShader->getId());
//		checkGlError("glAttachShader");
//		glAttachShader(this->id, fragmentShader->getId());
//		checkGlError("glAttachShader");
//		glLinkProgram(this->id);
//		GLint linkStatus = GL_FALSE;
//		glGetProgramiv(this->id, GL_LINK_STATUS, &linkStatus);
//		if (linkStatus != GL_TRUE) {
//			GLint bufLength = 0;
//			glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &bufLength);
//			if (bufLength) {
//				char* buf = (char*) malloc(bufLength);
//				if (buf) {
//					glGetProgramInfoLog(this->id, bufLength, NULL, buf);
//					LOGE("Could not link program:\n%s\n", buf);
//					free(buf);
//				}
//			}
//			glDeleteProgram(this->id);
//			this->id= 0;
//		}
//	}
}

GLuint Program::getId() {
	return this->id;
}
//Program::Program(char *name, char *vertex_shader_filename, char *fragment_shader_filename, unsigned char relative_path,
//			unsigned char debug_shader, PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback,
//			PROGRAM_DRAW_CALLBACK *program_draw_callback) {
//	strcpy(this->name, name);
//}

unsigned char Program::link(unsigned char debug) {
	unsigned int i = 0, type;

	char *log, name[ MAX_CHAR ];

	int status, len, total, size;

	if(this->id) return 0;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader->getId());

	glAttachShader(this->id, fragmentShader->getId());

//	if(program->programbindattribcallback) program->programbindattribcallback(program);

	glLinkProgram(this->id);

	if(debug)
	{
		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &len);

		if(len)
		{
			log = (char *) malloc(len);
			glGetProgramInfoLog(this->id, len, &len, log);

			#ifdef __IPHONE_4_0

				printf("[ %s ]\n%s", this->name, log);
			#else
				__android_log_print(ANDROID_LOG_ERROR, "", "[ %s ]\n%s", this->name, log);
			#endif

			free(log);
		}
	}

	glGetProgramiv(this->id, GL_LINK_STATUS, &status);

	if (!status) goto delete_program;


	if (debug)
	{
		glValidateProgram(this->id);

		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &len);

		if (len)
		{
			log = (char *) malloc(len);
			glGetProgramInfoLog(this->id, len, &len, log);

			#ifdef __IPHONE_4_0
				printf("[ %s ]\n%s", this->name, log);
			#else
				__android_log_print(ANDROID_LOG_ERROR, "", "[ %s ]\n%s", this->name, log);
			#endif

			free(log);
		}

		glGetProgramiv(this->id, GL_VALIDATE_STATUS, &status);

		if(!status) goto delete_program;
	}


	glGetProgramiv(this->id, GL_ACTIVE_ATTRIBUTES, &total);

	i = 0;
	while(i != total)
	{
		glGetActiveAttrib(this->id,
						   i,
						   MAX_CHAR,
						   &len,
						   &size,
						   &type,
						   name);

		addVertexAttrib(name, type);

		++i;
	}

	glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &total);

	i = 0;
	while(i != total)
	{
		glGetActiveUniform(this->id,
							i,
							MAX_CHAR,
							&len,
							&size,
							&type,
							name);

		addUniform(name, type);

		++i;
	}

	return 1;

	delete_program:
	glDeleteProgram(this->id);

	return 0;
}

//void Program::setDrawCallback(PROGRAM_DRAW_CALLBACK *program_draw_callback) {
//
//}

//void Program::setBindAttribLocationCallback(PROGRAM_BIND_ATTRIB_CALLBACK *program_bind_attrib_callback) {
//
//}

unsigned char Program::addUniform(char *name, unsigned char type) {
	unsigned char uniformIndex = numUniforms++;
//	numUniforms++;
	uniforms = (UNIFORM *) realloc(uniforms, numUniforms * sizeof(UNIFORM));

	memset(&uniforms[uniformIndex], 0, sizeof(UNIFORM));

	strcpy(uniforms[uniformIndex].name, name);

	uniforms[uniformIndex].type = type;

	uniforms[uniformIndex].location = glGetUniformLocation(this->id, name);

	return uniformIndex;
}

unsigned char Program::addVertexAttrib(char *name, unsigned char type) {
	unsigned char vertexAttribIndex = numVertexAttribs++;

//	numVertexAttribs++;
	vertexAttribs = (VERTEX_ATTRIB *) realloc(vertexAttribs, numVertexAttribs * sizeof(VERTEX_ATTRIB));

	memset(&vertexAttribs[vertexAttribIndex], 0, sizeof(VERTEX_ATTRIB));

	strcpy(vertexAttribs[vertexAttribIndex].name, name);

	vertexAttribs[vertexAttribIndex].type = type;

	vertexAttribs[vertexAttribIndex].location = glGetAttribLocation(this->id, name);

	return vertexAttribIndex;
}

GLuint Program::getVertexAttribLocation(const char *name) {
	if (name == NULL || id == 0) return -1;
	unsigned char i = 0;

	while(i != numVertexAttribs)
	{
		if( !strcmp(vertexAttribs[i].name, name))
			return vertexAttribs[i].location;
		++i;
	}

	return -1;
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
