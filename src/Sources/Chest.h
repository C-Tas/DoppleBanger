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
	const int NUM_FRAMES_OPEN = 9;
	const uint W_FRAME_OPEN = 40;
	const uint H_FRAME_OPEN = 40;
	const int FRAME_RATE_OPEN = 200;
	bool open = false;	//Booleano que determina si el cofre se ha abierto o no
public:
	//Constructora por defecto
	Chest(Application* app, Point2D pos, Vector2D scale) : //constructora
		interactuable(app, pos, scale), rN(RandEquipGen(app))
	{
		initObject();
	};

	virtual ~Chest() {};

	virtual bool update();

	virtual void onCollider();

	virtual void initObject();
	virtual void initAnim();
};