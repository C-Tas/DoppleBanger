#include "EnemyPirate.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "Collisions.h"
#include "CaribbeanIslandState.h"
#include <string>

bool EnemyPirate::update() {
	updateFrame();
	updateCooldowns();
	//Si el pirata ha muerto
	if (currState_ == STATE::DYING) {
		dieAnim();
	}
	else {
		if ((currState_ == STATE::IDLE || currState_ == STATE::PATROLLING) && currEnemy_ == nullptr && getEnemy(rangeVision_) && !idle_) {
			app_->getAudioManager()->playChannel(Resources::Agro, 0, Resources::EnemyPirateChannel1);
			initMove();
		}

		if (currEnemy_ == nullptr) {
			if (currState_ == STATE::IDLE && !idleCD_.isCooldownActive()) {
				target_ = patrol_[currPatrol_];
				initMove();
			}
			if (currState_ == STATE::PATROLLING) {
				updateDirVisObjective(target_);
				move(target_);
			}
		}
		else {
			if (onRange(currStats_.meleeRange_)) {
				if (!meleeCD_.isCooldownActive()) {
					initMelee();
				}
				stop();
			}
			else if (onRange(currStats_.distRange_)) {
				if (!shootCD_.isCooldownActive()) {
					initShoot();
				}
				stop();
			}
			else if (onRange(rangeVision_) && currState_ != STATE::ATTACKING && currState_ != STATE::SHOOTING) {
				updateDirVisObjective(currEnemy_->getCenter());
				if (idle_) initMove();
				move(currEnemy_->getCenter());
				idle_ = false;
			}
			else if (currState_ != STATE::ATTACKING && currState_ != STATE::SHOOTING) {
				currEnemy_ = nullptr;
				initMove();
				target_ = patrol_[currPatrol_];
				idle_ = false;
			}
		}
		if (currState_ == STATE::ATTACKING) meleeAnim();
		else if (currState_ == STATE::SHOOTING) shootAnim();
	}
	return false;
}

void EnemyPirate::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	if ((getCenter() - nextTarget_).magnitude() <= 1)
	{
		pathPos_ = { (int)PosToTile(nextTarget_).getX(), (int)PosToTile(nextTarget_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(posToReach).getX(), (int)PosToTile(posToReach).getY() }, pathPos_);
		if (pathing_.size() > 1)
			nextTarget_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
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

//Inicializa todas las animaciones
void EnemyPirate::initAnims()
{
	//Animación de idle
	//Arriba
	idleAnims_.push_back(Anim(IDLE_U_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, IDLE_U_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateIdleUpAnim));
	//Derecha																						
	idleAnims_.push_back(Anim(IDLE_R_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, IDLE_R_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateIdleRightAnim));
	//Abajo																							
	idleAnims_.push_back(Anim(IDLE_D_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, IDLE_D_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateIdleDownAnim));
	//Izquierda																						
	idleAnims_.push_back(Anim(IDLE_L_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, IDLE_L_FRAME_RATE, true));
	idleTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateIdleLeftAnim));

	//Animación de movimiento
	//Arriba
	moveAnims_.push_back(Anim(MOVE_U_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MOVE_U_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMoveUpAnim));
	//Derecha														
	moveAnims_.push_back(Anim(MOVE_R_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MOVE_R_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMoveRightAnim));
	//Abajo
	moveAnims_.push_back(Anim(MOVE_D_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MOVE_D_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMoveDownAnim));
	//Izquierda
	moveAnims_.push_back(Anim(MOVE_L_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MOVE_L_FRAME_RATE, true));
	moveTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMoveLeftAnim));

	//Animación de disparo
	//Arriba
	shootAnims_.push_back(Anim(SHOOT_U_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, SHOOT_U_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateShootUpAnim));
	//Derecha
	shootAnims_.push_back(Anim(SHOOT_R_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, SHOOT_R_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateShootRightAnim));
	//Abajo
	shootAnims_.push_back(Anim(SHOOT_D_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, SHOOT_D_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateShootDownAnim));
	//Izquierda
	shootAnims_.push_back(Anim(SHOOT_L_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, SHOOT_L_FRAME_RATE, false));
	shootTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateShootLeftAnim));

	//Animación de melee
	//Arriba
	meleeAnims_.push_back(Anim(MELEE_U_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MELEE_U_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMeleeUpAnim));
	//Derecha
	meleeAnims_.push_back(Anim(MELEE_R_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MELEE_R_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMeleeRightAnim));
	//Abajo
	meleeAnims_.push_back(Anim(MELEE_D_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MELEE_D_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMeleeDownAnim));
	//Izquierda
	meleeAnims_.push_back(Anim(MELEE_L_FRAMES, W_H_PIRATE_FRAME, W_H_PIRATE_FRAME, MELEE_L_FRAME_RATE, false));
	meleeTx_.push_back(app_->getTextureManager()->getTexture(Resources::PirateMeleeLeftAnim));

	//Inicializamos con la animación del idle
	currDir_ = DIR::DOWN;
	initIdle();
}

