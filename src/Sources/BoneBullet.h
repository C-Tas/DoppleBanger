#pragma once
#include "Bullet.h"
class BoneBullet: public Bullet
{
public:
	BoneBullet(Application* app, Texture* texture, Vector2D pos, Vector2D dir, int damage,
		double lifeSpan = 2, double speed = 1000, Vector2D scale = { 20, 20 }, int collisions = 2) :
		Bullet(app, texture, pos, dir, damage, lifeSpan, speed, scale, collisions){};

	bool update()override;
	virtual ~BoneBullet() {};
	bool returnBone = false;
};

