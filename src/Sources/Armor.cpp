#include "Armor.h"
#include "Player.h"

void Armor::equip()
{
	player_->addHealth(health_);
	player_->addArmor(armor_);
}

void Armor::remove()
{
	player_->removeHealth(health_);
	player_->removeArmor(armor_);
}