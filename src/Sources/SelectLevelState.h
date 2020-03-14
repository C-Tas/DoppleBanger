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

	///<summary>Callbacks para los botones de este estado</summary>
	///<summary>Go to CarribeanIslandState (change)</summary>
	static void goToIsland0(Application* app);
	///<summary>Go to SpookyIslandState (change)</summary>
	static void goToIsland1(Application* app);
	///<summary>Go to VolcanicIslandState (change)</summary>
	static void goToIsland2(Application* app);

private: 
	int islandsUnlocked_ = 1; //<summary>La primera por defecto siempre est� desbloqueada</summary>
	
	///<summary>M�todo privado para iniciar el estado</summary>
	void initState();

	///<summary>Arrays con la informaci�n de los botones para que su creaci�n dependiendo del n�mero de islas desbloqueadas
	///sea m�s sencilla</summary>
	const array<CallBackOnClick*, 3> functions_ = { goToIsland0, goToIsland1, goToIsland2 };
	const array <Vector2D, 3> buttonPositions_ = { Vector2D(100, 400), Vector2D(800, 400),Vector2D(1300, 400) };
}; 

