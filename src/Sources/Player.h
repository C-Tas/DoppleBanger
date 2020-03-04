#pragma once
#include "Actor.h"
class Player : public Actor
{
private:
	//Constantes para inicializar el player
#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 10;
	const int AD = 10;			//Attack damage
	const int CRIT = 0;
	const double MOVE_SPEED = 5;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 5;
#pragma endregion

public:
	Player(Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }) : Actor(texture, pos, scale) {
		initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, CRIT, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	};
	~Player() {};
	void update() {};
};