#include "Player.h"
#include "Camera.h"
#include <iostream>
#include <windows.h>

#define ANIM_RIGHT_COUNT 2
#define ANIM_LEFT_COUNT 2
#define ANIM_UP_COUNT 2
#define ANIM_DOWN_COUNT 2

#define ANIM_ATTACK_COUNT 3

//1.4142f = sqrt(sqr(1) + sqr(1))
#define SQRHYPE 1.4142f	

bool insideHouse = false;

extern float gDeltaTime;
extern Camera gCamera;

//Keys held down...
extern int gHorizKeysHeld;	//keys a and b
extern int gVertKeysHeld;	//keys w and s

							//Keys pressed...
extern bool gFirstKeyDown;	//keys 1
extern bool gSecondKeyDown;	//keys 2
extern bool gThirdKeyDown;	//keys 3
extern bool gFourthKeyDown;	//keys 4

							//Keys released...
extern bool gFirstKeyUp;	//keys e
extern bool gSecondKeyUp;	//keys 2
extern bool gThirdKeyUp;	//keys 3
extern bool gFourthKeyUp;	//keys 4

extern bool PAN_CAMERA;

namespace {
	int lastMoveIndex = 4;
	int lastAttackIndex = 0;
}

namespace {
	//Animation times...
	float attackTime = .25f;

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;

	float attackTimer = .0f;

	//Animation speeds...
	float animMoveSpeed = 12;
	float animAttackSpeed = 12;

	//Animation indices...
	int animRightIndices[ANIM_RIGHT_COUNT] = { 4, 18 };
	int animLeftIndices[ANIM_LEFT_COUNT] = { 2, 16 };
	int animUpIndices[ANIM_UP_COUNT] = { 3, 17 };
	int animDownIndices[ANIM_DOWN_COUNT] = { 1, 15 };

	int animAttackLeftIndices[4][ANIM_ATTACK_COUNT] = {
		{ 35, 49, 62 },	//right attack...
		{ 61, 48, 34 },	//left attack...
		{ 61, 48, 34 },	//down attack...
		{ 61, 48, 34 }	//up attack...
	};
}

void Player::Update() {
	if (gCamera.IsPanning()) {
		return;
	}

	Move();

	if (objectCollided) {
		if (objectCanTeleport) {
			if (!insideHouse) {
				TeleportIn();
				insideHouse = !insideHouse;
			}
			else {
				TeleportOut();
				insideHouse = !insideHouse;
			}
		}
	}

	Attack();
	Sprite::Update();
}

void Player::Move() {
	//If we are attacking we want to stop movement...
	if (attackTimer > 0.f) {
		return;
	}

	//Setting velocity...
	float velocity = mMoveSpeed * gDeltaTime;

	//Updates position. SQRHYPE is used so diagnal direction is NOT faster...
	mPos.x += (gVertKeysHeld != 0 ? (gHorizKeysHeld *
		SQRHYPE) / 2.0f : gHorizKeysHeld) * velocity;
	mPos.y += (gHorizKeysHeld != 0 ? (gVertKeysHeld *
		SQRHYPE) / 2.0f : gVertKeysHeld) * velocity;

	//std::cout << mPos.x << " " << mPos.y << std::endl;

	//Update animations...
	if (gHorizKeysHeld > 0) {
		moveRightTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveRightTimer % ANIM_RIGHT_COUNT;
		mSpriteClipIndex = animRightIndices[index];

		lastAttackIndex = 0;
		lastMoveIndex = animRightIndices[0];
	}
	else if (gHorizKeysHeld < 0) {
		moveLeftTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveLeftTimer % ANIM_LEFT_COUNT;
		mSpriteClipIndex = animLeftIndices[index];

		lastAttackIndex = 1;
		lastMoveIndex = animLeftIndices[0];
	}
	else if (gVertKeysHeld > 0) {
		moveDownTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveDownTimer % ANIM_DOWN_COUNT;
		mSpriteClipIndex = animDownIndices[index];

		lastAttackIndex = 2;
		lastMoveIndex = animDownIndices[0];
	}
	else if (gVertKeysHeld < 0) {
		moveUpTimer += animMoveSpeed * gDeltaTime;

		int index = (int)moveUpTimer % ANIM_UP_COUNT;
		mSpriteClipIndex = animUpIndices[index];

		lastAttackIndex = 3;
		lastMoveIndex = animUpIndices[0];
	}
	else {
		mSpriteClipIndex = lastMoveIndex;
	}
}

void Player::Attack() {
	//Update animation...
	if (attackTimer > 0.f) {
		attackTimer -= gDeltaTime;	//Updates timer...
		float time = 1.f - (attackTimer / attackTime);

		int index = (int)(time * ANIM_ATTACK_COUNT) % ANIM_ATTACK_COUNT;
		mSpriteClipIndex = animAttackLeftIndices[lastAttackIndex][index];

	}	//Start animation...
	else if (gFirstKeyDown) {
		attackTimer = attackTime;
	}
}

void Player::TeleportIn() {
	PAN_CAMERA = false;
	mPos.x = 1534;
	mPos.y = 1112;
	objectCollided = !objectCollided;
}

void Player::TeleportOut() {
	int tPosx = 440;
	int tPosy = 391;
	mPos.x = tPosx;
	mPos.y = tPosy;
	objectCollided = !objectCollided;
	
}
