#include "Armor.h"
#include "Player.h"

void Armor::equip(Player* player)
{
	player->addHealth(health_);
	player->addArmor(armor_);
}

void Armor::remove(Player* player)
{
	player->removeHealth(health_);
	player->removeArmor(armor_);
}