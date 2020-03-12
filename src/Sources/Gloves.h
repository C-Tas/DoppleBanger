#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	Player* player_ = nullptr;
	int crit_ = 0;
	int armor_ = 0;

public:
	Gloves(Player* player, Texture* texture, string name, string desc, double price, int crit, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), crit_(crit), armor_(armor) {};
	~Gloves() {};

	//Equipar dicho equipamiento
	void equip();

	//Desequiparlo y perder sus stats
	void remove();
};