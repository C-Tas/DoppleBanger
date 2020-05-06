#pragma once
#include "GameState.h"
class ControlsState : public GameState
{
public:
//<summary>Constructor del estado de los controles</summary>
	ControlsState(Application* app = nullptr) : GameState(app) { initState(); }
	virtual ~ControlsState() {}

private:
	void initState();
};

