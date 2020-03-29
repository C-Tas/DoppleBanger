#include "InventoryState.h"
void InventoryState::goToGame() {
	app_->getGameStateMachine()->popState();
}
