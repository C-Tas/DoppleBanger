#pragma once
#include "Item.h"

class usable: public Item
{
private:
#pragma region Constantes
	const double HEALTH_VALUE = 5;	//Porcentaje de la vida que se va a restaurar
	const double MANA_VALUE = 10;	//Porcentaje del maná que se va a restaurar
	const double SPEED_VALUE = 100;	//Cantidad de velocidad que se sumara
	const double DAMAGE_VALUE = 20;	//Porcentaje de daño que se sumara
	const double ARMOR_VALUE = 10;	//Cantidad de daño que se sumara
	const double CRIT_VALUE = 10;	//Cantidad de critico que se sumara

	const double SPEED_TIME = 15;	//Tiempo en segundos que durá la poción
	const double DAMAGE_TIME = 3.5;	//Tiempo en segundos que durá la poción
	const double ARMOR_TIME = 4;	//Tiempo en segundos que durá la poción
	const double CRIT_TIME = 4;		//Tiempo en segundos que durá la poción

	const double HEALTH_PRICE = 10;	//Precio de la pocion
	const double MANA_PRICE = 10;		//Precio de la pocion
	const double SPEED_PRICE = 10;		//Precio de la pocion
	const double DAMAGE_PRICE = 10;	//Precio de la pocion
	const double ARMOR_PRICE = 10;		//Precio de la pocion
	const double CRIT_PRICE = 10;		//Precio de la pocion
#pragma endregion

	potionType type_;
	double value_ = 0;		//Guardara el valor a sumar
	double time_ = 0;			//Tiempo en milisegundos que dura el efecto de la pocion
	bool used_ = false;		//Para saber si se ha usado
	double useTime_ = 0;	//Momento en el que se usa

	virtual void initObject();
public:
	usable(Application* app, potionType type) : Item(app, ObjectType::Usable), type_(type) { initObject(); };

	virtual ~usable() {}; //Destructora 
	virtual bool update();
	virtual void equip(Player* player) {};
	virtual void remove(Player* player) {};
	//Metodo que se llama para usar la pocion
	void use();
	void desactivePotion();
	const double getTime() { return time_; };
	const double getValue() { return value_; };
	const potionType getType() { return type_; };
	const bool isUsed() { return used_; };

};

