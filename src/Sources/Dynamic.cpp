#include "Dynamic.h"

void Dynamic::move(Point2D target)
{
	vel_.setX(target.getX() - target.getX());
	vel_.setY(target.getY() - target.getY());
	vel_.normalize();
}
