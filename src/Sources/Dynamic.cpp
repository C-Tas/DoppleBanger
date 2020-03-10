#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	obj_.setVec(target);
	dir_.setX(target.getX() - visPos_.getX());
	dir_.setY(target.getY() - visPos_.getY());
	dir_.normalize();
}