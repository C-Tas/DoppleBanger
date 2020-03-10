#pragma once
#include "GameState.h"
class InventoryState :
	public GameState
{
public:
//<summary>Constructora generica</summary>
	InventoryState(Application* app) :GameState(app) {};
	virtual ~InventoryState() {};
	//<summary>Elimina el estado</summary>
	void goToGame();
};

