#pragma once

#include "Equipment.h"

class Gun : public Equipment
{
private:
	virtual void initObject();
	double bulletSpeed_ = 0;
	//variables para las diferentes velocidades de las balas
	const double PISTOL_BULLET_SPEED = 1000;
	const double SHOTGUN_BULLET_SPEED = 500;
	//Vida de la bala en segundos
	const double PISTOL_BULLET_RANGE = 2;
	const double SHOTGUN_BULLET_RANGE = 1;
public:
	Gun(Application* app, double price, double distDamage, double distRate, equipType type) : Equipment(app, type) {
		price_ = price;
		modifiers_.distDmg_ = distDamage;
		modifiers_.distRate_ = distRate;
		initObject();
	};
	virtual ~Gun() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	//Devuelve la velocidad de la bala
	double getBulletSpeed() { return bulletSpeed_; };
};

