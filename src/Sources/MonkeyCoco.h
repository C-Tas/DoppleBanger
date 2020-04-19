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
	virtual ~MonkeyCoco() {};
private:
	//Diferentes animaciones del mono
	Anim attackAnim_ = { 0,0,0,0, false };
	Anim walkAnim_ = { 0,0,0,0, false };
	Anim idleAnim_ = { 0,0,0,0, false };
	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animaci�n del mono)
	#pragma region Constantes
	//Para el ataque
	const int NUM_FRAMES_ATK = 10;
	const int NUM_FRAMES_ROW_ATK = 3;
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
	//Proyectil
	const uint W_H_COCO = app_->getWindowHeight() / 40;		//Tama�o del coco
	const double COCO_VEL = 700;							//Velocidad del coco
	const double COCO_LIFE = 3;								//Vida del proyectil en segundos
	#pragma endregion
	//Estadisticas para inicializar al monkeyCoco
	#pragma region Stats
	const double HEALTH = 100;
	const double MANA = 100;
	const double MANA_REG = 1;
	const double ARMOR = 10;
	const double MELEE_DMG = 0;
	const double DIST_DMG = 100;
	const double CRIT = 0;
	const double MELEE_RANGE = 20;
	const double DIST_RANGE = 250;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 2500;
#pragma endregion

	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Determina si el jugador est� dentro del rango de ataque del monkeyCoco
	Vector2D isPlayerInRange();
	//Determina si el clon est� dentro del rango de ataque del monkeyCoco
	Vector2D isClonInRange();
	//Ataque del monkeyCoco
	void attack();
	//Devuelve true si el target est� dentro del rango de ataque
	bool onRange();
	//Inicializa todas las animaciones
	virtual void initAnims();
	//Busca y actualiza al enemigo que atacar
	bool getEnemy();
	//Cuando pierde el agro
	virtual void lostAgro();
};
