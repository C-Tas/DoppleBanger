#include "Armor.h"
#include "Player.h"


void Armor::equip(Player* player)
{
	player->addHealth(modifiers_.health_);
	player->addArmor(modifiers_.armor_);
}

void Armor::remove(Player* player)
{
	player->removeHealth(modifiers_.health_);
	player->removeArmor(modifiers_.armor_);
}