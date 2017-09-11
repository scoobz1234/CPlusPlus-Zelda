#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "Sprite.h"

class Sound {

public:

	void Update();

	void Cleanup();

private:
	//Music and Sound loading...
	Mix_Music *BGMusic = NULL;
	Mix_Music *BGMusic2 = NULL;
	Mix_Chunk *SFX = NULL;
	Mix_Chunk *SFX2 = NULL;

	void SetupSoundChunk();

	void SetupBGMusic();

	bool Setup();

};

