#ifndef _APP_H_
#define _APP_H_

#include "Program.h"
#include "Engine.h"
#include "Director.h"
#include "Screens.h"

enum {
	INVALID_SCREEN = 0,
	FLASH_SCREEN = 1,
	GAME_SCREEN = 2
};

class App {
private:
	int screenWidth;
	int screenHeight;
	int currentScreenId;
	Screen *currentScreen;

public:
	int isRenderable;
	static App *shared;

	App();
	~App();

	static void sharedNew();
	static void sharedDelete();

	int getScreenWidth();
	int getScreenHeight();

	static void printGLString(const char *name, GLenum s);
	static void checkGlError(const char* op);

//	GLuint loadShader(GLenum shaderType, const char* pSource);
//	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
	bool setupGraphics(int w, int h);
	void renderFrame();
};
#endif
