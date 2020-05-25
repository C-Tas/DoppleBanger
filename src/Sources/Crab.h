#pragma once
#include "Enemy.h"
#include <vector>

class Crab : public Enemy
{
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Crab(Application* app, Point2D pos, Vector2D scale) :
		Enemy(app, pos, scale), actualTarget_(0) { initObject(); }
	//<summary>Constructor por copia</summary>
	Crab(Crab& other) :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };
	//<summary>Constructor por movimiento<summary>
	Crab(Crab&& other)noexcept :Enemy(other.app_, other.pos_, other.scale_) { initAnims(); };
	//<summary>Metodo de colision</summary>
	virtual void onCollider() {};
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
	//Asigna los vectores
	inline void setPositions(Vector2D target) { targetsVector_.push_back(target); };
	virtual void initRewards() {};
private:
	Cooldown meleeCD_;
	bool attacking_ = false;	//Para saber si el cangrejo esta atacando
	//Dimensiones de collisionArea
	const int W_COLLISION = scale_.getX() * 0.5;
	const int H_COLLISION = scale_.getY() * (2 / 3);
#pragma region Animaciones
	//Inicializa la animacion
	void initMeleeAnim();
	void initWalk();
	void initIdle();
	virtual void initDie();

	//Gestiona la animacion
	void meleeAnim();
	const int W_H_FRAME = 100;

	//Idle
	const int IDLE_NUM_FRAMES = 8;
	const int IDLE_FRAME_RATE = 100;
	Anim idleAnim_{ 0, 0, 0, 0, true };
	Texture* idleTx_ = nullptr;

	//Ataque
	const int FRAME_ACTION = 9;
	const int NUM_FRAMES_ATK = 15;	//Numero de frames
	const int ATK_FRAME_RATE = 60;	//Velocidad de animacion
	//Animaciones
	Anim attackAnim_{ 0,0,0,0, false };
	Texture* attackTex_;

	//N�mero de frames
	const int NUM_FRAMES_WALK = 4;
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
	//Inicializa los stats
	virtual void initialStats();
	//Acutaliza Cooldowns
	virtual void updateCooldowns();
};