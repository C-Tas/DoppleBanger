#include "PlayState.h"
#include "PauseState.h"
#pragma region ChangeState
void PlayState::goToPauseState() {
	//app_->getStateMachine()->pushState( PauseState(app_));

}
void PlayState::goToSaveGame() {
	//app_->getStateMachine()->pushState( SaveLoadState(app_, false)); //TRUE => LOAD //FALSE => SAVE

}
void PlayState::goToInventoryState() {
	//app_->getStateMachine()->pushState( InventoryState(app_));

}
void PlayState::goToSelectState() {
	//app_->getStateMachine()->pushState( SelectLevelState(app_));

}
void PlayState::goToStashState()
{
	//app_->getStateMachine()->pushState( StashState(app_));
}
#pragma endregion

//Esta podria ser una clase padre de 4 clases que sean Ship, Island0, Island1 e Island2 de tal forma que al cambiar en SelectLevelState
// al hacer el pop de ese estado no de problemas de ejecucion al tener que cambiar la isla o hacer metodos a los que llamar