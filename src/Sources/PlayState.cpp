#include "Collisions.h"
#include "PlayState.h"
#include "SaveLoadState.h"
#include "SelectLevelState.h"
#include "EndState.h"
#include "StashState.h"
#include "PauseState.h"
#include "SkillState.h"
#include "Inventory.h"


void PlayState::update() {
	if (player_->getState() == STATE::DYING) { //Comprobamos que el player haya muerto para cambiar de estado
		collisionCtrl_->clearList();
		app_->getGameStateMachine()->changeState(new EndState(app_));
	}
	else {
		GameState::update();
		checkPlayerActions();
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
}

void PlayState::checkPlayerActions() {	
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
	{
		Enemy* obj; obj = checkAttack();
		if (obj != nullptr) {
			player_->attack(obj);
		}
		//else if NPC
		else player_->move(eventHandler_->getRelativeMousePos());
	}
	else if (eventHandler_->isKeyDown(SDLK_p)) {
		app_->getGameStateMachine()->pushState(new PauseState(app_));
	}
	else if (eventHandler_->isKeyDown(SDLK_c)) {
		app_->getGameStateMachine()->pushState(new Inventory(app_));
	}
	else if (eventHandler_->isKeyDown(SDLK_v)) {
		app_->getGameStateMachine()->pushState(new SkillState(app_));
	}

}

Enemy* PlayState::checkAttack() {
	bool found = false;
	Enemy* obj = nullptr;
	Vector2D mousePos = eventHandler_->getRelativeMousePos();
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

void PlayState::initState()
{
	collisionCtrl_ = CollisionCtrl::instance();
	player_ = new Player(app_, Vector2D(0, 0), Vector2D(0, 0));
}
