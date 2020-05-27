#include "tutorialState.h"
#include "tutorialObject.h"
#include "Chest.h"
#include "InventoryButton.h"
#include "ShopState.h" 
#include "usable.h"
#include "HUD.h"

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
			HUD* hud = new HUD(app_);
			addRenderUpdateLists(hud);
		}
		break;
	//Apreder a usar habilidades
	case 3:
		//crear dummy
		if (!dummyCreated_) {
			gm_->setMeleePoints(gm_->getMeleePoints() + (gm_->getMaxPoints() / 3) - 10);
			createDummy();
		}
		break;
	//Aprender los cofres
	case 4:
		//crear cofre con oro
		if (!chestCreated_) {
			createChest();
		}
		else {
			//crear potion en la tienda
			usable* potion = new usable(app_, potionType::Mana);
			//Gloves* gloves = new Gloves(app_, 50, 50, 12, equipType::GlovesI);
			InventoryButton* item = new InventoryButton(app_, { 0,0 }, { 100,100 }, potion, ShopState::callbackSelectObject, false, 1);
			auto aux = gm_->getShop();
			item->setIterator(aux->insert(aux->end(), item));
			GameManager::instance()->nextPhaseVenancio();
		}
		break;
	//Aprender sobre pociones
	case 5:
		if (gm_->getInventoryGold() > 0 && !goldWasted_) {
			goldWasted_ = true;
		}
		else if (goldWasted_ && gm_->getInventory()->empty() && gm_->getStash()->empty() && gm_->getObjectEquipped(Key::One) == ObjectName::Unequipped &&
			gm_->getObjectEquipped(Key::Two) == ObjectName::Unequipped && gm_->getInventoryGold() < 50)
		{
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
	bottlePos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() / 7);
	tutorialObject* bottle = new tutorialObject(app_, bottlePos_, Vector2D(50, 60), app_->getTextureManager()->getTexture(Resources::Bottle),1);
	collisionCtrl_->setBottle(bottle);
	dynamic_cast<PlayState*>(app_->getCurrState())->addEnemy(bottle);
	collisionCtrl_->addEnemy(bottle);
}

void tutorialState::createDummy()
{
	dummyCreated_ = true;
	dummyPos_ = Vector2D(app_->getWindowWidth() / 3, app_->getWindowHeight() * 7 / 10);
	tutorialObject* dummy = new tutorialObject(app_, dummyPos_, Vector2D(100, 100), app_->getTextureManager()->getTexture(Resources::Dummy),2);
	collisionCtrl_->setDummy(dummy);
	addEnemy(dummy);
	collisionCtrl_->addEnemy(dummy);
}

void tutorialState::createChest()
{
	chestCreated_ = true;
	Chest* chest = new Chest(app_, Vector2D(app_->getWindowWidth() * 2 / 3, app_->getWindowHeight() / 6), Vector2D(150,150), 100);
	//collisionCtrl_->addChest(chest);
	addRenderUpdateLists(chest);
}