#include "Gloves.h"
#include "Player.h"

void Gloves::equip()
{
	player_->addCrit(crit_);
	player_->addArmor(armor_);
}

void Gloves::remove()
{
	player_->removeCrit(crit_);
	player_->removeArmor(armor_);
}