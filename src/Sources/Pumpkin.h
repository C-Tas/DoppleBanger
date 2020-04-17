#pragma once
#include "Enemy.h"
class Pumpkin :
	public Enemy
{
private:
	///<summary>vector con todos los objetivos del cangrejo</summary>
	vector<Point2D> targetsVector_;
	///<summary>booleano que determina si debe o no seguir al jugador</summary>
	bool followPlayer_=false;
	///<summary>Int que determina el radio al que empieza a disparar</summary>
	double majorRadius_;
	///<summary>Int que determina el radio al que empieza a correr hacia el player</summary>
	double minorRadius_;
	///<summary>devuelve si ataca o no</summary>
	bool attack();
	///<summary>Devuelve si hay un enemigo en rango y establece cual es el más cercano </summary>
	bool isATargetInRange();
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Pumpkin(Application* app = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0, 0 }, double r1=0, double r2=0):Enemy(app, pos, scale), majorRadius_(r1),minorRadius_(r2) {initObject();};
	//<summary>Constructor por copia</summary>
	Pumpkin(Pumpkin& other) :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Constructor por movimiento<summary>
	Pumpkin(Pumpkin&& other)noexcept :Enemy(other.app_, other.pos_) { initObject(); };
	//<summary>Destructora<summary>
	~Pumpkin() {};
};

