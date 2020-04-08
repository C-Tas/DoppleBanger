#pragma once

#include "Dynamic.h"
#include "GameState.h"

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, int collisions = 1) :
		Dynamic(app, pos, scale), damage_(damage), lifeSpan_(lifeSpan), speed_(speed), collisionsBeforeDestroy_(collisions) {
		texture_ = texture;
		collisionArea_ = { (int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY() };
		init(pos, dir);
	};
	virtual ~Bullet() {};

	void init(Vector2D pos, Vector2D dir);
	virtual bool update();
	void onCollider() {
		if (collisionsBeforeDestroy_ == 0) {
			if (!deleting) {
				deleting = true;
				app_->getCurrState()->removeRenderUpdateLists(this);
			};
		}

	}
	const int getDamage() { return damage_; }
	void collisionDetected() { collisionsBeforeDestroy_--; }
	int numCollisions() { return collisionsBeforeDestroy_; }


protected:
	double lifeSpan_ = 0; //Tiempo máximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	int damage_ = 0;
	bool enemyBullet_ = false;
	bool deleting = false;
	uint collisionsBeforeDestroy_ = 1;//Variable para aquellas balas que chac mas de una vez antes destruirse

	virtual void initObject() {};
};