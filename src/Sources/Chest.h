#pragma once
#include "interactuable.h"
#include "RandEquipGen.h"
#include "Inventory.h"

class Chest : public interactuable
{

private:
	RandEquipGen rN;
	
	Anim openAnim_ = { 0,0,0,0, false };

	//Anim Chest
	const int NUM_FRAMES_OPEN = 10;
	const uint W_FRAME_OPEN = 200;
	const uint H_FRAME_OPEN = 200;
	const int FRAME_RATE_OPEN = 500;
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