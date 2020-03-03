#pragma once
#include <iostream>
#include "Vector2D.h"

using namespace std;
using uint = unsigned int;

class GameObject
{
private:

protected:
	Vector2D pos_, scale_;
public:
	//constructor vacío
	GameObject() : pos_({ 0,0 }), scale_(0, 0) {};
	//constructor con parámetros
	GameObject(Vector2D pos, Vector2D scale) : pos_(pos), scale_(scale) {};
	//constructor por copía
	GameObject(const GameObject& other) : pos_(other.pos_), scale_(other.scale_) {};
	//constructor por movimiento
	GameObject(const GameObject&& other)noexcept : pos_(other.pos_), scale_(other.scale_) {};
	virtual void update() = 0;
	//virtual void logic() = 0;

	//get
	const Vector2D getPos() { return pos_; }
	const Vector2D getScale() { return scale_; }
	const double getPosX() { return pos_.getX(); }
	const double getPosY() { return pos_.getY(); }
	const double getScaleX() { return scale_.getX(); }
	const double getScaleY() { return scale_.getY(); }

	//set
	Vector2D setPosX(double x) { pos_.setX(x); }
	Vector2D setPosY(double y) { pos_.setY(y); }
	Vector2D setPos(Vector2D newPos) { pos_.setVec(newPos); }
	Vector2D setScaleX(double x) { scale_.setX(x); }
	Vector2D setScaleY(double y) { scale_.setY(y); }
	Vector2D setScale(Vector2D newPos) { scale_.setVec(newPos); }
};

