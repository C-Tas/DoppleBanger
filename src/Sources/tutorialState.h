#pragma once
#include "ShipState.h"
#include "Gloves.h"
class tutorialState : public ShipState {
public:
	tutorialState(Application* app) : ShipState(app) {
		gm_ = GameManager::instance();
		gm_->activeTutorial();
		venancio_->setPos(TUTORIAL_POS);
		//gm_->setOnShip(false);
	};
	~tutorialState() {}
	virtual void update();
	void activeDummyCreation() { dummyCreated_ = false; }
	void currTaskSucess() { currTaskComplete_ = true; }
	void currTaskIncomplete() { currTaskComplete_ = false; }
	bool isCurrTaskComplete() { return currTaskComplete_; }
private:
	//Botella
	GameManager* gm_ = nullptr;
	Chest* chest = nullptr;
	Vector2D bottlePos_;
	Vector2D dummyPos_;
	bool dummyCreated_ = false;
	bool bottleCreated_ = false;
	bool chestCreated_ = false;
	bool goldWasted_ = false;
	bool currTaskComplete_ = false;
	void createBottle();
	void createDummy();
	void createChest();
	//Constantes
	const int POTION_COST = 250;
};