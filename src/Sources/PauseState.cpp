#include "PauseState.h"
#include "MainMenuState.h"
#include "ControlsState.h"

void PauseState::goControlState() {
	//app_->getStateMachine()->pushState( ControlsState(app_));
};
void PauseState::goMainMenuState() {
	//AGUS
	//app_->getStateMachine()->changeState(	MainMenuState(app_));

	//OSCAR
	//app_->getStateMachine()->popState(); //Osea goToGame();
	//app_->getStateMachine()->popState(); //Debajo de PlayState siempre está el Main, el estado más bajo en la pila, creo que es mejor volver a ese en vez de crear otro
};
void PauseState::backToGameState() {
	//app_->getStateMachine()->popState());

}