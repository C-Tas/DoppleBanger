#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
private:
	Vector2D vel_;
protected:
	Dynamic() : vel_({ 0,0 }) {};
	Dynamic(Vector2D vel) : vel_(vel) {};
	Dynamic(Dynamic& other): vel_(other.vel_) {};
	Dynamic(Dynamic&& other)noexcept : vel_(other.vel_) {};
public:
#pragma region getters
	const Vector2D* getVel() { return &vel_; };
#pragma endregion
#pragma region setters
	void setVel(Vector2D vel) { vel_ = vel; };
	void setVelX(double velX) { vel_.setX(velX); };
	void setVelY(double velY) { vel_.setY(velY); };
#pragma endregion
};

