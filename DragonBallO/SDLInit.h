//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Sprite.h"

class SDLInit {

public:
	bool Setup();

	void LoadTexture(Sprite &sprite);

	void SetColor(Sprite &sprite, Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(Sprite &sprite, SDL_BlendMode blending);
	void SetAlpha(Sprite &sprite, Uint8 alpha);

	void DrawSprite(Sprite &sprite);
	void DrawEntityCollider(Entity &entity);

	void Render();
	void Update();

	void CleanupSprite(Sprite &sprite);
	void Cleanup();

private:
	SDL_Rect *mDstRect = NULL;
	SDL_Rect *mSrcRect = NULL;
};