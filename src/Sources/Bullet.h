#pragma once

#include "Dynamic.h"
#include "GameState.h"

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage, double lifeSpan = 2, double speed = 100, Vector2D scale = { 20, 20 }) :
		Dynamic(app, texture, pos, scale, {(int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY()}), damage_(damage), lifeSpan_(lifeSpan), speed_(speed) {
		init(pos, dir);
	};
	~Bullet() {};

	void init(Vector2D pos, Vector2D dir);
	bool update();
	void onCollider() {};

private:
	double lifeSpan_ = 0; //Tiempo máximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	int damage_ = 0;
};