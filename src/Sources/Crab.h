#pragma once
#include "Enemy.h"
#include <vector>

class Crab : public Enemy
{
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Crab(Application* app, Point2D pos, Vector2D scale, vector<Vector2D> positions = { {0,0},{1200,1200},{3600,1800} }) : Enemy(app, pos, scale), targetsVector_(positions), actualTarget_(0) { currState_ = STATE::PATROLLING; initObject(); }
	//<summary>Constructor por copia</summary>
	Crab(Crab& other) :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };
	//<summary>Constructor por movimiento<summary>
	Crab(Crab&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };
	//<summary>Metodo de colision</summary>
	virtual void onCollider() { attack(); };
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
	//Asigna los vectores
	inline void setPositions(vector<Vector2D> targets) { targetsVector_ = targets; };
	virtual void initRewards() {};
private:
	bool cd = false;
	const int cdDamage_ = 1000;
	int entra_ = 0;
	//Dimensiones de collisionArea
	const int W_COLLISION = scale_.getX() * 0.5;
	const int H_COLLISION = scale_.getY() * (2 / 3);
#pragma region AttackAnimation
	//N�mero de frames
	const int NUM_FRAMES_ATK = 15;
	//const int NUM_FRAMES_ATK_ROW = 3;
	//Dimensiones del clip del spritesheet
	const int W_CLIP_ATK = 100;
	const int H_CLIP_ATK = 100;
	const int ATK_FRAME_RATE = 100;
	//Animaciones
	Anim attackAnim_{ 0,0,0,0, false };
	Texture* attackTex_;
#pragma endregion
#pragma region WalkAnimation
	//N�mero de frames
	const int NUM_FRAMES_WALK = 4;
	//Dimensiones del clip del spritesheet
	const int W_CLIP_WALK = 100;
	const int H_CLIP_WALK = 100;
	const int WALK_FRAME_RATE = 100;
	//Animaciones
	Anim walkAnim_{ 0,0,0,0, false };
	Texture* walkTex_;
#pragma endregion

	//<summary>Estadisticas del cangrejo</summary>
	///<summary>vector con todos los objetivos del cangrejo</summary>
	vector<Point2D> targetsVector_;
	///<summary>posicion del vector al que se dirige</summary>
	int actualTarget_;
	///<summary>actualiza el objetivo al que se dirige</summary>
	void updateTarget() { actualTarget_ = (actualTarget_ + 1) % (targetsVector_.size()); }
	///<summary>devuelve si ataca o no</summary>
	void attack();
	//Inicializa el objeto
	virtual void initObject();
	//Crea las animaciones
	virtual void initAnims();
	virtual void initialStats();

};