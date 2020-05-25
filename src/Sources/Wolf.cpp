#include "Wolf.h"
#include "GameManager.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include <string>
#include "PlayState.h"
#include "Collisions.h"

bool Wolf::update() {
#ifdef _DEBUG
//	string state;
//switch (currState_)
//{
//case STATE::ATTACKING:
//	state = "atacando";
//	break;
//case STATE::CHARGING:
//	state = "cargando";
//	break;
//case STATE::DYING:
//	state = "muriendo";
//	break;
//case STATE::FOLLOWING:
//	state = "siguiendo";
//	break;
//case STATE::IDLE:
//	state = "parado";
//	break;
//case STATE::PATROLLING:
//	state = "patrullando";
//	break;
//default:
//	break;
//}
//cout << state << endl;
#endif // _DEBUG

	updateFrame();
	updateCooldowns();

	//Si el lobo ha muerto
	if (currState_ == STATE::DYING) {
		//Tendr�a que hacer la animaci�n de muerte?
		applyRewards();
		dieAnim();
		return true;
	}
	else
	{
		//Si el lobo no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
		if ((currState_ == STATE::IDLE || currState_ == STATE::PATROLLING) && getEnemy()) {
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfDetection, 0, Resources::WolfChannel2);
			currState_ = STATE::ATTACKING;
		}
		//Si el lobo tiene enemigo y puede atacar
		if (currState_ == STATE::ATTACKING) {
			//Si el lobo tiene un enemigo y lo tiene a rango ->ataca
			if (onRange()) {
				attack();
			}
			//Tengo enemigo pero no a rango -> lo sigue
			else
			{
				cout << "FOLLOWING \n";
				currState_ = STATE::FOLLOWING;
				app_->getAudioManager()->playChannel(Resources::AudioId::WolfChase, -1, Resources::WolfChannel1);
				selectTarget();
			}
		}
		//Si el lobo se est� moviendo hacia un enemigo
		if (currState_ == STATE::FOLLOWING) {
			if (onRange()) {
				currState_ = STATE::ATTACKING;
				stop();
			}
			else//sigue follow al player
			{
				//changeAnim(walkAnim_);
				selectTarget();
				if (!Enemy::onRange(rangeVision_)) {
					currEnemy_ = nullptr;
					currState_ = STATE::IDLE;
				}
			}
		}
		//Paso a la siguiente patrulla
		if (currState_ == STATE::IDLE && !idleCD_.isCooldownActive()) {
			currState_ = STATE::PATROLLING;
			target_ = patrol_[currPatrol_];
			cout << "INIT PATROL \n";
		}
		//Si el lobo est� en patrulla
		if (currState_ == STATE::PATROLLING) {
			updateDirVisObjective(target_);
			move(target_);
			//Cuando ha llegado al target empieza el idle
			if (RectRect(getCenter().getX(), getCenter().getY(), getScaleX(), getScaleY(), target_.getX(), target_.getY(), 5, 5)) {
				idleCD_.initCooldown(IDLE_PAUSE);
				currState_ = STATE::IDLE;
				//Pasamos al siguiente patrol
				if (currPatrol_ == patrol_.size() - 1) {
					currPatrol_ = 0;
				}
				else
				{
					currPatrol_++;
				}
			}
		}
	}
	updateFrame();
	return false;
}

//Mueve al lobo DONE
void Wolf::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	if ((getCenter() - nextTarget_).magnitude() <= 0.05)
	{
		pathPos_ = { (int)PosToTile(getCenter()).getX(), (int)PosToTile(getCenter()).getY() };
		pathing_ = ((PlayState*)app_->getCurrState())->getGenerator()->findPath({ (int)PosToTile(posToReach).getX(), (int)PosToTile(posToReach).getY() }, pathPos_);
		if (pathing_.size() > 1)
			nextTarget_.setVec(TileToPos(Vector2D(pathing_[1].x, pathing_[1].y)));
	}
	dir_.setVec(nextTarget_ - getCenter());
	dir_.normalize();
	double delta = app_->getDeltaTime();
	pos_.setX(pos_.getX() + (dir_.getX() * (currStats_.moveSpeed_ * delta)));
	pos_.setY(pos_.getY() + (dir_.getY() * (currStats_.moveSpeed_ * delta)));
}

