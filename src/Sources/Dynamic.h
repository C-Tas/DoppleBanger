#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
protected:
	Vector2D dir_;				//Vector que representa la direcci�n

	Dynamic() : dir_({ 0,0 }) {};
	Dynamic(Texture* texture, Point2D pos, Vector2D scale, SDL_Rect collisionArea) :
		Collider(collisionArea, texture, pos, scale), dir_({ 0,0 }) {};
	Dynamic(Dynamic& other): dir_(other.dir_) {};
	Dynamic(Dynamic&& other)noexcept : dir_(other.dir_) {};
	void move(Point2D target);
};

