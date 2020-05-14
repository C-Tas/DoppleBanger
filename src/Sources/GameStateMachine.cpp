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
	while (gameStateStack_.size() > 1) {
		popState();
	}
	//Se necesita resetear para saber si existen partidas guardadas y así actualizar 
	//el botón de cargar partida de la interfaz de MainMenuState
	
	gameStateStack_.top()->resetState();
	GameManager::instance()->resetGameManager();
}