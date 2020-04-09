#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "MonkeyCoco.h"
#include "EnemyPirate.h"
#include "Wolf.h"
#include "EndState.h"
#include "WinState.h"


void CaribbeanIslandState::update()
{
	if (enemies_.empty()) {
		collisionCtrl_->clearList();
		app_->getGameStateMachine()->changeState(new WinState(app_));
	}
	else {
		collisionCtrl_->islandCollisions();
		PlayState::update();
	}
}


void CaribbeanIslandState::initState()
{
	collisionCtrl_ = CollisionCtrl::instance();
	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::CaribbeanMap));
	addRenderUpdateLists(background_);

	createMonkey(numMonkeys_);
	createPirates(numPirates_);
	createWolves(numWolves);

	//Siempre se a�ade el �ltimo para que se renderice por encima de los dem�s objetos
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
		addEnemy(newMonkey);
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
		addEnemy(newPirate);
	}
}

void CaribbeanIslandState::createWolves(int numWolves)
{
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	vector<Point2D> patrol;
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });
	patrol.push_back({ (double)app_->getRandom()->nextInt(200,app_->getWindowWidth() - 200) , (double)app_->getRandom()->nextInt(200,app_->getWindowHeight() - 200) });

	Wolf* newWolf;
	Vector2D pos;
	for (int i = 0; i < numWolves; i++) {
		pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
		newWolf = new Wolf(app_, pos, Vector2D(wMonkey, hMonkey), patrol);
		addEnemy(newWolf);
	}
}