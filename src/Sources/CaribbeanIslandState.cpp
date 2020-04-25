#include "CaribbeanIslandState.h"
#include "Player.h"
#include "ShipState.h"
#include "MonkeyCoco.h"
#include "EnemyPirate.h"
#include "Wolf.h"
#include "EndState.h"
#include "WinState.h"
#include "Chest.h"
#include "Kraken.h"

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

void CaribbeanIslandState::addMissionConter() {
	missionCounter++;
	if (missionCounter == NUM_WOLVES) gm_->setCompleteMission(missions::gallegaEnProblemas);
}

void CaribbeanIslandState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();

	background_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::CaribbeanMap));
	addRenderUpdateLists(background_);

	/*createMonkey(NUM_MONKEYS);
	createChest(NUM_CHEST);*/
	createPirates(NUM_PIRATES);
	createWolves(NUM_WOLVES);

	//Creamos la misión secundaria si no se ha completado aún
	if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) {
		//Reiniciamos el contador de muertes para cumplir la misión y creamos el NPC
		gm_->setStartedMission(missions::gallegaEnProblemas, true);
		missionCounter = 0;
		missionPass = false;
		createNPC();
	}

	//Kraken Temporal
	/*int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	Kraken* newKraken;
	Vector2D pos;
	
	app_->getWindowHeight() / 15;
	pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
	newKraken = new Kraken(app_, pos, Vector2D(app_->getWindowWidth() / 5, app_->getWindowHeight() / 3));
	addEnemy(newKraken);*/

	//Siempre se a�ade el ultimo para que se renderice por encima de los demas objetos
	playerEntry_ = Vector2D((app_->getWindowWidth() * 5 / 8) - W_PLAYER, (app_->getWindowHeight() * 8 / 10) - H_PLAYER);
	player_->setPos(playerEntry_);
	player_->setScale({ (double)W_PLAYER,(double)H_PLAYER });
	addRenderUpdateLists(player_);
	addRenderUpdateLists(hud_);
}

void CaribbeanIslandState::createMonkey(int numMonkeys)
{
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	MonkeyCoco* newMonkey;
	Vector2D pos;
	for (int i = 0; i < numMonkeys; i++) {
		pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
		newMonkey = new MonkeyCoco(app_, pos, Vector2D(W_MONKEY, H_MONKEY));
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
		newPirate = new EnemyPirate(app_, pos, Vector2D(W_MONKEY, H_MONKEY), patrol);
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
		newWolf = new Wolf(app_, pos, Vector2D(W_MONKEY, H_MONKEY), patrol);
		addEnemy(newWolf);
	}
}

void CaribbeanIslandState::createChest(int numChest) 
{
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	Chest* newChest;
	Vector2D pos;
	for (int i = 0; i < numChest; i++) {
		pos.setVec(Vector2D(app_->getRandom()->nextInt(wWin / 2, wWin), app_->getRandom()->nextInt(0, hWin / 2)));
		newChest = new Chest(app_, pos, Vector2D(W_CHEST, H_CHEST));
		addRenderUpdateLists(newChest);
		addObject(newChest);
	}
}

void CaribbeanIslandState::createNPC() {
	int wWin = app_->getWindowWidth();
	int hWin = app_->getWindowHeight();
	NPC* chef;
	Vector2D pos;
	pos.setVec(Vector2D(wWin / 2, hWin * 3 / 4));
	chef = new NPC(app_, app_->getTextureManager()->getTexture(Resources::Cooker), pos, Vector2D(app_->getWindowWidth() / 20, app_->getWindowHeight() / 8), 2);
	addRenderUpdateLists(chef);
	addObject(chef);
}