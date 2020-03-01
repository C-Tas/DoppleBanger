#include "GameStateMachine.h"

#pragma once Estados
#include "MainMenuState.h"
#include "PauseState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#pragma end;

GameStateMachine::GameStateMachine(Application* app) : app_(app)
{
	//Carga MainMenuState por defecto
	//gameStateStack_.push(new(MainMenuState(app_)));
}
