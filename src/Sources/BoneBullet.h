#pragma once
#include "Bullet.h"
class BoneBullet: public Bullet
{
public:
	BoneBullet(Application* app, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, int collisions = 2) :
		Bullet(app, nullptr, pos, dir, damage, lifeSpan, speed, scale, collisions) {initObject();};

	bool update()override;
	virtual ~BoneBullet() {};
	
private:
	bool returnBone = false;
	//ANIM
	int frameAction_ = 0;					//Frame en el que se realiza la acción
	const int W_BONE_FRAME = 15;			//Ancho del frame, estándar para todas
	const int H_BONE_FRAME = 15;			//Alto del frame, estándar para todas

	//Idle
	const int BONE_FRAME = 6;
	//Idle derecha
	const int BONE_FRAMES = 8;			//Frames de la animación
	const int BONE_FRAME_RATE = 75;		//Frame rate
	virtual void initObject();
};

