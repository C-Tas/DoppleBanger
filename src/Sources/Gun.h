#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	Player* player_ = nullptr;
	int ad_ = 0;
	double distRate_ = 0;

public:
	Gun(Player* player, Texture* texture, string name, string desc, double price, int ad, double distRate, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), ad_(ad), distRate_(distRate) {};
	~Gun() {};

	//Equipar dicho equipamiento
	void equip();

	//Desequiparlo y perder sus stats
	void remove();
};

