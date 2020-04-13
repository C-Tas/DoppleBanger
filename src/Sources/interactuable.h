#pragma once
#include "Collider.h"
class interactuable : public Collider
{
protected:

	interactuable(Application* app, Point2D pos, Vector2D scale) :
		Collider(app, pos, scale) { };
	virtual ~interactuable() {};
	///<summary>Metodo a redefinir en las clases hijas</summary>
	///<summary>Accion a realizar cuando se coge ese objeto</summary>
	virtual void pick() = 0;
public:

	
};

