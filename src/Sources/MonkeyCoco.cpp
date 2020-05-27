#include "MonkeyCoco.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include <string>
#include "PlayState.h"

bool MonkeyCoco::update() {
	updateFrame();
	updateCooldowns();
	//Si el mono ha muerto
	if (currState_ == STATE::DYING) {
		dieAnim();
	}
	else {
		//Si el mono no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
		if (currState_ == STATE::IDLE && getEnemy(currStats_.distRange_)) {
			currState_ = STATE::SHOOTING;
			if (firstAttack && onRange()) {
				app_->getAudioManager()->playChannel(Resources::MonkeyAttackSound, 0, Resources::MonkeyChannel);
				firstIdle = true;
			}
			firstAttack = false;
		}

		//Si el mono tiene enemigo y puede atacar
		if (currState_ == STATE::SHOOTING) {
			if (!shootCD_.isCooldownActive()) {
				//Si el mono tiene un enemigo y lo tiene a rango
				if (onRange()) {
					initShoot();
				}
				//Tengo enemigo pero no a rango
				else {
					if (firstIdle) {
						app_->getAudioManager()->playChannel(Resources::MonkeyIdleSound, 0, Resources::MonkeyChannel);
						firstIdle = false;
					}
					initIdle();
					currEnemy_ = nullptr;
					firstAttack = true;
				}
				shootCD_.initCooldown(currStats_.distRate_);
			}
			if (currEnemy_ != nullptr) shootAnim();
		}
	}
	return false;
}

//Inicializa todas las animaciones
void MonkeyCoco::initAnims() {
	//Animación de idle
	//Derecha arriba																					
	idleAnims_.push_back(Anim(IDLE_R_U_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, IDLE_R_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyIdleUpAnim));
	//Derecha abajo
	idleAnims_.push_back(Anim(IDLE_R_D_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, IDLE_R_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyIdleRightAnim));
	//Izquierda abajo																							
	idleAnims_.push_back(Anim(IDLE_L_D_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, IDLE_L_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyIdleDownAnim));
	//Izquierda arriba																				
	idleAnims_.push_back(Anim(IDLE_L_U_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, IDLE_L_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyIdleLeftAnim));

	//Animación de disparo
	//Derecha arriba
	shootAnims_.push_back(Anim(SHOOT_R_U_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, SHOOT_R_U_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyShootUpAnim));
	//Derecha abajo
	shootAnims_.push_back(Anim(SHOOT_R_D_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, SHOOT_R_D_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyShootRightAnim));
	//Izquierda abajo
	shootAnims_.push_back(Anim(SHOOT_L_D_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, SHOOT_L_D_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyShootDownAnim));
	//Izquierda arriba
	shootAnims_.push_back(Anim(SHOOT_L_U_FRAMES, W_H_MONKEY_FRAME, W_H_MONKEY_FRAME, SHOOT_L_U_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::MonkeyShootLeftAnim));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

//Se encarga de crear el coco en direcci�n al enemigo
void MonkeyCoco::attack() {
	Vector2D dir = Vector2D(currEnemy_->getPosX() + (currEnemy_->getScaleX() / 2), currEnemy_->getPosY() + (currEnemy_->getScaleY() / 2));
	Bullet* coco = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Coco),
		getCenter(), dir, currStats_.distDmg_, COCO_LIFE, COCO_VEL, Vector2D(W_H_COCO, W_H_COCO));
	app_->getCurrState()->addRenderUpdateListsAsFirst(coco);
	CollisionCtrl::instance()->addEnemyBullet(coco);
}

//Inicializa al mono
void MonkeyCoco::initObject() {
	Enemy::initObject();
	setTexture(app_->getTextureManager()->getTexture(Resources::MonkeyFront));
	initAnims();
	initRewards();

	/*double w = 1 / 3,
		h = 1 / 3,
		x = 1 / 3,
		y = 1 / 3;
	scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
	posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);*/
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
}

void MonkeyCoco::initialStats() 
{
	rangeVision_ = 1200;
	HEALTH = 500;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 5;
	MELEE_DMG = 0;
	DIST_DMG = 250;
	CRIT = 5;
	MELEE_RANGE = 0;
	DIST_RANGE = 1000;
	MOVE_SPEED = 0;
	MELEE_RATE = 0;
	DIST_RATE = 1500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void MonkeyCoco::updateDirVisObjective(GameObject* objective) {
	if (objective != nullptr) {
		Vector2D center = getCenter();		//Punto de referencia
		Vector2D enemyCenter = objective->getCenter();
		Vector2D dir = enemyCenter - center;		//Vector dirección
		dir.normalize();
		double angle = atan2(dir.getY(), dir.getX()) * 180 / M_PI;
		if (angle >= 0) {
			if (angle <= 90.0) currDir_ = DIR::RIGHT;	//Para la derecha abajo
			else currDir_ = DIR::DOWN;	//Para abajo izquierda
		}
		else {
			if (angle >= -90.0) currDir_ = DIR::UP;	//Para la derecha arriba
			else currDir_ = DIR::LEFT;	//Para la izquierda arriba
		}
	}
}

void MonkeyCoco::updateCooldowns()
{
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}

void MonkeyCoco::initIdle() {
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void MonkeyCoco::initShoot() {
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

void MonkeyCoco::shootAnim() {
	if (!shooted_ && currAnim_.currFrame_ == frameAction_) {
		app_->getAudioManager()->playChannel(Resources::MonkeyShootSound, 0, Resources::MonkeyChannel);
		attack();
		shooted_ = true;
		shootCD_.initCooldown(currStats_.distRate_);
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();	//Activa el idle
	}
}

void MonkeyCoco::initRewards()
{
	minGold = 70;
	maxGold = 120;
	minArchievementPoints = 4;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void MonkeyCoco::initDie() {
	Enemy::initDie();
	app_->getAudioManager()->playChannel(Resources::MonkeyDieSound, 0, Resources::SoundChannels::MonkeyChannel);
}