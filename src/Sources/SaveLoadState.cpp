#include "SaveLoadState.h"
#include "MainMenuState.h"

void backShipp(Application* app) {
	app->getGameStateMachine()->popState();
}

void SaveLoadState::goToGame(){
	app_->getGameStateMachine()->popState();

}
//mirar
void SaveLoadState::goToMainMenu() {
	app_->getGameStateMachine()->changeState(	new MainMenuState(app_));
	//AGUS
	//app_->getStateMachine()->changeState(	MainMenuState(app_));

	//OSCAR
	//app_->getStateMachine()->popState(); //Osea goToGame();
	//app_->getStateMachine()->popState(); //Debajo de PlayState siempre está el Main, el estado más bajo en la pila, creo que es mejor volver a ese en vez de crear otro
}

void SaveLoadState::initState()
{
	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), Vector2D(app_->getWindowWidth() / 2, app_->getWindowHeight() / 2),
		Vector2D(300, 300), backShipp);
}
