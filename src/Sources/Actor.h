#pragma once

#include "Dynamic.h"
#include "Stats.h"

class Actor : public Dynamic
{
protected:
///<summary>Constructor de la clase Actor</summary>
	Actor(Application* app, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea)
		: Dynamic(app, texture, pos, scale, collisionArea) {};
	Stats currStats_;
///<summary>Destructor de la clase Actor</summary>
	virtual ~Actor(){};
	//<summary>Inicializa todas las stats</summary>
	void initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, double moveSpeed, double meleeRate, double distRate);
};

