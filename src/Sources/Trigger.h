#pragma once
#include "GameObject.h"

class Trigger : public GameObject
{
protected:
	SDL_Rect triggerArea_ = {(0,0,0,0)};

	Trigger() {};
	Trigger(Application* app, Point2D pos, Vector2D scale)
		:GameObject(app, pos, scale) {};

	~Trigger() {  };
	virtual void onOverlap() = 0;
	virtual void initObject() = 0;
public:
	const SDL_Rect* getTriggerArea() { return &triggerArea_; };
	void setTriggerArea(SDL_Rect &newArea) { triggerArea_ = newArea; };
};