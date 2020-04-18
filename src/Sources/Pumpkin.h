#pragma once
#include "Enemy.h"
class Pumpkin :
	public Enemy
{
private:
	Uint32 lastHit = 0;
	///<summary>booleano que determina si debe o no seguir al jugador</summary>
	bool followPlayer_=false;

	 uint wHSeed = app_->getWindowHeight() / 40;		//Tamaño de la semilla
	 double seedVel = 700;							//Velocidad de la semilla
	 double seedLife = 3;								//Vida del proyectil en segundos
	 Anim explotingAnim_ = { 0,0,0,0,0 ,"" };
	 const int NUM_FRAMES_EXP = 10;
	 const int NUM_FRAMES_ROW_EXP = 3;
	 const int W_FRAME_EXP = 200;
	 const int H_FRAME_EXP = 200;
	 const int FRAME_RATE_EXP = 100;
	 const string NAME_EXP = "explode";
	///<summary>Devuelve si hay un enemigo en rango y establece cual es el más cercano </summary>
	bool onDistRange();
	///
	bool onMeleeRange();
	///
	void disAttack();
	///
	void initObject();
	///
	void lostAgro();
	///
	void animationsvar();
	///
	void initialStats();
	///
	void follow();
	///
	void explote();
	void move(Point2D posToReach);
	void onCollider() { explote(); }
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Pumpkin(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 } ):Enemy(app, pos, scale) {initObject();};
	//<summary>Constructor por copia</summary>
	Pumpkin(Pumpkin& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	Pumpkin(Pumpkin&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Destructora<summary>
	~Pumpkin() {};
};

