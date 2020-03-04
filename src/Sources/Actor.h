#pragma once
#include "Dynamic.h"
class Actor : public Dynamic
{
protected:
	Actor(Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }) : Dynamic(texture, pos, scale) {};
	//~Actor() {};
public:

};

