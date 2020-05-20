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
	SELFDESTRUCT,
	SWIMMING,
	VANISH
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
	void setHealth(double stat) { currStats_.health_ = stat; };
	void setMana(double stat) { currStats_.mana_ = stat; };
	void setManaReg(double stat) { currStats_.manaReg_ = stat; };
	void setArmor(double stat) { currStats_.armor_ = stat; };
	void setMeleeDmg(double stat) { currStats_.meleeDmg_ = stat; };
	void setDistDmg(double stat) { currStats_.distDmg_ = stat; };
	void setCrit(double stat) { currStats_.crit_ = stat; };
	void setMeleeRange(double stat) { currStats_.meleeRange_ = stat; };
	void setDistRange(double stat) { currStats_.distRange_ = stat; };
	void setMoveSpeed(double stat) { currStats_.moveSpeed_ = stat; };
	void setMeleeRate(double stat) { currStats_.meleeRate_ = stat; };
	void setDistRate(double stat) { currStats_.distRate_ = stat; };
	void setEnemy(GameObject* newEnemy) { currEnemy_ = newEnemy; }
#pragma endregion

#pragma region getters
	double getHealth() { return currStats_.health_; };
	double getMana() { return currStats_.mana_; };
	double getManaReg() { return currStats_.manaReg_; };
	double getArmor() { return currStats_.armor_; };
	double getMeleeDmg() { return currStats_.meleeDmg_; };
	double getDistDmg() { return currStats_.distDmg_; };
	double getCrit() { return currStats_.crit_; };
	double getMeleeRange() { return currStats_.meleeRange_; };
	double getDistRange() { return currStats_.distRange_; };
	double getMoveSpeed() { return currStats_.moveSpeed_; };
	double getMeleeRate() { return currStats_.meleeRate_; };
	double getDistRate() { return currStats_.distRate_; };
	const DIR getDir() { return currDir_; }
#pragma endregion

#pragma region addition
	void addHealth(double stat) { currStats_.health_ += stat; };
	void addMana(double stat) { currStats_.mana_ += stat; };
	void addManaReg(double stat) { currStats_.manaReg_ += stat; };
	void addArmor(double stat) { currStats_.armor_ += stat; };
	void addMeleeDmg(double stat) { currStats_.meleeDmg_ += stat; };
	void addDistDmg(double stat) { currStats_.distDmg_ += stat; };
	void addCrit(double stat) { currStats_.crit_ += stat; };
	void addMeleeRange(double stat) { currStats_.meleeRange_ += stat; };
	void addDistRange(double stat) { currStats_.distRange_ += stat; };
	void addMoveSpeed(int stat) { currStats_.moveSpeed_ += stat; };
	void addMeleeRate(double stat) { currStats_.meleeRate_ += stat; };
	void addDistRate(double stat) { currStats_.distRate_ += stat; };
#pragma endregion

#pragma region substraction
	void removeHealth(double stat) { currStats_.health_ -= stat; };
	void removeMana(double stat) { currStats_.mana_ -= stat; };
	void removeManaReg(double stat) { currStats_.manaReg_ -= stat; };
	void removeArmor(double stat) { currStats_.armor_ -= stat; };
	void removeMeleeDamage(double stat) { currStats_.meleeDmg_ -= stat; };
	void removeDistDamage(double stat) { currStats_.distDmg_ -= stat; };
	void removeCrit(double stat) { currStats_.crit_ -= stat; };
	void removeMeleeRange(double stat) { currStats_.meleeRange_ -= stat; };
	void removeDistRange(double stat) { currStats_.distRange_ -= stat; };
	void removeMoveSpeed(double stat) { currStats_.moveSpeed_ -= stat; };
	void removeMeleeRate(double stat) { currStats_.meleeRate_ -= stat; };
	void removeDistRate(double stat) { currStats_.distRate_ -= stat; };
#pragma endregion
	//Realiza una acción al detectar una colisión
	virtual void onCollider() = 0;
	//Calcula hacia dónde mira en función del objetivo
	void updateDirVisObjective(GameObject* objective);
	void updateDirVisObjective(Point2D objective);
	//Calcula hacia dónde mira en función de la posición del raton
	void updateDirVisMouse();
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
	DIR currDir_ = DIR::DOWN;
	//Puntero al audio manager
	AudioManager* am_ = nullptr;

	//Tiempo que va a estar tintado
	const double TINT_TIME = 1000;
	//Tiempo en que se tintó
	double lastTint_ = 0;
	//Gestiona el tintado
	void manageTint();
	//Gestiona los sonidos de herido
	virtual void feedBackHurtSounds() {};

	//Constructor vacío
	Actor() {};
	///<summary>Constructor de la clase Actor</summary>
	Actor(Application* app, Vector2D pos, Vector2D scale, double rot = 0) :
		Dynamic(app, pos, scale, rot) {};
	Actor(Actor& other) :Dynamic(other.app_, other.pos_, other.scale_),
		currStats_(other.currStats_), currState_(other.currState_) {};
	///<summary>Destructor de la clase Actor</summary>
	virtual ~Actor() {};

	//Inicializa al actor
	virtual void initObject() { am_ = app_->getAudioManager(); };
	virtual void initAnims() {};
	//Actualiza los Cooldowns
	virtual void updateCooldowns() = 0;
	//<summary>Inicializa todas las stats</summary>
	void initStats(double health, double mana, double manaReg, double armor, double meleeDmg, double distDmg, 
		double crit, double meleeRange, double distRange, double moveSpeed, double meleeRate, double distRate);

};
