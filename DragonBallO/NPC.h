#pragma once
#include "Sprite.h"
#include "Destructible.h"


class NPC : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	NPC() { mCanBePushedBack = false; }
	virtual ~NPC() override {}

	void Update() override;

public:
	void Move();
	void Controller();
	int VertMovement;
	int HorizMovement;

};