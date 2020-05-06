#pragma once
#include "Magordito.h"

class MagorditoIA : public GameObject
{
public:
	MagorditoIA(Magordito* magordito) : magordito_(magordito) {};
	~MagorditoIA() {};
	//
	virtual bool update();
	virtual void initObject() {};
private:
	//Puntero al magordito
	Magordito* magordito_ = nullptr;
};

