#include "App.h"

App *App::shared = NULL;

void App::sharedNew() {
	shared = new App();
}

void App::sharedDelete() {
	delete shared;
}

App::App() {
	this->grey = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	Director::sharedNew();
}

App::~App() {
	Director::sharedDelete();
	if (program) {
		delete program;
		program = NULL;
	}
}

void App::printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}

void App::checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
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
	LOGD("width: %d, height: %d", w, h);
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
//    gProgram = createProgram(gVertexShader, gFragmentShader);
//    program = new Program(gVertexShader, gFragmentShader);
    program = new Program("glsl/simpleVertexShader.glsl", "glsl/simpleFragShader.glsl");
//    if (!gProgram) {
    if (!program->getId()) {
        LOGE("Could not create program.");
        return false;
    }
//    gvPositionHandle = program->getVertexAttribLocation("vPosition");
//    checkGlError("glGetAttribLocation");
//    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
//            gvPositionHandle);


    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    float half_width = (float) w * 0.5f;
    float half_height = (float) h * 0.5f;
    LOGD("===== 1");
    Director::shared->setMatrixMode(PROJECTION_MATRIX);
    LOGD("===== 2");
    Director::shared->loadIdentity();
    LOGD("===== 3");
    Director::shared->setOrthoGraphic2D(-half_width,
    							 	 	 half_width,
    							 	 	-half_height,
    							 	 	 half_height);
    LOGD("===== 4");
    Director::shared->translate(-half_width, -half_height, 0.0f);
//    Director::shared->translate(0.0f, 0.0f, 0.0f);
    LOGD("===== 5");
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    return true;
}

void App::renderFrame() {
	static const float POSITION[ 8 ] = {
		0.0f, 0.0f, // Down left (pivot point)
		screenWidth / 2, 0.0f, // Up left
		0.0f, screenHeight / 2, // Down right
		screenWidth / 2, screenHeight / 2// Up right
		};
	static const unsigned short triangle_indices[6] = {
			1, 0, 2,
			1, 3, 2
	};
	static const unsigned short triangle_strip_indices[4] = {
			0, 1, 2, 3
	};
	static const unsigned short triangle_fan_indices[4] = {
			1, 0, 2, 3
	};

		static const float COLOR[ 16 ] = {
		1.0f, 0.0f, 0.0f, 1.0f, // Red
		0.0f, 1.0f, 0.0f, 1.0f, // Green
		0.0f, 0.0f, 1.0f, 1.0f, // Blue
		1.0f, 1.0f, 0.0f, 1.0f  // Yellow
		};
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    Director::shared->setMatrixMode(MODELVIEW_MATRIX);
    Director::shared->loadIdentity();
    Director::shared->scale(1.0f, 1.0f, 0.0f);

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
		glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, POSITION);

		attrib = program->getVertexAttribLocation((char *) "aColor");
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, 0, COLOR);

//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, triangle_indices);
//		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, triangle_strip_indices);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, triangle_fan_indices);
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//		checkGlError("glDrawArrays");
    }

//    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
//    checkGlError("glVertexAttribPointer");
//    glEnableVertexAttribArray(gvPositionHandle);
//    checkGlError("glEnableVertexAttribArray");
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    checkGlError("glDrawArrays");
}
