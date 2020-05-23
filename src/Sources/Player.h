#pragma once
#include "Actor.h"
#include "Clon.h"
#include "HandleEvents.h"
#include <array>
#include "GameManager.h"
#include "jute.h"
#include "TextBox.h"

class Skill;
class Armor;
class Gloves;
class Boots;
class Sword;
class Gun;
class usable;

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
	//<summary>Devuelve un puntero Skill* a la habilidad del tipo que le pases por parámetro
	//devuelve nullptr si no está equipada y si es una pasiva</summary>
	Skill* createSkill(SkillName name);
	//Crea un clon. A este método lo llama solo la skill "ClonSkill"
	void createClon();
	//Mueve al jugador una distancia en una direccion
	void displace(Vector2D dir, int dist);
	//Aplica una ralentiazación al jugador
	void applySlow(double slow, double duration);
	//Si se ha muerto el enemigo al que está atacando el jugador se setea a nullptr
	void isEnemyDead(Actor* obj);
	//Regeneración de mana
	void manaReg();
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
	virtual void stop() { dir_ = Vector2D(0, 0); initIdle(); onCollision_ = true; };

	#pragma region Getters
		const bool getDead() { return dead_; };
	const bool getOnCollision() { return onCollision_; };
		const bool isEquipInit() { return initEquip_; };
		const int getLiberation() { return liberation_; };
		const double getMaxHealth() { return maxHealth_; }; //Devuelve la vida maxima del player
		const double getMaxMana() { return maxMana_; };		//Devuelve el mana maximo del player
		Clon* getClon() { return clon_; };

		const Vector2D getPreviousPos() { return previousPos_; }
		 
		const Stats& getStats() { return currStats_; };
		//habilidades
		//activa la pasiva invencible y aplica los efectos de esta
		void activeInvincible();

		//<summary>Método para obtener el textbox que sale cuando el player llega al final del nivel</summary>
		TextBox* getEndZoneTextBox() { return endZoneTextBox_; };
	
#pragma endregion
	#pragma region Setters
	//Activa la perforación
	void setPerforate(bool perforate) {
		app_->getAudioManager()->playChannel(Resources::PerforateSkill, 0, Resources::PlayerChannel2);
		perforate_ = perforate; };
	//Activa el rebote y el momento en el que se usa
	void activeRicochet() { 
		app_->getAudioManager()->playChannel(Resources::Ricochet, 0, 3);
		ricochetCD_.initCooldown(RICOCHET_DELAY);
	};
		//Para saber si hay que inicializar el equipamiento
		void setinitEquip(bool init) { initEquip_ = init; };
	//Setea si el player ha colisionado
	void setOnCollision(bool coll) { onCollision_ = coll; };

		void decreaseMana(double mana);
		inline void setLiberation(int level) { liberation_ = level; };
		//inline void setLiberation2() { liberation_ = 2; };

		void equip(Armor* armor) { armor_ = armor; gm_->setArmor(armor); };
		void equip(Gloves* gloves) { gloves_ = gloves; gm_->setGloves(gloves); };
		void equip(Boots* boots) { boots_ = boots; gm_->setBoots(boots);};
		void equip(Sword* sword) { sword_ = sword; gm_->setSword(sword);};
		void equip(Gun* gun) { 
			changeDistWeaponStats(gun);
			gm_->setGun(gun);
		}
		void addMaxHealth(double addition) { maxHealth_ += addition; };
		void addMaxMana(double addition) { maxMana_ += addition; };
		//Aumenta la cadencia de tiro del player
		void activateSwiftGunslinger() { currStats_.distRate_ -= RANGE_SPEED; };
		//Activa el ataque potenciado
		void activateEmpowered() { initEmpowered(); };

		//Carga el equipamiento del player
		void load();
	#pragma endregion
	#pragma region Pociones
		//Metodo para usar las pociones
		void usePotion(usable* potion, int key);
		//Metodo para actualizar el tiempo de las pociones y desactivarlas
		void updateBuffPotion();
		//Equipa pociones
		void equipPotion1(usable* pot) { potions_[0] = pot; gm_->setPotion(0, potions_[0]); };
		void equipPotion2(usable* pot) { potions_[1] = pot; gm_->setPotion(1, potions_[1]); };
		//Devuelve el instante en el que se usó la poción
		const double getTimerPotion(int potion) { return timerPotion_[potion]; };
	#pragma endregion
	#pragma region Skills
		///<summary>Método para crear las skills que tiene el player
		///se llama desde el initState del playState porque es necesario que esté creado el HUD</summary>
		void initSkills();
		///<summary>Número máximo de skills equipables</summary>
		Skill* getEquippedSkill(int key) { return skills_[key]; }
		void setSkillAt(int key, Skill* skill) { 
			if(skills_[key]!= nullptr)delete skills_[key]; 
			skills_[key] = skill; }
		vector <Skill*>& getSkillsArray() { return skills_; }
		//Inicia la animacion empowered
		void initEmpowered();
	#pragma endregion
		//Determina si el player utiliza el golpe fuerte
		bool isDummyAttack() { return empoweredAct_; }

