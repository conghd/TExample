/*
 * Utils.h
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "Engine.h"
#include <ctype.h>

class Utils {
public:

	static unsigned int getMicroSeconds(void);
	static unsigned int getMilliSeconds(void);
	static void adjustFilePath(char *filePath);
	static void getFilePath(char *filePath, char *path);
	static void getFileName(char *filePath, char *name);
	static void getFileExtension(char *filePath, char *ext, unsigned char uppercase);
};

#endif
