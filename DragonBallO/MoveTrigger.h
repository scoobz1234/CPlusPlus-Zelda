#pragma once
#include "Trigger.h"
#include "Camera.h"


class MoveTrigger : public Trigger
{
public:
	MoveTrigger() {};
	~MoveTrigger() {};
	using Float2 = MyMath::Float2;
	bool mInOrOut{ false };
	void SetMovePos(Float2 movePos,bool inOrOut);


protected:
	Float2 mMovePos{ 0, 0 };
	void OnCollision(Entity *other) override;
};

