#pragma once
#include "Collider.h"
class TestObjectCollider : public Collider
{
private:

public:
	TestObjectCollider(Application* app, SDL_Rect collisionArea, Texture* texture, Vector2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale) {}

	void onCollider() { cout << "Colisión detectada" << endl; }
	bool update() { return false; }
};

