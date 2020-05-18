#pragma once
#include "GameState.h"

class BeerButton;

class EndState : public GameState
{
public:
	EndState(Application* app) : GameState(app) { initState(); }
	~EndState() {}

private:
	vector<Texture*> rain_;
	BeerButton* mainMenu_ = nullptr;
	BeerButton* ship_ = nullptr;
	BeerButton* yes_ = nullptr;
	BeerButton* no_ = nullptr;
	Uint32 rainTime_ = 100;
	Uint32 lastRainTime_;
	int currRain_ = 0;
	bool choosen = false;
	double winWidth = 0;
	double winHeight = 0;

	virtual void initState();
	void changeButtons();
	virtual void draw() const;
	virtual void update();

	//Callbacks
	//Para volver al barco
	static void backToShip(Application* app);
	//Para volver al menu principal
	static void backToMainMenu(Application* app);
	//Para escoger opciones
	static void chooseOption(Application* app);

	//Dimensiones de las entidades
	const double W_WIN = app_->getWindowWidth();
	const double H_WIN = app_->getWindowHeight();

#pragma region NPCs
	const double W_ELDERMAN = W_WIN * 2 / 10;
	const double H_ELDERMAN = H_WIN * 2 / 6;

	const double W_MERCHANT = W_WIN * 2 / 13;
	const double H_MERCHANT = H_WIN * 2 / 7;

	const double W_CHEF = W_WIN / 22;
	const double H_CHEF = H_WIN / 6;

	const double W_MORTY = W_WIN / 16;
	const double H_MORTY = H_WIN / 5;

	const double W_PARROT = W_WIN / 20;
	const double H_PARROT = H_WIN / 10;

	const double W_SKELETON = W_WIN / 10;
	const double H_SKELETON = H_WIN / 5;

	const double W_CARTOGRAPHER = W_WIN * 2 / 10;
	const double H_CARTOGRAPHER = H_WIN * 2 / 6;
#pragma region
};