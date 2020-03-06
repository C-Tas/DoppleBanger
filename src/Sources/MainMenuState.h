#pragma once
#include "GameState.h"
#include "Player.h" //Include temporal
#include "Equipment.h" //Include temporal

class MainMenuState :
	public GameState
{
private:
	Player* player_ = nullptr;

public:
	MainMenuState(Application* app = nullptr) : GameState(app) { initMenuState(); };
	void initMenuState();
	void goControlState();
	void goCreditsState();
	void goLoadState();
	void goStoryState();
};