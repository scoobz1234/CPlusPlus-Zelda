#pragma once
#include "Entity.h"

class Living : public Entity {
public:
	//Base class destructor is ALWAYS implicitly called...
	virtual ~Living() override {}

public:
	virtual void Move() = 0;
	virtual void Attack() = 0;

	void SetHealth(int health, int maxHealth);
	void SetMoveSpeed(float moveSpeed);

	bool TakeDamage(int damage);

protected:
	int mMaxHealth{100};
	int mHealth{100};

	//TODO: add typedef struct for inventory...
	//TODO: struct for weapons to attach and give damage...
};