#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	//establecemos el objetivo para poder parar al llegar
	obj_.setVec(target);
	dir_.setX(obj_.getX() - pos_.getX());
	dir_.setY(obj_.getY() - pos_.getY());
	dir_.normalize();
}