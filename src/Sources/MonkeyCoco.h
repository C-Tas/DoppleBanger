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
	//Último ataque
	Uint32 lastHit = 0;
	//Último frame de animación
	Uint32 lasFrame_ = 0;
	//Diferentes animaciones del mono
	Anim attackAnim_ = { 0,0,0,0,0 ,""};
	Anim walkAnim_ = { 0,0,0,0,0,"" };
	Anim idleAnim_ = { 0,0,0,0,0,"" };
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
	//Proyectil
	const uint W_H_COCO = app_->getWindowHeight() / 40;		//Tamaño del coco
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
	
	//Ataque del monkeyCoco
	void attack();
	//Gestiona las diferentes animaciones que tiene el monkeyCoco
	void changeAnim(Anim& newAnim);
	//Inicializa todas las animaciones
	void initAnims();
	//Actualiza la actual animación
	void updateAnim();
	
	
	
};
