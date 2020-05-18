#include "Gun.h"
#include "Player.h"
#include "TextBox.h"

void Gun::initObject()
{
	if (type_ == equipType::PistolI || type_ == equipType::PistolII) {
		bulletSpeed_ = PISTOL_BULLET_SPEED;
		distRange_ = PISTOL_BULLET_RANGE;
	}
	else if (type_ == equipType::ShotgunI || type_ == equipType::ShotgunII) {
		bulletSpeed_ = SHOTGUN_BULLET_SPEED;
		distRange_ = SHOTGUN_BULLET_RANGE;
	}
}

void Gun::equip(Player* player)
{
	player->addDistDmg(distDmg_);
	player->addDistRange(distRange_);
	player->addDistRate(distRate_);
}

void Gun::remove(Player* player)
{
	player->removeDistDamage(distDmg_);
	player->removeDistRange(distRange_);
	player->removeDistRate(distRate_);
}

void Gun::getDescription(TextBox* tex)
{
	if (type_ == equipType::PistolI) tex->pistolCaribbean();
	else if (type_ == equipType::PistolII) tex->pistolSpooky();
	else if (type_ == equipType::ShotgunI) tex->blunderbussCaribbean();
	else if (type_ == equipType::ShotgunII) tex->blunderbussSpooky();
}
