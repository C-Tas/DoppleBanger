#include "InventoryState.h"
void InventoryState::goToGame() {
	app_->getStateMachine()->popState();
}
