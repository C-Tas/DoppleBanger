#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	equipType type_;
	int crit_ = 0;
	int armor_ = 0;

public:
	Gloves(Texture* texture, string name, string desc, double price, int crit, int armor) :
		Equipment(texture, name, desc, price, Gloves_), crit_(crit), armor_(armor), type_(Gloves_) {};
	virtual ~Gloves() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
#pragma region Getters
	int getCrit() { return crit_; };
	int getArmor() { return armor_; };
#pragma endregion
	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "crit: " << crit_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};