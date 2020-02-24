#pragma once
#include "Draw.h"

class Collider: public Draw
{
protected:
	Collider(Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale= {0,0}):Draw(texture,pos,scale) {};
	virtual void onCollider() {};
};

