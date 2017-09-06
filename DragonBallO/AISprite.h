#pragma once
#include "Sprite.h"
#include "Destructible.h"


class AISprite : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	AISprite() { mCanBePushedBack = false; }
	virtual ~AISprite() override {}

	void Update() override;

public:
	/*void MoveRightAnim();
	void MoveLeftAnim();
	void MoveUpAnim();
	void MoveDownAnim();*/
	void StaticSpriteSwapping();


public:
	void SetAnimRightIndices(int count,float animSpeed, int * indices);
	void SetAnimLeftIndices(int count, float animSpeed, int * indices);
	void SetAnimDownIndices(int count, float animSpeed, int * indices);
	void SetAnimUpIndices(int count, float animSpeed, int * indices);
	void SetAnimSwapIndices(int count, float animSpeed, int * indices);
};



