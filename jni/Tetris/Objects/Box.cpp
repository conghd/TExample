/*
 * Box.cpp
 * Copyright (c) 2012 HanoiLabs
 *
 */

#include "Box.h"
#include "../App.h"

const char *Box::TAG = "Box";

Box::Box(float x, float y, float width, float height) :
		width(width), height(height) {
	uMVPMatrix = -1;
	program = new Program("glsl/simpleVertexShader.vsh", "glsl/simpleFragShader.fsh");
//    if (!gProgram) {
	if (!program->getId()) {
		LOGE(TAG, "Could not create program.");
		return;
	}

	vertices = (float *) malloc(8 * sizeof(float));
	vertices[0] = vertices[2] = x;
	vertices[4] = vertices[6] = width + x;

	vertices[1] = vertices[5] = y;
	vertices[3] = vertices[7] = y + height;

	vertexIndices = (unsigned short *) malloc(4 * sizeof(unsigned short));
	vertexIndices[0] = 0;
	vertexIndices[1] = 1;
	vertexIndices[2] = 2;
	vertexIndices[3] = 3;

	colors = (float *) malloc(16 * sizeof(float));
	colors[0] = colors[3] = colors[5] = colors[7] =
			colors[10] = colors[11] = colors[12] = colors[13] = colors[15] = 1.0f;
	colors[1] = colors[2] = colors[4] = colors[6] =
			colors[8] = colors[9] = colors[14] = 1.0f; //0.0f;
}

Box::~Box() {
	if (program) {
		delete program;
		program = NULL;
	}

	free(colors);
	free(vertexIndices);
	free(vertices);
}

void Box::draw() {
//	Director::shared->setMatrixMode(PROJECTION_MATRIX);
//	Director::shared->loadIdentity();
//	Director::shared->setPerspective(45.0f,
//			(float) App::shared->getScreenWidth() / (float) App::shared->getScreenHeight(),
//			0.01f,
//			100.0f,
//			0.0f);
//	glDisable(GL_CULL_FACE);

//	vec3 e = { 0.0f, 0.0f, -1000.0f }; // eye
//	vec3 c = {0.0f, 0.0f, 0.0f };	// center
//	vec3 u = { 0.0f, 0.0f, -1.0f };	// up

//	vec3 e = { App::shared->getScreenWidth(), App::shared->getScreenHeight(), 1000.0f }; // eye
//	vec3 e = { 0.0f, 0.001f, 1545.0f }; // eye
//	vec3 c = { App::shared->getScreenWidth() / 2.0f, App::shared->getScreenHeight() / 2.0f, 0.0f };	// center
//	vec3 u = { 0.0f, 0.0f, 1.0f };	// up
//	Director::shared->lookAt(&e, &c, &u);

	static float y = 0.0f;
//	static const float POSITION[ 12 ] = {
//		0.0f, 0.0f, 0.0f, // Bottom left
//		720.0f, 0.0f, 0.0f,
//		0.0f, 1280.0f,  0.0f,
//		360.0f, 1280.0f,  0.0f // Top right
//		};
	static const int SIZE = 100;
	static const float POSITION[ 12 ] = {
		-0.5f * SIZE, -0.5f * SIZE, 0.0f, // Bottom left
		 0.5f * SIZE, -0.5f * SIZE, 0.0f,
		-0.5f * SIZE,  0.5f * SIZE, 0.0f,
		 0.5f * SIZE,  0.5f * SIZE, 0.0f // Top right
		};

	static const float COLOR[ 16 ] = {
	1.0f, 0.0f, 0.0f, 1.0f, // Red
	0.0f, 1.0f, 0.0f, 1.0f, // Green
	0.0f, 0.0f, 1.0f, 1.0f, // Blue
	1.0f, 1.0f, 0.0f, 1.0f  // Yellow
	};
	y += 0.1f;
//	Director::shared->translate(720 / 2, 1280/ 2, 0.0f);
//	Director::shared->rotate(y * 50.0f, 0.0f, 0.0f, 1.0f);
//	Director::shared->translate(-720/ 2, -1280/ 2, 0.0f);
//	Director::shared->scale(2.0f, 1.0f, 1.0f);

	if (program->getId()) {
		GLuint attrib, uniform;

		glUseProgram(program->getId());
		checkGlError("glUseProgram");

		if (uMVPMatrix == -1) {
		uMVPMatrix = program->getUniformLocation((char *)"uMVPMatrix" );
		glUniformMatrix4fv(uMVPMatrix,
							1 /* How many 4x4 matrix */,
							GL_FALSE /* Transpose the matrix? */,
							(float *) Director::shared->getModelviewProjectionMatrix());
		}

		attrib = program->getVertexAttribLocation((char *) "aPosition");
		glEnableVertexAttribArray(attrib);
//		glVertexAttribPointer(attrib, 3, GL_FLOAT, GL_FALSE, 0, POSITION);
		glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, vertices);

		attrib = program->getVertexAttribLocation((char *) "aColor");
		glEnableVertexAttribArray(attrib);
//		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 0, COLOR);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 0, colors);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, vertexIndices);
	}

}
