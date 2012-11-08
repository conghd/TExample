/*
 * TAssetManager.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "TAssetManager.h"

TAssetManager *TAssetManager::shared = NULL;

void TAssetManager::sharedNew(AAssetManager *assetManager) {
	shared = new TAssetManager(assetManager);
	char *buffer = NULL;
	int length = 0;
	shared->readFile(&buffer, &length, "glsl/simpleFragShader.glsl");
	free(buffer);
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
		LOGD("Could not open the specified file...");
		return;
	}

	*outLength = AAsset_getLength(assetFile);
	*outBuffer = (char *) malloc(sizeof(char) * (*outLength));
	int count;
	while (((count = AAsset_read(assetFile, *outBuffer, *outLength)) > 0)) {
		LOGD("CONTENT: %s", *outBuffer);
	}
	AAsset_close(assetFile);
}
