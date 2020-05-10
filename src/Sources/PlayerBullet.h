#pragma once
#include "Bullet.h"
class PlayerBullet : public Bullet
{
public:
	PlayerBullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, double damage, double lifeSpan, double bulletSpeed) :
		Bullet(app, texture, pos, dir, damage){
		lifeSpan_ = lifeSpan;
		speed_ = bulletSpeed;
		scale_ = Vector2D(W_H_BULLET, W_H_BULLET);
	};
	~PlayerBullet() {};
	virtual bool update();

	//Para saber si está activada la perforación
	const bool getPerforate() { return perforate_; };
	//Para saber si está activado el rebote
	const bool getRicochet() { return ricochet_; };
	//Devuelve el número de rebotes
	const int getNumRico() { return NUM_RICO; };
	//Activa perforación
	void setPerforate(bool perforate) { perforate_ = perforate; };
	//Activa el rebote
	void setRicochet(bool ricochet) { ricochet_ = ricochet; };
	//Busca al siguiente enemigo en el que rebotar
	void searchEnemy(list<Enemy*> enemies, Enemy* currEnemy);

private:
	bool perforate_ = false;								//Para saber si perfora
	bool ricochet_ = false;									//Para saber si rebota
	const int NUM_RICO = 100;								//Número de rebotes máxmo
	int currRico = 0;										//Número de rebotes
	const float RADIUS = 1000;								// Radio de la circunferencia de búsqueda de la bala
	const uint W_H_BULLET = app_->getWindowHeight() / 40;	//Tamaño de la bala
	virtual void initObject() {};
};

