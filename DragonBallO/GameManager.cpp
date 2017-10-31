/*************************************************				INCLUDES			**************************************************/
#include "GameManager.h"
#include "SDLInit.h"
#include "World.h"
#include "Player.h"
#include "NPC.h"
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
/*************************************************			FLAGS and ECT			**************************************************/
#define CAMERA_MODE Camera::Mode::PAN
#define SHOW_COLLIDERS true

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//camera dimensions
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

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
GameManager::LoadedScene ls = GameManager::LoadedScene::LIGHTWORLD;
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
	NPC guard;																//AI NPC
	Sprite Map;

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
	player.SetTexturePath("textures/link_walk_attack.png");						//Player Texture Path
	sdlInit.LoadTexture(player);											//Player Texture Load
	player.SetPosition({ 68,143 });											//Sprite Position
	player.SetSize(45, 45);													//player Size
	player.InitSpriteSheet(0, 21, 4);										//Player Initialize SpriteSheet
	//up attack 1-8
	player.SetSpriteClip(0, 0, 45, 45, 0);
	player.SetSpriteClip(46, 0, 45, 45, 1);
	player.SetSpriteClip(91, 0, 45, 45, 2);
	player.SetSpriteClip(136, 0 , 45, 45, 3);
	player.SetSpriteClip(181, 0, 45, 45, 4);
	player.SetSpriteClip(226, 0, 45, 45, 5);
	player.SetSpriteClip(271, 0, 45, 45, 6);
	player.SetSpriteClip(316, 0, 45, 45, 7);
	player.SetSpriteClip(361, 0, 45, 45, 8);

	player.SetAnchorOffset({ 0, -8 }, 0);
	player.SetAnchorOffset({ 0, -8 }, 1);
	player.SetAnchorOffset({ 0, -8 }, 2);
	player.SetAnchorOffset({ 0, -8 }, 3);
	player.SetAnchorOffset({ 0, -8 }, 4);
	player.SetAnchorOffset({ 0, -8 }, 5);
	player.SetAnchorOffset({ 0, -8 }, 6);
	player.SetAnchorOffset({ 0, -8 }, 7);
	player.SetAnchorOffset({ 0, -8 }, 8);

	//left attack 9-17
	player.SetSpriteClip(406, 0, 45, 45, 17);
	player.SetSpriteClip(451, 0, 45, 45, 16);
	player.SetSpriteClip(496, 0, 45, 45, 15);
	player.SetSpriteClip(541, 0, 45, 45, 14);
	player.SetSpriteClip(586, 0, 45, 45, 13);
	player.SetSpriteClip(631, 0, 45, 45, 12);
	player.SetSpriteClip(676, 0, 45, 45, 11);
	player.SetSpriteClip(721, 0, 45, 45, 10);
	player.SetSpriteClip(766, 0, 45, 45, 9);

	player.SetAnchorOffset({ -8, -3 }, 10);
	player.SetAnchorOffset({ -8, -3 }, 11);
	player.SetAnchorOffset({ -8, -3 }, 12);
	player.SetAnchorOffset({ -8, -3 }, 13);
	player.SetAnchorOffset({ -8, -3 }, 14);
	player.SetAnchorOffset({ -8, -3 }, 15);
	player.SetAnchorOffset({ -8, -3 }, 16);
	player.SetAnchorOffset({ -8, -3 }, 17);
	player.SetAnchorOffset({ -8, -3 }, 9);

	//right attack 18-26	
	player.SetSpriteClip(0, 46, 45, 45, 18);
	player.SetSpriteClip(46, 46, 45, 45, 19);
	player.SetSpriteClip(91, 46, 45, 45, 20);
	player.SetSpriteClip(136, 46, 45, 45, 21);
	player.SetSpriteClip(181, 46, 45, 45, 22);	
	player.SetSpriteClip(226, 46, 45, 45, 23);
	player.SetSpriteClip(271, 46, 45, 45, 24);
	player.SetSpriteClip(316, 46, 45, 45, 25);
	player.SetSpriteClip(361, 46, 45, 45, 26);

	player.SetAnchorOffset({ 0, -3 }, 18);
	player.SetAnchorOffset({ 0, -3 }, 19);
	player.SetAnchorOffset({ 0, -3 }, 20);
	player.SetAnchorOffset({ 0, -3 }, 21);
	player.SetAnchorOffset({ 0, -3 }, 22);
	player.SetAnchorOffset({ 0, -3 }, 23);
	player.SetAnchorOffset({ 0, -3 }, 24);
	player.SetAnchorOffset({ 0, -3 }, 25);
	player.SetAnchorOffset({ 0, -3 }, 26);

	//down attack 27-32
	player.SetSpriteClip(406, 46, 45, 45, 27);
	player.SetSpriteClip(451, 46, 45, 45, 28);
	player.SetSpriteClip(496, 46, 45, 45, 29);
	player.SetSpriteClip(541, 46, 45, 45, 30);
	player.SetSpriteClip(586, 46, 45, 45, 31);
	player.SetSpriteClip(631, 46, 45, 45, 32);

	player.SetAnchorOffset({ 0, 0 }, 27);
	player.SetAnchorOffset({ 0, 0 }, 28);
	player.SetAnchorOffset({ 0, 0 }, 29);
	player.SetAnchorOffset({ 0, 0 }, 30);
	player.SetAnchorOffset({ 0, 0 }, 31);
	player.SetAnchorOffset({ 0, 0 }, 32);

	//up move 33-39
	player.SetSpriteClip(0, 91, 45, 45, 33);
	player.SetSpriteClip(46, 91, 45, 45, 34);
	player.SetSpriteClip(91, 91, 45, 45, 35);
	player.SetSpriteClip(136, 91, 45, 45, 36);
	player.SetSpriteClip(181, 91, 45, 45, 37);
	player.SetSpriteClip(226, 91, 45, 45, 38);
	player.SetSpriteClip(271, 91, 45, 45, 39);

	player.SetAnchorOffset({ -5, 0 }, 33);
	player.SetAnchorOffset({ -5, 0 }, 34);
	player.SetAnchorOffset({ -5, 0 }, 35);
	player.SetAnchorOffset({ -5, 0 }, 36);
	player.SetAnchorOffset({ -5, 0 }, 37);
	player.SetAnchorOffset({ -5, 0 }, 38);
	player.SetAnchorOffset({ -5, 0 }, 39);

	//left move 40-47
	player.SetSpriteClip(316, 91, 45, 45, 40);
	player.SetSpriteClip(361, 91, 45, 45, 41);
	player.SetSpriteClip(406, 91, 45, 45, 42);
	player.SetSpriteClip(451, 91, 45, 45, 43);
	player.SetSpriteClip(496, 91, 45, 45, 44);
	player.SetSpriteClip(541, 91, 45, 45, 45);
	player.SetSpriteClip(586, 91, 45, 45, 46);

	player.SetAnchorOffset({ 0, 0 }, 40);
	player.SetAnchorOffset({ 0, 0 }, 41);
	player.SetAnchorOffset({ 0, 0 }, 42);
	player.SetAnchorOffset({ 0, 0 }, 43);
	player.SetAnchorOffset({ 0, 0 }, 44);
	player.SetAnchorOffset({ 0, 0 }, 45);
	player.SetAnchorOffset({ 0, 0 }, 46);

	//right move 48-54
	player.SetSpriteClip(631, 91, 45, 45, 48);
	player.SetSpriteClip(676, 91, 45, 45, 49);
	player.SetSpriteClip(721, 91, 45, 45, 50);
	player.SetSpriteClip(766, 91, 45, 45, 51);
	player.SetSpriteClip(811, 91, 45, 45, 52);
	player.SetSpriteClip(856, 91, 45, 45, 53);
	player.SetSpriteClip(901, 91, 45, 45, 54);

	player.SetAnchorOffset({ -5, 0 }, 48);
	player.SetAnchorOffset({ -5, 0 }, 49);
	player.SetAnchorOffset({ -5, 0 }, 50);
	player.SetAnchorOffset({ -5, 0 }, 51);
	player.SetAnchorOffset({ -5, 0 }, 52);
	player.SetAnchorOffset({ -5, 0 }, 53);
	player.SetAnchorOffset({ -5, 0 }, 54);

	//down move 55-61
	player.SetSpriteClip(0, 136, 45, 45, 55);
	player.SetSpriteClip(46, 136, 45, 45, 56);
	player.SetSpriteClip(91, 136, 45, 45, 57);
	player.SetSpriteClip(136, 136, 45, 45, 58);
	player.SetSpriteClip(181, 136, 45, 45, 59);
	player.SetSpriteClip(226, 136, 45, 45, 60);
	player.SetSpriteClip(271, 136, 45, 45, 61);

	player.SetAnchorOffset({ -5, 0 }, 55);
	player.SetAnchorOffset({ -5, 0 }, 56);
	player.SetAnchorOffset({ -5, 0 }, 57);
	player.SetAnchorOffset({ -5, 0 }, 58);
	player.SetAnchorOffset({ -5, 0 }, 59);
	player.SetAnchorOffset({ -5, 0 }, 60);
	player.SetAnchorOffset({ -5, 0 }, 61);


	player.ConfigureCollision(true, true, { 10,10 }, { 17,15 });				//Player Collision
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

	//NPC GUARD
	guard.SetTexturePath("textures/link_walk_attack.png");
	sdlInit.LoadTexture(guard);
	guard.SetPosition({ 350,200 });
	guard.SetSize(45, 45);
	guard.InitSpriteSheet(0, 21, 4);

	//up move 33-39
	guard.SetSpriteClip(0, 91, 45, 45, 33);
	guard.SetSpriteClip(46, 91, 45, 45, 34);
	guard.SetSpriteClip(91, 91, 45, 45, 35);
	guard.SetSpriteClip(136, 91, 45, 45, 36);
	guard.SetSpriteClip(181, 91, 45, 45, 37);
	guard.SetSpriteClip(226, 91, 45, 45, 38);
	guard.SetSpriteClip(271, 91, 45, 45, 39);
	
	guard.SetAnchorOffset({ -5, 0 }, 33);
	guard.SetAnchorOffset({ -5, 0 }, 34);
	guard.SetAnchorOffset({ -5, 0 }, 35);
	guard.SetAnchorOffset({ -5, 0 }, 36);
	guard.SetAnchorOffset({ -5, 0 }, 37);
	guard.SetAnchorOffset({ -5, 0 }, 38);
	guard.SetAnchorOffset({ -5, 0 }, 39);

	//left move 40-47
	guard.SetSpriteClip(316, 91, 45, 45, 40);
	guard.SetSpriteClip(361, 91, 45, 45, 41);
	guard.SetSpriteClip(406, 91, 45, 45, 42);
	guard.SetSpriteClip(451, 91, 45, 45, 43);
	guard.SetSpriteClip(496, 91, 45, 45, 44);
	guard.SetSpriteClip(541, 91, 45, 45, 45);
	guard.SetSpriteClip(586, 91, 45, 45, 46);
	
	guard.SetAnchorOffset({ 0, 0 }, 40);
	guard.SetAnchorOffset({ 0, 0 }, 41);
	guard.SetAnchorOffset({ 0, 0 }, 42);
	guard.SetAnchorOffset({ 0, 0 }, 43);
	guard.SetAnchorOffset({ 0, 0 }, 44);
	guard.SetAnchorOffset({ 0, 0 }, 45);
	guard.SetAnchorOffset({ 0, 0 }, 46);

	//right move 48-54
	guard.SetSpriteClip(631, 91, 45, 45, 48);
	guard.SetSpriteClip(676, 91, 45, 45, 49);
	guard.SetSpriteClip(721, 91, 45, 45, 50);
	guard.SetSpriteClip(766, 91, 45, 45, 51);
	guard.SetSpriteClip(811, 91, 45, 45, 52);
	guard.SetSpriteClip(856, 91, 45, 45, 53);
	guard.SetSpriteClip(901, 91, 45, 45, 54);
	
	guard.SetAnchorOffset({ -5, 0 }, 48);
	guard.SetAnchorOffset({ -5, 0 }, 49);
	guard.SetAnchorOffset({ -5, 0 }, 50);
	guard.SetAnchorOffset({ -5, 0 }, 51);
	guard.SetAnchorOffset({ -5, 0 }, 52);
	guard.SetAnchorOffset({ -5, 0 }, 53);
	guard.SetAnchorOffset({ -5, 0 }, 54);

	//down move 55-61
	guard.SetSpriteClip(0, 136, 45, 45, 55);
	guard.SetSpriteClip(46, 136, 45, 45, 56);
	guard.SetSpriteClip(91, 136, 45, 45, 57);
	guard.SetSpriteClip(136, 136, 45, 45, 58);
	guard.SetSpriteClip(181, 136, 45, 45, 59);
	guard.SetSpriteClip(226, 136, 45, 45, 60);
	guard.SetSpriteClip(271, 136, 45, 45, 61);
	
	guard.SetAnchorOffset({ -5, 0 }, 55);
	guard.SetAnchorOffset({ -5, 0 }, 56);
	guard.SetAnchorOffset({ -5, 0 }, 57);
	guard.SetAnchorOffset({ -5, 0 }, 58);
	guard.SetAnchorOffset({ -5, 0 }, 59);
	guard.SetAnchorOffset({ -5, 0 }, 60);
	guard.SetAnchorOffset({ -5, 0 }, 61);

	guard.ConfigureCollision(true, true, { 10, 10 }, { 17,15 });

	guard.AddCollidableEntity(tree);										//Player/Sprite Collision
	guard.AddCollidableEntity(tree2);										//Player/Sprite Collision
	guard.AddCollidableEntity(redHouse1);									//Player/Sprite Collision
	guard.AddCollidableEntity(redHouse2);									//Player/Sprite Collision
	guard.AddCollidableEntity(blueHouse2);									//Player/Sprite Collision
	guard.AddCollidableEntity(blueHouse3);									//Player/Sprite Collision
	guard.AddCollidableEntity(blocker);									//Player/Sprite Collision
	guard.AddCollidableEntity(blocker2);									//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeTopLeft);								//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeTopLeftSide);							//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeBottomLeft);							//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeBottomLeftSide);						//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeBottomRight);							//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeBottomRightSide);						//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeTopRight);								//Player/Sprite Collision
	guard.AddCollidableEntity(hedgeTopRightSide);							//Player/Sprite Collision
	guard.AddCollidableEntity(statueBird);									//Player/Sprite Collision
	guard.AddCollidableEntity(house2BlackDoor);							//Player/Sprite Collision
	guard.AddCollidableEntity(bldgInsideBlkDoor);							//Player/Sprite Collision
	guard.AddCollidableEntity(houseToInside);								//Player/Sprite Collision
	guard.AddCollidableEntity(houseToOutside);								//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder1);						//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder2);						//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder3);						//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder4);						//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder5);						//Player/Sprite Collision
	guard.AddCollidableEntity(blockerHouseBorder6);						//Player/Sprite Collision
	guard.AddCollidableEntity(guyInBed);									//Player/Sprite Collision
	guard.AddCollidableEntity(witch);										//Player/Sprite Collision
	guard.AddCollidableEntity(sawGuys);									//Player/Sprite Collision
	guard.AddCollidableEntity(horizLongbush);								//Player/Sprite Collision

	//SPRITE DESERT CASTLE INSIDE
	Map.SetTexturePath("textures/LightWorld.png");				//Sprite Texture Path
	sdlInit.LoadTexture(Map);									//Sprite Texture Load
	Map.SetPosition({ 0,0 });								//Sprite Position
	Map.SetSize(4110, 4121);										//sprite Size
	Map.ConfigureCollision(true, false);							//Sprite Collision


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
	gWorld.InitWorldGrid({ 0,70 - 25,14,70 - 10 });
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
	sdlInit.CleanupSprite(guard);
	sdlInit.CleanupSprite(Map);
	sdlInit.Cleanup();
}
void GameManager::Update() {
/*************************************************				UPDATE				**************************************************/
	if (ls == LIGHTWORLD) {
		player.Update();									//Players Update Call
		guard.Update();
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
		sdlInit.DrawSprite(Map);
	//	sdlInit.DrawSprite(ground1);						//Render Sprite Under Player
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
		sdlInit.DrawSprite(guard);							//Render Sprite Above Player
		//weatherSystem.Render();
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
		sdlInit.DrawEntityCollider(guard);
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