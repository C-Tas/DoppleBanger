#pragma once
#include "GameState.h"

class PauseState : public GameState
{
private:
	void initState(); //Inicializa el estado

public:
	PauseState(Application* app = nullptr);
	virtual ~PauseState() {};

	void changeMute();
};