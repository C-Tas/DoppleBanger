#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	equipType type_;

public:
	Armor(Texture* texture, string name, string desc, double price, double health, double armor) :
		Equipment(texture, name, desc, price, Armor_), type_(Armor_) {
		modifiers_.health_ = health;
		modifiers_.armor_ = armor;
	};
	virtual ~Armor() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "health: " << modifiers_.health_ << "\n";
		std::cout << "armor: " << modifiers_.armor_ << "\n";
	};
};