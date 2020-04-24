#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	equipType type_;

public:
	Gun(Texture* texture, string name, string desc, double price, double distDamage, double distRate, equipType type) :
		Equipment(texture, name, desc, price, type), type_(type) {
		modifiers_.distDmg_ = distDamage;
		modifiers_.distRate_ = distRate;
	};
	virtual ~Gun() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "distDamage: " << modifiers_.distDmg_ << "\n";
		std::cout << "distRate: " << modifiers_.distRate_ << "\n";
	};
};

