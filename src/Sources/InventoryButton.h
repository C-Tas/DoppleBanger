#pragma once
#include "Button.h"
#include "Equipable.h"
#include <list>
using namespace std;
//using CallBackOnClickInventory = void(GameState* state, InventoryButton* button);
using CallBackOnClickInventory = void(GameState * state, Button * button);


class InventoryButton: public Button
{
private:
	list <InventoryButton*> ::iterator inventoryIterator_ ;
	Equipable* object_;
	bool equipped = false;
	CallBackOnClickInventory callBackInventory_;

public:

	InventoryButton(GameState* state,Texture* texture, Vector2D pos, Vector2D scale, Equipable* ob, CallBackOnClickInventory* callBack);
	virtual void update();
	bool isEquipped() { return equipped; }
	void Enable(bool e) { equipped = e; }

	//iterator
	void setIterator(list <InventoryButton*> ::iterator iterator) { inventoryIterator_ = iterator; }
	list <InventoryButton*> ::iterator getIterator() { return inventoryIterator_; }

	//Object
	void setObject(Equipable* ob) { object_ = ob; }
	Equipable* getObject() { return object_; }




};

