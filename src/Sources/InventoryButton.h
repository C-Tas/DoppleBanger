#pragma once
#include "Button.h"
#include "Equipable.h"
#include <list>
using namespace std;
using CallBackOnClick = void(InventoryButton* button);

class InventoryButton: public Button
{
private:
	list <InventoryButton*> ::iterator inventoryIterator_ ;
	Equipable* object_;
	bool equipped = false;

public:

	InventoryButton(Texture* texture, Vector2D pos, Vector2D scale, Equipable* ob, CallBackOnClick* callBack);
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

