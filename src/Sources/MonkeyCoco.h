#pragma once
#include "Enemy.h"
#include <vector>

class MonkeyCoco :
	public Enemy
{
private:
	//Ataque del monkeyCoco
	void attack();
	//Estadisticas para inicializar al monkeyCoco
	#pragma region consts
	const int HEALTH = 100;
	const int MANA = 100;
	const double MANA_REG = 1;
	const int ARMOR = 10;
	const int AD = 0;
	const int AP = 0;
	const int CRIT = 0;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 5;
#pragma endregion
	//Ancho y alto del sprite a renderizar
	const Vector2D START_SCALE = { 100,100 };
	//Vector que representa el alto y ancho de la caja de colisiones
	const Point2D BOX_COLLISION;
	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Determina si el jugador está dentro del rango de ataque del monkeyCoco
	bool isPlayerInRange();
	//Determina si el clon está dentro del rango de ataque del monkeyCoco
	bool isClonInRange();
	//Objetivo al que ataca
	Draw* target_ = nullptr;
	//Último ataque
	Uint32 lastHit = 0;
	//Gestiona las diferentes animaciones que tiene el monkeyCoco
	void changeAnim();
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	MonkeyCoco(Application* app = nullptr, Vector2D pos = { 0,0 })
		:Enemy(app, pos) {
		initObject();
	};
	//<summary>Constructor por copia</summary>
	MonkeyCoco(MonkeyCoco& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	MonkeyCoco(MonkeyCoco&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };
	
	virtual void initObject();
};
