#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"
#include "Button.h"

void backShip(Application* app) {
	app->getGameStateMachine()->popState();
}

//Le dice al GameManager a qué isla queremos ir
void goToIsland(Application* app, Island island) {
	GameManager::instance()->setCurrIsland(island);
	app->getGameStateMachine()->popState();
}

void SelectLevelState::draw() const
{
	GameState::draw();

	SDL_Rect destRect;
	destRect.x = 0; destRect.y = 0;
	destRect.w = app_->getWindowWidth();
	destRect.h = app_->getWindowHeight();
	table->render(destRect);
	map->render(destRect);
}

SelectLevelState::SelectLevelState(Application* app) 
	:GameState(app){
	initState();
}

void SelectLevelState::initState() {
	
	//Button* newIslandButton;

#pragma region Testeo
	GameManager* gm = GameManager::instance();
	table = app_->getTextureManager()->getTexture(Resources::Table);
	if (gm->getUnlockedIslands() == 0) map = app_->getTextureManager()->getTexture(Resources::Map1);
	else if(gm->getUnlockedIslands() == 1)  map = app_->getTextureManager()->getTexture(Resources::Map2);
	else if (gm->getUnlockedIslands() == 2)  map = app_->getTextureManager()->getTexture(Resources::Map3);
#pragma endregion

	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), Vector2D(100, 100),
		Vector2D(100, 100), backShip);
	////Bucle que genera los botones para pasar a las distintas islas según el numero que hayan sido desbloqueadas
	//for (int i = 0; i < functions_.size() && i < islandsUnlocked_; i++) {
	//	newIslandButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
	//		buttonPositions_[i], Vector2D(200, 200), functions_[i]);
	//	addRenderUpdateLists(newIslandButton);
	//}	
}

