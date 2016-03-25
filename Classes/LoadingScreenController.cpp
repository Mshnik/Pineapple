#include "LoadingScreenController.h"

#pragma mark -
#pragma mark Asset Management
// TODO: PRELOAD: Check if this is right way to do things
/**
* Preloads the assets needed for the game.
*/
void LoadingScreenController::preload() {
	// Load the textures (Autorelease objects)
	Texture2D::TexParams params;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;
	params.magFilter = GL_LINEAR;
	params.minFilter = GL_NEAREST;

	SceneManager* assets = AssetManager::getInstance()->getCurrent();
	TextureLoader* tloader = (TextureLoader*)assets->access<Texture2D>();

	tloader->loadAsync(TILE_TEXTURE, "textures/tiling.png", params);
	tloader->loadAsync(PLATFORM_TEXTURE, "textures/platform.png");
	tloader->loadAsync(PINEAPPLE_TEXTURE, "textures/will2.png");

	tloader->loadAsync(KID_TEXTURE_1, "textures/pineapplet_bow.png");
	tloader->loadAsync(KID_TEXTURE_2, "textures/pineapplet_glasses.png");
	tloader->loadAsync(KID_TEXTURE_3, "textures/pineapplet_hat.png");
	tloader->loadAsync(KID_TEXTURE_4, "textures/pineapplet_pirate.png");

	tloader->loadAsync(JELLO_TEXTURE, "textures/jello.png");
	tloader->loadAsync(SPIKE_TEXTURE, "textures/spikes.png");

	tloader->loadAsync(BLENDER_TEXTURE, "textures/blender.png");

	tloader->loadAsync(SPINNER_TEXTURE, "textures/barrier.png");
	tloader->loadAsync(GOAL_TEXTURE, "textures/goal.png");
	tloader->loadAsync(RED_CUP_TEXTURE, "textures/redcup.png");
	tloader->loadAsync(BLUE_CUP_TEXTURE, "textures/bluecup.png");
	tloader->loadAsync(GREEN_CUP_TEXTURE, "textures/greencup.png");
	tloader->loadAsync(CUPSTACK_TEXTURE, "textures/stackedcups.png");

	tloader->loadAsync(FRONT_BACKGROUND, "textures/background.png");
	tloader->loadAsync(MIDDLE_BACKGROUND, "textures/hills.png");
	tloader->loadAsync(BACK_BACKGROUND, "textures/clouds.png");

	//    _assets->loadAsync<Sound>(GAME_MUSIC,   "sounds/DD_Main.mp3");
	//    _assets->loadAsync<Sound>(WIN_MUSIC,    "sounds/DD_Victory.mp3");
	//    _assets->loadAsync<Sound>(LOSE_MUSIC,   "sounds/DD_Failure.mp3");
	//    _assets->loadAsync<Sound>(JUMP_EFFECT,  "sounds/jump.mp3");
	//    _assets->loadAsync<Sound>(PEW_EFFECT,   "sounds/pew.mp3");
	//    _assets->loadAsync<Sound>(POP_EFFECT,   "sounds/plop.mp3");
	assets->loadAsync<TTFont>(MESSAGE_FONT, "fonts/RetroGame.ttf");

}