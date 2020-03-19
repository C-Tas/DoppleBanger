#include "Crab.h"
bool Crab:: update() {
	move(targetVector_.at(actualTarget_));
	//Margen de 2 pixeles
	if (visPos_.getX() < obj_.getX() - 2 ||
		visPos_.getX() > obj_.getX() + 2 ||
		visPos_.getY() < obj_.getY() - 2 ||
		visPos_.getX() > obj_.getX() + 2)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}
	else
	{
		updateTarget();
	}
	Enemy::update();
	return false;
}