#pragma once
#include "Draw.h"

class Collider : public Draw
{
protected:
	//Variable con la rotación del collider
	double collisionRot_ = 0;
	///<summary>Rect con el area de colisiones</summary>
	SDL_Rect collisionArea_{ 0,0,0,0 };

	//Vectores que representan el tamaño y la posición de la caja de colisiones
	Point2D scaleCollision_ = scale_;
	Point2D posCollision_ = pos_;	//Por el momento se está igualando a pos_, es provisional

	///<summary>Constructor por defecto</summary>
	Collider() {};
	///<summary>Constructor de collider</summary>
	Collider(Application* app, Point2D pos, Vector2D scale, double rot = 0) : collisionRot_(rot),
		Draw(app, pos, scale) {
		posCollision_ = pos;
		scaleCollision_ = scale;
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
	///<summary>Devuelve la rotación de las colisiones</summary>
	const double getCollisionRot() { return collisionRot_; };
	///<summary>Devuelve el rect con el area de colisiones</summary>
	const SDL_Rect& getCollider() {
		collisionArea_.x =(int)round(posCollision_.getX());
		collisionArea_.y = (int)round(posCollision_.getY());
		collisionArea_.w = (int)round(scaleCollision_.getX());
		collisionArea_.h = (int)round(scaleCollision_.getY());
		return collisionArea_;
	};
	const Vector2D getColliderPos() {
		return pos_ + posCollision_;
	}
	const Vector2D getColliderScale() {
		return scaleCollision_;
	}
	///<summary>Establece el rect de colisiones con el valor de newRect</summary>
	void setCollider(SDL_Rect newRect) { collisionArea_ = newRect; };
	///<summary>Fija la rotación de las colisiones</summary>
	void setCollisionRot(double rot) { collisionRot_ = rot; };
	void setColliderPos(Point2D pos) { posCollision_ = pos; }
	void setColliderScale(Point2D pos) { scaleCollision_ = pos; }

};