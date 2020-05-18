#pragma once

#include "Equipment.h"

class Boots : public Equipment
{
private:
	virtual void initObject() {};
	double moveSpeed_;
	double armor_;

public:
	Boots(Application* app, double price, double speed, double armor, equipType type) : Equipment(app, type) {
		price_ = price;
		moveSpeed_ = speed;
		armor_ = armor;
	};
	virtual ~Boots() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void getDescription(TextBox* tex);
};

