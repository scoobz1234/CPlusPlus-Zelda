#include "Player.h"

#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2

extern int gHorizVelocity;
extern int gVertVelocity;

namespace {
	//Animation index information...
	int animRightIndex = 0;
	int animLeftIndex = 0;
	int animUpIndex = 0;
	int animDownIndex = 0;

	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 4, 18};
	int animLeftIndices[ANIM_LEFT_COUNT] = { 2, 16 };
	int animUpIndices[ANIM_UP_COUNT] = { 3, 17 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 1, 15 };
}

void Player::Move() {
	//Update position...
	mXPos += gHorizVelocity;
	mYPos += gVertVelocity;

	//Update animation...	//TODO: make this better with animations...
	if (gHorizVelocity > 0) {
		animRightIndex = (animRightIndex + 1) % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[animRightIndex];
	}
	else if (gHorizVelocity < 0) {
		animLeftIndex = (animLeftIndex + 1) % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[animLeftIndex];
	}
	else if (gVertVelocity > 0) {
		animDownIndex = (animDownIndex + 1) % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[animDownIndex];
	}
	else if (gVertVelocity < 0) {
		animUpIndex = (animUpIndex + 1) % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[animUpIndex];
	}
}