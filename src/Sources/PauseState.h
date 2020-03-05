#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
private:
public:
	PauseState(Application* app = nullptr) :GameState(app) {};
	virtual ~PauseState() {};
	void backToGameState();
	void goControlState();
	void goMainMenuState();
};