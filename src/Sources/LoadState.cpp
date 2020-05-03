#include "LoadState.h"
#include "ShipState.h"

#include <fstream>

void LoadState::backToPreviousState(Application* app)
{
	app->getGameStateMachine()->popState();
}

void LoadState::loadSlot1(Application* app)
{
	app->getGameStateMachine()->changeState(new ShipState(app));
	GameManager::instance()->loadSlot1();
}

void LoadState::loadSlot2(Application* app)
{
	app->getGameStateMachine()->changeState(new ShipState(app));
	GameManager::instance()->loadSlot2();
}

void LoadState::loadSlot3(Application* app)
{
	app->getGameStateMachine()->changeState(new ShipState(app));
	GameManager::instance()->loadSlot3();
}

void LoadState::initState()
{
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::SaveLoadBackground));
	addRenderUpdateLists(background_);

	//Posicion y tamanyo en funcion del tamanyo de la ventana
	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D scaleButton(winWidth / 20, winHeight / 20);
	Vector2D posButton(scaleButton.getX(), scaleButton.getY());
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState); //Boton "Volver"

	//Botón partida 1
	scaleButton = Vector2D(winWidth / 3, winHeight / 7.5);
	posButton = Vector2D((winWidth / 3) - scaleButton.getX() / 2, winHeight / 4);
	ifstream slot("../Sources/save_data/save1.json");
	createLoadButton(slot, 1, posButton, scaleButton);

	//Botón partida 2
	posButton = posButton + Vector2D(0, winHeight / 4);
	slot = ifstream("../Sources/save_data/save2.json");
	createLoadButton(slot, 2, posButton, scaleButton);

	//Botón partida 3
	posButton = posButton + Vector2D(0, winHeight / 4);
	slot = ifstream("../Sources/save_data/save3.json");
	createLoadButton(slot, 3, posButton, scaleButton);
}

void LoadState::createLoadButton(ifstream& slot, int numSlot, Vector2D pos, Vector2D scale)
{
	if (slot.fail()) {
		createButton(app_, app_->getTextureManager()->getTexture(Resources::LoadGameNull), pos, scale, nullptr);
	}
	else {
		switch (numSlot)
		{
			case 1:
				createButton(app_, app_->getTextureManager()->getTexture(Resources::LoadGame1), pos, scale, loadSlot1);
				break;
			case 2:
				createButton(app_, app_->getTextureManager()->getTexture(Resources::LoadGame2), pos, scale, loadSlot2);
				break;
			case 3:																				
				createButton(app_, app_->getTextureManager()->getTexture(Resources::LoadGame3), pos, scale, loadSlot3);
				break;
		}
	}
	slot.close();
}

