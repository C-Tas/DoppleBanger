#include "Crab.h"
#include <iostream>

bool Crab::update() {
	updateFrame();
	updateVisPos();
	move(targetsVector_.at(actualTarget_));
#ifdef _DEBUG

#endif // _DEBUG

	//Margen de 2 pixeles
	if (visPos_.getX() < target_.getX() - 2 ||
		visPos_.getX() > target_.getX() + 2 ||
		visPos_.getY() < target_.getY() - 2 ||
		visPos_.getX() > target_.getX() + 2)
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
bool Crab::attack() { 
	//if (visPos_.getX() < 200 && visPos_.getX() > 150 && visPos_.getY() < 500 && visPos_.getX() > 150) {
	//	doDamage();//falta definir en enemy
	//	return true;
	//}
	return false; 
}

void Crab::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);
	collisionArea_ = SDL_Rect{ (pos_.getX(), pos_.getY(), W_COLLISION, H_COLLISION) };
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	initAnim();
}

void Crab::initAnim()
{
	attackAnim = Anim(NUM_FRAMES_ATK, NUM_FRAMES_ATK_ROW, W_CLIP_ATK, H_CLIP_ATK);
	//Faltan las otras animaciones
}
