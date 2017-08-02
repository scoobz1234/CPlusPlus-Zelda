//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Entity.h"

class SDLInit{

	public:
		bool Setup();

		void LoadTexture(Entity &entity);

		void SetColor(Entity &entity, Uint8 red, Uint8 green, Uint8 blue);
		void SetBlendMode(Entity &entity, SDL_BlendMode blending);
		void SetAlpha(Entity &entity, Uint8 alpha);

		void DrawTexture(Entity &entity);

		void Render();
		void Update();

		void CleanupTexture(Entity &entity);
		void Cleanup();

	private:
		SDL_Rect *mDstRect = NULL;
		SDL_Rect *mSrcRect = NULL;
};