#include "AIHandler.h"
#include "MyMath.h"

#define GUY_IN_BED_ANIM 2
#define WITCH 7
#define SAWGUYS 3

extern float gDeltaTime;



namespace {
	//Animation timers...
	float guyInBedTimer = .0f;
	float witchTimer = .0f;
	float sawGuysTimer = .0f;
	
	//Animation speeds...
	float animGuyInBedSpeed = .2;
	float animWitchSpeed = 3;
	float animSawGuysSpeed = 1;

	//Animation indices...
	int guyInBedAnim[GUY_IN_BED_ANIM] = {1,2};
	int witchAnim[WITCH] = {1,2,3,4,5,6,7};
	int sawGuysAnim[SAWGUYS] = { 1,2,3 };

}

void AIHandler::Update() {
	
		GuyInBed();

}

void AIHandler::GuyInBed() {
		guyInBedTimer += animGuyInBedSpeed * gDeltaTime;

		int index = ((int)guyInBedTimer) % GUY_IN_BED_ANIM;
		mAISpriteClipIndex = guyInBedAnim[index];
}

void AIHandler::Witch() {
		witchTimer += animWitchSpeed * gDeltaTime;

		int i = ((int)witchTimer) % WITCH;
		mAISpriteClipIndex = witchAnim[i];
}

void AIHandler::SawGuys() {
	sawGuysTimer += animSawGuysSpeed * gDeltaTime;

	int i = ((int)sawGuysTimer) % SAWGUYS;
	mAISpriteClipIndex = sawGuysAnim[i];
}