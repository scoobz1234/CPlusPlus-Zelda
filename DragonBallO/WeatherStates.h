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
	WeatherStates(SDLInit *sdlInit);
	~WeatherStates();

	void Update();
	void Render();

private:
	//SDLInit *gSdlInit = nullptr;
	Weather mRain;							//Weather Sprite
	Weather mFog;							//Weather Sprite
	SDLInit * mSdlInit = nullptr;
	WeatherState mLastWeatherState;

};
