#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"
#include "Enemy.h"
#include "usable.h"

struct playerEquipment
{
	//Equipamiento del jugador
	Armor* armor_ = nullptr;
	Gloves* gloves_ = nullptr;
	Boots* boots_ = nullptr;
	Sword* sword_ = nullptr;
	Gun* gun_ = nullptr;
	
	usable* potion1_ = nullptr;
	usable* potion2_ = nullptr;
	

};

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

	playerEquipment equip_;
	int PotionTime1 = 0;//Variable auxiliar para comprobar la duracion de la pocion1
	int PotionTime2 = 0; //Variable auxiliar para comprobar la duracion de la pocion 2
	void desactivePotion();
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
	

	//metodos para guardar el puntero al equipamiento
	void equip(Armor* armor) {  equip_.armor_ = armor;  };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves;  };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword;  };
	void equip(Gun* gun) { equip_.gun_ = gun; };
	void equipPotion1(usable* pot) { equip_.potion1_ = pot; }
	void equipPotion2(usable* pot) { equip_.potion2_ = pot; }

	//metodos para usar las pociones
	void usePotion(int value, potionType type);

	//metodos para coger la info del player
	playerEquipment& const getInfoEquip() { return equip_; }
};