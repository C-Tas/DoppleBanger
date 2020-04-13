#pragma once
#include "interactuable.h"
#include "RandEquipGen.h"
#include "Inventory.h"

class Chest : public interactuable
{

private:
	RandEquipGen rN;
	
	//Anim Chest
	const int NUM_FRAMES_ATK = 10;
	const int NUM_FRAMES_ROW_ATK = 3;
	const uint W_FRAME_ATK = 200;
	const uint H_FRAME_ATK = 200;
	const int FRAME_RATE_ATK = 500;
	const string NAME_ATK = "attack";
public:
	//Constructora por defecto
	Chest(Application* app, Point2D pos, Vector2D scale) : //constructora
		interactuable(app, pos, scale), rN(RandEquipGen(app))
	{
		initObject();
	};

	virtual ~Chest() {};

	virtual bool update() { return false; };

	virtual void onCollider();

	virtual void initObject();
	virtual void initAnim();
};