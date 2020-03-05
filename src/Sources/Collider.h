#pragma once
#include "Draw.h"

class Collider: public Draw
{
protected:
	SDL_Rect collisionArea_;
	Collider() {};
	Collider(SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Draw(texture, pos, scale), collisionArea_(collisionArea) {};

	Collider(const Collider& other) :collisionArea_(other.collisionArea_) {};
	Collider(const Collider&& other)noexcept : collisionArea_(other.collisionArea_) {};
	virtual void onCollider() = 0;
public:
	const SDL_Rect getCollider() { return collisionArea_; };
	void setCollider(SDL_Rect newRect) { collisionArea_ = newRect; };
};

