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
	GameObject(Vector2D pos, Vector2D scale) : pos_(pos), scale_(scale) {};
	virtual void logic() = 0;
};

