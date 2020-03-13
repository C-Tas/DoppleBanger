#pragma once
#include "GameState.h"
class ControlsState : public GameState
{
private:
	//Variables de la imagen que mostrará la configuración de controles
	Texture* controlsImage_;
	const uint controlsW = app_->getWindowWidth();
	const uint controlsH = app_->getWindowHeight();
	void initState();
public:
//<summary>Constructor del estado de los controles</summary>
	ControlsState(Application* app = nullptr) : GameState(app) { initState(); }
	virtual void draw() const;
	virtual ~ControlsState() { controlsImage_ = nullptr; }

//<summary>Nos devuelve al estado anterior</summary>
	void backToPreviousState();

};

