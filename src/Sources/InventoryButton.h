#pragma once
#include "Button.h"
#include <list>
using namespace std;

class Item;
class Equipment;
class usable;
//Este class de InventoryButton en InventoryButton es necesario, no borrar
//Sin esto no funciona el Callback :O
class InventoryButton;
using CallBackOnClickInventory = void(Application* app, InventoryButton* button);

class InventoryButton: public Button
{
private:
	list <InventoryButton*> ::iterator inventoryIterator_ ;
	Item* object_ = nullptr;
	bool equipped = false;
	CallBackOnClickInventory* callBackInventory_ = nullptr;
	virtual void initObject();
	void initTextureEquipment();
	void initTextureUsable();
public:

	InventoryButton(Application* app, Vector2D pos, Vector2D scale, Item* ob, CallBackOnClickInventory* callBack, bool equip = false, int id = 0)
		: Button(app, nullptr, pos, scale, nullptr, id), object_(ob), equipped(equip) {
		callBackInventory_ = callBack;
		initObject();
	}
	virtual bool update();
	bool isEquipped() { return equipped; }
	void Enable(bool e) { equipped = e; }
	virtual ~InventoryButton() {
		if(!equipped) delete object_;};

	//iterator
	void setIterator(list <InventoryButton*> ::iterator iterator) { inventoryIterator_ = iterator; }
	list <InventoryButton*> ::iterator getIterator() { return inventoryIterator_; }

	//Object
	void setObject(Equipment* ob);
	Item* getObject() { return object_; }
	void setNewCallBack(CallBackOnClickInventory* newCallBack) { callBackInventory_ = newCallBack; };
};