private:
	bool dead_ = false;
	bool attacking_ = false;
	bool onCollision_ = false;
	bool initEquip_ = true;	//Para saber si hiay que inicializar el equipamiento
	bool slowed_ = false;
	double slowEffect_ = 0;
	HandleEvents* eventHandler_ = nullptr;
	GameManager* gm_ = nullptr;
	Clon* clon_ = nullptr;

	Vector2D previousPos_;
	//Habilidades
	vector<Skill*> skills_ = { nullptr, nullptr, nullptr, nullptr};

	//cambia los stats de un arma
	void changeDistWeaponStats(Gun* newWeapon);

	//Objetos
	//<Speed, Damage, Armor, Crit>
	vector<bool> potionUsing_{ 0, 0, 0, 0 };		//Para saber si se está usando la poción y resetear el tiempo
	vector<double> timerPotion_{ 0, 0, 0, 0 };		//Para guardar y restablecer el tiempo de las pociones
	vector<double> valuePotion_{ 0, 0, 0, 0 };		//Para guardar los valores de incremento de Stats
	vector<double> lastTicksPotion_{ 0, 0, 0, 0 };	//Para guardar el último tick 
	#pragma region Animaciones
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

		//Golpe Fuerte
		vector<Texture*>empoweredTx_;
		vector<Anim> empoweredAnims_;
		//Derecha e izquierda
		const int EMPOWERED_R_L_FRAMES = 11;
		const int EMPOWERED_R_L_RATE = 70;
		//Arriba y abajo
		const int EMPOWERED_U_D_FRAMES = 12;
		const int EMPOWERED_U_D_RATE = 75;

		virtual void feedBackHurtSounds();
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
		void empoweredAnim();
	#pragma endregion
	//<summary>Variables relativas a las habilidades</summary>
	#pragma region Abilities
	const int CRIT_INV = 20;	//Crítico agregado al player después de activar invencible( a falta de equilibrado)
	const int DMG_INV = 20;		//Daño agregado al player después de activar invencible( a falta de equilibrado)
	int liberation_ = 2;	//Nivel de la habilidad del clon, debería llevarse a GameManager
	const int RANGE_SPEED = 1000;	//Velocidad extra para el pistolero raudo (a falta de equilibrado)
	bool empoweredAct_ = false;		//Si tiene la habilidad activada
	bool meleeActive_ = false;		//Para saber si la animación se ha inicializado
	double empoweredBonus_ = 1.5;	//Bonus porcentual del daño
	bool perforate_ = false;	//Para saber si el siguiente disparo perfora
#pragma endregion
	//<summary>Variables de los cooldowns del jugador</summary>
	#pragma region Cooldowns
	virtual void updateCooldowns();
	Cooldown slowTimeCD_;	//Tiempo que nos queda "slow"
	Cooldown shootCD_;	//Cooldown del disparo
	Cooldown meleeCD_;	//Cooldown ataque melee
	const double EMPOWERED_DELAY = 10000;
	Cooldown empoweredCD_;	//Cooldown skill golpe fuerte
	const double RICOCHET_DELAY = 5000;
	Cooldown ricochetCD_;	//Cooldown skill golpe fuerte
	Cooldown manaCD_;		//Cooldown manaReg
	const double MANA_REG_DELAY = 3000; //Tiempo regeneracion de mana = 1 seg
	bool initManaReg_ = true;
#pragma endregion

	//<summary>Estadisticas iniciales del jugador</summary>
	#pragma region Stats
	double maxHealth_ = 100000000;			//Representa la cantidad maxima de vida
	double maxMana_ = 100;				//Representa la cantidad maxima de mana
	const double MANA_REG = 1;			//Regeneración de maná por segundo
	const double ARMOR = 10;			//Armadura
	const double MELEE_DAMAGE = 100;	//Daño a melee
	const double DIST_DAMAGE = 1000;	//Daño a distancia y de las habilidades
	const double CRIT = 0;				//Crítico
	const double MELEE_RANGE = 20;		//Rango del ataque a melee
	const double DIST_RANGE = 2000;		//Rango del ataque a distancia
	const double MOVE_SPEED = 300;		//Velocidad de movimiento
	const double MELEE_RATE = 3000;		//Velocidad del ataque a melee en segundos
	const double DIST_RATE = 5000;		//Velocidad del ataque a distancia en segundos
	const double CLON_SPAWN_RANGE = 200;
#pragma endregion
	//Constantes para el delay de los efectos de sonido
	#pragma region constSounds
		const double WALK_TIME = 600;
	#pragma endregion
	//variables para controlar ultimos sonidos
	#pragma region LastSounds
		double lastWalkSound_ = 0;
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
	//Equipamiento
	Armor* armor_ = nullptr;	//Pechera
	Gloves* gloves_ = nullptr;	//Guantes
	Boots* boots_ = nullptr;	//Botas
	Sword* sword_ = nullptr;	//Espada
	Gun* gun_ = nullptr;		//Pistola
	vector<usable*> potions_{ nullptr, nullptr };	//Pociones

	TextBox* endZoneTextBox_ = nullptr;
};