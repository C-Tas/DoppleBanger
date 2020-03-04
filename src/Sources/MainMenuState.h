#pragma once
#include "GameState.h"
#include "Player.h"

class MainMenuState :
	public GameState
{
private:
	Draw* player_;
public:
	MainMenuState(Application* app = nullptr) : GameState(app) { printf("MainMenuState"); initMenuState(); };
	void initMenuState();
	void goControlState();
	void goCreditsState();
	void goLoadState();
	void goStoryState();
};