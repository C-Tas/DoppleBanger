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
	virtual void initialStats() {};
	virtual void lostAggro();
	virtual void initRewards();
	//Se redefine como publico porque el tentaculo necesita acceso a el
	virtual bool applyCritic() { return Actor::applyCritic(); }
	inline void setPositions(Vector2D pos){ krakenSpots_.push_back(pos); };
private:
	Cooldown attackCD_;
	Cooldown swimCD_;

	//Lista con los tent�culos invocados
	list<Tentacle*> tentacles_;

	//Posiciones en las que puede aparecer el kraken
	vector<Point2D> krakenSpots_;

	//Diferentes animaciones del kraken
	Anim idleAnim_ = { 0,0,0,0,false };
	Anim inkAnim_ = { 0,0,0,0,false };
	Anim diveAnim_ = { 0,0,0,0,false };
	Anim exitAnim_ = { 0,0,0,0,false };

	//Inicializa las animaciones
	void initAnims();
	void slam();
	void sweep();
	void swimInit(); //Empieza la animación de sumergirse y calcula a donde nadar
	void swimEnd(); //Se mueve a la posición calculada y empieza la animacion de emerger
	void ink();
	virtual void updateCooldowns();

	//Constantes para crear las diferentes animaciones 
	//(los valores puestos no son los correctos, a falta de hacer la animaci�n del kraken)
#pragma region Constantes
	//Tiempo desde que se sumerge hasta que emerge
	const double SWIM_DURATION = 1000;
	const int AVERAGE_INK_SHOTS = 7;
	const int NORMAL_DESVIATION = 2;
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
	const double HEALTH = 5000;
	const double MANA = 0;
	const double MANA_REG = 0;
	const double ARMOR = 10;
	const double MELEE_DMG = 100;
	const double DIST_DMG = 75;
	const double CRIT = 0;
	const double MELEE_RANGE = 0;
	const double DIST_RANGE = 0;
	const double MOVE_SPEED = 0;
	const double MELEE_RATE = 2000;	//En milisegundos
	const double DIST_RATE = 5000;	//En milisegundos
#pragma endregion
};