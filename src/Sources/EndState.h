#pragma once
#include "GameState.h"

class BeerButton;

class EndState : public GameState
{
public:
	EndState(Application* app) : GameState(app) { initState(); }
	~EndState() {}

private:
	BeerButton* mainMenu_ = nullptr;
	BeerButton* ship_ = nullptr;
	BeerButton* yes_ = nullptr;
	BeerButton* no_ = nullptr;
	bool choosen = false;
	double winWidth = 0;
	double winHeight = 0;

	virtual void initState();
	void changeButtons();
	//Callbacks
	//Para volver al barco
	static void backToShip(Application* app);
	//Para volver al menu principal
	static void backToMainMenu(Application* app);
	//Para escoger opciones
	static void chooseOption(Application* app);
};

