#pragma once
#include "Item.h"
//#include "Player.h"
class Player;

const enum potionType { live_, mana_, velocity_, damage_, defense_, critic_ };

class usable: public Item
{
private:
	potionType type_;
	int value_;//guardara el valor a sumar
public:
	usable(Texture* texture, string name, string desc, double price, potionType type, int value) :
		Item(texture, name, desc, price, 1), type_(type) , value_(value){ };

	virtual ~usable() {}; //Destructora 

	//Metodo que se llama para usar la pocion
	void use(Player* player);
	virtual void equip(Player* player) {};
	virtual void remove(Player* player) {};



};

