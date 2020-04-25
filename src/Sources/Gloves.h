#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	equipType type_;

public:
	Gloves(Texture* texture, string name, string desc, double price, double crit, double armor) :
		Equipment(texture, name, desc, price, equipType::Gloves), type_(equipType::Gloves) {
		modifiers_.crit_ = crit;
		modifiers_.armor_ = armor;
	};
	virtual ~Gloves() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << "crit: " << modifiers_.crit_ << "\n";
		std::cout << "armor: " << modifiers_.armor_ << "\n";
	};
};