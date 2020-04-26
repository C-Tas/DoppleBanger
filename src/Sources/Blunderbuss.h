#pragma once
#include "PlayerBullet.h"
#include "CollisionCtrl.h"
#include "GameObject.h"

class Blunderbuss: public GameObject
{
public:
	//Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage)
	Blunderbuss(Application* app, Texture* tex, Vector2D pos, Vector2D dir, int damage, double lifeSpan, double bulletSpeed);

	//Activa a todas las balas la skill de perforar
	void activatePerforate();

	//Activa a todas las balas la skill de ricochet
	void activateRicochet();

	//Limpia el vector de balas
	void cleanBullets() { bullets_.clear(); }

	//Devuelve el numero de balas que quedan 
	const int getCurrBullets();
	
	~Blunderbuss() {
		cleanBullets();
	}

	virtual bool update() { return false; };
	virtual void initObject() {};

private:
	Application* app_ = nullptr;
	CollisionCtrl* collisionCtrol = nullptr;
	//vector con todas las balas
	vector<PlayerBullet*> bullets_;
	const int NUM_BULLETS = 5;
	const double MIN_DISTANCE = 50;
	const double START_DEVIATION_X = 50;
	const double START_DEVIATION_Y = 50;
	const double DEVIATION_X = 10;
	const double DEVIATION_Y = 10;
};

