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
	static void saveSlot1();
	static void saveSlot2();
	static void saveSlot3();
};

