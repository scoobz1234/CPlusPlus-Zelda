/*************************************************				INCLUDES			**************************************************/
#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "MoveTrigger.h"
#include "AISprite.h"
#include "Weather.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "WeatherStates.h"
#include <chrono>
#include <thread>
/*************************************************			FLAG and ECT			**************************************************/
#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS false

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//camera dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Window Definitions
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Camera and World
Camera gCamera(CAMERA_MODE);
World gWorld;

//Music and sound
extern void PlaySFX(Mix_Chunk *sfxName);
extern void PlayBGMusic(Mix_Music *bgmName);
extern void StopBGMusic();
extern Mix_Music *selectScreen;
extern Mix_Music *BGMusic1;
extern Mix_Chunk *SFX2;
extern Mix_Chunk *SFX3;
extern Mix_Chunk *SFX4;

//keypresses inventory
extern bool gIKeyDown;						//bool so we can check if the I key is pressed
extern bool gIKeyUp;
bool invOpen{ false };						//another inventory bool so we can toggle stuff

//weather stuff...
extern bool inside;							//checks if player is "inside" so we can toggle weather

//for start menu...
extern bool gEKeyDown;

bool playingMusic = false;

static SDLInit sdlInit;

//GameManager::LoadedScene ls = GameManager::LoadedScene::LIGHTWORLD;
GameManager::LoadedScene ls = GameManager::LoadedScene::SPLASH;
namespace {
	Player player;															//Player
	Sprite tree;															//Sprite
	Sprite tree2;															//Sprite
	Sprite blocker;															//Invisible Blockade Sprite
	Sprite blocker2;														//Invisible Blockade Sprite
	Sprite blockerHouseBorder1;												//Invisible Blockade Sprite
	Sprite blockerHouseBorder2;												//Invisible Blockade Sprite
	Sprite blockerHouseBorder3;												//Invisible Blockade Sprite
	Sprite blockerHouseBorder4;												//Invisible Blockade Sprite
	Sprite blockerHouseBorder5;												//Invisible Blockade Sprite
	Sprite blockerHouseBorder6;												//Invisible Blockade Sprite
	Sprite house2BlackDoor;													//Sprite
	Sprite bldgInsideBlkDoor;												//Sprite
	Sprite hedgeTopLeft;													//Sprite
	Sprite hedgeTopRight;													//Sprite
	Sprite hedgeTopLeftSide;												//Sprite
	Sprite hedgeTopRightSide;												//Sprite
	Sprite hedgeBottomLeft;													//Sprite
	Sprite hedgeBottomRight;												//Sprite
	Sprite hedgeBottomLeftSide;												//Sprite
	Sprite hedgeBottomRightSide;											//Sprite
	Sprite statueBird;														//Sprite
	Sprite buildingInside;													//Sprite
	Sprite horizLongbush;													//Sprite
	Sprite redHouse1;														//House Sprite
	Sprite redHouse2;														//House Sprite
	Sprite blueHouse2;														//House Sprite
	Sprite blueHouse3;														//House Sprite
	Sprite ground1;															//Ground Sprite
	Sprite magicMeter;														//HUD Sprite
	Sprite lifeText;														//HUD Sprite
	Sprite itemBox;															//HUD Sprite
	Sprite hudItems;														//HUD Sprite
	Sprite inventory;														//HUD Sprite
	AISprite witch;															//AI Sprite
	AISprite guyInBed;														//AI Sprite
	AISprite sawGuys;														//AI Sprite
	MoveTrigger houseToInside;												//Trigger Sprite
	MoveTrigger houseToOutside;												//Trigger Sprite
	WeatherStates weatherSystem;											//Weather System
	
	//SPLASH
	AISprite splashBackground;
	AISprite startText;
	Sprite menuBackground;
	
	//SWAP INDICES FOR ANIMATIONS
	int witchSwapIndices[] = { 0,1,2,3,4,5,6,7};
	int guyInBedIndices[] = {0,1};
	int sawGuysIndices[] = {0,1,2};
	int splashBackgroundIndices[] = {0,0,0,0,0,1,2,3,4,5,6,7,7,7,7,7,7,7};
	int startTextIndices[] = { 0,1 };

}

