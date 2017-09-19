#include "Weather.h"
#include "Camera.h"


//1.4142f = sqrt(sqr(1) + sqr(1))
#define SQRHYPE 1.4142f	

extern float gDeltaTime;
extern Camera gCamera;


namespace {
	//index sizes...
	int numRightIndices{ 0 };
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

	//Animation timers...
	float moveRightTimer = 0.f;
	float moveLeftTimer = 0.f;
	float moveUpTimer = 0.f;
	float moveDownTimer = 0.f;

	//timer for the sprite swap...
	float swapTimer = 0.f;

	//Animation speeds...
	float animMoveSpeed{ 0 };
	float animSwapSpeed{ 0 };
}

void Weather::Update() {
	StaticSpriteSwapping();
	Sprite::Update();
}
//functions to set indices and counts for swaps and movements...
void Weather::SetAnimSwapIndices(int count, float animSpeed, int * indices) {
	numSwapIndices = count;
	swapIndices = indices;
	animSwapSpeed = animSpeed;
}
//swaps sprites staticly..
void Weather::StaticSpriteSwapping() {
	swapTimer += animSwapSpeed * gDeltaTime;
	int i = (int)swapTimer % numSwapIndices;
	mSpriteClipIndex = swapIndices[i];
}

