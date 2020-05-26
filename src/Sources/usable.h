#pragma once
#include "Item.h"

class usable: public Item
{
private:
#pragma region Constantes
	const double HEALTH_VALUE = 10;	//Porcentaje de la vida que se va a restaurar
	const double MANA_VALUE = 10;	//Porcentaje del man� que se va a restaurar
	const double SPEED_VALUE = 100;	//Cantidad de velocidad que se sumara
	const double DAMAGE_VALUE = 30;	//Porcentaje de da�o que se sumara
	const double ARMOR_VALUE = 15;	//Cantidad de da�o que se sumara
	const double CRIT_VALUE = 10;	//Cantidad de critico que se sumara

	const double SPEED_TIME = 15000;	//Tiempo en segundos que dur� la poci�n
	const double DAMAGE_TIME = 3500;	//Tiempo en segundos que dur� la poci�n
	const double ARMOR_TIME = 4000;		//Tiempo en segundos que dur� la poci�n
	const double CRIT_TIME = 4000;		//Tiempo en segundos que dur� la poci�n

	const double HEALTH_PRICE = 25;		//Precio de la pocion
	const double MANA_PRICE = 50;		//Precio de la pocion
	const double SPEED_PRICE = 75;		//Precio de la pocion
	const double DAMAGE_PRICE = 150;		//Precio de la pocion
	const double ARMOR_PRICE = 100;		//Precio de la pocion
	const double CRIT_PRICE = 100;		//Precio de la pocion
#pragma endregion

	potionType type_;
	double value_ = 0;		//Guardara el valor a sumar
	double time_ = 0;		//Tiempo en milisegundos de duracion que queda del efecto de la pocion

	virtual void initObject();
public:
	usable(Application* app, potionType type) : Item(app, ObjectType::Usable), type_(type) { initObject(); };

	virtual ~usable() {}; //Destructora 
	virtual bool update() { return false; };
	virtual void equip(Player* player) {};
	virtual void remove(Player* player) {};

	const double getTime() { return time_; };
	const double getValue() { return value_; };
	void setTime(double time) { time_ = time; };
	const potionType getType() { return type_; };
	//const bool isUsed() { return used_; };
	virtual void getDescription(TextBox* tex);

};

