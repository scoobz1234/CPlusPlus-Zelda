#include "SDLInit.h"

#define BG_R 0x68
#define BG_G 0xB1
#define BG_B 0x38
#define BG_A 0xFF

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Checked in main...
bool gQuitGame = false;

//Key input...
int gHorizVelocity = 0;
int gVertVelocity = 0;

namespace {
	SDL_Event event;
}

void HandleKeyboardEvents() {
	/* Poll for events */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
		case SDL_KEYDOWN:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
					case SDLK_w: gVertVelocity -= 1; break;		//up...
					case SDLK_s: gVertVelocity += 1; break;		//down...
					case SDLK_a: gHorizVelocity -= 1; break;	//left...
					case SDLK_d: gHorizVelocity += 1; break;	//right...
					default: break;
				}
			}
			break;

		case SDL_KEYUP:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
				case SDLK_w: gVertVelocity += 1; break;		//up...
				case SDLK_s: gVertVelocity -= 1; break;		//down...
				case SDLK_a: gHorizVelocity += 1; break;	//left...
				case SDLK_d: gHorizVelocity -= 1; break;	//right...
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

bool SDLInit::Setup(){
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window				//TODO: Make this name global...
		gWindow = SDL_CreateWindow( "Dragon Ball O!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
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
			}
		}
	}

	return success;
}

void SDLInit::LoadTexture(Entity &entity) {
	//This is how we get our file name...
	const char* filePath = entity.mTexturePath;

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
			entity.mWidth = loadedSurface->w;
			entity.mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	entity.mTexture = newTexture;
}

void SDLInit::SetColor(Entity &entity, Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(entity.mTexture, red, green, blue);
}

void SDLInit::SetBlendMode(Entity &entity, SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(entity.mTexture, blending);
}

void SDLInit::SetAlpha(Entity &entity, Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(entity.mTexture, alpha);
}

void SDLInit::CleanupTexture(Entity &entity) {
	SDL_DestroyTexture(entity.mTexture);
	entity.mTexture = NULL;
}

void SDLInit::DrawTexture(Entity &entity) {
	//Set rendering space and render to screen
	SDL_Rect renderRect = {entity.mXPos, entity.mYPos,
		entity.mWidth, entity.mHeight };

	////Set clip rendering dimensions
	//if (clip != NULL) {
	//	renderQuad.w = clip->w;
	//	renderQuad.h = clip->h;
	//}

	//Render to screen
	SDL_RenderCopy(gRenderer, entity.mTexture,
		entity.GetSpriteClip(), &renderRect);
}

void SDLInit::Render() {
	//Clear screen	68B13A
	SDL_SetRenderDrawColor(gRenderer, BG_R, BG_G, BG_B, BG_A);
	SDL_RenderClear(gRenderer);
}

//TODO: add delta time to update...
void SDLInit::Update(){
	//Checks for key presses...
	HandleKeyboardEvents();

	//Update screen
	SDL_RenderPresent(gRenderer);

	SDL_Delay(4);
	//Wait two seconds
	//SDL_Delay( 2000 );
}

void SDLInit::Cleanup(){
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}