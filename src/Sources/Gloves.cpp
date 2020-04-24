#include "Gloves.h"
#include "Player.h"

void Gloves::equip(Player* player)
{
	player->addCrit(modifiers_.crit_);
	player->addArmor(modifiers_.armor_);
}

void Gloves::remove(Player* player)
{
	player->removeCrit(modifiers_.crit_);
	player->removeArmor(modifiers_.armor_);
}