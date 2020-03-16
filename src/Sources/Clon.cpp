#include "Clon.h"

bool Clon::update()
{
	if ((SDL_GetTicks() - timeSpawn_) / 1000 < duration_ && ad_ > 0) {
		//Ataca con ad_ y meleeRate_
	}
	else explode();

	return false;
}