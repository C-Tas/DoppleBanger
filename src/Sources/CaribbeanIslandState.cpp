#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "MonkeyCoco.h"
#include "EnemyPirate.h"
#include "EndState.h"
#include "WinState.h"

void backShipCaribbean(Application* app) {
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void CaribbeanIslandState::update()
{
	if (kills >= (numMonkeys_ + numPirates_)) {
		cout << kills << endl;
		collisionCtrl_->clearLists();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
	else if (player_->getStats().health_ > 0) {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
	else {
		collisionCtrl_->clearLists();
		app_->getGameStateMachine()->changeState(new EndState(app_));
	}
}


void CaribbeanIslandState::initState()
{
	collisionCtrl_ = CollisionCtrl::instance();
	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::CaribbeanMap));
	addRenderUpdateLists(background_);

	createMonkey(numMonkeys_);
	createPirates(numPirates_);

	//Siempre se añade el último para que se renderice por encima de los demás objetos
	playerEntry_ = Vector2D(((app_->getWindowWidth() * 5/8)- wPlayer), ((app_->getWindowHeight() * 8 / 10) - hPlayer));
	player_ = new Player(app_, playerEntry_, Vector2D(wPlayer, hPlayer));
	addRenderUpdateLists(player_);
}

void CaribbeanIslandState::createMonkey(int numMonkeys)
{
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	MonkeyCoco* newMonkey;
	Vector2D pos;
	for (int i = 0; i < numMonkeys; i++) {
		pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
		newMonkey = new MonkeyCoco(app_, pos, Vector2D(wMonkey, hMonkey));
		addRenderUpdateLists(newMonkey);
	}
}

void CaribbeanIslandState::createPirates(int numPirates)
{
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	vector<Point2D> patrol;
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });

	EnemyPirate* newPirate;
	Vector2D pos;
	for (int i = 0; i < numPirates; i++) {
		pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
		newPirate = new EnemyPirate(app_, pos, Vector2D(wMonkey, hMonkey), patrol);
		addRenderUpdateLists(newPirate);
	}
}