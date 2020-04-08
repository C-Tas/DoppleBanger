#pragma once
#include "Bullet.h"
class BoneBullet: public Bullet
{
public:
	BoneBullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, int collisions = 2) :
		Bullet(app, texture, pos, dir, damage, lifeSpan, speed, scale, collisions){};

	virtual void onCollider() {
		if (collisionsBeforeDestroy_ == 0) {
			if (!deleting) {
				deleting = true;
				app_->getCurrState()->removeRenderUpdateLists(this);
			};
		}
		else {
			//hacemos que pase al jugador
			//Hay que ajustar el valor de separacion en funcion de el tamaño del hueso y del player, cuando estos sean definitivos
			pos_.setX(pos_.getX() + (dir_.getX() * 80 ));
			pos_.setY(pos_.getY() + (dir_.getY() * 80));
		}

	}

	bool update()override;
	virtual ~BoneBullet() {};
	bool returnBone = false;
};

