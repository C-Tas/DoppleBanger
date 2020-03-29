#pragma once
#include "GameState.h"
class StashState : public GameState
{
private:
	void initState();

public:
	StashState(Application* app = nullptr) : GameState(app) { initState(); };
	virtual ~StashState() {};
};

