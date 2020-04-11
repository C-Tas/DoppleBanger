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
	//Se redefine el método draw para que tenga en cuenta la cámara
	const virtual void draw() {
		SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
		if (currAnim_.numberFrames_ <= 0) texture_->render(dest, SDL_FLIP_NONE);
		else texture_->render(dest, frame_);
	};
};