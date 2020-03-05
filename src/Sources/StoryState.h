#pragma once
#include "GameState.h"
class StoryState :
	public GameState
{
public:
	StoryState(Application* app = nullptr) :GameState(app) {};
	virtual ~StoryState() {};
	void goToGame();
};

