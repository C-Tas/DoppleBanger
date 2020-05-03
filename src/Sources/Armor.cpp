#include "Armor.h"
#include "Player.h"


void Armor::equip(Player* player)
{
	//Modifica la vida maxima, antes modificaba solo la vida actual
	player->addMaxHealth(modifiers_.health_);
	player->addArmor(modifiers_.armor_);
}

void Armor::remove(Player* player)
{
	//Modifica la vida maxima, antes modificaba solo la vida actual
	player->addMaxHealth(-modifiers_.health_);
	player->removeArmor(modifiers_.armor_);
}