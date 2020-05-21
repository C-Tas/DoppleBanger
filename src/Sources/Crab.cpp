#include "Crab.h"
#include "Player.h"
#include "PlayState.h"
#include <iostream>

bool Crab::update() {
	updateFrame(); //Redefinir
#ifdef _DEBUG

#endif // _DEBUG
	if (currState_ == STATE::DYING) {}
	else
	{
		if (currState_ == STATE::PATROLLING && !getEnemy(rangeVision_)) {
			move(targetsVector_.at(actualTarget_));
		}
		else
		{
			//Si entramos en este caso indica que el enemigo esta al alcance ya que es el factor que rechazo el anterior if y así tiene coste O(1) y no coste O(getenemy)
			if (currState_ == STATE::PATROLLING) {
				currState_ = STATE::ATTACKING;
				currAnim_ = attackAnim_;
				texture_ = attackTex_;
				frame_.x = 0; frame_.y = 0;
				frame_.w = currAnim_.widthFrame_;
				frame_.h = currAnim_.heightFrame_;
			}
			//Se vuelve a comprobar la posicion del enemigo ya que sino podria no parar de atacar
			//cambairr a on range
			if (currState_ == STATE::ATTACKING && onRange()) {
				attack();
			}
			else
			{
				currState_ = STATE::PATROLLING;
				texture_ = walkTex_;
				currAnim_ = walkAnim_;
				frame_.x = 0; frame_.y = 0;
				frame_.w = currAnim_.widthFrame_;
				frame_.h = currAnim_.heightFrame_;
			}
		}
	}

	return false;
}
void Crab::move(Point2D target)
{
	Vector2D visPos = getVisPos();
	target_ = target;
	//Margen de 2 pixeles
	if (visPos.getX() < target_.getX() - 2 ||
		visPos.getX() > target_.getX() + 2 ||
		visPos.getY() < target_.getY() - 2 ||
		visPos.getX() > target_.getX() + 2)
	{
		if ((getCenter() - target_).magnitude() <= 0.05)
		{
			pathPos_ = { (int)PosToTile(target_).getX(), (int)PosToTile(target_).getY() };
			pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(target).getX(), (int)PosToTile(target).getY() }, pathPos_);
			if (pathing_.size() > 1)
				target_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
		}
		dir_.setVec(target_ - getCenter());
		dir_.normalize();
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
	if (!cd) { 
		cd = true;
		entra_ = SDL_GetTicks(); 
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		if (dmg != nullptr) {
			dmg->receiveDamage(currStats_.meleeDmg_);
		}
	}
	else {
		if (SDL_GetTicks() - entra_ >= 1000) {
			cd = false;
		}
	}
}

void Crab::initObject()
{
	texture_ = app_->getTextureManager()->getTexture(Resources::CrabWalk);
	Enemy::initObject();
	initAnims();
	rangeVision_ = 40;
}

void Crab::initAnims()
{
	walkAnim_ = Anim(NUM_FRAMES_WALK, W_CLIP_WALK, H_CLIP_WALK, WALK_FRAME_RATE,true);
	walkTex_= app_->getTextureManager()->getTexture(Resources::CrabWalk);
	//Cambiar los n�meros magicos
	attackAnim_ = Anim(NUM_FRAMES_ATK, W_CLIP_ATK, H_CLIP_ATK, ATK_FRAME_RATE,true);
	attackTex_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);
	//Faltan las otras animaciones
	texture_ = walkTex_;
	currAnim_ = walkAnim_;
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
void Crab::initialStats() {
	HEALTH = 1000;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 1000;
	MELEE_DMG = 10;
	DIST_DMG = 0;
	CRIT = 0;
	MELEE_RANGE = 50;
	DIST_RANGE = 0;
	MOVE_SPEED = 100;
	MELEE_RATE = 1;
	DIST_RATE = 2;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}