#pragma once
#include "GameState.h"
class SaveLoadState :
	public GameState
{
public:
	SaveLoadState(Application* app = nullptr) :GameState(app) {};
	void goToGame();
	void goToMainMenu();

};

