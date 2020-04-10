#pragma once
#include "interactuable.h"
#include "RandEquipGen.h"

class Chest : public interactuable
{

private:
	RandEquipGen rN;

public:
	Chest(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) : //constructora
		interactuable(app, collisionArea, texture, pos, scale), rN(RandEquipGen(app)) {};

	virtual ~Chest() {};

	virtual void pick();

	virtual bool update();

	virtual void onCollider() {};
};