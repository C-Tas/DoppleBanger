#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"

void MainMenuState::initMenuState()
{
	//meter botones etc..
	player_ = new Player(Vector2D(0.5, -0.5), new Texture(app_->getRenderer(), "../Sources/assets/timon.png"),
		&SDL_Rect({ 50,50,100,100 }), Vector2D(50, 50), Vector2D(50, 50), SDL_Rect({ 0,0,0,0 }));
	addUpdateList(player_);
	addRenderList(player_);
}

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