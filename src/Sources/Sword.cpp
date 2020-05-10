#include "Sword.h"
#include "Player.h"
#include "TextBox.h"

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
	else if (type_ == equipType::SwordII) tex->swordSpooky();
	else if (type_ == equipType::SaberI) tex->saberCaribbean();
	else if (type_ == equipType::SaberI) tex->saberSpooky();
}
