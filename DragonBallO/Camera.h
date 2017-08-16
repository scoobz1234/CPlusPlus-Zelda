#pragma once
#include "MyMath.h"
#include "Entity.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPos(MyMath::Float2 pos);
	void LookAt(Entity &target);

private:
	MyMath::Float2 mPos;
};

