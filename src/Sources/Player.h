#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"
#include "Enemy.h"
#include <array>

class Skill;
class ClonSkill;
class WhirlwindSkill;
class ClonSelfDestructSkill;

class Player : public Actor
{
private:
	bool attacking = false;
	Enemy* objective_ = nullptr;
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;
	
	///<summary>Número máximo de skills equipables</summary>
	static const int MAX_SKILLS = 3;
	array<Skill*, MAX_SKILLS> skillsEquiped_ = {nullptr, nullptr, nullptr};

//<summary>Variables relativas a las habilidades</summary>
#pragma region abilities
	int liberation_ = 2;
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region cooldowns
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
#pragma endregion

	//Prueba del torbellino
	WhirlwindSkill* skillWhirl_;
	ClonSkill* skillClon_;
	ClonSelfDestructSkill* skillExplosion_;

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
		eventHandler_ = HandleEvents::instance();
		initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
		init();
	};
	virtual ~Player();
	virtual bool update();
	void shoot(Vector2D dir);
	virtual void onCollider() { /*Colisi�n con enemigo*/ };
	void move(Point2D target);
	void attack(Enemy* obj);
	virtual void stop() { dir_ = Vector2D(0, 0); }

	//M�todo que desequipa al jugador y equipa un nuevo objeto
	//M�todos unequip no son necesarios porque nunca va a poder estar desequipado
	void equip(Equipment* equip);

	//Crea un clon. A este método lo llama solo la skill "ClonSkill"
	void createClon();
	//Mata al clon
	void killClon() { clon_->die(); };
	//Devuelve la posición del clon
	Vector2D getClonPos() { return clon_->getPos(); };
	//Devuelve la escala del clon
	Vector2D getClonScale() { return clon_->getScale(); };

#pragma region SkillsEquipped
	Skill* getSkillEquipped(int key) { return skillsEquiped_[key]; }
	void setSkillAt(int key, Skill* skill) { if(skillsEquiped_[key]!= nullptr)delete skillsEquiped_[key]; skillsEquiped_[key] = skill; }
	array <Skill*, MAX_SKILLS>& getSkillsArray() { return skillsEquiped_; }

#pragma endregion

};