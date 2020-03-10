#pragma once

#include "Equipment.h"
#include "SRandBasedGenerator.h"

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