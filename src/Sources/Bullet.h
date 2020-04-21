#pragma once

#include "Dynamic.h"
#include "GameState.h"
#include <list>
class Enemy;

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }) :
		Dynamic(app, pos, scale), damage_(damage), lifeSpan_(lifeSpan) {
		texture_ = texture;
		speed_ = speed;
		collisionArea_ = { (int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY() };
		initObject(pos, dir);
	};
	~Bullet() {};

	void initObject(Vector2D pos, Vector2D dir);
	bool update();
	void onCollider() {
		if (!deleting) {
			deleting = true;
			app_->getCurrState()->removeRenderUpdateLists(this);
		}; 
	}
	const int getDamage() { return damage_; };

protected:
	double lifeSpan_ = 0; //Tiempo máximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	int damage_ = 0;
	bool enemyBullet_ = false;
	bool deleting = false;

	virtual void initObject() {};
};