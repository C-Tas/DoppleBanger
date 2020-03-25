#pragma once

#include "Actor.h"
#include "HandleEvents.h"
#include "Enemy.h"

class Player : public Actor
{
private:
	bool attacking = false;

	//Variables relacionadas con los cooldowns
	double lastAttack = 0;
	double meleeCooldown = 0;
	Enemy* objective = nullptr;
	HandleEvents* eventHandler_ = nullptr;

//<summary>Estadisticas del jugador</summary>
#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 10;
	const int AD = 20;
	const int AP = 0;
	const int CRIT = 0;
	const int RANGE = 300;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 5;
	const double DIST_RATE = 10;
#pragma endregion

public:
//Constructora de player
	Player(Application* app, vector<Texture*> texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) {
		eventHandler_ = HandleEvents::instance();
		initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	};
	~Player() { texture_ = nullptr; };

	virtual bool update();
	virtual void onCollider() {};
	void move(Point2D target);
	void attack(Enemy* obj);
};