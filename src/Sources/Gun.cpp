#include "Gun.h"
#include "Player.h"

void Gun::initObject()
{
	if (type_ == equipType::PistolI || type_ == equipType::PistolII) {
		bulletSpeed_ = PISTOL_BULLET_SPEED;
		modifiers_.distRange_ = PISTOL_BULLET_RANGE;
	}
	else if (type_ == equipType::ShotgunI || type_ == equipType::ShotgunII) {
		bulletSpeed_ = SHOTGUN_BULLET_SPEED;
		modifiers_.distRange_ = SHOTGUN_BULLET_RANGE;
	}
}

void Gun::equip(Player* player)
{
	player->addDistDmg(modifiers_.distDmg_);
	player->addDistRange(modifiers_.distRange_);
	player->addDistRate(modifiers_.distRate_);
}

void Gun::remove(Player* player)
{
	player->removeDistDamage(modifiers_.distDmg_);
	player->removeDistRange(modifiers_.distRange_);
	player->removeDistRate(modifiers_.distRate_);
}
