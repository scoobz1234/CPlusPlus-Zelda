#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"
#include "AIHandler.h"

#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS false

//camera dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Camera gCamera(CAMERA_MODE);
World gWorld;

static SDLInit sdlInit;

namespace {
	Player player;
	Sprite tree;
	Sprite tree2;
	Sprite blocker;
	Sprite blocker2;
	Sprite blockerHouseBorder1;
	Sprite blockerHouseBorder2;
	Sprite blockerHouseBorder3;
	Sprite blockerHouseBorder4;
	Sprite blockerHouseBorder5;
	Sprite blockerHouseborder6;
	Sprite house2BlackDoor;
	Sprite buildingInsideBlackDoor;
	Sprite hedgeTopLeft;
	Sprite hedgeTopRight;
	Sprite hedgeTopLeftSide;
	Sprite hedgeTopRightSide;
	Sprite hedgeBottomLeft;
	Sprite hedgeBottomRight;
	Sprite hedgeBottomLeftSide;
	Sprite hedgeBottomRightSide;
	Sprite statueBird;
	Sprite buildingInside;
	Sprite horizLongbush;
	//houses
	Sprite redHouse1;
	Sprite redHouse2;
	Sprite blueHouse2;
	Sprite blueHouse3;
	//grounds
	Sprite ground1;
	//Hud Items
	Sprite magicMeter;
	Sprite lifeText;
	Sprite itemBox;
	Sprite hudItems;
	//AI
	AIHandler witch;
	AIHandler guyInBed;
	//triggers
	MoveTrigger houseToInside;
	MoveTrigger houseToOutside;
}

