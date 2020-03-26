#pragma once
#include "Draw.h"

class Collider: public Draw
{
protected:
	///<summary>Rect con el area de colisiones</summary>
	SDL_Rect collisionArea_;

	///<summary>Constructor por defecto</summary>
	Collider() : collisionArea_({0,0,0,0}) {};
	///<summary>Constructor de collider</summary>
	Collider(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale, SDL_Rect frame = {0,0,0,0}, int numberFrames = 0) :
		Draw(app, texture, pos, scale,frame,numberFrames), collisionArea_(collisionArea) {};

	///<summary>Constructor por copia</summary
	Collider(const Collider& other) :collisionArea_(other.collisionArea_) {};
	///<summary>Constructor por movimiento</summary>
	Collider(const Collider&& other)noexcept : collisionArea_(other.collisionArea_) {};

	///<summary>Destructor de la clase Collider</summary>
	virtual ~Collider(){};

	///<summary>Método abstracto a redefinir en los hijos de Collider</summary>
	virtual void onCollider() = 0;

public:
	///<summary>Devuelve el rect con el area de colisiones</summary>
	const SDL_Rect getCollider() { return collisionArea_; };
	///<summary>Establece el rect de colisiones con el valor de newRect</summary>
	void setCollider(SDL_Rect newRect) { collisionArea_ = newRect; };
};

