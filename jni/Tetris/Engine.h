#ifndef _ENGINE_H_
#define _ENGINE_H_

#ifndef __ANDROID
#define __ANDROID
#endif

#ifdef __IPHONE_4_0
#undef __IPHONE_4_0
#endif

#ifdef __IPHONE_4_0

	#include <OpenGLES/ES2/gl.h>
	#include <OpenGLES/ES2/glext.h>

	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>

	#include "png.h"
	#include "zlib.h"
	#include "unzip.h"
	#include "NvTriStrip.h"

	#include "btBulletDynamicsCommon.h"
	#include "btSoftRigidDynamicsWorld.h"
	#include "btSoftBodyRigidBodyCollisionConfiguration.h"
	#include "btShapeHull.h"
	#include "btSoftBodyHelpers.h"
	#include "btSoftBody.h"
	#include "btGImpactShape.h"
	#include "btGImpactCollisionAlgorithm.h"
	#include "btBulletWorldImporter.h"

	#include "Recast.h"
	#include "DetourDebugDraw.h"
	#include "DetourNavMesh.h"
	#include "DetourNavMeshBuilder.h"

	#include "stb_truetype.h"

	#include "vorbisfile.h"

#else // Android
	#include <jni.h>
	#include <errno.h>
	#include <android/sensor.h>
	#include <android/log.h>
	#include <android_native_app_glue.h>

	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

	#include "../libpng/png.h"

	#include "../zlib/zlib.h"
	#include "../zlib/unzip.h"

/*
	#include "nvtristrip/NvTriStrip.h"

	#include "bullet/btAlignedAllocator.h"
	#include "bullet/btBulletDynamicsCommon.h"
	#include "bullet/btSoftRigidDynamicsWorld.h"
	#include "bullet/btSoftBodyRigidBodyCollisionConfiguration.h"
	#include "bullet/btShapeHull.h"
	#include "bullet/btSoftBodyHelpers.h"
	#include "bullet/btSoftBody.h"
	#include "bullet/btGImpactShape.h"
	#include "bullet/btGImpactCollisionAlgorithm.h"
	#include "bullet/btBulletWorldImporter.h"

	#include "recast/Recast.h"
	#include "detour/DetourDebugDraw.h"
	#include "detour/DetourNavMesh.h"
	#include "detour/DetourNavMeshBuilder.h"

	#include "ttf/stb_truetype.h"

	#include "openal/al.h"
	#include "openal/alc.h"

	#include "vorbis/vorbisfile.h"


	extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
	extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
	extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
	*/

#endif



#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "Types.h"
#include "Log.h"

#define LOG_TAG "Engine"

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
