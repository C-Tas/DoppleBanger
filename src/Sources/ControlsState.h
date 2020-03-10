#pragma once
#include "GameState.h"
class ControlsState :
	public GameState
{

public:
	ControlsState(Application* app = nullptr) : GameState(app) {};
	virtual ~ControlsState() {};
	void backToPreviousState() ;
};

