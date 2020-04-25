#pragma once
#include "Actor.h"
#include "Clon.h"
#include "usable.h"
#include "HandleEvents.h"
#include <array>
#include "GameManager.h"
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

	//Calcula hacia dónde mira el player en función del ratón
	void updateDirVisMouse();
	//Calcula hacia dónde mira el player en función del enemigo
	void updateDirVisEnemy();
	//Establece la direccion del movimiento
	virtual void move(Point2D target);
	//Dispara creando una bala en la posicion dir
	void shoot(Vector2D dir);
	//Ataque cuerpo a cuerpo
	void attack(Enemy* obj);
	//Grita
	void shout();
	//<summary>Devuelve un puntero Skill* a la habilidad del tipo que le pases por parámetro
	//devuelve nullptr si no está equipada y si es una pasiva</summary>
	Skill* createSkill(SkillName name);
	//Crea un clon. A este método lo llama solo la skill "ClonSkill"
	void createClon();
	//Mueve al jugador una distancia en una direccion
	void displace(Vector2D dir, int dist);
	//Si se ha muerto el enemigo al que está atacando el jugador se setea a nullptr
	void isEnemyDead(Actor* obj);
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
	virtual void stop() { dir_ = Vector2D(0, 0); initIdle(); };
	///<summary>Método para crear las skills que tiene el player
	///se llama desde el initState del playState porque es necesario que esté creado el HUD</summary>
	void initSkills();

#pragma region Getters
	const Clon* getClon() { return clon_; };
	const int getLiberation() { return liberation_; };
	const int getMoney() { return money_; };
	const double getMaxHealth() { return HEALTH; }; //Faltaria poner una variable que lleve la vida maxima sin ser cte
	const double getMaxMana() { return MANA; }; //Faltaria poner una variable que lleve el mana maximo sin ser cte

	const Vector2D getPreviousPos() { return previousPos_; }

	const Stats& getStats() { return currStats_; };
	//habilidades
	//activa la pasiva invencible y aplica los efectos de esta
	void activeInvincible();
	//Devuelve la información del equipment
	playerEquipment& const getInfoEquip() { return equip_; }
	
#pragma endregion
#pragma region Setters
	//Activa la perforación
	void setPerforate(bool perforate) { perforate_ = perforate; };
	//Activa el rebote y el momento en el que se usa
	void setRicochet(bool ricochet) { ricochet_ = ricochet; lastTimeRico_ = SDL_GetTicks(); };

	void decreaseMana(double mana);
	inline void setLiberation1() { liberation_ = 1; };
	inline void setLiberation2( ) { liberation_ = 2; };

	void equip(Armor* armor) { equip_.armor_ = armor; };
	void equip(Gloves* gloves) { equip_.gloves_ = gloves; };
	void equip(Boots* boots) { equip_.boots_ = boots; };
	void equip(Sword* sword) { equip_.sword_ = sword; };
	void equip(Gun* gun) { equip_.gun_ = gun; };
	void equipPotion1(usable* pot) { equip_.potion1_ = pot; };
	void equipPotion2(usable* pot) { equip_.potion2_ = pot; };

	void addMoney(int money) { money_ += money; };
	void usePotion(int value, potionType type);
	void desactivePotion();
	void setClonCoolDown() { cdSkills[3] = true; }
	//Aumenta la cadencia de tiro del player
	void activateSwiftGunslinger() { currStats_.distRate_ -= RANGE_SPEED; };
	//Activa el ataque potenciado
	void activateEmpowered() { empoweredAct_ = true; };
#pragma endregion

#pragma region Skills
	///<summary>Número máximo de skills equipables</summary>
	Skill* getEquippedSkill(int key) { return skills_[key]; }
	void setSkillAt(int key, Skill* skill) { 
		if(skills_[key]!= nullptr)delete skills_[key]; 
		skills_[key] = skill; }
	vector <Skill*>& getSkillsArray() { return skills_; }
#pragma endregion


private:
	bool attacking_ = false;
	int money_ = 0;
	HandleEvents* eventHandler_ = nullptr;
	GameManager* gm_ = nullptr;
	Clon* clon_ = nullptr;

	Vector2D previousPos_;

	//Habilidades
	vector<Skill*> skills_;
	vector<bool> cdSkills = { false, false, false, false }; //Para saber si están en coolDown
	DIR lookAt;	//Hacia dónde mira
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

	//Movimiento
	vector<Anim> moveAnims_;
	vector<Texture*> moveTx_;
	//Movimieno derecha
	const int MOVE_R_FRAMES = 8;			//Frames de la animación
	const int MOVE_R_FRAME_RATE = 100;		//Frame rate
	//Movimieno hacia arriba
	const int MOVE_U_FRAMES = 8;			//Frames de la animación
	const int MOVE_U_FRAME_RATE = 100;		//Frame rate
	//Movimieno hacia izquierda
	const int MOVE_L_FRAMES = 8;			//Frames de la animación
	const int MOVE_L_FRAME_RATE = 100;		//Frame rate
	//Movimieno hacia abajo
	const int MOVE_D_FRAMES = 8;			//Frames de la animación
	const int MOVE_D_FRAME_RATE = 100;		//Frame rate

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
	void initMove();
	void initShoot();
	void initMelee();
	//Controla la animación
	void shootAnim();
	void meleeAnim();
#pragma endregion
//<summary>Variables relativas a las habilidades</summary>
#pragma region Abilities
	const int CRIT_INV = 20;	//Crítico agregado al player después de activar invencible( a falta de equilibrado)
	const int DMG_INV = 20;		//Daño agregado al player después de activar invencible( a falta de equilibrado)
	int liberation_ = 2;	//Nivel de la habilidad del clon, debería llevarse a GameManager
	const int RANGE_SPEED = 1000;	//Velocidad extra para el pistolero raudo (a falta de equilibrado)
	bool empoweredAct_ = false;		//Si tiene la habilidad activada
	bool empoweredAnim_ = false; //Si ha empezado la animación del ataque potenciado
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
	const double HEALTH = 1000;			//Vida
	const double MANA = 100;			//Mana
	const double MANA_REG = 1;			//Regeneración de maná por segundo
	const double ARMOR = 10;			//Armadura
	const double MELEE_DAMAGE = 0;		//Daño a melee
	const double DIST_DAMAGE = 1000;	//Daño a distancia y de las habilidades
	const double CRIT = 0;				//Crítico
	const double MELEE_RANGE = 20;		//Rango del ataque a melee
	const double DIST_RANGE = 0;		//Rango del ataque a distancia
	const double MOVE_SPEED = 300;		//Velocidad de movimiento
	const double MELEE_RATE = 1;		//Velocidad del ataque a melee en segundos
	const double DIST_RATE = 1;			//Velocidad del ataque a distancia en segundos

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
	void updateDir(Vector2D dir);
	playerEquipment equip_;
	int PotionTime1 = 0;//Variable auxiliar para comprobar la duracion de la pocion1
	int PotionTime2 = 0; //Variable auxiliar para comprobar la duracion de la pocion 2
};