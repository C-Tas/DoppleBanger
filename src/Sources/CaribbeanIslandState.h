#pragma once
#include "PlayState.h"
class Player;

class CaribbeanIslandState : public PlayState
{
public:
//<summary>Constructor de la isla caribeña</summary>
	CaribbeanIslandState(Application* app) : PlayState(app) { initState(); }
//<summary>Destructor de la isla caribeña</summary>
	virtual ~CaribbeanIslandState() {};

private:
	//Dimensiones de las entidades
	const uint wPlayer = app_->getWindowWidth() / 40;
	const uint hPlayer = app_->getWindowHeight() / 15;

	const uint wCrab = app_->getWindowWidth() / 40;
	const uint hCrab = app_->getWindowHeight() / 30;

	//Lista de los enemigos de la isla
	list<Enemy*> enemies_;
	const int numCrabs_ = 2; //Número de cangrejos que sea van a crear

	void initState();
#pragma region Provisional
	void createCrab(int numCrabs);
#pragma endregion
};

