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
	virtual void draw()const;
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

	//Dimensiones de las entidades
	const uint W_WIN = app_->getWindowWidth();
	const uint H_WIN = app_->getWindowHeight();

	const uint W_STASH = W_WIN / 7;
	const uint H_STASH = H_WIN / 6;

	const uint W_DOOR = W_WIN / 8;
	const uint H_DOOR = H_WIN / 8;

	const uint W_WHEEL = W_WIN / 11;
	const uint H_WHEEL = H_WIN / 5;

	const uint W_EXIT = W_WIN / 15;
	const uint H_EXIT = H_WIN / 3;

	const uint W_PLAYER = W_WIN / 25;
	const uint H_PLAYER = H_WIN / 10;
	#pragma endregion

	void initState();
	#pragma region Callbacks
	static void goIsland(Application* app);
	static void goStashState(Application* app);
	static void goMap(Application* app);
	static void goSaveState(Application* app);
	#pragma endregion
};