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
	Entity tree2;
	Entity house;
	Entity house2;
	Entity blocker;
	Entity blocker2;
	Entity black;
	Entity steps;
	Entity stepsHouse2;
	Entity hedgeTopLeft;
	Entity hedgeTopRight;
	Entity hedgeTopLeftSide;
	Entity hedgeTopRightSide;
	Entity hedgeBottomLeft;
	Entity hedgeBottomRight;
	Entity hedgeBottomLeftSide;
	Entity hedgeBottomRightSide;
	Entity statueBird;
	Entity news;
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

	//Setting position information...
	player.SetPosition(0, 0);
	tree.SetPosition(320, 120);
	tree2.SetPosition(536, 120);
	house.SetPosition(400, 100);
	house2.SetPosition(400, 300);
	blocker.SetPosition(401, 345);
	blocker2.SetPosition(476, 345);
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

	//Setting size information...
	player.SetSize(50, 50);
	tree.SetSize(64, 78);
	tree2.SetSize(64, 78);
	house.SetSize(120, 100);
	house2.SetSize(120,100);
	steps.SetSize(40, 30);
	stepsHouse2.SetSize(40, 30);
	blocker.SetSize(46,57);
	blocker2.SetSize(43,57);
	black.SetSize(50, 50);
	hedgeTopLeft.SetSize(65, 25);
	hedgeTopLeftSide.SetSize(20, 75);
	hedgeTopRight.SetSize(65, 25);
	hedgeTopRightSide.SetSize(20, 75);
	hedgeBottomLeft.SetSize(65, 25);
	hedgeBottomLeftSide.SetSize(20, 75);
	hedgeBottomRight.SetSize(65, 25);
	hedgeBottomRightSide.SetSize(20, 75);
	statueBird.SetSize(45, 60);
	news.SetSize(120, 120);

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
//		*** (collidable?, {ColliderX,ColliderY},{OriginX,OriginY}) ***
	tree.ConfigureCollision(true, { 15, 15 }, { 5, 10 });
	tree2.ConfigureCollision(true, { 15, 15 }, { 5, 10 });
	house.ConfigureCollision(true, { 15, 7 }, { 3, 27 });
	house2.ConfigureCollision(true, { 15, 7 }, { 3, 65 });
	steps.ConfigureCollision(false);
	blocker.ConfigureCollision(true, { 14, 7 }, { 0, 15 });
	blocker2.ConfigureCollision(true, { 10, 7 }, { 0, 15 });
	hedgeTopLeft.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeTopLeftSide.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeTopRight.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeTopRightSide.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeBottomLeft.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeBottomLeftSide.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeBottomRight.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	hedgeBottomRightSide.ConfigureCollision(true, { 14, 7 }, { 3, 15 });
	statueBird.ConfigureCollision(true, { 14, 17 }, { 3, 12 });
	news.ConfigureCollision(false);
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
	sdlInit.CleanupTexture(house);
	sdlInit.CleanupTexture(house2);
	sdlInit.CleanupTexture(blocker);
	sdlInit.CleanupTexture(blocker2);
	sdlInit.CleanupTexture(black);
	sdlInit.CleanupTexture(steps);
	sdlInit.CleanupTexture(stepsHouse2);
	sdlInit.CleanupTexture(hedgeTopLeft);
	sdlInit.CleanupTexture(hedgeTopLeftSide);
	sdlInit.CleanupTexture(hedgeTopRight);
	sdlInit.CleanupTexture(hedgeTopRightSide);
	sdlInit.CleanupTexture(hedgeBottomLeft);
	sdlInit.CleanupTexture(hedgeBottomLeftSide);
	sdlInit.CleanupTexture(hedgeBottomRight);
	sdlInit.CleanupTexture(hedgeBottomRightSide);
	sdlInit.CleanupTexture(statueBird);
	sdlInit.CleanupTexture(news);
	sdlInit.Cleanup();
}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Move();
	player.Attack();

//          *** Collision ***
	(void)tree.CheckCollision(player);
	(void)tree2.CheckCollision(player);
	(void)house.CheckCollision(player);
	(void)house2.CheckCollision(player);
	(void)blocker.CheckCollision(player);
	(void)blocker2.CheckCollision(player);
	(void)hedgeTopLeft.CheckCollision(player);
	(void)hedgeTopLeftSide.CheckCollision(player);
	(void)hedgeTopRight.CheckCollision(player);
	(void)hedgeTopRightSide.CheckCollision(player);
	(void)hedgeBottomLeft.CheckCollision(player);
	(void)hedgeBottomLeftSide.CheckCollision(player);
	(void)hedgeBottomRight.CheckCollision(player);
	(void)hedgeBottomRightSide.CheckCollision(player);
	(void)statueBird.CheckCollision(player);


	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();
//		*** Anything here will be below the player (stepped on) ect.. ***
	sdlInit.DrawTexture(steps);
	sdlInit.DrawTexture(stepsHouse2);
	sdlInit.DrawTexture(news);
	sdlInit.DrawTexture(house);
	sdlInit.DrawTexture(hedgeTopLeft);
	sdlInit.DrawTexture(hedgeTopLeftSide);
	sdlInit.DrawTexture(hedgeTopRight);
	sdlInit.DrawTexture(hedgeTopRightSide);
	sdlInit.DrawTexture(hedgeBottomLeft);
	sdlInit.DrawTexture(hedgeBottomLeftSide);
	sdlInit.DrawTexture(hedgeBottomRight);
	sdlInit.DrawTexture(hedgeBottomRightSide);
	sdlInit.DrawTexture(black);
//      *** Player drawn at this point ***
	sdlInit.DrawTexture(player);
//      *** Anything after here will appear in front of the player ***
	sdlInit.DrawTexture(statueBird);
	sdlInit.DrawTexture(tree);
	sdlInit.DrawTexture(tree2);
	sdlInit.DrawTexture(house2);
	//sdlInit.DrawTexture(blocker);
	//sdlInit.DrawTexture(blocker2);
	
	
	
}