#include "Sword.h"
#include "Player.h"

void Sword::equip(Player* player)
{
	player->addMeleeDmg(meleeDmg_);
	player->addMeleeRate(meleeRate_);
}

void Sword::remove(Player* player)
{
	player->removeMeleeDamage(meleeDmg_);
	player->removeMeleeRate(meleeRate_);
}

void Sword::getDescription(TextBox* tex)
{
	if (type_ == equipType::SwordI) tex->swordCaribbean();
	else if (type_ == equipType::SwordII) tex->saberSpooky();
}
