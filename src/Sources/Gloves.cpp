#include "Gloves.h"
#include "Player.h"

void Gloves::equip(Player* player)
{
	player->addCrit(crit_);
	player->addArmor(armor_);
}

void Gloves::remove(Player* player)
{
	player->removeCrit(crit_);
	player->removeArmor(armor_);
}