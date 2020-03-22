#include "PauseState.h"
#include "MainMenuState.h"
#include "ControlsState.h"


PauseState::PauseState(Application* app) : GameState(app) {
	
};

void PauseState::initState()
{
	//Creación de botones
	
}
void PauseState::goControlState(Application* app) {
	app->getStateMachine()->pushState( new ControlsState(app));
};

void PauseState::goMainMenuState(Application* app) {
	app->getStateMachine()->clearAllStateExceptFirst();
};


void PauseState::backToGameState(Application* app) {
	app->getStateMachine()->popState();

}