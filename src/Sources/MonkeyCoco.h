#pragma once
#include "Enemy.h"
#include <vector>

class MonkeyCoco : public Enemy
{
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	MonkeyCoco(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 })
		:Enemy(app, pos, scale) {
		initObject();
	};
	//<summary>Constructor por copia</summary>
	MonkeyCoco(MonkeyCoco& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	MonkeyCoco(MonkeyCoco&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };


	virtual void initObject();
	virtual void onCollider();
	virtual void die() { currState_ = STATE::DYING; };
private:
	//Último ataque
	Uint32 lastHit = 0;
	//Estadisticas para inicializar al monkeyCoco
	#pragma region consts
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
	const double DIST_RATE = 1500;
#pragma endregion
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
	//Ataque del monkeyCoco
	void attack();
	//Gestiona las diferentes animaciones que tiene el monkeyCoco
	void changeAnim(Anim& newAnim);
	//Devuelve true si el target está dentro del rango de ataque
	bool onRange();
};
