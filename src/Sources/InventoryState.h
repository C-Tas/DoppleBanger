#pragma once
#include "GameState.h"
class InventoryState :
	public GameState
{
public:
	InventoryState(Application* app) :GameState(app) {};
	void goToGame();
};

