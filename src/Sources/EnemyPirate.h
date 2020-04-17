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
	EnemyPirate(EnemyPirate& other):Enemy(other.app_,other.pos_,other.scale_) { initObject(); };
	EnemyPirate(EnemyPirate&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initObject(); };

	virtual bool update();
	virtual void initObject();
	virtual void onCollider();
	virtual void move(Vector2D pos);
	virtual  ~EnemyPirate() {};

private:
	//Puntos del mapa donde va a patrullar
	vector<Point2D> patrol_;
	//Punto que representa dentro del vector de patrulla
	int currPatrol_ = 0;
	//Enum que representa los diferentes estados de ataque del pirata
	enum class ATK_STATUS
	{
		MELEE,RANGE
	};
	//Estado de ataque actual del pirata
	ATK_STATUS currAtackStatus_ = ATK_STATUS::RANGE;
	//Último ataque a distancia
	Uint32 lastRangeHit_ = 0;
	//Último ataque a melee
	Uint32 lastMeleeHit_ = 0;
	//Último frame de animación
	//Uint32 lastFrame_ = 0;
	//Tiempo que el pirata pasa parado cuando llega a un target
	Uint32 idleTime_ = 1000;
	//Tiempo 
	uint lastIdleTime = 0;
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
	//Devuelve true si el target está dentro del rango de ataque
	bool onRange();
	//Busca y actualiza al enemigo que atacar
	virtual bool getEnemy();
	//Cuando pierde agro del enemigo
	virtual void lostAgro();
	//Genera la posición a la que se mueve el pirata en función de su rango 
	void selectTarget();

	virtual void animationsvar();
	virtual void initialStats();
};

