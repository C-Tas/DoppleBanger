#include "Boots.h"
#include "Player.h"
#include "TextBox.h"

void Boots::equip(Player* player)
{
	player->addMoveSpeed(moveSpeed_);
	player->addArmor(armor_);
}

void Boots::remove(Player* player)
{
	player->removeMoveSpeed(moveSpeed_);
	player->removeArmor(armor_);
}

void Boots::getDescription(TextBox* tex)
{
	if (type_ == equipType::BootsI) tex->bootsCaribbean();
	else if (type_ == equipType::BootsII) tex->bootsSpooky();
}
