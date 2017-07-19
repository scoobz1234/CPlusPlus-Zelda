//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#pragma once

class SDLInit{

	public:
		bool Setup();
		bool Cleanup();
		void Update();
};