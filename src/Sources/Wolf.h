#pragma once
#include "Enemy.h"
class Wolf :
	public Enemy
{
public:
	Wolf(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 },
		vector<Point2D> patrol = { {0,0} }) :
		Enemy(app, pos, scale), patrol_(patrol) {
		initObject();
	};
	Wolf(Wolf& other) :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };
	Wolf(Wolf&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };

	virtual bool update();
	virtual void initObject();
	virtual void onCollider();
	virtual void move(Vector2D pos);
	virtual  ~Wolf() {};

private:
	//Puntos del mapa donde va a patrullar
	vector<Point2D> patrol_;
	//Punto que representa dentro del vector de patrulla
	int currTarget_ = 0;
	//�ltimo ataque a melee
	Uint32 lastMeleeHit_ = 0;
	//Tiempo que el lobo pasa parado cuando llega a un target
	Uint32 idleTime_ = 1000;
	//Tiempo 
	uint lastIdleTime = 0;

	//Ataque del monkeyCoco
	void attack();
	//Devuelve true si el target est� dentro del rango de ataque
	bool onRange();
	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy();
	//Cuando pierde agro del enemigo
	virtual void lostAgro();
	//Genera la posici�n a la que se mueve el pirata en funci�n de su rango 
	void selectTarget();

	virtual void animationsvar();
	virtual void initialStats();
};