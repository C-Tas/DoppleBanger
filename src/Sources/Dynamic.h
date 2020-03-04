#pragma once
#include "Collider.h"
class Dynamic : public Collider
{
protected:
	Dynamic(Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }) : Collider(texture, pos, scale) {};
	//~Dynamic();
	Vector2D vel_;
public:
};

