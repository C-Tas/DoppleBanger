#include "Sword.h"
#include "Player.h"

void Sword::equip()
{
	player_->addAd(ad_);
	player_->addMeleeRate(meleeRate_);
}

void Sword::remove()
{
	player_->removeAd(ad_);
	player_->removeMeleeRate(meleeRate_);
}