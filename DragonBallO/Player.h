#pragma once
#include "Living.h"

class Player : public Living {
public:
	//Base class destructor is ALWAYS implicitly called...
	Player() : Living() { mCollisionBlocks = true; };
	virtual ~Player() override {}

public:
	void Move() override;
	void Attack() override;
};