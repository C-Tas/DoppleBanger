#pragma once
#include "interactuable.h"
#include "Player.h"
#include "Inventory.h"

using namespace std;
class Equipable: public interactuable
{
protected:
	string name_;
	Player* player_;
	Inventory* inventory_;
	


public:
	Equipable() {};

	virtual void OnEnabled() = 0;//Metodo que se utilizara cuando el objeto se equipe
	virtual void OnDisabled() = 0;//Metodo que se utiliza cuando el objeto se desEquipa
	
};

