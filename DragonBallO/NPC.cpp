#include "NPC.h"
#include "Camera.h"
#include <stdlib.h>

#define ANIM_RIGHT_COUNT 7
#define ANIM_LEFT_COUNT 7
#define ANIM_UP_COUNT 7
#define ANIM_DOWN_COUNT 7

//1.4142f = sqrt(sqr(1) + sqr(1))
#define SQRHYPE 1.4142f	

extern float gDeltaTime;
extern Camera gCamera;

namespace {
	int lastMoveIndex = 55;

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;
	float pauseTimer = 0.f;

	//Animation speeds...
	float animMoveSpeed = 10;

	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 48,49,50,51,52,53,54 };
	int animLeftIndices[ANIM_LEFT_COUNT] = { 40,41,42,43,44,45,46 };
	int animUpIndices[ANIM_UP_COUNT] = { 36,37,38,39,35,34,33 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 55,56,57,58,59,60,61 };

}

void NPC::Update() {
	Controller();
	Move();
	Sprite::Update();

}

void NPC::Move() {
	
	//Setting velocity...
	float velocity = mMoveSpeedAI * gDeltaTime;

	//Updates position. SQRHYPE is used so diagnal direction is NOT faster...
	mPos.x += (VertMovement != 0 ? (HorizMovement *
		SQRHYPE) / 2.0f : HorizMovement) * velocity;
	mPos.y += (HorizMovement != 0 ? (VertMovement *
		SQRHYPE) / 2.0f : VertMovement) * velocity;

	//Update animations...
	if (HorizMovement > 0) {
		moveRightTimer += animMoveSpeed * gDeltaTime;
		int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[index];
		lastMoveIndex = animRightIndices[0];
	}
	else if (HorizMovement < 0) {
		moveLeftTimer += animMoveSpeed * gDeltaTime;
		int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[index];
		lastMoveIndex = animLeftIndices[0];
	}
	else if (VertMovement > 0) {
		moveDownTimer += animMoveSpeed * gDeltaTime;
		int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[index];
		lastMoveIndex = animDownIndices[0];
	}
	else if (VertMovement < 0) {
		moveUpTimer += animMoveSpeed * gDeltaTime;
		int index = (int)moveUpTimer % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[index];
		lastMoveIndex = animUpIndices[0];
	}
	else {
		mSpriteClipIndex = lastMoveIndex;
	}
}

void NPC::Controller() {
	if (moveRightTimer > 5 && HorizMovement == 1) {
		HorizMovement = 0;
		moveRightTimer = 0;
	}
	if (moveLeftTimer > 5 && HorizMovement == -1) {
		HorizMovement = 0;
		moveLeftTimer = 0;
	}
	if (moveUpTimer > 5 && VertMovement == -1) {
		VertMovement = 0;
		moveUpTimer = 0;
	}
	if (moveDownTimer > 5 && VertMovement == 1) {
		VertMovement = 0;
		moveDownTimer = 0;
	}
	if (HorizMovement == 0 && VertMovement == 0) {
		pauseTimer += animMoveSpeed * gDeltaTime;
	}
	if (pauseTimer > 50 && HorizMovement == 0 && VertMovement == 0) {
		int direction = rand() % 4;
		switch (direction) {
		case 0: HorizMovement = -1; break;
		case 1: HorizMovement = 1; break;
		case 2: VertMovement = -1; break;
		case 3: VertMovement = 1; break;
		}
	}

}

