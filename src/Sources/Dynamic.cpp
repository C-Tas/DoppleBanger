#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(target);
	dir_.setX(target_.getX() - getCenter(pos_).getX());
	dir_.setY(target_.getY() - getCenter(pos_).getY());
	dir_.normalize();
}