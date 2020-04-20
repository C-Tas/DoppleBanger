#pragma once

#include "Enemy.h"

class Kraken;

enum class ATTACKS { SLAM, SWEEP };

class Tentacle : public Enemy
{
public:
	Tentacle(Application* app, Kraken* kraken, Vector2D pos, Vector2D scale, double rot, ATTACKS attack) : Enemy(app, pos, scale, rot), kraken_(kraken), attack_(attack)
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
	ATTACKS attack_;

	//Velocidad y direcci�n en la que se mueve el tent�culo en sweep
	bool rotating_ = false;
	double deltaAngle_ = 0; //Incremento del �ngulo de rotaci�n
	double speed_ = 500;
	int turns_ = 0; //N�mero de giros
	Vector2D sweepDir_;
	Vector2D centerRot_; //Centro de rotaci�n en relaci�n a las esquinas cuando rotan
	Vector2D initPos_; //Posici�n inicial

	//Area del colisi�n del tent�culo que se guarda para cuando ya ha ca�do
	SDL_Rect collArea_;

	Anim spawnAnim_ = { 0,0,0,0,0 ,"" };
	Anim idleAnim_ = { 0,0,0,0,0,"" };
	Anim despawnAnim_ = { 0,0,0,0,0,"" };

	void initObject();
	void initAnims();
	bool slamUpdate();
	bool sweepUpdate();

#pragma region Constantes
	//Duraci�n del tent�culo
	const int TENTACLE_DURATION = 5;
	//Duraci�n del tent�culo cayendo
	const int ATTACK_DURATION = 1;

	//Tent�culo aparece
	const int NUM_FRAMES_SPAWN = 0;
	const int NUM_FRAMES_ROW_SPAWN = 0;
	const uint W_FRAME_SPAWN = 0;
	const uint H_FRAME_SPAWN = 0;
	const int FRAME_RATE_SPAWN = 0;
	const string NAME_SPAWN = "spawn";
	//Tent�culo idle
	const int NUM_FRAMES_IDLE = 0;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE = 0;
	const string NAME_IDLE = "idle";
	//Tent�culo desaparece
	const int NUM_FRAMES_DESPAWN = 0;
	const int NUM_FRAMES_ROW_DESPAWN = 0;
	const uint W_FRAME_DESPAWN = 0;
	const uint H_FRAME_DESPAWN = 0;
	const int FRAME_RATE_DESPAWN = 0;
	const string NAME_DESPAWN = "despawn";
#pragma endregion
};

