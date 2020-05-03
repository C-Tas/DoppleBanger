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
	//virtual void onCollider();
	virtual ~Skeleton() {};
private:
	//Último ataque
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

	virtual void initialStats();
};

