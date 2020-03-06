#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	dir_.setX(target.getX() - pos_.getX());
	dir_.setY(target.getY() - pos_.getY());
	dir_.normalize(); //No normaliza
}
