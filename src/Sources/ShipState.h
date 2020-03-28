#pragma once
#include "PlayState.h"

class Player;
class ShipObject;
class Trigger;

class ShipState : public PlayState
{
private:
	void initState();

#pragma region Testeo
	ShipObject* stash_ = nullptr;
	ShipObject* door_ = nullptr;
	ShipObject* wheel_ = nullptr;
	Trigger* exit_ = nullptr;

	SDL_Point mouse; //Para guardar la posición del clik del ratón
	bool stashClick = false; //Para saber si se ha pulsado el objeto
	bool doorClick = false;
	bool wheelClick = false; 
#pragma endregion	

	//Dimensiones de las entidades
	const uint wStash = app_->getWindowWidth() / 7;
	const uint hStash = app_->getWindowHeight() / 6;

	const uint wDoor = app_->getWindowWidth() / 8;
	const uint hDoor = app_->getWindowHeight() / 8;

	const uint wWheel = app_->getWindowWidth() / 11;
	const uint hWheel = app_->getWindowHeight() / 5;

	const uint wExit = app_->getWindowWidth() / 30;
	const uint hExit = app_->getWindowHeight() / 5;
public:
	///<summary> Constructora del barco</summary>
	ShipState(Application* app) : PlayState(app) { initState(); }
	virtual ~ShipState() {}
	
	void update();
};