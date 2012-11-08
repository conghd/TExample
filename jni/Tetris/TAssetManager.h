/*
 * TAssetManager.h.
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef TASSET_MANAGER_H
#define TASSET_MANAGER_H

#include "Engine.h"

class TAssetManager {
private:
	AAssetManager *assetManager;

public:

	static TAssetManager *shared;

	static void sharedNew(AAssetManager *assetManager);
	static void sharedDelete();

	TAssetManager(AAssetManager *assetManager);
	~TAssetManager();

	void readFile(char **outBuffer, int *outLength, const char *filename);
};
#endif
