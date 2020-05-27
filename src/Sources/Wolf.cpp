#include "Wolf.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include <string>
#include "PlayState.h"
#include "Collisions.h"

bool Wolf::update() {
	updateFrame();
	updateCooldowns();

	//Si el lobo ha muerto
	if (currState_ == STATE::DYING) {
		dieAnim();
	}
	else
	{
		if ((currState_ == STATE::IDLE || currState_ == STATE::PATROLLING) && currEnemy_ == nullptr && getEnemy() && !idle_) {
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfDetection, 0, Resources::WolfChannel2);
			initMove();
		}

		if (currEnemy_ == nullptr) {
			if (currState_ == STATE::IDLE && !idleCD_.isCooldownActive()) {
				target_ = patrol_[currPatrol_];
				initMove();
			}
			if (currState_ == STATE::PATROLLING) {
				move(target_);
			}
		}
		else {
			if (Enemy::onRange(currStats_.meleeRange_)) {
				if (!meleeCD_.isCooldownActive()) {
					initMelee();
					switch (rand() % 2)
					{
					case 0:
						app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack1, 0, Resources::WolfChannel2);
						break;
					case 1:
						app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack2, 0, Resources::WolfChannel2);
						break;
					}
				}
				stop();
			}
			else if (Enemy::onRange() && currState_ != STATE::ATTACKING) {
				if (idle_) {
					initMove();
				}
				move(currEnemy_->getCenter());
				app_->getAudioManager()->playChannel(Resources::AudioId::WolfChase, -1, Resources::WolfChannel1);
				idle_ = false;
			}
			else if (currState_ != STATE::ATTACKING) {
				currEnemy_ = nullptr;
				initMove();
				target_ = patrol_[currPatrol_];
				idle_ = false;
			}
		}
		if (currState_ == STATE::ATTACKING) meleeAnim();
	}
	return false;
}

//Mueve al lobo DONE
void Wolf::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	if ((getCenter() - nextTarget_).magnitude() <= 1)
	{
		pathPos_ = { (int)PosToTile(nextTarget_).getX(), (int)PosToTile(nextTarget_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(posToReach).getX(), (int)PosToTile(posToReach).getY() }, pathPos_);
		if (pathing_.size() > 1) {
			nextTarget_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));

			updateDirVisObjective(nextTarget_);
			texture_ = moveTx_[(int)currDir_];
			currAnim_ = moveAnims_[(int)currDir_];
		}
		else
		{
			initIdle();
			idleCD_.initCooldown(IDLE_PAUSE);

			//Pasamos al siguiente patrol
			if (currPatrol_ == patrol_.size() - 1) currPatrol_ = 0;
			else currPatrol_++;
		}
	}
	dir_.setVec(nextTarget_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}

//Se encarga de gestionar el ataque a melee DONE
void Wolf::attack() {
	auto dmg = dynamic_cast<Player*>(currEnemy_);
	if (dmg != nullptr) {
		switch (rand() % 2)
		{
		case 0:
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack1, 0, Resources::WolfChannel1);
			break;
		case 1:
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack2, 0, Resources::WolfChannel1);
			break;
		}
		double realDamage = currStats_.meleeDmg_;
		if (applyCritic()) realDamage *= 1.5;
		dmg->receiveDamage(realDamage);

	}
}

//Inicializa al lobo
void Wolf::initObject() {
	Enemy::initObject();
	currState_ = STATE::IDLE;
	target_ = pos_;
	nextTarget_ = pos_;
	setTexture(app_->getTextureManager()->getTexture(Resources::WolfFront));
	initRewards();
	rangeVision_ = VIS_RANGE;
	tag_ = "Wolf";
}

void Wolf::onCollider() {}

//Esto lo llama el clon cuando se destruye
void Wolf::lostAggro()
{
	currEnemy_ = nullptr;
	currState_ = STATE::PATROLLING;
}

//Genera la posici�n a la que se mueve el pirata en funci�n de su rango 
void Wolf::selectTarget() {
	if (currEnemy_ != nullptr) {
		Point2D centerPos = { getPosX() + getScaleX() / 2, getPosY() + getScaleY() / 2 };
		Point2D enemycenterPos = { currEnemy_->getPosX() + currEnemy_->getScaleX() / 2, currEnemy_->getPosY() + currEnemy_->getScaleY() / 2 };
		Vector2D posToReach;
		posToReach.setX((enemycenterPos.getX() + currStats_.meleeRange_) - centerPos.getX());
		posToReach.setY((enemycenterPos.getY() + currStats_.meleeRange_) - centerPos.getY());
		target_ = posToReach;
		move(enemycenterPos);
	}
}

bool Wolf::getEnemy() {
	if (Enemy::getEnemy(rangeVision_)) {
		return true;
	}
	else return false;
}

