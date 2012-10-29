/*
 * AssetManager.h
 * Copyright (C) 2012 HanoiLabs
 *
 */

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Engine.h"
#include <android/asset_manager.h>

class AssetManager {
public:
	void readFile(const char *name);

};

#endif
