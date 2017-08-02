#pragma once
#include <string>
#include <SDL_image.h>

class Entity{

friend class SDLInit;
using uInt = unsigned int;

public:
	void SetTexturePath(const char* texturePath);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);

	//Call InitSPriteSheet before calling SetSpriteClip...
	void InitSpriteSheet(uInt startClipIndex, uInt numSpriteCLipsX, uInt numSpriteClipsY);
	void SetSpriteClip(int x, int y, uInt w, uInt h, uInt index);

	SDL_Rect* GetSpriteClip();

protected:
	//The actual hardware texture
	SDL_Texture* mTexture;
	const char* mTexturePath;

	int mXPos{0}, mYPos{0};
	int mWidth{0}, mHeight{0};

	int mSpriteClipIndex{0};
	int mNumSpriteClips{0};
	int mNumSpriteClipsX{0};
	int mNumSpriteClipsY{0};

	SDL_Rect *mSpriteCLips = NULL;
};