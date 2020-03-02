#include "PlayState.h"
#include "PauseState.h"
#include "SaveLoadState.h"
#include "InventoryState.h"
#include "SelectLevelState.h"
#pragma region ChangeState
void PlayState::goToPauseState() {
	app_->getStateMachine()->pushState(new PauseState(app_));

}
void PlayState::goToSaveGame() {
	app_->getStateMachine()->pushState( new SaveLoadState(app_));

}
void PlayState::goToInventoryState() {
	app_->getStateMachine()->pushState( new InventoryState(app_));

}
void PlayState::goToSelectState() {
	app_->getStateMachine()->pushState( new SelectLevelState(app_));

}
#pragma endregion

//Esta podria ser una clase padre de 3 clases que sean Island0 Island1 e Island2 de tal forma que al cambiar en SelectLevelState
// al hacer el pop de ese estado no de problemas de ejecucion al tener que cambiar la isla o hacer metodos a los que llamar