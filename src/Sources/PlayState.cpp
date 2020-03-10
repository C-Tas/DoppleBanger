#include "PlayState.h"
#include "PauseState.h"
#include "SaveLoadState.h"
#include "InventoryState.h"
#include "SelectLevelState.h"
#include "StashState.h"
#pragma region ChangeState
void PlayState::goToPauseState(Application* app) {
	app->getStateMachine()->pushState(new PauseState(app));

}
void PlayState::goToSaveGame(Application* app) {
	app->getStateMachine()->pushState(new SaveLoadState(app, false)); //TRUE => LOAD //FALSE => SAVE
}
void PlayState::goToInventoryState(Application* app) {
	app->getStateMachine()->pushState( new InventoryState(app));

}
void PlayState::goToSelectState(Application* app) {
	app->getStateMachine()->pushState( new SelectLevelState(app));

}
void PlayState::goToStashState(Application* app)
{
	app->getStateMachine()->pushState( new StashState(app));
}
#pragma endregion

//Esta podria ser una clase padre de 4 clases que sean Ship, Island0, Island1 e Island2 de tal forma que al cambiar en SelectLevelState
// al hacer el pop de ese estado no de problemas de ejecucion al tener que cambiar la isla o hacer metodos a los que llamar