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
}

FlashScreen::~FlashScreen() {
	delete box;
}

void FlashScreen::draw() {
	box->draw();
}

void FlashScreen::update(void) {

}
