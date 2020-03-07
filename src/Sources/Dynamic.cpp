#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	obj_.setVec(target);
	dir_.setX(target.getX() - pos_.getX());
	dir_.setY(target.getY() - pos_.getY());
	dir_.normalize();
}