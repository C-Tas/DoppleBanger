#include "SaveState.h"
#include "GameManager.h"

void SaveState::backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState();
	SDL_ShowCursor(SDL_DISABLE);
}
void SaveState::saveSlot1() {
	GameManager::instance()->saveSlot1();
}
void SaveState::saveSlot2() {
	GameManager::instance()->saveSlot2();
}
void SaveState::saveSlot3() {
	GameManager::instance()->saveSlot3();
}

void SaveState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::SaveLoadBackground));
	addRenderUpdateLists(background_);

	//Posicion y tamanyo en funcion del tamanyo de la ventana
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D scaleButton(winWidth / 20, winHeight/ 20);
	Vector2D posButton(scaleButton.getX(), scaleButton.getY());
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState); //Boton "Volver"

	//Botón partida 1
	scaleButton = Vector2D(winWidth / 3, winHeight / 7.5);
	posButton = Vector2D((winWidth / 3) - scaleButton.getX() / 2, winHeight / 4);
	createBeerButton2(saveSlot1, app_, app_->getTextureManager()->getTexture(Resources::SaveGame1), posButton, scaleButton, this);

	//Botón partida 2
	posButton = posButton + Vector2D(0, winHeight / 4);
	createBeerButton2(saveSlot2, app_, app_->getTextureManager()->getTexture(Resources::SaveGame2), posButton, scaleButton, this);

	//Botón partida 3
	posButton = posButton + Vector2D(0, winHeight / 4);
	createBeerButton2(saveSlot3, app_, app_->getTextureManager()->getTexture(Resources::SaveGame3), posButton, scaleButton, this);
}
