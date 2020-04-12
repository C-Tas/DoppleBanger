#pragma once
#include "GameState.h"
class EndState : public GameState
{
public:
	EndState(Application* app) : GameState(app) { initState(); }
	~EndState() {}

protected:
	virtual void initState();
};

