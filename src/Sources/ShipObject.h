#pragma once
#include "Collider.h"

class ShipObject : public Collider
{
public:
	ShipObject(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale) {}

	virtual ~ShipObject() {}

	void onCollider() {}
	void onColliderStash();	// Colisión con el alijo
	void onColliderDoor();	// Colisión con la trampilla
	void onColliderWheel(int island);	//Colisión con el timón
};