#include "Entity.h"

void Entity::SetTexturePath(const char* texturePath) {
	mTexturePath = texturePath;
}

void Entity::SetPosition(int x, int y) {
	mXPos = x;
	mYPos = y;
}

void Entity::SetSize(int width, int height) {
	mWidth = width;
	mHeight = height;
}

void Entity::InitSpriteSheet(uInt startClipIndex, uInt numSpriteCLipsX, uInt numSpriteClipsY) {
	if (numSpriteCLipsX == 0 || numSpriteClipsY == 0) {
		printf("Number of sprite clips must be at least 1.");
		return;
	}

	mNumSpriteClips = numSpriteCLipsX * numSpriteClipsY;
	mNumSpriteClipsX = numSpriteCLipsX;
	mNumSpriteClipsY = numSpriteClipsY;

	mSpriteCLips = new SDL_Rect[mNumSpriteClips];
	mSpriteClipIndex = startClipIndex;
}

void Entity::SetSpriteClip(int x, int y, uInt w, uInt h, uInt index) {
	if (mSpriteCLips == NULL) {
		printf("Cannot set sprite clip. Please call InitSpriteSheet first.");
		return;
	}

	int i = index % mNumSpriteClips;
	mSpriteCLips[i].x = x; mSpriteCLips[i].y = y;
	mSpriteCLips[i].w = w; mSpriteCLips[i].h = h;
}

SDL_Rect* Entity::GetSpriteClip() {
	return mSpriteCLips + mSpriteClipIndex;
}