#include "Entity.h"

Entity::~Entity() {
	if (mSpriteCLips == nullptr) {
		delete[] mSpriteCLips;
		mSpriteCLips = nullptr;
	}

	if (mAnchorOffsets == nullptr) {
		delete[] mAnchorOffsets;
		mAnchorOffsets = nullptr;
	}
}

void Entity::SetTexturePath(const char* texturePath) {
	mTexturePath = texturePath;
}

void Entity::SetPosition(float x, float y) {
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
	mAnchorOffsets = new Int2[mNumSpriteClips];
	mSpriteClipIndex = startClipIndex;
}

/************************************************************************/
/* 	Sprite clip is used to render texture coordinates (for sprite
sheets)
/************************************************************************/
void Entity::SetSpriteClip(int x, int y, uInt w, uInt h, uInt index) {
	if (mSpriteCLips == NULL) {
		printf("Cannot set sprite clip. Please call InitSpriteSheet first.");
		return;
	}

	int i = index % mNumSpriteClips;
	mSpriteCLips[i].x = x; mSpriteCLips[i].y = y;
	mSpriteCLips[i].w = w; mSpriteCLips[i].h = h;
}

/************************************************************************/
/* 	If the sprite size changes, the sprite will move. This offset
is for anchoring the sprite, so that it doesn't move.
/************************************************************************/
void Entity::SetAnchorOffset(Int2 anchorOffset, uInt index) {
	if (mAnchorOffsets == NULL) {
		printf("Cannot set clip offset. Please call InitSpriteSheet first.");
		return;
	}

	int i = index % mNumSpriteClips;
	mAnchorOffsets[i] = anchorOffset;
}

bool Entity::CheckCollision(Entity &other) {
	float leftDist = other.mXPos - mXPos + mOriginOffset.x;
	float upDist = other.mYPos - mYPos + mOriginOffset.y;
	float rightDist = (mXPos + mWidth) - ((other.mXPos - mColliderOffset.x) + (other.mWidth - mColliderOffset.x));
	float downDist = (mYPos + mHeight) - ((other.mYPos - mColliderOffset.y) + (other.mHeight - mColliderOffset.y));

	bool collidesHoriz = (rightDist < mWidth && leftDist < mWidth);
	bool collidesVert = (downDist < mHeight && upDist < mHeight);
	bool hasCollided = collidesHoriz && collidesVert;

	//Handle push back...
	if (hasCollided && mCollisionBlocks) {
		//push left...
		if (leftDist < rightDist && leftDist < upDist && leftDist < downDist) {
			other.mXPos -= mWidth - rightDist;
		}	//push right...
		else if (rightDist < upDist && rightDist < downDist) {
			other.mXPos += mWidth - leftDist;
		}	//push up...
		else if (upDist < downDist) {
			other.mYPos -= mHeight - downDist;
		}	//push down...
		else {
			other.mYPos += mHeight - upDist;
		}
	}

	return hasCollided;
}

/************************************************************************/
/* 	Sprite clip is used to render texture coordinates (for sprite
sheets)
/************************************************************************/
SDL_Rect* Entity::GetSpriteClip() {
	return mSpriteCLips + mSpriteClipIndex;
}

/************************************************************************/
/* 	If the sprite size changes, the sprite will move. This offset
is for anchoring the sprite, so that it doesn't move.
/************************************************************************/
Entity::Int2* Entity::GetAnchorOffset() {
	return mAnchorOffsets + mSpriteClipIndex;
}