#pragma once

#include "Item.h"
#include "Stats.h"
#include <iostream>



class InventoryButton;

const enum equipType { Armor_, Boots_, Gloves_, Sword_, Saber_, Pistol_, Shotgun_ };

class Equipment : public Item
{
protected:
	equipType type_;
	Stats modifiers_;
	
public:
	//Crea un item equipable del tipo dado
	Equipment(Texture* texture, string name, string desc, double price, equipType type) : 
		Item(texture, name, desc, price, 1), type_(type) { };
	virtual ~Equipment() {}; //Destructora generica

	

	virtual void equip(Player* player) = 0;
	virtual void remove(Player* player) = 0;
	virtual void writeStats() = 0;

};