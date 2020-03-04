#pragma once
#include "Dynamic.h"
class Actor : public Dynamic
{
private:
	struct stats
	{
		int health_ = 0;
		int mana_ = 0;
		double manaReg_ = 0;
		int armor_ = 0;
		int ad_ = 0;//Attack damage
		int crit_ = 0;
		double moveSpeed_ = 0;
		double meleeRate_ = 0;
		double distRate_ = 0;
		stats(int health, int mana, int manaReg, int armor, int ad, int crit, double moveSpeed, double meleeRate, double distRate) :
			health_(health), mana_(mana), manaReg_(manaReg), armor_(armor), ad_(ad), crit_(crit), moveSpeed_(moveSpeed), meleeRate_(meleeRate), distRate_(distRate) {};
		stats() {
			health_, mana_, manaReg_, armor_, ad_, crit_, moveSpeed_, meleeRate_, distRate_ = 0;
		}
	};

protected:
	Actor() {};
	Actor(Vector2D dir, Texture* texture, SDL_Rect* destiny, Vector2D pos, Vector2D scale, SDL_Rect* collisionArea)
		: Dynamic(dir, texture, destiny, pos, scale, collisionArea) {};
	stats currStats;
	void initStats(int health, int mana, int manaReg, int armor, int ad, int crit, double moveSpeed, double meleeRate, double distRate);
};

