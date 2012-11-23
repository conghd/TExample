/*
 * FlashScreen.h
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef FLASH_SCREEN_H
#define FLASH_SCREEN_H

#include "../Engine.h"
#include "../Vector.h"
#include "../Matrix.h"

class FlashScreen {
public:
	FlashScreen();
	~FlashScreen();

	void draw(void);
	void update(void);
};

#endif
