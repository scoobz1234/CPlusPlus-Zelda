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
/*************************************************			FLAG and ECT			**************************************************/
#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS false

using namespace std;

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
bool BGMusicPlaying { false };
bool BGMusicRainPlaying{ false };
bool BGMusicInsideRainPlaying{ false };
extern void PlayBGMusic(Mix_Music *bgmName);
extern void PlaySFX(Mix_Chunk *sfxName);
extern void StopBGMusic();
extern Mix_Music *weatherRain;
extern Mix_Music *weatherRainInside;
extern Mix_Music *BGMusic1;
extern Mix_Chunk *SFX2;
extern Mix_Chunk *SFX3;

//keypresses inventory
extern bool gIKeyDown;						//bool so we can check if the I key is pressed
extern bool gIKeyUp;
bool invOpen{ false };						//another inventory bool so we can toggle stuff

//weather stuff...
float weatherTimer = 0.f;					//Timer for the weather generator
int weatherGenerator{ 0 };					//Weather Generator set to 0 initially
bool rainOn{ false };						//rain toggle bool set to false
bool fogOn{ false };						//fog toggle bool set to false
extern bool inside;							//checks if player is "inside" so we can toggle weather

static SDLInit sdlInit;
namespace {
/*************************************************			INTRODUCTIONS			**************************************************/
	Player player;							//Player
	Sprite tree;							//Sprite
	Sprite tree2;							//Sprite
	Sprite blocker;							//Invisible Blockade Sprite
	Sprite blocker2;						//Invisible Blockade Sprite
	Sprite blockerHouseBorder1;				//Invisible Blockade Sprite
	Sprite blockerHouseBorder2;				//Invisible Blockade Sprite
	Sprite blockerHouseBorder3;				//Invisible Blockade Sprite
	Sprite blockerHouseBorder4;				//Invisible Blockade Sprite
	Sprite blockerHouseBorder5;				//Invisible Blockade Sprite
	Sprite blockerHouseBorder6;				//Invisible Blockade Sprite
	Sprite house2BlackDoor;					//Sprite
	Sprite buildingInsideBlackDoor;			//Sprite
	Sprite hedgeTopLeft;					//Sprite
	Sprite hedgeTopRight;					//Sprite
	Sprite hedgeTopLeftSide;				//Sprite
	Sprite hedgeTopRightSide;				//Sprite
	Sprite hedgeBottomLeft;					//Sprite
	Sprite hedgeBottomRight;				//Sprite
	Sprite hedgeBottomLeftSide;				//Sprite
	Sprite hedgeBottomRightSide;			//Sprite
	Sprite statueBird;						//Sprite
	Sprite buildingInside;					//Sprite
	Sprite horizLongbush;					//Sprite
	Sprite redHouse1;						//House Sprite
	Sprite redHouse2;						//House Sprite
	Sprite blueHouse2;						//House Sprite
	Sprite blueHouse3;						//House Sprite
	Sprite ground1;							//Ground Sprite
	Sprite magicMeter;						//HUD Sprite
	Sprite lifeText;						//HUD Sprite
	Sprite itemBox;							//HUD Sprite
	Sprite hudItems;						//HUD Sprite
	Sprite inventory;						//HUD Sprite
	AISprite witch;							//AI Sprite
	AISprite guyInBed;						//AI Sprite
	AISprite sawGuys;						//AI Sprite
	MoveTrigger houseToInside;				//Trigger Sprite
	MoveTrigger houseToOutside;				//Trigger Sprite
	WeatherStates weatherSystem;	//Weather System
	//Weather rain;							//Weather Sprite
	//Weather fog;							//Weather Sprite
/*************************************************		SET ANIMATION INDICES		**************************************************/
	int witchSwapIndices[] = { 0,1,2,3,4,5,6,7};
	int guyInBedIndices[] = {0,1};
	int rainIndices[] = { 0,1,2,3 };
	int fogIndices[] = { 0,1,2,3 };
	int sawGuysIndices[] = {0,1,2};
}
void InitEntities() {
/*************************************************			SET TEXTURE PATH		**************************************************/
	weatherSystem.Init(&sdlInit);
	player.SetTexturePath("textures/link_sheet.png");						//Player Texture Path
	tree.SetTexturePath("textures/tree_green.gif");							//Sprite Texture Path
	tree2.SetTexturePath("textures/tree_green.gif");						//Sprite Texture Path
	house2BlackDoor.SetTexturePath("textures/Door_Black.png");				//Sprite Texture Path
	buildingInsideBlackDoor.SetTexturePath("textures/Door_Black.png");		//Sprite Texture Path
	hedgeTopLeft.SetTexturePath("textures/Hedge_Top.png");					//Sprite Texture Path
	hedgeTopLeftSide.SetTexturePath("textures/Hedge_Top_left.png");			//Sprite Texture Path
	hedgeTopRight.SetTexturePath("textures/Hedge_Top.png");					//Sprite Texture Path
	hedgeTopRightSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	statueBird.SetTexturePath("textures/Statue_Bird.png");					//Sprite Texture Path
	hedgeBottomLeft.SetTexturePath("textures/Hedge_Top.png");				//Sprite Texture Path
	hedgeBottomLeftSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	hedgeBottomRight.SetTexturePath("textures/Hedge_Top.png");				//Sprite Texture Path
	hedgeBottomRightSide.SetTexturePath("textures/Hedge_Top_left.png");		//Sprite Texture Path
	buildingInside.SetTexturePath("textures/inside_bld.png");				//Sprite Texture Path
	horizLongbush.SetTexturePath("textures/horizLongBush.png");				//Sprite Texture Path
	guyInBed.SetTexturePath("textures/guyInBed.png");						//AI Texture Path
	witch.SetTexturePath("textures/witch.png");								//AI Texture Path
	sawGuys.SetTexturePath("textures/sawGuys.png");							//AI Texture Path
	redHouse1.SetTexturePath("textures/Red_Roof_House.png");				//House Texture Path
	redHouse2.SetTexturePath("textures/Skull_House.png");					//House Texture Path
	blueHouse2.SetTexturePath("textures/blueHouse2.png");					//House Texture Path
	blueHouse3.SetTexturePath("textures/blueHouse3.png");					//House Texture Path
	ground1.SetTexturePath("textures/ground1.png");							//Ground Texture Path
	magicMeter.SetTexturePath("textures/tempMeter.png");					//Hud Texture Path
	lifeText.SetTexturePath("textures/lifeTextHud.png");					//Hud Texture Path
	itemBox.SetTexturePath("textures/itemBox.png");							//Hud Texture Path
	hudItems.SetTexturePath("textures/hudItems.png");						//Hud Texture Path
	inventory.SetTexturePath("textures/Inventory.png");						//Hud Texture Path
	//rain.SetTexturePath("textures/rain2.png");								//Weather Texture Path
	//fog.SetTexturePath("textures/fog.png");									//Weather Texture Path
/*************************************************			LOAD TEXTURES			**************************************************/
	sdlInit.LoadTexture(player);						//Player Texture Load
	sdlInit.LoadTexture(tree);							//Sprite Texture Load
	sdlInit.LoadTexture(tree2);							//Sprite Texture Load
	sdlInit.LoadTexture(house2BlackDoor);				//Sprite Texture Load
	sdlInit.LoadTexture(buildingInsideBlackDoor);		//Sprite Texture Load
	sdlInit.LoadTexture(hedgeTopLeft);					//Sprite Texture Load
	sdlInit.LoadTexture(hedgeTopLeftSide);				//Sprite Texture Load
	sdlInit.LoadTexture(hedgeTopRight);					//Sprite Texture Load
	sdlInit.LoadTexture(hedgeTopRightSide);				//Sprite Texture Load
	sdlInit.LoadTexture(hedgeBottomLeft);				//Sprite Texture Load
	sdlInit.LoadTexture(hedgeBottomLeftSide);			//Sprite Texture Load
	sdlInit.LoadTexture(hedgeBottomRight);				//Sprite Texture Load
	sdlInit.LoadTexture(hedgeBottomRightSide);			//Sprite Texture Load
	sdlInit.LoadTexture(statueBird);					//Sprite Texture Load
	sdlInit.LoadTexture(buildingInside);				//Sprite Texture Load
	sdlInit.LoadTexture(horizLongbush);					//Sprite Texture Load
	sdlInit.LoadTexture(guyInBed);						//AI Texture Load
	sdlInit.LoadTexture(witch);							//AI Texture Load
	sdlInit.LoadTexture(sawGuys);						//AI Texture Load
	sdlInit.LoadTexture(redHouse1);						//House Texture Load
	sdlInit.LoadTexture(redHouse2);						//House Texture Load
	sdlInit.LoadTexture(blueHouse2);					//House Texture Load
	sdlInit.LoadTexture(blueHouse3);					//House Texture Load
	sdlInit.LoadTexture(ground1);						//Ground Texture Load
	sdlInit.LoadTexture(magicMeter);					//Hud Texture Load
	sdlInit.LoadTexture(lifeText);						//Hud Texture Load
	sdlInit.LoadTexture(itemBox);						//Hud Texture Load
	sdlInit.LoadTexture(hudItems);						//Hud Texture Load
	sdlInit.LoadTexture(inventory);						//HUD Texture Load
	//sdlInit.LoadTexture(rain);							//Weather Texture Load
	//sdlInit.LoadTexture(fog);							//Weather Texture Load
/*************************************************			SET POSITION			**************************************************/
	player.SetPosition({ 68,143 });							//Sprite Position
	tree.SetPosition({ 360, 20 });							//Sprite Position
	tree2.SetPosition({360, 120});							//Sprite Position
	house2BlackDoor.SetPosition({ 510,288 });				//Sprite Position
	buildingInsideBlackDoor.SetPosition({ 1510,1224 });		//Sprite Position
	hedgeTopLeft.SetPosition({ 153, 33 });					//Sprite Position
	hedgeTopLeftSide.SetPosition({ 153, 33 });				//Sprite Position
	hedgeTopRight.SetPosition({ 235, 33 });					//Sprite Position
	hedgeTopRightSide.SetPosition({ 280, 33 });				//Sprite Position
	hedgeBottomLeft.SetPosition({ 153, 180 });				//Sprite Position
	hedgeBottomLeftSide.SetPosition({ 153, 122 });			//Sprite Position
	hedgeBottomRight.SetPosition({ 235, 180 });				//Sprite Position
	hedgeBottomRightSide.SetPosition({ 280, 122 });			//Sprite Position
	statueBird.SetPosition({ 208, 72 });					//Sprite Position
	buildingInside.SetPosition({ 1210,880 });				//Sprite Position
	horizLongbush.SetPosition({0,446});						//Sprite Position
	redHouse1.SetPosition({ 492, 35 });						//House Position
	redHouse2.SetPosition({ 475, 250 });					//House Position
	blueHouse2.SetPosition({ 43, 275 });					//House Position
	blueHouse3.SetPosition({ 284, 258 });					//House Position
	ground1.SetPosition({0,0});								//Ground Position
	magicMeter.SetPosition({20,20});						//Hud Position
	lifeText.SetPosition({500,10});							//Hud Position
	itemBox.SetPosition({50,20});							//Hud Position
	hudItems.SetPosition({110,10});							//Hud Position
	inventory.SetPosition({ 0,0 });							//Hud Position
	guyInBed.SetPosition({ 1392,1016 });					//AI Position
	witch.SetPosition({575,133});							//AI Position
	sawGuys.SetPosition({ 348,161 });						//AI Position
	blocker.SetPosition({ 475, 292 });						//Invisible Blockade Position
	blocker2.SetPosition({ 546, 292 });						//Invisible Blockade Position
	blockerHouseBorder1.SetPosition({1210,880});			//Invisible Blockade Position
	blockerHouseBorder2.SetPosition({1210,1225});			//Invisible Blockade Position
	blockerHouseBorder3.SetPosition({1210,1016});			//Invisible Blockade Position
	blockerHouseBorder4.SetPosition({1668,1016});			//Invisible Blockade Position
	blockerHouseBorder5.SetPosition({1555,1225});			//Invisible Blockade Position
	blockerHouseBorder6.SetPosition({1512,1300});			//Invisible Blockade Position
	//rain.SetPosition({0,0});								//Weather Position
	//fog.SetPosition({0,0});									//Weather Position
	houseToInside.SetPosition({ 510,284 });					//Teleport Positions
	houseToOutside.SetPosition({ 1510,1280 });				//Teleport Positions
/*************************************************			SET SIZE				**************************************************/
	player.SetSize(45, 45);						//player Size
	tree.SetSize(54, 68);						//sprite Size
	tree2.SetSize(54, 68);						//sprite Size
	house2BlackDoor.SetSize(50, 50);			//sprite Size
	buildingInsideBlackDoor.SetSize(50, 50);	//sprite Size
	hedgeTopLeft.SetSize(60, 20);				//sprite Size
	hedgeTopLeftSide.SetSize(15, 65);			//sprite Size
	hedgeTopRight.SetSize(60, 20);				//sprite Size
	hedgeTopRightSide.SetSize(15, 65);			//sprite Size
	hedgeBottomLeft.SetSize(60, 20);			//sprite Size
	hedgeBottomLeftSide.SetSize(15, 65);		//sprite Size
	hedgeBottomRight.SetSize(60, 20);			//sprite Size
	hedgeBottomRightSide.SetSize(15, 65);		//sprite Size
	statueBird.SetSize(30, 50);					//sprite Size
	buildingInside.SetSize(640,480);			//sprite Size
	horizLongbush.SetSize(216,23);				//sprite Size
	redHouse1.SetSize(120, 100);				//house sprite Size
	redHouse2.SetSize(120, 100);				//house sprite Size
	blueHouse2.SetSize(120, 100);				//house sprite Size
	blueHouse3.SetSize(120, 100);				//house sprite Size
	ground1.SetSize(640,480);					//ground texture Size
	magicMeter.SetSize(26,62);					//hud Size
	lifeText.SetSize(64,17);					//hud Size
	itemBox.SetSize(32,32);						//hud Size
	hudItems.SetSize(100,18);					//hud Size
	inventory.SetSize(640, 480);				//hud Size
	guyInBed.SetSize(43,55);					//AI Size
	witch.SetSize(25, 35);						//AI Size
	sawGuys.SetSize(79,28);						//AI Size
	houseToInside.SetSize(50, 22);				//Trigger Size
	houseToOutside.SetSize(50, 20);				//Trigger Size
	blocker.SetSize(48, 56);					//invisible blockade Size
	blocker2.SetSize(48, 56);					//invisible blockade Size
	blockerHouseBorder1.SetSize(640,136);		//invisible blockade Size
	blockerHouseBorder2.SetSize(302,136);		//invisible blockade Size
	blockerHouseBorder3.SetSize(182,209);		//invisible blockade Size
	blockerHouseBorder4.SetSize(182,209);		//invisible blockade Size
	blockerHouseBorder5.SetSize(302,136);		//invisible blockade Size
	blockerHouseBorder6.SetSize(43, 60);		//invisible blockade Size
	//rain.SetSize(640,480);						//weather Size
	//fog.SetSize(640, 480);						//weather Size
/*************************************************		INITITIALIZE SPRITESHEETS	**************************************************/
	player.InitSpriteSheet(0, 14, 6);					//Player Initialize SpriteSheet
	player.SetSpriteClip(90, 1, 30, 30, 3);				//Player Set Sprite Clips			up...
	player.SetSpriteClip(90, 31, 30, 30, 17);			//Player Set Sprite Clips			up move...
	player.SetSpriteClip(30, 1, 30, 30, 1);				//Player Set Sprite Clips			down...
	player.SetSpriteClip(30, 31, 30, 30, 15);			//Player Set Sprite Clips			down move...
	player.SetSpriteClip(120, 1, 30, 30, 4);			//Player Set Sprite Clips			right...
	player.SetSpriteClip(120, 31, 30, 30, 18);			//Player Set Sprite Clips			right move...
	player.SetSpriteClip(60, 1, 30, 30, 2);				//Player Set Sprite Clips			left...
	player.SetSpriteClip(60, 31, 30, 30, 16);			//Player Set Sprite Clips			left move...

	player.SetSpriteClip(170, 141, 30, 31, 61);			//Player Set Sprite Clips			first left attack...
	player.SetSpriteClip(173, 109, 30, 30, 48);			//Player Set Sprite Clips			second left attack...
	player.SetSpriteClip(173, 71, 30, 30, 34);			//Player Set Sprite Clips			last left attack...
	player.SetSpriteClip(203, 142, 30, 30, 62);			//Player Set Sprite Clips			last right attack...
	player.SetSpriteClip(203, 109, 30, 30, 49);			//Player Set Sprite Clips			second right attack...
	player.SetSpriteClip(203, 77, 30, 31, 35);			//Player Set Sprite Clips			first right attack...
	player.SetAnchorOffset({ -16, -13 }, 61);			//Player Set Sprite Clips			first left attack...
	player.SetAnchorOffset({ -23, -10 }, 48);			//Player Set Sprite Clips			second left attack...
	player.SetAnchorOffset({ -26, -5 }, 34);			//Player Set Sprite Clips			last left attack...
	player.SetAnchorOffset({ 4, 0 }, 62);				//Player Set Sprite Clips			last right attack...
	player.SetAnchorOffset({ 2, -10 }, 49);				//Player Set Sprite Clips			second right attack...
	player.SetAnchorOffset({ -11, -13 }, 35);			//Player Set Sprite Clips			first right attack...=>2
	guyInBed.InitSpriteSheet(0,3,1);					//AI Initialize SpriteSheet
	guyInBed.SetSpriteClip(0, 1, 32, 40, 0);			//AI Set Sprite Clip
	guyInBed.SetSpriteClip(32, 1, 32, 40, 1);			//AI Set Sprite Clip
	witch.InitSpriteSheet(0, 8, 1);						//AI Initialize SpriteSheet
	witch.SetSpriteClip(0, 0, 24, 35, 0);				//AI Set Sprite Clip
	witch.SetSpriteClip(25, 0, 24, 35, 1);				//AI Set Sprite Clip
	witch.SetSpriteClip(50, 0, 24, 35, 2);				//AI Set Sprite Clip
	witch.SetSpriteClip(75, 0, 24, 35, 3);				//AI Set Sprite Clip
	witch.SetSpriteClip(100, 0, 24, 35, 4);				//AI Set Sprite Clip
	witch.SetSpriteClip(125, 0, 24, 35, 5);				//AI Set Sprite Clip
	witch.SetSpriteClip(150, 0, 24, 35, 6);				//AI Set Sprite Clip
	witch.SetSpriteClip(175, 0, 24, 35, 7);				//AI Set Sprite Clip
	
	sawGuys.InitSpriteSheet(0, 3, 1);					//AI Initialize SpriteSheet
	sawGuys.SetSpriteClip(0,0,79,28,0);					//AI Set Sprite Clip
	sawGuys.SetSpriteClip(80,0,79,28,1);				//AI Set Sprite Clip
	sawGuys.SetSpriteClip(160,0,79,28,2);				//AI Set Sprite Clip
	
	//rain.InitSpriteSheet(0, 4, 1);						//Weather Initialize SpriteSheet
	//rain.SetSpriteClip(0, 0, 256, 223, 0);				//Weather Set Sprite Clip
	//rain.SetSpriteClip(257, 0, 256, 223, 1);			//Weather Set Sprite Clip
	//rain.SetSpriteClip(513, 0, 256, 223, 2);			//Weather Set Sprite Clip
	//rain.SetSpriteClip(769, 0, 256, 223, 3);			//Weather Set Sprite Clip
	//
	//fog.InitSpriteSheet(0, 4, 1);						//Weather Initialize SpriteSheet
	//fog.SetSpriteClip(0, 0, 480, 360, 0);				//Weather Set Sprite Clip
	//fog.SetSpriteClip(481, 0, 480, 360, 1);				//Weather Set Sprite Clip
	//fog.SetSpriteClip(961, 0, 480, 360, 2);				//Weather Set Sprite Clip
	//fog.SetSpriteClip(1441, 0, 480, 360, 3);			//Weather Set Sprite Clip
/*************************************************			SET COLLISION			**************************************************/
	player.ConfigureCollision(true,true, {5,10}, {28,15});							//Player Collision
	tree.ConfigureCollision(true,false, {0,15}, {0,0});								//Sprite Collision
	tree2.ConfigureCollision(true,false,{0, 15}, { 0,0 });							//Sprite Collision
	hedgeTopLeft.ConfigureCollision(true, false);									//Sprite Collision
	hedgeTopLeftSide.ConfigureCollision(true, false);								//Sprite Collision
	hedgeTopRight.ConfigureCollision(true, false);									//Sprite Collision
	hedgeTopRightSide.ConfigureCollision(true, false);								//Sprite Collision
	hedgeBottomLeft.ConfigureCollision(true, false);								//Sprite Collision
	hedgeBottomLeftSide.ConfigureCollision(true, false);							//Sprite Collision
	hedgeBottomRight.ConfigureCollision(true, false);								//Sprite Collision
	hedgeBottomRightSide.ConfigureCollision(true, false);							//Sprite Collision
	horizLongbush.ConfigureCollision(true, false);									//Sprite Collision
	statueBird.ConfigureCollision(true, false, {0,25}, {0,0});						//Sprite Collision
	house2BlackDoor.ConfigureCollision(false,false, {0,0}, {0,40});					//Sprite Collision
	buildingInsideBlackDoor.ConfigureCollision(false, false, { 0,40 }, { 0,0 });	//Sprite Collision
	buildingInside.ConfigureCollision(true, false);									//Sprite Collision
	houseToInside.ConfigureCollision(false, false);									//Teleport Collision
	houseToOutside.ConfigureCollision(false, false);								//Teleport Collision
	redHouse1.ConfigureCollision(true, false, { 0,8 }, { 0,5 });					//House Collision
	redHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,55 });					//House Collision
	blueHouse2.ConfigureCollision(true, false, { 0,8 }, { 0,5 });					//House Collision
	blueHouse3.ConfigureCollision(true, false, { 0,8 }, { 0,55 });					//House Collision
	blocker.ConfigureCollision(true, false);										//Invisible Blockade Collision
	blocker2.ConfigureCollision(true, false);										//Invisible Blockade Collision
	blockerHouseBorder2.ConfigureCollision(true, false);							//Invisible Blockade Collision
	blockerHouseBorder1.ConfigureCollision(true, false);							//Invisible Blockade Collision
	blockerHouseBorder3.ConfigureCollision(true, false);							//Invisible Blockade Collision
	blockerHouseBorder4.ConfigureCollision(true, false);							//Invisible Blockade Collision
	blockerHouseBorder5.ConfigureCollision(true, false);							//Invisible Blockade Collision
	blockerHouseBorder6.ConfigureCollision(true, false);							//Invisible Blockade Collision
	guyInBed.ConfigureCollision(true, false);										//AI Collision
	witch.ConfigureCollision(true, false);											//AI Collision
	sawGuys.ConfigureCollision(true, false);										//AI Collision
	//rain.ConfigureCollision(false, false);											//Weather Collision
	//fog.ConfigureCollision(false, false);											//Weather Collision