void InitEntities() {
	//***SET TEXTURE PATH***
	player.SetTexturePath("textures/link_sheet.png");
	tree.SetTexturePath("textures/tree_green.gif");
	tree2.SetTexturePath("textures/tree_green.gif");
	house2BlackDoor.SetTexturePath("textures/Door_Black.png");
	buildingInsideBlackDoor.SetTexturePath("textures/Door_Black.png");
	hedgeTopLeft.SetTexturePath("textures/Hedge_Top.png");
	hedgeTopLeftSide.SetTexturePath("textures/Hedge_Top_left.png");
	hedgeTopRight.SetTexturePath("textures/Hedge_Top.png");
	hedgeTopRightSide.SetTexturePath("textures/Hedge_Top_left.png");
	statueBird.SetTexturePath("textures/Statue_Bird.png");
	hedgeBottomLeft.SetTexturePath("textures/Hedge_Top.png");
	hedgeBottomLeftSide.SetTexturePath("textures/Hedge_Top_left.png");
	hedgeBottomRight.SetTexturePath("textures/Hedge_Top.png");
	hedgeBottomRightSide.SetTexturePath("textures/Hedge_Top_left.png");
	buildingInside.SetTexturePath("textures/inside_bld.png");
	guyInBed.SetTexturePath("textures/guyInBed.png");
	witch.SetTexturePath("textures/witch.png");
	horizLongbush.SetTexturePath("textures/horizLongBush.png");
	//houses
	redHouse1.SetTexturePath("textures/Red_Roof_House.png");
	redHouse2.SetTexturePath("textures/Skull_House.png");
	blueHouse2.SetTexturePath("textures/blueHouse2.png");
	blueHouse3.SetTexturePath("textures/blueHouse3.png");
	//grounds
	ground1.SetTexturePath("textures/ground1.png");
	//hud
	magicMeter.SetTexturePath("textures/tempMeter.png");
	lifeText.SetTexturePath("textures/lifeTextHud.png");
	itemBox.SetTexturePath("textures/itemBox.png");
	hudItems.SetTexturePath("textures/hudItems.png");

	//***LOAD TEXTURES ***
	sdlInit.LoadTexture(player);
	sdlInit.LoadTexture(tree);
	sdlInit.LoadTexture(tree2);
	sdlInit.LoadTexture(house2BlackDoor);
	sdlInit.LoadTexture(buildingInsideBlackDoor);
	sdlInit.LoadTexture(hedgeTopLeft);
	sdlInit.LoadTexture(hedgeTopLeftSide);
	sdlInit.LoadTexture(hedgeTopRight);
	sdlInit.LoadTexture(hedgeTopRightSide);
	sdlInit.LoadTexture(hedgeBottomLeft);
	sdlInit.LoadTexture(hedgeBottomLeftSide);
	sdlInit.LoadTexture(hedgeBottomRight);
	sdlInit.LoadTexture(hedgeBottomRightSide);
	sdlInit.LoadTexture(statueBird);
	sdlInit.LoadTexture(buildingInside);
	sdlInit.LoadTexture(guyInBed);
	sdlInit.LoadTexture(witch);
	sdlInit.LoadTexture(horizLongbush);
	//houses
	sdlInit.LoadTexture(redHouse1);
	sdlInit.LoadTexture(redHouse2);
	sdlInit.LoadTexture(blueHouse2);
	sdlInit.LoadTexture(blueHouse3);
	//grounds
	sdlInit.LoadTexture(ground1);
	//hud
	sdlInit.LoadTexture(magicMeter);
	sdlInit.LoadTexture(lifeText);
	sdlInit.LoadTexture(itemBox);
	sdlInit.LoadTexture(hudItems);
	
	//***SET POSITION***
	player.SetPosition({ 68,143 });
	tree.SetPosition({ 360, 20 });
	tree2.SetPosition({360, 120});
	house2BlackDoor.SetPosition({ 510,288 });
	buildingInsideBlackDoor.SetPosition({ 1510,1224 });
	hedgeTopLeft.SetPosition({ 153, 33 });
	hedgeTopLeftSide.SetPosition({ 153, 33 });
	hedgeTopRight.SetPosition({ 235, 33 });
	hedgeTopRightSide.SetPosition({ 280, 33 });
	hedgeBottomLeft.SetPosition({ 153, 180 });
	hedgeBottomLeftSide.SetPosition({ 153, 122 });
	hedgeBottomRight.SetPosition({ 235, 180 });
	hedgeBottomRightSide.SetPosition({ 280, 122 });
	statueBird.SetPosition({ 208, 72 });
	buildingInside.SetPosition({ 1210,880 });
	horizLongbush.SetPosition({0,446});
	//houses
	redHouse1.SetPosition({ 492, 35 });
	redHouse2.SetPosition({ 475, 250 });
	blueHouse2.SetPosition({ 43, 275 });
	blueHouse3.SetPosition({ 284, 258 });
	//ground
	ground1.SetPosition({0,0});
	//hud
	magicMeter.SetPosition({20,20});
	lifeText.SetPosition({500,10});
	itemBox.SetPosition({50,20});
	hudItems.SetPosition({110,10});
	//AI
	guyInBed.SetPosition({ 1392,1016 });
	witch.SetPosition({575,133});
	//Blockers (borders)...
	blocker.SetPosition({ 475, 292 });
	blocker2.SetPosition({ 546, 292 });
	blockerHouseBorder1.SetPosition({1210,880});
	blockerHouseBorder2.SetPosition({1210,1225});
	blockerHouseBorder3.SetPosition({1210,1016});
	blockerHouseBorder4.SetPosition({1668,1016});
	blockerHouseBorder5.SetPosition({1555,1225});
	blockerHouseborder6.SetPosition({1512,1300});
	//Teleports ...
	houseToInside.SetPosition({ 510,284 });
	houseToOutside.SetPosition({ 1510,1280 });

	//***SET SIZE***
	player.SetSize(45, 45);
	tree.SetSize(54, 68);
	tree2.SetSize(54, 68);
	house2BlackDoor.SetSize(50, 50);
	buildingInsideBlackDoor.SetSize(50, 50);
	hedgeTopLeft.SetSize(60, 20);
	hedgeTopLeftSide.SetSize(15, 65);
	hedgeTopRight.SetSize(60, 20);
	hedgeTopRightSide.SetSize(15, 65);
	hedgeBottomLeft.SetSize(60, 20);
	hedgeBottomLeftSide.SetSize(15, 65);
	hedgeBottomRight.SetSize(60, 20);
	hedgeBottomRightSide.SetSize(15, 65);
	statueBird.SetSize(30, 50);
	buildingInside.SetSize(640,480);
	horizLongbush.SetSize(216,23);
	//houses
	redHouse1.SetSize(120, 100);
	redHouse2.SetSize(120, 100);
	blueHouse2.SetSize(120, 100);
	blueHouse3.SetSize(120, 100);
	//grounds
	ground1.SetSize(640,480);
	//hud
	magicMeter.SetSize(26,62);
	lifeText.SetSize(64,17);
	itemBox.SetSize(32,32);
	hudItems.SetSize(100,18);
	//AI
	guyInBed.SetSize(48,60);
	witch.SetSize(25, 35);
	//Triggers...
	houseToInside.SetSize(50, 22);
	houseToOutside.SetSize(50, 20);
	//Invisible Blockers (borders)...
	blocker.SetSize(48, 56);
	blocker2.SetSize(48, 56);
	blockerHouseBorder1.SetSize(640,136);
	blockerHouseBorder2.SetSize(302,136);
	blockerHouseBorder3.SetSize(182,209);
	blockerHouseBorder4.SetSize(182,209);
	blockerHouseBorder5.SetSize(302,136);
	blockerHouseborder6.SetSize(43, 60);


	//***INIT SPRITESHEETS***
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
	//guy in bed
	guyInBed.InitSpriteSheet(0,3,1);
	guyInBed.SetSpriteClip(0, 1, 32, 40, 1);
	guyInBed.SetSpriteClip(32, 1, 32, 40, 2);
	//witch
	witch.InitSpriteSheet(0, 8, 1);
	witch.SetSpriteClip(0, 0, 24, 35, 1);
	witch.SetSpriteClip(25, 0, 24, 35, 2);
	witch.SetSpriteClip(50, 0, 24, 35, 3);
	witch.SetSpriteClip(75, 0, 24, 35, 4);
	witch.SetSpriteClip(100, 0, 24, 35, 5);
	witch.SetSpriteClip(125, 0, 24, 35, 6);
	witch.SetSpriteClip(150, 0, 24, 35, 7);
	witch.SetSpriteClip(175, 0, 24, 35, 8);
	//hud magic meter
	//magicMeter.InitSpriteSheet(0, 5, 1);
	//magicMeter.SetSpriteClip(0, 0, 16, 42, 1);
	//magicMeter.SetSpriteClip(16, 0, 16, 42, 2);
	//magicMeter.SetSpriteClip(32, 0, 16, 42, 3);
	//magicMeter.SetSpriteClip(48, 0, 16, 42, 4);
	//Set sprite sheet anchor positions...
	player.SetAnchorOffset({-16, -13}, 61);			//first left attack...
	player.SetAnchorOffset({-23, -10}, 48);			//second left attack...
	player.SetAnchorOffset({-26, -5}, 34);			//last left attack...
	player.SetAnchorOffset({4, 0}, 62);				//last right attack...
	player.SetAnchorOffset({2, -10}, 49);			//second right attack...
	player.SetAnchorOffset({-11, -13}, 35);			//first right attack...=>2

	//***COLLISION***
//		*** (canbepushed,canteleport, {ColliderX,ColliderY},{OriginX,OriginY}) ***
	player.ConfigureCollision(true,true, {5,10}, {28,15});
	tree.ConfigureCollision(true,false, {0,15}, {0,0});
	tree2.ConfigureCollision(true,false,{0, 15}, { 0,0 });
	hedgeTopLeft.ConfigureCollision(true, false);
	hedgeTopLeftSide.ConfigureCollision(true, false);
	hedgeTopRight.ConfigureCollision(true, false);
	hedgeTopRightSide.ConfigureCollision(true, false);
	hedgeBottomLeft.ConfigureCollision(true, false);
	hedgeBottomLeftSide.ConfigureCollision(true, false);
	hedgeBottomRight.ConfigureCollision(true, false);
	hedgeBottomRightSide.ConfigureCollision(true, false);
	horizLongbush.ConfigureCollision(true, false);
	statueBird.ConfigureCollision(true, false, {0,25}, {0,0});
	house2BlackDoor.ConfigureCollision(false,false, {0,0}, {0,40});
	buildingInsideBlackDoor.ConfigureCollision(false, false, { 0,40 }, { 0,0 });
	buildingInside.ConfigureCollision(true, false);
	houseToInside.ConfigureCollision(false, false);
	houseToOutside.ConfigureCollision(false, false);
	//houses
	redHouse1.ConfigureCollision(true, false, { 0,8 }, { 0,5 });
	redHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,55 });
	blueHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,5 });
	blueHouse3.ConfigureCollision(true, false, { 0,8 }, { 0,55 });
	//Blockers
	blocker.ConfigureCollision(true, false);
	blocker2.ConfigureCollision(true, false);
	blockerHouseBorder1.ConfigureCollision(true, false);
	blockerHouseBorder2.ConfigureCollision(true, false);
	blockerHouseBorder3.ConfigureCollision(true, false);
	blockerHouseBorder4.ConfigureCollision(true, false);
	blockerHouseBorder5.ConfigureCollision(true, false);
	blockerHouseborder6.ConfigureCollision(true, false);
	//AI
	guyInBed.ConfigureCollision(true, false);
	witch.ConfigureCollision(true, false);


	//***ENABLE COLLISION ***
	player.AddCollidableEntity(tree);
	player.AddCollidableEntity(tree2);
	player.AddCollidableEntity(redHouse1);
	player.AddCollidableEntity(redHouse2);
	player.AddCollidableEntity(blueHouse2);
	player.AddCollidableEntity(blueHouse3);
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
	player.AddCollidableEntity(house2BlackDoor);
	player.AddCollidableEntity(buildingInsideBlackDoor);
	player.AddCollidableEntity(houseToInside);
	player.AddCollidableEntity(houseToOutside);
	player.AddCollidableEntity(blockerHouseBorder1);
	player.AddCollidableEntity(blockerHouseBorder2);
	player.AddCollidableEntity(blockerHouseBorder3);
	player.AddCollidableEntity(blockerHouseBorder4);
	player.AddCollidableEntity(blockerHouseBorder5);
	player.AddCollidableEntity(blockerHouseborder6);
	player.AddCollidableEntity(guyInBed);
	player.AddCollidableEntity(witch);
	player.AddCollidableEntity(horizLongbush);

