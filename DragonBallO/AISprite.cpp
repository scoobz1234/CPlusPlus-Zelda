#include "AISprite.h"
#include "Camera.h"


//1.4142f = sqrt(sqr(1) + sqr(1))
#define SQRHYPE 1.4142f	

extern float gDeltaTime;
extern Camera gCamera;


namespace {
	//index sizes...
	int numRightIndices { 0 };
	int numLeftIndices{ 0 };
	int numDownIndices{ 0 };
	int numUpIndices{ 0 };
	int numSwapIndices{ 0 };

	//indices...
	int *rightIndices = nullptr;
	int *leftIndices = nullptr;
	int *downIndices = nullptr;
	int *upIndices = nullptr;
	int *swapIndices = nullptr;
}

namespace {
	//Animation times...
	float attackTime = .25f;

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;
	float swapTimer = .0f;


	//Animation speeds...
	float animMoveSpeed{ 0 };
	float animSwapSpeed{ 0 };

}

void AISprite::Update() {
	StaticSpriteSwapping();
	Sprite::Update();
}

//functions to set indices and counts for swaps and movements...
void AISprite::SetAnimRightIndices(int count,float animSpeed, int * indices) {
	numRightIndices = count;
	rightIndices = indices;
	animMoveSpeed = animSpeed;
}

void AISprite::SetAnimLeftIndices(int count,float animSpeed, int * indices) {
	numLeftIndices = count;
	leftIndices = indices;
	animMoveSpeed = animSpeed;
}

void AISprite::SetAnimDownIndices(int count,float animSpeed, int * indices) {
	numDownIndices = count;
	downIndices = indices;
	animMoveSpeed = animSpeed;
}

void AISprite::SetAnimUpIndices(int count,float animSpeed, int * indices) {
	numUpIndices = count;
	upIndices = indices;
	animMoveSpeed = animSpeed;
}
void AISprite::SetAnimSwapIndices(int count,float animSpeed, int * indices) {
	numSwapIndices = count;
	swapIndices = indices;
	animSwapSpeed = animSpeed;
}


void AISprite::StaticSpriteSwapping() {
	swapTimer += animSwapSpeed * gDeltaTime;
	int i = (int)swapTimer % numSwapIndices;
	mSpriteClipIndex = swapIndices[i];
}

//
//
//
//
//void AISprite::MoveRightAnim() {
//
//	//Setting velocity...and movement...
////	float velocity = mMoveSpeed * gDeltaTime;
////  mPos.x += something * velocity;
////  mPos.y += something * velocity;
//	
//	//changing of the sprites...
//	moveRightTimer += animMoveSpeed * gDeltaTime;
//	int index = (int)moveRightTimer % AI_ANIM_RIGHT_MOVE_COUNT;
//	mSpriteClipIndex = AIanimRightIndices[index];
//	
//	lastAttackIndex = 0;
//	lastMoveIndex = AIanimRightIndices[0];
//}
//
//void AISprite::MoveLeftAnim() {
//
//	//Setting velocity...and movement...
////	float velocity = mMoveSpeed * gDeltaTime;
////  mPos.x += something * velocity;
////	mPos.y += something * velocity;
//
//	//changing of the sprites...
//	moveLeftTimer += animMoveSpeed * gDeltaTime;
//	int index = (int)moveLeftTimer % AI_ANIM_LEFT_MOVE_COUNT;
//	mSpriteClipIndex = AIanimLeftIndices[index];
//	
//	lastAttackIndex = 1;
//	lastMoveIndex = AIanimLeftIndices[0];
//}
//
//void AISprite::MoveUpAnim() {
//
//	//Setting velocity...and movement...
////	float velocity = mMoveSpeed * gDeltaTime;
////	mPos.x += something * velocity;
////  mPos.y += something * velocity;
//
//	//changing of the sprites...
//	moveUpTimer += animMoveSpeed * gDeltaTime;
//	int index = (int)moveUpTimer % AI_ANIM_UP_MOVE_COUNT;
//	mSpriteClipIndex = AIanimUpIndices[index];
//	
//	lastAttackIndex = 3;
//	lastMoveIndex = AIanimUpIndices[0];
//}
//
//void AISprite::MoveDownAnim() {
//
//	//Setting velocity...and movement...
////	float velocity = mMoveSpeed * gDeltaTime;
////	mPos.x += something * velocity;
////	mPos.y += something * velocity;
//	
//	//changing of the sprites...
//	moveDownTimer += animMoveSpeed * gDeltaTime;
//	int index = (int)moveDownTimer % AI_ANIM_DOWN_MOVE_COUNT;
//	mSpriteClipIndex = AIanimDownIndices[index];
//	
//	lastAttackIndex = 2;
//	lastMoveIndex = AIanimDownIndices[0];
//}
