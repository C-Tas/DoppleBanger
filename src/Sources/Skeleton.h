#pragma once
#include "Enemy.h"
#include <vector>

class Skeleton: public Enemy
{
public:
	
	Skeleton(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 })
		:Enemy(app, pos, scale) {
		initObject();
	};
	virtual bool update();
	virtual void initRewards();
	virtual void initObject();
	virtual void lostAggro();
	//virtual void onCollider();
	virtual ~Skeleton() {};
protected:
	//�ltimo ataque
	Cooldown shootCD_;

	//Diferentes animaciones del esqueleto
	//Anim moveAnim_ = { 0,0,0,0,false };

	//Constantes para crear las animaciones 
	//la animacion aun no esta 
#pragma region Constantes
//Para el ataque
	const int NUM_FRAMES_MOV = 0;
	const int NUM_FRAMES_ROW_MOV = 0;
	const double W_FRAME_MOV = 0;
	const double H_FRAME_MOV = 0;
	const int FRAME_RATE_MOV = 0;
	const string NAME_MOV = "move";

	//Hueso que lanza el esqueleto
	const uint BONE_HEIGHT = app_->getWindowHeight() / 30;		//Alto del hueso
	const uint BONE_WIDTH = app_->getWindowWidth() / 30;		//Ancho del hueso
	const double BONE_VEL = 400;								//Velocidad del hueso
	const double BONE_LIFE = 3000;								//Vida del proyectil en milisegundos
	
	int Distance;											//distancia que recorre el hueso a la ida y a la vuelta

	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Ataque del esqueleto
	void attack();
	bool firstAttack = true;
	//Inicializa todas las animaciones
	void initAnims();
	void shootAnim();
	//Inicializa los stats
	void initialStats();
	//Actualiza los cooldowns
	virtual void updateCooldowns();


#pragma region Anims
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_SKELETON_FRAME = 100;			//Ancho del frame, estándar para todas
	const int H_SKELETON_FRAME = 100;			//Alto del frame, estándar para todas
	const int FRAME_ACTION_SHOOT = 10;

	//Idle
	const int IDLE_FRAME = 6;
	void initIdle();
	Anim idleAnims_ = { 0, 0, 0, 0, false };
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_FRAMES = 4;			//Frames de la animación
	const int IDLE_FRAME_RATE = 250;		//Frame rate

	//Disparo
	void initShoot();
	bool shooted_ = false;					//Para disparar una sola vez en el frame adecuado
	vector<Anim> shootAnims_;				//Vector de las animaciones
	vector<Texture*> shootTx_;				//Vector de las texturas
	//Disparo derecha abajo
	const int SHOOT_D_FRAMES = 20;		//Frames de la animación
	const int SHOOT_D_FRAME_RATE = 50;	//Frame rate
	//Disparo hacia derecha arriba
	const int SHOOT_U_FRAMES = 14;		//Frames de la animación
	const int SHOOT_U_FRAME_RATE = 75;	//Frame rate
	//Disparo hacia izquierda y derecha
	const int SHOOT_RL_FRAMES = 13;		//Frames de la animación
	const int SHOOT_RL_FRAME_RATE = 70;	//Frame rate
	//Movimiento
	void initMove();
	vector<Anim> moveAnims_;
	vector<Texture*> moveTx_;
	//Movimiento arriba y abajo
	const int MOVE_UD_FRAMES = 8;			//Frames de las animaciones
	const int MOVE_UD_FRAME_RATE = 500;		//Frame rate
	//Movimiento derecha e izquierda
	const int MOVE_RL_FRAMES = 16;          //Frames de las animaciones
	const int MOVE_RL_FRAMES_RATE = 1000;		//Frame rate de las animaciones
};

