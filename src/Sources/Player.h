#pragma once

#include "Actor.h"
#include "HandleEvents.h"

class Player : public Actor
{
private:
	HandleEvents* eventHandler_ = nullptr;

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
#pragma endregion

public:
//Constructora de player
	Player(Application* app, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) {
		eventHandler_ = HandleEvents::instance();
		initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	};
	~Player() { texture_ = nullptr; };
	virtual bool update();
	virtual void onCollider() {};
	virtual void stop() { dir_ = Vector2D(0, 0); }
};