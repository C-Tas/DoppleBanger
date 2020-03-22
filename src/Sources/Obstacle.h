#pragma once
#include "Collider.h"
using namespace std;

class Obstacle : public Collider {
private:
public:
	Obstacle(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale) {};
	virtual ~Obstacle() {};

	virtual void onCollider() {	//No hace nada, porque lo hacen directamente las otras clases que colisionan (P.ej player)
#ifdef _DEBUG
		cout << "Colisión obstáculo";
#endif
	};
	virtual bool update() { return false; };
};