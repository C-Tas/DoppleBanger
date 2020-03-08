#include "GameStateMachine.h"
#include "MainMenuState.h"

//Inicializa el juego en MainMenuState
GameStateMachine::GameStateMachine()
{
	/*GameState* startedState;
	startedState = new MainMenuState();
	gameStateStack_.push(startedState);*/
}

GameStateMachine::~GameStateMachine()
{
	while (!gameStateStack_.empty())
	{
		delete gameStateStack_.top();
		gameStateStack_.pop();
	}
}
