#pragma once
#include "ShipState.h"
class tutorialState :
	public ShipState
{
public:
	tutorialState(Application* app) : ShipState(app) { 
		gm_ = GameManager::instance(); 
		gm_->activeTutorial();
		venancio_->setPos(TUTORIAL_POS);
	};
	~tutorialState() { }
	virtual void update();
	void currTaskSucess() { currTaskComplete_ = true; }
	bool isCurrTaskComplete() { return currTaskComplete_; }
	void currTaskincomplete() { currTaskComplete_ = false; }
private:
	//Botella
	GameManager* gm_ = nullptr;
	Vector2D bottlePos_;
	Vector2D dummyPos_;
	bool dummyCreated_ = false;
	bool bottleCreated_ = false;
	bool currTaskComplete_ = false;
	virtual void initState();
	void createBottle();
	void createDummy();
	
};

