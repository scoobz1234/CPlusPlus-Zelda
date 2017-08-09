#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Actor.h"
#include <iostream>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern int SCREEN_WIDTH;		//TODO: currently not using...
extern int SCREEN_HEIGHT;		//TODO: currently not using...

static SDLInit sdlInit;

bool ischopped = false;

namespace {
	Player player;
	Entity tree;
	Entity tree2;
}

void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	tree2.SetTexturePath("textures/tree_green.gif");

	//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(tree2);

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(200, 300);
	tree2.SetPosition(300, 300);

	//Setting size information...
	player.SetSize(50, 50);
	tree.SetSize(64, 78);
	tree2.SetSize(64, 78);

	//Set sprite sheet texture coordinates...
	player.InitSpriteSheet(0, 14, 6);
	player.SetSpriteClip(90, 1, 30, 30, 3);			//up...
	player.SetSpriteClip(90, 31, 30, 30, 17);		//up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);			//down...
	player.SetSpriteClip(30, 31, 30, 30, 15);		//down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);		//right...
	player.SetSpriteClip(120, 31, 30, 30, 18);		//right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);			//left...
	player.SetSpriteClip(60, 31, 30, 30, 16);		//left move...

	player.SetSpriteClip(170, 141, 30, 31, 61);		//first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);		//second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);		//last left attack...

	player.SetSpriteClip(203, 142, 30, 30, 62);		//last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);		//second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);		//first right attack...

	//Set sprite sheet anchor positions...
	player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	player.SetAnchorOffset({-26, -5}, 34);			//last left attack...

	player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	//Setup collision...
	tree.ConfigureCollision(true, { 15,15 }, { 5, 10 });
	tree2.ConfigureCollision(true, { 15,15 }, { 5, 10 });
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
	sdlInit.CleanupTexture(tree2);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Move();
	player.Attack();

	(void)tree.CheckCollision(player);
	ischopped = tree2.CheckCollision(player);


	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();
	sdlInit.DrawTexture(player);
	sdlInit.DrawTexture(tree);
	if(!ischopped)
	sdlInit.DrawTexture(tree2);
	
	
}