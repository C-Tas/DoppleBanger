#include "tutorialState.h"
#include "tutorialObject.h"
#include "Chest.h"
#include "InventoryButton.h"
#include "ShopState.h" 

void tutorialState::update()
{
	ShipState::update();
	collisionCtrl_->tutorialCollision();
	//Control de tutorial
	switch (gm_->getVenancioPhase())
	{
	//Aprender a disparar
	case 1:
		//crear botella
		if (!bottleCreated_) {
			createBottle();
		}
		break;
	//Aprender el ataque a melee
	case 2:
		//crear dummy
		if (!dummyCreated_) {
			createDummy();
		}
		break;
	//Apreder a usar habilidades
	case 3:
		//crear dummy
		if (!dummyCreated_) {
			gm_->setMeleePoints((gm_->getMaxPoints() / 3) - 10);
			createDummy();
		}
		break;
	//Aprender los cofres
	case 4:
		//crear cofre
		if (!chestCreated_) {
			createChest();
		}
		if (static_cast<Chest*>(chest) == nullptr) {
			//crear objeto en la tienda
			GameManager::instance()->nextPhaseVenancio();
		}
		break;
	//Aprender sobre pociones
	case 5:
		//Vende objetos en la tienda 
		if (GameManager::instance()->getInventoryGold() > 200) {

			GameManager::instance()->nextPhaseVenancio();
		}
		break;
	default:
		break;
	}
}


void tutorialState::createBottle()
{
	bottleCreated_ = true;
	app_->getWindowHeight() / 7;
	bottlePos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() / 7);
	tutorialObject* bottle = new tutorialObject(app_, bottlePos_, Vector2D(50, 60), app_->getTextureManager()->getTexture(Resources::Bottle),1);
	collisionCtrl_->setBottle(bottle);
	dynamic_cast<PlayState*>(app_->getCurrState())->addEnemy(bottle);
	collisionCtrl_->addEnemy(bottle);
}

void tutorialState::createDummy()
{
	dummyCreated_ = true;
	app_->getWindowHeight() / 7;
	dummyPos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() * 7 / 10 );
	tutorialObject* dummy = new tutorialObject(app_, dummyPos_, Vector2D(100, 100), app_->getTextureManager()->getTexture(Resources::Dummy),2);
	collisionCtrl_->setDummy(dummy);
	addEnemy(dummy);
	collisionCtrl_->addEnemy(dummy);
}

void tutorialState::createChest()
{
	chestCreated_ = true;
	Chest* chest = new Chest(app_,dummyPos_,Vector2D(150,150), 50);
	collisionCtrl_->addChest(chest);
	addRenderUpdateLists(chest);
}