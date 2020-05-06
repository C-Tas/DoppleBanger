#pragma once
#include "GameState.h"

class LoadState : public GameState
{
public:
	LoadState(Application* app) : GameState(app) { initState(); };
	~LoadState() {};

private:
	//Callbacks
	static void backToPreviousState(Application* app);
	static void loadSlot1(Application* app);
	static void loadSlot2(Application* app);
	static void loadSlot3(Application* app);
	//Inicializa el estado
	virtual void initState();
	//Crea los botones de cargar
	void createLoadButton(ifstream& slot, int numSlot, Vector2D pos, Vector2D scale);
};

