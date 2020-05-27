#pragma once
#include <array>
#include "jute.h"
#include "TextBox.h"
#include "Actor.h"

class CollisionCtrl;
class GameManager;
class HandleEvents;
class Skill;
class Armor;
class Gloves;
class Boots;
class Sword;
class Gun;
class usable;
class Clon;

class Player : public Actor
{
public:
	//Constructora de player
	Player(Application* app, Vector2D pos, Vector2D scale);
	~Player();
	///<summary>Constructor por copia</summary>
	Player(const Player& other) : Actor(other.app_, other.pos_, other.scale_), skills_(other.skills_) {
		eventHandler_ = HandleEvents::instance();
	};

	#pragma region Inicializadores
		//Carga el equipamiento del player
		void load();
		//Inicializa las skills
		void initSkills();
		//Inicia la animacion empowered
		void initEmpowered();
		//Inicia la animacion torbellino
		void initWhirl();
	#pragma endregion

	//Actualizador principal
	virtual bool update();
	//Metodo para actualizar el tiempo de las pociones y desactivarlas
	void updateBuffPotion();
	//Regeneración de mana
	void manaReg();

	#pragma region Habilidades y pociones
		//<summary>Devuelve un puntero Skill* a la habilidad del tipo que le pases por parámetro
		//devuelve nullptr si no está equipada y si es una pasiva</summary>
		Skill* createSkill(SkillName name);
		//activa la pasiva invencible y aplica los efectos de esta
		void activeInvincible();
		//Aumenta la cadencia de tiro del player
		void activateSwiftGunslinger() { currStats_.distRate_ -= RANGE_SPEED; };
		//Crea un clon. A este método lo llama solo la skill "ClonSkill"
		void createClon();
		//Mata al clon
		bool killClon();

		//Metodo para usar las pociones
		void usePotion(usable* potion, int key);
		//Equipa pociones
		void equipPotion1(usable* pot) { potions_[0] = pot; gm_->setPotion(0, potions_[0]); };
		void equipPotion2(usable* pot) { potions_[1] = pot; gm_->setPotion(1, potions_[1]); };
	#pragma endregion

	#pragma region Getters
		const bool getDead() { return dead_; };
		const bool getOnCollision() { return onCollision_; };
		const bool isEquipInit() { return initEquip_; };
		const bool isDummyAttack() { return empoweredAct_; }		//Determina si el player utiliza el golpe fuerte
		
		const int getLiberation() { return liberation_; };
		
		const double getMaxHealth() { return maxHealth_; }; //Devuelve la vida maxima del player
		const double getMaxMana() { return maxMana_; };		//Devuelve el mana maximo del player

		const Vector2D getPreviousPos() { return previousPos_; }
		vector <Skill*>& getSkillsArray() { return skills_; }
		const Stats& getStats() { return currStats_; };
		///<summary>Método para crear las skills que tiene el player
		///se llama desde el initState del playState porque es necesario que esté creado el HUD</summary>
		///<summary>Número máximo de skills equipables</summary>
		Skill* getEquippedSkill(int key) { return skills_[key]; }
		//<summary>Método para obtener el textbox que sale cuando el player llega al final del nivel</summary>
		TextBox* getEndZoneTextBox() { return endZoneTextBox_; };
		//Devuelve el clon
		Clon* getClon() { return clon_; };
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
		//Gasta mana
		void decreaseMana(double mana);
		inline void setLiberation(int level) { liberation_ = level; };

		void equip(Armor* armor) { armor_ = armor; gm_->setArmor(armor); };
		void equip(Gloves* gloves) { gloves_ = gloves; gm_->setGloves(gloves); };
		void equip(Boots* boots) { boots_ = boots; gm_->setBoots(boots);};
		void equip(Sword* sword) { sword_ = sword; gm_->setSword(sword);};
		void equip(Gun* gun) { gun_ = gun; gm_->setGun(gun); }

		void addMaxHealth(double addition) { maxHealth_ += addition; };
		void addMaxMana(double addition) { maxMana_ += addition; };
		void setSkillAt(int key, Skill* skill);

	#pragma endregion

	#pragma region Otros
		virtual void onCollider() {};
		//Mueve al jugador una distancia en una direccion
		void displace(Vector2D dir, int dist);
		//Aplica una ralentiazación al jugador
		void applySlow(double slow, double duration);
		//Si se ha muerto el enemigo al que está atacando el jugador se setea a nullptr
		void isEnemyDead(Actor* obj);
		//Cambia de estado a muriendo
		virtual void die() { currState_ = STATE::DYING; }
		virtual void stop() { dir_ = Vector2D(0, 0); initIdle(); onCollision_ = true; };
	#pragma endregion

private:
	#pragma region Variables
		//Singleton
		HandleEvents* eventHandler_ = nullptr;
		GameManager* gm_ = nullptr;
		CollisionCtrl* collisionCtrl_ = nullptr;

