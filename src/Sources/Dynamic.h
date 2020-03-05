#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
protected:
	Vector2D vel_;				//Vector que representa la direcci�n
	Dynamic() : vel_({ 0,0 }) {};
	Dynamic(Vector2D dir, Texture* texture, Point2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Collider(collisionArea, texture, pos, scale), vel_(dir) {};
	Dynamic(Dynamic& other): vel_(other.vel_) {};
	Dynamic(Dynamic&& other)noexcept : vel_(other.vel_) {};
	void move(Point2D target);
};

