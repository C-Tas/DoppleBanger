#include "Sword.h"
#include "Player.h"

void Sword::equip(Player* player)
{
	player->addMeleeDmg(modifiers_.meleeDmg_);
	player->addMeleeRate(modifiers_.meleeRate_);
}

void Sword::remove(Player* player)
{
	player->removeMeleeDamage(modifiers_.meleeDmg_);
	player->removeMeleeRate(modifiers_.meleeRate_);
}