#include "PlayState.h"
#include "PauseState.h"
#include "SaveLoadState.h"
#include "InventoryState.h"
#include "SelectLevelState.h"
#include "StashState.h"

void PlayState::update() {
	checkPlayerActions();
	//Update de todos los objetos. En los botones que cambian estado devuelve true para dejar de updatear los objetos
	//de ese estado
	for (auto it = gameObjects_.begin(); it != gameObjects_.end(); ++it) {
		if ((*it)->update())return;
	}
}

void PlayState::addEnemy(Enemy* obj) {
	//Push front porque a suponiendo que dos enemigos se superpongan y se haga click en ellos para atacar,
	//se renderizan en un orden (el de objectsToRender) y por lo cual las comprobaciones deben hacerse en el contrario.
	enemies_.push_front(obj);
	addRenderUpdateLists(obj);
}

void PlayState::removeEnemy(Enemy* obj) {
	//Push front porque a suponiendo que dos enemigos se superpongan y se haga click en ellos para atacar,
	//se renderizan en un orden (el de objectsToRender) y por lo cual las comprobaciones deben hacerse en el contrario.
	enemies_.remove(obj);
	removeRenderUpdateLists(obj);
}

void PlayState::checkPlayerActions() {
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
	{
		Enemy* obj; obj = checkAttack();
		if (obj != nullptr) player_->attack(obj);
		//else if NPC
		else player_->move(eventHandler_->getMousePos());
	}
}

Enemy* PlayState::checkAttack() {
	bool found = false;
	Enemy* obj = nullptr;
	Vector2D mousePos = eventHandler_->getMousePos();
	SDL_Point mouse = { 0, 0 }; mouse.x = mousePos.getX(); mouse.y = mousePos.getY();
	for (auto it = enemies_.begin(); !found && it != enemies_.end(); ++it) {
		if (SDL_PointInRect(&mouse, &(*it)->getCollider())) {
			obj = (*it);
			found = true;
		}
	}
	return obj;
}

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