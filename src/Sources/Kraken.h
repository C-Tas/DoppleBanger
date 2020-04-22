#pragma once

#include "Enemy.h"
#include "Tentacle.h"
#include <list>

class Kraken : public Enemy
{
public:
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Kraken(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 })
		:Enemy(app, pos, scale) {
		initObject();
	};
	virtual ~Kraken();

	virtual bool update();
	virtual void initObject();
	virtual void onCollider() {};
	void tentDeath(Tentacle* obj);

private:

	int lastAttack_ = 0;
	//Lista con los tentáculos invocados
	list<Tentacle*> tentacles_;
	//Posiciones en las que puede aparecer el kraken
	Point2D krakenSpots_[6]
	{
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
	};

	//Diferentes animaciones del kraken
	Anim idleAnim_ = { 0,0,0,0 ,"" };
	Anim inkAnim_ = { 0,0,0,0,"" };
	Anim diveAnim_ = { 0,0,0,0 ,"" };
	Anim exitAnim_ = { 0,0,0,0,"" };


	//Inicializa las animaciones
	void initAnims();
	void slam();

	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animación del mono)
#pragma region Constantes
	//Idle
	const int NUM_FRAMES_IDLE = 0;
	const uint W_FRAME_IDLE = 0;
	const uint H_FRAME_IDLE = 0;
	const int FRAME_RATE_IDLE = 0;
	//Disparo de tinta
	const int NUM_FRAMES_INK = 0;
	const uint W_FRAME_INK = 0;
	const uint H_FRAME_INK = 0;
	const int FRAME_RATE_INK = 0;
	//Sumergirse
	const int NUM_FRAMES_DIVE = 0;
	const uint W_FRAME_DIVE = 0;
	const uint H_FRAME_DIVE = 0;
	const int FRAME_RATE_DIVE = 0;
	//Salir del agua
	const int NUM_FRAMES_EXIT = 0;
	const uint W_FRAME_EXIT = 0;
	const uint H_FRAME_EXIT = 0;
	const int FRAME_RATE_EXIT = 0;
#pragma endregion


#pragma region Stats
	const double HEALTH = 200;
	const double MANA = 0;
	const double MANA_REG = 0;
	const double ARMOR = 10;
	const double MELEE_DMG = 50;
	const double DIST_DMG = 0;
	const double CRIT = 0;
	const double MELEE_RANGE = 0;
	const double DIST_RANGE = 0;
	const double MOVE_SPEED = 0;
	const double MELEE_RATE = 0;
	const double DIST_RATE = 0;
#pragma endregion
};