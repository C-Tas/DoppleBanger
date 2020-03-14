#pragma once

#include "Equipment.h"

class Sword : public Equipment
{
private:
	equipType type_;
	Player* player_ = nullptr;
	int ad_ = 0;
	double meleeRate_ = 0;

public:
	Sword(Player* player, Texture* texture, string name, string desc, double price, int ad, double meleeRate, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), ad_(ad), meleeRate_(meleeRate), type_(type) {};
	virtual ~Sword() {};

	//Equipar dicho equipamiento
	virtual void equip();

	//Desequiparlo y perder sus stats
	virtual void remove();

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "ad: " << ad_ << "\n";
		std::cout << "meleeRate: " << meleeRate_ << "\n";
	};
};

