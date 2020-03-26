#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"
#include "Button.h"

//Le dice al GameManager a qué isla queremos ir
void goToIsland(Application* app, int island) {
	GameManager::instance()->setIsland(island);
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

SelectLevelState::SelectLevelState(Application* app, int islandUnlocked ) 
	:GameState(app), islandsUnlocked_(islandUnlocked) {
	initState();
}

void SelectLevelState::initState() {
	
	Button* newIslandButton;

#pragma region Testeo
	table = app_->getTextureManager()->getTexture(Resources::Table);
	if (islandsUnlocked_ == 1) map = app_->getTextureManager()->getTexture(Resources::Map1);
	else if(islandsUnlocked_ == 2)  map = app_->getTextureManager()->getTexture(Resources::Map2);
	else if (islandsUnlocked_ == 3)  map = app_->getTextureManager()->getTexture(Resources::Map3);
#pragma endregion

	////Bucle que genera los botones para pasar a las distintas islas según el numero que hayan sido desbloqueadas
	//for (int i = 0; i < functions_.size() && i < islandsUnlocked_; i++) {
	//	newIslandButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
	//		buttonPositions_[i], Vector2D(200, 200), functions_[i]);
	//	addRenderUpdateLists(newIslandButton);
	//}	
}

