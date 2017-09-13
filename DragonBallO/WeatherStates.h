#pragma once
#include "SDLInit.h"
#include "Weather.h"
#include <cstdlib>
#include <ctime>

class WeatherStates
{

enum WeatherState {
	SUNNY,
	RAIN,
	FOG
};

public:
	WeatherStates() {};
	~WeatherStates();

	void Init(SDLInit *sdlInit);

	void Update();
	void Render();

private:
	//SDLInit *gSdlInit = nullptr;
	Weather mRain;							//Weather Sprite
	Weather mFog;							//Weather Sprite
	SDLInit * mSdlInit = nullptr;
	WeatherState mLastWeatherState;

};
