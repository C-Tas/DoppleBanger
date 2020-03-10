#pragma once
#include "GameState.h"
#include <array>

using CallBackOnClick = void(Application * App);

class SelectLevelState :
	public GameState
{
public:
	SelectLevelState(Application* app, int islandUnlocked = 1);
	virtual ~SelectLevelState() {};

	//Callbacks para los botones de este estado
	static void goToIsland0(Application* app);
	static void goToIsland1(Application* app);
	static void goToIsland2(Application* app);

private: 
	int islandsUnlocked_ = 1; //La primera por defecto siempre est� desbloqueada
	
	//M�todo privado para iniciar el estado
	void initState();

	/*Arrays con la informaci�n de los botones para que su creaci�n dependiendo del n�mero de islas desbloqueadas
	sea m�s sencilla*/
	const array<CallBackOnClick*, 3> functions_ = { goToIsland0, goToIsland1, goToIsland2 };
	const array <Vector2D, 3> buttonPositions_ = { Vector2D(100, 400), Vector2D(800, 400),Vector2D(1300, 400) };
}; 

