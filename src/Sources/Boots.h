#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	equipType type_;
	int speed_ = 0;
	int armor_ = 0;

public:
	Boots(Texture* texture, string name, string desc, double price, int speed, int armor) :
		Equipment(texture, name, desc, price, Boots_), speed_(speed), armor_(armor), type_(Boots_) {};
	virtual ~Boots() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

#pragma region Getters
	int getSpeed() { return speed_; };
	int getArmor() { return armor_; };
#pragma endregion
	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "speed: " << speed_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};

