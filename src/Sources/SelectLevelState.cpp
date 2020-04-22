#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"
#include "Button.h"
#include "Draw.h"

void backShip(Application* app) {
	SDL_ShowCursor(SDL_DISABLE);
	app->getGameStateMachine()->popState();
}

//Le dice al GameManager a qué isla queremos ir
void goToIsland(Application* app, Island island) {
	GameManager::instance()->setCurrIsland(island);
	app->getGameStateMachine()->popState();
}

SelectLevelState::SelectLevelState(Application* app) 
	:GameState(app){
	initState();
}

void SelectLevelState::initState() {
	SDL_ShowCursor(SDL_ENABLE);

	//Button* newIslandButton;

#pragma region Testeo
	GameManager* gm = GameManager::instance();
	table_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Table));
	addRenderUpdateLists(table_);
	if (gm->getUnlockedIslands() == Island::Caribbean) map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map1));
	else if(gm->getUnlockedIslands() == Island::Spooky)  map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map2));
	else if (gm->getUnlockedIslands() == Island::Volcanic)  map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map3));
	addRenderUpdateLists(map_);
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

