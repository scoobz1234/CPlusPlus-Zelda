#include "Sound.h"
#include <iostream>

#define MILLI_PER_SEC 1000.f
//In milliseconds...
float gDeltaTime = 0.f;

//Checked in main...
bool gQuitGame = false;


//Mix_PlayChannel(-1, SFX, 0);
//if (Mix_PlayChannel(-1, SFX, 0) == -1) {
//	printf("Mix_PlayChannel: %s\n", Mix_GetError());
//}
//	// may be critical error, or maybe just no channels were free.
//	// you could allocated another channel in that case...
//
//if (!Mix_PlayingMusic()) {
//	Mix_PlayMusic(BGMusic, -1);
//}
//else if (Mix_PausedMusic()) {
//	Mix_ResumeMusic();
//}
//else {
//	Mix_PauseMusic();
//}
//break;
//case SDLK_n: Mix_HaltMusic(); break;
//default: break;
//}
//Initialize SDL_mixer
//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//	success = false;
//}
//
//else {
//	SFX = Mix_LoadWAV("music/golden_sword.wav");
//	BGMusic = Mix_LoadMUS("music/village.it");
//}

void Sound::SetupSoundChunk() {

}
void Sound::SetupBGMusic() {

}

bool Sound::Setup() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize Audio! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

void Sound::Update() {
	//Updating gDeltaTime in milliseconds...
	static Uint32 lastTime = 0;
	Uint32 runningTime = SDL_GetTicks();
	gDeltaTime = (runningTime - lastTime) / MILLI_PER_SEC;
	lastTime = runningTime;

	//Checks for key presses...
	//HandleKeyboardEvents();

}

void Sound::Cleanup() {
	Mix_FreeMusic(BGMusic);
	Mix_FreeMusic(BGMusic2);
	Mix_FreeChunk(SFX);
	Mix_FreeChunk(SFX2);

	BGMusic = nullptr;
	BGMusic2 = nullptr;
	SFX = nullptr;
	SFX2 = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}



