#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
private:
public:
	///<summary>Constructora PauseState</summary>
	PauseState(Application* app = nullptr) :GameState(app) {};
	///<summary>Destructora</summary>
	virtual ~PauseState() {};
	///<summary>Vuelve a playState (pop)</summary>
	static void backToGameState(Application* app);
	///<summary>Push a controlState</summary>
	static void goControlState(Application* app);
	///<summary>Vuelta al menú principal, borra todos los estados menos el primero</summary>
	static void goMainMenuState(Application* app);
};