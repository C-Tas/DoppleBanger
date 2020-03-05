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
	GameObject() : pos_({ 0,0 }), scale_(0, 0) {};
	//GameObject(Vector2D pos, Vector2D scale) : pos_(pos), scale_(scale) {};
	GameObject(Vector2D pos = { 0,0 }, Vector2D scale = {0,0}): pos_(pos),scale_(scale) {}
	virtual void update() = 0;
	virtual void logic() = 0;

	//get
	inline const Vector2D& getPos() const { return pos_; }
	inline double getPosX() { return pos_.getX(); }
	inline double getPosY() { return pos_.getY(); }

	inline const Vector2D& getScale()const { return scale_; }
	double getScaleX() { return scale_.getX(); }
	double getScaleY() { return scale_.getY(); }

	//set
	Vector2D setPosX(double x) { pos_.setX(x); }
	Vector2D setPosY(double y) { pos_.setY(y); }
	Vector2D setPos(Vector2D newPos) { pos_.setVec(newPos); }

	Vector2D setScaleX(double x) { scale_.setX(x); }
	Vector2D setScaleY(double y) { scale_.setY(y); }
	Vector2D setScale(Vector2D newPos) { scale_.setVec(newPos); }

};

