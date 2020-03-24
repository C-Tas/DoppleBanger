#pragma once
#include "PlayState.h"
class ShipState : public PlayState
{
private:
	void initState();
	Texture* background = nullptr;

public:
	ShipState(Application* app) : PlayState(app) { initState(); }
	void draw() const;
};

