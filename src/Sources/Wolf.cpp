#include "Wolf.h"
#include <iostream>
#include "GameManager.h"
#include "Resources.h"
#include "Bullet.h"
#include "CollisionCtrl.h"
#include "CaribbeanIslandState.h"
#include <string>

bool Wolf::update() {
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
	}
	cout << state << endl;*/
#endif // _DEBUG

	//Si el lobo ha muerto
	if (currState_ == STATE::DYING) {
		//Tendr�a que hacer la animaci�n de muerte?
		if (!app_->getMute()) {
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfDie, 0, 3);
		}

		//Esta línea habría que moverla al cangrejo cuando esté hecho
		GameManager* gm_ = GameManager::instance();
		if (gm_->isThatMissionStarted(missions::gallegaEnProblemas)) gm_->addMissionCounter(missions::gallegaEnProblemas);

		applyRewards();
		app_->getCurrState()->removeRenderUpdateLists(this);
		return true;
	}
	//Si el lobo no tiene enemigo al atacar, elige enemigo teniendo prioridad sobre el enemigo m�s cercano
	if ((currState_ == STATE::IDLE || currState_ == STATE::PATROLLING) && getEnemy()) {
		currState_ = STATE::ATTACKING;
	}
	//Si el lobo tiene enemigo y puede atacar
	if (currState_ == STATE::ATTACKING) {
		//Si el lobo tiene un enemigo y lo tiene a rango
		if (onRange()) {
			//changeAnim(attackAnim_);
			attack();
		}
		else
		{
			currState_ = STATE::FOLLOWING;
			//changeAnim(walkAnim_);
			selectTarget();
		}
	}
	//Si el lobo se est� moviendo hacia un enemigo
	if (currState_ == STATE::FOLLOWING) {
		if (onRange()) {
			currState_ = STATE::ATTACKING;
			stop();
			attack();
		}
		else
		{
			//changeAnim(walkAnim_);
			selectTarget();
		}
	}
	if (currState_ == STATE::IDLE && idleTime_ <= (SDL_GetTicks() - lastIdleTime)) {
		currState_ = STATE::PATROLLING;;
		target_ = patrol_[currTarget_];
	}
	//Si el lobo est� en patrulla
	if (currState_ == STATE::PATROLLING) {
		move(target_);
		SDL_Rect targetPos = SDL_Rect(
			{ (int)target_.getX() / 2,(int)target_.getY() / 2,(int)scale_.getX() / 2,(int)scale_.getY() / 2 });
		SDL_Rect pos = SDL_Rect(
			{ (int)pos_.getX() / 2,(int)pos_.getY() / 2,(int)scale_.getX() / 2,(int)scale_.getY() / 2 });
		if (SDL_HasIntersection(&pos, &targetPos)) {
			currState_ = STATE::IDLE;
			lastIdleTime = SDL_GetTicks();
			if (currTarget_ == patrol_.size() - 1) {
				currTarget_ = 0;
			}
			else
			{
				currTarget_++;
			}
		}
	}
	updateFrame();
	return false;
}

//Mueve al lobo DONE
void Wolf::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(posToReach);
	dir_.setX(posToReach.getX() - getCenter().getX());
	dir_.setY(posToReach.getY() - getCenter().getY());
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

	SDL_Rect meleeAttack = { meleePosX   ,meleePosY,meleeRangeX * 2, meleeRangeY * 2 };
	if (currEnemy_ != nullptr && SDL_HasIntersection(&enemyRect, &meleeAttack)) {
		return true;
	}
	else
	{
		false;
	}
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
	if (currStats_.meleeRate_ <= SDL_GetTicks() - lastMeleeHit_)
	{
		lastMeleeHit_ = SDL_GetTicks();
		if (!app_->getMute()) {
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfAttack, 0, 1);
		}
		auto dmg = dynamic_cast<Player*>(currEnemy_);
		if (dmg != nullptr) {
			dmg->receiveDamage(currStats_.meleeDmg_);

		}
	}
}

//Inicializa al lobo
void Wolf::initObject() {
	Enemy::initObject();
	setTexture(app_->getTextureManager()->getTexture(Resources::WolfFront));
	initRewards();
	rangeVision_ = 80;//numero magico
}

//gesti�n de colisiones
void Wolf::onCollider()
{
}

//Cuando el pirata pierde el agro, se le asigna el agro del player
//Esto lo llama el clon cuando se destruye
void Wolf::lostAggro()
{
	currEnemy_ = nullptr;
	currState_ = STATE::PATROLLING;
}

//Genera la posici�n a la que se mueve el pirata en funci�n de su rango 
void Wolf::selectTarget() {

	Point2D centerPos = { getPosX() + getScaleX() / 2, getPosY() + getScaleY() / 2 };
	Point2D enemycenterPos = { currEnemy_->getPosX() + currEnemy_->getScaleX() / 2, currEnemy_->getPosY() + currEnemy_->getScaleY() / 2 };
	Vector2D posToReach;
	posToReach.setX((enemycenterPos.getX() + currStats_.meleeRange_) - centerPos.getX());
	posToReach.setY((enemycenterPos.getY() + currStats_.meleeRange_) - centerPos.getY());
	target_ = posToReach;
	move(enemycenterPos);
}

bool Wolf::getEnemy() {
	if (Enemy::getEnemy(rangeVision_)) {
		if (!app_->getMute()) {
			app_->getAudioManager()->playChannel(Resources::AudioId::WolfHowl, 0, 0);
		}
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
	HEALTH = 1000;
	MANA = 100;
	MANA_REG = 100;
	ARMOR = 10;
	MELEE_DMG = 1;
	DIST_DMG = 1;
	CRIT = 2000;
	MELEE_RANGE = 50;
	DIST_RANGE = 75;
	MOVE_SPEED = 250;
	MELEE_RATE = 1500;
	DIST_RATE = 1500;
	initStats(HEALTH, MANA, MANA_REG, ARMOR, MELEE_DMG, DIST_DMG, CRIT, MELEE_RANGE, DIST_RANGE, MOVE_SPEED, MELEE_RATE, DIST_RATE);
}

void Wolf::initRewards()
{
	minGold = 30;
	maxGold = 50;
	minArchievementPoints = 2;
	maxArchievementPoints = 10;
	goldPoints_ = app_->getRandom()->nextInt(minGold, maxGold + 1);
	achievementPoints_ = app_->getRandom()->nextInt(minArchievementPoints, maxArchievementPoints + 1);
}