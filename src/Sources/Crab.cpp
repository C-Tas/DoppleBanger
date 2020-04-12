#include "Crab.h"
#include <iostream>

bool Crab::update() {
	updateFrame(); //Redefinir
	move(targetsVector_.at(actualTarget_));
#ifdef _DEBUG

#endif // _DEBUG
	if (currState_ == STATE::ATTACKING) {
		
	}
	else if (currState_ == STATE::DYING) {
		return true;
	}
	else if (currState_ == STATE::IDLE) {
		
	}

	return false;
}
void Crab::move(Point2D target)
{
	Vector2D visPos = getVisPos(pos_);
	//Margen de 2 pixeles
	if (visPos.getX() < target_.getX() - 2 ||
		visPos.getX() > target_.getX() + 2 ||
		visPos.getY() < target_.getY() - 2 ||
		visPos.getX() > target_.getX() + 2)
	{
		double delta = app_->getDeltaTime();
		pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
		pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	}
	else {
		updateTarget();
	}
}
void Crab::attack() { 
	Vector2D visPos = getVisPos(pos_);
	if (visPos.getX() < 200 && visPos.getX() > 150 && visPos.getY() < 500 && visPos.getX() > 150) {
		//doDamage();//falta definir en enemy
		currState_ = STATE::ATTACKING;
		currAnim_ = attackAnim_;
	}
}

void Crab::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);
	collisionArea_ = SDL_Rect{ (pos_.getX(), pos_.getY(), W_COLLISION, H_COLLISION) };
	initStats(HEALTH, MANA, MANA_REG, ARMOR, AD, AP, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	initAnim();
}

void Crab::initAnim()
{
	//Cambiar los n�meros magicos
	attackAnim_ = Anim(NUM_FRAMES_ATK, NUM_FRAMES_ATK_ROW, W_CLIP_ATK, H_CLIP_ATK, 10,"Attack");
	//Faltan las otras animaciones
}
