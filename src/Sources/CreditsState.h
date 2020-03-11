#pragma once
#include "GameState.h"
class CreditsState :
	public GameState
{
public:
	///<summary>Constructora de CreditsState</summary>
	CreditsState(Application* app = nullptr) :GameState(app) {};
	///<summary>Destructora</summary>
	virtual ~CreditsState() {};
	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	static void backToPreviousState(Application* app);
};

