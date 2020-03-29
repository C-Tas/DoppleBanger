#include "Actor.h"

//Inicialliza los stats
void Actor::initStats(double health, double mana, double manaReg, double armor, double ad, double ap, double crit, double range, double moveSpeed, double meleeRate, double distRate)
{
	currStats_ = Stats(health, mana, manaReg, armor, ad, ap, crit, range, moveSpeed, meleeRate, distRate);
}
 
//A falta de definir la gesti�n del da�o en funci�n de la armadura
void Actor::reciveDmg(int damage) {
	double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;
}

//A falta de definir la gesti�n del da�o en funci�n de la armadura
void Actor::reciveDmg(int damage) {
	double finalDamage = (currStats_.armor_ * damage) / 100;
	currStats_.health_ -= finalDamage;
}