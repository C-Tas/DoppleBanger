#include "tutorialState.h"
#include "tutorialObject.h"
#include "Chest.h"
#include "InventoryButton.h"
#include "ShopState.h" 
#include "usable.h"
#include "HUD.h"
#include "TutoTask.h"

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
			//USABILIDAD
			timest = std::chrono::duration_cast<std::chrono::seconds>(
				std::chrono::system_clock::now().time_since_epoch()).count();
			tutoTask1 = (TutoTask*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::TutoTask));
			tutoTask1->setName("Aprender a disparar.");
			createBottle();
		}
		break;
		//Aprender el ataque a melee
	case 2:
		//USABILIDAD
		timeOut = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask1->setTimeOut(timeOut);
		Tracker::TrackEvent(tutoTask1);

		//crear dummy
		if (!dummyCreated_) {
			//USABILIDAD
			timest = std::chrono::duration_cast<std::chrono::seconds>(
				std::chrono::system_clock::now().time_since_epoch()).count();
			tutoTask2 = (TutoTask*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::TutoTask));
			tutoTask2->setName("Aprender ataque melee.");

			createDummy();
			HUD* hud = new HUD(app_);
			addRenderUpdateLists(hud);
		}
		break;
		//Apreder a usar habilidades
	case 3:
		//USABILIDAD
		timeOut = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask2->setTimeOut(timeOut);
		Tracker::TrackEvent(tutoTask2);

		//USABILIDAD
		timest = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask3 = (TutoTask*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::TutoTask));
		tutoTask3->setName("Aprender a usar habilidades.");
		//crear dummy
		if (!dummyCreated_) {

			gm_->setMeleePoints(gm_->getMeleePoints() + (gm_->getMaxPoints() / 3) - 10);
			createDummy();
		}
		break;
	
	//Aprender los cofres
	case 4:
		//USABILIDAD
		timeOut = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask3->setTimeOut(timeOut);
		Tracker::TrackEvent(tutoTask3);

		//crear cofre con oro
		if (!chestCreated_) {
			//USABILIDAD
			timest = std::chrono::duration_cast<std::chrono::seconds>(
				std::chrono::system_clock::now().time_since_epoch()).count();
			tutoTask4 = (TutoTask*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::TutoTask));
			tutoTask4->setName("Aprender los cofres.");

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
		//USABILIDAD
		timeOut = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask4->setTimeOut(timeOut);
		Tracker::TrackEvent(tutoTask4);

		//USABILIDAD
		timest = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
		tutoTask5 = (TutoTask*)(Tracker::CreateNewEvent(timest, "a", "a", (int)EventInfo::EventType::TutoTask));
		tutoTask5->setName("Aprender sobre pociones.");

		if (gm_->getInventoryGold() > 0 && !goldWasted_) {
			goldWasted_ = true;
		}
		else if (goldWasted_ && gm_->getInventory()->empty() && gm_->getStash()->empty() && gm_->getObjectEquipped(Key::One) == ObjectName::Unequipped &&
			gm_->getObjectEquipped(Key::Two) == ObjectName::Unequipped && gm_->getInventoryGold() < 50)
		{
			GameManager::instance()->nextPhaseVenancio();
			//USABILIDAD
			timeOut = std::chrono::duration_cast<std::chrono::seconds>(
				std::chrono::system_clock::now().time_since_epoch()).count();
			tutoTask5->setTimeOut(timeOut);
			Tracker::TrackEvent(tutoTask5);
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