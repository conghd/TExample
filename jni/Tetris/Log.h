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
	#define  LOGD(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
	#define  LOGE(tag, ...)  __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
	#define  LOGI(tag, ...)  __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
	#define  LOGW(tag, ...)  __android_log_print(ANDROID_LOG_WARN, tag, __VA_ARGS__)
#endif

#endif
