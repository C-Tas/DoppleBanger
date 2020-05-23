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
	const double SLOW_DURATION = 3000;
	const double SLOW_EFFECT = 0.5;

	bool fallen_ = false;
	Cooldown fallingCD_;
	Cooldown lifeCD_;
	STATE state_;
	Kraken* kraken_ = nullptr;
	//animacion
	Texture* inkTx_;
	const int NUM_FRAMES_IDLE = 9;
	const uint W_FRAME_IDLE = 100;
	const uint H_FRAME_IDLE = 100;
	const int FRAME_RATE_IDLE = 200;

	//animacion
	Anim inkanim_ = { 0,0,0,0,false };

	bool update();
	virtual void initAnims();
	void initInk();
	void initObject();
	void onCollider();
	void updateCooldowns() {
		if (fallingCD_.isCooldownActive()) fallingCD_.updateCooldown();
		if (lifeCD_.isCooldownActive()) lifeCD_.updateCooldown();

	};
	bool falling = true;
};

