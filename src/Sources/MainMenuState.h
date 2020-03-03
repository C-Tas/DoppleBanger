#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
private:
public:
	MainMenuState(Application* app = nullptr) : GameState(app) { printf("MainMenuState"); initMenuState(); };
	void initMenuState();
	void goControlState();
	void goCreditsState();
	void goLoadState();
	void goStoryState();
};