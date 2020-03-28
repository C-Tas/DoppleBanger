#pragma once
#include "Draw.h"

class Collider: public Draw
{
protected:
	///<summary>Rect con el area de colisiones</summary>
	SDL_Rect collisionArea_{ 0,0,0,0 };

	///<summary>Constructor por defecto</summary>
	Collider() {};
	///<summary>Constructor de collider</summary>
	Collider(Application* app, Point2D pos, Vector2D scale) :
		Draw(app, pos, scale) {
		initObject();
	};

	///<summary>Constructor por copia</summary
	Collider(const Collider& other) :Draw(other.app_, other.pos_, other.scale_),
		collisionArea_(other.collisionArea_) {};

	///<summary>Constructor por movimiento</summary>
	Collider(const Collider&& other)noexcept :Draw(other.app_, other.pos_,other.scale_),
		collisionArea_(other.collisionArea_) {};

	///<summary>Destructor de la clase Collider</summary>
	virtual ~Collider(){};

	///<summary>Método abstracto a redefinir en los hijos de Collider</summary>
	virtual void onCollider() = 0;
	virtual void initObject() {};
public:

	///<summary>Devuelve el rect con el area de colisiones</summary>
	const SDL_Rect getCollider() { return collisionArea_; };
	///<summary>Establece el rect de colisiones con el valor de newRect</summary>
	void setCollider(SDL_Rect newRect) { collisionArea_ = newRect; };
};

