#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	equipType type_;
	Player* player_ = nullptr;
	int health_ = 0;
	int armor_ = 0;

public:
	Armor(Player* player, Texture* texture, string name, string desc, double price, int health, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), health_(health), armor_(armor), type_(type) {};
	virtual ~Armor() {};

	//Equipar dicho equipamiento
	virtual void equip();

	//Desequiparlo y perder sus stats
	virtual void remove();

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "health: " << health_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};