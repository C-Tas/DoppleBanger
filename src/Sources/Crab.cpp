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
			move(targetsVector_.at(actualTarget_));
		}
		//Cuando tenemos enemigo
		if (currEnemy_ != nullptr) {
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

	if ((getCenter() - nextTarget_).magnitude() <= 3)
	{
		pathPos_ = { (int)PosToTile(nextTarget_).getX(), (int)PosToTile(nextTarget_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(target).getX(), (int)PosToTile(target).getY() }, pathPos_);

		if (pathing_.size() > 1) nextTarget_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
		else updateTarget(); 
		
	}

	dir_.setVec(nextTarget_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}

void Crab::initMeleeAnim()
{
	app_->getAudioManager()->playChannel(Resources::AudioId::CrabDetection, 0, Resources::CrabChannel2);
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
	app_->getAudioManager()->playChannel(Resources::AudioId::CrabDetection, -1, Resources::CrabChannel2);
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
	app_->getAudioManager()->playChannel(Resources::AudioId::CrabIdleSound, -1, Resources::CrabChannel2);
	texture_ = idleTx_;
	currAnim_ = idleAnim_;

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Crab::initDie()
{
	Enemy::initDie();
	app_->getAudioManager()->haltChannel(Resources::CrabChannel1);
	app_->getAudioManager()->haltChannel(Resources::CrabChannel2);

	GameManager* gm_ = GameManager::instance();
	if (gm_->isThatMissionStarted(missions::gallegaEnProblemas))
		gm_->addMissionCounter(missions::gallegaEnProblemas);
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
	app_->getAudioManager()->playChannel(Resources::AudioId::CrabAttackSound, 0, Resources::CrabChannel2);
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
	nextTarget_ = pos_;
	app_->getAudioManager()->playChannel(Resources::AudioId::CrabIdleSound, 0, Resources::CrabChannel1);
	/*double w = 2 / 4,
		h = 1 / 3,
		x = 1 / 4,
		y = 1 / 3;
	scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
	posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);*/
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	tag_ = "Crab";
}

void Crab::initAnims()
{
	//Idle
	idleAnim_ = Anim(IDLE_NUM_FRAMES, W_H_FRAME, W_H_FRAME, IDLE_FRAME_RATE, true);
	idleTx_ = app_->getTextureManager()->getTexture(Resources::CrabIdle);
	//Caminar
	walkAnim_ = Anim(NUM_FRAMES_WALK, W_H_FRAME, W_H_FRAME, WALK_FRAME_RATE, true);
	walkTex_ = app_->getTextureManager()->getTexture(Resources::CrabWalk);
	//Atacar
	attackAnim_ = Anim(NUM_FRAMES_ATK, W_H_FRAME, W_H_FRAME, ATK_FRAME_RATE, false);
	attackTex_ = app_->getTextureManager()->getTexture(Resources::CrabAttack);

	initWalk();
}

void Crab::initialStats() {
	initHealth_ = 600;
	initMana_ = 0;
	initManaReg_ = 0;
	initArmor_ = 10;
	initMeleeDmg = 60;
	initDistDmg = 0;
	initCrit_ = 5;
	initMeleeRange = getScaleX() / 2;	//Medido con photoshop
	initDistRange_ = 0;
	initMoveSpeed = 250;
	initMeleeRate_ = 1200;	//En milisegundos
	initDistRate_ = 0;
	initStats(initHealth_, initMana_, initManaReg_, initArmor_, initMeleeDmg, initDistDmg, initCrit_, initMeleeRange, initDistRange_, initMoveSpeed, initMeleeRate_, initDistRate_);
}

void Crab::initRewards()
{
	minGold = 50;
	maxGold = 100;
	minArchievementPoints = 3;
	maxArchievementPoints = 8;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void Crab::updateCooldowns()
{
	if (meleeCD_.isCooldownActive()) meleeCD_.updateCooldown();
}