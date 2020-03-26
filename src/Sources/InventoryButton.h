#pragma once
#include "Button.h"
#include "Equipment.h"
#include <list>
using namespace std;
using CallBackOnClickInventory = void(GameState* state, InventoryButton* button);
//using CallBackOnClickInventory = void(GameState * state, Equipment * ob);


class InventoryButton: public Button
{
private:
	list <InventoryButton*> ::iterator inventoryIterator_ ;
	Equipment* object_;
	bool equipped = false;
	CallBackOnClickInventory* callBackInventory_;
	

public:

	InventoryButton(Application* app, GameState* state,Texture* texture, Vector2D pos, Vector2D scale, Equipment* ob, CallBackOnClickInventory* callBack);
	virtual bool update();
	bool isEquipped() { return equipped; }
	void Enable(bool e) { equipped = e; }
	virtual ~InventoryButton() {};

	//iterator
	void setIterator(list <InventoryButton*> ::iterator iterator) { inventoryIterator_ = iterator; }
	list <InventoryButton*> ::iterator getIterator() { return inventoryIterator_; }

	//Object
	void setObject(Equipment* ob) { object_ = ob; }
	Equipment* getObject() { return object_; }




};

