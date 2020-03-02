#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"

void MainMenuState::goControlState() {
	//app_->getStateMachine()->pushState( ControlsState(app_));
};
void MainMenuState::goCreditsState() {
	//app_->getStateMachine()->pushState( CreditsState(app_));
};
void MainMenuState::goLoadState() {
	//app_->getStateMachine()->pushState( SaveLoadState(app_));
};
void MainMenuState::goStoryState() {
	//app_->getStateMachine()->pushState( StoryState(app_));
};