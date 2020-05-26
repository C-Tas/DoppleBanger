#pragma once
#include "Equipment.h"

class Sword : public Equipment
{
private:
	virtual void initObject() {};
	double meleeDmg_;
	double meleeRate_;

public:
	Sword(Application* app, double price, double meleeDamage, double meleeRate, equipType type) : Equipment(app, type) {
		price_ = price;
		meleeDmg_ = meleeDamage;
		meleeRate_ = meleeRate;
	};
	virtual ~Sword() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void getDescription(TextBox* tex);

	virtual double getMeleeRate() { return meleeRate_; }
	virtual double getMeleeDmg() { return meleeDmg_; };


};

