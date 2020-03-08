#pragma once
#include "InventoryButton.h"
#include "GameState.h"
#include <list>
using namespace std;
struct Equipment
{
	InventoryButton* helmet_ = nullptr;
	InventoryButton* armor_ = nullptr;
	InventoryButton* boots_ = nullptr;
	InventoryButton* gloves_ = nullptr;
	InventoryButton* sword_ = nullptr;
	InventoryButton* gun_ = nullptr;

};

class Inventory: public GameState
{
private:
	Texture* background_;
	list<InventoryButton*> InventoryList_;
	Button* deleteButton_;
	Button* equippedButton_;
	Button* advanceButton_;
	Button* gobackButton_;
	Button* ExitButton_;
	
	InventoryButton* sellect_ = nullptr;
	list<InventoryButton>:: iterator ListPos;
	Equipment equipment_;
	//const int MAX_OBJECTS;

	//metodos privados
	void selectObject(InventoryButton* ob);
	void equippedObj();
	void deleteObj();
	void printInformation() {};
	
public:
	Inventory(Application* app = nullptr);
	void addToInventory(Equipable* ob);
	virtual void draw() const;
	virtual void update();
	

	

	

};

