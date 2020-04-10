#include "SkillState.h"

void SkillState::initState()
{
	cout << "SkillState" << endl;
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), Vector2D(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2),
		Vector2D(100, 100), goToGame);
}

void SkillState::goToGame(Application* app)
{
	app->getGameStateMachine()->popState();
}