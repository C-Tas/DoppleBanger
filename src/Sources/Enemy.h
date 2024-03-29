#pragma once

#include "Actor.h"
#include "AStar.hpp"
using namespace std;

class Enemy : public Actor
{
public:
	//virtuales
	virtual bool update() { return false; };
	virtual void onCollider() {};
	virtual void receiveDamage(double damage);
	//<summary>Metodo que mata a este enemigo</summary>
	virtual void die();
	virtual void lostAggro() { currEnemy_ = nullptr; };
	//Cuando se crea un clon se fija como nuevo objetivo
	virtual void newEnemy(GameObject* obj) { currEnemy_ = obj; };

	void setIniPosMap_(Vector2D pos) { iniPosMap_ = pos; };
	void setPathPos(AStar::Vec2i pos) { pathPos_ = pos; };

	Vector2D getIniPosMap_() { return iniPosMap_; };
	AStar::Vec2i getPathPos() { return pathPos_; };
	//Devuelve el tag 
	string getTag() { return tag_; }
protected:
	//Ultimo actualizacion del AStar
	AStar::CoordinateList pathing_;
	//Posicion en el mapa de tiled
	AStar::Vec2i pathPos_ = {};
	//Posicion inicial del mapa
	Vector2D iniPosMap_;
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
	//Rango de visión de la entidad
	double rangeVision_ = 0;
	//Tag del enemy
	string tag_ = "";
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
	//Devuelve true si el target está dentro del rango de ataque en función de un rango en concreto
	virtual bool onRange(double range);
	//Inicializa al Enemy
	virtual void initObject();
	//Inicializa las animaciones
	virtual void initAnims() {};

	virtual void initDie();
	//en cada enemigo establece las stats de los enemigos
	virtual void initialStats() = 0;

	Vector2D PosToTile(Vector2D pos);
	Vector2D TileToPos(Vector2D tile);
	//inicializa los puntos de hazaña y el oro que da esta entidad
	virtual void initRewards() = 0;
	//Aplica los rewards al player
	virtual void applyRewards();
	//Actualiza los Cooldowns
	virtual void updateCooldowns() = 0;
#pragma region stats
	double initHealth_ = 0;
	double initMana_ = 0;
	double initManaReg_ = 0;
	double initArmor_ = 0;
	double initMeleeDmg = 0;
	double initDistDmg = 0;
	double initCrit_ = 0;
	double initMeleeRange = 0;
	double initDistRange_ = 0;
	double initMoveSpeed = 0;
	double initMeleeRate_ = 0;
	double initDistRate_ = 0;
#pragma endregion

};