//Devuelve true si el enemigo que tengo est� a rango DONE
bool Wolf::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect enemyRect = SDL_Rect({ (int)currEnemy_->getPosX(),(int)currEnemy_->getPosY(),
		(int)currEnemy_->getScaleX(),(int)currEnemy_->getScaleY() });

	double meleePosX = getPosX() + getScaleX() / 2 - currStats_.meleeRange_ - getScaleX() / 2;
	double meleePosY = getPosY() + getScaleY() / 2 - currStats_.meleeRange_ - getScaleY() / 2;
	double meleeRangeX = currStats_.meleeRange_ + getScaleX() / 2;
	double meleeRangeY = currStats_.meleeRange_ + getScaleY() / 2;

	SDL_Rect meleeAttack = { (int)round(meleePosX)   ,(int)round(meleePosY),(int)round(meleeRangeX * 2), (int)round(meleeRangeY * 2) };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&enemyRect, &meleeAttack)) {
		return true;
	}
	else
	{
		false;
	}
}

void Wolf::initMove() {
	if (currEnemy_ != nullptr) updateDirVisObjective(currEnemy_->getCenter());
	else updateDirVisObjective(target_);


	frame_.x = 0; frame_.y = 0;
	currState_ = STATE::PATROLLING;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}

//Inicializa todas las animaciones 
void Wolf::initAnims()
{
	//Para la animaci�n de ataque
	attackAnim_ = Anim(NUM_FRAMES_ATK, W_FRAME_ATK, H_FRAME_ATK, FRAME_RATE_ATK, false);
	//Para la animaci�n de caminar
	walkAnim_ = Anim(NUM_FRAMES_MOV, W_FRAME_MOV, H_FRAME_MOV, FRAME_RATE_MOV, true);
	//Para la animaci�n de parado
	idleAnim_ = Anim(NUM_FRAMES_IDLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, true);
}

//Se encarga de gestionar el ataque a melee DONE
void Wolf::attack() {
	if (!meleeCD_.isCooldownActive())
	{
		meleeCD_.initCooldown(currStats_.meleeRate_);
		switch (rand() % 2)
		{
		case 0:
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack1, 0, Resources::WolfChannel1);
			break;
		case 1:
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack2, 0, Resources::WolfChannel1);
			break;
		}
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		if (dmg != nullptr) {
			double realDamage = currStats_.meleeDmg_;
			if (applyCritic()) realDamage *= 1.5;
			dmg->receiveDamage(realDamage);

		}
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
	rangeVision_ = 80;//numero magico
	tag_ = "Wolf";
	switch (rand() % 2)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle1, -1, Resources::WolfChannel1);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle2, -1, Resources::WolfChannel1);
		break;
	}
}

//gesti�n de colisiones
void Wolf::onCollider()
{
}

//Esto lo llama el clon cuando se destruye
void Wolf::lostAggro()
{
	currEnemy_ = nullptr;
	currState_ = STATE::PATROLLING;
	switch (rand() % 2)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle1, -1, Resources::WolfChannel1);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle2, -1, Resources::WolfChannel1);
		break;
	}
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
	switch (rand() % 2)
	{
	case 0:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle1, -1, Resources::WolfChannel1);
		break;
	case 1:
		app_->getAudioManager()->playChannel(Resources::AudioId::WolfIdle2, -1, Resources::WolfChannel1);
		break;
	}
}


void Wolf::initialStats()
{
	HEALTH = 1500;
	MANA = 0;
	MANA_REG = 0;
	ARMOR = 0;
	MELEE_DMG = 450;
	DIST_DMG = 0;
	CRIT = 10;
	MELEE_RANGE = 50;
	DIST_RANGE = 75;
	MOVE_SPEED = 500;
	MELEE_RATE = 1500;
	DIST_RATE = 1500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Wolf::initRewards()
{
	minGold = 110;
	maxGold = 160;
	minArchievementPoints = 4;
	maxArchievementPoints = 10;
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
	//texture_ = idleTx_[(int)currDir_];
	//currAnim_ = idleAnims_[(int)currDir_];

	frame_.x = 0; frame_.y = 0;
	frame_.w = currAnim_.widthFrame_;
	frame_.h = currAnim_.heightFrame_;
}
