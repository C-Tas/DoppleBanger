#include "StoryState.h"
#include "PlayState.h"
void StoryState::goToGame() {
	app_->getStateMachine()->changeState(new PlayState(app_));
}