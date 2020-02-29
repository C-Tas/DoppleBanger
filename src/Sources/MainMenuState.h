#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
private:
public:
	MainMenuState(Application* app = nullptr) :GameState(app) {};
	void goControlState();
	void goCreditsState();
	void goLoadState();
	void goStoryState();
};