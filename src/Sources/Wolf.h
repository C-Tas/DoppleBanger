#pragma once
#include "Enemy.h"
class Wolf :
	public Enemy
{
public:
	Wolf(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 },
		vector<Point2D> patrol = { {0,0} }) :
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

	virtual  ~Wolf() {};

private:
	//Puntos del mapa donde va a patrullar
	vector<Point2D> patrol_;
	//Punto que representa dentro del vector de patrulla
	int currTarget_ = 0;
	//Último ataque a melee
	Uint32 lastMeleeHit_ = 0;
	//Tiempo que el lobo pasa parado cuando llega a un target
	Uint32 idleTime_ = 1000;
	//Tiempo 
	uint lastIdleTime = 0;
	//Diferentes animaciones del lobo
	Anim attackAnim_ = { 0,0,0,0, false };
	Anim walkAnim_ = { 0,0,0,0, false};
	Anim idleAnim_ = { 0,0,0,0, false };
	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animación del mono)
	#pragma region Constantes
	//Para el ataque
	const int NUM_FRAMES_ATK = 10;
	const int W_FRAME_ATK = 200;
	const int H_FRAME_ATK = 200;
	const int FRAME_RATE_ATK = 100;
	//Para el movimiento
	const int NUM_FRAMES_MOV = 10;
	const int W_FRAME_MOV = 200;
	const int H_FRAME_MOV = 200;
	const int FRAME_RATE_MOV = 100;
	//Para estar parado
	const int NUM_FRAMES_IDLE = 10;
	const int W_FRAME_IDLE = 200;
	const int H_FRAME_IDLE = 200;
	const int FRAME_RATE_IDLE = 100;
	#pragma endregion

	//Ataque del monkeyCoco
	void attack();
	//Devuelve true si el target est� dentro del rango de ataque
	bool onRange();
	//Inicializa todas las animaciones
	void initAnims();
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