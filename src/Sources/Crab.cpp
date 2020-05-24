#include "Crab.h"
#include "Player.h"
#include "PlayState.h"
#include <iostream>
#include "Collisions.h"

bool Crab::update() {
	updateFrame();
	updateCooldowns();

	if (currState_ == STATE::DYING) {
		dieAnim();
	}
	else
	{
		//Cuando no tenemos enemigo
		if (currEnemy_ == nullptr && !getEnemy(currStats_.meleeRange_)) {
			if (RectRect(getCenter().getX(), getCenter().getY(), getScaleX(), getScaleY(),
				targetsVector_.at(actualTarget_).getX(), targetsVector_.at(actualTarget_).getY(), 1, 1)) {
				updateTarget();
			}
			move(targetsVector_.at(actualTarget_));
		}
		//Cuando tenemos enemigo
		if(currEnemy_ != nullptr){
			//Si esta a rango y se puede atacar
			if (onRange(currStats_.meleeRange_) && !meleeCD_.isCooldownActive()) {
				initMeleeAnim();
			}
			//Si no esta a rango
			else if (!onRange(currStats_.meleeRange_)) {
				initWalk();	//Si no esta a rango empieza a caminar
			}
		}

		if (currState_ == STATE::ATTACKING) meleeAnim();
	}

	return false;
}

void Crab::move(Point2D target)
{
	/*Vector2D visPos = getVisPos();
	target_ = target;*/
	if ((getCenter() - nextTarget_).magnitude() <= 0.05)
	{
		pathPos_ = { (int)PosToTile(nextTarget_).getX(), (int)PosToTile(nextTarget_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(target).getX(), (int)PosToTile(target).getY() }, pathPos_);
		if (pathing_.size() > 1)
			nextTarget_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
	}
	dir_.setVec(nextTarget_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}

void Crab::initMeleeAnim()
{
	app_->getAudioManager()->playChannel(Resources::CrabDetection, 0, Resources::CrabChannel2);
	currState_ = STATE::ATTACKING;
	currAnim_ = attackAnim_;
	texture_ = attackTex_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	meleeCD_.initCooldown(currStats_.meleeRate_);
}

void Crab::initWalk()
{
	currEnemy_ = nullptr;
	app_->getAudioManager()->playChannel(Resources::CrabWalk, -1, Resources::CrabChannel2);
	currState_ = STATE::PATROLLING;
	texture_ = walkTex_;
	currAnim_ = walkAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Crab::initIdle()
{
	currState_ = STATE::IDLE;
	app_->getAudioManager()->playChannel(Resources::CrabIdle, -1, Resources::CrabChannel2);
	texture_ = idleTx_;
	currAnim_ = idleAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Crab::meleeAnim()
{
	if (currAnim_.currFrame_ == FRAME_ACTION) {
		attack();
		meleeCD_.initCooldown(currStats_.meleeRate_);
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();
		currEnemy_ = nullptr;
	}
}

void Crab::attack() {
	app_->getAudioManager()->playChannel(Resources::CrabAttackSound, 0, Resources::CrabChannel2);
	auto dmg = dynamic_cast<Player*>(currEnemy_);
	if (dmg != nullptr) {
		//Critico
		double realDamage = currStats_.meleeDmg_;
		if (applyCritic()) realDamage *= 1.5;

		dmg->receiveDamage(realDamage);
	}
}

void Crab::initObject()
{
	Enemy::initObject();
	texture_ = app_->getTextureManager()->getTexture(Resources::CrabWalk);
	initAnims();
	initialStats();
	rangeVision_ = 40;
	target_ = pos_;
	nextTarget_ = pos_;
	app_->getAudioManager()->playChannel(Resources::CrabIdleSound, 0, Resources::CrabChannel1);
	tag_ = "Crab";
}

void Crab::initAnims()
{
	//Idle
	idleAnim_ = Anim(IDLE_NUM_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true);
	idleTx_ = app_->getTextureManager()->getTexture(Resources::CrabIdle);
	//Caminar
	walkAnim_ = Anim(NUM_FRAMES_WALK, W_H_FRAME, W_H_FRAME, WALK_FRAME_RATE,true);
	walkTex_= app_->getTextureManager()->getTexture(Resources::CrabWalk);
	//Atacar
	attackAnim_ = Anim(NUM_FRAMES_ATK, W_H_FRAME, W_H_FRAME, ATK_FRAME_RATE, false);
	attackTex_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);

	initWalk();
}

void Crab::initialStats() {
	HEALTH = 1;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 1000;
	MELEE_DMG = 10;
	DIST_DMG = 0;
	CRIT = 0;
	MELEE_RANGE = getScaleX() / 2;	//Medido con photoshop
	DIST_RANGE = 0;
	MOVE_SPEED = 100;
	MELEE_RATE = 1000;	//En milisegundos
	DIST_RATE = 2;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Crab::updateCooldowns()
{
	if (meleeCD_.isCooldownActive()) meleeCD_.updateCooldown();
}
