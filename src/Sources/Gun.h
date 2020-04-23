#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	equipType type_;
	int ad_ = 0;
	double distRate_ = 0;

public:
	Gun(Texture* texture, string name, string desc, double price, int ad, double distRate, equipType type) :
		Equipment(texture, name, desc, price, type), ad_(ad), distRate_(distRate), type_(type) {};
	virtual ~Gun() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
#pragma region Getters
	int getAd() { return ad_; };
	double distRate() { return distRate_; };
#pragma endregion
	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "ad: " << ad_ << "\n";
		std::cout << "distRate: " << distRate_ << "\n";
	};
};

