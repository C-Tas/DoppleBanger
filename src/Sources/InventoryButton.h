#pragma once
#include "Button.h"
#include "interactuable.h"
#include <list>
using namespace std;
using CallBackOnClick = void();

class InventoryButton: public Button
{
private:
	list <InventoryButton> ::iterator inventoryIterator_ ;
	interactuable* object_;

public:

	InventoryButton(Texture* texture, Vector2D pos, Vector2D scale, interactuable* ob, CallBackOnClick* callBack);
	//iterator
	void setIterator(list <InventoryButton> ::iterator iterator) { inventoryIterator_ = iterator; }
	list <InventoryButton> ::iterator getIterator() { return inventoryIterator_; }

	//Object
	void setObject(interactuable* ob) { object_ = ob; }
	interactuable* getObject() { return object_; }




};

