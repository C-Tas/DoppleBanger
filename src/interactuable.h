#pragma once
#include "Collider.h"
class interactuable :
	public Collider
{
protected:
	virtual void pick() = 0;
};

