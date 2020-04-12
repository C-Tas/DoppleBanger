#include "Sword.h"
#include "Player.h"

void Sword::equip(Player* player)
{
	player->addMeleeDmg(ad_);
	player->addMeleeRate(meleeRate_);
}

void Sword::remove(Player* player)
{
	player->removeAd(ad_);
	player->removeMeleeRate(meleeRate_);
}