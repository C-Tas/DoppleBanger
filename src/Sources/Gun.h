#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	virtual void initObject() {};

public:
	Gun(double price, double distDamage, double distRate, equipType type) : Equipment(type) {
		price_ = price;
		modifiers_.distDmg_ = distDamage;
		modifiers_.distRate_ = distRate;
	};
	virtual ~Gun() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
};

