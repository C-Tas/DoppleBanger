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
	//Último ataque a distancia
	Uint32 lastRangeHit_ = 0;
	//Último ataque a melee
	Uint32 lastMeleeHit_ = 0;
	//�ltimo frame de animaci�n
	//Uint32 lastFrame_ = 0;
	//Tiempo que el pirata pasa parado cuando llega a un target
	Uint32 idleTime_ = 1000;
	//Tiempo 
	uint lastIdleTime = 0;
	//Diferentes animaciones del pirata
	Anim attackAnim_ = { 0,0,0,0 ,"" };
	Anim walkAnim_ = { 0,0,0,0,"" };
	Anim idleAnim_ = { 0,0,0,0,"" };
	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animación del mono)
#pragma region Constantes
//Para el ataque
	const int NUM_FRAMES_ATK = 10;
	const int NUM_FRAMES_ROW_ATK = 3;
	const uint W_FRAME_ATK = 200;
	const uint H_FRAME_ATK = 200;
	const int FRAME_RATE_ATK = 100;
	const string NAME_ATK = "attack";
	//Para el movimiento
	const int NUM_FRAMES_MOV = 10;
	const int NUM_FRAMES_ROW_MOV = 3;
	const uint W_FRAME_MOV = 200;
	const uint H_FRAME_MOV = 200;
	const int FRAME_RATE_MOV = 100;
	const string NAME_MOV = "walk";
	//Para estar parado
	const int NUM_FRAMES_IDLE = 10;
	const int NUM_FRAMES_ROW_ADLE = 3;
	const uint W_FRAME_IDLE = 200;
	const uint H_FRAME_IDLE = 200;
	const int FRAME_RATE_IDLE = 100;
	const string NAME_IDLE = "idle";
#pragma endregion
	//Estadisticas para inicializar al monkeyCoco
	#pragma region consts
	const int VIS_RANGE = 75;
#pragma endregion

	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Ataque del pirata enemigo
	void attack();
	//Devuelve true si el target est� dentro del rango de ataque
	bool onRange();
	//Inicializa todas las animaciones
	void initAnims();
	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy();
	//Cuando pierde agro del enemigo
	virtual void lostAgro();
	//Genera la posición a la que se mueve el pirata en función de su rango 
	void selectTarget();

	virtual void animationsvar();
	virtual void initialStats();
};