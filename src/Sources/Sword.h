#pragma once

#include "Equipment.h"

class Sword : public Equipment
{
private:
	equipType type_;
	int ad_ = 0;
	double meleeRate_ = 0;

public:
	Sword(Texture* texture, string name, string desc, double price, int ad, double meleeRate, equipType type) :
		Equipment(texture, name, desc, price, type), ad_(ad), meleeRate_(meleeRate), type_(type) {};
	virtual ~Sword() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "ad: " << ad_ << "\n";
		std::cout << "meleeRate: " << meleeRate_ << "\n";
	};
};

