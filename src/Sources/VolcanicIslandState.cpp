#include "VolcanicIslandState.h"
#include "Crab.h"

void VolcanicIslandState::initState()
{
	gm_->setOnShip(false);
}

VolcanicIslandState::VolcanicIslandState(Application* app): PlayState(app)
{
}