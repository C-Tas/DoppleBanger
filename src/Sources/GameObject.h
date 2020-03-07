#pragma once
#include "Application.h"
#include "Vector2D.h"

using namespace std;
using uint = unsigned int;

class GameObject
{
protected:
	Vector2D pos_, scale_;
	Application* app_;

public:
	//constructor vac�o
	GameObject() : pos_({ 0,0 }), scale_(0, 0) {};
	//constructor con par�metros
	GameObject(Application* app, Vector2D pos, Vector2D scale) : app_(app), pos_(pos), scale_(scale) {};

	//constructor por cop�a
	GameObject(const GameObject& other) : pos_(other.pos_), scale_(other.scale_) {};
	//constructor por movimiento
	GameObject(const GameObject&& other)noexcept : pos_(other.pos_), scale_(other.scale_) {};
	virtual void update() = 0;
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

