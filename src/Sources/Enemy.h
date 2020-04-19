#pragma once
#include "Actor.h"
using namespace std;
class Enemy : public Actor
{
public:
	virtual bool update() { return false; };
	virtual void onCollider() {};
	//<summary>Metodo que mata a este enemigo</summary>
	virtual void die();
	virtual void lostAgro() {};
protected:
	//Rango de visión de la entidad
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

	//Vector que representa el alto y ancho de la caja de colisiones
	Point2D boxCollision_;
	//Último ataque
	Uint32 lastHit = 0;
	//Último frame de animación
	Uint32 lastFrame_ = 0;

	//Inicializa al Enemy
	virtual void initObject() {};
	//Inicializa las animaciones
	virtual void initAnims() {};
	//Ataque
	virtual void attack() {};
	//Actualiza la actual animación
	virtual void updateAnim();
	//Devuelve true si el target está dentro del rango de ataque
	virtual bool onRange(bool melee);
	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy(bool melee);
	//Determina si el jugador está dentro del rango de ataque del monkeyCoco
	virtual Vector2D isPlayerInRange(int range);
	//Determina si el clon está dentro del rango de ataque del monkeyCoco
	virtual Vector2D isClonInRange(int range);
};