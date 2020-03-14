#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	equipType type_;
	Player* player_ = nullptr;
	int speed_ = 0;
	int armor_ = 0;

public:
	Boots(Player* player, Texture* texture, string name, string desc, double price, int speed, int armor, equipType type) :
		Equipment(texture, name, desc, price, type), player_(player), speed_(speed), armor_(armor), type_(type) {};
	virtual ~Boots() {};

	//Equipar dicho equipamiento
	virtual void equip();

	//Desequiparlo y perder sus stats
	virtual void remove();

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "speed: " << speed_ << "\n";
		std::cout << "armor: " << armor_ << "\n";
	};
};

