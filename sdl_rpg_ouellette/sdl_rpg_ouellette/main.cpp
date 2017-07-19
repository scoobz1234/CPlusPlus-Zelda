// include the sdl and studio header files
#include <SDL.h>
#include <stdio.h>
// set the screen width and screen heights
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// the main function!

// argument c is argument count, and args is your actual arguments
int main(int argc, char* args[]) {
	// The window we'll render to
	SDL_Window* window = NULL;
	
	//The surface contained byt he window 
	SDL_Surface* screenSurface = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

	}
	else {
		//Create your window
		window = SDL_CreateWindow("A Zelda Knock-Off", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//if the window can't be created print the error
		if (window == NULL) {
			printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
		}
		else {
		
		}



		// Get window surface ...
		screenSurface = SDL_GetWindowSurface(window);

		//
	}

	return 0;
}