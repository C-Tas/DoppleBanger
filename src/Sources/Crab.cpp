#include "Crab.h"
#include <iostream>
bool Crab::update() {
	updateFrame();
	updateVisPos();
	move(targetsVector_.at(actualTarget_));
#ifdef _DEBUG

#endif // _DEBUG

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
	else {
		updateTarget();
	}
	return false;
}