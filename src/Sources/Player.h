#pragma once

#include "Actor.h"
#include "HandleEvents.h"
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
//<summary>Estadisticas base del jugador</summary>
#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 0;
	const int AD = 0;
	const int AP = 0;
	const int CRIT = 0;
	const int MOVE_SPEED = 100;
	const double MELEE_RATE = 0;
	const double DIST_RATE = 0;
#pragma endregion

private:
	
	playerEquipment equip_;
	HandleEvents* eventHandler_ = nullptr;
	void init();

public:
	//Constructora de player
	Player(Application* app, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) { init(); };
	~Player();
	virtual bool update();
	virtual void onCollider() {};

	//M�todo que desequipa al jugador y equipa un nuevo objeto
	//M�todos unequip no son necesarios porque nunca va a poder estar desequipado
	//void equip(Equipment* equip);

	//metodos para guardar el puntero al equipamiento
	void equip(Armor* armor) {  equip_.armor_ = armor;  };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves;  };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword;  };
	void equip(Gun* gun) { equip_.gun_ = gun; };

	//metodos para usar las pociones
	void usePotion(int value, potionType type);
};