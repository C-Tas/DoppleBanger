#pragma once
#include "Draw.h"

class Collider: public Draw
{
private:
	SDL_Rect* collisionArea_;
protected:
	Collider(): collisionArea_(nullptr) {};
	Collider(SDL_Rect* collisionArea) : collisionArea_(collisionArea) {};
	Collider(const Collider& other) :collisionArea_(other.collisionArea_) {};
	Collider(const Collider&& other)noexcept : collisionArea_(other.collisionArea_) {};
	virtual void onCollider() = 0;
};