		bool empoweredAct_ = false;		//Si tiene la habilidad activada
		bool empoweredInit_ = false;	//Para saber si la animación se ha inicializado
		bool perforate_ = false;		//Para saber si el siguiente disparo perfora
		bool bussy_ = false;			//Para saber si el player esta ocupado ejecutando otras acciones
		bool meleeBussy_ = false;		//Para no inicializar otra vez el melee si se dan mas clicks
		bool dead_ = false;				//Para saber si el player ha muerto de verdad (fin animacion)
		bool attacking_ = false;		//Para saber si el player esta atacando
		bool onCollision_ = false;		//Para saber si el player esta colisionando
		bool initEquip_ = true;			//Para saber si hay que inicializar el equipamiento
		bool slowed_ = false;			//Para saber si esta ralentizado
		bool changeZone_ = false;		//Para saber si hay que cambiar de zona

		int liberation_ = 0;			//Nivel de la habilidad del clon, debería llevarse a GameManager
		double slowEffect_ = 0;			//Efecto del slow
		double lastWalkSound_ = 0;		//Ultimo tick del sonido
		double maxHealth_ = 1300;		//Representa la cantidad maxima de vida
		double maxMana_ = 1000;			//Representa la cantidad maxima de mana

		Vector2D previousPos_;
		TextBox* endZoneTextBox_ = nullptr;

		//Equipamiento
		Armor* armor_ = nullptr;	//Pechera
		Gloves* gloves_ = nullptr;	//Guantes
		Boots* boots_ = nullptr;	//Botas
		Sword* sword_ = nullptr;	//Espada
		Gun* gun_ = nullptr;		//Pistola
		Clon* clon_ = nullptr;

		//Objetos
		vector<usable*> potions_{ nullptr, nullptr };	//Pociones
			//<Speed, Damage, Armor, Crit>
		vector<bool> potionUsing_{ 0, 0, 0, 0 };		//Para saber si se está usando la poción y resetear el tiempo
		vector<double> timerPotion_{ 0, 0, 0, 0 };		//Para guardar y restablecer el tiempo de las pociones
		vector<double> valuePotion_{ 0, 0, 0, 0 };		//Para guardar los valores de incremento de Stats
		vector<double> lastTicksPotion_{ 0, 0, 0, 0 };	//Para guardar el último tick 
		//Habilidades
		vector<Skill*> skills_ = { nullptr, nullptr, nullptr, nullptr};
		#pragma region Cheats
				bool cheat_ = false;			//Para saber si el player esta chetado

				//Valores adicionales para el cheat
				double healthCheat_ = 100000;			//Vida
				double manaRegCheat_ = 100;				//Regeneración de maná por segundo, porcentaje
				double armorCheat_ = 100;				//Armadura
				double meleeDamageCheat_ = 1000000;		//Daño a melee
				double distDmgCheat_ = 100000;			//Daño a distancia y de las habilidades
				double critCheat_ = 100;				//Crítico
				double distRangeCheat_ = 10000;			//Rango del ataque a distancia
				double moveSpeedCheat_ = 500;			//Velocidad de movimiento
		#pragma endregion

		#pragma region Cooldowns
			Cooldown slowTimeCD_;		//Tiempo que nos queda "slow"
			Cooldown shootCD_;			//Cooldown del disparo
			Cooldown meleeCD_;			//Cooldown ataque melee
			Cooldown empoweredCD_;		//Cooldown skill golpe fuerte
			Cooldown ricochetCD_;		//Cooldown skill golpe fuerte
			Cooldown manaCD_;			//Cooldown manaReg
			bool initManaReg_ = true;	//Para saber cuando empezar a recuperar mana
		#pragma endregion

		#pragma region Constantes
		//Estadisticas iniciales del jugador</summary>
		const double MANA_REG = 3;						//Regeneración de maná por segundo, porcentaje
		const double ARMOR = 0;							//Armadura, porcentaje
		const double MELEE_DAMAGE = 0;					//Daño a melee
		const double DIST_DAMAGE = 0;					//Daño a distancia y de las habilidades
		const double CRIT = 0;							//Crítico
		const double MELEE_RANGE = scale_.getX() / 2;	//Rango del ataque a melee
		const double DIST_RANGE = 0;					//Rango del ataque a distancia
		const double MOVE_SPEED = 250;					//Velocidad de movimiento
		const double MELEE_RATE = 1200;					//Velocidad del ataque a melee en milisegundos
		const double DIST_RATE = 1300;					//Velocidad del ataque a distancia en milisegundos

		//Additional Stats
		const int CRIT_INV = 20;				//Crítico agregado al player después de activar invencible( a falta de equilibrado)
		const int DMG_INV = 20;					//Daño agregado al player después de activar invencible( a falta de equilibrado)
		const double EMPOWERED_BONUS = 2.5;		//Bonus porcentual del daño
		const int RANGE_SPEED = 1000;			//Velocidad extra para el pistolero raudo (a falta de equilibrado)

