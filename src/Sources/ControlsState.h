#pragma once
#include "GameState.h"
class ControlsState :
	public GameState
{

public:
//<summary>Constructor del estado de los controles</summary>
	ControlsState(Application* app = nullptr) : GameState(app) {};
//<summary>Destructor del estado de los controles</summary>
	virtual ~ControlsState() {};
//<summary>Nos devuelve al estado anterior</summary>
	void backToPreviousState() ;
};

