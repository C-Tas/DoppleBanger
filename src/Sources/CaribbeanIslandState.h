#pragma once
#include "PlayState.h"
#include "Chest.h"
class Player;

class CaribbeanIslandState : public PlayState
{
private:
	Chest* chest_ = nullptr; //temporal
public:
//<summary>Constructor de la isla caribeña</summary>
	CaribbeanIslandState(Application* app) : PlayState(app) { initState(); }
//<summary>Destructor de la isla caribeña</summary>
	virtual ~CaribbeanIslandState() {};

	virtual void update();

#pragma region Provisional
	void createMonkey(int numMonkeys);
	void createPirates(int numPirates);
	void createWolves(int numWolves);
	void createChest(int numChest);
	//void addKills() { kills += 1; }
#pragma endregion
protected:
	//Dimensiones de las entidades
	const int W_PLAYER = app_->getWindowWidth() / 40;
	const int H_PLAYER = app_->getWindowHeight() / 15;

	const int W_MONKEY = app_->getWindowWidth() / 20;
	const int H_MONKEY = app_->getWindowHeight() / 15;

	const int NUM_MONKEYS = 1;
	const int NUM_PIRATES = 2;
	const int NUM_WOLVES = 3;
	const int NUM_CHEST = 1;

	virtual void initState();
};

