#pragma once
#include "Sprite.h"
#include "Destructible.h"


class AIHandler : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	AIHandler() { mCanBePushedBack = false; }
	virtual ~AIHandler() override {}

	void Update() override;

public:
	void GuyInBed();
	void Witch();
	void Attack();

};
