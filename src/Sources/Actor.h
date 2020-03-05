#pragma once

#include "Dynamic.h"
#include "Stats.h"

class Actor : public Dynamic
{
protected:
	Actor() {};
	Actor(Vector2D dir, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea)
		: Dynamic(dir, texture, pos, scale, collisionArea) {};
	Stats currStats;
	void initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, double moveSpeed, double meleeRate, double distRate);
};

