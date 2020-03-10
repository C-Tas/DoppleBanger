#pragma once

#include "Item.h"
#include "Stats.h"

const enum equipType { Armor, Boots, Gloves, Sword, Gun };

class Equipment : public Item
{
private:
	equipType type_;
	Stats modifiers_;

public:
	//Crea un item equipable del tipo dado
	Equipment(equipType type) : Item(), type_(type) { modifiers_ = Stats(); };
	void writeStats();
	~Equipment() {}; //Destructora generica

#pragma region Setters
	void setHealth(int health) { modifiers_.health_ = health; };// Asigna el valor de Health
	void setArmor(int armor) { modifiers_.armor_ = armor; };// Asigna el valor de Armor
	void setAd(int ad) { modifiers_.ad_ = ad; }; // Asigna el valor de AD
	void setCrit(int crit) { modifiers_.crit_ = crit; }; // Asigna el valor de Crit
	void setSpeed(int speed) { modifiers_.moveSpeed_ = speed; }; // Asigna el valor de Speed
	void setDistRate(double distRate) { modifiers_.distRate_ = distRate; }; // Asigna el valor de DistRate
	void setMeleeRate(double meleeRate) { modifiers_.meleeRate_ = meleeRate; }; // Asigna el valor de MeleeRate
#pragma endregion

#pragma region Getters
	int getHealth() { return modifiers_.health_; }; // Devuelve el valor de Health
	int getArmor() { return modifiers_.armor_; }; // Devuelve el valor de Armor
	int getAd() { return modifiers_.ad_; }; // Devuelve el valor de AD
	int getCrit() { return modifiers_.crit_; }; // Devuelve el valor de Crit
	int getSpeed() { return modifiers_.moveSpeed_; }; // Devuelve el valor de Speed
	double getDistRate() { return modifiers_.distRate_; }; // Devuelve el valor de DistRate
	double getMeleeRate() { return modifiers_.meleeRate_; }; // Devuelve el valor de MeleeRate
#pragma endregion

};