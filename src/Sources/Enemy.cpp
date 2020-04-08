#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"

void Enemy::die()
{
	Actor::die();
	CollisionCtrl::instance()->addEnemiesToErase(this);
	static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

//Devuelve true si encontro un enemigo cerca y lo asigna a currEnemy_
bool Enemy::getEnemy() {
	auto gm = GameManager::instance();
	Vector2D playerPos = isPlayerInRange();
	Vector2D clonPos = isClonInRange();
	if (playerPos == Vector2D{ -1,-1 } && clonPos == Vector2D{ -1,-1 }) {
		currEnemy_ = nullptr;
		return false;
	}

	Vector2D closesetEnemy;
	closesetEnemy = pos_.getClosest(playerPos, clonPos);
	closesetEnemy == playerPos ? currEnemy_ = gm->getPlayer() : currEnemy_ = gm->getClon();
	return true;
}

//Devuelve la posición del player si está a rango 
Vector2D Enemy::isPlayerInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return { -1,-1 }; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + (getScaleX() / 2) + currStats_.distRange_ && playerPos.getX() >= pos_.getX() - (getScaleX() / 2) - currStats_.distRange_
		&& playerPos.getY() <= pos_.getY() + (getScaleY() / 2) + currStats_.distRange_ && playerPos.getY() >= pos_.getY() - (getScaleY() / 2) - currStats_.distRange_) {
		return playerPos;
	}
	else
	{
		return  { -1,-1 };
	}
}
//Devuelve la posición del clon si está a rango
Vector2D Enemy::isClonInRange() {
	GameManager* gm = GameManager::instance();
	if (gm->getClon() == nullptr) { return { -1,-1 }; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr &&
		clonPos.getX() <= pos_.getX() + (getScaleX() / 2) + currStats_.distRange_ && clonPos.getX() >= pos_.getX() - (getScaleX() / 2) - currStats_.distRange_
		&& clonPos.getY() <= pos_.getY() + (getScaleY() / 2) + currStats_.distRange_ && clonPos.getY() >= pos_.getY() - (getScaleY() / 2) - currStats_.distRange_) {
		static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
		return clonPos;
	}
	else
	{
		return { -1,-1 };
	}
}

void Enemy::lostAgro()
{
	currEnemy_ = nullptr;
}

//Devuelve true si el enemigo que tengo está a rango
bool Enemy::onRange() {
	if (currEnemy_ == nullptr) {
		return false;
	}
	SDL_Rect rangeAttack = { getPosX() - currStats_.meleeRange_ - (getScaleX() / 2)  ,
	getPosY() - currStats_.meleeRange_ - (getScaleY() / 2),currStats_.meleeRange_ * 2, currStats_.meleeRange_ * 2 };;
	if (currEnemy_ != nullptr && SDL_HasIntersection(&static_cast<Draw*>(currEnemy_)->getDestiny(), &rangeAttack)) {
		return true;
	}
	else
	{
		false;
	}
}
