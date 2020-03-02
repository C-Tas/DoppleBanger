#include "CreditsState.h"

void CreditsState::backToPreviousState() {
	app_->getStateMachine()->popState();
}
