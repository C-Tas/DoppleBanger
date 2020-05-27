#pragma once
#include "Bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, double damage, double lifeSpan, double bulletSpeed) :
		Bullet(app, texture, pos, dir, damage, lifeSpan, bulletSpeed) {
		scale_ = Vector2D(W_H_BULLET, W_H_BULLET);
	};
	~PlayerBullet() {};
	virtual bool update();

	//Para saber si est� activada la perforaci�n
	const bool getPerforate() { return perforate_; };
	//Para saber si est� activado el rebote
	const bool getRicochet() { return ricochet_; };
	//Devuelve el n�mero de rebotes
	const int getNumRico() { return NUM_RICO; };
	//Activa perforaci�n
	void setPerforate(bool perforate) { perforate_ = perforate; };
	//Activa el rebote
	void setRicochet(bool ricochet) { ricochet_ = ricochet; };
	//Busca al siguiente enemigo en el que rebotar
	void searchEnemy(list<Enemy*> enemies, Enemy* currEnemy);

private:
	bool perforate_ = false;								//Para saber si perfora
	bool ricochet_ = false;									//Para saber si rebota
	const int NUM_RICO = 4;									//N�mero de rebotes m�xmo
	int currRico = 0;										//N�mero de rebotes
	const float RADIUS = 500;								//Radio de la circunferencia de b�squeda de la bala
	const double W_H_BULLET = app_->getWindowHeight() / 40;	//Tama�o de la bala
	virtual void initObject() {};
};

