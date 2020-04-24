#include "Boots.h"
#include "Player.h"

void Boots::equip(Player* player)
{
	player->addMoveSpeed(modifiers_.moveSpeed_);
	player->addArmor(modifiers_.armor_);
}

void Boots::remove(Player* player)
{
	player->removeMoveSpeed(modifiers_.moveSpeed_);
	player->removeArmor(modifiers_.armor_);
}