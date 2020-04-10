#pragma once
#include "Collider.h"
using namespace std;

class Obstacle : public Collider {
public:
	Obstacle(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, pos, scale) {
		collisionArea_ = collisionArea;
		texture_ = texture;
	};
	virtual ~Obstacle() {};

	virtual void initObject() {};
	virtual void onCollider() {};	//No hace nada, porque lo hacen directamente las otras clases que colisionan (P.ej player)
	virtual bool update() { return false; };
};