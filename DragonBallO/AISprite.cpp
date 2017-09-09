#include "AISprite.h"
#include <iostream>
extern float gDeltaTime;

void AISprite::Update() {
	StaticSpriteSwapping();
	Sprite::Update();
}

//functions to set indices and counts for swaps and movements...
void AISprite::SetAnimSwapIndices(int count,float animSpeed,int * indices) {
	numSwapIndices = count;
	swapIndices = indices;
	animSwapSpeed = animSpeed;
}

//swaps sprites staticly..
void AISprite::StaticSpriteSwapping() {
		swapTimer += animSwapSpeed * gDeltaTime;
		int i = (int)swapTimer % numSwapIndices;
		mSpriteClipIndex = swapIndices[i];
	}