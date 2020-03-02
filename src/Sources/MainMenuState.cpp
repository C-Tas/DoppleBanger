#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"

void MainMenuState::goControlState() {
	app_->getStateMachine()->pushState( new ControlsState(app_));
};
void MainMenuState::goCreditsState() {
	app_->getStateMachine()->pushState( new CreditsState(app_));
};
void MainMenuState::goLoadState() {
	app_->getStateMachine()->pushState(new SaveLoadState(app_, true)); //TRUE => LOAD //FALSE => SAVE
};
void MainMenuState::goStoryState() {
	app_->getStateMachine()->pushState( new StoryState(app_));
};