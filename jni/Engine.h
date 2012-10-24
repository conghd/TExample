#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <jni.h>

#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/native_window.h>

#define LOG_TAG "Engine"


#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)

//static void printGLString(const char *name, GLenum s) {
//    const char *v = (const char *) glGetString(s);
//    LOGI("GL %s = %s\n", name, v);
//}

//static void checkGlError(const char* op) {
//    for (GLint error = glGetError(); error; error
//            = glGetError()) {
//        LOGI("after %s() glError (0x%x)\n", op, error);
//    }
//}

#endif