//INIT the world, wont work without this garble...
	gWorld.InitWorldGrid({ 0,70 - 35,14,70 - 16 });
	
//***TELEPORT LOCATIONS ***
	houseToInside.SetMovePos({1520,1214});
	houseToOutside.SetMovePos({ 523,312 });

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
	sdlInit.CleanupSprite(redHouse1);
	sdlInit.CleanupSprite(redHouse2);
	sdlInit.CleanupSprite(blueHouse2);
	sdlInit.CleanupSprite(blueHouse3);
	sdlInit.CleanupSprite(blocker);
	sdlInit.CleanupSprite(blocker2);
	sdlInit.CleanupSprite(house2BlackDoor);
	sdlInit.CleanupSprite(buildingInsideBlackDoor);
	sdlInit.CleanupSprite(hedgeTopLeft);
	sdlInit.CleanupSprite(hedgeTopLeftSide);
	sdlInit.CleanupSprite(hedgeTopRight);
	sdlInit.CleanupSprite(hedgeTopRightSide);
	sdlInit.CleanupSprite(hedgeBottomLeft);
	sdlInit.CleanupSprite(hedgeBottomLeftSide);
	sdlInit.CleanupSprite(hedgeBottomRight);
	sdlInit.CleanupSprite(hedgeBottomRightSide);
	sdlInit.CleanupSprite(statueBird);
	sdlInit.CleanupSprite(buildingInside);
	sdlInit.CleanupSprite(blockerHouseBorder1);
	sdlInit.CleanupSprite(blockerHouseBorder2);
	sdlInit.CleanupSprite(blockerHouseBorder3);
	sdlInit.CleanupSprite(blockerHouseBorder4);
	sdlInit.CleanupSprite(blockerHouseBorder5);
	sdlInit.CleanupSprite(blockerHouseborder6);
	sdlInit.CleanupSprite(guyInBed);
	sdlInit.CleanupSprite(witch);
	sdlInit.CleanupSprite(magicMeter);
	sdlInit.CleanupSprite(lifeText);
	sdlInit.CleanupSprite(itemBox);
	sdlInit.CleanupSprite(hudItems);
	sdlInit.CleanupSprite(ground1);
	sdlInit.CleanupSprite(horizLongbush);
	sdlInit.Cleanup();

}

