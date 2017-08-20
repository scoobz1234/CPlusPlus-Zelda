#include "GameManager.h"
#include "SDLInit.h"
#include "Player.h"
#include "Camera.h"
#include "Entity.h"
#include <iostream>

#define PAN_CAMERA_INSTEAD false
#define SHOW_COLLIDERS true

//camera dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int WORLD_WIDTH = 2400;
const int WORLD_HEIGHT = 2400;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;


Camera gCamera;

static SDLInit sdlInit;

namespace {
	Camera camera;
	Player player;
	Sprite tree;
	Sprite tree2;
	Sprite house;
	Sprite house2;
	Sprite blocker;
	Sprite blocker2;
	Sprite black;
	Sprite steps;
	Sprite stepsHouse2;
	Sprite hedgeTopLeft;
	Sprite hedgeTopRight;
	Sprite hedgeTopLeftSide;
	Sprite hedgeTopRightSide;
	Sprite hedgeBottomLeft;
	Sprite hedgeBottomRight;
	Sprite hedgeBottomLeftSide;
	Sprite hedgeBottomRightSide;
	Sprite statueBird;
	Sprite news;
	Sprite buildingInside;


}


void InitEntities() {
	//Setting path names...
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	tree2.SetTexturePath("textures/tree_green.gif");
	house.SetTexturePath("textures/Red_Roof_House.png");
	house2.SetTexturePath("textures/Skull_House.png");
	steps.SetTexturePath("textures/Door_Steps.png");
	stepsHouse2.SetTexturePath("textures/Door_Steps.png");
	blocker.SetTexturePath("textures/Hedge_Top_Left.png");
	blocker2.SetTexturePath("textures/Hedge_Top_Left.png");
	black.SetTexturePath("textures/Door_Black.png");
	hedgeTopLeft.SetTexturePath("textures/Hedge_Top.png");
	hedgeTopLeftSide.SetTexturePath("textures/Hedge_Top_left.png");
	hedgeTopRight.SetTexturePath("textures/Hedge_Top.png");
	hedgeTopRightSide.SetTexturePath("textures/Hedge_Top_left.png");
	statueBird.SetTexturePath("textures/Statue_Bird.png");
	hedgeBottomLeft.SetTexturePath("textures/Hedge_Top.png");
	hedgeBottomLeftSide.SetTexturePath("textures/Hedge_Top_left.png");
	hedgeBottomRight.SetTexturePath("textures/Hedge_Top.png");
	hedgeBottomRightSide.SetTexturePath("textures/Hedge_Top_left.png");
	news.SetTexturePath("textures/NEWS.png");
	buildingInside.SetTexturePath("textures/inside_bld.png");

		//Loading textures...
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(tree2);
	sdlInit.LoadTexture(house);
	sdlInit.LoadTexture(house2);
	sdlInit.LoadTexture(steps);
	sdlInit.LoadTexture(stepsHouse2);
	sdlInit.LoadTexture(blocker);
	sdlInit.LoadTexture(blocker2);
	sdlInit.LoadTexture(black);
	sdlInit.LoadTexture(hedgeTopLeft);
	sdlInit.LoadTexture(hedgeTopLeftSide);
	sdlInit.LoadTexture(hedgeTopRight);
	sdlInit.LoadTexture(hedgeTopRightSide);
	sdlInit.LoadTexture(hedgeBottomLeft);
	sdlInit.LoadTexture(hedgeBottomLeftSide);
	sdlInit.LoadTexture(hedgeBottomRight);
	sdlInit.LoadTexture(hedgeBottomRightSide);
	sdlInit.LoadTexture(statueBird);
	sdlInit.LoadTexture(news);
	sdlInit.LoadTexture(buildingInside);

	//Setting position information...
	player.SetPosition(500,400);
	tree.SetPosition(318, 120);
	tree2.SetPosition(538, 120);
	house.SetPosition(400, 100);
	house2.SetPosition(400, 300);
	blocker.SetPosition(401, 345);
	blocker2.SetPosition(470, 345);
	black.SetPosition(430,338);
	steps.SetPosition(440, 200);
	stepsHouse2.SetPosition(440,391);
	hedgeTopLeft.SetPosition(60, 50);
	hedgeTopLeftSide.SetPosition(41, 50);
	hedgeTopRight.SetPosition(170, 50);
	hedgeTopRightSide.SetPosition(234, 50);
	hedgeBottomLeft.SetPosition(60, 215);
	hedgeBottomLeftSide.SetPosition(41, 165);
	hedgeBottomRight.SetPosition(170, 215);
	hedgeBottomRightSide.SetPosition(234, 165);
	statueBird.SetPosition(125, 105);
	news.SetPosition(86, 86);
	buildingInside.SetPosition(1241,900);

	//Setting size information...
	player.SetSpriteSize(50, 50);
	tree.SetSpriteSize(64, 78);
	tree2.SetSpriteSize(64, 78);
	house.SetSpriteSize(120, 100);
	house2.SetSpriteSize(120,100);
	steps.SetSpriteSize(40, 30);
	stepsHouse2.SetSpriteSize(40, 30);
	blocker.SetSpriteSize(47,56);
	blocker2.SetSpriteSize(50,56);
	black.SetSpriteSize(50, 50);
	hedgeTopLeft.SetSpriteSize(65, 25);
	hedgeTopLeftSide.SetSpriteSize(20, 75);
	hedgeTopRight.SetSpriteSize(65, 25);
	hedgeTopRightSide.SetSpriteSize(20, 75);
	hedgeBottomLeft.SetSpriteSize(65, 25);
	hedgeBottomLeftSide.SetSpriteSize(20, 75);
	hedgeBottomRight.SetSpriteSize(65, 25);
	hedgeBottomRightSide.SetSpriteSize(20, 75);
	statueBird.SetSpriteSize(45, 60);
	news.SetSpriteSize(120, 120);
	buildingInside.SetSpriteSize(640,480);

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
//		*** (canbepushed,canteleport, {ColliderX,ColliderY},{OriginX,OriginY}) ***
	player.ConfigureCollision(true,false, {5,10}, {28,15});
	tree.ConfigureCollision(false,false, {0,15}, {0,0});
	tree2.ConfigureCollision(false,false);
	house.ConfigureCollision(false, false, {0,8}, {0,0});
	house2.ConfigureCollision(false, false, {0,8}, {0,55});
	steps.ConfigureCollision(false, false);
	blocker.ConfigureCollision(false, false);
	blocker2.ConfigureCollision(false, false);
	hedgeTopLeft.ConfigureCollision(false, false);
	hedgeTopLeftSide.ConfigureCollision(false, false);
	hedgeTopRight.ConfigureCollision(false, false);
	hedgeTopRightSide.ConfigureCollision(false, false);
	hedgeBottomLeft.ConfigureCollision(false, false);
	hedgeBottomLeftSide.ConfigureCollision(false, false);
	hedgeBottomRight.ConfigureCollision(false, false);
	hedgeBottomRightSide.ConfigureCollision(false, false);
	statueBird.ConfigureCollision(false, false, {0,25}, {0,0});
	news.ConfigureCollision(false, false);
	black.ConfigureCollision(false,true, {0,0}, {0,40});
	buildingInside.ConfigureCollision(false, false);



	//checks collision?
	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(tree2);
	player.AddCollidableEntity(house);
	player.AddCollidableEntity(house2);
	player.AddCollidableEntity(blocker);
	player.AddCollidableEntity(blocker2);
	player.AddCollidableEntity(hedgeTopLeft);
	player.AddCollidableEntity(hedgeTopLeftSide);
	player.AddCollidableEntity(hedgeBottomLeft);
	player.AddCollidableEntity(hedgeBottomLeftSide);
	player.AddCollidableEntity(hedgeBottomRight);
	player.AddCollidableEntity(hedgeBottomRightSide);
	player.AddCollidableEntity(hedgeTopRight);
	player.AddCollidableEntity(hedgeTopRightSide);
	player.AddCollidableEntity(statueBird);
	player.AddCollidableEntity(black);
	player.AddCollidableEntity(buildingInside);
	
}

bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) {
		InitEntities();
	}

	return initSuccess;
}

void GameManager::Cleanup(){
	sdlInit.CleanupSprite(player);
	sdlInit.CleanupSprite(tree);
	sdlInit.CleanupSprite(tree2);
	sdlInit.CleanupSprite(house);
	sdlInit.CleanupSprite(house2);
	sdlInit.CleanupSprite(blocker);
	sdlInit.CleanupSprite(blocker2);
	sdlInit.CleanupSprite(black);
	sdlInit.CleanupSprite(steps);
	sdlInit.CleanupSprite(stepsHouse2);
	sdlInit.CleanupSprite(hedgeTopLeft);
	sdlInit.CleanupSprite(hedgeTopLeftSide);
	sdlInit.CleanupSprite(hedgeTopRight);
	sdlInit.CleanupSprite(hedgeTopRightSide);
	sdlInit.CleanupSprite(hedgeBottomLeft);
	sdlInit.CleanupSprite(hedgeBottomLeftSide);
	sdlInit.CleanupSprite(hedgeBottomRight);
	sdlInit.CleanupSprite(hedgeBottomRightSide);
	sdlInit.CleanupSprite(statueBird);
	sdlInit.CleanupSprite(news);
	sdlInit.CleanupSprite(buildingInside);
	sdlInit.Cleanup();

}

