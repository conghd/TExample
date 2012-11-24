/*
 * Screen.h
 * Copyright (c) 2012 HanoiLabs
 *
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <Engine.h>
#include <Director.h>
#include <Program.h>

class Screen {
public:
	virtual void draw(void);
	virtual void update(void);
};

#endif
