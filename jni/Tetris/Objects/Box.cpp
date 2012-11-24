/*
 * Box.cpp
 * Copyright (c) 2012 HanoiLabs
 *
 */

#include "Box.h"

const char *Box::TAG = "Box";

Box::Box(float x, float y, float width, float height) :
		width(width), height(height) {
	program = new Program("glsl/simpleVertexShader.vsh", "glsl/simpleFragShader.fsh");
//    if (!gProgram) {
	if (!program->getId()) {
		LOGE(TAG, "Could not create program.");
		return;
	}

	float screenWidth = 720.0f;
	float screenHeight = 1280.0f;
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
			colors[8] = colors[9] = colors[14] = 0.0f;
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
	Director::shared->setMatrixMode(MODELVIEW_MATRIX);
	Director::shared->loadIdentity();
	vec3 e = { 0.0f, -3.0f, 0.0f };
	vec3 c = { 0.0f, 0.0f, 0.0f };
	vec3 u = { 0.0f, 0.0f, 1.0f };
//	Director::shared->lookAt(&e, &c, &u);
	static float y = 0.0f;
	y += 0.1f;
	Director::shared->translate(720 / 2, 1280/ 2, 0.0f);
	Director::shared->rotate(y * 50.0f, 0.0f, 0.0f, 1.0f);
	Director::shared->translate(-720/ 2, -1280/ 2, 0.0f);
//	Director::shared->scale(1.0f, 1.0f, 0.0f);

	if (program->getId()) {
		GLuint attrib, uniform;

		glUseProgram(program->getId());
		checkGlError("glUseProgram");

		uniform = program->getUniformLocation((char *)"uMVPMatrix" );
		glUniformMatrix4fv(uniform,
							1 /* How many 4x4 matrix */,
							GL_FALSE /* Transpose the matrix? */,
							(float *) Director::shared->getModelviewProjectionMatrix());

		attrib = program->getVertexAttribLocation((char *) "aPosition");
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, vertices);

		attrib = program->getVertexAttribLocation((char *) "aColor");
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 0, colors);

		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, vertexIndices);
	}

}
