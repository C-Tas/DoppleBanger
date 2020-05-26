#pragma once
#include "Enemy.h"
#include "Barrel.h"


class Player;

class Cleon : public Enemy { 
public: 

	//constructora y destructora
	Cleon(Application* app = nullptr, Point2D pos = { 0, 0 }, Vector2D scale = { 0, 0 }) :
		Enemy(app, pos, scale) {
		initObject();
	};
	~Cleon() {};

	//M�todos virtuales p�blicos
	virtual bool update() override ;
	virtual void onCollider()override;
	virtual void receiveDamage(double damage) override;
	virtual void lostAggro();

	//Habilidades
		//*Barril
			//Quita un barril de la cuenta de barriles totales
	void quitBarrel() { barrelsInGame--; }
	//Fin habilidades//

private:
	//Habilidades
		//*Bloqueo
			//Posibilidad de bloquear un ataque 1 entre BLOCK_CHANCE
	const int BLOCK_CHANCE = 5;
			//Devuelve true si activa el bloqueo
	bool activeBlock() { return app_->getRandom()->nextInt(0, BLOCK_CHANCE + 1) == BLOCK_CHANCE ? true : false; }
		
		//*Estocada
			//M�todo que se encarga de crear la estocada
	void thrust();
			//�ltima estocada
	Cooldown lastThrust_;
			//Cooldown de la estocada
	const double THRUST_TIME = 2500;

		//*Carga
			//Rango en que aplica la carga del pirata
	const double CHARGE_RANGE = 350;
			//�lima carga
	Cooldown lastCharge_;
			//Cooldown de la carga
	const double CHARGE_TIME = 5000;
			//Velocidad con la que carga Cle�n
	const double CHARGE_SPEED = 3000;
			//Velocidad de movimiento de Cle�n para recuperar luego
	double movSpeed_ = 0;
			//Da�o que produce la carga
	const int CHARGE_DMG = 300;
			//M�todo que crea la carga del pirata
	void pirateCharge();
	
		//* Barrido
	void sweep();
		//�limo barrido
	Cooldown lastSweep_;
		//Cooldown del barrido
	const double SWEEP_TIME = 3000;

		//*Barril
			//Cooldown del barril
	Cooldown lastBarrel_;
			//N�mero m�ximo de barriles a crear
	const int NUM_MAX_BARREL = 10;
			//Posibilidad de crear un barril
	const int BARREL_CHANCE = 100;
			//Anchura del barril
	const double BARREL_W = 100;
			//Altura del barril
	const double BARREL_H = 100;
			//Barriles creados
	int barrelsInGame = 0;
			//Tiempo de creaci�n de barril
	const double BARREL_CREATOR = 6500;
			//M�todo que crea un barril
	void createBarrel();

		//*Combo
	void combo();
	//Fin habilidades//


	//M�todos virtuales privados
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

