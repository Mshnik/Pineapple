#ifndef __LOADING_SCREEN_CONTROLLER_H__
#define __LOADING_SCREEN_CONTROLLER_H__

#include <cornell.h>
#include "BackgroundView.h"
#include "Texture.h"
#include "LevelModel.h"
#include "Levels.h"

/** Font size for loading message */
#define DEFAULT_FONT_SIZE   64.0f
/** Loading font name */
#define LOADING_FONT_NAME   "felt"
/** Loading font message */
#define LOADING_MESSAGE     "Loading..."

class LoadingScreenController {
public:
	/**
	* Constructor
	*/
	LoadingScreenController() {};

	/**

	* Preloads all of the assets necessary for this game world
	*/
	void preload();
};

#endif