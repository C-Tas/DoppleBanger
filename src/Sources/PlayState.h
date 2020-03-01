#pragma once
#include "GameState.h"
class PlayState :
	public GameState
{
public:
	PlayState(Application* app=nullptr) :GameState(app) {};
	void goToPauseState();
	void goToSaveGame();
	void goToInventoryState();
	void goToSelectState();
	void goToStashState();
	//falta otro cambio
};

