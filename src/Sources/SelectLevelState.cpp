#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"
#include "Button.h"
#include "Draw.h"
#include "VisualElement.h"

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
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

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
	Vector2D scaleButton(winWidth / 6, winHeight / 15);
	Vector2D posButton(scaleButton.getX() / 2, scaleButton.getY());
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton,
		scaleButton, backShip, this);
	////Bucle que genera los botones para pasar a las distintas islas según el numero que hayan sido desbloqueadas
	//for (int i = 0; i < functions_.size() && i < islandsUnlocked_; i++) {
	//	newIslandButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon),
	//		buttonPositions_[i], Vector2D(200, 200), functions_[i]);
	//	addRenderUpdateLists(newIslandButton);
	//}	
}

