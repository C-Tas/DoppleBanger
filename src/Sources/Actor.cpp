#include "Actor.h"

void Actor::initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, ad, ap, crit, moveSpeed, meleeRate, distRate);
}
