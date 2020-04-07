#pragma once
#include "GameState.h"
class InventoryState :
	public GameState
{
public:
//<summary>Constructora generica</summary>
	InventoryState(Application* app) :GameState(app) { initState(); };
	virtual ~InventoryState() {};

protected:
	virtual void initState();
	static void goToGame(Application* app);
};

