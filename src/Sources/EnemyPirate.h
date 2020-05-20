#pragma once
#include "Enemy.h"
class EnemyPirate :
	public Enemy
{
public:
	EnemyPirate(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 },
		vector<Point2D> patrol = { {0,0} }) :
		Enemy(app, pos, scale), patrol_(patrol) {
		initObject();
	};
	EnemyPirate(EnemyPirate& other) :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };
	EnemyPirate(EnemyPirate&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };

	virtual bool update();
	virtual void initObject();
	virtual void onCollider();
	virtual void move(Vector2D pos);
	//Cuando pierde agro del enemigo
	virtual void lostAggro();
	virtual  ~EnemyPirate() {};

private:
	//Puntos del mapa donde va a patrullar
	vector<Point2D> patrol_;
	//Punto que representa dentro del vector de patrulla
	int currPatrol_ = 0;
	//Enum que representa los diferentes estados de ataque del pirata
	enum class ATK_STATUS
	{
		MELEE, RANGE
	};
	//Estado de ataque actual del pirata
	ATK_STATUS currAtackStatus_ = ATK_STATUS::RANGE;
	//Tiempo que espera entre disparos
	Cooldown shootCD_;
	//Tiempo que espera entre golpes
	Cooldown meleeCD_;
	//Tiempo que espera parado
	const double IDLE_PAUSE = 5000;
	Cooldown idleCD_;

	//Constantes para crear las diferentes animaciones 
#pragma region Animaciones
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_H_PIRATE_FRAME = 100;		//Ancho del frame, estándar para todas

	//Idle
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_R_FRAMES = 4;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 500;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 4;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 500;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 4;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 500;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 4;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 500;		//Frame rate

	//Movimiento
	vector<Anim> moveAnims_;
	vector<Texture*> moveTx_;
	//Movimieno derecha
	const int MOVE_R_FRAMES = 4;			//Frames de la animación
	const int MOVE_R_FRAME_RATE = 200;		//Frame rate
	//Movimieno hacia arriba
	const int MOVE_U_FRAMES = 4;			//Frames de la animación
	const int MOVE_U_FRAME_RATE = 200;		//Frame rate
	//Movimieno hacia izquierda
	const int MOVE_L_FRAMES = 4;			//Frames de la animación
	const int MOVE_L_FRAME_RATE = 200;		//Frame rate
	//Movimieno hacia abajo
	const int MOVE_D_FRAMES = 4;			//Frames de la animación
	const int MOVE_D_FRAME_RATE = 200;		//Frame rate

	//Disparo
	bool shooted_ = false;					//Para disparar una sola vez en el frame adecuado
	vector<Anim> shootAnims_;				//Vector de las animaciones
	vector<Texture*> shootTx_;				//Vector de las texturas
	//Disparo derecha
	const int SHOOT_R_FRAMES = 15;			//Frames de la animación
	const int SHOOT_R_FRAME_RATE = 150;		//Frame rate
	//Disparo hacia arriba
	const int SHOOT_U_FRAMES = 17;			//Frames de la animación
	const int SHOOT_U_FRAME_RATE = 132;		//Frame rate
	//Disparo hacia izquierda
	const int SHOOT_L_FRAMES = 16;			//Frames de la animación
	const int SHOOT_L_FRAME_RATE = 141;		//Frame rate
	//Disparo hacia abajo
	const int SHOOT_D_FRAMES = 12;			//Frames de la animación
	const int SHOOT_D_FRAME_RATE = 187;		//Frame rate

	//Melee
	bool attacked_ = false;					//Para atacar una sola vez en el frame adecuado
	vector<Anim> meleeAnims_;				//Vector de las animaciones
	vector<Texture*> meleeTx_;				//Vector de las texturas
	//Melee derecha
	const int MELEE_R_FRAMES = 6;			//Frames de la animación
	const int MELEE_R_FRAME_RATE = 100;		//Frame rate
	//Melee hacia arriba
	const int MELEE_U_FRAMES = 4;			//Frames de la animación
	const int MELEE_U_FRAME_RATE = 150;		//Frame rate
	//Melee hacia izquierda
	const int MELEE_L_FRAMES = 6;			//Frames de la animación
	const int MELEE_L_FRAME_RATE = 100;		//Frame rate
	//Melee hacia abajo
	const int MELEE_D_FRAMES = 6;			//Frames de la animación
	const int MELEE_D_FRAME_RATE = 100;		//Frame rate

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

	//Estadisticas para inicializar
	const int VIS_RANGE = 500;
	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Ataque del pirata enemigo
	void attack();
	//Devuelve true si el target est� dentro del rango de ataque
	bool onRange();
	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy();
	//Cuando pierde agro del enemigo
	virtual void lostAgro();
	//Genera la posición a la que se mueve el pirata en función de su rango 
	void selectTarget();
	virtual void initialStats();
	virtual void initRewards();
	virtual void updateCooldowns();
};