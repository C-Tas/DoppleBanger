#pragma once
#include "Dynamic.h"
#include "Stats.h"

//Enum que repesenta los diferentes estados que puede tener un personaje
enum class STATE
{
	ATTACKING,
	SHOOTING,
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
public:
#pragma region setters
	void setHealth(int stat) { currStats_.health_ = stat; };
	void setMana(int stat) { currStats_.mana_ = stat; };
	void setManaReg(double stat) { currStats_.manaReg_ = stat; };
	void setArmor(int stat) { currStats_.armor_ = stat; };
	void setAd(int stat) { currStats_.meleeDmg_ = stat; };
	void setAp(int stat) { currStats_.distDmg_ = stat; };
	void setCrit(int stat) { currStats_.crit_ = stat; };
	void setMoveSpeed(int stat) { currStats_.moveSpeed_ = stat; };
	void setMeleeRate(double stat) { currStats_.meleeRate_ = stat; };
	void setDistRate(double stat) { currStats_.distRate_ = stat; };
#pragma endregion

#pragma region getters
	int getHealth() { return currStats_.health_; };
	int getMana() { return currStats_.mana_; };
	double getManaReg() { return currStats_.manaReg_; };
	int getArmor() { return currStats_.armor_; };
	int getAd() { return currStats_.meleeDmg_; };
	int getAp() { return currStats_.distDmg_; };
	int getCrit() { return currStats_.crit_; };
	int getMoveSpeed() { return currStats_.moveSpeed_; };
	double getMeleeRate() { return currStats_.meleeRate_; };
	double getDistRate() { return currStats_.distRate_; };
#pragma endregion

#pragma region addition
	void addHealth(int stat) { currStats_.health_ += stat; };
	void addMana(int stat) { currStats_.mana_ += stat; };
	void addManaReg(double stat) { currStats_.manaReg_ += stat; };
	void addArmor(int stat) { currStats_.armor_ += stat; };
	void addAd(int stat) { currStats_.meleeDmg_ += stat; };
	void addAp(int stat) { currStats_.distDmg_ += stat; };
	void addCrit(int stat) { currStats_.crit_ += stat; };
	void addMoveSpeed(int stat) { currStats_.moveSpeed_ += stat; };
	void addMeleeRate(double stat) { currStats_.meleeRate_ += stat; };
	void addDistRate(double stat) { currStats_.distRate_ += stat; };
#pragma endregion

#pragma region substraction
	void removeHealth(int stat) { currStats_.health_ -= stat; };
	void removeMana(int stat) { currStats_.mana_ -= stat; };
	void removeManaReg(double stat) { currStats_.manaReg_ -= stat; };
	void removeArmor(int stat) { currStats_.armor_ -= stat; };
	void removeAd(int stat) { currStats_.meleeDmg_ -= stat; };
	void removeAp(int stat) { currStats_.distDmg_ -= stat; };
	void removeCrit(int stat) { currStats_.crit_ -= stat; };
	void removeMoveSpeed(int stat) { currStats_.moveSpeed_ -= stat; };
	void removeMeleeRate(double stat) { currStats_.meleeRate_ -= stat; };
	void removeDistRate(double stat) { currStats_.distRate_ -= stat; };
#pragma endregion
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
	virtual void stop() { dir_ = Vector2D(0, 0); };
	//Cambia al enemigo al que está atacando
	inline void changeAgro(GameObject* newEnemy) { currEnemy_ = newEnemy; };

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
	virtual void initAnims() {};
	//<summary>Inicializa todas las stats</summary>
	void initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, 
		double crit, double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate);
};
