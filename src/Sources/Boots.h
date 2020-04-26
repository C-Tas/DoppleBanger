#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	virtual void initObject() {};

public:
	Boots(double price, double speed, double armor, equipType type) : Equipment(type) {
		price_ = price;
		modifiers_.moveSpeed_ = speed;
		modifiers_.armor_ = armor;
	};
	virtual ~Boots() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
};

