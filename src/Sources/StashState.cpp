#include "StashState.h"
#include "GameManager.h"
void StashState::backToPrevious(Application* app) {
	app->getStateMachine()->popState();
}

void StashState::initState() {
	//La textura es temporal porque de momento no está la interfaz de este estado
	background_ = app_->getTextureManager()->getTexture(Resources::TextureId::InventaryMenu);

	GameManager* gm = GameManager::instance();

	stash_ = gm->getStash();
	inventory_ = gm->getInventory();
}