#include "WinState.h"
#include "EndState.h"

void resetGame(Application* app) {
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

void WinState::initState()
{
	createButton(app_, app_->getTextureManager()->getTexture(Resources::Win), Vector2D(0, 0),
		Vector2D(app_->getWindowWidth(), app_->getWindowHeight()), resetGame);
}

