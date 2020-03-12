#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	Player* player_ = nullptr;
	int health_ = 0;
	int armor_ = 0;

public:
	Armor(Player* player, Texture* texture, string name, string desc, double price, int health, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), health_(health), armor_(armor) {};
	~Armor() {};

	//Equipar dicho equipamiento
	void equip();

	//Desequiparlo y perder sus stats
	void remove();
};