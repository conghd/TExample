#include "App.h"

App *App::shared = NULL;

void App::sharedNew() {
	shared = new App();
}

void App::sharedDelete() {
	delete shared;
}

App::App() {
	this->isRenderable = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	Director::sharedNew();
	currentScreen = NULL;
	currentScreenId = INVALID_SCREEN;
}

App::~App() {
	isRenderable = 0;
	if (currentScreen != NULL) {
		delete(currentScreen);
		currentScreenId = INVALID_SCREEN;
	}

	Director::sharedDelete();
}

void App::printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("App", "GL %s = %s\n", name, v);
}

void App::checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("App", "after %s() glError (0x%x)\n", op, error);
    }
}

int App::getScreenWidth() {
	return screenWidth;
}

int App::getScreenHeight() {
	return screenHeight;
}
//GLuint App::loadShader(GLenum shaderType, const char* pSource) {
//    GLuint shader = glCreateShader(shaderType);
//    if (shader) {
//        glShaderSource(shader, 1, &pSource, NULL);
//        glCompileShader(shader);
//        GLint compiled = 0;
//        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//        if (!compiled) {
//            GLint infoLen = 0;
//            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
//            if (infoLen) {
//                char* buf = (char*) malloc(infoLen);
//                if (buf) {
//                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
//                    LOGE("Could not compile shader %d:\n%s\n",
//                            shaderType, buf);
//                    free(buf);
//                }
//                glDeleteShader(shader);
//                shader = 0;
//            }
//        }
//    }
//    return shader;
//}

//GLuint App::createProgram(const char* pVertexSource, const char* pFragmentSource) {
//	vShader = new Shader((char *)GL_VERTEX_SHADER_NAME, GL_VERTEX_SHADER);
//	vShader->compile(pVertexSource, 1);
//	vertexShader = vShader->id;
//	LOGD("=====SHADER ID: %d", vShader->id);
////    vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
//    if (!vertexShader) {
//        return 0;
//    }
//
//    fragShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
//    if (!fragShader) {
//        return 0;
//    }
//
//    GLuint program = glCreateProgram();
//    if (program) {
//        glAttachShader(program, vertexShader);
//        checkGlError("glAttachShader");
//        glAttachShader(program, fragShader);
//        checkGlError("glAttachShader");
//        glLinkProgram(program);
//        GLint linkStatus = GL_FALSE;
//        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
//        if (linkStatus != GL_TRUE) {
//            GLint bufLength = 0;
//            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
//            if (bufLength) {
//                char* buf = (char*) malloc(bufLength);
//                if (buf) {
//                    glGetProgramInfoLog(program, bufLength, NULL, buf);
//                    LOGE("Could not link program:\n%s\n", buf);
//                    free(buf);
//                }
//            }
//            glDeleteProgram(program);
//            program = 0;
//        }
//    }
//    return program;
//}

bool App::setupGraphics(int w, int h) {
	this->screenWidth = w;
	this->screenHeight = h;
	LOGD("App", "width: %d, height: %d", w, h);
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("App", "setupGraphics(%d, %d)", w, h);
    Director::shared->start();

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    float half_width = (float) w * 0.5f;
    float half_height = (float) h * 0.5f;
    Director::shared->setMatrixMode(PROJECTION_MATRIX);
    Director::shared->loadIdentity();
	Director::shared->setPerspective(60.0f,
			(float) App::shared->getScreenWidth() / (float) App::shared->getScreenHeight(),
			0.01f,
			3550.0f,
			0.0f);
	glDisable(GL_CULL_FACE);
//    Director::shared->setOrthoGraphic2D(-half_width,
//    							 	 	 half_width,
//    							 	 	-half_height,
//    							 	 	 half_height);
    Director::shared->translate(-half_width, -half_height, 0.0f);
//    vec3 c = {0.0f, 0.0f, 0.0f };	// center
    vec3 c = { 0.0f, 0.0f, 0.0f };	// center
    	vec3 u = { 0.0f, 0.0f, -1.0f };	// up

//    	vec3 e = { 0.0f, 0.001f, 545.0f }; // eye
    	vec3 e = { 0.0f, 0.0001f, 2.2566f * w }; // eye
    //	vec3 c = { App::shared->getScreenWidth() / 2.0f, App::shared->getScreenHeight() / 2.0f, 0.0f };	// center
    //	vec3 u = { 0.0f, 0.0f, 1.0f };	// up
    	Director::shared->lookAt(&e, &c, &u);
//    glDisable(GL_DEPTH_TEST);
//    glDepthMask(GL_FALSE);

    isRenderable = 1;
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return true;
}

void App::renderFrame() {
    if (currentScreenId == INVALID_SCREEN) {
    	currentScreenId = FLASH_SCREEN;
    	currentScreen = (Screen *) new FlashScreen();
    }

    if (isRenderable)
		currentScreen->draw();
}
