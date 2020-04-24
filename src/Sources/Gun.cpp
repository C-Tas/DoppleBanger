#include "Gun.h"
#include "Player.h"

void Gun::equip(Player* player)
{
	player->addDistDmg(modifiers_.distDmg_);
	player->addDistRate(modifiers_.distRate_);
}

void Gun::remove(Player* player)
{
	player->removeDistDamage(modifiers_.distDmg_);
	player->removeDistRate(modifiers_.distRate_);
}