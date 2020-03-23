#include "Actor.h"

void Actor::initStats(int health, int mana, double manaReg, int armor, int ad, int ap, int crit, int moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, ad, ap, crit, moveSpeed, meleeRate, distRate);
}
