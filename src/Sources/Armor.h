#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
private:
	virtual void initObject() {};
	double health_;
	double armor_;

public:
	Armor(Application* app, double price, double health, double armor, equipType type) : Equipment(app, type) {
		price_ = price;
		health_ = health;
		armor_ = armor;
	};
	virtual ~Armor() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);
	double getHealth() { return health_; }; // Devuelve el valor de Health
	double getArmor() { return armor_; }; // Devuelve el valor de Armor
	virtual void getDescription(TextBox* tex);
};