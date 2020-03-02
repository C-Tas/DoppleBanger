#include "ControlsState.h"

void ControlsState::backToPreviousState() {
	app_->getStateMachine()->popState();
		
}