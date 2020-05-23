#include "Gloves.h"
#include "Player.h"
#include "TextBox.h"

void Gloves::equip(Player* player)
{
	player->addCrit(crit_);
	player->addArmor(armor_);
}

void Gloves::remove(Player* player)
{
	player->addCrit(-crit_);
	player->addCrit(-armor_);
}

void Gloves::getDescription(TextBox* tex)
{
	if (type_ == equipType::GlovesI) tex->glovesCaribbean();
	else if (type_ == equipType::GlovesII) tex->glovesSpooky();
}
