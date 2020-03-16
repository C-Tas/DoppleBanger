#pragma once

#include "Equipment.h"
#include "SRandBasedGenerator.h"

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