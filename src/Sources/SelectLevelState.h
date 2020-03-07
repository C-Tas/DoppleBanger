#pragma once
#include "GameState.h"

//Callbacks para los botones de este estado
void goToIsland0(Application* app);
void goToIsland1(Application* app);
void goToIsland2(Application* app);

class SelectLevelState :
	public GameState
{
public:
	SelectLevelState(Application* app, int islandUnlocked  = 1);
	virtual ~SelectLevelState() {};
	void initState();

private: 
	int islandsUnlocked_ = 1; //La primera por defecto siempre está desbloqueada
};

