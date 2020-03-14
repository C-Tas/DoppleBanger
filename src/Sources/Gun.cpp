#include "Gun.h"
#include "Player.h"

void Gun::equip()
{
	player_->addAd(ad_);
	player_->addDistRate(distRate_);
}

void Gun::remove()
{
	player_->removeAd(ad_);
	player_->removeDistRate(distRate_);
}