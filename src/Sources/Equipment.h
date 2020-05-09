#pragma once
#include "Item.h"
#include "Stats.h"

class Equipment : public Item
{
protected:
	equipType type_;
	//Stats modifiers_ = Stats();
	virtual void initObject() = 0;
public:
	//Crea un item equipable del tipo dado
	Equipment(Application* app, equipType type) : Item(app, ObjectType::Equipment), type_(type) {};
	virtual ~Equipment() {}; //Destructora generica

	virtual bool update() { return false; };

	
#pragma region Getters
	virtual double getHealth() { }; // Devuelve el valor de Health
	virtual double getArmor() { }; // Devuelve el valor de Armor
	virtual double getMeleeDmg() {}; // Devuelve el valor de AD
	virtual double getDistDmg() { }; // Devuelve el valor de DistDamage
	virtual double getCrit() { }; // Devuelve el valor de Crit
	virtual double getSpeed() {  }; // Devuelve el valor de Speed
	virtual double getDistRate() {  }; // Devuelve el valor de DistRate
	virtual double getMeleeRate() {  }; // Devuelve el valor de MeleeRate
	virtual double getDistRange() {  }//devuelve el rango del arma a distancia
	virtual inline equipType getEquipType()const { return type_; };
#pragma endregion
	virtual void equip(Player* player) = 0;
	virtual void remove(Player* player) = 0;
};