void EnemyPirate::initIdle() {
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void EnemyPirate::initMove() {
	if (currEnemy_ != nullptr) updateDirVisObjective(currEnemy_->getCenter());
	else updateDirVisObjective(target_);
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	currState_ = STATE::PATROLLING;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void EnemyPirate::initShoot() {
	currState_ = STATE::SHOOTING;	//Cambio de estado
	shooted_ = false;	//Aún no se ha creado la bala
	updateDirVisObjective(currEnemy_);	//Hacia dónde mira
	texture_ = shootTx_[(int)currDir_];
	currAnim_ = shootAnims_[(int)currDir_];

	//Asigna el frame donde ocurrirá la acción
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 8;
		break;
	case DIR::RIGHT:
		frameAction_ = 7;
		break;
	case DIR::DOWN:
		frameAction_ = 6;
		break;
	case DIR::LEFT:
		frameAction_ = 8;
	}

	//Inicio de los frames
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	shootCD_.initCooldown(currStats_.distRate_);
}

void EnemyPirate::initMelee() {
	currState_ = STATE::ATTACKING;	//Cambio de estado
	attacked_ = false;	//Aún no se ha atacado
	updateDirVisObjective(currEnemy_);	//Hacia dónde está el enemigo
	texture_ = meleeTx_[(int)currDir_];
	currAnim_ = meleeAnims_[(int)currDir_];
	//Frame exacto del ataque
	switch (currDir_)
	{
	case DIR::UP:
		frameAction_ = 4;
		break;
	case DIR::RIGHT:
		frameAction_ = 5;
		break;
	case DIR::DOWN:
		frameAction_ = 6;
		break;
	case DIR::LEFT:
		frameAction_ = 5;
		break;
	}

	//Se inicia el frame
	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;

	meleeCD_.initCooldown(currStats_.meleeRate_);
}

void EnemyPirate::shootAnim() {
	stop();
	if (!shooted_ && currAnim_.currFrame_ == frameAction_) {
		shoot();
		shooted_ = true;
		shootCD_.initCooldown(currStats_.distRate_);
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		idleCD_.initCooldown(IDLE_PAUSE);
		currEnemy_ = nullptr;
		idle_ = true;
		initIdle();	//Activa el idle
	}
}

void EnemyPirate::meleeAnim() {
	stop();
	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		if (dmg != nullptr) {
			//Critico
			double realDamage = currStats_.meleeDmg_;
			if (applyCritic()) realDamage *= 1.5;

			dmg->receiveDamage(realDamage);
		}
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

//Se encarga de gestionar el ataque a melee o distancia DONE
void EnemyPirate::shoot() {
	Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Bullet),
		getCenter(), currEnemy_->getCenter(), currStats_.distDmg_, BULLET_LIFE, BULLET_VEL);
	app_->getCurrState()->addRenderUpdateListsAsFirst(bullet);
	CollisionCtrl::instance()->addEnemyBullet(bullet);

	//shootCD_.initCooldown(currStats_.distRate_);
}

//Inicializa al pirata
void EnemyPirate::initObject() {
	Enemy::initObject();
	initRewards();
	target_ = pos_;
	nextTarget_ = pos_;
	rangeVision_ = VIS_RANGE;
	/*double w = 1 / 3,
		h = 2 / 3,
		x = 1 / 3,
		y = 1 / 3;
	scaleCollision_.setVec(Vector2D(scale_.getX() * w, scale_.getY() * h));
	posCollision_ = Vector2D(scale_.getX() * x, scale_.getY() * y);*/
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });

	initAnims();
	tag_ = "EnemyPirate";
}

//Esto es un apaño, se eliminara cuando este completa la gestión de muertes
void EnemyPirate::onCollider()
{

}

void EnemyPirate::setPatrol(Vector2D pos)
{
	patrol_.push_back(pos);
}

void EnemyPirate::initialStats()
{
	GameManager* gm_ = GameManager::instance();
	if (gm_->getCurrIsland() == Island::Caribbean) {
		initHealth_ = 800;
		initMana_ = 0;
		initManaReg_ = 0;
		initArmor_ = 15;
		initMeleeDmg = 130;
		initDistDmg = 100;
		initCrit_ = 10;
		initMeleeRange = getScaleX() / 3;
		initDistRange_ = 700;
		initMoveSpeed = 300;
		initMeleeRate_ = 1000;
		initDistRate_ = 1000;
	}
	else {
		initHealth_ = 1500;
		initMana_ = 0;
		initManaReg_ = 0;
		initArmor_ = 15;
		initMeleeDmg = 200;
		initDistDmg = 200;
		initCrit_ = 20;
		initMeleeRange = getScaleX() / 3;
		initDistRange_ = 1500;
		initMoveSpeed = 300;
		initMeleeRate_ = 1000;
		initDistRate_ = 1000;
	}
	initStats(initHealth_, initMana_, initManaReg_, initArmor_, initMeleeDmg, initDistDmg, initCrit_, initMeleeRange, initDistRange_, initMoveSpeed, initMeleeRate_, initDistRate_);
}

void EnemyPirate::initRewards()
{
	minGold = 30;
	maxGold = 70;
	minArchievementPoints = 3;
	maxArchievementPoints = 9;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void EnemyPirate::updateCooldowns()
{
	if (idleCD_.isCooldownActive()) idleCD_.updateCooldown();
	if (meleeCD_.isCooldownActive()) meleeCD_.updateCooldown();
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}

void EnemyPirate::initDie() {
	Enemy::initDie();

	GameManager* gm_ = GameManager::instance();
	missions mission = missions::arlongPark;
	if (gm_->isThatMissionStarted(mission)) {
		gm_->addMissionCounter(mission);
	}
}