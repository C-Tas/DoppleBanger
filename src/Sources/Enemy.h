#pragma once
#include "Actor.h"
using namespace std;
class Enemy : public Actor
{
public:
	virtual void onCollider() {};
	//<summary>Metodo que mata a este enemigo</summary>
	virtual void die() {}
	virtual void lostAgro() {};
protected:
	double rangeVision_ = 0;
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores serán los puestos, si se le pasan valores los editara</summary>
	Enemy(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 })
		:Actor(app, pos, scale) {};
	//<summary>Constructor por copia</summary>
	Enemy(Enemy& other) :Actor(other.app_, other.pos_, other.scale_) {};
	//<summary>Constructor por movimiento<summary>
	Enemy(Enemy&& other)noexcept :Actor(other.app_, other.pos_, other.scale_) {};
	//<summary>Destructor</summary>
	virtual ~Enemy() {};

	//Inicializa al Enemy
	virtual void initObject() {};
	//Inicializa las animaciones
	virtual void initAnim() {};
	virtual bool update() { return false; };

};