void InitEntities() {
	//CLASS PLAYER
	player.SetTexturePath("textures/link_sheet.png");						//Player Texture Path
	sdlInit.LoadTexture(player);											//Player Texture Load
	player.SetPosition({ 68,143 });											//Sprite Position
	player.SetSize(45, 45);													//player Size
	player.InitSpriteSheet(0, 14, 6);										//Player Initialize SpriteSheet
	player.SetSpriteClip(90, 1, 30, 30, 3);									//Player Set Sprite Clips			up...
	player.SetSpriteClip(90, 31, 30, 30, 17);								//Player Set Sprite Clips			up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);									//Player Set Sprite Clips			down...
	player.SetSpriteClip(30, 31, 30, 30, 15);								//Player Set Sprite Clips			down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);								//Player Set Sprite Clips			right...
	player.SetSpriteClip(120, 31, 30, 30, 18);								//Player Set Sprite Clips			right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);									//Player Set Sprite Clips			left...
	player.SetSpriteClip(60, 31, 30, 30, 16);								//Player Set Sprite Clips			left move...
	player.SetSpriteClip(170, 141, 30, 31, 61);								//Player Set Sprite Clips			first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);								//Player Set Sprite Clips			second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);								//Player Set Sprite Clips			last left attack...
	player.SetSpriteClip(203, 142, 30, 30, 62);								//Player Set Sprite Clips			last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);								//Player Set Sprite Clips			second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);								//Player Set Sprite Clips			first right attack...
	player.SetAnchorOffset({ -16, -13 }, 61);								//Player Set Sprite Clips			first left attack...
	player.SetAnchorOffset({ -23, -10 }, 48);								//Player Set Sprite Clips			second left attack...
	player.SetAnchorOffset({ -26, -5 }, 34);								//Player Set Sprite Clips			last left attack...
	player.SetAnchorOffset({ 4, 0 }, 62);									//Player Set Sprite Clips			last right attack...
	player.SetAnchorOffset({ 2, -10 }, 49);									//Player Set Sprite Clips			second right attack...
	player.SetAnchorOffset({ -11, -13 }, 35);								//Player Set Sprite Clips			first right attack...=>2
	player.ConfigureCollision(true, true, { 5,10 }, { 28,15 });				//Player Collision
	player.AddCollidableEntity(tree);										//Player/Sprite Collision
	player.AddCollidableEntity(tree2);										//Player/Sprite Collision
	player.AddCollidableEntity(redHouse1);									//Player/Sprite Collision
	player.AddCollidableEntity(redHouse2);									//Player/Sprite Collision
	player.AddCollidableEntity(blueHouse2);									//Player/Sprite Collision
	player.AddCollidableEntity(blueHouse3);									//Player/Sprite Collision
	player.AddCollidableEntity(blocker);									//Player/Sprite Collision
	player.AddCollidableEntity(blocker2);									//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopLeft);								//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopLeftSide);							//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomLeft);							//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomLeftSide);						//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomRight);							//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomRightSide);						//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopRight);								//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopRightSide);							//Player/Sprite Collision
	player.AddCollidableEntity(statueBird);									//Player/Sprite Collision
	player.AddCollidableEntity(house2BlackDoor);							//Player/Sprite Collision
	player.AddCollidableEntity(bldgInsideBlkDoor);							//Player/Sprite Collision
	player.AddCollidableEntity(houseToInside);								//Player/Sprite Collision
	player.AddCollidableEntity(houseToOutside);								//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder1);						//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder2);						//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder3);						//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder4);						//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder5);						//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder6);						//Player/Sprite Collision
	player.AddCollidableEntity(guyInBed);									//Player/Sprite Collision
	player.AddCollidableEntity(witch);										//Player/Sprite Collision
	player.AddCollidableEntity(sawGuys);									//Player/Sprite Collision
	player.AddCollidableEntity(horizLongbush);								//Player/Sprite Collision

	//SPRITE TREE
	tree.SetTexturePath("textures/tree_green.gif");							//Sprite Texture Path
	sdlInit.LoadTexture(tree);												//Sprite Texture Load
	tree.SetPosition({ 360, 20 });											//Sprite Position
	tree.SetSize(54, 68);													//sprite Size
	tree.ConfigureCollision(true, false, { 0,15 }, { 0,0 });				//Sprite Collision

	//SPRITE TREE2
	tree2.SetTexturePath("textures/tree_green.gif");						//Sprite Texture Path
	sdlInit.LoadTexture(tree2);												//Sprite Texture Load
	tree2.SetPosition({ 360, 120 });										//Sprite Position
	tree2.SetSize(54, 68);													//sprite Size
	tree2.ConfigureCollision(true, false, { 0, 15 }, { 0,0 });				//Sprite Collision

	//SPRITE BLOCKER
	blocker.SetPosition({ 475, 292 });										//Invisible Blockade Position
	blocker.SetSize(48, 56);												//invisible blockade Size
	blocker.ConfigureCollision(true, false);								//Invisible Blockade Collision

	//SPRITE BLOCKER2
	blocker2.SetPosition({ 546, 292 });										//Invisible Blockade Position
	blocker2.SetSize(48, 56);												//invisible blockade Size
	blocker2.ConfigureCollision(true, false);								//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 1
	blockerHouseBorder1.SetPosition({ 1210,880 });							//Invisible Blockade Position
	blockerHouseBorder1.SetSize(640, 136);									//invisible blockade Size
	blockerHouseBorder1.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 2
	blockerHouseBorder2.SetPosition({ 1210,1225 });							//Invisible Blockade Position
	blockerHouseBorder2.SetSize(302, 136);									//invisible blockade Size
	blockerHouseBorder2.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 3
	blockerHouseBorder3.SetPosition({ 1210,1016 });							//Invisible Blockade Position
	blockerHouseBorder3.SetSize(182, 209);									//invisible blockade Size
	blockerHouseBorder3.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 4
	blockerHouseBorder4.SetPosition({ 1668,1016 });							//Invisible Blockade Position
	blockerHouseBorder4.SetSize(182, 209);									//invisible blockade Size
	blockerHouseBorder4.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 5
	blockerHouseBorder5.SetPosition({ 1555,1225 });							//Invisible Blockade Position
	blockerHouseBorder5.SetSize(302, 136);									//invisible blockade Size
	blockerHouseBorder5.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE BLOCKER HOUSE BORDER 6
	blockerHouseBorder6.SetPosition({ 1512,1300 });							//Invisible Blockade Position
	blockerHouseBorder6.SetSize(43, 60);									//invisible blockade Size
	blockerHouseBorder6.ConfigureCollision(true, false);					//Invisible Blockade Collision

	//SPRITE HOUSE 2 BLACK DOOR
	house2BlackDoor.SetTexturePath("textures/Door_Black.png");				//Sprite Texture Path
	sdlInit.LoadTexture(house2BlackDoor);									//Sprite Texture Load
	house2BlackDoor.SetPosition({ 510,288 });								//Sprite Position
	house2BlackDoor.SetSize(50, 50);										//sprite Size
	house2BlackDoor.ConfigureCollision(false, false, { 0,0 }, { 0,40 });	//Sprite Collision

	//SPRITE BUILDING INSIDE BLACK DOOR
	bldgInsideBlkDoor.SetTexturePath("textures/Door_Black.png");			//Sprite Texture Path
	sdlInit.LoadTexture(bldgInsideBlkDoor);									//Sprite Texture Load
	bldgInsideBlkDoor.SetPosition({ 1510,1224 });							//Sprite Position
	bldgInsideBlkDoor.SetSize(50, 50);										//sprite Size
	bldgInsideBlkDoor.ConfigureCollision(false, false, { 0,40 }, { 0,0 });	//Sprite Collision

	//SPRITE HEDGE TOP LEFT
	hedgeTopLeft.SetTexturePath("textures/Hedge_Top.png");					//Sprite Texture Path
	sdlInit.LoadTexture(hedgeTopLeft);										//Sprite Texture Load
	hedgeTopLeft.SetPosition({ 153, 33 });									//Sprite Position
	hedgeTopLeft.SetSize(60, 20);											//sprite Size
	hedgeTopLeft.ConfigureCollision(true, false);							//Sprite Collision

	//SPRITE HEDGE TOP RIGHT
	hedgeTopRight.SetTexturePath("textures/Hedge_Top.png");					//Sprite Texture Path
	sdlInit.LoadTexture(hedgeTopRight);										//Sprite Texture Load
	hedgeTopRight.SetPosition({ 235, 33 });									//Sprite Position
	hedgeTopRight.SetSize(60, 20);											//sprite Size
	hedgeTopRight.ConfigureCollision(true, false);							//Sprite Collision

	//SPRITE HEDGE TOP LEFT SIDE
	hedgeTopLeftSide.SetTexturePath("textures/Hedge_Top_left.png");			//Sprite Texture Path
	sdlInit.LoadTexture(hedgeTopLeftSide);									//Sprite Texture Load
	hedgeTopLeftSide.SetPosition({ 153, 33 });								//Sprite Position
	hedgeTopLeftSide.SetSize(15, 65);										//sprite Size
	hedgeTopLeftSide.ConfigureCollision(true, false);						//Sprite Collision

	//SPRITE HEDGE TOP RIGHT SIDE
	hedgeTopRightSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	sdlInit.LoadTexture(hedgeTopRightSide);									//Sprite Texture Load
	hedgeTopRightSide.SetPosition({ 280, 33 });								//Sprite Position
	hedgeTopRightSide.SetSize(15, 65);										//sprite Size
	hedgeTopRightSide.ConfigureCollision(true, false);						//Sprite Collision

	//SPRITE HEDGE BOTTOM LEFT
	hedgeBottomLeft.SetTexturePath("textures/Hedge_Top.png");				//Sprite Texture Path
	sdlInit.LoadTexture(hedgeBottomLeft);									//Sprite Texture Load
	hedgeBottomLeft.SetPosition({ 153, 180 });								//Sprite Position
	hedgeBottomLeft.SetSize(60, 20);										//sprite Size
	hedgeBottomLeft.ConfigureCollision(true, false);						//Sprite Collision

	//SPRITE HEDGE BOTTOM RIGHT
	hedgeBottomRight.SetTexturePath("textures/Hedge_Top.png");				//Sprite Texture Path
	sdlInit.LoadTexture(hedgeBottomRight);									//Sprite Texture Load
	hedgeBottomRight.SetPosition({ 235, 180 });								//Sprite Position
	hedgeBottomRight.SetSize(60, 20);										//sprite Size
	hedgeBottomRight.ConfigureCollision(true, false);						//Sprite Collision

	//SPRITE HEDGE BOTTOM LEFT SIDE
	hedgeBottomLeftSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	sdlInit.LoadTexture(hedgeBottomLeftSide);								//Sprite Texture Load
	hedgeBottomLeftSide.SetPosition({ 153, 122 });							//Sprite Position
	hedgeBottomLeftSide.SetSize(15, 65);									//sprite Size
	hedgeBottomLeftSide.ConfigureCollision(true, false);					//Sprite Collision

	//SPRITE HEDGE BOTTOM RIGHT SIDE
	hedgeBottomRightSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	sdlInit.LoadTexture(hedgeBottomRightSide);								//Sprite Texture Load
	hedgeBottomRightSide.SetPosition({ 280, 122 });							//Sprite Position
	hedgeBottomRightSide.SetSize(15, 65);									//sprite Size
	hedgeBottomRightSide.ConfigureCollision(true, false);					//Sprite Collision

	//SPRITE STATUE BIRD
	statueBird.SetTexturePath("textures/Statue_Bird.png");					//Sprite Texture Path
	sdlInit.LoadTexture(statueBird);										//Sprite Texture Load
	statueBird.SetPosition({ 208, 72 });									//Sprite Position
	statueBird.SetSize(30, 50);												//sprite Size
	statueBird.ConfigureCollision(true, false, { 0,25 }, { 0,0 });			//Sprite Collision

	//SPRITE BUILDING INSIDE
	buildingInside.SetTexturePath("textures/inside_bld.png");				//Sprite Texture Path
	sdlInit.LoadTexture(buildingInside);									//Sprite Texture Load
	buildingInside.SetPosition({ 1210,880 });								//Sprite Position
	buildingInside.SetSize(640, 480);										//sprite Size
	buildingInside.ConfigureCollision(true, false);							//Sprite Collision

	//SPRITE HORIZONTAL LONG BUSH
	horizLongbush.SetTexturePath("textures/horizLongBush.png");				//Sprite Texture Path
	sdlInit.LoadTexture(horizLongbush);										//Sprite Texture Load
	horizLongbush.SetPosition({ 0,446 });									//Sprite Position
	horizLongbush.SetSize(216, 23);											//sprite Size
	horizLongbush.ConfigureCollision(true, false);							//Sprite Collision

	//SPRITE RED HOUSE 1
	redHouse1.SetTexturePath("textures/Red_Roof_House.png");				//House Texture Path
	sdlInit.LoadTexture(redHouse1);											//House Texture Load
	redHouse1.SetPosition({ 492, 35 });										//House Position
	redHouse1.SetSize(120, 100);											//house sprite Size
	redHouse1.ConfigureCollision(true, false, { 0,8 }, { 0,5 });			//House Collision

	//SPRITE RED HOUSE 2
	redHouse2.SetTexturePath("textures/Skull_House.png");					//House Texture Path
	sdlInit.LoadTexture(redHouse2);											//House Texture Load
	redHouse2.SetPosition({ 475, 250 });									//House Position
	redHouse2.SetSize(120, 100);											//house sprite Size
	redHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,55 });			//House Collision

	//SPRITE BLUE HOUSE 2
	blueHouse2.SetTexturePath("textures/blueHouse2.png");					//House Texture Path
	sdlInit.LoadTexture(blueHouse2);										//House Texture Load
	blueHouse2.SetPosition({ 43, 275 });									//House Position
	blueHouse2.SetSize(120, 100);											//house sprite Size
	blueHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,5 });			//House Collision

	//SPRITE BLUE HOUSE 3
	blueHouse3.SetTexturePath("textures/blueHouse3.png");					//House Texture Path
	sdlInit.LoadTexture(blueHouse3);										//House Texture Load
	blueHouse3.SetPosition({ 284, 258 });									//House Position
	blueHouse3.SetSize(120, 100);											//house sprite Size
	blueHouse3.ConfigureCollision(true, false, { 0,8 }, { 0,5 });			//House Collision

	//SPRITE GROUND 1
	ground1.SetTexturePath("textures/ground1.png");							//Ground Texture Path
	sdlInit.LoadTexture(ground1);											//Ground Texture Load
	ground1.SetPosition({ 0,0 });											//Ground Position
	ground1.SetSize(640, 480);												//ground texture Size

	//SPRITE MAGIC METER
	magicMeter.SetTexturePath("textures/tempMeter.png");					//Hud Texture Path
	sdlInit.LoadTexture(magicMeter);										//Hud Texture Load
	magicMeter.SetPosition({ 20,20 });										//Hud Position
	magicMeter.SetSize(26, 62);												//hud Size

	//SPRITE LIFE TEXT
	lifeText.SetTexturePath("textures/lifeTextHud.png");					//Hud Texture Path
	sdlInit.LoadTexture(lifeText);											//Hud Texture Load
	lifeText.SetPosition({ 500,10 });										//Hud Position
	lifeText.SetSize(64, 17);												//hud Size

	//SPRITE ITEM BOX
	itemBox.SetTexturePath("textures/itemBox.png");							//Hud Texture Path
	sdlInit.LoadTexture(itemBox);											//Hud Texture Load
	itemBox.SetPosition({ 50,20 });											//Hud Position
	itemBox.SetSize(32, 32);												//hud Size

	//SPRITE HUD ITEMS
	hudItems.SetTexturePath("textures/hudItems.png");						//Hud Texture Path
	sdlInit.LoadTexture(hudItems);											//Hud Texture Load
	hudItems.SetPosition({ 110,10 });										//Hud Position
	hudItems.SetSize(100, 18);												//hud Size

	//SPRITE INVENTORY
	inventory.SetTexturePath("textures/Inventory.png");						//Hud Texture Path
	sdlInit.LoadTexture(inventory);											//HUD Texture Load
	inventory.SetPosition({ 0,0 });											//Hud Position
	inventory.SetSize(640, 480);											//hud Size

	//AI SPRITE WITCH
	witch.SetTexturePath("textures/witch.png");								//AI Texture Path
	sdlInit.LoadTexture(witch);												//AI Texture Load
	witch.SetPosition({ 575,133 });											//AI Position
	witch.SetSize(25, 35);													//AI Size
	witch.InitSpriteSheet(0, 8, 1);											//AI Initialize SpriteSheet
	witch.SetSpriteClip(0, 0, 24, 35, 0);									//AI Set Sprite Clip
	witch.SetSpriteClip(25, 0, 24, 35, 1);									//AI Set Sprite Clip
	witch.SetSpriteClip(50, 0, 24, 35, 2);									//AI Set Sprite Clip
	witch.SetSpriteClip(75, 0, 24, 35, 3);									//AI Set Sprite Clip
	witch.SetSpriteClip(100, 0, 24, 35, 4);									//AI Set Sprite Clip
	witch.SetSpriteClip(125, 0, 24, 35, 5);									//AI Set Sprite Clip
	witch.SetSpriteClip(150, 0, 24, 35, 6);									//AI Set Sprite Clip
	witch.SetSpriteClip(175, 0, 24, 35, 7);									//AI Set Sprite Clip
	witch.ConfigureCollision(true, false);									//AI Collision

	//AI SPRITE GUY IN BED
	guyInBed.SetTexturePath("textures/guyInBed.png");						//AI Texture Path
	sdlInit.LoadTexture(guyInBed);											//AI Texture Load
	guyInBed.SetPosition({ 1392,1016 });									//AI Position
	guyInBed.SetSize(43, 55);												//AI Size
	guyInBed.InitSpriteSheet(0, 3, 1);										//AI Initialize SpriteSheet
	guyInBed.SetSpriteClip(0, 1, 32, 40, 0);								//AI Set Sprite Clip
	guyInBed.SetSpriteClip(32, 1, 32, 40, 1);								//AI Set Sprite Clip
	guyInBed.ConfigureCollision(true, false);								//AI Collision

	//AI SPRITE SAW GUYS
	sawGuys.SetTexturePath("textures/sawGuys.png");							//AI Texture Path
	sdlInit.LoadTexture(sawGuys);											//AI Texture Load
	sawGuys.SetPosition({ 348,161 });										//AI Position
	sawGuys.SetSize(79, 28);												//AI Size
	sawGuys.InitSpriteSheet(0, 3, 1);										//AI Initialize SpriteSheet
	sawGuys.SetSpriteClip(0, 0, 79, 28, 0);									//AI Set Sprite Clip
	sawGuys.SetSpriteClip(80, 0, 79, 28, 1);								//AI Set Sprite Clip
	sawGuys.SetSpriteClip(160, 0, 79, 28, 2);								//AI Set Sprite Clip
	sawGuys.ConfigureCollision(true, false);								//AI Collision

	//MOVE TRIGGER HOUSE TO INSIDE
	houseToInside.SetPosition({ 510,284 });									//Teleport Positions
	houseToInside.SetSize(50, 22);											//Trigger Size
	houseToInside.ConfigureCollision(false, false);							//Teleport Collision
	houseToInside.SetMovePos({ 1520,1214 }, true);							//Telport Into House

	//MOVE TRIGGER HOUSE TO OUTSIDE
	houseToOutside.SetPosition({ 1510,1280 });								//Teleport Positions
	houseToOutside.SetSize(50, 20);											//Trigger Size
	houseToOutside.ConfigureCollision(false, false);						//Teleport Collision
	houseToOutside.SetMovePos({ 523,312 }, false);							//Teleport Outside Of House

	//WEATHER STATES WEATHER SYSTEM
	weatherSystem.Init(&sdlInit);											//Initialize sdl for the weather system

	//SPLASH SPRITE SPLASH BACKGROUND
	splashBackground.SetTexturePath("textures/splashBackground.png");		//AI Texture Path
	sdlInit.LoadTexture(splashBackground);									//AI Texture Load
	splashBackground.SetPosition({ 0,0 });									//AI Position
	splashBackground.SetSize(640,480);										//AI Size
	splashBackground.InitSpriteSheet(0, 8, 1);								//AI Initiate Sprite Sheet
	splashBackground.SetSpriteClip(0, 0, 640, 480, 0);						//AI Set Sprite Clip
	splashBackground.SetSpriteClip(641, 0, 640, 480, 1);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(1281, 0, 640, 480, 2);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(1921, 0, 640, 480, 3);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(2561, 0, 640, 480, 4);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(3201, 0, 640, 480, 5);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(3841, 0, 640, 480, 6);					//AI Set Sprite Clip
	splashBackground.SetSpriteClip(4481, 0, 640, 480, 7);					//AI Set Sprite Clip

	//SPLASH SPRITE START TEXT
	startText.SetTexturePath("textures/startText.png");						//AI Texture Path
	sdlInit.LoadTexture(startText);											//AI Texture Load
	startText.SetPosition({ 250,380 });										//AI Position
	startText.SetSize(192, 29);												//AI Size
	startText.InitSpriteSheet(0, 2, 1);										//AI Set Sprite Clip
	startText.SetSpriteClip(0, 0, 192, 29, 0);								//AI Set Sprite Clip
	startText.SetSpriteClip(0, 0, 0, 0, 1);									//AI Set Sprite Clip

	//MAIN MENU SPRITE BACKGROUND
	menuBackground.SetTexturePath("textures/mainMenu.png");					//Hud Texture Path
	sdlInit.LoadTexture(menuBackground);									//HUD Texture Load
	menuBackground.SetPosition({ 0,0 });									//Hud Position
	menuBackground.SetSize(640, 480);										//hud Size

	//WORLD GRID INITIALIZATION
	gWorld.InitWorldGrid({ 0,70 - 35,14,70 - 16 });
}
bool GameManager::Init(){
	bool initSuccess = sdlInit.Setup();
	if (initSuccess) { InitEntities(); }
	return initSuccess;
}
void GameManager::Cleanup(){
/*************************************************				CLEANUP				**************************************************/
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
	sdlInit.CleanupSprite(bldgInsideBlkDoor);
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
	sdlInit.CleanupSprite(blockerHouseBorder6);
	sdlInit.CleanupSprite(guyInBed);
	sdlInit.CleanupSprite(witch);
	sdlInit.CleanupSprite(sawGuys);
	sdlInit.CleanupSprite(magicMeter);
	sdlInit.CleanupSprite(lifeText);
	sdlInit.CleanupSprite(itemBox);
	sdlInit.CleanupSprite(hudItems);
	sdlInit.CleanupSprite(ground1);
	sdlInit.CleanupSprite(horizLongbush);
	sdlInit.CleanupSprite(inventory);
	sdlInit.Cleanup();
}
void GameManager::Update() {
/*************************************************				UPDATE				**************************************************/
	if (ls == LIGHTWORLD) {
		player.Update();									//Players Update Call
		animationStates();									//AI Animations Call
		Inventory();
		gCamera.LookAt(player);								//Camera Looks At Player
		weatherSystem.Update();
	}
	else if (ls == INSIDEHOUSE) {
		player.Update();
		animationStates();
		Inventory();
		gCamera.LookAt(player);
	}
	else if (ls == SPLASH) {
		animationStates();
	}
	else if (ls == MAINMENU) {
		animationStates();
	}
	sdlInit.Update();										//SDL Update Call
}

