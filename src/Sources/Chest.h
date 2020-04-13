#pragma once
#include "interactuable.h"
#include "RandEquipGen.h"

class Chest : public interactuable
{

private:
	RandEquipGen rN;
	//Anim Chest
public:
	//Constructora por defecto
	Chest(Application* app, Point2D pos, Vector2D scale) : //constructora
		interactuable(app, pos, scale), rN(RandEquipGen(app)) 
	{
		initObject();
	};

	virtual ~Chest() {};

	virtual void pick();

	virtual bool update();

	virtual void onCollider();

	virtual void initObject();
};