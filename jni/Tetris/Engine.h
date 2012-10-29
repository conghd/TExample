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
//#include <android/native_window.h>

#include "types.h"
#include "Log.h"

#define LOG_TAG "Engine"

#ifdef __IPHONE_4_0
#undef __IPHONE_4_0
#endif

#ifndef __ANDROID
#define __ANDROID
#endif

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

#endif
