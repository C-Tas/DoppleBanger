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


	changeTexture(attack(),1);
	return false;
}
bool Crab::attack() { 
	if (visPos_.getX() < 200 && visPos_.getX() > 150 && visPos_.getY() < 500 && visPos_.getX() > 150) {
		doDamage();
		return true;
	}
	return false; 
}