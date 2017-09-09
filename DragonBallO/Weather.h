#pragma once
#include "Sprite.h"
#include "Destructible.h"


class Weather : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	Weather() { mCanBePushedBack = false; }
	virtual ~Weather() override {}

	void Update() override;

public:
	void StaticSpriteSwapping();


public:
	void SetAnimSwapIndices(int count, float animSpeed, int * indices);
};



