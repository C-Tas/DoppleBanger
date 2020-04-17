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
	//virtual void onCollider();
	virtual ~MonkeyCoco() {};
private:
	//Último ataque
	Uint32 lastHit = 0;
	//Último frame de animación
	//Uint32 lasFrame_ = 0;
	//Diferentes animaciones del mono
	//Anim attackAnim_ = { 0,0,0,0,0 ,""};
	//Anim walkAnim_ = { 0,0,0,0,0,"" };
	//Anim idleAnim_ = { 0,0,0,0,0,"" };
	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animación del mono)
	#pragma region Constantes
	//Para el ataque
	// int NUM_FRAMES_ATK = 10;
	// int NUM_FRAMES_ROW_ATK = 3;
	// uint W_FRAME_ATK = 200;
	// uint H_FRAME_ATK = 200;
	// int FRAME_RATE_ATK = 100;
	// string NAME_ATK = "attack";
	////Para el movimiento
	// int NUM_FRAMES_MOV = 10;
	// int NUM_FRAMES_ROW_MOV = 3;
	// uint W_FRAME_MOV = 200;
	// uint H_FRAME_MOV = 200;
	// int FRAME_RATE_MOV = 100;
	// string NAME_MOV = "walk";
	////Para estar parado
	// int NUM_FRAMES_IDLE = 10;
	// int NUM_FRAMES_ROW_ADLE = 3;
	// uint W_FRAME_IDLE = 200;
	// uint H_FRAME_IDLE = 200;
	// int FRAME_RATE_IDLE = 100;
	// string NAME_IDLE = "idle";
	//Proyectil
	const uint W_H_COCO = app_->getWindowHeight() / 40;		//Tamaño del coco
	const double COCO_VEL = 700;							//Velocidad del coco
	const double COCO_LIFE = 3;								//Vida del proyectil en segundos
	#pragma endregion
	//Estadisticas para inicializar al monkeyCoco
	#pragma region Stats
	  //HEALTH = 100;
	  //MANA = 100;
	  //MANA_REG = 1;
	  //ARMOR = 10;
	  //MELEE_DMG = 0;
	  //DIST_DMG = 100;
	  //CRIT = 0;
	  //MELEE_RANGE = 20;
	  //DIST_RANGE = 250;
	  //MOVE_SPEED = 100;
	  //MELEE_RATE = 1;
	  //DIST_RATE = 2500;
#pragma endregion

	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Ataque del monkeyCoco
	void attack();
	//Gestiona las diferentes animaciones que tiene el monkeyCoco
	//void changeAnim(Anim& newAnim);
	//Devuelve true si el target está dentro del rango de ataque
	bool onRange();
	//Inicializa todas las animaciones
	//void initAnims();
	//Actualiza la actual animación
	//void updateAnim();
	//Cuando pierde el agro
	virtual void lostAgro();
	virtual void animationsvar();
	virtual void initialStats();
};
