#pragma once
#include "GameState.h"
#include <fstream>

class SaveState : public GameState
{
public:
	SaveState(Application* app) : GameState(app) { initState(); };
private:
	//Inicializa el estado
	virtual void initState();
	//Callbacks
	static void backToPreviousState(Application* app);
	static void saveGame1();
	static void saveGame2();
	static void saveGame3();
};

