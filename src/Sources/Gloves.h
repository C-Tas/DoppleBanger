#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	virtual void initObject() {};
public:
	Gloves(double price, double crit, double armor, equipType type) : Equipment(type) {
		price_ = price;
		modifiers_.crit_ = crit;
		modifiers_.armor_ = armor;
	};
	virtual ~Gloves() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
};