#pragma once
#include "GameState.h"
class CreditsState :
	public GameState
{
public:
	CreditsState(Application* app = nullptr) :GameState(app) {};
	virtual ~CreditsState() {};
	void backToPreviousState();
};

