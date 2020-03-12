#pragma once

#include "SRandBasedGenerator.h"
#include "Armor.h"
#include "Boots.h"
#include "Gloves.h"
#include "Gun.h"
#include "Sword.h"

class Application;

class RandEquipGen
{
private:
	Application* app_ = nullptr;
	SRandBasedGenerator rn_;

public:
	RandEquipGen(Application* app);
	Equipment* genEquip();
	Equipment* genEquip(equipType type);
};