#include "Skeleton.h"
#include <iostream>
#include "Resources.h"
#include "BoneBullet.h"
#include "CollisionCtrl.h"
//#include "CaribbeanIslandState.h"

void Skeleton::initialStats() {
	HEALTH = 100;
	MANA = 100;
	MANA_REG = 1;
	ARMOR = 10;
	MELEE_DMG = 0;
	DIST_DMG = 100;
	CRIT = 0;
	MELEE_RANGE = 20;
	DIST_RANGE = 250;
	MOVE_SPEED = 100;
	MELEE_RATE = 1;
	DIST_RATE = 2500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Skeleton::attack() {
	if (currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		lastHit = SDL_GetTicks();
		Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
		BoneBullet* bone = new BoneBullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
			getCenter(), dir, currStats_.distDmg_, BONE_LIFE, BONE_VEL, Vector2D(BONE_WIDTH, BONE_HEIGHT));
		app_->getCurrState()->addRenderUpdateLists(bone);
		CollisionCtrl::instance()->addEnemyBullet(bone);
	}
}

void Skeleton::initObject() {
	setTexture(app_->getTextureManager()->getTexture(Resources::Skeleton));
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

void Skeleton::lostAggro()
{
	currEnemy_ = nullptr;
}

bool Skeleton::update() {

	updateFrame();
	//Si el esqueleto ha muerto
	if (currState_ == STATE::DYING) {
		// animación de muerte si la tiene
		//Cuando acabe la animación, lo mata
		applyRewards();
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el esqueleto no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
	if (currState_ == STATE::IDLE && getEnemy(currStats_.distRange_)) {
		currState_ = STATE::SHOOTING;
		if (firstAttack && onRange()) {
			//sonido
		}
		firstAttack = false;
	}
	//Si el esqueleto tiene enemigo y puede atacar
	if (currState_ == STATE::SHOOTING && currStats_.distRate_ <= SDL_GetTicks() - lastHit) {
		//Si el esqueeto tiene un enemigo y lo tiene a rango
		if (onRange()) {
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			initShoot();
			attack();
		}
		//Tengo enemigo como objetivo, pero no a rango, busco si hay otro cerca para atacar
		else if (getEnemy(currStats_.distRange_))
		{
			//changeAnim(attackAnim_);//animacion de ataque del esqueleto
			attack();
		}
		//Tengo enemigo pero no a rango
		else
		{
			currState_ == STATE::IDLE;
			initIdle();
			currEnemy_ = nullptr;
			firstAttack = true;
		}
		lastHit = SDL_GetTicks();
	}
	if (currEnemy_ != nullptr) initShoot();
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
	idleAnims_.push_back(Anim(IDLE_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, IDLE_FRAME_RATE, true));
	//Arriba
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleUpAnim));
	//Derecha
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleRightAnim));
	//Abajo
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleDownAnim));
	//Izquierda
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonIdleLeftAnim));

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
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonMoveLeftAnim));

	//Animacion de disparo
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_D_FRAME_RATE, false)),
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackDownAnim));
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_ ->getTextureManager()->getTexture(Resources::SkeletonAttackUpAnim));
	//Animacion derecha e izquierda
	shootAnims_.push_back(Anim(SHOOT_RL_FRAMES, W_SKELETON_FRAME, H_SKELETON_FRAME, SHOOT_RL_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackRightAnim));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::SkeletonAttackLeftAnim));
	//Inicializamos con la animación del idle
	currDir_ = DIR::UP;
	initIdle();
}

void Skeleton::initIdle()
{
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Skeleton::initShoot() {
	currState_ = STATE::SHOOTING;	//Cambio de estado
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisObjective(currEnemy_);	//Hacia dónde mira
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];

	//Asigna el frame donde ocurrirá la acción
	switch (currDir_)
	{
	case DIR::UP:		//Derecha arriba
		frameAction_ = 10;
		break;
	case DIR::RIGHT:	//Derecha abajo
		frameAction_ = 9;
		break;
	case DIR::DOWN:		//Izquierda abajo
		frameAction_ = 10;
		break;
	case DIR::LEFT:		//Izquierda arriba
		frameAction_ = 10;
	}

	//Inicio de lso frames
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Skeleton::initMove()
{
	app_->getAudioManager()->playChannel(Resources::MovePumpkin, -1, 6);
	currState_ = STATE::FOLLOWING;
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}