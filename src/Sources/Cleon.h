#pragma once
#include "Enemy.h"


class Cleon : public Enemy { 
public: 

	//constructora y destructora
	Cleon(Application* app = nullptr, Point2D pos = { 0, 0 }, Vector2D scale = { 0, 0 }) :
		Enemy(app, pos, scale) {
		initObject();
	};
	~Cleon() {};

	virtual bool update();
	virtual void onCollider() {};

private:
	//Estadisticas de Cleon
#pragma region Stats
	const double HEALTH = 0;
	const double MANA = 0;
	const double MANA_REG = 0;
	const double ARMOR = 0;
	const double MELEE_DMG = 0;
	const double DIST_DMG = 0;
	const double CRIT = 0;
	const double MELEE_RANGE = 0;
	const double DIST_RANGE = 0;
	const double MOVE_SPEED = 0;
	const double MELEE_RATE = 0;
	const double DIST_RATE = 0;
#pragma endregion

	//Animaciones de Cleon
	Anim idleAnim_ = { 0,0,0,0,"" };
	Anim runAnim_ = { 0,0,0,0, "" };
	Anim assaultAnim_ = { 0,0,0,0,"" };
	Anim meleeAnim_ = { 0,0,0,0, "" };
	Anim barrelAnim_ = { 0,0,0,0, "" };

	//Inicializa objetos
	virtual void initObject();
	//Inicializa animaciones
	void initAnims();

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

