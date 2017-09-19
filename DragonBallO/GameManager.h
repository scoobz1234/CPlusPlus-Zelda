#pragma once

class GameManager {
public:
enum LoadedScene {SPLASH,MAINMENU,LIGHTWORLD,INSIDEHOUSE};

public:
	bool Init();
	void Cleanup();

	void Update();
	void Render();
	void animationStates();
	//void weatherStates();
	void Inventory();
};