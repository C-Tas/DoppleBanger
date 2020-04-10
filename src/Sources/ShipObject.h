#pragma once
#include "Collider.h"

using CallBackChangeState = void(Application * app);
class ShipObject : public Collider
{
public:
	//Constructora por defecto
	ShipObject(Application* app, Point2D pos, Vector2D scale, Texture* texture, CallBackChangeState* cb) :
		Collider(app, pos, scale), cb_(cb) {
		setTexture(texture);
	};
	//Constructora por copia
	ShipObject(ShipObject& other) : Collider(other.app_, other.pos_, other.scale_) {};
	//Constructora por movimiento
	ShipObject(ShipObject&& other) noexcept : Collider(other.app_, other.pos_, other.scale_) {};
	virtual ~ShipObject() {};

	void onCollider();
private:
	CallBackChangeState* cb_ = nullptr;
};