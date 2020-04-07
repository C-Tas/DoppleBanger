#pragma once
#include "PlayState.h"

class Player;
class ShipObject;
class Trigger;

class ShipState : public PlayState
{
public:
	///<summary> Constructora del barco</summary>
	ShipState(Application* app) : PlayState(app) { initState(); }
	virtual ~ShipState() {}
	
	void update();

private:
	//Tiempo para que canten los piratas
	Uint32 pirateSingers_ = 18000;
	Uint32 startInstance_ = 0;
	bool songActive = false;

	//Para guardar la posición del clik del ratón  
	SDL_Point mouse; 

	#pragma region ShipObjects
	ShipObject* stash_ = nullptr;//Alijo
	ShipObject* door_ = nullptr; //Trampilla
	ShipObject* wheel_ = nullptr;//Timón
	ShipObject* exit_ = nullptr; //Salida

	//Para saber si se ha pulsado el objeto
	bool stashClick = false; 
	bool doorClick = false;
	bool wheelClick = false; 
	bool exitClick = false;

	//Dimensiones de las entidades
	const uint W_STASH = app_->getWindowWidth() / 7;
	const uint H_STASH = app_->getWindowHeight() / 6;

	const uint W_DOOR = app_->getWindowWidth() / 8;
	const uint H_DOOR = app_->getWindowHeight() / 8;

	const uint W_WHEEL = app_->getWindowWidth() / 11;
	const uint H_WHEEL = app_->getWindowHeight() / 5;

	const uint W_EXIT = app_->getWindowWidth() / 15;
	const uint H_EXIT = app_->getWindowHeight() / 3;

	const uint W_PLAYER = app_->getWindowWidth() / 25;
	const uint H_PLAYER = app_->getWindowHeight() / 10;
	#pragma endregion

	void initState();
	#pragma region Callbacks
	static void goIsland(Application* app);
	static void goStashState(Application* app);
	static void goMap(Application* app);
	static void goSaveState(Application* app);
	#pragma endregion
};