//TODO: Add deltatime later...
void GameManager::Update() {
	tree.Update();
	tree2.Update();
	house.Update();
	house2.Update();
	blocker.Update();
	blocker2.Update();
	hedgeTopLeft.Update();
	hedgeTopLeftSide.Update();
	hedgeTopRight.Update();
	hedgeTopRightSide.Update();
	hedgeBottomLeft.Update();
	hedgeBottomLeftSide.Update();
	hedgeBottomRight.Update();
	hedgeBottomRightSide.Update();
	statueBird.Update();
	buildingInside.Update();
	player.Update();


	if (PAN_CAMERA_INSTEAD) {
		gCamera.PanWith(player);
	}
	else {
		gCamera.LookAt(player);
	}

	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

//		*** Anything here will be below the player (stepped on) ect.. ***
	//sdlInit.DrawSprite(gridGuide);
	sdlInit.DrawSprite(steps);
	sdlInit.DrawSprite(stepsHouse2);
	sdlInit.DrawSprite(news);
	sdlInit.DrawSprite(hedgeTopLeft);
	sdlInit.DrawSprite(hedgeTopLeftSide);
	sdlInit.DrawSprite(hedgeTopRight);
	sdlInit.DrawSprite(hedgeTopRightSide);
	sdlInit.DrawSprite(hedgeBottomLeft);
	sdlInit.DrawSprite(hedgeBottomLeftSide);
	sdlInit.DrawSprite(hedgeBottomRight);
	sdlInit.DrawSprite(hedgeBottomRightSide);
	sdlInit.DrawSprite(black);
	sdlInit.DrawSprite(buildingInside);
//      *** Player drawn at this point ***
	sdlInit.DrawSprite(player);

//      *** Anything after here will appear in front of the player ***
	sdlInit.DrawSprite(statueBird);
	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(tree2);
	sdlInit.DrawSprite(house2);
	sdlInit.DrawSprite(house);
	

	if (SHOW_COLLIDERS) {
		//sdlInit.DrawSprite(gridGuide);
		sdlInit.DrawEntityCollider(steps);
		sdlInit.DrawEntityCollider(stepsHouse2);
		sdlInit.DrawEntityCollider(news);
		sdlInit.DrawEntityCollider(house);
		sdlInit.DrawEntityCollider(hedgeTopLeft);
		sdlInit.DrawEntityCollider(hedgeTopLeftSide);
		sdlInit.DrawEntityCollider(hedgeTopRight);
		sdlInit.DrawEntityCollider(hedgeTopRightSide);
		sdlInit.DrawEntityCollider(hedgeBottomLeft);
		sdlInit.DrawEntityCollider(hedgeBottomLeftSide);
		sdlInit.DrawEntityCollider(hedgeBottomRight);
		sdlInit.DrawEntityCollider(hedgeBottomRightSide);
		sdlInit.DrawEntityCollider(black);
		sdlInit.DrawEntityCollider(player);
		sdlInit.DrawEntityCollider(statueBird);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(tree2);
		sdlInit.DrawEntityCollider(house2);
		sdlInit.DrawEntityCollider(blocker);
		sdlInit.DrawEntityCollider(blocker2);
	}
}