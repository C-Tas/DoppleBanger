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
void GameStateMachine::popState() { 
	if (!gameStateStack_.empty()) { 
		GameState* n = gameStateStack_.top();
		delete n; gameStateStack_.pop();
	}
}
void GameStateMachine::clearAllStateExceptFirst() {
	for (int i = 0; i < gameStateStack_.size() + 1; i++) popState();
	gameStateStack_.top()->resetState();
	GameManager::instance()->resetGame();
}