#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	//establecemos el objetivo para poder parar al llegar
	obj_.setVec(target);
	//establecemos la direccion
	dir_.setX(target.getX() - visPos_.getX());
	dir_.setY(target.getY() - visPos_.getY());
	dir_.normalize();
}