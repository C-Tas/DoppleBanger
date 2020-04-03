#pragma once
#include "Item.h"
class Player;

const enum potionType { live_, mana_, velocity_, damage_, defense_, critic_ };

class usable: public Item
{
private:
	potionType type_;
	int value_;//guardara el valor a sumar

	int time_;//tiempo en segundos que dura el efecto de la pocion 
			// poner a -1 si el efecto es permanente;
	bool used_ = false;

public:
	usable(Texture* texture, string name, string desc, double price, potionType type, int value, int time) :
		Item(texture, name, desc, price, 1), type_(type) , value_(value), time_(time){ };

	virtual ~usable() {}; //Destructora 

	//Metodo que se llama para usar la pocion
	void use(Player* player);
	virtual void equip(Player* player) {};
	virtual void remove(Player* player) {};

	int getDuration() { return time_; }
	int getValue() { return value_; }
	potionType getType() { return type_; }
	bool isUsed() { return used_; }



};

