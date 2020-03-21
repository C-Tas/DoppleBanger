#pragma once

#include "Equipment.h"
#include "SRandBasedGenerator.h"

class GameManager;
class Application;

class RandEquipGen
{
private:
	Application* app_ = nullptr;
	GameManager* gameManager_ = nullptr;
	SRandBasedGenerator rn_;

public:
	RandEquipGen(Application* app);
	Equipment* genEquip();
	Equipment* genEquip(equipType type);
};