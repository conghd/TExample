# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := tetris
LOCAL_CFLAGS	:= -Werror -Wno-psabi
	
#SRC_DIRS		:= $(LOCAL_PATH)/Screens
#LOCAL_SRC_FILES += $(foreach sdir, $(SRC_DIRS), $(wildcard $(sdir)/*.cpp))
#LOCAL_SRC_FILES += $(wildcard $(LOCAL_PATH)/*/*.cpp)
FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/**/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/**/**/**/*.cpp)

#LOCAL_SRC_FILES :=\
#	AssetManager.cpp \
#	App.cpp \
#	Director.cpp \
#	esUtils.cpp \
#	main.cpp \
#	Matrix.cpp \
#	Program.cpp \
#	Shader.cpp \
#	TAssetManager.cpp \
#	Utils.cpp \
#	Vector.cpp \

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
	
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := \
	android_native_app_glue \
	png \
	zip \
	zlib \

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
