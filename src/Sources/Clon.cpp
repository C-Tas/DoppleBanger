#include "Clon.h"
#include "GameState.h"

bool Clon::update()
{
	if ((SDL_GetTicks() - timeSpawn_) / 1000 < duration_) {
		//Ataca con ad_ y meleeRate_
	}
	else if (explotion_) explode();
	else die();

	return false;
}

void Clon::die()
{
	app_->getGameStateMachine()->getState()->removeRenderUpdateLists(this);
}