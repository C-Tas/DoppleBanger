#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	equipType type_;
	Player* player_ = nullptr;
	int ad_ = 0;
	double distRate_ = 0;

public:
	Gun(Player* player, Texture* texture, string name, string desc, double price, int ad, double distRate, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), ad_(ad), distRate_(distRate), type_(type) {};
	virtual ~Gun() {};

	//Equipar dicho equipamiento
	virtual void equip();

	//Desequiparlo y perder sus stats
	virtual void remove();

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "ad: " << ad_ << "\n";
		std::cout << "distRate: " << distRate_ << "\n";
	};
};