void GameManager::Render(){
	sdlInit.Render();										//Render SDL
	if (ls == LIGHTWORLD) {
		sdlInit.DrawSprite(ground1);						//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeTopLeft);					//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeTopLeftSide);				//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeTopRight);					//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeTopRightSide);				//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeBottomLeftSide);			//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeBottomRightSide);			//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeBottomLeft);				//Render Sprite Under Player
		sdlInit.DrawSprite(hedgeBottomRight);				//Render Sprite Under Player
		sdlInit.DrawSprite(horizLongbush);					//Render Sprite Under Player
		sdlInit.DrawSprite(house2BlackDoor);				//Render Sprite Under Player
		sdlInit.DrawSprite(bldgInsideBlkDoor);				//Render Sprite Under Player
		sdlInit.DrawSprite(guyInBed);						//Render Sprite Under Player
		sdlInit.DrawSprite(player);							//Render Sprite ***PLAYER***
		sdlInit.DrawSprite(statueBird);						//Render Sprite Above Player
		sdlInit.DrawSprite(tree);							//Render Sprite Above Player
		sdlInit.DrawSprite(tree2);							//Render Sprite Above Player
		sdlInit.DrawSprite(redHouse2);						//Render Sprite Above Player
		sdlInit.DrawSprite(redHouse1);						//Render Sprite Above Player
		sdlInit.DrawSprite(blueHouse2);						//Render Sprite Above Player
		sdlInit.DrawSprite(blueHouse3);						//Render Sprite Above Player
		sdlInit.DrawSprite(witch);							//Render Sprite Above Player
		sdlInit.DrawSprite(sawGuys);						//Render Sprite Above Player
		sdlInit.DrawSprite(buildingInside);					//Render Sprite Above Player
		weatherSystem.Render();
		if (!invOpen) {
			sdlInit.DrawHud(magicMeter);					//Render HUD
			sdlInit.DrawHud(lifeText);						//Render HUD
			sdlInit.DrawHud(itemBox);						//Render HUD
			sdlInit.DrawHud(hudItems);
		}						//Render HUD
		if (invOpen) { sdlInit.DrawHud(inventory); }		//Render Inventory
	}
	else if (ls== SPLASH) {
		sdlInit.DrawSprite(splashBackground);
	}
	else if (ls == MAINMENU) {
		sdlInit.DrawSprite(menuBackground);
		sdlInit.DrawHud(startText);
	}
	
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
		sdlInit.DrawEntityCollider(bldgInsideBlkDoor);
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
		sdlInit.DrawEntityCollider(blockerHouseBorder6);
		sdlInit.DrawEntityCollider(guyInBed);
	}
}

