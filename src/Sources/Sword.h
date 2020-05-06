#pragma once
#include "Equipment.h"

class Sword : public Equipment
{
private:
	virtual void initObject() {};

public:
	Sword(Application* app, double price, double meleeDamage, double meleeRate, equipType type) : Equipment(app, type) {
		price_ = price;
		modifiers_.meleeDmg_ = meleeDamage;
		modifiers_.meleeRate_ = meleeRate;
	};
	virtual ~Sword() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
};

