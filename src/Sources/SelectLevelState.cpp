#include "SelectLevelState.h"
#include "CaribbeanIslandState.h"
#include "SpookyIslandState.h"
#include "VolcanicIslandState.h"
#include "GameManager.h"
#include "Button.h"
#include "Draw.h"
#include "VisualElement.h"

//Para volver al barco
void backShip(Application* app) {
	SDL_ShowCursor(SDL_DISABLE);
	app->getGameStateMachine()->popState();
}

//Para viajar a la isla 1
void goToIsland1(Application* app) {
	GameManager::instance()->setCurrIsland(Island::Caribbean);
	app->getGameStateMachine()->popState();
}

//Para viajar a la isla 2
void goToIsland2(Application* app) {
	GameManager::instance()->setCurrIsland(Island::Spooky);
	app->getGameStateMachine()->popState();
}

//Para viajar a la isla 3
void goToIsland3(Application* app) {
	GameManager::instance()->setCurrIsland(Island::Volcanic);
	app->getGameStateMachine()->popState();
}

//Constructora de la escena
SelectLevelState::SelectLevelState(Application* app) : GameState(app){
	gm_ = GameManager::instance();
	initState();
}

//Inicia el estado
void SelectLevelState::initState() {
	SDL_ShowCursor(SDL_ENABLE);

	//Añadimos la mesa de fondo
	table_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Table));
	addRenderUpdateLists(table_);

	//Muestra el mapa en funcion de las islas desbloqueadas
	if (gm_->getUnlockedIslands() == Island::Caribbean) {
		map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map1));
	}
	else if (gm_->getUnlockedIslands() == Island::Spooky) {
		map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map2));
	}
	else if (gm_->getUnlockedIslands() == Island::Volcanic) {
		map_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Map3));
	}
	addRenderUpdateLists(map_);

	//Creamos los botones
	createButtons();
}

void SelectLevelState::createButtons()
{
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();
	Vector2D scaleButton(winWidth / 6, winHeight / 15);

	//Boton Volver
	Vector2D posButton(scaleButton.getX() / 2, scaleButton.getY());
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backShip, this);

	//Imagen Isla Actual
	currIsland = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::IslaActualButton));
	currIsland->setScale(scaleButton);
	currIsland->setPos(buttonPosition_[(int)gm_->getCurrIsland()]);
	addRenderUpdateLists(currIsland);

	//Boton viajar isla 1 (Siempre está desbloqueada, solo se comprueba que no sea la isla actual)
	if (gm_->getCurrIsland() != Island::Caribbean) {
		Vector2D posButton1(buttonPosition_[(int)Island::Caribbean]);
		createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ViajarButton), posButton1, scaleButton, goToIsland1, this);
	}

	//Boton viajar isla 2 (Comprueba que esté desbloqueada, y que no sea la isla actual)
	if ((int)gm_->getUnlockedIslands() >= 1 && gm_->getCurrIsland() != Island::Spooky) {
		Vector2D posButton2(buttonPosition_[(int)Island::Spooky]);
		createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ViajarButton), posButton2, scaleButton, goToIsland2, this);
	}

	//Boton viajar isla 3 (Comprueba que esté desbloqueada, y que no sea la isla actual)
	if ((int)gm_->getUnlockedIslands() >= 2 && gm_->getCurrIsland() != Island::Volcanic) {
		Vector2D posButton3(buttonPosition_[(int)Island::Volcanic]);
		createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::ViajarButton), posButton3, scaleButton, goToIsland3, this);
	}
}

