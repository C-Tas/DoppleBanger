#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	dir_.setX(target.getX() - target.getX());
	dir_.setY(target.getY() - target.getY());
	dir_.normalize();
}