//TODO: Add deltatime later...
void GameManager::Update() {
	player.Update();
	guyInBed.Update();
	witch.Update();

	// camera looks at the player
	gCamera.LookAt(player);
	
	sdlInit.Update();
}

void GameManager::Render(){
	sdlInit.Render();

//		*** Anything here will be below the player (stepped on) ect.. ***
	sdlInit.DrawSprite(ground1);
	sdlInit.DrawSprite(hedgeTopLeft);
	sdlInit.DrawSprite(hedgeTopLeftSide);
	sdlInit.DrawSprite(hedgeTopRight);
	sdlInit.DrawSprite(hedgeTopRightSide);
	sdlInit.DrawSprite(hedgeBottomLeftSide);
	sdlInit.DrawSprite(hedgeBottomRightSide);
	sdlInit.DrawSprite(hedgeBottomLeft);
	sdlInit.DrawSprite(hedgeBottomRight);
	sdlInit.DrawSprite(horizLongbush);
	sdlInit.DrawSprite(house2BlackDoor);
	sdlInit.DrawSprite(buildingInsideBlackDoor);
	sdlInit.DrawSprite(guyInBed);
	
//      *** Player drawn at this point ***
	sdlInit.DrawSprite(player);
//      *** Anything after here will appear in front of the player ***
	sdlInit.DrawSprite(statueBird);
	sdlInit.DrawSprite(tree);
	sdlInit.DrawSprite(tree2);
	sdlInit.DrawSprite(redHouse2);
	sdlInit.DrawSprite(redHouse1);
	sdlInit.DrawSprite(blueHouse2);
	sdlInit.DrawSprite(blueHouse3);
	sdlInit.DrawSprite(witch);
	sdlInit.DrawSprite(buildingInside);
	sdlInit.DrawHud(magicMeter);
	sdlInit.DrawHud(lifeText);
	sdlInit.DrawHud(itemBox);
	sdlInit.DrawHud(hudItems);
	

	if (SHOW_COLLIDERS) {
		sdlInit.DrawEntityCollider(redHouse1);
		sdlInit.DrawEntityCollider(hedgeTopLeft);
		sdlInit.DrawEntityCollider(hedgeTopLeftSide);
		sdlInit.DrawEntityCollider(hedgeTopRight);
		sdlInit.DrawEntityCollider(hedgeTopRightSide);
		sdlInit.DrawEntityCollider(hedgeBottomLeft);
		sdlInit.DrawEntityCollider(hedgeBottomLeftSide);
		sdlInit.DrawEntityCollider(hedgeBottomRight);
		sdlInit.DrawEntityCollider(hedgeBottomRightSide);
		sdlInit.DrawEntityCollider(house2BlackDoor);
		sdlInit.DrawEntityCollider(buildingInsideBlackDoor);
		sdlInit.DrawEntityCollider(player);
		sdlInit.DrawEntityCollider(statueBird);
		sdlInit.DrawEntityCollider(tree);
		sdlInit.DrawEntityCollider(tree2);
		sdlInit.DrawEntityCollider(redHouse2);
		sdlInit.DrawEntityCollider(blocker);
		sdlInit.DrawEntityCollider(blocker2);
		sdlInit.DrawEntityCollider(houseToInside);
		sdlInit.DrawEntityCollider(houseToOutside);
		sdlInit.DrawEntityCollider(blockerHouseBorder1);
		sdlInit.DrawEntityCollider(blockerHouseBorder2);
	    sdlInit.DrawEntityCollider(blockerHouseBorder3);
		sdlInit.DrawEntityCollider(blockerHouseBorder4);
		sdlInit.DrawEntityCollider(blockerHouseBorder5);
		sdlInit.DrawEntityCollider(blockerHouseborder6);
		sdlInit.DrawEntityCollider(guyInBed);
	}
}