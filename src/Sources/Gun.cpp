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

void Gun::initStats()
{
	modifiers_.crit_ = crit_;
	modifiers_.distDmg_ = ad_;
	modifiers_.distRange_ = disRange_;
	modifiers_.distRate_ = distRate_;
}
