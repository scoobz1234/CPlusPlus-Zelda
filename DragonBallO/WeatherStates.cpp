#include "WeatherStates.h"

//SOUND
extern void PlayBGMusic(Mix_Music *bgmName);
extern void PlaySFX(Mix_Chunk *sfxName);
extern void StopBGMusic();
extern Mix_Music *weatherRain;
extern Mix_Music *weatherRainInside;
extern Mix_Music *BGMusic1;
extern Mix_Chunk *SFX2;
extern Mix_Chunk *SFX3;

extern float gDeltaTime;

namespace {
	const int minChangeWeatherTime = 5;		//In seconds...
	const int maxChanhgeWeatherTime = 30;			//In seconds...
	int rainIndices[] = { 0,1,2,3 };
	int fogIndices[] = { 0,1,2,3 };
}

void WeatherStates::Init(SDLInit *sdlInit) {
	mSdlInit = sdlInit;
	//RAIN
	mRain.SetTexturePath("textures/rain2.png");								//Weather Texture Path
	mSdlInit->LoadTexture(mRain);												//Weather Texture Load
	mRain.SetPosition({ 0,0 });												//Weather Position
	mRain.SetSize(640, 480);													//weather Size
	mRain.ConfigureCollision(false, false);									//Weather Collision
	mRain.InitSpriteSheet(0, 4, 1);											//Weather Initialize SpriteSheet
	mRain.SetSpriteClip(0, 0, 256, 223, 0);									//Weather Set Sprite Clip
	mRain.SetSpriteClip(257, 0, 256, 223, 1);								//Weather Set Sprite Clip
	mRain.SetSpriteClip(513, 0, 256, 223, 2);								//Weather Set Sprite Clip
	mRain.SetSpriteClip(769, 0, 256, 223, 3);								//Weather Set Sprite Clip
																			//FOG
	mFog.SetTexturePath("textures/fog.png");									//Weather Texture Path
	mSdlInit->LoadTexture(mFog);												//Weather Texture Load
	mFog.SetPosition({ 0,0 });												//Weather Position
	mFog.SetSize(640, 480);													//weather Size
	mFog.ConfigureCollision(false, false);									//Weather Collision
	mFog.InitSpriteSheet(0, 4, 1);											//Weather Initialize SpriteSheet
	mFog.SetSpriteClip(0, 0, 480, 360, 0);									//Weather Set Sprite Clip
	mFog.SetSpriteClip(481, 0, 480, 360, 1);									//Weather Set Sprite Clip
	mFog.SetSpriteClip(961, 0, 480, 360, 2);									//Weather Set Sprite Clip
	mFog.SetSpriteClip(1441, 0, 480, 360, 3);								//Weather Set Sprite Clip
}

WeatherStates::~WeatherStates(){
	mSdlInit->CleanupSprite(mRain);
	mSdlInit->CleanupSprite(mFog);
}

void WeatherStates::Update() {

	static float timeToChangeWeather = 0.0f;
	timeToChangeWeather -= gDeltaTime;
	
	if (timeToChangeWeather < 0.0f) {
		srand((unsigned int)time(NULL));

		timeToChangeWeather = float(minChangeWeatherTime +
			(rand() % (maxChanhgeWeatherTime - minChangeWeatherTime)));

		printf("Weather about to change...\n");
		WeatherState ws = WeatherState(rand() % 3);

		if (mLastWeatherState != ws) {
			switch (ws) {
			case WeatherState::RAIN:
				mRain.SetAnimSwapIndices(4, 6.0f, rainIndices);							
				mRain.Update();
				PlayBGMusic(weatherRain);
				Render();
				printf("Weather changed to rainy\n");
				break;
			case WeatherState::FOG:
				mFog.SetAnimSwapIndices(4, .3f, fogIndices);
				mFog.Update();
				PlayBGMusic(BGMusic1);
				Render();
				printf("Weather changed to fogy\n");
				break;
			case WeatherState::SUNNY:
				StopBGMusic();												
				PlayBGMusic(BGMusic1);	
				printf("Weather changed to sunny\n");
				break;
			}
			mLastWeatherState = ws;
		}

		printf("Weather changed to current weather\n");
	}
	mRain.Update();
	mFog.Update();
}


void WeatherStates::Render() {
	switch (mLastWeatherState) {
		case WeatherState::RAIN:
			mSdlInit->DrawHud(mRain);
			break;
		case WeatherState::FOG:
			mSdlInit->DrawHud(mFog);
			break;
		case WeatherState::SUNNY:
			//Draw nothing...
			break;
	}
}


