#include "SaveLoadState.h"
#include "MainMenuState.h"

void SaveLoadState::goToGame(Application* app){
	SDL_ShowCursor(SDL_DISABLE);
	app->getGameStateMachine()->popState();
}
//mirar
void SaveLoadState::goToMainMenu() {
	app_->getGameStateMachine()->changeState(new MainMenuState(app_));
	//AGUS
	//app_->getStateMachine()->changeState(	MainMenuState(app_));

	//OSCAR
	//app_->getStateMachine()->popState(); //Osea goToGame();
	//app_->getStateMachine()->popState(); //Debajo de PlayState siempre está el Main, el estado más bajo en la pila, creo que es mejor volver a ese en vez de crear otro
}

void SaveLoadState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);

	createButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), Vector2D(0, 0), Vector2D(100, 100), goToGame);
}
