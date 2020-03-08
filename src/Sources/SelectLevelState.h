#pragma once
#include "GameState.h"
#include <array>

using CallBackOnClick = void(Application * App);
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

	//Arrays con la información de los botones para que su creación dependiendo del número de islas desbloqueadas
	//sea más sencilla
	const array<CallBackOnClick*, 3> functions_ = { goToIsland0, goToIsland1, goToIsland2 };
	const array <Vector2D, 3> buttonPositions_ = { Vector2D(100, 400), Vector2D(800, 400),Vector2D(1300, 400) };
}; 

