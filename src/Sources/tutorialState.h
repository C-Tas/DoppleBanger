#pragma once
#include "ShipState.h"
#include "Gloves.h"


class tutorialState : public ShipState {
public:
	tutorialState(Application* app);
	~tutorialState();
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
	
	//USABILIDAD
	TutoTask* tutoTask1 = nullptr;
	TutoTask* tutoTask2 = nullptr;
	TutoTask* tutoTask3 = nullptr;
	TutoTask* tutoTask4 = nullptr;
	TutoTask* tutoTask5 = nullptr;

	long long timest = 0;
	long long timeOut = 0;
};