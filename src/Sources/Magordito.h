#pragma once
#include "Enemy.h"

class Magordito : public Enemy {
public:
	Magordito(Application* app = nullptr, Point2D pos = { 0, 0 }, Vector2D scale = { 0, 0 }) : 
		Enemy(app, pos, scale) { initObject(); };
	~Magordito() {}

	virtual bool update();
	virtual void onCollider() {};

private:
	//Estadisticas de Magordito
#pragma region Stats
	const double HEALTH = 1000;
	const double MANA = 0;
	const double MANA_REG = 0;
	const double ARMOR = 500;
	const double MELEE_DMG = 0;
	const double DIST_DMG = 150;
	const double CRIT = 10;
	const double MELEE_RANGE = 0;
	const double DIST_RANGE = 1000;
	const double MOVE_SPEED = 0;
	const double MELEE_RATE = 0;
	const double DIST_RATE = 500;
#pragma endregion

	//Animaciones de Magordito
	Anim idleAnim_ = { 0,0,0,0,0 ,"" };
	Anim teleportAnim_ = { 0,0,0,0,0,"" };
	Anim kirinAnim_ = { 0,0,0,0,0, "" };

	//Posiciones de los puntos de teletransporte
	Point2D MagorditoSpots_[5] {
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}
	};

	//Inicializa objetos
	virtual void initObject();
	//Inicializa animaciones
	void initAnims();

#pragma region Constantes
	//Animacion idle de Magordito
	const int NUM_FRAMES_IDLE = 0;
	const int NUM_FRAMES_ROW_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE= 0;
	const string NAME_IDLE = "idle";

	//Animacion del teletransporte (junto a invocación al final)
	const int NUM_FRAMES_TELEPORT = 0;
	const int NUM_FRAMES_ROW_TELEPORT = 0;
	const uint W_FRAME_TELEPORT = 0;
	const uint H_FRAME_TELEPORT = 0;
	const int FRAME_RATE_TELEPORT = 0;
	const string NAME_TELEPORT = "teleport";

	//Animacion del disparo de un meteorito de rayos 
	const int NUM_FRAMES_KIRIN = 0;
	const int NUM_FRAMES_ROW_KIRIN = 0;
	const uint W_FRAME_KIRIN = 0;
	const uint H_FRAME_KIRIN = 0;
	const int FRAME_RATE_KIRIN = 0;
	const string NAME_KIRIN = "kirin";
#pragma endregion
};