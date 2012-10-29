/*
 * Log.h
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <android/log.h>

#ifdef __IPHONE_4_0
	#define  LOGD(...)  printf(__VA_ARGS__)
	#define  LOGE(...)  printf(__VA_ARGS__)
	#define  LOGI(...)  printf(__VA_ARGS__)
	#define  LOGW(...)  printf(__VA_ARGS__)
#else
	#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
	#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
	#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
	#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#endif

#endif
