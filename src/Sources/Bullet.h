#pragma once

#include "Dynamic.h"
#include "GameState.h"
#include <list>
class Enemy;

class Bullet : public Dynamic
{
public:
	Bullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, double damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, int col = 1) :
		Dynamic(app, pos, scale), damage_(damage), lifeSpan_(lifeSpan), collisionsBeforeDestroy_(col) {
		texture_ = texture;
		speed_ = speed;
		collisionArea_ = { (int)pos.getX(), (int)pos.getY(), (int)scale.getX(), (int)scale.getY() };
		initObject(pos, dir);
	};
	virtual ~Bullet() {};

	void initObject(Vector2D pos, Vector2D dir);
	virtual bool update();
	virtual void onCollider() {
			if (!deleting) {
				deleting = true;
				app_->getCurrState()->removeRenderUpdateLists(this);
			};

	}
	const double getDamage() { return damage_; }
	void collisionDetected() { collisionsBeforeDestroy_--; }
	int numCollisions() { return collisionsBeforeDestroy_; }
	void setDoDamage(bool dmg) { MakeDamage = dmg; }
	bool doDamage() { return MakeDamage; }


protected:
	double lifeSpan_ = 0; //Tiempo m�ximo que dura la bala
	double initTime_ = 0; //Ticks cuando se creo la bala
	double currTime_ = 0; //Ticks en cada update
	double speed_ = 0;
	double damage_ = 0;
	bool enemyBullet_ = false;
	bool deleting = false;
	uint collisionsBeforeDestroy_ = 1;//Variable para aquellas balas que chac mas de una vez antes destruirse
	bool MakeDamage = true; //variable para comprobar si tiene que atacar al jugador

	virtual void initObject() {};
};