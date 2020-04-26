#pragma once
#include "Item.h"

class usable: public Item
{
private:
#pragma region Constantes
	const double HEALTH_VALUE = 5;	//Porcentaje de la vida que se va a restaurar
	const double MANA_VALUE = 10;	//Porcentaje del maná que se va a restaurar
	const double SPEED_VALUE = 20;	//Cantidad de velocidad que se sumara
	const double DAMAGE_VALUE = 20;	//Porcentaje de daño que se sumara
	const double ARMOR_VALUE = 10;	//Cantidad de daño que se sumara
	const double CRIT_VALUE = 10;	//Cantidad de critico que se sumara

	const int SPEED_TIME = 3000;	//Tiempo en ilisegundos que durá la poción
	const int DAMAGE_TIME = 3500;	//Tiempo en ilisegundos que durá la poción
	const int ARMOR_TIME = 4000;	//Tiempo en ilisegundos que durá la poción
	const int CRIT_TIME = 4000;		//Tiempo en ilisegundos que durá la poción

	const int HEALTH_PRICE = 10;	//Precio de la pocion
	const int MANA_PRICE = 10;		//Precio de la pocion
	const int SPEED_PRICE = 10;		//Precio de la pocion
	const int DAMAGE_PRICE = 10;	//Precio de la pocion
	const int ARMOR_PRICE = 10;		//Precio de la pocion
	const int CRIT_PRICE = 10;		//Precio de la pocion
#pragma endregion

	potionType type_;
	int value_ = 0;			//Guardara el valor a sumar
	int time_ = -1;			//Tiempo en milisegundos que dura el efecto de la pocion
	bool used_ = false;		//Para saber si se ha usado
	double useTime_ = 0;	//Momento en el que se usa

	virtual void initObject();
public:
	usable(potionType type) : Item(ObjectType::Usable), type_(type) { initObject(); };

	virtual ~usable() {}; //Destructora 
	virtual bool update();
	virtual void equip(Player* player) {};
	virtual void remove(Player* player) {};
	//Metodo que se llama para usar la pocion
	void use();

	int getDuration() { return time_; }
	int getValue() { return value_; }
	potionType getType() { return type_; }
	bool isUsed() { return used_; }

};

