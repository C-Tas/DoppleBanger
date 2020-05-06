#pragma once
#include "GameState.h"

class SaveState : public GameState
{
public:
	SaveState(Application* app) : GameState(app) { initState(); };
private:
	//Callbacks
	static void backToPreviousState(Application* app);
	static void saveSlot1();
	static void saveSlot2();
	static void saveSlot3();
	//Inicializa el estado
	virtual void initState();
};

