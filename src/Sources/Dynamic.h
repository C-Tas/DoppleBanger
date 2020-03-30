#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
protected:
	//<summary>Vector que representa la direccion</summary>
	Vector2D dir_{ 0,0 };
	//<summary>Lugar al que tiene que llegar</summary>	
	Point2D target_{ 0,0 };


	//<summary>Constructor vacio de la clase Dynamic</summary>	
	Dynamic() {};
	//<summary>Constructor  de la clase Dynamic</summary>	
	Dynamic(Application* app, Point2D pos, Vector2D scale) :
		Collider(app, pos, scale) {};
	//<summary>Constructor  por copia de la clase Dynamic</summary>	
	Dynamic(Dynamic& other) : Collider(other.app_, other.pos_, other.scale_),
		dir_(other.dir_), target_(other.target_) {};
	//<summary>Constructor  por movimiento de la clase Dynamic</summary>	
	Dynamic(Dynamic&& other)noexcept : Collider(other.app_, other.pos_, other.scale_),
		dir_(other.dir_), target_(other.target_) {};

	//<summary>Destructor de Dynamic</summary>	
	virtual ~Dynamic() {};

	virtual void initObject() {};
	virtual void initAnim() {};
public:
	//Realiza una acci�n al detectar una colisi�n
	virtual void onCollider() {};
	//<summary>Establece la direccion del movimiento</summary>	
	virtual void move(Point2D target);
};