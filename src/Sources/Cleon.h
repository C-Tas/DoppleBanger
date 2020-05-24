#pragma once
#include "Enemy.h"


class Player;

class Cleon : public Enemy { 
public: 

	//constructora y destructora
	Cleon(Application* app = nullptr, Point2D pos = { 0, 0 }, Vector2D scale = { 0, 0 }) :
		Enemy(app, pos, scale) {
		initObject();
	};
	~Cleon() {};

	//Métodos virtuales públicos
	virtual bool update() override ;
	virtual void onCollider()override;
	virtual void receiveDamage(double damage) override;
	virtual void lostAggro();

	//Habilidades
		//*Bloqueo
			//Posibilidad de bloquear un ataque
	const int BLOCK_CHANCE = 5;
			//Devuelve true si activa el bloqueo
	bool activeBlock() { return app_->getRandom()->nextInt(0, BLOCK_CHANCE + 1) == BLOCK_CHANCE ? true : false; }
		
		//*Estocada
			//última estocada
	Cooldown lastThrust_;
			//Cooldown de la estocada
	const double THRUST_TIME = 2500;
			//Método que se encarga de crear la estocada
	void thrust();

		//*Carga
			//Rango en que aplica la carga del pirata
	const double CHARGE_RANGE = 200;
			//Úlima carga
	Cooldown lastCharge_;
			//Método que crea la carga del pirata
	void pirateCharge();
			//Cooldown de la carga
	const double CHARGE_TIME = 20000;
			//Velocidad con la que carga Cleón
	const double CHARGE_SPEED = 1000;
			//Velocidad de movimiento de Cleón para recuperar luego
	double movSpeed_ = 0;
			//Daño que produce la carga
	const int CHARGE_DMG = 300;
	//Fin habilidades//

private:
	//Métodos virtuales privados
	virtual void initialStats()override;
	virtual void initObject()override;
	virtual void initRewards()override;
	virtual void initAnims()override;
	virtual void updateCooldowns() override;
	virtual void move(Point2D target);
	virtual void initRun();
	virtual void initAssault() {};
	virtual void initMelee();
	virtual void initBarrel();
	virtual void initIdle();
	void initCharge();
	void selectTarget();
	//Punteros
	Player* player_ = nullptr;

	//Animaciones de Cleon
	vector<Anim> idleAnim_;
	vector<Anim> runAnim_;
	vector<Anim> assaultAnim_;
	vector<Anim> meleeAnim_;
	vector<Anim> barrelAnim_;
	vector<Texture*> idleTxt_;
	vector<Texture*> runTxt_;
	vector<Texture*> assaultTxt_;
	vector<Texture*> meleeTxt_;
	vector<Texture*> barrelTxt_;
#pragma region Constantes
	//Animacion idle de Cleon
	const int NUM_FRAMES_IDLE = 2;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 100;
	const uint H_FRAME_IDLE = 100;
	const int FRAME_RATE_IDLE = 20;

	//Animacion correr
	const int NUM_FRAMES_RUN_UD = 4;
	const int NUM_FRAMES_ROW_RUN_UD = 0;
	const uint W_FRAME_RUN_UD = 100;
	const uint H_FRAME_RUN_UD = 100;
	const int FRAME_RATE_RUN_UD = 30;
	
	const int NUM_FRAMES_RUN_RL = 7;
	const int NUM_FRAMES_ROW_RUN_RL = 0;
	const uint W_FRAME_RUN_RL = 100;
	const uint H_FRAME_RUN_RL = 100;
	const int FRAME_RATE_RUN_RL = 60;
	//Animacion embestida
	const int NUM_FRAMES_ASSAULT = 0;
	const int NUM_FRAMES_ROW_ASSAULT = 0;
	const uint W_FRAME_ASSAULT = 0;
	const uint H_FRAME_ASSAULT = 0;
	const int FRAME_RATE_ASSAULT = 0;

	//Animacion cuerpo a cuerpo
	const int NUM_FRAMES_MELEE_UD = 7;
	const int NUM_FRAMES_ROW_MELEE_UD = 0;
	const uint W_FRAME_MELEE_UD = 100;
	const uint H_FRAME_MELEE_UD = 100;
	const int FRAME_RATE_MELEE_UD = 30;

	const int NUM_FRAMES_MELEE_RL = 9;
	const int NUM_FRAMES_ROW_MELEE_RL = 0;
	const uint W_FRAME_MELEE_RL = 100;
	const uint H_FRAME_MELEE_RL = 100;
	const int FRAME_RATE_MELEE_RL = 40;
	//Animacion embestida
	const int NUM_FRAMES_BARREL = 0;
	const int NUM_FRAMES_ROW_BARREL = 0;
	const uint W_FRAME_BARREL = 0;
	const uint H_FRAME_BARREL = 0;
	const int FRAME_RATE_BARREL = 0;
#pragma endregion
};

