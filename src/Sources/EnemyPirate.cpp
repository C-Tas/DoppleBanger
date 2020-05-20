#include "EnemyPirate.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "CaribbeanIslandState.h"
#include <string>

bool EnemyPirate::update() {
#ifdef _DEBUG
	/*string state;
	switch (currAtackStatus_)
	{
	case ATK_STATUS::MELEE:
		state = "melee";
		break;
	case ATK_STATUS::RANGE:
		state = "range";
	default:
		break;
	}
	/*switch (currState_)
	{
	case STATE::ATTACKING:
		state = "atacando";
		break;
	case STATE::DYING:
		state = "muriendo";
		break;
	case STATE::FOLLOWING:
		state = "siguiendo";
		break;
	case STATE::IDLE:
		state = "parado";
		break;
	case STATE::PATROLLING:
		state = "patrullando";
		break;
	default:
		break;
	}*/
#endif // _DEBUG

	updateFrame();
	updateCooldowns();
	//Si el pirata ha muerto
	if (currState_ == STATE::DYING) {
		//Tendría que hacer la animación de muerte?
		//CollisionCtrl::instance()->addEnemiesToErase(this);
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el pirata no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo más cercano
	if ((currState_ == STATE::IDLE || currState_ == STATE::PATROLLING) && getEnemy()) {
		if (onRange()) {
			if (currAtackStatus_ == ATK_STATUS::MELEE && !meleeCD_.isCooldownActive()) {
				initMelee();
			}
			else if (currAtackStatus_ == ATK_STATUS::RANGE && !shootCD_.isCooldownActive()) {
				initShoot();
			}
		}
		else
		{
			currState_ = STATE::FOLLOWING;
			selectTarget();
		}
	}
	//Si el pirata tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING) {
		//Si el pirata tiene un enemigo y lo tiene a rango
		if (onRange()) {
			if (currAtackStatus_ == ATK_STATUS::MELEE) {
				meleeAnim();
			}
			else if (currAtackStatus_ == ATK_STATUS::RANGE) {
				shootAnim();
			}
		}
		else
		{
			currState_ = STATE::FOLLOWING;
			selectTarget();
		}
	}
	//Si el pirata se está moviendo hacia un enemigo
	if (currState_ == STATE::FOLLOWING) {
		if (onRange()) {
			if (currAtackStatus_ == ATK_STATUS::MELEE) {
				meleeAnim();
			}
			else if (currAtackStatus_ == ATK_STATUS::RANGE) {
				shootAnim();
			}
			stop();
		}
		else
		{
			selectTarget();
		}
	}

	if (currState_ == STATE::IDLE && !idleCD_.isCooldownActive()) {
		currState_ = STATE::PATROLLING;
		target_ = patrol_[currPatrol_];
	}
	//Si el pirata está en patrulla
	if (currState_ == STATE::PATROLLING) {
		move(target_);
		SDL_Rect targetPos = SDL_Rect(
			{ (int)target_.getX() / 2,(int)target_.getY() / 2,(int)scale_.getX() / 2,(int)scale_.getY() / 2 });
		SDL_Rect pos = SDL_Rect(
			{ (int)pos_.getX() / 2,(int)pos_.getY() / 2,(int)scale_.getX() / 2,(int)scale_.getY() / 2 });
		if (SDL_HasIntersection(&pos, &targetPos)) {
			initIdle();
			idleCD_.initCooldown(IDLE_PAUSE);
			if (currPatrol_ == patrol_.size() - 1) {
				currPatrol_ = 0;
			}
			else
			{
				currPatrol_++;
			}
		}
	}
	return false;
}


void EnemyPirate::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	if ((getCenter() - target_).magnitude() <= 0.05)
	{
		pathPos_ = { (int)PosToTile(target_).getX(), (int)PosToTile(target_).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(posToReach).getX(), (int)PosToTile(posToReach).getY() }, pathPos_);
		if (pathing_.size() > 1)
			target_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
	}
	dir_.setVec(target_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
	initMove();
}

