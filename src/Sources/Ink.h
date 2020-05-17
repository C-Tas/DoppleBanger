#pragma once

#include "Collider.h"
#include "GameManager.h"

class Kraken;

class Ink : public Collider
{
public:
	Ink(Application* app, Kraken* kraken, Point2D pos, Vector2D scale) : Collider(app, pos, scale), kraken_(kraken) { initObject(); };
	~Ink() {};

private:
	const double INK_DURATION = 4000;	//En milisegundos
	const double FALL_DURATION = 1000;
	const double SLOW_DURATION = 2;
	const double SLOW_EFFECT = 0.5;

	bool fallen_ = false;
	Cooldown lifeCD_;
	STATE state_;
	Kraken* kraken_ = nullptr;

	bool update();
	void initObject();
	void onCollider();
};

