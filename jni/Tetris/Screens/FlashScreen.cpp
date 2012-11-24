/*
 * FlashScreen.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "FlashScreen.h"

const char *FlashScreen::TAG = "FlashScreen";

FlashScreen::FlashScreen() {
	int screenWidth = 720;
	int screenHeight = 1280;
	int boxSize = 600;
	box = new Box((screenWidth - boxSize) / 2, (screenHeight - boxSize) / 2, boxSize, boxSize);
	int boxSize2 = 300;
	box2 = new Box((screenWidth - boxSize2) / 2, (screenHeight - boxSize2) / 2, boxSize2, boxSize2);
}

FlashScreen::~FlashScreen() {
	delete box2;
	delete box;
}

void FlashScreen::draw() {
	box->draw();
	box2->draw();
}

void FlashScreen::update(void) {

}
