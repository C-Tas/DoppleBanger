#pragma once

#include "Dynamic.h"
#include "GameState.h"

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage, double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, bool enemyBullet = false) :
		Dynamic(app, pos, scale), damage_(damage), lifeSpan_(lifeSpan), speed_(speed), enemyBullet_(enemyBullet) {
		texture_ = texture;
		collisionArea_ = { (int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY() };
		init(pos, dir);
	};
	~Bullet() {};

	void init(Vector2D pos, Vector2D dir);
	bool update();
	void onCollider() { app_->getCurrState()->removeRenderUpdateLists(this); }; //Cuando colisiona elimina la bala
	const int getDamage() { return damage_; }

private:
	double lifeSpan_ = 0; //Tiempo máximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	int damage_ = 0;
	bool enemyBullet_ = false;

	virtual void initObject() {};
};