//Cuando el pirata pierde el agro, se le asigna el agro del player
//Esto lo llama el clon cuando se destruye
void Wolf::lostAgro()
{
	currEnemy_ = nullptr;
	currState_ = STATE::PATROLLING;
}

void Wolf::initialStats()
{
	initHealth_ = 900;
	initMana_ = 0;
	initManaReg_ = 0;
	initArmor_ = 0;
	initMeleeDmg = 180;
	initDistDmg = 0;
	initCrit_ = 10;
	initMeleeRange = getScaleX() / 3;
	initDistRange_ = 0;
	initMoveSpeed = 500;
	initMeleeRate_ = 1500;
	initDistRate_ = 0;
	initStats(initHealth_, initMana_, initManaReg_, initArmor_, initMeleeDmg, initDistDmg, initCrit_, initMeleeRange, initDistRange_, initMoveSpeed, initMeleeRate_, initDistRate_);
}

//Inicializa todas las animaciones 
void Wolf::initAnims() {
	//Animación de idle
	//Arriba
	idleAnims_.push_back(Anim(IDLE_U_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, IDLE_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfIdleUpAnim));
	//Derecha																						
	idleAnims_.push_back(Anim(IDLE_R_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, IDLE_R_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfIdleRightAnim));
	//Abajo																							
	idleAnims_.push_back(Anim(IDLE_D_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, IDLE_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfIdleDownAnim));
	//Izquierda																						
	idleAnims_.push_back(Anim(IDLE_L_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, IDLE_L_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfIdleLeftAnim));

	//Animación de movimiento
	//Arriba
	moveAnims_.push_back(Anim(MOVE_U_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MOVE_U_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfMoveUpAnim));
	//Derecha														
	moveAnims_.push_back(Anim(MOVE_R_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MOVE_R_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfMoveRightAnim));
	//Abajo
	moveAnims_.push_back(Anim(MOVE_D_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MOVE_D_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfMoveDownAnim));
	//Izquierda
	moveAnims_.push_back(Anim(MOVE_L_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MOVE_L_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfMoveLeftAnim));

	//Animación de melee
	//Arriba
	meleeAnims_.push_back(Anim(MELEE_U_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MELEE_U_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfAttackUpAnim));
	//Derecha
	meleeAnims_.push_back(Anim(MELEE_R_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MELEE_R_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfAttackRightAnim));
	//Abajo
	meleeAnims_.push_back(Anim(MELEE_D_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MELEE_D_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfAttackDownAnim));
	//Izquierda
	meleeAnims_.push_back(Anim(MELEE_L_FRAMES, W_H_WOLF_FRAME, W_H_WOLF_FRAME, MELEE_L_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::WolfAttackLeftAnim));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

void Wolf::initRewards()
{
	minGold = 110;
	maxGold = 160;
	minArchievementPoints = 3;
	maxArchievementPoints = 8;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void Wolf::updateCooldowns()
{
	if (meleeCD_.isCooldownActive()) meleeCD_.updateCooldown();
	if (idleCD_.isCooldownActive()) idleCD_.updateCooldown();
}

void Wolf::setPatrol(Vector2D pos)
{
	patrol_.push_back(pos);
}

void Wolf::initIdle() {
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Wolf::initMove() {
	if (currEnemy_ != nullptr) updateDirVisObjective(currEnemy_->getCenter());
	else updateDirVisObjective(target_);
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	currState_ = STATE::PATROLLING;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void Wolf::initMelee() {
	currState_ = STATE::ATTACKING;	//Cambio de estado
	attacked_ = false;	//Aún no se ha atacado
	updateDirVisObjective(currEnemy_);	//Hacia dónde está el enemigo
	texture_ = meleeTx_[(int)currDir_];
	currAnim_ = meleeAnims_[(int)currDir_];
	//Frame exacto del ataque
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 5;
		break;
	case DIR::RIGHT:
		frameAction_ = 4;
		break;
	case DIR::DOWN:
		frameAction_ = 6;
		break;
	case DIR::LEFT:
		frameAction_ = 4;
		break;
	}

	//Se inicia el frame
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	meleeCD_.initCooldown(currStats_.meleeRate_);
}

void Wolf::initDie() {
	Enemy::initDie();
	app_->getAudioManager()->playChannel(Resources::AudioId::WolfDeath, 0, Resources::WolfChannel1);

	GameManager* gm_ = GameManager::instance();
	if (gm_->isThatMissionStarted(missions::laboon))
		gm_->addMissionCounter(missions::laboon);
}

void Wolf::meleeAnim() {
	stop();
	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		attack();

		meleeCD_.initCooldown(currStats_.meleeRate_);
		attacked_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		idleCD_.initCooldown(IDLE_PAUSE);
		currEnemy_ = nullptr;
		idle_ = true;
		initIdle();	//Activa el idle
	}
}