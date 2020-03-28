#pragma once
#include "Collider.h"

class ShipObject : public Collider
{
public:
	ShipObject(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale) {}

	virtual ~ShipObject() {}

	void onCollider() {}
	void onColliderStash();	// Colisi�n con el alijo
	void onColliderDoor();	// Colisi�n con la trampilla
	void onColliderWheel(int island);	//Colisi�n con el tim�n
};