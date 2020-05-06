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
	virtual void onCollider() {};
	virtual void initRewards();
	//Cuando pierde agro del enemigo
	virtual void lostAggro() { currEnemy_ = nullptr; };

	virtual ~MonkeyCoco() {};

private:
	//Ataque del monkeyCoco
	void attack();
	//Inicializa las animaciones
	void initAnims();
	virtual void initialStats();

	//Calcula hacia dónde mira el mono en función del player (se redefine porque las vistas del mono son distintas que las del resto de enemigos)
	virtual void updateDirVisObjective(GameObject* objective);

#pragma region Animaciones
	//Inicia la animación
	void initIdle();
	void initShoot();

	//Controla la animación
	void shootAnim();

	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_H_MONKEY_FRAME = 100;		//Ancho del frame, estándar para todas
	bool firstAttack = true;
	bool firstIdle = true;

	//Idle
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha abajo
	const int IDLE_R_D_FRAMES = 9;			//Frames de la animación
	const int IDLE_R_D_FRAME_RATE = 200;	//Frame rate
	//Idle hacia derecha arriba
	const int IDLE_R_U_FRAMES = 9;			//Frames de la animación
	const int IDLE_R_U_FRAME_RATE = 200;	//Frame rate
	//Idle hacia izquierda abajo
	const int IDLE_L_D_FRAMES = 9;			//Frames de la animación
	const int IDLE_L_D_FRAME_RATE = 200;	//Frame rate
	//Idle hacia izquierda arriba
	const int IDLE_L_U_FRAMES = 9;			//Frames de la animación
	const int IDLE_L_U_FRAME_RATE = 200;	//Frame rate

	//Disparo
	bool shooted_ = false;					//Para disparar una sola vez en el frame adecuado
	vector<Anim> shootAnims_;				//Vector de las animaciones
	vector<Texture*> shootTx_;				//Vector de las texturas
	//Disparo derecha abajo
	const int SHOOT_R_D_FRAMES = 10;		//Frames de la animación
	const int SHOOT_R_D_FRAME_RATE = 100;	//Frame rate
	//Disparo hacia derecha arriba
	const int SHOOT_R_U_FRAMES = 13;		//Frames de la animación
	const int SHOOT_R_U_FRAME_RATE = 77;	//Frame rate
	//Disparo hacia izquierda abajo
	const int SHOOT_L_D_FRAMES = 11;		//Frames de la animación
	const int SHOOT_L_D_FRAME_RATE = 91;	//Frame rate
	//Disparo hacia izquierda arriba
	const int SHOOT_L_U_FRAMES = 13;		//Frames de la animación
	const int SHOOT_L_U_FRAME_RATE = 77;	//Frame rate

	//Proyectil
	const uint W_H_COCO = app_->getWindowHeight() / 40;		//Tama�o del coco
	const double COCO_VEL = 700;							//Velocidad del coco
	const double COCO_LIFE = 3;								//Vida del proyectil en segundos
#pragma endregion
};
