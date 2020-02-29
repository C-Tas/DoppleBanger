#include "PauseState.h"
#include "MainMenuState.h"
#include "ControlsState.h"

void PauseState::goControlState() {
	//app_->getStateMachine()->pushState( ControlsState(app_));
};
void PauseState::goMainMenuState() {
	//app_->getStateMachine()->pushState( MainMenuState(app_));
};
void PauseState::backToGameState() {
	//app_->getStateMachine()->popState());

}