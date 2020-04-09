#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"

class Skill;

class Player : public Actor
{
public:
	//Constructora de player
	Player(Application* app, Vector2D pos, Vector2D scale) :
		Actor(app, pos, scale) {
		initObject();
	};
	~Player() {
		delete w_; w_ = nullptr;
		delete e_; e_ = nullptr;
	};

	///<summary>Constructor por copia</summary>
	Player(const Player& other) : Actor(other.app_, other.pos_, other.scale_) {
		eventHandler_ = HandleEvents::instance();
	};

	virtual bool update();
	void shoot(Vector2D dir);
	virtual void onCollider();
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
	void attack(Enemy* obj);
	const int getLiberation() { return liberation_; };
	const bool getExplotion() { return explotion_; };
	const Stats& getStats() { return currStats_; };
	//Activa la perforación
	void setPerforate(bool perforate) { perforate_ = perforate; };
	//Activa el rebote y el momento en el que se usa
	void setRicochet(bool ricochet) { ricochet_ = ricochet; lastTimeRico_ = SDL_GetTicks(); };
	virtual void die() { currState_ = STATE::DYING; }
private:
	uint lastMeleeHit_ = 0;
	bool attacking_ = false;
	Actor* objective_ = nullptr;
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;

//<summary>Variables relativas a las habilidades</summary>
#pragma region Abilities
	int liberation_ = 2;	//Nivel de la habilidad del clon
	bool explotion_ = false;	//Si tiene la habilidad activada
	bool perforate_ = false;	//Para saber si el siguiente disparo perfora
	bool ricochet_ = false;		//Para saber si los disparos van a rebotar
	const int TIME_RICO = 4;	//En segundos
	int lastTimeRico_ = 0;		//Momento en el que se usa rebote
	Skill* w_ = nullptr;		//Habilidad asignada a la w
	Skill* e_ = nullptr;		//Habilidad asignada a la e
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region Cooldowns
	double clonCooldown_ = 2;
	double clonTime_ = 0; //Momento del último clon
	double meleeTime_ = 0; //Momento del último ataque
	double shotTime_ = 0; //Momento del �ltimo disparo
#pragma endregion

//<summary>Estadisticas iniciales del jugador</summary>
#pragma region Stats
	const double HEALTH = 1000;		//Vida
	const double MANA = 100;		//Mana
	const double MANA_REG = 1;		//Regeneración de maná por segundo
	const double ARMOR = 10;		//Armadura
	const double AD = 1000;			//Daño a melee
	const double AP = 1000;			//Daño a distancia y de las habilidades
	const double CRIT = 0;			//Crítico
	const double MELEE_RANGE = 20;	//Rango del ataque a melee
	const double DIST_RANGE = 0;	//Rango del ataque a distancia
	const double MOVE_SPEED = 300;	//Velocidad de movimiento
	const double MELEE_RATE = 1;	//Velocidad del ataque a melee en segundos
	const double DIST_RATE = 1;		//Velocidad del ataque a distancia en segundos

	const double CLON_SPAWN_RANGE = 200;
#pragma endregion

//<summary>Constantes iniciales del jugador</summary>
#pragma region Constantes
	//Balas
	const uint W_H_BULLET = app_->getWindowHeight() / 40;	//Tamaño de la bala
	const double BULLET_VEL = 1000;							//Velocidad de la bala
	const double BULLET_LIFE = 1;							//Vida de la bala, en segundo
#pragma endregion
	virtual void initObject();


};