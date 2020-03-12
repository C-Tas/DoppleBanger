#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	Player* player_ = nullptr;
	int speed_ = 0;
	int armor_ = 0;

public:
	Boots(Player* player, Texture* texture, string name, string desc, double price, int speed, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), speed_(speed), armor_(armor) {};
	~Boots() {};

	//Equipar dicho equipamiento
	void equip();

	//Desequiparlo y perder sus stats
	void remove();
};

