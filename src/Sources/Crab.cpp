#include "Crab.h"
#include "Player.h"
#include <iostream>

bool Crab::update() {
	updateFrame(); //Redefinir
#ifdef _DEBUG

#endif // _DEBUG
if(currState_==STATE::DYING){}
else
{
	if (currState_ == STATE::PATROLLING&&!getEnemy(10)) {
		move(targetsVector_.at(actualTarget_));
	}
	else
	{
		//Si entramos en este caso indica que el enemigo esta al alcance ya que es el factor que rechazo el anterior if y así tiene coste O(1) y no coste O(getenemy)
		if (currState_ == STATE::PATROLLING) {
			currState_ = STATE::ATTACKING;
		}
		//Se vuelve a comprobar la posicion del enemigo ya que sino podria no parar de atacar
		if (currState_ == STATE::ATTACKING&&getEnemy(10)) {
			attack();
		}
		else
		{
			currState_ = STATE::PATROLLING;
		}
	}
}

	return false;
}
void Crab::move(Point2D target)
{
	Vector2D visPos = getVisPos();
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
	else 
	{
		updateTarget();
	}
}
void Crab::attack() { 
	auto dmg = dynamic_cast<Player*>(currEnemy_);
	if (dmg != nullptr) {
		dmg->receiveDamage(currStats_.meleeDmg_);
	}
		currAnim_ = attackAnim_;
	}

void Crab::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);
	Enemy::initObject();
	initAnims();
}

void Crab::initAnims()
{
	//Cambiar los n�meros magicos
	attackAnim_ = Anim(NUM_FRAMES_ATK, W_CLIP_ATK, H_CLIP_ATK, 10, false);
	//Faltan las otras animaciones
}
void Crab::initialStats(){
		  HEALTH = 1000;
	  MANA = 0;
	  MANA_REG = 0;
	  ARMOR = 1000;
	  MELEE_DMG = 1000;
	  DIST_DMG = 0;
	  CRIT = 0;
	  MELEE_RANGE = 50;
	  DIST_RANGE = 0;
	  MOVE_SPEED = 100;
	  MELEE_RATE = 1;
	  DIST_RATE = 2;
	  initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}