#pragma once

#include "Collider.h"
#include "GameManager.h"

class Ink : public Collider
{
public:
	Ink(Application* app, Point2D pos, Vector2D scale) : Collider(app, pos, scale) { initObject(); };
	~Ink() {};

private:
	const double INK_DURATION = 4;
	const double SLOW_DURATION = 2;
	const double SLOW_EFFECT = 0.5;

	double spawnTime_ = 0;

	bool update();
	void initObject();
	void onCollider();
};

