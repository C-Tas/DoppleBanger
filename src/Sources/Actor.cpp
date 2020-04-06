#include "Actor.h"

//Inicialliza los stats
void Actor::initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, double crit,
	double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, meleeDmg, distDmg, crit, meleeRange, distRange, moveSpeed, meleeRate, distRate);
}
 
//A falta de definir la gesti�n del da�o en funci�n de la armadura
bool Actor::reciveDmg(int damage) {
	/*double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;*/
	currStats_.health_ -= damage;
	return currStats_.health_ <= 0;
}