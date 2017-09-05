#include "AIHandler.h"
#include "Camera.h"

#define GUY_IN_BED_ANIM 2
#define WITCH 7

extern float gDeltaTime;
extern Camera gCamera;

bool animate = true;

namespace {
	//Animation timers...
	float guyInBedTimer = .0f;
	float witchTimer = .0f;

	//Animation speeds...
	float animGuyInBedSpeed = .2;
	float animWitchSpeed = 3;

	//Animation indices...
	int guyInBedAnim[GUY_IN_BED_ANIM] = {1,2};
	int witch[WITCH] = {1,2,3,4,5,6,7};

}

void AIHandler::Update() {
	
	if (animate) {
		GuyInBed();
	}
	else if (!animate) {
		Witch();
	}

	Sprite::Update();

}

void AIHandler::GuyInBed() {
		guyInBedTimer += animGuyInBedSpeed * gDeltaTime;

		int index = (int)guyInBedTimer % GUY_IN_BED_ANIM;
		mSpriteClipIndex = guyInBedAnim[index];
		animate = false;
}

void AIHandler::Witch() {
		witchTimer += animWitchSpeed * gDeltaTime;

		int i = (int)witchTimer % WITCH;
		mSpriteClipIndex = witch[i];
		animate = true;
}