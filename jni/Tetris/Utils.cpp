/*
 * Utils.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "Utils.h"

unsigned int Utils::getMicroSeconds(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

unsigned int Utils::getMilliSeconds(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec / 1000 + tv.tv_sec * 1000;
}

void Utils::adjustFilePath(char *filePath) {
	unsigned int i = 0;
	unsigned int l = strlen(filePath);
	while (i != l) {
		if (filePath[i] == '\\') filePath[i] = '/';
		++i;
	}
}

void Utils::getFilePath(char *filePath, char *path) {
	char *t = NULL;
	unsigned int p;
	adjustFilePath(filePath);
	t = strrchr(filePath, '/');
	if (t) {
		p = (t - filePath) + 1;
		strncpy(path, filePath, p);
		path[p] = 0;
	}
}

void Utils::getFileName(char *filePath, char *name) {
	char *t = NULL;
	adjustFilePath(filePath);
	t = strrchr(filePath, '/');
	if (t)
		strcpy(name, t + 1);
	else
		strcpy(name, filePath);
}

void Utils::getFileExtension(char *filePath, char *ext, unsigned char uppercase) {
	char *t = NULL;
	adjustFilePath(filePath);
	t = strrchr(filePath, '.');
	if (t) strcpy(ext, t + 1);

	if (uppercase) {
		unsigned int i = 0;
		unsigned int l = strlen(ext);
		while (i != l) {
			ext[i] = toupper(ext[i]);
			++i;
		}
	}
}
