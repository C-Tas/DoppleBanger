#pragma once
#include "GameState.h"
class PlayState :
	public GameState
{
public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app=nullptr) :GameState(app) {};
	///<summary>Destructora</summary>
	virtual ~PlayState() {};
	///<summary>Ir a pauseState (push)</summary>
	static void goToPauseState(Application* app);
	///<summary>Ir a SaveGameState (push)</summary>
	static void goToSaveGame(Application* app);
	///<summary>Ir a InventoryState (push)</summary>
	static void goToInventoryState(Application* app);
	///<summary>Ir a SelectLevelState (push)</summary>
	static void goToSelectState(Application* app);
	///<summary>Ir a StashState (push)</summary>
	static void goToStashState(Application* app);
	//falta otro cambio
};

