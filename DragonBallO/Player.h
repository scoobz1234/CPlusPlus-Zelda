#pragma once
#include "Sprite.h"
#include "Destructible.h"


class Player : public Sprite, public Destructible {
public:
	//Base class destructor is ALWAYS implicitly called...
	Player() { mCanBePushedBack = false; }
	virtual ~Player() override {}

	void Update() override;

public:
	void Move();
	void Attack();
	void TeleportIn();
	void TeleportOut();

};