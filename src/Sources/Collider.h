#pragma once
#include "Draw.h"

class Collider : public Draw
{
protected:
	///<summary>Rect con el area de colisiones</summary>
	SDL_Rect collisionArea_{ 0,0,0,0 };

	//Vectores que representan el tamaño y la posición de la caja de colisiones
	Point2D scaleCollision_;
	Point2D posCollision_ = pos_;	//Por el momento se está igualando a pos_, es provisional

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
	Collider(const Collider&& other)noexcept :Draw(other.app_, other.pos_, other.scale_),
		collisionArea_(other.collisionArea_) {};

	///<summary>Destructor de la clase Collider</summary>
	virtual ~Collider() {};

	///<summary>Método abstracto a redefinir en los hijos de Collider</summary>
	virtual void initObject() {};
	virtual void initAnims() {};

public:
	//Realiza una acción al detectar una colisión
	virtual void onCollider() = 0;
	///<summary>Devuelve el rect con el area de colisiones</summary>
	const SDL_Rect& getCollider() {
		posCollision_ = pos_;	//Provisional -> esta línea se borrará
		collisionArea_.x = posCollision_.getX();
		collisionArea_.y = posCollision_.getY();
		collisionArea_.w = scaleCollision_.getX();
		collisionArea_.h = scaleCollision_.getY();
		return collisionArea_;
	};
	///<summary>Establece el rect de colisiones con el valor de newRect</summary>
	void setCollider(SDL_Rect newRect) { collisionArea_ = newRect; };
};