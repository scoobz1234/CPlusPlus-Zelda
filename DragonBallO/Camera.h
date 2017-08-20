#pragma once

#include "MyMath.h"
#include "Entity.h"

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int WORLD_WIDTH;
extern const int WORLD_HEIGHT;

class Camera
{

	friend class SDLInit;

	using Float2 = MyMath::Float2;

public:
	Camera() {};
	~Camera() {};

	void SetPos(Float2 pos);
	void LookAt(Entity &target);
	void PanWith(Entity &target);

	void RestrictTargetToWorld(Entity &target);

	bool IsPanning();

private:
	void RestrictCameraToWorld();

private:
	Float2 mPos;
	Float2 mStartPanPos;
	Float2 mEndPanPos;

	SDL_Rect *mBounds = nullptr;
};

