#include "Boots.h"
#include "Player.h"

void Boots::equip(Player* player)
{
	player->addMoveSpeed(speed_);
	player->addArmor(armor_);
}

void Boots::remove(Player* player)
{
	player->removeMoveSpeed(speed_);
	player->removeArmor(armor_);
}