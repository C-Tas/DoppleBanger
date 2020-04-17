#pragma once
#include "Actor.h"
using namespace std;
class Enemy : public Actor
{
public:
	virtual bool update() { return false; };
	virtual void onCollider() {};
	//<summary>Metodo que mata a este enemigo</summary>
	virtual void die();
	virtual void lostAgro() {};
protected:
	//Rango de visión de la entidad
	double rangeVision_ = 0;
	Uint32 lastFrame_ = 0;
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores serán los puestos, si se le pasan valores los editara</summary>
	Enemy(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 })
		:Actor(app, pos, scale) {};
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
	//Actualiza la animaci�n en funci�n del frameRate de la actual animaci�n
	virtual void updateAnim();
	//Inicializa al Enemy
	virtual void initObject();
	//Inicializa las animaciones
	virtual void initAnim();
	//cambia la animacion
	virtual void changeAnim(Anim& newAnim);
	virtual void animationsvar()=0;
	virtual void initialStats() = 0;
#pragma region Animacion
	Anim attackAnim_ = { 0,0,0,0,0 ,"" };
	Anim walkAnim_ = { 0,0,0,0,0,"" };
	Anim idleAnim_ = { 0,0,0,0,0,"" };
	 int NUM_FRAMES_ATK = 0;
	 int NUM_FRAMES_ROW_ATK = 0;
	 uint W_FRAME_ATK = 0;
	 uint H_FRAME_ATK = 0;
	 int FRAME_RATE_ATK = 0;
	 string NAME_ATK = "attack";
	//Para el movimiento
	 int NUM_FRAMES_MOV = 0;
	 int NUM_FRAMES_ROW_MOV = 0;
	 uint W_FRAME_MOV = 0;
	 uint H_FRAME_MOV = 0;
	 int FRAME_RATE_MOV = 0;
	 string NAME_MOV = "walk";
	//Para estar parado
	 int NUM_FRAMES_IDLE =0;
	 int NUM_FRAMES_ROW_ADLE = 0;
	 uint W_FRAME_IDLE = 0;
	 uint H_FRAME_IDLE = 0;
	 int FRAME_RATE_IDLE = 0;
	 string NAME_IDLE = "idle";

	 virtual void animationsVar() {};
#pragma endregion
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