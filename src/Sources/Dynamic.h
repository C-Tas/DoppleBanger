#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
private:
	Vector2D vel_;
protected:
	Vector2D dir_;				//Vector que representa la direcci�n
	double speed_;				//Representa la velocidad del cuerpo
	Dynamic() : dir_({ 0,0 }), speed_(0) {};
	Dynamic(Vector2D vel, double speed) : dir_(vel), speed_(speed) {};
	Dynamic(Dynamic& other): dir_(other.dir_),speed_(other.speed_) {};
	Dynamic(Dynamic&& other)noexcept : dir_(other.dir_), speed_(other.speed_) {};
	void move(Point2D target);
};

