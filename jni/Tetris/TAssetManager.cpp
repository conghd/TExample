/*
 * TAssetManager.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "TAssetManager.h"

TAssetManager *TAssetManager::shared = NULL;
const char *TAssetManager::TAG = "TAssetManager";

void TAssetManager::sharedNew(AAssetManager *assetManager) {
	shared = new TAssetManager(assetManager);
	LOGD(TAG, "start:sharedNew()");
	char *buffer = NULL;
	int length = 0;
	shared->readFile(&buffer, &length, "glsl/simpleFragShader.fsh");
	LOGD(TAG, "CONTENT: %s", buffer);
	free(buffer);
	LOGD(TAG, "end:sharedNew()");
}

void TAssetManager::sharedDelete() {
	delete shared;
}

TAssetManager::TAssetManager(AAssetManager *assetManager) {
	this->assetManager = assetManager;
}

TAssetManager::~TAssetManager() {
	this->assetManager = NULL;
}

void TAssetManager::readFile(char **outBuffer, int *outLength, const char *filename) {
	if (filename == NULL) return;
	AAsset* assetFile = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
	if (!assetFile) {
		LOGD(TAG, "Could not open the specified file...");
		return;
	}

	*outLength = AAsset_getLength(assetFile);
	*outBuffer = (char *) malloc(sizeof(char) * (*outLength));
	int count;
	while (((count = AAsset_read(assetFile, *outBuffer, *outLength)) > 0)) {
		LOGD(TAG, "CONTENT: %s", *outBuffer);
	}
	AAsset_close(assetFile);
}
