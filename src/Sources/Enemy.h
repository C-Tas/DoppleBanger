#pragma once

#include "Actor.h"

using namespace std;

class Enemy : public Actor
{
public:
	//virtuales
	virtual bool update() { return false; };
	virtual void onCollider() {};
	//<summary>Metodo que mata a este enemigo</summary>
	virtual void die();
	virtual void lostAggro() {};
	//Cuando se crea un clon se fija como nuevo objetivo
	virtual void newEnemy(GameObject* obj) { currEnemy_ = obj; };
protected:
	//Rango de puntos de hazaña de la calabaza
	int maxArchievementPoints = 0;
	int minArchievementPoints = 0;
	//Rango de oro que da la calabaza
	int maxGold = 0;
	int minGold = 0;
	//Puntos de hazaña que da esta entidad
	int achievementPoints_ = 0;
	//Oro que esta entidad da
	int goldPoints_ = 0;
	//Último ataque
	Uint32 lastHit = 0;
	//Rango de visión de la entidad
	double rangeVision_ = 0;
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores serán los puestos, si se le pasan valores los editara</summary>
	Enemy(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, double rot = 0)
		:Actor(app, pos, scale, rot) {};
	//<summary>Constructor por copia</summary>
	Enemy(Enemy& other) :Actor(other.app_, other.pos_, other.scale_) {};
	//<summary>Constructor por movimiento<summary>
	Enemy(Enemy&& other)noexcept :Actor(other.app_, other.pos_, other.scale_) {};
	//<summary>Destructor</summary>
	virtual ~Enemy() {};
	//<summary> Devuelve la posicion del player si esta en rango, sino devuelve {-1,-1}</summary>
	virtual Vector2D isPlayerInRange(double n);
	//<summary> Devuelve la posicion del clon si esta en rango, sino devuelve {-1,-1}</summary>
	virtual Vector2D isClonInRange(double n);
	//<summary> Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_</summary>
	virtual bool getEnemy(double n);
	//Devuelve true si el target está dentro del rango de ataque
	virtual bool onRange();
	//Inicializa al Enemy
	virtual void initObject();
	//Inicializa las animaciones
	virtual void initAnims() {};
	//en cada enemigo establece las stats de los enemigos
	virtual void initialStats() = 0;
	//inicializa los puntos de hazaña y el oro que da esta entidad
	virtual void initRewards() = 0;
	//Aplica los rewards al player
	virtual void applyRewards();
#pragma region stats
	  double HEALTH = 0;
	  double MANA = 0;
	  double MANA_REG = 0;
	  double ARMOR = 0;
	  double MELEE_DMG = 0;
	  double DIST_DMG = 0;
	  double CRIT = 0;
	  double MELEE_RANGE = 0;
	  double DIST_RANGE = 0;
	  double MOVE_SPEED = 0;
	  double MELEE_RATE = 0;
	  double DIST_RATE = 0;
#pragma endregion

};