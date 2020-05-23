#include "Skeleton.h"
#include <iostream>
#include "Resources.h"
#include "BoneBullet.h"
#include "CollisionCtrl.h"
#include "PlayState.h"
//#include "CaribbeanIslandState.h"

void Skeleton::initialStats() {
	HEALTH = 1500;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 0;
	DIST_DMG = 100;
	CRIT = 0;
	MELEE_RANGE = 20;
	DIST_RANGE = 250;
	MOVE_SPEED = 100;
	MELEE_RATE = 0;
	DIST_RATE = 3500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Skeleton::updateCooldowns()
{
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}


void Skeleton::attack() {
	if (!shootCD_.isCooldownActive()) {
		shootCD_.initCooldown(currStats_.distRate_);
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	//Critico
	double realDamage = currStats_.distDmg_;
	if (applyCritic()) realDamage *= 1.5;

	BoneBullet* bone = new BoneBullet(app_, getCenter(), dir, realDamage, BONE_LIFE, BONE_VEL, Vector2D(BONE_WIDTH, BONE_HEIGHT));
	app_->getCurrState()->addRenderUpdateLists(bone);
	CollisionCtrl::instance()->addEnemyBullet(bone);
	}
}

void Skeleton::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Skeleton));
	initialStats();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	rangeVision_ = 270;
	initAnims();
}

void Skeleton::lostAggro()
{
	currEnemy_ = nullptr;
}

bool Skeleton::update() {
	updateFrame();
	updateCooldowns();

	//Si el esqueleto ha muerto
	if (currState_ == STATE::DYING) {
		//Sonido muerte
		app_->getAudioManager()->playChannel(Resources::SkeletonDeath, 0, Resources::SkeletonChannel1);
		// animación de muerte si la tiene
		//Cuando acabe la animación, lo mata
		applyRewards();
		CollisionCtrl::instance()->removeEnemy(this);
		static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		
		return true;
	}
	else if (currState_ == STATE::IDLE && getEnemy(rangeVision_)) {
		currState_ = STATE::ATTACKING;
	}
	//Si el esqueleto tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING && !shootCD_.isCooldownActive()) {
		//Si el esqueeto tiene un enemigo y lo tiene a rango
		if (onRange()) {
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			initShoot();
		}
		//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
		else if (getEnemy(currStats_.distRange_))
		{
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			initShoot();
		}
		//Tengo enemigo pero no a rango
		else
		{
			initIdle();
			//changeAnim(idleAnim_); animacion de idle del esqueleto
			currEnemy_ = nullptr;
		}
	}
	if(currState_ == STATE::SHOOTING)
		shootAnim();
	return false;
}

void Skeleton::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void Skeleton::initAnims() 
{
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
	/*
	//Animaciones movimiento
	//Animacion movimiento arriba y abajo
	moveAnims_.push_back(Anim(MOVE_UD_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, MOVE_UD_FRAME_RATE, true));
	//Arriba
	moveTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonMoveUpAnim));
	//Abajo
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonMoveDownAnim));
	//Animacion movimiento derecha e izquierda
	moveAnims_.push_back(Anim(MOVE_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, MOVE_RL_FRAMES_RATE, true));
	//Derecha
	moveTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonMoveRightAnim));
	//Izquierda
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonMoveLeftAnim));*/

	//Animacion de disparo
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_D_FRAME_RATE, false)),
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackDownAnim));
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackUpAnim));
	//Animacion derecha
	shootAnims_.push_back(Anim(SHOOT_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_RL_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackRightAnim));
	//Anim izquierda
	shootAnims_.push_back(Anim(SHOOT_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_RL_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackLeftAnim));
	//Inicializamos con la animación del idle
	currDir_ = DIR::LEFT;
	initIdle();
}

void Skeleton::initIdle()
{
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
	currState_ = STATE::SHOOTING;	//Cambio de estado
	//Sonido ataque
	app_->getAudioManager()->playChannel(Resources::SkeletonAttack, 0, Resources::SkeletonChannel2);
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisObjective(currEnemy_);	//Hacia dónde mira
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];

	//Asigna el frame donde ocurrirá la acción
	switch (currDir_)
	{
	case DIR::UP:		//arriba
		frameAction_ = 12;
		break;
	case DIR::RIGHT:	//derecha
		frameAction_ = 11;
		break;
	case DIR::DOWN:		//abajo
		frameAction_ = 19;
		break;
	case DIR::LEFT:		// izquierda
		frameAction_ = 11;
	}

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