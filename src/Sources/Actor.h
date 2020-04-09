#pragma once
#include "Dynamic.h"
#include "Stats.h"

//Enum que repesenta los diferentes estados que puede tener un personaje
enum class STATE
{
	ATTACKING,
	IDLE,
	DYING,
	FOLLOWING,
	PATROLLING,
};

//Enumerado para representar la dirección a la que mira una entidad
enum class DIR {
	UP,
	RIGHT,
	DOWN,
	LEFT
};


class Actor : public Dynamic
{
protected:
	//Clase que representa las estadisticas dea actor
	Stats currStats_;
	//Emun que representa el actual estado del personaje
	STATE currState_ = STATE::IDLE;
	//Target objetivo para atacar. Enemy también puede ser el player.
	//Es el enemigo visto desde la entidad
	GameObject* currEnemy_ = nullptr;
	//Actual dirección a la que mira la entidad
	DIR currDir_ = DIR::RIGHT;
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
	void initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, 
		double crit, double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate);

public:
	//Realiza una acción al detectar una colisión
	virtual void onCollider() = 0;
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target) {};
	//Método para gestionar el daño recibido 
	virtual void receiveDamage(int damage);
	//Método para matar
	virtual void die() { currState_ = STATE::DYING; };
	//Devuelve el estado actual del actor
	const STATE getState() { return currState_; };
	//Detiene el movimiento
	void stop() { dir_ = Vector2D(0, 0); };
	//Cambia al enemigo al que está atacando
	inline void changeAgro(GameObject* newEnemy) { currEnemy_ = newEnemy; };
};