#include "EndState.h"

void restartGame(Application* app) {
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

void EndState::initState()
{
	createButton(app_, app_->getTextureManager()->getTexture(Resources::GameOver), Vector2D(0,0), 
		Vector2D(app_->getWindowWidth(), app_->getWindowHeight()), restartGame);
}
