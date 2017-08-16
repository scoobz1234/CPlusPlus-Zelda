#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::SetPos(MyMath::Float2 pos) {
	mPos = pos;
}

void Camera::LookAt(Entity &target) {
	MyMath::Float2  cameraPos = target.GetPosition();
	SetPos(cameraPos);
}