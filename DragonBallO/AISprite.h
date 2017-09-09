#pragma once
#include "Sprite.h"
#include "Destructible.h"


class AISprite : public Sprite {
public:
	//Base class destructor is ALWAYS implicitly called...
	AISprite() {}
	void Update();

public:

	void StaticSpriteSwapping();
	//index sizes...
	int numSwapIndices{ 0 };
	//indices...
	int *swapIndices = nullptr;
	//timer for the sprite swap...
	float swapTimer{ 0.f };
	//Animation speeds...
	float animSwapSpeed{ 0 };

public:
	void SetAnimSwapIndices(int count,float animSpeed,int * indices);

};



