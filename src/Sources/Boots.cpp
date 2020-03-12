#include "Boots.h"
#include "Player.h"

void Boots::equip()
{
	player_->addMoveSpeed(speed_);
	player_->addArmor(armor_);
}

void Boots::remove()
{
	player_->removeMoveSpeed(speed_);
	player_->removeArmor(armor_);
}