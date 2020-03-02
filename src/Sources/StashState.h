#pragma once
#include "GameState.h"
class StashState :
	public GameState
{
public:
	StashState(Application* app = nullptr) : GameState(app) {};
	virtual ~StashState() {};
	void backToPrevious();
};

