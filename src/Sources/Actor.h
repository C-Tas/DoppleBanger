#pragma once

#include "Dynamic.h"
#include "Stats.h"

class Actor : public Dynamic
{
protected:
	Actor(Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea)
		: Dynamic(texture, pos, scale, collisionArea) {};
	Stats currStats_;
	void initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, double moveSpeed, double meleeRate, double distRate);
};

