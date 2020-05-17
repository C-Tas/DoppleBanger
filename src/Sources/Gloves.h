#pragma once

#include "Equipment.h"

class Gloves : public Equipment
{
private:
	virtual void initObject() {};
	double crit_;
	double armor_;
public:
	Gloves(Application* app, double price, double crit, double armor, equipType type) : Equipment(app, type) {
		price_ = price;
		crit_ = crit;
		armor_ = armor;
	};
	virtual ~Gloves() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void getDescription(TextBox* tex);
};