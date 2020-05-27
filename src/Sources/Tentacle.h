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
	Cooldown lifeCD_;
	Cooldown fallingCD_;
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

	//Anim spawnAnim_ = { 0,0,0,0, false };
	///*Anim idleAnim_ = { 0,0,0,0, false };*/
	//Anim despawnAnim_ = { 0,0,0,0, false };
	/*bool animation = true;
	void initSpawnAnim();
	void initDespawnAnim();
	void initSweep();*/


	void initObject();
	void initDie() {};
	bool slamUpdate();
	bool sweepUpdate();
	virtual void initialStats() {};	
	virtual void initRewards() {};
	virtual void updateCooldowns();

#pragma region Constantes
	//Duraci�n del tent�culo
	const int TENTACLE_DURATION = 4000;
	const int FALL_DURATION = 1000;

	//Tent�culo aparece
	/*Texture* spawnTX_;
	const int NUM_FRAMES_SPAWN = 16;
	const uint W_FRAME_SPAWN = 114;
	const uint H_FRAME_SPAWN = 85;
	const int FRAME_RATE_SPAWN = 200;*/


	//Tent�culo desaparece
	/*Texture* despawnTX_;
	const int NUM_FRAMES_DESPAWN = 16;
	const uint W_FRAME_DESPAWN = 114;
	const uint H_FRAME_DESPAWN = 85;
	const int FRAME_RATE_DESPAWN = 200;*/
#pragma endregion
};