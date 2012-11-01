#ifndef _APP_H_
#define _APP_H_

#include "Program.h"
#include "Engine.h"

static const char gVertexShader[] =
			  "attribute vec4 vPosition;\n"
			    "void main() {\n"
			    "  gl_Position = vPosition;\n"
			    "}\n";

static const char gFragmentShader[] =
			 "precision mediump float;\n"
			    "void main() {\n"
			    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
			    "}\n";
const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
	        0.5f, -0.5f };

class App {
public:
	static App *shared;

	App();
	~App();

	GLuint gvPositionHandle;
	Program *program;


	float grey;

	static void sharedNew();
	static void sharedDelete();

	static void printGLString(const char *name, GLenum s);
	static void checkGlError(const char* op);

	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
	bool setupGraphics(int w, int h);
	void renderFrame();
};
#endif
