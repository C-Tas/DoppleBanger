#pragma once
#include "Enemy.h"
#include <vector>

class MonkeyCoco : public Enemy
{
public:
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	MonkeyCoco(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 })
		:Enemy(app, pos, scale) {
		initObject();
	};
	//<summary>Constructor por copia</summary>
	MonkeyCoco(MonkeyCoco& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	MonkeyCoco(MonkeyCoco&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };

	virtual bool update();
	virtual void initObject();
	virtual void onCollider();
	virtual void initRewards();
	//Cuando pierde agro del enemigo
	virtual void lostAggro() { currEnemy_ = nullptr; };

	virtual ~MonkeyCoco() {};
private:
	//Diferentes animaciones del mono
	Anim attackAnim_ = { 0,0,0,0, false};
	Anim walkAnim_ = { 0,0,0,0, true};
	Anim idleAnim_ = { 0,0,0,0, true};


	//Ataque del monkeyCoco
	void attack();
	//Inicializa las animaciones
	void initAnims();
	virtual void initialStats();

	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animaci�n del mono)
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
	//Proyectil
	const uint W_H_COCO = app_->getWindowHeight() / 40;		//Tama�o del coco
	const double COCO_VEL = 700;							//Velocidad del coco
	const double COCO_LIFE = 3;								//Vida del proyectil en segundos
#pragma endregion
#pragma endregion
};
