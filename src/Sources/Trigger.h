#pragma once
#include "GameObject.h"
class Trigger : public GameObject
{
protected:
	SDL_Rect* triggerArea_;
	Trigger() : triggerArea_(nullptr) {};
	Trigger(Application* app ,SDL_Rect* triggerArea, Point2D pos, Vector2D scale)
		:GameObject(app,pos, scale), triggerArea_(triggerArea) {};
	~Trigger() { delete triggerArea_; };
public:
	const SDL_Rect* getTriggerArea() { return triggerArea_; };
	void setTriggerArea(SDL_Rect* newArea) { triggerArea_ = newArea; };
	virtual void onOverlap() = 0;
};