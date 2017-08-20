#include "MyMath.h"

int MyMath::Abs(int num) {
	return num < 0 ? -num : num;
}

float MyMath::Abs(float num) {
	return num < 0.0f ? -num : num;
}

float MyMath::Lerp(float start, float end, float time) {
	if (time > 1) {
		return end;
	}

	float value = start + ((end - start) * time);
	return value;
}