#pragma once

#include "Collider.h"

class Dynamic : public Collider
{
public:
	//Realiza una acción al detectar una colisión
	virtual void onCollider() {};
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
	//Devuelve la dirección de la entidad
	Vector2D& getDir() { return dir_; };
	//Devuelve la componente x de la dirección
	double getDirX() { return dir_.getX(); };
	//Devuelve la componente y de la dirección
	double getDirY() { return dir_.getY(); };

	//Cambia el objetivo al que se mueve la entidad
	inline void setTarget(Vector2D pos) { target_ = pos; };
protected:
	//<summary>Vector que representa la direccion</summary>
	Vector2D dir_{ 0,0 };
	//<summary>Lugar al que tiene que llegar</summary>	
	Point2D target_{ 0,0 };


	//<summary>Constructor vacio de la clase Dynamic</summary>	
	Dynamic() {};
	//<summary>Constructor  de la clase Dynamic</summary>	
	Dynamic(Application* app, Point2D pos, Vector2D scale, double rot = 0) :
		Collider(app, pos, scale, rot) {};
	//<summary>Constructor  por copia de la clase Dynamic</summary>	
	Dynamic(Dynamic& other) : Collider(other.app_, other.pos_, other.scale_),
		dir_(other.dir_), target_(other.target_) {};
	//<summary>Constructor  por movimiento de la clase Dynamic</summary>	
	Dynamic(Dynamic&& other)noexcept : Collider(other.app_, other.pos_, other.scale_),
		dir_(other.dir_), target_(other.target_) {};

	//<summary>Destructor de Dynamic</summary>	
	virtual ~Dynamic() {};

	virtual void initObject() {};
	virtual void initAnims() {};

};