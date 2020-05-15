#include "CreditsState.h"
#include "Button.h"

void CreditsState::backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState();
}

void CreditsState::initState() {
	Button* b = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::MenuButton),
		{ double(app_->getWindowWidth() / 2),double(app_->getWindowHeight() / 2) - 400 }, { 500,500 }, backToPreviousState);
	gameObjects_.push_back(b);
	objectsToRender_.push_back(b);
}
