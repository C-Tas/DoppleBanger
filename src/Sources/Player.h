#pragma once

#include "Actor.h"
#include "HandleEvents.h"

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
	//Equipamiento del jugador
	Armor* armor_ = nullptr;
	Gloves* gloves_ = nullptr;
	Boots* boots_ = nullptr;
	Sword* sword_ = nullptr;
	Gun* gun_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;

	void init();

public:
	//Constructora de player
	Player(Application* app, Texture* texture, Vector2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Actor(app, texture, pos, scale, collisionArea) { init(); };
	~Player();
	virtual bool update();
	virtual void onCollider() {};
	virtual void stop() { dir_ = Vector2D(0, 0); }

	//M�todo que desequipa al jugador y equipa un nuevo objeto
	//M�todos unequip no son necesarios porque nunca va a poder estar desequipado
	void equip(Equipment* equip);

	/*void equip(Armor* armor) { armor_->remove(this); armor_ = armor; armor_->equip(this); };
	void equip(Gloves* gloves) { gloves_->remove(this); gloves_ = gloves; gloves_->equip(this); };
	void equip(Boots* boots) { boots_->remove(this); boots_ = boots; boots_->equip(this); };
	void equip(Sword* sword) { sword_->remove(this); sword_ = sword; sword_->equip(this); };
	void equip(Gun* gun) { gun_->remove(this); gun_ = gun; gun_->equip(this); };*/
};