#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(target);
	dir_.setX(target_.getX() - getCenter().getX());
	dir_.setY(target_.getY() - getCenter().getY());
	dir_.normalize();
}