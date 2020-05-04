#include "Armor.h"
#include "Player.h"


void Armor::equip(Player* player)
{
	//Se mantiene la proporcion entre la vida actual y la vida maxima
	//para que cuando se aumente la vida al equipar, tambien aumente
	//la vida acutal.
	double maxHealth_ = player->getMaxHealth();
	double prop = player->getStats().health_ / maxHealth_;
	//Modifica la vida maxima, antes modificaba solo la vida actual
	player->addMaxHealth(modifiers_.health_);
	maxHealth_ += modifiers_.health_;
	//Se modifica la vida actual en funcion de la proporcion con la vida
	//maxima anterior. se mantiene la proporcion
	player->setHealth(maxHealth_ * prop);
	player->addArmor(modifiers_.armor_);
}

void Armor::remove(Player* player)
{
	//Se mantiene la proporcion entre la vida actual y la vida maxima
	//para que cuando se aumente la vida al equipar, tambien aumente
	//la vida acutal.
	double maxHealth_ = player->getMaxHealth();
	double prop = player->getStats().health_ / maxHealth_;
	//Se modifica la vida actual en funcion de la proporcion con la vida
	//maxima anterior. se mantiene la proporcion
	player->addMaxHealth(-modifiers_.health_);
	maxHealth_ -= modifiers_.health_;
	//Se modifica la vida actual en funcion de la proporcion
	player->setHealth(maxHealth_ * prop);
	player->removeArmor(modifiers_.armor_);
}