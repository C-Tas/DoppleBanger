#pragma once
#include "GameState.h"
class ControlsState :
	public GameState
{
private:
public:
	ControlsState(Application* app = nullptr) : GameState(app) {};
	void backToPreviousState() ;
};