/*************************************************			ENABLE COLLISION		**************************************************/
	player.AddCollidableEntity(tree);							//Player/Sprite Collision
	player.AddCollidableEntity(tree2);							//Player/Sprite Collision
	player.AddCollidableEntity(redHouse1);						//Player/Sprite Collision
	player.AddCollidableEntity(redHouse2);						//Player/Sprite Collision
	player.AddCollidableEntity(blueHouse2);						//Player/Sprite Collision
	player.AddCollidableEntity(blueHouse3);						//Player/Sprite Collision
	player.AddCollidableEntity(blocker);						//Player/Sprite Collision
	player.AddCollidableEntity(blocker2);						//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopLeft);					//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopLeftSide);				//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomLeft);				//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomLeftSide);			//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomRight);				//Player/Sprite Collision
	player.AddCollidableEntity(hedgeBottomRightSide);			//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopRight);					//Player/Sprite Collision
	player.AddCollidableEntity(hedgeTopRightSide);				//Player/Sprite Collision
	player.AddCollidableEntity(statueBird);						//Player/Sprite Collision
	player.AddCollidableEntity(house2BlackDoor);				//Player/Sprite Collision
	player.AddCollidableEntity(buildingInsideBlackDoor);		//Player/Sprite Collision
	player.AddCollidableEntity(houseToInside);					//Player/Sprite Collision
	player.AddCollidableEntity(houseToOutside);					//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder1);			//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder2);			//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder3);			//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder4);			//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder5);			//Player/Sprite Collision
	player.AddCollidableEntity(blockerHouseBorder6);			//Player/Sprite Collision
	player.AddCollidableEntity(guyInBed);						//Player/Sprite Collision
	player.AddCollidableEntity(witch);							//Player/Sprite Collision
	player.AddCollidableEntity(sawGuys);						//Player/Sprite Collision
	player.AddCollidableEntity(horizLongbush);					//Player/Sprite Collision
