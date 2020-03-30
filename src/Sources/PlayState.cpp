#include "PlayState.h"
#include "PauseState.h"
#include "SaveLoadState.h"
#include "InventoryState.h"
#include "SelectLevelState.h"
#include "StashState.h"
#include "Collisions.h"
#include "PauseState.h"
#include "EndState.h"

void PlayState::update() {
	//collisionCtrl_->islandCollisions();
		GameState::update();
		checkPlayerActions();
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
	else if (eventHandler_->isKeyDown(SDLK_p)) {
		app_->getGameStateMachine()->pushState(new PauseState(app_));
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

Enemy* PlayState::findClosestEnemy(Point2D pos) {
	Enemy* obj = nullptr;
	auto it = enemies_.begin(); if (enemies_.begin() != enemies_.end()) { obj = (*it); ++it; }
	for (; it != enemies_.end(); ++it)
		if (abs(Vector2D((*it)->getPos().getX() - pos.getX(), (*it)->getPos().getY() - pos.getY()).magnitude()) <
			abs(Vector2D(obj->getPos().getX() - pos.getX(), obj->getPos().getY() - pos.getY()).magnitude()))
			obj = (*it);

	return obj;
}

Enemy* PlayState::collidesWithEnemy(Point2D pos, Vector2D scale) {
	bool found = false;
	Enemy* obj = nullptr;
	for (auto it = enemies_.begin(); !found && it != enemies_.end(); ++it) {
		if (Collisions::collides(pos, scale.getX(), scale.getY(), (*it)->getPos(), (*it)->getScaleX(), (*it)->getScaleY()))
		{
			obj = (*it);
			found = true;
		}
	}

	return obj;
}

#pragma region ChangeState
void PlayState::goToPauseState(Application* app) {
	app->getGameStateMachine()->pushState(new PauseState(app));
}

void PlayState::goToInventoryState(Application* app) {
	app->getGameStateMachine()->pushState( new InventoryState(app));

}
#pragma endregion

//Esta podria ser una clase padre de 4 clases que sean Ship, Island0, Island1 e Island2 de tal forma que al cambiar en SelectLevelState
// al hacer el pop de ese estado no de problemas de ejecucion al tener que cambiar la isla o hacer metodos a los que llamar