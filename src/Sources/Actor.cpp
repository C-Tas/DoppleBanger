#include "Actor.h"

//Inicialliza los stats
void Actor::initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, ad, ap, crit, moveSpeed, meleeRate, distRate);
}
 
//A falta de definir la gestión del daño en función de la armadura
void Actor::reciveDmg(int damage) {
	double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;
}
