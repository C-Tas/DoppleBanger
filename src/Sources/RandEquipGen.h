#pragma once

#include "SRandBasedGenerator.h"
#include "Armor.h"
#include "Boots.h"
#include "Gloves.h"
#include "Gun.h"
#include "Sword.h"

class GameManager;


class RandEquipGen
{
private:
	GameManager* gameManager_ = nullptr;
	SRandBasedGenerator rn_;

public:
	RandEquipGen(GameManager* gm);
	Equipment* genEquip();
	Equipment* genEquip(equipType type);
};