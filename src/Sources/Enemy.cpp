#include "Enemy.h"
#include "PlayState.h"
#include "GameManager.h"
#include "Collisions.h"

void Enemy::die()
{
	static_cast<Player*>(GameManager::instance()->getPlayer())->isEnemyDead(this);
	Actor::die();
	//CollisionCtrl::instance()->removeEnemy(this);
	//static_cast<PlayState*>(app_->getCurrState())->removeEnemy(this);
}

Vector2D Enemy::isPlayerInRange(double rangeAttack)
{
	GameManager* gm = GameManager::instance();
	if (gm->getPlayer() == nullptr) { return NOPE; }

	Point2D playerPos = gm->getPlayerPos();
	if (currEnemy_ == nullptr &&
		playerPos.getX() <= pos_.getX() + (getScaleX() / 2) + rangeAttack && playerPos.getX() >= pos_.getX() - rangeAttack
		&& playerPos.getY() <= pos_.getY() + (getScaleY() / 2) + rangeAttack && playerPos.getY() >= pos_.getY() -rangeAttack) {
		return playerPos;
	}
	else
	{
		return  NOPE;
	}
}

Vector2D Enemy::isClonInRange(double n)
{
	GameManager* gm = GameManager::instance();
	if (gm->getClon() == nullptr) { return NOPE ; }

	Point2D clonPos = gm->getClon()->getPos();
	if (currEnemy_ == nullptr &&
		clonPos.getX() <= pos_.getX() + (getScaleX() / 2) + n && clonPos.getX() >= pos_.getX() - n
		&& clonPos.getY() <= pos_.getY() + (getScaleY() / 2) + n && clonPos.getY() >= pos_.getY() - n) {
		//static_cast<Clon*>(gm->getClon())->addAgredEnemy(this);
		return clonPos;
	}
	else
	{
		return NOPE;
	}
}

bool Enemy::getEnemy(double n)
{
	auto gm = GameManager::instance();
	Vector2D playerPos = isPlayerInRange(n);
	Vector2D clonPos = isClonInRange(n);
	if (playerPos == Vector2D(NOPE)&& clonPos == Vector2D(NOPE)) {
		currEnemy_ = nullptr;
		return false;
	}

	Vector2D closesetEnemy;
	closesetEnemy = pos_.getClosest(playerPos, clonPos);
	closesetEnemy == playerPos ? currEnemy_ = gm->getPlayer() : currEnemy_ = gm->getClon();
	return true;
}


void Enemy::initObject()
{
	initialStats();
	destiny_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getX(),(int)scale_.getX(),(int)scale_.getY() });
	scaleCollision_.setVec(Vector2D(scale_.getX(), scale_.getY()));
	collisionArea_ = SDL_Rect({ (int)pos_.getX(),(int)pos_.getY(),(int)scaleCollision_.getX(),(int)scaleCollision_.getY() });
	initAnims();
}

//Devuelve true si el enemigo que tengo está a rango
bool Enemy::onRange() {
	if (currEnemy_ != nullptr) {
		Point2D center = getCenter();
		Point2D currEnemyCenter = currEnemy_->getCenter();
		if (RectBall(currEnemyCenter.getX(), currEnemyCenter.getY(), currEnemy_->getScaleX(), currEnemy_->getScaleY(),
			center.getX(), center.getY(), currStats_.distRange_))
		{
			return true;
		}
	}
	return false;
}