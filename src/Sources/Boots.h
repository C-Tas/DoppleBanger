#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	equipType type_;

public:
	Boots(Texture* texture, string name, string desc, double price, double speed, double armor) :
		Equipment(texture, name, desc, price, equipType::Boots), type_(equipType::Boots) {
		modifiers_.moveSpeed_ = speed;
		modifiers_.armor_ = armor;
	};
	virtual ~Boots() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << "speed: " << modifiers_.moveSpeed_ << "\n";
		std::cout << "armor: " << modifiers_.armor_ << "\n";
	};
};

