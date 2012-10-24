#ifndef _APP_H_
#define _APP_H_

#include "Engine.h"

class App {
public:
	static App *sharedApp;
	static void sharedNew();
	static void sharedDelete();
};
#endif
