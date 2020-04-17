#pragma once
#include "Actor.h"
#include "HandleEvents.h"
#include "Clon.h"
#include "Enemy.h"
#include "usable.h"
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
	const int getLiberation() { return liberation_; };
	const bool getExplotion() { return explotion_; };
	const Stats& getStats() { return currStats_; };
	const Vector2D getPreviousPos() { return previousPos_; }
	virtual void die() { currState_ = STATE::DYING; }
	//metodos para coger la info del player
	playerEquipment& const getInfoEquip() { return equip_; }
	void desactivePotion();
	void init();
	void equip(Armor* armor) { equip_.armor_ = armor; };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves; };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword; };
	void equip(Gun* gun) { equip_.gun_ = gun; };
	void equipPotion1(usable* pot) { equip_.potion1_ = pot; }
	void equipPotion2(usable* pot) { equip_.potion2_ = pot; }

	//metodos para usar las pociones
	void usePotion(int value, potionType type);
	//metodos para guardar el puntero al equipamiento

#pragma region SkillsEquipped
	///<summary>Número máximo de skills equipables</summary>
	static const int MAX_SKILLS = 3;
	Skill* getSkillEquipped(int key) { return skillsEquiped_[key]; }
	void setSkillAt(int key, Skill* skill) { if(skillsEquiped_[key]!= nullptr)delete skillsEquiped_[key]; skillsEquiped_[key] = skill; }
	array <Skill*, MAX_SKILLS>& getSkillsArray() { return skillsEquiped_; }
#pragma endregion

private:
	uint lastMeleeHit_ = 0;
	bool attacking_ = false;
	Actor* objective_ = nullptr;
	Clon* clon_ = nullptr;
	HandleEvents* eventHandler_ = nullptr;
	Vector2D previousPos_;
	DIR lookAt;	//Hacia dónde mira
	array<Skill*, MAX_SKILLS> skillsEquiped_ = {nullptr, nullptr, nullptr};
#pragma region Animaciones
	Texture* auxTx_ = nullptr;				//Textura de idle temporal, se borrará cuadno esté el idle
	Vector2D mousePos_{ 0,0 };				//Vector donde se ha hecho click al disparar
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_H_PLAYER_FRAME = 100;		//Ancho del frame, estándar para todas
	
	//Idle
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_R_FRAMES = 4;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 500;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 2;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 500;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 4;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 500;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 2;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 500;		//Frame rate

	//Disparo
	bool shooted_ = false;					//Para disparar una sola vez en el frame adecuado
	vector<Anim> shootAnims_;				//Vector de las animaciones
	vector<Texture*> shootTx_;				//Vector de las texturas
	//Disparo derecha
	const int SHOOT_R_FRAMES = 3;			//Frames de la animación
	const int SHOOT_R_FRAME_RATE = 150;		//Frame rate
	//Disparo hacia arriba
	const int SHOOT_U_FRAMES = 7;			//Frames de la animación
	const int SHOOT_U_FRAME_RATE = 40;		//Frame rate
	//Disparo hacia izquierda
	const int SHOOT_L_FRAMES = 3;			//Frames de la animación
	const int SHOOT_L_FRAME_RATE = 150;		//Frame rate
	//Disparo hacia abajo
	const int SHOOT_D_FRAMES = 7;			//Frames de la animación
	const int SHOOT_D_FRAME_RATE = 40;		//Frame rate

	//Melee
	bool attacked_ = false;					//Para atacar una sola vez en el frame adecuado
	vector<Anim> meleeAnims_;				//Vector de las animaciones
	vector<Texture*> meleeTx_;				//Vector de las texturas
	//Melee derecha
	const int MELEE_R_FRAMES = 5;			//Frames de la animación
	const int MELEE_R_FRAME_RATE = 200;		//Frame rate
	//Melee hacia arriba
	const int MELEE_U_FRAMES = 3;			//Frames de la animación
	const int MELEE_U_FRAME_RATE = 150;		//Frame rate
	//Melee hacia izquierda
	const int MELEE_L_FRAMES = 5;			//Frames de la animación
	const int MELEE_L_FRAME_RATE = 200;		//Frame rate
	//Melee hacia abajo
	const int MELEE_D_FRAMES = 5;			//Frames de la animación
	const int MELEE_D_FRAME_RATE = 200;		//Frame rate

	//Inicialización de las animaciones
	virtual void initAnims();
	//Inicia la animación
	void initIdle();
	void initShoot();
	void initMelee();
	//Controla la animación
	void shootAnim();
	void meleeAnim();
	//Calcula hacia dónde mira el player en función del ratón
	void updateDirVisMouse();
	//Calcula hacia dónde mira el player en función del enemigo
	void updateDirVisEnemy();
#pragma endregion
//<summary>Variables relativas a las habilidades</summary>
#pragma region Abilities
	int liberation_ = 2;	//Nivel de la habilidad del clon
	bool explotion_ = false;	//Si tiene la habilidad activada
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
	playerEquipment equip_;
	int PotionTime1 = 0;//Variable auxiliar para comprobar la duracion de la pocion1
	int PotionTime2 = 0; //Variable auxiliar para comprobar la duracion de la pocion 2
};