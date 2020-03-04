#include "PauseState.h"
#include "MainMenuState.h"
#include "ControlsState.h"

void PauseState::goControlState() {
	app_->getStateMachine()->pushState( new ControlsState(app_));
};
//mirar
void PauseState::goMainMenuState() {

	app_->getStateMachine()->clearAllStateExceptFirst();
};
void PauseState::backToGameState() {
	app_->getStateMachine()->popState();

}