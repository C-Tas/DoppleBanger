#pragma once
#include "GameState.h"

class PauseState : public GameState
{
private:
	void initState(); //Inicializa el estado
	Button* muteButton = nullptr;
	Texture* background_ = nullptr;
	const uint backgroundW = app_->getWindowWidth();
	const uint backgroundH = app_->getWindowHeight();
public:
	PauseState(Application* app = nullptr);
	virtual ~PauseState() {};

	void draw() const;
	void changeMute(); //Cambia la textura del botón mute
};