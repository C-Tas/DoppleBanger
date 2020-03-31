#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
protected:
    //<summary>Vector que representa la direccion</summary>
	Vector2D dir_;	
	//<summary>Lugar al que tiene que llegar</summary>	
	Point2D obj_;				
	//<summary>Constructor vacio de la clase Dynamic</summary>	
	Dynamic() : dir_({ 0,0 }),obj_({0,0}) {};
	//<summary>Constructor  de la clase Dynamic</summary>	
	Dynamic(Application* app, Texture* texture, Point2D pos, Vector2D scale, SDL_Rect collisionArea, SDL_Rect frame = {0,0,0,0},int numberFrames=0) :
		Collider(app, collisionArea, texture, pos, scale,frame,numberFrames), dir_({ 0,0 }), obj_({0,0}) {};
	//<summary>Constructor  por copia de la clase Dynamic</summary>	
	Dynamic(Dynamic& other): dir_(other.dir_),obj_(other.obj_) {};
	//<summary>Constructor  por movimiento de la clase Dynamic</summary>	
	Dynamic(Dynamic&& other)noexcept : dir_(other.dir_),obj_(other.obj_) {};
	//<summary>Destructor de Dynamic</summary>	
	virtual ~Dynamic(){};

public:
	//<summary>Establece la direccion del movimiento</summary>	
	void move(Point2D target);
};

