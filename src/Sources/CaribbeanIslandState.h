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

	virtual void update();


#pragma region Provisional
	void createMonkey(int numMonkeys);
	void addKills() { kills += 1; }
#pragma endregion
protected:
	//Dimensiones de las entidades
	const uint wPlayer = app_->getWindowWidth() / 40;
	const uint hPlayer = app_->getWindowHeight() / 15;

	const uint wMonkey = app_->getWindowWidth() / 20;
	const uint hMonkey = app_->getWindowHeight() / 15;

	//Lista de los enemigos de la isla
	list<Enemy*> enemies_;
	const int numMonkeys_ = 1; //Número de cangrejos que sea van a crear
	int kills = 0; //Kills del state para saber si se gana

	virtual void initState();
};

