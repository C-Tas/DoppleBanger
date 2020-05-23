#include "Collisions.h"
#include "PlayState.h"
#include "SelectLevelState.h"
#include "ShipState.h"
#include "StashState.h"
#include "PauseState.h"
#include "SkillState.h"
#include "ShopState.h"
#include "EndState.h"
#include "Inventory.h"
#include "HUD.h"
#include "conio.h"
#include "TestState.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"

void PlayState::draw() const {
	GameState::draw();
	collisionCtrl_->drawTextBox();
	mousePointer->draw();
}

void PlayState::update() {
	if (player_->getDead()) { //Comprobamos que el player haya muerto para cambiar de estado
		//Cargamos música de fondo
		app_->resetMusicChannels();
		app_->resetSoundsChannels();
		app_->getAudioManager()->playChannel(Resources::AudioId::FuneralTheme, -1, Resources::MainMusicChannel);
		app_->getGameStateMachine()->changeState(new EndState(app_));
	}
	else {
		updateMousePointer();
		GameState::update();
		checkPlayerActions();
	}
}

void PlayState::updateMousePointer() {
	point.x = eventHandler_->getRelativeMousePos().getX();
	point.y = eventHandler_->getRelativeMousePos().getY();
	mousePointer->setPos(Vector2D(point.x, point.y));

	bool found = false;
	for (auto it = objects_.begin(); !found && it != objects_.end(); ++it) {
		if (SDL_PointInRect(&point, &(*it)->getCollider())) {
			mousePointer->setTexture(app_->getTextureManager()->getTexture(Resources::GrabPointer));
			found = true;
		}
	}
	for (auto it = enemies_.begin(); !found && it != enemies_.end(); ++it) {
		if (SDL_PointInRect(&point, &(*it)->getCollider())) {
			mousePointer->setTexture(app_->getTextureManager()->getTexture(Resources::AttackPointer));
			found = true;
		}
	}
	if (!found) mousePointer->setTexture(app_->getTextureManager()->getTexture(Resources::MovementPointer));
}

void PlayState::addEnemy(Enemy* obj) {
	//Push front porque a suponiendo que dos enemigos se superpongan y se haga click en ellos para atacar,
	//se renderizan en un orden (el de objectsToRender) y por lo cual las comprobaciones deben hacerse en el contrario.
	enemies_.push_front(obj);
	addRenderUpdateLists(obj);
}


void PlayState::addObject(Collider* obj) {
	objects_.push_back(obj);
}

void PlayState::removeEnemy(Enemy* obj) {
	//Push front porque a suponiendo que dos enemigos se superpongan y se haga click en ellos para atacar,
	//se renderizan en un orden (el de objectsToRender) y por lo cual las comprobaciones deben hacerse en el contrario.
	enemies_.remove(obj);
}

void PlayState::removeObject(Collider* obj) {
	objects_.remove(obj);
}

void PlayState::checkPlayerActions() {
	if (eventHandler_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT))
	{
		Enemy* obj; obj = checkAttack();
		player_->updateDirVisMouse();
		if (obj != nullptr) {
			player_->attack(obj);
		}
		else if (!player_->getOnCollision()) {
			player_->move(eventHandler_->getRelativeMousePos());
		}
		else player_->setOnCollision(false);

		if (collisionCtrl_->isNextZoneTextBoxActive())player_->getEndZoneTextBox()->updateButtons();
	}
	else if (eventHandler_->isKeyDown(SDLK_p)) {
		app_->getGameStateMachine()->pushState(new PauseState(app_));
		player_->stop();
	}
	else if (eventHandler_->isKeyDown(SDLK_c)) {
		app_->getGameStateMachine()->pushState(new Inventory(app_));
		player_->stop();
	}
	else if (eventHandler_->isKeyDown(SDLK_v)) {
		app_->getGameStateMachine()->pushState(new SkillState(app_, player_));
		player_->stop();
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

Enemy* PlayState::getEnemyByTag(string tag)
{
	for (auto i = enemies_.begin(); i != enemies_.end(); i++) {
		auto aux = dynamic_cast<Enemy*>(*(i));
		if (aux != nullptr && aux->getTag() == tag) {
			return aux;
		}
	}
}

void PlayState::swapRenders(GameObject* obj, GameObject* other)
{
	for (auto i = objectsToRender_.begin(); i != objectsToRender_.end(); i++) {
		if ((*i) == obj) {
			for (auto e = objectsToRender_.begin(); e != objectsToRender_.end(); e++) {
				if ((*e) == other) {
					auto aux = (*i);
					(*i) = (*e);
					(*e) = aux;
					return;
				}
			}
		}
	}
}

void PlayState::deleteExceptHUD(Zone newZone)
{
	gm_->setCurrentPlayerLife(player_->getHealth());
	gm_->setCurrentPlayerMana(player_->getMana());
	gm_->setCurrentZone(newZone);
	for (auto i = gameObjects_.begin(); i != --gameObjects_.end(); ++i) {
		removeUpdateList(*(i));
	}
	gameObjects_.clear();
	objectsToRender_.clear();
}

void PlayState::initState()
{
	generator_ = new AStar::Generator();
	//Desactivamos el puntero para poder renderizar los punteros del juego
	SDL_ShowCursor(SDL_DISABLE);
	//Creamos nuestro nuevo puntero
	mousePointer = new Draw(app_, app_->getTextureManager()->getTexture(Resources::MovementPointer));
	mousePointer->setScale(Vector2D(W_MOUSE_POINTER, H_MOUSE_POINTER));

	collisionCtrl_ = CollisionCtrl::instance();
	generator_->setHeuristic(AStar::Heuristic::euclidean);
	generator_->setDiagonalMovement(false);
}

void PlayState::resetGame()
{
	//Se pierde el oro
	gm_->setInventoryGold(0);
	//Se resetea el inventario
	gm_->resetInventory();
	//Se limpia la lista de colisiones
	collisionCtrl_->clearList();
	//Se vuelve a tener que empezar desde la zona inicial de la isla en la que nos encontremos
	gm_->resetIsland();
	//Se reinicia la partida en el barco
	app_->getGameStateMachine()->changeState(new ShipState(app_));
}
