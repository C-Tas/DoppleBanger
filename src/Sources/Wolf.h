#pragma once
#include "Enemy.h"
class Wolf :
	public Enemy
{
public:
	Wolf(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 },
		vector<Point2D> patrol = { }) :
		Enemy(app, pos, scale), patrol_(patrol) {
		initObject();
	};
	Wolf(Wolf& other) :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };
	Wolf(Wolf&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };

	virtual bool update();
	virtual void initObject();
	virtual void onCollider();
	virtual void move(Vector2D pos);
	//Cuando pierde agro del enemigo
	virtual void lostAggro();
	void setPatrol(Vector2D pos);
	virtual ~Wolf() {};

private:
	virtual void dieAudio() { app_->getAudioManager()->playChannel(Resources::AudioId::WolfDeath, 0, Resources::WolfChannel1); }
	//Punto que representa dentro del vector de patrulla
	int currPatrol_ = 0;
	//Puntos del mapa donde va a patrullar
	vector<Point2D> patrol_;
	//Punto que representa dentro del vector de patrulla
	int currTarget_ = 0;
	bool idle_ = false;
	//Cooldown melee
	Cooldown meleeCD_;
	//Tiempo que el lobo pasa parado cuando llega a un target
	Cooldown idleCD_;
	const double IDLE_PAUSE = 1000;	
	const int VIS_RANGE = 400;

	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animación del lobo)

	//Constantes para crear las diferentes animaciones 
#pragma region Animaciones
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_H_WOLF_FRAME = 100;			//Ancho del frame, estándar para todas

	//Idle
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_R_FRAMES = 4;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 500;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 8;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 500;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 4;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 500;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 8;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 500;		//Frame rate

	//Movimiento
	vector<Anim> moveAnims_;
	vector<Texture*> moveTx_;
	//Movimieno derecha
	const int MOVE_R_FRAMES = 8;			//Frames de la animación
	const int MOVE_R_FRAME_RATE = 80;		//Frame rate
	//Movimieno hacia arriba
	const int MOVE_U_FRAMES = 8;			//Frames de la animación
	const int MOVE_U_FRAME_RATE = 80;		//Frame rate
	//Movimieno hacia izquierda
	const int MOVE_L_FRAMES = 8;			//Frames de la animación
	const int MOVE_L_FRAME_RATE = 80;		//Frame rate
	//Movimieno hacia abajo
	const int MOVE_D_FRAMES = 8;			//Frames de la animación
	const int MOVE_D_FRAME_RATE = 80;		//Frame rate

	//Melee
	bool attacked_ = false;					//Para atacar una sola vez en el frame adecuado
	vector<Anim> meleeAnims_;				//Vector de las animaciones
	vector<Texture*> meleeTx_;				//Vector de las texturas
	//Melee derecha
	const int MELEE_R_FRAMES = 7;			//Frames de la animación
	const int MELEE_R_FRAME_RATE = 200;		//Frame rate
	//Melee hacia arriba
	const int MELEE_U_FRAMES = 8;			//Frames de la animación
	const int MELEE_U_FRAME_RATE = 175;		//Frame rate
	//Melee hacia izquierda
	const int MELEE_L_FRAMES = 7;			//Frames de la animación
	const int MELEE_L_FRAME_RATE = 200;		//Frame rate
	//Melee hacia abajo
	const int MELEE_D_FRAMES = 7;			//Frames de la animación
	const int MELEE_D_FRAME_RATE = 200;		//Frame rate

	//Inicialización de las animaciones
	virtual void initAnims();
	//Inicia la animación
	void initIdle();
	void initMove();
	void initMelee();
	//Controla la animación
	void meleeAnim();
#pragma endregion

	//Ataque del lobo
	void attack();

	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy();
	//Cuando pierde agro del enemigo
	virtual void lostAgro();
	//Genera la posici�n a la que se mueve el pirata en funci�n de su rango 
	void selectTarget();

	virtual void initialStats();
	virtual void initRewards();
	virtual void updateCooldowns();
};