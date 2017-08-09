#include "Living.h"

void Living::SetHealth(int health, int maxHealth) {
	mHealth = health;
	mMaxHealth = maxHealth;
}

void Living::SetMoveSpeed(float moveSpeed) {
	mMoveSpeed = moveSpeed;
}

bool Living::TakeDamage(int damage) {
	mHealth -= damage;
	bool hasDied = mHealth <= 0;

	return hasDied;
}