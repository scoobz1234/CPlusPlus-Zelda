#include "SDLInit.h"
#include "Camera.h"
#include <iostream>

#define MILLI_PER_SEC 1000.f

#define BG_R 0x4b
#define BG_G 0x9a
#define BG_B 0x49
#define BG_A 0xFF

extern Camera gCamera;

//Also camera dimension...
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//Music and Sound loading...
Mix_Music *villageMusic = Mix_LoadMUS("music/village.it");
Mix_Chunk *swordSound = Mix_LoadWAV("music/golden_sword.it");    //why the hell will you not work!!!


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//In milliseconds...
float gDeltaTime = 0.f;

//Checked in main...
bool gQuitGame = false;

								//Keys held down...
int gHorizKeysHeld = 0;			//keys a and d
int gVertKeysHeld = 0;			//keys w and s

								//Keys pressed...
bool gFirstKeyDown = false;		//keys 1
bool gSecondKeyDown = false;	//keys 2
bool gThirdKeyDown = false;		//keys 3
bool gFourthKeyDown = false;	//keys 4
bool gIKeyDown = false;			//keys I

								//Keys released...
bool gFirstKeyUp = false;		//keys 1
bool gSecondKeyUp = false;		//keys 2
bool gThirdKeyUp = false;		//keys 3
bool gFourthKeyUp = false;		//keys 4
bool gIKeyUp = false;			//keys I



namespace {
	SDL_Event event;
}

void HandleKeyboardEvents() {
	//Reset pressed keys here...
	gFirstKeyDown = false;
	gSecondKeyDown = false;
	gThirdKeyDown = false;
	gFourthKeyDown = false;
	//gIKeyDown = false;
	
	//Reset released keys here...
	gFirstKeyUp = false;
	gSecondKeyUp = false;
	gThirdKeyUp = false;
	gFourthKeyUp = false;
	//gIKeyUp = false;
	/* Poll for events */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
		case SDL_KEYDOWN:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
					//Keys held down...
				case SDLK_w: gVertKeysHeld -= 1; break;		//up...
				case SDLK_UP: gVertKeysHeld -= 1; break;    //up....
				case SDLK_s: gVertKeysHeld += 1; break;		//down...
				case SDLK_DOWN: gVertKeysHeld += 1; break;  //down...
				case SDLK_a: gHorizKeysHeld -= 1; break;	//left...
				case SDLK_LEFT: gHorizKeysHeld -= 1; break; //left...
				case SDLK_d: gHorizKeysHeld += 1; break;	//right...
				case SDLK_RIGHT: gHorizKeysHeld += 1; break; //right...
				case SDLK_e: 
					Mix_PlayChannel(-1, swordSound, 0);
					if (Mix_PlayChannel(-1, swordSound, 0) == -1) {
					printf("Mix_PlayChannel: %s\n", Mix_GetError());
					// may be critical error, or maybe just no channels were free.
					// you could allocated another channel in that case...
				} gFirstKeyDown = true; break;
				case SDLK_2: gSecondKeyDown = true; break;
				case SDLK_3: gThirdKeyDown = true; break;
				case SDLK_4: gFourthKeyDown = true; break;
				case SDLK_i: gIKeyDown = !gIKeyDown; break;
				case SDLK_m: 
					if (!Mix_PlayingMusic())
						Mix_PlayMusic(villageMusic, -1);
					else if (Mix_PausedMusic())
						Mix_ResumeMusic();
					else
						Mix_PauseMusic();
					break;
				case SDLK_n:
					Mix_HaltMusic();
					break;
				default: break;
				}
			}
			break;

		case SDL_KEYUP:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
					//Keys held down...
				case SDLK_w: gVertKeysHeld += 1; break;		//up...
				case SDLK_UP: gVertKeysHeld += 1; break;    //up....
				case SDLK_s: gVertKeysHeld -= 1; break;		//down...
				case SDLK_DOWN: gVertKeysHeld -= 1; break;  //down...
				case SDLK_a: gHorizKeysHeld += 1; break;	//left...
				case SDLK_LEFT: gHorizKeysHeld += 1; break; //left...
				case SDLK_d: gHorizKeysHeld -= 1; break;	//right...
				case SDLK_RIGHT: gHorizKeysHeld -= 1; break; //right
															//Keys released...
				case SDLK_e: gFirstKeyUp = true; break;
				case SDLK_2: gSecondKeyUp = true; break;
				case SDLK_3: gThirdKeyUp = true; break;
				case SDLK_4: gFourthKeyUp = true; break;
				//case SDLK_i: gIKeyUp = true; break;
				default: break;
				}
			}

			break;

			/* SDL_QUIT event (window close) */
		case SDL_QUIT:
			gQuitGame = true;
			break;

		default:
			break;
		}
	}
}

bool SDLInit::Setup() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window				//TODO: Make this name global...
		gWindow = SDL_CreateWindow("Dragon Ball O!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				else {
					SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				}
			}
		}
	}

	return success;
}


