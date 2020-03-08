#pragma once
#include "InventoryButton.h"
#include "GameState.h"
#include <list>
using namespace std;


class Inventory: public GameState
{
private:
	Texture* background_;
	list<InventoryButton> InventoryList_;
	struct Equipped
	{
		InventoryButton* helmet_;
		InventoryButton* armor_;
		InventoryButton* boots_;
		InventoryButton* gloves_;
		InventoryButton* sword_;
		InventoryButton* gun_;

	};
	InventoryButton* sellect_;
	list<InventoryButton>:: iterator ListPos;

	

	

};

