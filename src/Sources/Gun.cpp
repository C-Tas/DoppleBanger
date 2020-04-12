#include "Gun.h"
#include "Player.h"

void Gun::equip(Player* player)
{
	player->addMeleeDmg(ad_);
	player->addDistRate(distRate_);
}

void Gun::remove(Player* player)
{
	player->removeAd(ad_);
	player->removeDistRate(distRate_);
}