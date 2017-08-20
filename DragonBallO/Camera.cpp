#include "Camera.h"

using namespace MyMath;

extern float gDeltaTime;

namespace {
	float panTime = 1.0f;
	bool isPanning = false;
}

void Camera::RestrictCameraToWorld() {
	float halfWidth = SCREEN_WIDTH / 2.0f;
	float halfHeight = SCREEN_HEIGHT / 2.0f;

	if (mPos.x < 0.0f) {
		mPos.x = 0.0f;
	}
	if (mPos.y < 0.0f) {
		mPos.y = 0.0f;
	}

	if (mPos.x + SCREEN_WIDTH > WORLD_WIDTH) {
		mPos.x = WORLD_WIDTH - SCREEN_WIDTH;
	}
	if (mPos.y + SCREEN_HEIGHT > WORLD_HEIGHT) {
		mPos.y = WORLD_HEIGHT - SCREEN_HEIGHT;
	}
}

void Camera::RestrictTargetToWorld(Entity &target) {
	//Restricting player to world...
	if (target.mPos.x + target.mTopLeftCollOffset.x < 0.0f) {
		target.mBlockedSides |= 1 << 0;	//blocks right...
		target.mPos.x = (float)target.mTopLeftCollOffset.x;
	}
	if (target.mPos.y + target.mTopLeftCollOffset.y < 0.0f) {
		target.mPos.y = (float)-target.mTopLeftCollOffset.y;
		target.mBlockedSides |= 1 << 3;	//blocks bottom...
	}
	if (target.mPos.x + target.mSize.x - target.mBottomRightCollOffset.x > WORLD_WIDTH) {
		target.mPos.x = float(WORLD_WIDTH - target.mSize.x + target.mBottomRightCollOffset.x);
		target.mBlockedSides |= 1 << 2;	//blocks left...
	}
	if (target.mPos.y + target.mSize.y - target.mBottomRightCollOffset.y > WORLD_HEIGHT) {
		target.mPos.y = float(WORLD_HEIGHT - target.mSize.y + target.mBottomRightCollOffset.y);
		target.mBlockedSides |= 1 << 1;	//blocks top...
	}
}

void Camera::SetPos(Float2 pos) {
	mPos.x = pos.x - (SCREEN_WIDTH / 2.0f);
	mPos.y = pos.y - (SCREEN_HEIGHT / 2.0f);
}

void Camera::LookAt(Entity &target) {
	SetPos({ target.mPos.x + (target.mSize.x / 2.0f), target.mPos.y + (target.mSize.y / 2.0f) });
	RestrictCameraToWorld();
}

void Camera::PanWith(Entity &target) {
	bool panLeft = target.mPos.x + target.mTopLeftCollOffset.x < mPos.x;
	bool panUp = target.mPos.y + target.mTopLeftCollOffset.y < mPos.y;
	bool panRight = target.mPos.x + target.mSize.x - target.mBottomRightCollOffset.x >
		mPos.x + SCREEN_WIDTH;
	bool panDown = target.mPos.y + target.mSize.y - target.mBottomRightCollOffset.y >
		mPos.y + SCREEN_HEIGHT;

	if (panLeft || panUp || panRight || panDown) {
		if (panLeft) {
			target.mPos.x = mPos.x - target.mTopLeftCollOffset.x;
			mEndPanPos.x = target.mPos.x - SCREEN_WIDTH + target.mSize.x - target.mBottomRightCollOffset.x;
		}
		else if (panUp) {
			target.mPos.y = mPos.y - target.mTopLeftCollOffset.y;
			mEndPanPos.y = target.mPos.y - SCREEN_HEIGHT + target.mSize.y - target.mBottomRightCollOffset.y;
		}
		else if (panRight) {
			target.mPos.x = mPos.x + SCREEN_WIDTH - target.mSize.x + target.mBottomRightCollOffset.x;
			mEndPanPos.x = target.mPos.x + target.mTopLeftCollOffset.x;
		}
		else {	//Pan down...
			target.mPos.y = mPos.y + SCREEN_HEIGHT - target.mSize.y + target.mBottomRightCollOffset.y;
			mEndPanPos.y = target.mPos.y + target.mTopLeftCollOffset.y;
		}

		//Restricting to world bounds...
		if (mEndPanPos.x < 0.0f || mEndPanPos.y < 0.0f ||
			mEndPanPos.x + SCREEN_WIDTH > WORLD_WIDTH ||
			mEndPanPos.y + SCREEN_HEIGHT > WORLD_HEIGHT) {
			mEndPanPos = mStartPanPos;
			//panTime = 1.0f;
			isPanning = false;
			return;
		}

		panTime = 0.0f;
		isPanning = true;
		mStartPanPos = mPos;
	}

	if (isPanning) {
		panTime += gDeltaTime;
		mPos.x = Lerp(mStartPanPos.x, mEndPanPos.x, panTime);
		mPos.y = Lerp(mStartPanPos.y, mEndPanPos.y, panTime);
	}
}

bool Camera::IsPanning() {
	return isPanning && panTime < 1.0f;
}
