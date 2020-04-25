#pragma once

#include "Equipment.h"

class Sword : public Equipment
{
private:
	equipType type_;

public:
	Sword(Texture* texture, string name, string desc, double price, double meleeDamage, double meleeRate, equipType type) :
		Equipment(texture, name, desc, price, type), type_(type) {
		modifiers_.meleeDmg_ = meleeDamage;
		modifiers_.meleeRate_ = meleeRate;
	};
	virtual ~Sword() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << "meleeDamage: " << modifiers_.meleeDmg_ << "\n";
		std::cout << "meleeRate: " << modifiers_.meleeRate_ << "\n";
	};
};