//Devuelve true si el enemigo que tengo está a rango y en función de ello cambia entre melee y range
bool EnemyPirate::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect enemyRect = SDL_Rect({ (int)currEnemy_->getPosX(),(int)currEnemy_->getPosY(),
		(int)currEnemy_->getScaleX(),(int)currEnemy_->getScaleY() });

	double meleePosX = getPosX() + getScaleX() / 2 - currStats_.meleeRange_ - getScaleX() / 2;
	double meleePosY = getPosY() + getScaleY() / 2 - currStats_.meleeRange_ - getScaleY() / 2;
	double meleeRangeX = currStats_.meleeRange_ + getScaleX() / 2;
	double meleeRangeY = currStats_.meleeRange_ + getScaleY() / 2;

	SDL_Rect meleeAttack = { meleePosX   ,meleePosY,meleeRangeX * 2, meleeRangeY * 2 };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&enemyRect, &meleeAttack)) {
		currAtackStatus_ = ATK_STATUS::MELEE;
		return true;
	}
	else if (currEnemy_ != nullptr) {
		double rangePosX = getPosX() + getScaleX() / 2 - currStats_.distRange_ - getScaleX() / 2;
		double rangePosY = getPosY() + getScaleY() / 2 - currStats_.distRange_ - getScaleY() / 2;
		double rangeAttackX = getScaleX() / 2 + currStats_.distRange_;
		double rangeAttackY = getScaleY() / 2 + currStats_.distRange_;

		SDL_Rect rangeAttack = { rangePosX   ,rangePosY,rangeAttackX * 2, rangeAttackY * 2 };
		if (SDL_HasIntersection(&enemyRect, &rangeAttack)) {
			currAtackStatus_ = ATK_STATUS::RANGE;
			return true;
		}
	}
	else
	{
		false;
	}
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
	cout << "Idle" << endl;
	currState_ = STATE::IDLE;
	texture_ = idleTx_[(int)currDir_];
	currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void EnemyPirate::initMove() {
	updateDirVisObjective(target_);
	texture_ = moveTx_[(int)currDir_];
	currAnim_ = moveAnims_[(int)currDir_];
	if (currState_ != STATE::PATROLLING) {
		currState_ = STATE::PATROLLING;
		frame_.x = 0; frame_.y = 0;
	}

	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

void EnemyPirate::initShoot() {
	currState_ = STATE::ATTACKING;	//Cambio de estado
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
	//Inicia 
	meleeCD_.initCooldown(currStats_.meleeRate_);
}

void EnemyPirate::shootAnim() {
	if (!shooted_ && currAnim_.currFrame_ == frameAction_) {
		attack();
		shooted_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();	//Activa el idle
	}
}

void EnemyPirate::meleeAnim() {
	if (!attacked_ && currAnim_.currFrame_ == frameAction_) {
		attack();

		//if (static_cast<Actor*>(currEnemy_)->getState() == STATE::DYING) attacking_ = false;
		attacked_ = true;
	}
	else if (currAnim_.currFrame_ >= currAnim_.numberFrames_) {
		initIdle();	//Activa el idle
	}
}

//Se encarga de gestionar el ataque a melee o distancia DONE
void EnemyPirate::attack() {
	if (currAtackStatus_ == ATK_STATUS::RANGE) {
		shootCD_.initCooldown(currStats_.distRate_);
		Bullet* bullet = new Bullet(app_, app_->getTextureManager()->getTexture(Resources::Bullet),
			getCenter(), currEnemy_->getCenter(), currStats_.distDmg_);
		app_->getCurrState()->addRenderUpdateLists(bullet);
		CollisionCtrl::instance()->addEnemyBullet(bullet);
	}
	else if (currAtackStatus_ == ATK_STATUS::MELEE)
	{
		//meleeCD_.initCooldown(currStats_.meleeRate_);
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		if (dmg != nullptr) {
			dmg->receiveDamage(currStats_.meleeDmg_);
		}
	}
}

//Inicializa al pirata
void EnemyPirate::initObject() {
	Enemy::initObject();
	initRewards();
	rangeVision_ = VIS_RANGE;
	initAnims();
}

//Esto es un apaño, se eliminara cuando este completa la gestión de muertes
void EnemyPirate::onCollider()
{

}

//Cuando el pirata pierde el agro, se le asigna el agro del player
//Esto lo llama el clon cuando se destruye
void EnemyPirate::lostAggro()
{
	currEnemy_ = GameManager::instance()->getPlayer();
}

//Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_ DONE
bool EnemyPirate::getEnemy() {
	if (Enemy::getEnemy(rangeVision_)) {
		app_->getAudioManager()->playChannel(Resources::AudioId::Agro, 0, Resources::EnemyPirateChannel);
		
		return true;
	}
	else return false;
}

//Cuando el pirata pierde el agro, se le asigna el agro del player
//Esto lo llama el clon cuando se destruye
void EnemyPirate::lostAgro()
{
	currEnemy_ = GameManager::instance()->getPlayer();
}


//Genera la posici�n a la que se mueve el pirata en funci�n de su rango 
void EnemyPirate::selectTarget() {

	Point2D centerPos = { getPosX() + getScaleX() / 2, getPosY() + getScaleY() / 2 };
	Point2D enemycenterPos = { currEnemy_->getPosX() + currEnemy_->getScaleX() / 2, currEnemy_->getPosY() + currEnemy_->getScaleY() / 2 };
	Vector2D posToReach;
	if (currAtackStatus_ == ATK_STATUS::RANGE) {

		posToReach.setX((enemycenterPos.getX() + currStats_.distRange_) - centerPos.getX());
		posToReach.setY((enemycenterPos.getY() + currStats_.distRange_) - centerPos.getY());
	}
	else
	{
		posToReach.setX((enemycenterPos.getX() + currStats_.meleeRange_) - centerPos.getX());
		posToReach.setY((enemycenterPos.getY() + currStats_.meleeRange_) - centerPos.getY());
	}
	target_ = posToReach;
	move(enemycenterPos);
}
void EnemyPirate::initialStats()
{
	HEALTH = 1000;
	MANA = 100;
	MANA_REG = 100;
	ARMOR = 10;
	MELEE_DMG = 0;
	DIST_DMG = 0;
	CRIT = 2000;
	MELEE_RANGE = 50;
	DIST_RANGE = 75;
	MOVE_SPEED = 250;
	MELEE_RATE = 600;
	DIST_RATE = 1500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void EnemyPirate::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}

void EnemyPirate::updateCooldowns()
{
	if (idleCD_.isCooldownActive()) idleCD_.updateCooldown();
	if (meleeCD_.isCooldownActive()) meleeCD_.updateCooldown();
	if (shootCD_.isCooldownActive()) shootCD_.updateCooldown();
}
