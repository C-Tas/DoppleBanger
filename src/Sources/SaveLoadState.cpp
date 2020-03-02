#include "SaveLoadState.h"
#include "MainMenuState.h"



void SaveLoadState::goToGame(){
	app_->getStateMachine()->popState();

}
//mirar
void SaveLoadState::goToMainMenu() {
	app_->getStateMachine()->changeState(	new MainMenuState(app_));
	//AGUS
	//app_->getStateMachine()->changeState(	MainMenuState(app_));

	//OSCAR
	//app_->getStateMachine()->popState(); //Osea goToGame();
	//app_->getStateMachine()->popState(); //Debajo de PlayState siempre está el Main, el estado más bajo en la pila, creo que es mejor volver a ese en vez de crear otro
}