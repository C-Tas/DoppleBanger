#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	virtual void initObject() {};

public:
	Armor(double price, double health, double armor, equipType type) : Equipment(type) {
		price_ = price;
		modifiers_.health_ = health;
		modifiers_.armor_ = armor;
	};
	virtual ~Armor() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
};