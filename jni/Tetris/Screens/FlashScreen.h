/*
 * FlashScreen.h
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef FLASH_SCREEN_H
#define FLASH_SCREEN_H

#include "../Vector.h"
#include "../Matrix.h"
#include "Screen.h"
#include "../Director.h"
#include "../Objects/Box.h"

class FlashScreen : Screen {
private:
	Box *box;

public:
	static const char *TAG;
	FlashScreen();
	~FlashScreen();

	void draw(void);
	void update(void);
};

#endif
