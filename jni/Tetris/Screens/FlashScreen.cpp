/*
 * FlashScreen.cpp
 * Copyright (C) 2012 HanoiLabs
 *
 */

#include "FlashScreen.h"
#include "../App.h"

const char *FlashScreen::TAG = "FlashScreen";

FlashScreen::FlashScreen() {
	int screenWidth = App::shared->getScreenWidth();
	int screenHeight = App::shared->getScreenHeight();
	int boxSize = screenWidth - 2;
	int boxHeight = screenHeight - 2;
	box = new Box((screenWidth - boxSize) / 2, (screenHeight - boxHeight) / 2, boxSize, boxHeight);
	int boxSize2 = 300;
//	box2 = new Box((screenWidth - boxSize2) / 2, (screenHeight - boxSize2) / 2, boxSize2, boxSize2);
}

FlashScreen::~FlashScreen() {
//	delete box2;
	delete box;
}

void FlashScreen::draw() {
	box->draw();
//	box2->draw();
}

void FlashScreen::update(void) {

}
