#pragma once
#include "Collider.h"
class interactuable : public Collider
{
protected:

	interactuable(Application* app, Point2D pos, Vector2D scale) :
		Collider(app, pos, scale) { };
	virtual ~interactuable() {};
};