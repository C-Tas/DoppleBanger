#include "StashState.h"

void backToPrevious(Application* app) {
	app->getGameStateMachine()->popState();
}

void StashState::initState()
{
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), Vector2D(0, 0), Vector2D(100, 100), backToPrevious);
}
