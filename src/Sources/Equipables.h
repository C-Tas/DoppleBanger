#pragma once
#include "interactuable.h"
#include "Player.h"

using namespace std;
class Equipables: public interactuable
{
protected:
	string name_;
	Player* player_;


public:
	Equipables() {};

	virtual void OnEnabled() = 0;//Metodo que se utilizara cuando el objeto se equipe
	virtual void OnDisabled() = 0;//Metodo que se utiliza cuando el objeto se desEquipa
};

