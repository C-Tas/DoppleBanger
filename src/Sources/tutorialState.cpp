#include "tutorialState.h"
#include "tutorialObject.h"
#include "Chest.h"

void tutorialState::update()
{
	ShipState::update();
	collisionCtrl_->tutorialCollision();
	//Control de tutorial
	switch (gm_->getVenancioPhase())
	{
	case 1:
		//crear botella
		if (!bottleCreated_) {
			createBottle();
		}
		break;
	case 2:
		//crear dummy
		if (!dummyCreated_) {
			gm_->setSkillUnlocked(SkillName::GolpeFuerte);
			createDummy();
		}
		break;
	case 3:
		//crear cofre
		if (!chestCreated_) {
			
			createChest();
		}
		break;
	default:
		break;
	}
}

void tutorialState::initState() {}

void tutorialState::createBottle()
{
	bottleCreated_ = true;
	app_->getWindowHeight() / 7;
	bottlePos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() / 7);
	tutorialObject* bottle = new tutorialObject(app_, bottlePos_, Vector2D(50, 60), app_->getTextureManager()->getTexture(Resources::Bottle));
	collisionCtrl_->setBottle(bottle);
	dynamic_cast<PlayState*>(app_->getCurrState())->addEnemy(bottle);
	collisionCtrl_->addEnemy(bottle);
}

void tutorialState::createDummy()
{
	dummyCreated_ = true;
	app_->getWindowHeight() / 7;
	dummyPos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() * 7 / 10 );
	tutorialObject* dummy = new tutorialObject(app_, dummyPos_, Vector2D(100, 100), app_->getTextureManager()->getTexture(Resources::Dummy));
	collisionCtrl_->setDummy(dummy);
	addEnemy(dummy);
	collisionCtrl_->addEnemy(dummy);
}

void tutorialState::createChest()
{
	chestCreated_ = true;
	Chest* chest = new Chest(app_,dummyPos_,Vector2D(150,150));
	collisionCtrl_->addChest(chest);
	addRenderUpdateLists(chest);
}