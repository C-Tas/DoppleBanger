#pragma once
#include"GameState.h"
#include<stack>
using namespace std;
class GameStateMachine
{
private:
	stack<GameState*> gameStateStack_;
	Application* app_ = nullptr;
public:
	GameStateMachine(Application* app);
	virtual ~GameStateMachine() {};

	//<summary>Devuelve el estado actual</summary>
	GameState* getState() { return gameStateStack_.top(); };

	//<summary>Devuelve el puntero a la aplicacion</summary>
	Application* getApp() { return app_; };

	void popState() { if (!gameStateStack_.empty())gameStateStack_.pop(); };
	void pushState(GameState* gameState) { gameStateStack_.push(gameState); };
	void changeState(GameState* gameState) { if (!gameStateStack_.empty())gameStateStack_.pop(); gameStateStack_.push(gameState);};
};

