#pragma once
#include <string>
#include <SDL_image.h>
#include "MyMath.h"
#include <vector>

class Entity {

	friend class SDLInit;
	friend class Camera;

	using UInt = unsigned int;
	using Int2 = MyMath::Int2;
	using Float2 = MyMath::Float2;
	using UByte = MyMath::UByte;

public:
	//Needs to be virtual so that derived destructor gets called...
	virtual ~Entity() {};

public:
	virtual void Update();
	virtual void OnCollision(Entity *other);

	void SetPosition(float x, float y);
	void SetMoveSpeed(float moveSpeed);

	void ConfigureCollision(bool canBePushedBack,bool canTeleport, Int2 topLeftCollOffset = { 0, 0 },
		Int2 bottomRightCollOffset = { 0, 0 });

	void AddCollidableEntity(Entity &entity);

	bool objectCollided{ false };
	bool objectCanTeleport{ false };

private:
	void CheckCollision();

	UByte mBlockedSides{ 0 };

protected:
	Float2 mPos;
	Int2 mSize;

	Int2 mTopLeftCollOffset;
	Int2 mBottomRightCollOffset;

	//If this entity can move, it needs a move speed...
	float mMoveSpeed{ 140.f };

	//For collision...
	std::vector<Entity*> mCollidableEntities;
	bool mCanBePushedBack{ false };
	int mHasCollided{ false };
	bool mCanTeleport{ false };
};