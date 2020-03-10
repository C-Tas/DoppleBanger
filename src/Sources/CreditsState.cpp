#include "CreditsState.h"

void CreditsState::backToPreviousState(Application* app) {
	app->getStateMachine()->popState();
}
