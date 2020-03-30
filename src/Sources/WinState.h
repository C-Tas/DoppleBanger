#pragma once
#include "GameState.h"
class WinState : public GameState
{
public:
	WinState(Application* app) : GameState(app) { initState(); }
	~WinState() {}

protected:
	virtual void initState();
};