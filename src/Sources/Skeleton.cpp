#include "Skeleton.h"
#include <iostream>
#include "Resources.h"
#include "BoneBullet.h"
#include "CollisionCtrl.h"
#include "PlayState.h"

bool Skeleton::update() {
	updateFrame();

	//Si el esqueleto ha muerto
	if (currState_ == STATE::DYING) {
		//Sonido muerte

		dieAnim();

	}
	else {
		updateCooldowns();

		if (!attacking_) {
			//Si no esta atacando, se mira a ver cual e sel target mas cercano
			if (getEnemy(currStats_.distRange_) && !shootCD_.isCooldownActive() && onRange(currStats_.distRange_)) {
				//Si esta a rango dispara
				initShoot();
			}
		}

		if (currState_ == STATE::SHOOTING) {
			shootAnim();
		}
	}
	return false;
}

void Skeleton::initialStats() {
	HEALTH = 1200;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 5;
	MELEE_DMG = 0;
	DIST_DMG = 150;
	CRIT = 0;
	MELEE_RANGE = 0;
	DIST_RANGE = 800;
	MOVE_SPEED = 300;
	MELEE_RATE = 0;
	DIST_RATE = 2000;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Skeleton::updateCooldowns()
{
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}

void Skeleton::attack() {
	//Sonido ataque
	app_->getAudioManager()->playChannel(Resources::SkeletonAttack, 0, Resources::SkeletonChannel2);
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	//Critico
	double realDamage = currStats_.distDmg_;
	if (applyCritic()) realDamage *= 1.5;

	BoneBullet* bone = new BoneBullet(app_, getCenter(), dir, (int)round(realDamage), BONE_LIFE, BONE_VEL, Vector2D(BONE_WIDTH, BONE_HEIGHT));
	app_->getCurrState()->addRenderUpdateListsAsFirst(bone);
	CollisionCtrl::instance()->addEnemyBullet(bone);
}

void Skeleton::initObject() {
	initialStats();
	initRewards();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

void Skeleton::lostAggro()
{
	currEnemy_ = GameManager::instance()->getPlayer();
}

Skeleton::~Skeleton()
{
	if (GameManager::instance()->isThatMissionStarted(missions::papelesSiniestros))
		GameManager::instance()->addMissionCounter(missions::papelesSiniestros);
	if (GameManager::instance()->isThatMissionStarted(missions::arlongPark))
		GameManager::instance()->addMissionCounter(missions::arlongPark);
}

void Skeleton::initRewards()
{
	minGold = 20;
	maxGold = 30;
	minArchievementPoints = 65;
	maxArchievementPoints = 95;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void Skeleton::initAnims() 
{
	/*
	UP,
	RIGHT,
	DOWN,
	LEFT
	*/
	//Animaci�n de idle
	idleAnims_= Anim(IDLE_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, IDLE_FRAME_RATE, true);
	//Arriba
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleUpAnim));
	//Derecha
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleRightAnim));
	//Abajo
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleDownAnim));
	//Izquierda
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleLeftAnim));

	//Animacion de disparo
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackUpAnim));
	//Animacion derecha
	shootAnims_.push_back(Anim(SHOOT_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_RL_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackRightAnim));
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_D_FRAME_RATE, false)),
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackDownAnim));
	//Anim izquierda
	shootAnims_.push_back(Anim(SHOOT_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_RL_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackLeftAnim));

	//Inicializamos con la animación del idle
	currDir_ = DIR::LEFT;
	initIdle();
}

void Skeleton::initIdle()
{
	attacking_ = false;
	currEnemy_ = nullptr;
	currState_ = STATE::IDLE;
	//Sonido ataque
	app_->getAudioManager()->playChannel(Resources::SkeletonIdle, -1, Resources::SkeletonChannel1);
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_;
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Skeleton::shootAnim() {
	if (!shooted_ &&currAnim_.currFrame_ == frameAction_ ) {
		shooted_ = true;
		attack();
		shootCD_.initCooldown(currStats_.distRate_);
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();
	}
}

void Skeleton::initShoot() {
	//Sonido ataque
	app_->getAudioManager()->playChannel(Resources::SkeletonAttack, 0, Resources::SkeletonChannel2);
	//Para decir que esta atacando
	attacking_ = true;
	currState_ = STATE::SHOOTING;	//Cambio de estado
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisObjective(currEnemy_);	//Hacia dónde mira
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];

	//Asigna el frame donde ocurrirá la acción
	switch (currDir_)
	{
	case DIR::UP:		//arriba
		frameAction_ = 10;
		break;
	case DIR::RIGHT:	//derecha
		frameAction_ = 10;
		break;
	case DIR::DOWN:		//abajo
		frameAction_ = 19;
		break;
	case DIR::LEFT:		// izquierda
		frameAction_ = 10;
	}

	shootCD_.initCooldown(currStats_.distRate_);
	//Inicio de lso frames
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Skeleton::initMove()
{
	currState_ = STATE::FOLLOWING;
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Skeleton::feedBackHurtSounds()
{
	switch (rand() % 3)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::SkeletonHit1, 0, Resources::SkeletonChannel3);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::SkeletonHit2, 0, Resources::SkeletonChannel3);
		break;
	case 2:
		app_->getAudioManager()->playChannel(Resources::SkeletonHit3, 0, Resources::SkeletonChannel3);
		break;
	}
}

void Skeleton::initDie() 
{
	Enemy::initDie();
	app_->getAudioManager()->playChannel(Resources::SkeletonDeath, 0, Resources::SkeletonChannel1);
}