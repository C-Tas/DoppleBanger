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
	Uint32 lastHit = 0;
	//Último frame de animación
	Uint32 lasFrame_ = 0;
	//Diferentes animaciones del esqueleto
	//Anim moveAnim_ = { 0,0,0,0,false };

	//Constantes para crear las animaciones 
	//la animacion aun no esta 
#pragma region Constantes
//Para el ataque
	const int NUM_FRAMES_MOV = 0;
	const int NUM_FRAMES_ROW_MOV = 0;
	const uint W_FRAME_MOV = 0;
	const uint H_FRAME_MOV = 0;
	const int FRAME_RATE_MOV = 0;
	const string NAME_MOV = "move";

	//Hueso que lanza el esqueleto
	const uint BONE_HEIGHT = app_->getWindowHeight() / 40;		//Alto del hueso
	const uint BONE_WIDTH = app_->getWindowWidth() / 36;		//Ancho del hueso
	const double BONE_VEL = 400;							//Velocidad del hueso
	const double BONE_LIFE = 3;							//Vida del proyectil en segundos
	
	int Distance;											//distancia que recorre el hueso a la ida y a la vuelta

	//Entero que representa la cantidad de frames que tiene para las animaciones
	const int NUM_FRAMES = 0;
	//Frame para renderizar dentro de un spritesheet
	const SDL_Rect FIRST_FRAME = { 0,0,0,0 };
	//Ataque del esqueleto
	void attack();
	//Inicializa todas las animaciones
	void initAnims();
	//Actualiza la actual animación
	void updateAnim();
	void initialStats();

#pragma region Anims
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_SKELETON_FRAME = 70;			//Ancho del frame, estándar para todas
	const int H_SKELETON_FRAME = 45;			//Alto del frame, estándar para todas
	const int FRAME_ACTION_SHOOT = 10;
	bool shooted_ = false;
	//Idle
	const int LAUGH_FRAME = 1;
	const int IDLE_FRAME = 6;
	void initIdle();
	vector<Anim> idleAnims_;
	vector<Texture*> idleTx_;
	//Idle derecha
	const int IDLE_R_FRAMES = 16;			//Frames de la animación
	const int IDLE_R_FRAME_RATE = 100;		//Frame rate
	//Idle hacia arriba
	const int IDLE_U_FRAMES = 16;			//Frames de la animación
	const int IDLE_U_FRAME_RATE = 100;		//Frame rate
	//Idle hacia izquierda
	const int IDLE_L_FRAMES = 16;			//Frames de la animación
	const int IDLE_L_FRAME_RATE = 100;		//Frame rate
	//Idle hacia abajo
	const int IDLE_D_FRAMES = 16;			//Frames de la animación
	const int IDLE_D_FRAME_RATE = 100;		//Frame rate
};

