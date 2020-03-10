#pragma once
#include "interactuable.h"
#include "Player.h"
//#include "Inventory.h"

class Inventory;
class InventoryButton;

using namespace std;
class Equipable: public interactuable
{
protected:
	string name_;
	Player* player_;
	Inventory* inventory_;
	InventoryButton* inventoryButton_;
	
	
	


public:
	Equipable() {};

	virtual void OnEnabled() = 0;//Metodo que se utilizara cuando el objeto se equipe
	virtual void OnDisabled() = 0;//Metodo que se utiliza cuando el objeto se desEquipa
	InventoryButton* getButton() { return inventoryButton_; }
	
	
};

