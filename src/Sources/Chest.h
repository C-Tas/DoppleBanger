#pragma once
#include "Collider.h"

class RandEquipGen;
class Inventory;

class Chest : public Collider
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
		Collider(app, pos, scale), rN(RandEquipGen(app))
	{
		initObject();
	};

	virtual ~Chest() {};

	virtual bool update() { return false; };

	virtual void onCollider();

	virtual void initObject();
	virtual void initAnim();
};