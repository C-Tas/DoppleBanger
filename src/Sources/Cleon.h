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

	//Métodos virtuales públicos
	virtual bool update() override ;
	virtual void onCollider()override;
	virtual void receiveDamage(int damage) override;
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
			//Método que se encarga de crear la estocada
	void thrust();
			//última estocada
	Cooldown lastThrust_;
			//Cooldown de la estocada
	const double THRUST_TIME = 2500;

		//*Carga
			//Rango en que aplica la carga del pirata
	const double CHARGE_RANGE = 200;
			//Úlima carga
	Cooldown lastCharge_;
			//Cooldown de la carga
	const double CHARGE_TIME = 2000;
			//Velocidad con la que carga Cleón
	const double CHARGE_SPEED = 1000;
			//Velocidad de movimiento de Cleón para recuperar luego
	double movSpeed_ = 0;
			//Daño que produce la carga
	const int CHARGE_DMG = 300;
			//Método que crea la carga del pirata
	void pirateCharge();
	
		//* Barrido
	void sweep();
		//Úlimo barrido
	Cooldown lastSweep_;
		//Cooldown del barrido
	const double SWEEP_TIME = 3000;

		//*Barril
			//Número máximo de barriles a crear
	const int NUM_MAX_BARREL = 10;
			//Posibilidad de crear un barril
	const int BARREL_CHANCE = 100;
			//Anchura del barril
	const double BARREL_W = 50;
			//Altura del barril
	const double BARREL_H = 50;
			//Barriles creados
	int barrelsInGame = 0;
			//Método que crea un barril
	void createBarrel();
	//Fin habilidades//


	//Métodos virtuales privados
	virtual void initialStats()override;
	virtual void initObject()override;
	virtual void initRewards()override;
	virtual void initAnims()override;
	virtual void updateCooldowns() override;
	virtual void move(Point2D target);

	void selectTarget();
	//Punteros
	Player* player_ = nullptr;

	//Animaciones de Cleon
	Anim idleAnim_ = { 0,0,0,0,"" };
	Anim runAnim_ = { 0,0,0,0, "" };
	Anim assaultAnim_ = { 0,0,0,0,"" };
	Anim meleeAnim_ = { 0,0,0,0, "" };
	Anim barrelAnim_ = { 0,0,0,0, "" };

#pragma region Constantes
	//Animacion idle de Cleon
	const int NUM_FRAMES_IDLE = 0;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE = 0;

	//Animacion correr
	const int NUM_FRAMES_RUN = 0;
	const int NUM_FRAMES_ROW_RUN = 0;
	const uint W_FRAME_RUN = 0;
	const uint H_FRAME_RUN = 0;
	const int FRAME_RATE_RUN = 0;

	//Animacion embestida
	const int NUM_FRAMES_ASSAULT = 0;
	const int NUM_FRAMES_ROW_ASSAULT = 0;
	const uint W_FRAME_ASSAULT = 0;
	const uint H_FRAME_ASSAULT = 0;
	const int FRAME_RATE_ASSAULT = 0;

	//Animacion cuerpo a cuerpo
	const int NUM_FRAMES_MELEE = 0;
	const int NUM_FRAMES_ROW_MELEE = 0;
	const uint W_FRAME_MELEE = 0;
	const uint H_FRAME_MELEE = 0;
	const int FRAME_RATE_MELEE = 0;

	//Animacion embestida
	const int NUM_FRAMES_BARREL = 0;
	const int NUM_FRAMES_ROW_BARREL = 0;
	const uint W_FRAME_BARREL = 0;
	const uint H_FRAME_BARREL = 0;
	const int FRAME_RATE_BARREL = 0;
#pragma endregion
};

