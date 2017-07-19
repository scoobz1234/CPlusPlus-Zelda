#include "SDLInit.h"

//Screen dimension constants
#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 480

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

bool SDLInit::Setup() {
	bool success = true;

//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %n\n", SDL_GetError());
		success = false;
	}
	else {
//Create the window	
		window = SDL_CreateWindow("Zelda Rip-Off!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

//Fill the surface white
			Uint32 color = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
			if (SDL_FillRect(screenSurface, NULL, color) < 0) {
				printf("SDL rect could not be filled! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}

	return success;
}

void SDLInit::Update() {
//Update the surface
	SDL_UpdateWindowSurface(window);
}

bool SDLInit::Cleanup() {
	bool initSuccess = true;

//Destroy window
	SDL_DestroyWindow(window);

//Quit SDL subsystem
	SDL_Quit();

	return initSuccess;
}