void GameManager::animationStates() {
	static int i = 0;
	witch.SetAnimSwapIndices(8, 6.0f, witchSwapIndices);
	witch.Update();
	sawGuys.SetAnimSwapIndices(3, .8f, sawGuysIndices);
	sawGuys.Update();
	guyInBed.SetAnimSwapIndices(2, .2f, guyInBedIndices);
	guyInBed.Update();
	if (ls == SPLASH) {
		if (!playingMusic) {
			PlayBGMusic(selectScreen);
			playingMusic = true;
		}

		if (i <= 1500 ) {
			sleep_for(nanoseconds(20));
			splashBackground.SetAnimSwapIndices(18, 8.0f, splashBackgroundIndices);
			splashBackground.Update();
			std::cout << i << std::endl;
			if (i > 1499) ls = MAINMENU;
			i++;
		}
	}
	if (ls == MAINMENU) {
		startText.SetAnimSwapIndices(2, 1.0f, startTextIndices);
		startText.Update();
		if (gEKeyDown) {
			PlaySFX(SFX4);
			ls = LIGHTWORLD;
			StopBGMusic();
			PlayBGMusic(BGMusic1);
		}
	}
}

void GameManager::Inventory() {
	if (gIKeyDown) {
		if (!invOpen)
			PlaySFX(SFX2);
		invOpen = true;
	}
	else if (!gIKeyDown) {
		if (invOpen)
			PlaySFX(SFX3);
		invOpen = false;
	}
}