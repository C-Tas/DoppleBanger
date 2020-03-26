#pragma once
#include "GameState.h"

class Player;

class PlayState : public GameState
{
protected:
	Player* player_ = nullptr;
	Texture* background_ = nullptr;

	//Dimensiones de las entidades
	const uint wPlayer = app_->getWindowWidth() / 15;
	const uint hPlayer = app_->getWindowHeight() / 4;
public:
	///<summary>Constructora PlayState</summary>
	PlayState(Application* app);
	///<summary>Destructora</summary>
	virtual ~PlayState() {};
	///<summary>Ir a pauseState (push)</summary>
	static void goToPauseState(Application* app);
	///<summary>Ir a InventoryState (push)</summary>
	static void goToInventoryState(Application* app);

	void draw() const;
};

