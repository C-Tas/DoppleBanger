#pragma once
#include "Enemy.h"
#include <vector>

class Crab : public Enemy
{
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Crab(Application* app, Point2D pos, Vector2D scale) : Enemy(app, pos, scale) { initObject(); }
	//<summary>Constructor por copia</summary>
	Crab(Crab& other) :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };
	//<summary>Constructor por movimiento<summary>
	Crab(Crab&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };

	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
	//Asigna los vectores
	inline void setPositions(vector<Vector2D> targets) { targetsVector_ = targets; };

private:
	//Dimensiones de collisionArea
	const int W_COLLISION = scale_.getX() * 0.5;
	const int H_COLLISION = scale_.getY() * (2 / 3);
#pragma region AttackAnimation
	//N�mero de frames
	const int NUM_FRAMES_ATK = 14;
	const int NUM_FRAMES_ATK_ROW = 3;
	//Dimensiones del clip del spritesheet
	const int W_CLIP_ATK = 70;
	const int H_CLIP_ATK = 45;
	//Animaciones
	Anim attackAnim_{ 0,0,0,0, false };
#pragma endregion
	//<summary>Estadisticas del cangrejo</summary>
#pragma region ConstStats
	const double HEALTH = 1000;
	const double MANA = 0;
	const double MANA_REG = 0;
	const double ARMOR = 1000;
	const double MELEE_DAMAGE = 1000;
	const double DIST_DAMAGE = 0;
	const double CRIT = 0;
	const double MELEE_RANGE = 50;
	const double DIST_RANGE = 0;
	const double MOVE_SPEED = 100;
	const double MELEE_RATE = 1;
	const double DIST_RATE = 2;
#pragma endregion
	///<summary>vector con todos los objetivos del cangrejo</summary>
	vector<Point2D> targetsVector_;
	///<summary>posicion del vector al que se dirige</summary>
	int actualTarget_;
	///<summary>actualiza el objetivo al que se dirige</summary>
	void updateTarget() { actualTarget_ = (actualTarget_ + 1) % targetsVector_.size(); }
	///<summary>devuelve si ataca o no</summary>
	void attack();
	//Inicializa el objeto
	virtual void initObject();
	//Crea las animaciones
	virtual void initAnims();

};