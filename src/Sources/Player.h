#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"
#include "Enemy.h"

class Player : public Actor
{
private:
	bool attacking = false;

	Enemy* objective_ = nullptr;
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;

//<summary>Variables relativas a las habilidades</summary>
#pragma region abilities
	int liberation_ = 2;
	bool explotion_ = false;
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region cooldowns
	double clonCooldown_ = 5;
	double clonTime_ = 0; //Momento del último clon
	double meleeTime_ = 0; //Momento del último ataque
	double shotTime_ = 0; //Momento del �ltimo disparo
#pragma endregion

//<summary>Estadisticas del jugador</summary>
#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 10;
	const int AD = 20;
	const int AP = 0;
	const int CRIT = 0;
	const int RANGE = 50;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 2;

	const double CLON_SPAWN_RANGE = 700;
#pragma endregion

private:
	//Equipamiento del jugador
	Armor* armor_ = nullptr;
	Gloves* gloves_ = nullptr;
	Boots* boots_ = nullptr;
	Sword* sword_ = nullptr;
	Gun* gun_ = nullptr;

	void init();

public:
//Constructora de player
	Player(Application* app, vector<Texture*> texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) {
		init();
	};
	~Player();
	virtual bool update();
	void shoot(Vector2D dir);
	virtual void onCollider() { /*Colisi�n con enemigo*/ };
	void move(Point2D target);
	void attack(Enemy* obj);
	virtual void stop() { dir_ = Vector2D(0, 0); }
	//M�todo que desequipa al jugador y equipa un nuevo objeto
	//M�todos unequip no son necesarios porque nunca va a poder estar desequipado
	void equip(Equipment* equip);
};