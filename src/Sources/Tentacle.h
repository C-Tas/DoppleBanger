#pragma once

#include "Enemy.h"

class Kraken;

class Tentacle : public Enemy
{
public:
	Tentacle(Application* app, Kraken* kraken, Vector2D pos, Vector2D scale, double rot) : Enemy(app, pos, scale, rot), kraken_(kraken)
		{  initObject(); };
	virtual ~Tentacle() {};

	virtual void onCollider();
	virtual bool update();
	const virtual void draw();
	virtual void receiveDamage(int dmg);

private:
	int spawnTime_ = 0;
	int attackFrames_ = 0;
	//Puntero al kraken padre
	Kraken* kraken_ = nullptr;

	//Area del colisión del tentáculo que se guarda para cuando ya ha caído
	SDL_Rect collArea_;

	Anim spawnAnim_ = { 0,0,0,0,0 ,"" };
	Anim idleAnim_ = { 0,0,0,0,0,"" };
	Anim despawnAnim_ = { 0,0,0,0,0,"" };

	void initObject();
	void initAnims();

#pragma region Constantes
	//Duración del tentáculo
	const int TENTACLE_DURATION = 2;
	//Duración del tentáculo cayendo
	const int ATTACK_DURATION = 1;

	//Tentáculo aparece
	const int NUM_FRAMES_SPAWN = 0;
	const int NUM_FRAMES_ROW_SPAWN = 0;
	const uint W_FRAME_SPAWN = 0;
	const uint H_FRAME_SPAWN = 0;
	const int FRAME_RATE_SPAWN = 0;
	const string NAME_SPAWN = "spawn";
	//Tentáculo idle
	const int NUM_FRAMES_IDLE = 0;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE = 0;
	const string NAME_IDLE = "idle";
	//Tentáculo desaparece
	const int NUM_FRAMES_DESPAWN = 0;
	const int NUM_FRAMES_ROW_DESPAWN = 0;
	const uint W_FRAME_DESPAWN = 0;
	const uint H_FRAME_DESPAWN = 0;
	const int FRAME_RATE_DESPAWN = 0;
	const string NAME_DESPAWN = "despawn";
#pragma endregion
};

