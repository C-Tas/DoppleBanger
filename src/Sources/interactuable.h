#pragma once
#include "Collider.h"
class interactuable : public Collider
{
protected:
	///<summary>Metodo a redefinir en las clases hijas</summary>
	///<summary>Accion a realizar cuando se coge ese objeto</summary>
	virtual void pick() = 0;
public:

	
};

