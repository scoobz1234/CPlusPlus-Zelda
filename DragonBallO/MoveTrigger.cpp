#include "MoveTrigger.h"

extern Camera gCamera;
bool inside;
void MoveTrigger::OnCollision(Entity *other) {
	other->SetPosition(mMovePos);
	inside = mInOrOut;
	gCamera.SetPos(mMovePos);
	Entity::OnCollision(other);
}

void MoveTrigger::SetMovePos(Float2 movePos, bool inOrOut) {
	mMovePos = movePos;
	mInOrOut = inOrOut;
}
