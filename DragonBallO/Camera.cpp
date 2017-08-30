#include "Camera.h"

using namespace MyMath;

extern float gDeltaTime;

namespace {
	float panTime = 1.0f;
	int horizScrnIndex = 0;
	int vertScrnIndex = 0;
}

void Camera::RestrictTargetToWorld(Entity &target) {
	int targetWidth = target.mSize.x - target.mBottomRightCollOffset.x - target.mTopLeftCollOffset.x;
	int targetHeight = target.mSize.y - target.mBottomRightCollOffset.y - target.mTopLeftCollOffset.y;

	int lookAtTargetWidth = mLookAtTarget == nullptr ? target.mSize.x -
		target.mBottomRightCollOffset.x - target.mTopLeftCollOffset.x : mLookAtTarget->mSize.x -
		mLookAtTarget->mBottomRightCollOffset.x - mLookAtTarget->mTopLeftCollOffset.x;
	int lookAtTargetHeight = mLookAtTarget == nullptr ? target.mSize.y -
		target.mBottomRightCollOffset.y - target.mTopLeftCollOffset.y : mLookAtTarget->mSize.y -
		mLookAtTarget->mBottomRightCollOffset.y - mLookAtTarget->mTopLeftCollOffset.y;

	int maxNumHorizScrns = WORLD_WIDTH / SCREEN_WIDTH - 1;
	int maxNumVertScrns = WORLD_HEIGHT / SCREEN_HEIGHT - 1;

	float maxHoriz = mMode == Mode::FOLLOW ? WORLD_WIDTH : float((SCREEN_WIDTH +
		(SCREEN_WIDTH * maxNumHorizScrns) - (lookAtTargetWidth * maxNumHorizScrns)));
	float maxVert = mMode == Mode::FOLLOW ? WORLD_HEIGHT : float((SCREEN_HEIGHT +
		(SCREEN_HEIGHT * maxNumVertScrns) - (lookAtTargetHeight * maxNumVertScrns)));

	//Blocks left side...
	if (target.mPos.x + target.mTopLeftCollOffset.x < 0.0f) {
		target.mPos.x = -(float)target.mTopLeftCollOffset.x;
		target.mBlockedSides |= 1 << 0;	//blocks right...
	}	//blocks right side...
	else if (target.mPos.x + targetWidth > maxHoriz) {
		target.mPos.x = float(maxHoriz - target.mSize.x + target.mBottomRightCollOffset.x);
		target.mBlockedSides |= 1 << 2;	//blocks left...
	}	//blocks top side...
	if (target.mPos.y + target.mTopLeftCollOffset.y < 0.0f) {
		target.mPos.y = (float)-target.mTopLeftCollOffset.y;
		target.mBlockedSides |= 1 << 3;	//blocks bottom...
	}	//blocks bottom side...
	else if (target.mPos.y + target.mTopLeftCollOffset.y + targetHeight > maxVert) {
		target.mPos.y = float(maxVert - target.mSize.y + target.mBottomRightCollOffset.y);
		target.mBlockedSides |= 1 << 1;	//blocks top...
	}
}

void Camera::SetPos(Float2 pos) {
	mPos.x = pos.x - (SCREEN_WIDTH / 2.0f);
	mPos.y = pos.y - (SCREEN_HEIGHT / 2.0f);
}

void Camera::LookAt(Entity &target) {
	mLookAtTarget = &target;

	//Camera follows target...
	if (mMode == Mode::FOLLOW) {
		SetPos({ target.mPos.x + (target.mSize.x / 2.0f), target.mPos.y + (target.mSize.y / 2.0f) });

		//Restricting camera to world coords...
		float halfWidth = SCREEN_WIDTH / 2.0f;
		float halfHeight = SCREEN_HEIGHT / 2.0f;

		if (mPos.x < 0.0f) {
			mPos.x = 0.0f;
		}
		if (mPos.y < 0.0f) {
			mPos.y = 0.0f;
		}

		if (mPos.x + SCREEN_WIDTH > WORLD_WIDTH) {
			mPos.x = float(WORLD_WIDTH - SCREEN_WIDTH);
		}
		if (mPos.y + SCREEN_HEIGHT > WORLD_HEIGHT) {
			mPos.y = float(WORLD_HEIGHT - SCREEN_HEIGHT);
		}

		return;
	}

	if (panTime > 1) {
		//else, camera pans over to next screen (when player outside camera bounds...
		int targetWidth = target.mSize.x - target.mBottomRightCollOffset.x - target.mTopLeftCollOffset.x;
		int targetHeight = target.mSize.y - target.mBottomRightCollOffset.y - target.mTopLeftCollOffset.y;

		float nextRight = float((SCREEN_WIDTH + (SCREEN_WIDTH * horizScrnIndex) -
			(targetWidth * horizScrnIndex)));
		float nextDown = float((SCREEN_HEIGHT + (SCREEN_HEIGHT * vertScrnIndex) -
			(target.mBottomRightCollOffset.y * vertScrnIndex)));
		float nextLeft = float((SCREEN_WIDTH * horizScrnIndex) -
			(target.mTopLeftCollOffset.x * horizScrnIndex));

		bool panRight = target.mPos.x + targetWidth > nextRight;
		bool panDown = target.mPos.y + targetHeight + target.mBottomRightCollOffset.y > nextDown;
		//bool panLeft = target.mPos.x + target.mTopLeftCollOffset.x < nextLeft;

		if (panRight) {
			mStartPanPos = mEndPanPos = mPos;
			mEndPanPos.x = nextRight - targetWidth;
			++horizScrnIndex;
			panTime = 0.0f;
			printf("Pan Right...!\n");
		}
		//else if (panLeft) {
		//	mStartPanPos = mEndPanPos = mPos;
		//	mEndPanPos.x = nextLeft + targetWidth;
		//	--horizScrnIndex;
		//	panTime = 0.0f;
		//	printf("Pan Left...!\n");
		//}

		if (panDown) {
			mStartPanPos = mEndPanPos = mPos;
			mEndPanPos.y = nextDown - targetHeight;
			++vertScrnIndex;
			panTime = 0.0f;
			printf("Pan Down...!\n");
		}

	}

	panTime += gDeltaTime;
	mPos.x = Lerp(mStartPanPos.x, mEndPanPos.x, panTime);
	mPos.y = Lerp(mStartPanPos.y, mEndPanPos.y, panTime);
}

bool Camera::IsPanning() {
	return panTime < 1.0f;
}

void Camera::SetMode(Mode mode) {
	mMode = mode;
}