/*************************************************		WORLD GRID INITIALIZATION	**************************************************/
	gWorld.InitWorldGrid({ 0,70 - 35,14,70 - 16 });					//Initialize the World Grid
/*************************************************			TELEPORT LOCATIONS		**************************************************/
	houseToInside.SetMovePos({1520,1214},true);					//Telport Into House
	houseToOutside.SetMovePos({ 523,312 },false);				//Teleport Outside Of House
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
	//sdlInit.CleanupSprite(rain);
	//sdlInit.CleanupSprite(fog);
	sdlInit.CleanupSprite(inventory);
	sdlInit.Cleanup();
}
void GameManager::Update() {
/*************************************************				UPDATE				**************************************************/
	player.Update();									//Players Update Call
	animationStates();									//AI Animations Call
	//weatherStates();									//Weather States Call
	Inventory();
	gCamera.LookAt(player);								//Camera Looks At Player
	sdlInit.Update();									//SDL Update Call
	weatherSystem.Update();
}

void GameManager::Render(){
/*************************************************				RENDERING			**************************************************/
	sdlInit.Render();									//Render SDL
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
	sdlInit.DrawSprite(buildingInsideBlackDoor);		//Render Sprite Under Player
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
	//if (!inside) {
	//	if (rainOn) { sdlInit.DrawHud(rain);  }			//Render Weather Under HUD
	//	if (fogOn) { sdlInit.DrawHud(fog); }}			//Render Weather Under HUD
	weatherSystem.Render();
	if (!invOpen) {
		sdlInit.DrawHud(magicMeter);					//Render HUD
		sdlInit.DrawHud(lifeText);						//Render HUD
		sdlInit.DrawHud(itemBox);						//Render HUD
		sdlInit.DrawHud(hudItems);}						//Render HUD
	if (invOpen) { sdlInit.DrawHud(inventory); }		//Render Inventory
	
/*************************************************		RENDERING COLLIDERS			**************************************************/
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
		sdlInit.DrawEntityCollider(blockerHouseBorder6);
		sdlInit.DrawEntityCollider(guyInBed);
	}
}
void GameManager::animationStates() {
	witch.SetAnimSwapIndices(8, 6.0f, witchSwapIndices);
	witch.Update();
	sawGuys.SetAnimSwapIndices(3, .8f, sawGuysIndices);
	sawGuys.Update();
	guyInBed.SetAnimSwapIndices(2, .2f, guyInBedIndices);
	guyInBed.Update();
}
//void GameManager::weatherStates() {
//	weatherTimer--;														//Timer De-crements every tick
//
//	if (weatherTimer <= 0) {
//		srand(time(NULL));												//Primes random # Generator
//		weatherGenerator = rand() % 3;								//Generators Random Number between 1-30
//	
//		if (weatherGenerator ==0) {	
//			StopBGMusic();												//stops currently playing music
//			PlayBGMusic(BGMusic1);										//plays background music
//			rainOn = false;												//if clear weather 0-10 rain false
//			fogOn = false;												//if clear weather 0-10 fog false
//			weatherTimer = 80000.f;										//if clear weather 0-10 reset timer
//			return;
//		}
//		else if (weatherGenerator ==1) {
//			fogOn = false;												//if rainy weather 10-20 fog false
//			rainOn = true;												//if rainy weather 10-20 rain on
//			weatherTimer = 80000.f;										//if rainy weather 10-20 reset timer
//			BGMusicRainPlaying = false;
//		}
//		else {
//			StopBGMusic();
//			PlayBGMusic(BGMusic1);
//			rainOn = false;												//if foggy weather 20-30 rain false
//			fogOn = true;												//if foggy weather 20-30 fog false
//			weatherTimer = 80000.f;										//if foggy weather 20-30 reset timer
//		}
//	}
//
//	if (rainOn) {
//		if (inside && !BGMusicInsideRainPlaying) {
//			BGMusicRainPlaying = false;										//set flag for outside rain music to false
//			StopBGMusic();													//stop currently playing music
//			PlayBGMusic(weatherRainInside);									//start the inside rain music
//			BGMusicInsideRainPlaying = true;								//set flag for inside rain music to true, so we dont keep restarting it.
//			rain.SetAnimSwapIndices(4, 6.0f, rainIndices);					//if rainy weather set the params for the class
//			rain.Update();													//if rainy weather update it!
//		}
//		else if (inside && BGMusicInsideRainPlaying) {
//			BGMusicRainPlaying = false;										//set flag for outside rain music to false
//			BGMusicInsideRainPlaying = true;								//set the inside rain music to true (won't work without it for some reason)
//			rain.SetAnimSwapIndices(4, 6.0f, rainIndices);					//if rainy weather set the params for the class
//			rain.Update();													//if rainy weather update it!
//		}
//		else if (!inside && !BGMusicRainPlaying) {
//			BGMusicInsideRainPlaying = false;								//set flag for inside rain music to false (incase we went outside)
//			StopBGMusic();													//stop currently playing music
//			PlayBGMusic(weatherRain);										//start the outside rain music
//			BGMusicRainPlaying = true;										//set flag for outside rain music to true, so we dont keep restarting it.
//			rain.SetAnimSwapIndices(4, 6.0f, rainIndices);					//if rainy weather set the params for the class
//			rain.Update();													//if rainy weather update it!
//		}
//		else if (!inside && BGMusicRainPlaying) {
//			BGMusicInsideRainPlaying = false;								//set flag for inside rain music to false (incase we went outside)
//			BGMusicRainPlaying = true;										//set flag for outside rain to true (wont work without it for some reason)
//			rain.SetAnimSwapIndices(4, 6.0f, rainIndices);					//if rainy weather set the params for the class
//			rain.Update();													//if rainy weather update it!
//		}
//	}
//	else if (fogOn) {
//		fog.SetAnimSwapIndices(4, .3f, fogIndices);						//if foggy weather set the params for the class
//		fog.Update();													//if foggy weather update it!
//	}
//	else {
//		return;															//else return...
//	}
//}
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