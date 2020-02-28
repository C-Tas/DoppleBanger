#pragma once
#include"GameState.h"
#include<stack>
using namespace std;
class GameStateMachine
{
private:
	stack<GameState*> gameStateStack_;
public:
	GameStateMachine();
	virtual ~GameStateMachine() {};
	GameState* GetState() { return gameStateStack_.top(); };
	void PopState() { if (!gameStateStack_.empty())gameStateStack_.pop(); };
	void PushState(GameState* gameState) { gameStateStack_.push(gameState); };
	void ChangeState(GameState* gameState) { if (!gameStateStack_.empty())gameStateStack_.pop(); gameStateStack_.push(gameState);};
};

