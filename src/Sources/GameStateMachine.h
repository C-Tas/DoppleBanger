#pragma once
#include<stack>
#include "checkML.h"

class GameState;
class PlayState;

using namespace std;
class GameStateMachine
{
private:
	stack<GameState*> gameStateStack_;
public:
	GameStateMachine();
	virtual ~GameStateMachine();

	//<summary>Devuelve el estado actual</summary>
	GameState* getState() { return gameStateStack_.top(); };
	void popState();
	void pushState(GameState* gameState) { gameStateStack_.push(gameState); };
	void changeState(GameState* gameState) { popState(); gameStateStack_.push(gameState);};
	void clearAllStateExceptFirst();
};

