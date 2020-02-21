#pragma once
#include "GameObject.h"
class Trigger :
	public GameObject
{
protected:
	virtual void onOverlap() {};
};