void SDLInit::LoadTexture(Sprite &sprite) {
	//This is how we get our file name...
	const char* filePath = sprite.mTexturePath;

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filePath);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
		}
		else {	//get image dimensions. Can call Entity.SetSize to override...
			sprite.mSize.x = loadedSurface->w;
			sprite.mSize.y = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	sprite.mTexture = newTexture;
}

void SDLInit::SetColor(Sprite &sprite, Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(sprite.mTexture, red, green, blue);
}

void SDLInit::SetBlendMode(Sprite &sprite, SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(sprite.mTexture, blending);
}

void SDLInit::SetAlpha(Sprite &sprite, Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(sprite.mTexture, alpha);
}

void SDLInit::CleanupSprite(Sprite &sprite) {
	SDL_DestroyTexture(sprite.mTexture);
	sprite.mTexture = NULL;
}

void SDLInit::DrawSprite(Sprite &sprite) {
	//Set rendering space and render to screen
	SDL_Rect renderRect = {
		int(sprite.mPos.x - gCamera.mPos.x),
		int(sprite.mPos.y - gCamera.mPos.y),
		sprite.mSize.x, sprite.mSize.y
	};

	auto *anchorOffset = sprite.GetAnchorOffset();

	//If the sprite size changes, the sprite will move. This offset
	//	is for anchoring the sprite, so that it doesn't move.
	if (anchorOffset != NULL) {
		renderRect.x += anchorOffset->x;
		renderRect.y += anchorOffset->y;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, sprite.mTexture,
		sprite.GetSpriteClip(), &renderRect);
}

void SDLInit::DrawHud(Sprite &sprite) {
	//Set rendering space and render to screen
	SDL_Rect renderRect = {
		int(sprite.mPos.x),
		int(sprite.mPos.y),
		sprite.mSize.x, sprite.mSize.y
	};

	auto *anchorOffset = sprite.GetAnchorOffset();

	//If the sprite size changes, the sprite will move. This offset
	//	is for anchoring the sprite, so that it doesn't move.
	if (anchorOffset != NULL) {
		renderRect.x += anchorOffset->x;
		renderRect.y += anchorOffset->y;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, sprite.mTexture,
		sprite.GetSpriteClip(), &renderRect);
}

void SDLInit::DrawWeather(Sprite &sprite) {
	//Set rendering space and render to screen
	SDL_Rect renderRect = {
		int(sprite.mPos.x),
		int(sprite.mPos.y),
		sprite.mSize.x, sprite.mSize.y
	};

	auto *anchorOffset = sprite.GetAnchorOffset();

	//If the sprite size changes, the sprite will move. This offset
	//	is for anchoring the sprite, so that it doesn't move.
	if (anchorOffset != NULL) {
		renderRect.x += anchorOffset->x;
		renderRect.y += anchorOffset->y;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, sprite.mTexture,
		sprite.GetSpriteClip(), &renderRect);
}

void SDLInit::DrawEntityCollider(Entity &entity) {
	if (entity.mHasCollided) {
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 32, 48);
		//TODO: Not the best place to put this, but works...
		entity.mHasCollided = false;
		entity.mPushbackSides = 0;
	}
	else {
		SDL_SetRenderDrawColor(gRenderer, 32, 0, 255, 48);
	}

	SDL_Rect rectangle;

	rectangle.x = int(entity.mPos.x + entity.mTopLeftCollOffset.x - gCamera.mPos.x);
	rectangle.y = int(entity.mPos.y + entity.mTopLeftCollOffset.y - gCamera.mPos.y);
	rectangle.w = int(entity.mSize.x - entity.mTopLeftCollOffset.x - entity.mBottomRightCollOffset.x);
	rectangle.h = int(entity.mSize.y - entity.mTopLeftCollOffset.y - entity.mBottomRightCollOffset.y);
	SDL_RenderFillRect(gRenderer, &rectangle);
}

void SDLInit::Render() {
	//Clear screen	68B13A
	SDL_SetRenderDrawColor(gRenderer, BG_R, BG_G, BG_B, BG_A);
	SDL_RenderClear(gRenderer);
}

//TODO: add delta time to update...
void SDLInit::Update() {
	//Updating gDeltaTime in milliseconds...
	static Uint32 lastTime = 0;
	Uint32 runningTime = SDL_GetTicks();
	gDeltaTime = (runningTime - lastTime) / MILLI_PER_SEC;
	lastTime = runningTime;

	//Checks for key presses...
	HandleKeyboardEvents();

	//Update screen
	SDL_RenderPresent(gRenderer);

	//Wait two seconds
	//SDL_Delay( 2000 );
}

void SDLInit::Cleanup() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	Mix_FreeMusic(villageMusic);
	Mix_FreeChunk(swordSound);

	gWindow = NULL;
	gRenderer = NULL;
	villageMusic = nullptr;
	swordSound = nullptr;
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}