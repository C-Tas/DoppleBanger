#include "ShipState.h"

void ShipState::initState()
{
}

void ShipState::draw() const
{
	PlayState::draw();

	SDL_Rect destRect;
	destRect.x = 0; destRect.y = 0;
	destRect.w = app_->getWindowWidth();
	destRect.h = app_->getWindowHeight();

	background->render(destRect);
}
