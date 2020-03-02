#include "StashState.h"
void StashState::backToPrevious() {
	app_->getStateMachine()->popState();
}