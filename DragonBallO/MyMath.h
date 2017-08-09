#pragma once

namespace MyMath {
	struct Int2 {
		Int2(){}
		Int2(int x, int y) : x(x), y(y) {}
		int x{0};
		int y{0};
	};
	struct Float2 {
		Float2(){}
		Float2(float x, float y) : x(x), y(y) {}
		float x{0.f};
		float y{0.f};
	};
}