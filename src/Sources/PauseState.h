#pragma once
#include "GameState.h"

//HAY QUE MEJORAR LO DEL BOTON DE MUTE PORQUE SIEMPRE QUE SE CREA EL ESTADO SE CREA EN MUTE_ON
class PauseState : public GameState
{
private:
	void initState(); //Inicializa el estado
	Button* muteButton = nullptr;
	const uint backgroundW = app_->getWindowWidth();
	const uint backgroundH = app_->getWindowHeight();
public:
	PauseState(Application* app = nullptr);
	virtual ~PauseState() {};

	void changeMute(); //Cambia la textura del botón mute
};