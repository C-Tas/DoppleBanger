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
	const double CHARGE_RANGE = 500;
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
	void swept();
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
	virtual void initThrust();
	virtual void initIdle();
	void initSwept();
	void initCharge();
	void initMove();

	//gestores de las animaciones
	void thrustAnim();
	void sweptAnim();

	void selectTarget();
	//Punteros
	Player* player_ = nullptr;

	//Animaciones de Cleon
	vector<Anim> idleAnim_;
	vector<Anim> runAnim_;
	vector<Anim> meleeAnim_;
	vector<Anim> chargeAnim_;
	vector<Anim> sweptAnim_;
	vector<Texture*> idleTxt_;
	vector<Texture*> runTxt_;
	vector<Texture*> meleeTxt_;
	vector<Texture*> chargeTxt_;
	vector<Texture*> sweptTxt_;

	bool attacked_ = false;

#pragma region Constantes
	//Frame en el cual vamos a atacar
	int frameAction_ = 0;
	//Constantes de ancho y alto de los frames
	const uint W_FRAME_CLEON = 100;
	const uint H_FRAME_CLEON = W_FRAME_CLEON;

	//Animacion idle de Cleon
	const int NUM_FRAMES_IDLE = 2;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const int FRAME_RATE_IDLE = 500;

	//Animacion correr
	const int NUM_FRAMES_RUN_UD = 4;
	const int NUM_FRAMES_ROW_RUN_UD = 0;
	const int FRAME_RATE_RUN_UD = 30;
	
	const int NUM_FRAMES_RUN_RL = 7;
	const int NUM_FRAMES_ROW_RUN_RL = 0;
	const int FRAME_RATE_RUN_RL = 60;

	//Animacion cuerpo a cuerpo
	const int NUM_FRAMES_MELEE_UD = 7;
	const int FRAME_RATE_MELEE_UD = 30;

	const int NUM_FRAMES_MELEE_RL = 9;
	const int FRAME_RATE_MELEE_RL = 40;

	//Animacion carga
	//arriba/abajo
	const int NUM_FRAMES_CHARGE_UD = 9;
	const int FRAME_RATE_CHARGE_UD = 120;
	//izquierda/dcha
	const int NUM_FRAMES_CHARGE_RL = 4;
	const int FRAME_RATE_CHARGE_RL = 80;

	//Animacion barrido
	//arriba
	const int NUM_FRAMES_SWEPT_UP = 5;
	const int FRAME_RATE_SWEPT_UP = 60;
	//abajo
	const int NUM_FRAMES_SWEPT_DOWN = 6;
	const int FRAME_RATE_SWEPT_DOWN = 50;
	//izquierda/dcha
	const int NUM_FRAMES_SWEPT_RL = 4;
	const int FRAME_RATE_SWEPT_RL = 40;

	
#pragma endregion
};

