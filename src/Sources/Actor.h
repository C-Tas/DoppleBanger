#pragma once

#include "Dynamic.h"
#include "Stats.h"

//Enum que repesenta los diferentes estados que puede tener un personaje
enum class STATE
{
	ATTACKING,
	IDLE,
	DIYING,
};


class Actor : public Dynamic
{
protected:
	//Clase que representa las estadisticas dea actor
	Stats currStats_;
	//Emun que representa el actual estado del personaje
	STATE currState_ = STATE::IDLE;
	//Objetivo al que ataca
	Draw* currEnemy_ = nullptr;

	//Constructor vacío
	Actor() {};
	///<summary>Constructor de la clase Actor</summary>
	Actor(Application* app, Vector2D pos, Vector2D scale) :
		Dynamic(app, pos, scale) {};
	Actor(Actor& other) :Dynamic(other.app_, other.pos_, other.scale_),
		currStats_(other.currStats_), currState_(other.currState_) {};
	///<summary>Destructor de la clase Actor</summary>
	virtual ~Actor() {};

	//Inicializa al actor
	virtual void initObject() {};
	virtual void initAnim() {};
	//<summary>Inicializa todas las stats</summary>
	void initStats(double health, double mana, double manaReg, double armor, double ad, double ap, 
		double crit, double range, double moveSpeed, double meleeRate, double distRate);

public:
	//Método para gestionar el daño recibido 
	void reciveDmg(int damage);
	//Devuelve el estado actual del actor
	const STATE getState() { return currState_; };
	//Detiene el movimiento
	void stop() { dir_ = Vector2D(0, 0); };
	//Cambia al enemigo al que está atacando
	inline void changeAgro(Draw* newEnemy) { currEnemy_ = newEnemy; };
};