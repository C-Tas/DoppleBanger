#pragma once

#include "Equipment.h"

class Sword : public Equipment
{
private:
	Player* player_ = nullptr;
	int ad_ = 0;
	double meleeRate_ = 0;

public:
	Sword(Player* player, Texture* texture, string name, string desc, double price, int ad, double meleeRate, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), ad_(ad), meleeRate_(meleeRate) {};
	~Sword() {};

	//Equipar dicho equipamiento
	void equip();

	//Desequiparlo y perder sus stats
	void remove();
};

