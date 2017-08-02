#pragma once
#include "Entity.h"

class Living : public Entity {
public:
	virtual void Move() = 0;

	void SetHealth(int health, int maxHealth);
	bool TakeDamage(int damage);


public:
	int mMaxHealth{100};
	int mHealth{100};

	//TODO: add typedef struct for inventory...
	//TODO: struct for weapons to attach and give damage...
};