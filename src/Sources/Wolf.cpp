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
			changeAnim(attackAnim_);
			attack();
		}
		else
		{
			currState_ = STATE::FOLLOWING;
			changeAnim(walkAnim_);
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
			changeAnim(walkAnim_);
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
	updateAnim();
	return false;
}

//Mueve al lobo DONE
void Wolf::move(Vector2D posToReach) {
	//establecemos el objetivo para poder parar al llegar
	target_.setVec(posToReach);
	dir_.setX(posToReach.getX() - getCenter(pos_).getX());
	dir_.setY(posToReach.getY() - getCenter(pos_).getY());
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
//void Wolf::initAnims()
//{
//	//Para la animaci�n de ataque
//	attackAnim_ = Anim(NUM_FRAMES_ATK, NUM_FRAMES_ROW_ATK, W_FRAME_ATK, H_FRAME_ATK, FRAME_RATE_ATK, NAME_ATK);
//	//Para la animaci�n de caminar
//	walkAnim_ = Anim(NUM_FRAMES_MOV, NUM_FRAMES_ROW_MOV, W_FRAME_MOV, H_FRAME_MOV, FRAME_RATE_MOV, NAME_MOV);
//	//Para la animaci�n de parado
//	idleAnim_ = Anim(NUM_FRAMES_IDLE, NUM_FRAMES_ROW_ADLE, W_FRAME_IDLE, H_FRAME_IDLE, FRAME_RATE_IDLE, NAME_IDLE);
//}

//Actualiza la animaci�n en funci�n del frameRate de la actual animaci�n DONE
//void Wolf::updateAnim()
//{
//	if (currAnim_.frameRate_ <= SDL_GetTicks() - lastFrame_) {
//		lastFrame_ = SDL_GetTicks();
//		frame_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)currAnim_.widthFrame_,(int)currAnim_.heightFrame_ });
//	}
//}

//Cambia la actual animaci�n del lobo si no la tiene "equipada" DONE
//void Wolf::changeAnim(Anim& newAnim) {
//	if (newAnim.name_ != currAnim_.name_) {
//		currAnim_ = newAnim;
//	}
//}

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
	setTexture(app_->getTextureManager()->getTexture(Resources::WolfFront));
	rangeVision_ = 80;//numero magico
	Enemy::initObject();
}

//gesti�n de colisiones
void Wolf::onCollider()
{
}

//Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_ DONE
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

//Devuelve la posici�n del player si est� a rango DONE
//Vector2D Wolf::isPlayerInRange() {
//	GameManager* gm = GameManager::instance();
//	if (gm->getPlayer() == nullptr) { return { -1,-1 }; }
//
//	Point2D playerPos = gm->getPlayerPos();
//	if (currEnemy_ == nullptr &&
//		playerPos.getX() <= pos_.getX() + (getScaleX() / 2) + rangeVision_ && playerPos.getX() >= pos_.getX() - rangeVision_
//		&& playerPos.getY() <= pos_.getY() + (getScaleY() / 2) + rangeVision_ && playerPos.getY() >= pos_.getY() - rangeVision_) {
//		return playerPos;
//	}
//	else
//	{
//		return  { -1,-1 };
//	}
//}
//
////Devuelve la posici�n del clon si est� a rango DONE
//Vector2D Wolf::isClonInRange() {
//	GameManager* gm = GameManager::instance();
//	if (gm->getClon() == nullptr) { return { -1,-1 }; }
//
//	Point2D clonPos = gm->getClon()->getPos();
//	if (currEnemy_ == nullptr &&
//		clonPos.getX() <= pos_.getX() + (getScaleX() / 2) + rangeVision_ && clonPos.getX() >= pos_.getX() - rangeVision_
//		&& clonPos.getY() <= pos_.getY() + (getScaleY() / 2) + rangeVision_ && clonPos.getY() >= pos_.getY() - rangeVision_) {
//		static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
//		return clonPos;
//	}
//	else
//	{
//		return { -1,-1 };
//	}
//}

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

void Wolf::animationsvar()
{
	//Para el ataque
	 NUM_FRAMES_ATK = 10;
	 NUM_FRAMES_ROW_ATK = 3;
	 W_FRAME_ATK = 200;
	 H_FRAME_ATK = 200;
	 FRAME_RATE_ATK = 100;
	 NAME_ATK = "attack";
	//Para el movimiento
	 NUM_FRAMES_MOV = 10;
	 NUM_FRAMES_ROW_MOV = 3;
	 W_FRAME_MOV = 200;
	 H_FRAME_MOV = 200;
	 FRAME_RATE_MOV = 100;
	 NAME_MOV = "walk";
	//Para estar parado
	 NUM_FRAMES_IDLE = 10;
	 NUM_FRAMES_ROW_ADLE = 3;
	 W_FRAME_IDLE = 200;
	 H_FRAME_IDLE = 200;
	 FRAME_RATE_IDLE = 100;
	 NAME_IDLE = "idle";
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