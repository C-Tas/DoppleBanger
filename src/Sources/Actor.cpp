#include "Actor.h"

void Actor::initStats(int health, int mana, int manaReg, int armor, int ad, int crit, double moveSpeed, double meleeRate, double distRate)
{
	currStats = stats(health, mana, manaReg, armor, ad, crit, moveSpeed, meleeRate, distRate);
}
