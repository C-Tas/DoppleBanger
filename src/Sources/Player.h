#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"
#include "Enemy.h"
#include "usable.h"
#include <array>

class Skill;
class ClonSkill;
class WhirlwindSkill;
class ClonSelfDestructSkill;
class EmpoweredSkill;

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
public:
	//Constructora de player
	Player(Application* app, Vector2D pos, Vector2D scale) :
		Actor(app, pos, scale) {
		initObject();
	};
	~Player();

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
	void shout();
	const int getLiberation() { return liberation_; };
	const Stats& getStats() { return currStats_; };
	const Vector2D getPreviousPos() { return previousPos_; }
	virtual void die() { currState_ = STATE::DYING; }

	//Aumenta la cadencia de tiro del player
	void activateSwiftGunslinger() { currStats_.distRate_ -= RANGE_SPEED; };
	//Activa el ataque potenciado
	void activateEmpowered() { empoweredAct_ = true; };
	//metodos para coger la info del player
	playerEquipment& const getInfoEquip() { return equip_; }
	void usePotion(int value, potionType type);
	void desactivePotion();

	void equip(Armor* armor) { equip_.armor_ = armor; };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves; };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword; };
	void equip(Gun* gun) { equip_.gun_ = gun; };
	void equipPotion1(usable* pot) { equip_.potion1_ = pot; }
	void equipPotion2(usable* pot) { equip_.potion2_ = pot; }

	//Crea un clon. A este método lo llama solo la skill "ClonSkill"
	void createClon();
	//Mata al clon
	bool killClon() {
		if (clon_ != nullptr) {
			clon_->die();
			return true;
		}
		else return false;
	};
	//Devuelve la posición del clon
	Vector2D getClonPos() { return clon_->getPos(); };
	//Devuelve la escala del clon
	Vector2D getClonScale() { return clon_->getScale(); };

#pragma region SkillsEquipped
	///<summary>Número máximo de skills equipables</summary>
	static const int MAX_SKILLS = 3;
	Skill* getSkillEquipped(int key) { return skillsEquiped_[key]; }
	void setSkillAt(int key, Skill* skill) { if(skillsEquiped_[key]!= nullptr)delete skillsEquiped_[key]; skillsEquiped_[key] = skill; }
	array <Skill*, MAX_SKILLS>& getSkillsArray() { return skillsEquiped_; }
#pragma endregion

private:
	bool attacking_ = false;
	Actor* objective_ = nullptr;
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;
	Vector2D previousPos_;

	array<Skill*, MAX_SKILLS> skillsEquiped_ = {nullptr, nullptr, nullptr};

	//Prueba del torbellino
	WhirlwindSkill* skillWhirl_;
	ClonSkill* skillClon_;
	ClonSelfDestructSkill* skillExplosion_;
	EmpoweredSkill* skillEmpowered_;

//<summary>Variables relativas a las habilidades</summary>
#pragma region Abilities
	int liberation_ = 2;	//Nivel de la habilidad del clon
	const int RANGE_SPEED = 1000;	//Velocidad extra para el pistolero raudo (a falta de equilibrado)
	bool empoweredAct_ = false;		//Si tiene la habilidad activada
	double empoweredBonus_ = 1.5;	//Bonus porcentual del daño
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region Cooldowns
	double clonCooldown_ = 2;
	double clonTime_ = 0; //Momento del último clon
	double empoweredCooldown_ = 4;
	double empoweredTime_ = 0; //Momento del último ataque potenciado
	double meleeTime_ = 0; //Momento del último ataque
	double shotTime_ = 0; //Momento del �ltimo disparo
#pragma endregion

//<summary>Estadisticas iniciales del jugador</summary>
#pragma region Stats
	const double HEALTH = 1000;		//Vida
	const double MANA = 100;		//Mana
	const double MANA_REG = 1;		//Regeneración de maná por segundo
	const double ARMOR = 10;		//Armadura
	const double AD = 40;			//Daño a melee
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

	playerEquipment equip_;
	int PotionTime1 = 0;//Variable auxiliar para comprobar la duracion de la pocion1
	int PotionTime2 = 0; //Variable auxiliar para comprobar la duracion de la pocion 2
	void initObject();
};