		//Cooldowns milisegundos
		const double EMPOWERED_DELAY = 6000;	//Cooldown del golpe fuerte
		const double RICOCHET_DELAY = 10000;	//Cooldown del rebote
		const double MANA_REG_DELAY = 1500;		//Tiempo regeneracion de mana

		//Balas
		const double W_H_BULLET = app_->getWindowHeight() / 40;	//Tamaño de la bala
		const double BULLET_VEL = 1000;							//Velocidad de la bala
		const double BULLET_LIFE = 1;							//Vida de la bala, en segundo

		//Sonidos
		const double WALK_TIME = 600;
		#pragma endregion

	#pragma endregion

	#pragma region Metodos
		//Inicializadores
		virtual void initObject();
		//Updates
		//Actualiza el estado de los debuffs actuales
		void updateDebuffs();
		//Actualiza los cooldowns
		virtual void updateCooldowns();
		//Checkea si se ha pulsado la tecla para el cheto
		void checkInputCheat();
		//Checkea si se ha pulsado alguna tecla
		void checkInput();
		//Checkea si se ha pulsado una tecla para cambiar de estado
		void checkInputState();
		//Mira si se ha pulsado sobre un enemigo
		Enemy* checkAttack();
		//Actualiza dir
		void updateDir(Vector2D dir);
		//Gestor de movimiento
		void movementManager();

		//Especial, contiene metodos y variables
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
			const int SHOOT_U_FRAME_RATE = 65;		//Frame rate
			//Disparo hacia izquierda
			const int SHOOT_L_FRAMES = 3;			//Frames de la animación
			const int SHOOT_L_FRAME_RATE = 150;		//Frame rate
			//Disparo hacia abajo
			const int SHOOT_D_FRAMES = 7;			//Frames de la animación
			const int SHOOT_D_FRAME_RATE = 65;		//Frame rate

			//Melee
			bool attacked_ = false;					//Para atacar una sola vez en el frame adecuado
			vector<Anim> meleeAnims_;				//Vector de las animaciones
			vector<Texture*> meleeTx_;				//Vector de las texturas
			//Melee derecha
			const int MELEE_R_FRAMES = 5;			//Frames de la animación
			const int MELEE_R_FRAME_RATE = 150;		//Frame rate
			//Melee hacia arriba
			const int MELEE_U_FRAMES = 3;			//Frames de la animación
			const int MELEE_U_FRAME_RATE = 250;		//Frame rate
			//Melee hacia izquierda
			const int MELEE_L_FRAMES = 5;			//Frames de la animación
			const int MELEE_L_FRAME_RATE = 150;		//Frame rate
			//Melee hacia abajo
			const int MELEE_D_FRAMES = 5;			//Frames de la animación
			const int MELEE_D_FRAME_RATE = 150;		//Frame rate

			//Golpe Fuerte
			vector<Texture*>empoweredTx_;
			vector<Anim> empoweredAnims_;
			//Derecha e izquierda
			const int EMPOWERED_R_L_FRAMES = 11;
			const int EMPOWERED_R_L_RATE = 70;
			//Arriba y abajo
			const int EMPOWERED_U_D_FRAMES = 12;
			const int EMPOWERED_U_D_RATE = 75;

			//Torbellino
			vector<Texture*>whirlTx_;
			vector<Anim> whirlAnim_;
			const int W_H_WHIRL_FRAME = 500;
			const int WHIRL_FRAMES = 11;
			const int WHIRL_FRAME_RATE = 60;
			const double WHIRL_DAMAGE = 300;

			virtual void feedBackHurtSounds();
			//Inicialización de las animaciones
			virtual void initAnims();
			//Inicia la animacion de muerte con sus extras
			virtual void initDie();
			//Inicia la animación de idle
			void initIdle();
			//Inicia la animacion de movimiento
			void initMove();
			//Inicia la animacion de disparo
			void initShoot();
			//Inicia la animacion de melee
			void initMelee();
			//Gestor de animaciones
			void animator();
			//Gestiona la animacion de muerte
			virtual void dieAnim();
			//Controla la animación de disparo
			void shootAnim();
			//Controla la animacion de melee
			void meleeAnim();
			//Controla la animacion de empowered
			void empoweredAnim();
			//Controla la animacion de torbellino
			void whirlAnim();
		#pragma endregion

		#pragma region Otros
			//Dispara creando una bala en la posicion dir
			void shoot(Vector2D dir);
			//Establece la direccion del movimiento
			virtual void move(Point2D target);
			//Ataque cuerpo a cuerpo
			void attack(Enemy* obj);
			//Grita
			void shout();
			//Para chetar al player
			void cheatPlayer();
		#pragma endregion
	#pragma endregion
};