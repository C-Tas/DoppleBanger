#include "SaveState.h"
#include "GameManager.h"

void SaveState::backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState();
}

void SaveState::saveGame1() {
	GameManager::instance()->saveGame1();
}
void SaveState::saveGame2() {
	GameManager::instance()->saveGame2();
}
void SaveState::saveGame3() {
	GameManager::instance()->saveGame3();
}

void SaveState::initState()
{
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
	createButton2(saveGame1, app_, app_->getTextureManager()->getTexture(Resources::SaveGame1), posButton, scaleButton);

	//Botón partida 2
	posButton = posButton + Vector2D(0, winHeight / 4);
	createButton2(saveGame2, app_, app_->getTextureManager()->getTexture(Resources::SaveGame2), posButton, scaleButton);

	//Botón partida 3
	posButton = posButton + Vector2D(0, winHeight / 4);
	createButton2(saveGame3, app_, app_->getTextureManager()->getTexture(Resources::SaveGame3), posButton, scaleButton);
}
