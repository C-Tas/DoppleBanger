#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"

void backShipCaribbean(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void CaribbeanIslandState::initState()
{
	collisionCtrl_ = CollisionCtrl::instance();
	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::CaribbeanMap));
	addRenderUpdateLists(background_);

	//Siempre se añade el último para que se renderice por encima de los demás objetos
	playerEntry_ = Vector2D(((app_->getWindowWidth() * 5/8)- wPlayer), ((app_->getWindowHeight() * 8 / 10) - hPlayer));
	player_ = new Player(app_, playerEntry_, Vector2D(wPlayer, hPlayer));
	addRenderUpdateLists(player_);
}

void CaribbeanIslandState::createCrab(int numCrabs)
{
	int wHalfWin = app_->getWindowWidth() / 2;
	int hHalfWin = app_->getWindowHeight() / 2;
	//Crab* newCrab;
	Vector2D pos;
	for (int i = 0; i < numCrabs; i++) {
		pos.setVec(Vector2D(rand() % wHalfWin * 2 + wHalfWin, rand() % hHalfWin * 2 + hHalfWin));
		//newCrab = new Crab(app_, pos, Vector2D(wCrab, hCrab));
	}
}