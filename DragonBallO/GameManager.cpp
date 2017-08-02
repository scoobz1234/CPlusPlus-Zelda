#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Actor.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern int SCREEN_WIDTH;		//TODO: currently not using...
extern int SCREEN_HEIGHT;		//TODO: currently not using...

static SDLInit sdlInit;

namespace {
	Player player;
	Entity tree;
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");

	//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(200, 300);

	//Setting size information...
	player.SetSize(50, 50);
	tree.SetSize(64, 78);

	//Set sprite sheet information...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...
	player.SetSpriteClip(90, 31, 30, 30, 17);		//up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(30, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);		//right...
	player.SetSpriteClip(120, 31, 30, 30, 18);		//right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);			//left...
	player.SetSpriteClip(60, 31, 30, 30, 16);		//left move...
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupTexture(player);
	sdlInit.CleanupTexture(tree);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Move();
	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();
	sdlInit.DrawTexture(tree);
	sdlInit.DrawTexture(player);
}