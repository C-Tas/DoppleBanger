#pragma once
#include "GameState.h"
class EndState : public GameState
{
public:
	EndState(Application* app) : GameState(app) { initState(); }
	~EndState() {}

protected:
	virtual void initState();

	//Callbacks
	//Para volver al barco
	static void backToShip(Application* app);
	//Para volver al menu principal
	static void backToMainMenu(Application* app);
};

