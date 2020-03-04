#pragma once
#include "Draw.h"

class Collider: public Draw
{
protected:
	SDL_Rect* collisionArea_;
	Collider(): collisionArea_(nullptr) {};
	Collider(SDL_Rect* collisionArea, Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale) :
		Draw(texture, destiny, pos, scale), collisionArea_(collisionArea) {};

	Collider(const Collider& other) :collisionArea_(other.collisionArea_) {};
	Collider(const Collider&& other)noexcept : collisionArea_(other.collisionArea_) {};
	virtual void onCollider() = 0;
public:
	const SDL_Rect* getCollider() { return collisionArea_; };
	void setCollider(SDL_Rect* newRect) { collisionArea_ = newRect; };
};

