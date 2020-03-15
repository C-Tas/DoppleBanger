#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	equipType type_;
	int health_ = 0;
	int armor_ = 0;

public:
	Armor(Texture* texture, string name, string desc, double price, int health, int armor) :
		Equipment(texture, name, desc, price, Armor_), health_(health), armor_(armor), type_(Armor_) {};
	virtual ~Armor() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "health: " << health_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};