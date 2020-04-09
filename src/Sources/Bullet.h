#pragma once

#include "Dynamic.h"
#include "GameState.h"
#include <list>
class Enemy;

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }) :
		Dynamic(app, pos, scale), damage_(damage), lifeSpan_(lifeSpan), speed_(speed) {
		texture_ = texture;
		collisionArea_ = { (int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY() };
		init(pos, dir);
	};
	~Bullet() {};

	void init(Vector2D pos, Vector2D dir);
	bool update();
	void onCollider() {
		if (!deleting) {
			deleting = true;
			app_->getCurrState()->removeRenderUpdateLists(this);
		}; 
	}
	const int getDamage() { return damage_; }

	#pragma region PlayerAbilities
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
	#pragma endregion

private:
	double lifeSpan_ = 0; //Tiempo máximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	int damage_ = 0;
	bool enemyBullet_ = false;
	bool deleting = false;

	#pragma region PlayerAbilities
	bool perforate_ = false;	//Para saber si perfora
	bool ricochet_ = false;		//Para saber si rebota
	const int NUM_RICO = 100;		//Número de rebotes máxmo
	int currRico = 0;			//Número de rebotes
	const float RADIUS = 1000;  // Radio de la circunferencia de búsqueda de la bala
	#pragma endregion

	virtual void initObject() {};
};