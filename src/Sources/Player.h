#pragma once
#include "Actor.h"
#include "Clon.h"
#include "usable.h"
#include "HandleEvents.h"
#include <array>
class Skill;

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
	Player(Application* app, Vector2D pos, Vector2D scale) : Actor(app, pos, scale) { initObject(); };
	~Player();
	///<summary>Constructor por copia</summary>
	Player(const Player& other) : Actor(other.app_, other.pos_, other.scale_), skills_(other.skills_) {
		eventHandler_ = HandleEvents::instance();
	};

	virtual bool update();
	virtual void onCollider();

	//Establece la direccion del movimiento
	virtual void move(Point2D target);
	//Dispara creando una bala en la posicion dir
	void shoot(Vector2D dir);
	//Ataque cuerpo a cuerpo
	void attack(Enemy* obj);
	//Grita
	void shout();
	//Crea un clon. A este método lo llama solo la skill "ClonSkill"
	void createClon();
	//Cambia de estado a muriendo
	virtual void die() { currState_ = STATE::DYING; }
	//Mata al clon
	bool killClon() {
		if (clon_ != nullptr) {
			clon_->die();
			clon_ = nullptr;
			return true;
		}
		else return false;
	};

#pragma region Getters
	const Clon* getClon() { return clon_; };
	const int getLiberation() { return liberation_; };
	const int getMoney() { return money_; };
	const double getMaxHealth() { return HEALTH; }; //Faltaria poner una variable que lleve la vida maxima sin ser cte
	const double getMaxMana() { return MANA; }; //Faltaria poner una variable que lleve el mana maximo sin ser cte

	const Vector2D getPreviousPos() { return previousPos_; }
	//Devuelve la posición del clon
	const Stats& getStats() { return currStats_; };
	//Devuelve la información del equipment
	playerEquipment& const getInfoEquip() { return equip_; }
	
#pragma endregion
#pragma region Setters
	void decreaseMana(double mana);

	void equip(Armor* armor) { equip_.armor_ = armor; };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves; };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword; };
	void equip(Gun* gun) { equip_.gun_ = gun; };
	void equipPotion1(usable* pot) { equip_.potion1_ = pot; }
	void equipPotion2(usable* pot) { equip_.potion2_ = pot; }

	void addMoney(int money) { money_ += money; };
	void usePotion(int value, potionType type);
	void desactivePotion();

	void setElementsHUD();
	void setClonCoolDown() { cdSkills[3] = true; }
	//Aumenta la cadencia de tiro del player
	void activateSwiftGunslinger() { currStats_.distRate_ -= RANGE_SPEED; };
	//Activa el ataque potenciado
	void activateEmpowered() { empoweredAct_ = true; };
#pragma endregion
#pragma region SkillsEquipped
	///<summary>Número máximo de skills equipables</summary>
	static const int MAX_SKILLS = 3;
	Skill* getEquippedSkill(int key) { return skillsEquipped_[key]; }
	void setSkillAt(int key, Skill* skill) { if(skillsEquipped_[key]!= nullptr)delete skillsEquipped_[key]; skillsEquipped_[key] = skill; }
	array <Skill*, MAX_SKILLS>& getSkillsArray() { return skillsEquipped_; }
#pragma endregion

	void setPerforate(bool perforate) { perforate_ = perforate; };
	//Activa la perforación
	//Activa el rebote y el momento en el que se usa
	void setRicochet(bool ricochet) { ricochet_ = ricochet; lastTimeRico_ = SDL_GetTicks(); };
private:
	bool attacking_ = false;
	int money_ = 0;
	HandleEvents* eventHandler_ = nullptr;
	GameManager* gm_ = nullptr;
	Clon* clon_ = nullptr;

	Vector2D previousPos_;
	array<Skill*, MAX_SKILLS> skillsEquipped_ = {nullptr, nullptr, nullptr};

	//Habilidades
	vector<Skill*> skills_;
	vector<bool> cdSkills = { false, false, false, false }; //Para saber si están en coolDown
//<summary>Variables relativas a las habilidades</summary>
#pragma region Abilities
	int liberation_ = 2;	//Nivel de la habilidad del clon, debería llevarse a GameManager
	const int RANGE_SPEED = 1000;	//Velocidad extra para el pistolero raudo (a falta de equilibrado)
	bool empoweredAct_ = false;		//Si tiene la habilidad activada
	double empoweredBonus_ = 1.5;	//Bonus porcentual del daño
	bool perforate_ = false;	//Para saber si el siguiente disparo perfora
	bool ricochet_ = false;		//Para saber si los disparos van a rebotar
	const int TIME_RICO = 4;	//En segundos
	int lastTimeRico_ = 0;		//Momento en el que se usa rebote
#pragma endregion

//<summary>Variables de los cooldowns del jugador</summary>
#pragma region Cooldowns
	double clonCooldown_ = 2;		//Cooldown del clon
	double clonTime_ = 0;			//Momento del último clon
	double empoweredCooldown_ = 4;	//Cooldown GolpeFuerte
	double empoweredTime_ = 0;		//Momento del último ataque potenciado
	double meleeTime_ = 0;			//Momento del último ataque
	double shotTime_ = 0;			//Momento del �ltimo disparo
#pragma endregion

//<summary>Estadisticas iniciales del jugador</summary>
#pragma region Stats
	const double HEALTH = 1000;		//Vida
	const double MANA = 100;		//Mana
	const double MANA_REG = 1;		//Regeneración de maná por segundo
	const double ARMOR = 10;		//Armadura
	const double AD = 0;			//Daño a melee
	const double AP = 1000;			//Daño a distancia y de las habilidades
	const double CRIT = 0;			//Crítico
	const double MELEE_RANGE = 20;	//Rango del ataque a melee
	const double DIST_RANGE = 0;	//Rango del ataque a distancia
	const double MOVE_SPEED = 300;	//Velocidad de movimiento
	const double MELEE_RATE = 1;	//Velocidad del ataque a melee en segundos
	const double DIST_RATE = 1;		//Velocidad del ataque a distancia en segundos

	const double CLON_SPAWN_RANGE = 200;
#pragma endregion

	playerEquipment equip_;
	int PotionTime1 = 0;//Variable auxiliar para comprobar la duracion de la pocion1
	int PotionTime2 = 0; //Variable auxiliar para comprobar la duracion de la pocion 2

	void initObject();
	void updateDir(Vector2D target);
};