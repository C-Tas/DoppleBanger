#pragma once

#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"

class Player : public Actor
{
private:
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;

//<summary>Variables relativas a las habilidades</summary>
#pragma region abilities
	int liberation_ = 0;
	bool explotion_ = false;
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region cooldowns
	double clonCooldown_ = 5;
	double clonTime_ = 0;
#pragma endregion

//<summary>Estadisticas del jugador</summary>
#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 10;
	const int AD = 0;
	const int AP = 0;
	const int CRIT = 0;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 5;

	const double CLON_SPAWN_RANGE = 100;
#pragma endregion

public:
//Constructora de player
	Player(Application* app, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) {
		eventHandler_ = HandleEvents::instance();
		initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	};
	~Player() {};
	virtual bool update();
	virtual void onCollider() {};
};