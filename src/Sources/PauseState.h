#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
private:
public:
	PauseState(Application* app = nullptr) :GameState(app) {};
	void backToGameState();
	void goControlState();
	void goMainMenuState();
};