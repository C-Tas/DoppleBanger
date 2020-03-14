#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	equipType type_;
	Player* player_ = nullptr;
	int crit_ = 0;
	int armor_ = 0;

public:
	Gloves(Player* player, Texture* texture, string name, string desc, double price, int crit, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), crit_(crit), armor_(armor), type_(type) {};
	virtual ~Gloves() {};

	//Equipar dicho equipamiento
	virtual void equip();

	//Desequiparlo y perder sus stats
	virtual void remove();

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "crit: " << crit_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};